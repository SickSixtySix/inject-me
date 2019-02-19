#pragma once

// InjectMe
#include "Buffer.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// Предварительное объявление класса внутреннего декоратора эмулятора клиента
	class InnerClientEmuDecorator;

	// Предварительное объявление класса эмулятора клиента
	class ClientEmu;

	// Внутренний интерфейс эмулятора клиента
	class IInnerClientEmu
	{
	protected:

#pragma region События эмулятора

		// Обрабатывает событие подключения сокета сервера авторизации
		virtual void HandleAuthConnected() = 0;

		// Обрабатывает событие подключения сокета игрового сервера
		virtual void HandleGameConnected() = 0;

		// Обрабатывает пакет сокета сервера авторизации
		virtual void HandleAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// Обрабатывает пакет сокета игрового сервера
		virtual void HandleGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// Обрабатывает пакет из очереди пакетов сокета сервера авторизации
		virtual void HandleAuthQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// Обрабатывает пакет из очереди пакетов сокета игрового сервера
		virtual void HandleGameQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// Обрабатывает событие отключения сокета сервера авторизации
		virtual void HandleAuthDisconnected() = 0;

		// Обрабатывает событие отключения сокета игрового сервера
		virtual void HandleGameDisconnected() = 0;

#pragma endregion

		// Объявление класса декоратора эмулятора клиента дружественным данному классу
		friend class InnerClientEmuDecorator;

		// Объявление класса эмулятора клиента дружественным данному классу
		friend class ClientEmu;
	};
}