#pragma once

// InjectMe
#include "Socket.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/TcpListener.hpp>

namespace InjectMe::Network
{
	// ����� ���������� ������
	class ServerSocket : public Socket
	{
		// ������ ��� �������� ����������� � ������� ������
		sf::TcpListener listener;

		// ���� ����������� ������� ������
		sf::Uint16 m_port;

		// ������� ������ ��������� ������������ ������
		void socketFunction() final;

	public:

		// ����������� ������
		ServerSocket(sf::Uint16 port, ISocketHandler *handler, IEncryption *encryption);

		// ������������ ����������� ������� ������
		bool Connect() final;
	};
}