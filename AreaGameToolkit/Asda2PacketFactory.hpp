#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IPacketFactory.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// Класс фабрики пакетов Asda 2
	class Asda2PacketFactory : public IPacketFactory
	{
		// Экземпляр фабрики пакетов
		static Asda2PacketFactory *s_instance;

		// Конструктор фабрики пакетов
		Asda2PacketFactory();

	public:

		// Возвращает экземпляр фабрики пакетов
		static Asda2PacketFactory* Instance();

		// Возвращает пакет
		Utils::Buffer MakePacket(sf::Uint16 packetID) final;
	};
}