#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IBufferHandler.hpp"
#include "IEncryption.hpp"
#include "ISocketHandler.hpp"
#include "IEncryption.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

// C++
#include <queue>
#include <utility>

namespace InjectMe::Network
{
	// Класс сокета
	class Socket : public Utils::IBufferHandler
	{
	protected:

		// Нижележащий сокет
		sf::TcpSocket m_socket;

		// Поток обработки нижележащего сокета
		sf::Thread m_socketThread;

		// Очередь пакетов данного сокета
		std::queue<std::pair<sf::Uint16, Utils::Buffer>> m_queue;
		sf::Mutex m_queueMutex;

		// Поток обработки очереди пакетов данного сокета
		sf::Thread m_queueThread;

		// Обработчик событий данного сокета
		ISocketHandler *m_handler = nullptr;

		// Поставщик шифрования для данного сокета
		IEncryption *m_encryption = nullptr;

		// Флаг подключения данного сокета
		bool m_connected = false;

		// Функция потока обработки нижележащего сокета
		virtual void socketFunction();

		// Функция потока обработки очереди пакетов данного сокета
		void queueFunction();

	public:

		// Конструктор сокета
		Socket(ISocketHandler *handler, IEncryption *encryption);

		// Осуществляет подключение данного сокета
		virtual bool Connect();

		// Отправляет данные через данный сокет
		void Send(const char *data, size_t size);

		// Отправляет пакет через данный сокет
		void SendPacket(sf::Uint16 packetID, Utils::Buffer &buffer);

		// Помещает пакет в очередь пакетов данного сокета
		void Enqueue(sf::Uint16 packetID, Utils::Buffer &buffer);

		// Отключает данный сокет
		void Disconnect();

		// Возвращает флаг подключения данного сокета
		bool IsConnected() const;

		// Обработчик события чтения значения из буфера
		void HandleRead(const Utils::Buffer &buffer, void *data, size_t offset, size_t length) final;

		// Обработчик события записи значения в буфер
		void HandleWrite(Utils::Buffer &buffer, char *data, size_t offset, size_t length) final;
	};
}