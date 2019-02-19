#pragma once

// InjectMe
#include "Socket.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/TcpListener.hpp>

namespace InjectMe::Network
{
	// Класс серверного сокета
	class ServerSocket : public Socket
	{
		// Служит для ожидания подключения к данному сокету
		sf::TcpListener listener;

		// Порт подключения данного сокета
		sf::Uint16 m_port;

		// Функция потока обработки нижележащего сокета
		void socketFunction() final;

	public:

		// Конструктор сокета
		ServerSocket(sf::Uint16 port, ISocketHandler *handler, IEncryption *encryption);

		// Осуществляет подключение данного сокета
		bool Connect() final;
	};
}