#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IEncryption.hpp"
#include "IPacketFactory.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// ����� ������� ������� Asda Global
	class AsdaGlobalPacketFactory : public IPacketFactory
	{
		// ��������� ������� �������
		static AsdaGlobalPacketFactory *s_instance;

		// ����������� ������� �������
		AsdaGlobalPacketFactory();

	public:

		// ���������� ��������� ������� �������
		static AsdaGlobalPacketFactory* Instance();

		// ���������� �����
		Utils::Buffer MakePacket(sf::Uint16 packetID) final;
	};
}