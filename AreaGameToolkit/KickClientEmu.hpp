#pragma once

// InjectMe
#include "ClientEmu.hpp"

namespace InjectMe::Network
{
	class KickClientEmu : public ClientEmu
	{
#pragma region Данные клиента

		// Идентификатор аккаунта данного эмулятора
		sf::Uint32 m_victimAccountID;

		// Номер персонажа аккаунта данного эмулятора
		sf::Uint16 m_victimCharNum;

#pragma endregion

	public:

		// Конструктор эмулятора
		KickClientEmu(const sf::IpAddress &address, sf::Uint16 port, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, sf::Uint32 victimAccountID, sf::Uint16 victimCharNum, IEncryption *encryption, IInnerClientEmu *innerClientEmu = nullptr);

#pragma region События эмулятора (реализация IClientEmu)

		// Обрабатывает пакет сокета игрового сервера
		void HandleGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

#pragma endregion
	};
}