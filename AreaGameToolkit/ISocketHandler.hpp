#pragma once

// InjectMe
#include "Buffer.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// ��������������� ���������� ������ ������
	class Socket;

	// ��������� ����������� ������� ������
	class ISocketHandler
	{
	public:

		// ���������� ������� ����������� ������
		virtual void HandleConnected(Socket *socket) = 0;

		// ���������� ������� �������� ������ �������
		virtual void HandlePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// ���������� ������� �������� ������ ������� �� �������
		virtual void HandleQueuePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// ���������� ������� ���������� ������
		virtual void HandleDisconnected(Socket *socket) = 0;
	};
}