#pragma once

// InjectMe
#include "Proxy.hpp"
#include "IMiscButtonHandler.hpp"
#include "INPCButtonHandler.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/IpAddress.hpp>

// Пакеты DailyBonus
// DailyBonusRequest [out] (запрос на информацию о ежедневном бонусе)
// DailyBonusResponse [in] (ответ с информацией о ежеденвном бонусе)

// Пакеты MiningWar
// MiningWarBattleUpdate [in] (обновление фазы битвы)
// MiningWarMiningUpdate [in] (обновление фазы добычи)
// MiningWarJoinRequest [out] (запрос на вход)
// MiningWarJoinResponse [in] (ответ с информацией о входе)
// MiningWarJoinRequestOK [out] (запрос на вход на карту шахты духа)
// MiningWarBattleStarted [in] (информирование о начале битвы)
// MiningWarBattleStopped [in] (информирование о конце битвы)
// MiningWarBattleStartTimeUpdate [in] (обновление времени начала битвы)

namespace InjectMe::Network
{
	enum PacketID : sf::Uint16
	{
		// Пакеты DailyBonus
		DailyBonusRequest = 6666,
		DailyBonusResponse,

		// Пакеты MiningWar
		MiningWarBattleUpdate,
		MiningWarMiningUpdate,
		MiningWarJoinRequest,
		MiningWarJoinResponse,
		MiningWarJoinRequestOK,
		MiningWarBattleStarted,
		MiningWarBattleStopped,
		MiningWarBattleStartTimeUpdate
	};

	class Asda2Proxy : public Proxy, public Hook::Asda2::IMiscButtonHandler, public Hook::Asda2::INPCButtonHandler
	{
		// Флаг инициализации пользовательского интерфейса
		static bool s_isUIInitialized;

		// Флаг инициализации механизма перехвата Asda 2
		static bool s_isAsda2BypassInitialized;

	public:

		// Конструктор прокси
		Asda2Proxy(const sf::IpAddress &serverAddress, sf::Uint16 serverPort, sf::Uint16 clientPort, IProxyHandler *handler, IEncryption *encryption);

		// Обрабатывает пакет из клиентской очереди данного прокси
		void HandleClientQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// Обрабатывает пакет из серверной очереди данного прокси
		void HandleServerQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// Обрабатывает клиентский пакет в реальном времени
		void HandleClientPacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// Обрабатывает серверный пакет в реальном времени
		void HandleServerPacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// Обработчик события подключения сокета
		void HandleConnected(Socket *socket) final;

		// Обработчик события нажатия кнопки в дополнительном меню
		void HandleMiscButton(const Hook::Asda2::MiscButtonData &args) final;

		// Обработчик события нажатия кнопки в диалоге с NPC
		void HandleNPCButton(const Hook::Asda2::NPCButtonData &args) final;
	};
}