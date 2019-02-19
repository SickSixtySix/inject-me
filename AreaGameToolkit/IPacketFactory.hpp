#pragma once

// InjectMe
#include "Buffer.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// ��������� ������� �������
	class IPacketFactory
	{
	public:

		// ���������� �����
		virtual Utils::Buffer MakePacket(sf::Uint16 packetID) = 0;
	};
}