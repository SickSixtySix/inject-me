#pragma once

// InjectMe
#include "Proxy.hpp"
#include "IMiscButtonHandler.hpp"
#include "INPCButtonHandler.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/IpAddress.hpp>

// ������ DailyBonus
// DailyBonusRequest [out] (������ �� ���������� � ���������� ������)
// DailyBonusResponse [in] (����� � ����������� � ���������� ������)

// ������ MiningWar
// MiningWarBattleUpdate [in] (���������� ���� �����)
// MiningWarMiningUpdate [in] (���������� ���� ������)
// MiningWarJoinRequest [out] (������ �� ����)
// MiningWarJoinResponse [in] (����� � ����������� � �����)
// MiningWarJoinRequestOK [out] (������ �� ���� �� ����� ����� ����)
// MiningWarBattleStarted [in] (�������������� � ������ �����)
// MiningWarBattleStopped [in] (�������������� � ����� �����)
// MiningWarBattleStartTimeUpdate [in] (���������� ������� ������ �����)

namespace InjectMe::Network
{
	enum PacketID : sf::Uint16
	{
		// ������ DailyBonus
		DailyBonusRequest = 6666,
		DailyBonusResponse,

		// ������ MiningWar
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
		// ���� ������������� ����������������� ����������
		static bool s_isUIInitialized;

		// ���� ������������� ��������� ��������� Asda 2
		static bool s_isAsda2BypassInitialized;

	public:

		// ����������� ������
		Asda2Proxy(const sf::IpAddress &serverAddress, sf::Uint16 serverPort, sf::Uint16 clientPort, IProxyHandler *handler, IEncryption *encryption);

		// ������������ ����� �� ���������� ������� ������� ������
		void HandleClientQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// ������������ ����� �� ��������� ������� ������� ������
		void HandleServerQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// ������������ ���������� ����� � �������� �������
		void HandleClientPacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// ������������ ��������� ����� � �������� �������
		void HandleServerPacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// ���������� ������� ����������� ������
		void HandleConnected(Socket *socket) final;

		// ���������� ������� ������� ������ � �������������� ����
		void HandleMiscButton(const Hook::Asda2::MiscButtonData &args) final;

		// ���������� ������� ������� ������ � ������� � NPC
		void HandleNPCButton(const Hook::Asda2::NPCButtonData &args) final;
	};
}