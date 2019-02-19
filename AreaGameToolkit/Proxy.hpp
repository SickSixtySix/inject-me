#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IProxyHandler.hpp"
#include "ISocketHandler.hpp"
#include "ClientSocket.hpp"
#include "ServerSocket.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

// C++
#include <queue>

namespace InjectMe::Network
{
	// Класс прокси
	class Proxy : public ISocketHandler
	{
	protected:

		// Адрес сервера для подключения данного прокси
		sf::IpAddress m_serverAddress;

		// Порт сервера для подключения данного прокси
		sf::Uint16 m_serverPort;

		// Порт клиента для подключения данного прокси
		sf::Uint16 m_clientPort;

		// Обработчик событий данного прокси
		IProxyHandler *m_handler = nullptr;

		// Поставщик шифрования данного прокси
		IEncryption *m_encryption;

		// Клиентский сокет данного прокси
		ClientSocket *m_clientSocket = nullptr;

		// Серверный сокет данного прокси
		ServerSocket *m_serverSocket = nullptr;

		// Обрабатывает пакет клиентского сокета
		virtual void HandleClientPacket(sf::Uint16 packetID, Utils::Buffer &buffer);

		// Обрабатывает пакет серверного сокета
		virtual void HandleServerPacket(sf::Uint16 packetID, Utils::Buffer &buffer);

		// Обрабатывает пакет из очереди пакетов клиентского сокета
		virtual void HandleClientQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) {};

		// Обрабатывает пакет из очереди пакетов серверного сокета
		virtual void HandleServerQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) {};

		// Добавляет пакет в очередь пакетов клиентского сокета
		void ClientEnqueue(sf::Uint16 packetID, Utils::Buffer &buffer);

		// Добавляет пакет в очередь пакетов серверного сокета
		void ServerEnqueue(sf::Uint16 packetID, Utils::Buffer &buffer);

	public:

		// Конструктор полного прокси
		Proxy(const sf::IpAddress &serverAddress, sf::Uint16 serverPort, sf::Uint16 clientPort, IProxyHandler *handler, IEncryption *encryption);

		// Отправляет пакет через клиентский сокет
		virtual void SendClientPacket(sf::Uint16 packetID, Utils::Buffer &buffer);

		// Отправляет пакет через серверный сокет
		virtual void SendServerPacket(sf::Uint16 packetID, Utils::Buffer &buffer);

		// Возвращает адрес сервера для подключения данного прокси
		const sf::IpAddress& GetServerAddress() const;

		// Возвращает порт сервера для подключения данного прокси
		sf::Uint16 GetServerPort() const;

		// Обработчик события подключения сокета
		void HandleConnected(Socket *socket) override;

		// Обработчик события принятия пакета сокетом
		void HandlePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Обработчик события принятия пакета сокетом из очереди
		void HandleQueuePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Обработчик события отключения сокета
		void HandleDisconnected(Socket *socket) override;
	};
}