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
	// ������� ����������� ������
	m_connected = true;
	m_handler->HandleConnected(this);

	// ������ ������ ��������� ������� �������
	m_queueThread.launch();

	// �������� ������� ������ ��� ����������� ������ � �� ������
	MEMORY_BLOCK_CHAIN general; ChainAlloc(32768, &general); size_t buffered = 0;

	// ��������� ������� ������ ��� ����������� ������ � �� ������
	MEMORY_BLOCK_CHAIN partial; ChainAlloc(16384, &partial); size_t received = 0;

	while (m_socket.receive(partial.lpAddress, partial.dwSize, received) == sf::Socket::Status::Done)
	{
		// ���������� �������� ������� ������
		if (general.dwSize - buffered < received)
			ChainReAlloc(buffered + received, &general);

		// ���������� ������ � �������� ������� ������ � ���������� �� �������
		memcpy_s(general.lpAddress + buffered, general.dwSize - buffered, partial.lpAddress, received);
		buffered += received;

		// �������� ������ �������� ������� ������
		size_t offset = 0;

		while (buffered - offset > 2)
		{
			// ����� ��� ������� �������� ������� ������
			Buffer buffer(general.lpAddress + offset, buffered - offset);

			// ������ ����� ������
			sf::Uint16 packetLength;
			buffer.Read(1, packetLength);

			// ����� ��������� ������� ������ ��������� ������
			if (packetLength <= buffer.GetMemory().dwSize)
			{
				// ����� ��� �������� ������
				Buffer packet(general.lpAddress + offset, packetLength);
				packet.SetOffset(packetLength);
				packet.SetHandler(this);

				// ������ �������������� ������
				sf::Uint16 packetID;
				packet.Read(8, packetID);

				// ��������� ������
				m_handler->HandlePacket(this, packetID, packet);

				// ��������� �������� ������ ��������� ������
				offset += packetLength;
			}
			else
				break;
		}

		// ����������� ������ �������� ������� ������ � �� ������
		memmove_s(general.lpAddress, general.dwSize, general.lpAddress + offset, buffered - offset);
		buffered -= offset;
	}

	// ����������� �������� ������� ������ ��� ����������� ������ � �� ���������
	ChainFree(general);

	// ����������� ��������������� ������� ������ ��� ����������� ������ � �� ���������
	ChainFree(partial);

	// ������� ���������� ������
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

			// �������� 2�� ����� ����������� ���������� �������
			sf::sleep(sf::milliseconds(2));
		}

		// ����������� ����� �������� - 2��
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
	// ���� ����������
	sf::Uint8 packetKey = static_cast<sf::Uint8>(rand() % 0x100);

	// ������ �����-������ ������
	buffer.Write(0, static_cast<sf::Uint8>(0xFBu));

	// ������ ����� ������
	buffer.Write(1, static_cast<sf::Uint16>(buffer.GetOffset() + 1));

	// ������ ����� ���������� ������
	buffer.Write(3, packetKey);

	// ������ �������������� ������
	buffer.Write(8, packetID);

	// ������ �����-����� ������
	buffer.Write(static_cast<sf::Uint8>(0xFEu));

	// ���������� ������
	m_encryption->Encrypt(buffer.GetMemory().lpAddress + 4, packetKey, 4, buffer.GetOffset() - 5);

	// �������� ������
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