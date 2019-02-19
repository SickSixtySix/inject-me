#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IEncryption.hpp"
#include "IPacketFactory.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// Класс фабрики пакетов Asda Global
	class AsdaGlobalPacketFactory : public IPacketFactory
	{
		// Экземпляр фабрики пакетов
		static AsdaGlobalPacketFactory *s_instance;

		// Конструктор фабрики пакетов
		AsdaGlobalPacketFactory();

	public:

		// Возвращает экземпляр фабрики пакетов
		static AsdaGlobalPacketFactory* Instance();

		// Возвращает пакет
		Utils::Buffer MakePacket(sf::Uint16 packetID) final;
	};
}