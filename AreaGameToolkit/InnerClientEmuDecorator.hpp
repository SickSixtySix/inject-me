#pragma once

// InjectMe
#include "IInnerClientEmu.hpp"

namespace InjectMe::Network
{
	// Класс внутреннего декоратора эмулятора клиента
	class InnerClientEmuDecorator : public IInnerClientEmu
	{
		// Внутренний декоратор эмулятора клиента
		IInnerClientEmu *m_innerClientEmu;

	protected:

#pragma region События эмулятора (реализация IClientEmu)

		// Обрабатывает событие подключения сокета сервера авторизации
		void HandleAuthConnected() override;

		// Обрабатывает событие подключения сокета игрового сервера
		void HandleGameConnected() override;

		// Обрабатывает пакет сокета сервера авторизации
		void HandleAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Обрабатывает пакет сокета игрового сервера
		void HandleGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Обрабатывает пакет из очереди пакетов сокета сервера авторизации
		void HandleAuthQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Обрабатывает пакет из очереди пакетов сокета игрового сервера
		void HandleGameQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Обрабатывает событие отключения сокета сервера авторизации
		void HandleAuthDisconnected() override;

		// Обрабатывает событие отключения сокета игрового сервера
		void HandleGameDisconnected() override;

#pragma endregion

	public:

		// Конструктор декоратора эмулятора клиента
		InnerClientEmuDecorator(IInnerClientEmu *innerClientEmu = nullptr);
	};
}