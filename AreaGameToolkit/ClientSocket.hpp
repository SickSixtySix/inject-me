#pragma once

// InjectMe
#include "Socket.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/IpAddress.hpp>

namespace InjectMe::Network
{
	// Класс клиентского сокета
	class ClientSocket : public Socket
	{
		// Адрес подключения данного сокета
		sf::IpAddress m_address;

		// Порт подключения данного сокета
		sf::Uint16 m_port;

	public:

		// Конструктор сокета
		ClientSocket(const sf::IpAddress &address, sf::Uint16 port, ISocketHandler *handler, IEncryption *encryption);

		// Осуществляет подключение данного сокета
		bool Connect() final;
	};
}