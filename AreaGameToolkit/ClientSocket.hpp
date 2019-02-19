#pragma once

// InjectMe
#include "Socket.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/IpAddress.hpp>

namespace InjectMe::Network
{
	// ����� ����������� ������
	class ClientSocket : public Socket
	{
		// ����� ����������� ������� ������
		sf::IpAddress m_address;

		// ���� ����������� ������� ������
		sf::Uint16 m_port;

	public:

		// ����������� ������
		ClientSocket(const sf::IpAddress &address, sf::Uint16 port, ISocketHandler *handler, IEncryption *encryption);

		// ������������ ����������� ������� ������
		bool Connect() final;
	};
}