#pragma once

// InjectMe
#include "IOuterClientEmu.hpp"

namespace InjectMe::Network
{
	// Класс внешнего декоратора эмулятора клиента
	class OuterClientEmuDecorator : public IOuterClientEmu
	{
		// Вышестоящий эмулятора клиента или его декоратор
		IOuterClientEmu *m_outerClientEmu = nullptr;

	public:

		// Конструктор внешнего декоратора
		OuterClientEmuDecorator(IOuterClientEmu *clientEmu);

		// Запускает данный эмулятор
		void StartClientEmu() override;

#pragma region Отправка пакетов (реализация IClientEmu)

		// Отправляет пакет через сокет сервера авторизации
		void SendAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Отправляет пакет через сокет игрового сервера
		void SendGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

#pragma endregion
	};
}