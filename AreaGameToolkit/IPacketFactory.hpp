#pragma once

// InjectMe
#include "Buffer.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// Интерфейс фабрики пакетов
	class IPacketFactory
	{
	public:

		// Возвращает пакет
		virtual Utils::Buffer MakePacket(sf::Uint16 packetID) = 0;
	};
}