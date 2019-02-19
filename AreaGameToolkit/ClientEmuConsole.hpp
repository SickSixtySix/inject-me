#pragma once

// InjectMe
#include "InnerClientEmuDecorator.hpp"

namespace InjectMe::Network
{
	// Класс внутреннего декоратора эмулятора клиента
	class ClientEmuConsole : public InnerClientEmuDecorator
	{
		// Количество персонажей
		size_t m_charactersCount = 0;

	public:

		// Конструктор внутреннего декоратора эмулятора клиента
		ClientEmuConsole(IInnerClientEmu *innerClientEmu = nullptr);

#pragma region События эмулятора (реализация IClientEmu)

		// Обрабатывает событие подключения сокета сервера авторизации
		void HandleAuthConnected() override;

		// Обрабатывает событие подключения сокета игрового сервера
		void HandleGameConnected() override;

		// Обрабатывает пакет сокета сервера авторизации
		void HandleAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Обрабатывает пакет сокета игрового сервера
		void HandleGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

#pragma endregion
	};
}