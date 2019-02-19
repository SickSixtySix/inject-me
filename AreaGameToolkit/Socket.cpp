// InjectMe
#include "Memory.hpp"
#include "Socket.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;

// SFML
#include <SFML/System/Lock.hpp>
#include <SFML/System/Sleep.hpp>

void Socket::socketFunction()
{
	// Событие подключения сокета
	m_connected = true;
	m_handler->HandleConnected(this);

	// Запуск потока обработки очереди пакетов
	m_queueThread.launch();

	// Основная область памяти для поступающих данных и их размер
	MEMORY_BLOCK_CHAIN general; ChainAlloc(32768, &general); size_t buffered = 0;

	// Частичная область памяти для поступающих данных и их размер
	MEMORY_BLOCK_CHAIN partial; ChainAlloc(16384, &partial); size_t received = 0;

	while (m_socket.receive(partial.lpAddress, partial.dwSize, received) == sf::Socket::Status::Done)
	{
		// Расширение основной области памяти
		if (general.dwSize - buffered < received)
			ChainReAlloc(buffered + received, &general);

		// Добавление данных в основную область памяти и обновление их размера
		memcpy_s(general.lpAddress + buffered, general.dwSize - buffered, partial.lpAddress, received);
		buffered += received;

		// Смещение внутри основной области памяти
		size_t offset = 0;

		while (buffered - offset > 2)
		{
			// Буфер для участка основной области памяти
			Buffer buffer(general.lpAddress + offset, buffered - offset);

			// Чтение длины пакета
			sf::Uint16 packetLength;
			buffer.Read(1, packetLength);

			// Пакет находится целиком внутри основного буфера
			if (packetLength <= buffer.GetMemory().dwSize)
			{
				// Буфер для текущего пакета
				Buffer packet(general.lpAddress + offset, packetLength);
				packet.SetOffset(packetLength);
				packet.SetHandler(this);

				// Чтение идентификатора пакета
				sf::Uint16 packetID;
				packet.Read(8, packetID);

				// Обработка пакета
				m_handler->HandlePacket(this, packetID, packet);

				// Изменение смещения внутри основного буфера
				offset += packetLength;
			}
			else
				break;
		}

		// Перемещение данных основной области памяти к ее началу
		memmove_s(general.lpAddress, general.dwSize, general.lpAddress + offset, buffered - offset);
		buffered -= offset;
	}

	// Возвращение основной области памяти для поступающих данных в ее хранилище
	ChainFree(general);

	// Возвращение вспомогательной области памяти для поступающих данных в ее хранилище
	ChainFree(partial);

	// Событие отключения сокета
	m_connected = false; 
	m_handler->HandleDisconnected(this);
}

void Socket::queueFunction()
{
	while (m_connected)
	{
		while (true)
		{
			{
				sf::Lock lock(m_queueMutex);
				if (!m_queue.empty())
				{
					auto pair = m_queue.front();
					m_handler->HandleQueuePacket(this, pair.first, pair.second);
					m_queue.pop();
					if (m_queue.empty())
						break;
				}
				else
					break;
			}

			// Задержка 2мс между обработками клиентских пакетов
			sf::sleep(sf::milliseconds(2));
		}

		// Минимальная общая задержка - 2мс
		sf::sleep(sf::milliseconds(2));
	}
}

Socket::Socket(ISocketHandler *handler, IEncryption *encryption) : m_socketThread(&Socket::socketFunction, this), m_queueThread(&Socket::queueFunction, this), m_handler(handler), m_encryption(encryption) {}

bool Socket::Connect()
{
	m_socketThread.launch();
	return true;
}

void Socket::Send(const char *data, size_t size)
{
	if (m_socket.send(data, size) != sf::Socket::Status::Done)
		m_connected = false;
}

void Socket::SendPacket(sf::Uint16 packetID, Buffer &buffer)
{
	// Ключ шифрования
	sf::Uint8 packetKey = static_cast<sf::Uint8>(rand() % 0x100);

	// Запись байта-начала пакета
	buffer.Write(0, static_cast<sf::Uint8>(0xFBu));

	// Запись длины пакета
	buffer.Write(1, static_cast<sf::Uint16>(buffer.GetOffset() + 1));

	// Запись ключа шифрования пакета
	buffer.Write(3, packetKey);

	// Запись идентификатора пакета
	buffer.Write(8, packetID);

	// Запись байта-конца пакета
	buffer.Write(static_cast<sf::Uint8>(0xFEu));

	// Шифрование пакета
	m_encryption->Encrypt(buffer.GetMemory().lpAddress + 4, packetKey, 4, buffer.GetOffset() - 5);

	// Отправка пакета
	Send(buffer.GetMemory().lpAddress, buffer.GetOffset());
}

void Socket::Enqueue(sf::Uint16 packetID, Buffer &buffer)
{
	sf::Lock lock(m_queueMutex);
	m_queue.push({ packetID, buffer });
}

void Socket::Disconnect()
{
	m_socket.disconnect();
	m_connected = false;
}

bool Socket::IsConnected() const
{
	return m_connected;
}

void Socket::HandleRead(const Buffer &buffer, void *data, size_t offset, size_t length)
{
	m_encryption->Encrypt(data, *reinterpret_cast<sf::Uint8*>(buffer.GetMemory().lpAddress + 3), offset, length);
}

void Socket::HandleWrite(Buffer &buffer, char *data, size_t offset, size_t length)
{
	m_encryption->Encrypt(data + offset, *reinterpret_cast<sf::Uint8*>(buffer.GetMemory().lpAddress + 3), offset, length);
}