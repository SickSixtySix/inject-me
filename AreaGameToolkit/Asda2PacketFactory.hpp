#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IPacketFactory.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// ����� ������� ������� Asda 2
	class Asda2PacketFactory : public IPacketFactory
	{
		// ��������� ������� �������
		static Asda2PacketFactory *s_instance;

		// ����������� ������� �������
		Asda2PacketFactory();

	public:

		// ���������� ��������� ������� �������
		static Asda2PacketFactory* Instance();

		// ���������� �����
		Utils::Buffer MakePacket(sf::Uint16 packetID) final;
	};
}