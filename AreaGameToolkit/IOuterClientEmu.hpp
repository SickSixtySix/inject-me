#pragma once

// InjectMe
#include "Buffer.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// Внешний интерфейс эмулятора клиента
	class IOuterClientEmu
	{
	public:

		// Запускает данный эмулятор
		virtual void StartClientEmu() = 0;

#pragma region Отправка пакетов

		// Отправляет пакет через сокет сервера авторизации
		virtual void SendAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// Отправляет пакет через сокет игрового сервера
		virtual void SendGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

#pragma endregion
	};
}