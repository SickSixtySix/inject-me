#pragma once

// InjectMe
#include "Proxy.hpp"

namespace Cheat::Teleport
{
	// Телепортирует персонажа
	void Teleport(InjectMe::Network::Proxy *proxy, sf::Uint16 mapID, sf::Uint16 posX, sf::Uint16 posY);
}