// InjectMe
#include "Asda2Hook.hpp"
#include "Asda2Proxy.hpp"
#include "Logger.hpp"
#include "Translator.hpp"
//#include "Protection.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;
using namespace InjectMe::Hook::Asda2;

// Addon
#include "DailyBonus.hpp"
#include "MiningWar.hpp"

using namespace Addon::UI::DailyBonus;
using namespace Addon::UI::MiningWar;

// WinAPI
#include <Windows.h>

// Флаг инициализации пользовательского интерфейса
bool Asda2Proxy::s_isUIInitialized = false;

// Флаг инициализации механизма перехвата Asda 2
bool Asda2Proxy::s_isAsda2BypassInitialized = false;

Asda2Proxy *asda2Proxy = nullptr;
sf::Int16 sessionID = 0;

Asda2Proxy::Asda2Proxy(const sf::IpAddress &serverAddress, sf::Uint16 serverPort, sf::Uint16 clientPort, IProxyHandler *handler, IEncryption *encryption)
	: Proxy(serverAddress, serverPort, clientPort, handler, encryption) 
{
	Logger::GetInstance()->printf("Asda2Proxy::Asda2Proxy(): %s:%u -> 127.0.0.1:%u (this = %p)", serverAddress.toString().c_str(), serverPort, clientPort, this);

	asda2Proxy = this;
}

void Asda2Proxy::HandleClientQueuePacket(sf::Uint16 packetID, Buffer &buffer)
{
	buffer.SetHandler(nullptr);
	m_encryption->Encrypt(buffer);

	switch (packetID)
	{
	case 0: break;
	case PacketID::DailyBonusResponse: OpenDailyBonus(buffer); break;
	case PacketID::MiningWarBattleUpdate: HandleBattleUpdate(buffer); break;
	case PacketID::MiningWarMiningUpdate: HandleMiningUpdate(buffer); break;
	case PacketID::MiningWarJoinResponse: HandleJoinResponse(buffer); break;
	case PacketID::MiningWarBattleStarted: HandleBattleStarted(buffer); break;
	case PacketID::MiningWarBattleStopped: HandleBattleStopped(buffer); break;
	case PacketID::MiningWarBattleStartTimeUpdate: HandleBattleStartTimeUpdate(buffer); break;
	}

	if (packetID == 4003)
	{
		buffer.Read(10, sessionID);
	}
}

void Asda2Proxy::HandleServerQueuePacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (packetID == 1003)
	{
		if (s_isAsda2BypassInitialized == false)
		{
			char clientVersion[5];
			buffer.Read(34, clientVersion);

			if (sf::String(clientVersion) == "AGEN")
				SetAsda2Locale(Asda2Locale::English);
			else if (sf::String(clientVersion) == "AGAR")
				SetAsda2Locale(Asda2Locale::Arabian);
			else if (sf::String(clientVersion) == "AGRU")
				SetAsda2Locale(Asda2Locale::Russian);

			// Общие записи (RU)
			Translator::GetInstance()->AddEntry(RU, OK, u8"ОК");
			Translator::GetInstance()->AddEntry(RU, CANCEL, u8"Отмена");

			// Записи шахты духа (RU)
			Translator::GetInstance()->AddEntry(RU, NEXT_WAR_TIME, u8"Время следующей битвы");
			Translator::GetInstance()->AddEntry(RU, NEXT_WAR_TIME_VALUE, u8"%s в %02u:%02u/%02u:%02u");
			Translator::GetInstance()->AddEntry(RU, DOESNT_BELONG_TO_ANY_FACTION, u8"Не принадлежит ни одной фракции");
			Translator::GetInstance()->AddEntry(RU, BELONGS_TO_LIGHT, u8"Принадлежит фракции света");
			Translator::GetInstance()->AddEntry(RU, BELONGS_TO_DARK, u8"Принадлежит фракции тьмы");
			Translator::GetInstance()->AddEntry(RU, BELONGS_TO_CHAOS, u8"Принадлежит фракции хаоса");
			Translator::GetInstance()->AddEntry(RU, N_PLAYERS, u8"игроков");
			Translator::GetInstance()->AddEntry(RU, LIGHT, u8"Свет");
			Translator::GetInstance()->AddEntry(RU, DARK, u8"Тьма");
			Translator::GetInstance()->AddEntry(RU, CHAOS, u8"Хаос");
			Translator::GetInstance()->AddEntry(RU, YOU_HAVE_WON, u8"Вы победили");
			Translator::GetInstance()->AddEntry(RU, YOU_HAVE_LOSE, u8"Вы проиграли");
			Translator::GetInstance()->AddEntry(RU, ADDITIONAL_REWARD, u8"Дополнительные награды");
			Translator::GetInstance()->AddEntry(RU, HONOR_POINT, u8"Очки почета");
			Translator::GetInstance()->AddEntry(RU, NEXT_BATTLE_TIME, u8"Следующая битвы");
			Translator::GetInstance()->AddEntry(RU, MONDAY, u8"Понедельник");
			Translator::GetInstance()->AddEntry(RU, TUESDAY, u8"Вторник");
			Translator::GetInstance()->AddEntry(RU, WEDNESDAY, u8"Среда");
			Translator::GetInstance()->AddEntry(RU, THURSDAY, u8"Четверг");
			Translator::GetInstance()->AddEntry(RU, FRIDAY, u8"Пятница");
			Translator::GetInstance()->AddEntry(RU, SATURDAY, u8"Суббота");
			Translator::GetInstance()->AddEntry(RU, SUNDAY, u8"Воскресенье");

			// Общие записи (EN)
			Translator::GetInstance()->AddEntry(EN, OK, "OK");
			Translator::GetInstance()->AddEntry(EN, CANCEL, "Cancel");

			// Записи шахты духа (EN)
			Translator::GetInstance()->AddEntry(EN, NEXT_WAR_TIME, "Next war time");
			Translator::GetInstance()->AddEntry(EN, NEXT_WAR_TIME_VALUE, u8"%s %02u:%02u/%02u:%02u");
			Translator::GetInstance()->AddEntry(EN, DOESNT_BELONG_TO_ANY_FACTION, "Doesn't belong to any faction.");
			Translator::GetInstance()->AddEntry(EN, BELONGS_TO_LIGHT, u8"Belongs to light");
			Translator::GetInstance()->AddEntry(EN, BELONGS_TO_DARK, u8"Belongs to dark");
			Translator::GetInstance()->AddEntry(EN, BELONGS_TO_CHAOS, u8"Belongs to chaos");
			Translator::GetInstance()->AddEntry(EN, N_PLAYERS, "Players");
			Translator::GetInstance()->AddEntry(EN, LIGHT, "Light");
			Translator::GetInstance()->AddEntry(EN, DARK, "Dark");
			Translator::GetInstance()->AddEntry(EN, CHAOS, "Chaos");
			Translator::GetInstance()->AddEntry(EN, YOU_HAVE_WON, "You Have Won");
			Translator::GetInstance()->AddEntry(EN, YOU_HAVE_LOSE, "You Have Lose");
			Translator::GetInstance()->AddEntry(EN, ADDITIONAL_REWARD, "Additional reward");
			Translator::GetInstance()->AddEntry(EN, HONOR_POINT, "Honor Point");
			Translator::GetInstance()->AddEntry(EN, NEXT_BATTLE_TIME, "Next Battle Time");
			Translator::GetInstance()->AddEntry(EN, MONDAY, "Monday");
			Translator::GetInstance()->AddEntry(EN, TUESDAY, "Tuesday");
			Translator::GetInstance()->AddEntry(EN, WEDNESDAY, "Wednesday");
			Translator::GetInstance()->AddEntry(EN, THURSDAY, "Thursday");
			Translator::GetInstance()->AddEntry(EN, FRIDAY, "Friday");
			Translator::GetInstance()->AddEntry(EN, SATURDAY, "Saturday");
			Translator::GetInstance()->AddEntry(EN, SUNDAY, "Sunday");

			s_isAsda2BypassInitialized = true;
			StartAsda2Hook();
		}
	}
	else if (packetID == 5055 || packetID == 6015)
	{
		CloseDailyBonus();
	}
	else if (packetID == 9915)
	{
		Buffer outBuffer; outBuffer.SetOffset(10);
		SendClientPacket(6666, outBuffer);
	}
	else if (packetID == 20000)
	{
		AppendMiscButtonHandler(this);
		AppendNPCButtonHandler(this);
	}
}

void Asda2Proxy::HandleClientPacket(sf::Uint16 packetID, Buffer &buffer)
{
	// Отправка в очередь
	switch (packetID)
	{
	case 0: break;
	// TODO
	case 4003: 
		ClientEnqueue(packetID, buffer);
		break;
	}

	// Сброс
	switch (packetID)
	{
	case PacketID::DailyBonusResponse:
	case PacketID::MiningWarBattleUpdate:
	case PacketID::MiningWarMiningUpdate:
	case PacketID::MiningWarJoinResponse:
	case PacketID::MiningWarBattleStarted:
	case PacketID::MiningWarBattleStopped:
	case PacketID::MiningWarBattleStartTimeUpdate:
		ClientEnqueue(packetID, buffer);
		break;
	default:
		Proxy::HandleClientPacket(packetID, buffer);
	}
}

void Asda2Proxy::HandleServerPacket(sf::Uint16 packetID, Buffer &buffer)
{
	// Отправка в очередь
	switch (packetID)
	{
	case 1003:
	case 5055:
	case 6015:
	case 9915:
	case 20000:
		ServerEnqueue(packetID, buffer);
		break;
	}

	// Сброс
	switch (packetID)
	{
	case 0: break;
	default:
		Proxy::HandleServerPacket(packetID, buffer);
	}
}

void Asda2Proxy::HandleConnected(Socket *socket)
{
	if (m_clientSocket == socket)
	{
		Logger::GetInstance()->printf("Asda2Proxy::HandleConnected(): proxy connected to server (this = %p)", this);

		// TODO: Вернуть (защита!)
		//Buffer outBuffer; outBuffer.SetOffset(10);
		//QueryProtectionInfo(outBuffer);
		//m_clientSocket->SendPacket(6668, outBuffer);
	}
	else if (m_serverSocket == socket)
		Logger::GetInstance()->printf("Asda2Proxy::HandleConnected(): client connected to proxy (this = %p)", this);

	Proxy::HandleConnected(socket);
}

void Asda2Proxy::HandleMiscButton(const MiscButtonData &args)
{
	if (args._Std_MiscIndex == 17 && !IsDailyBonusActive())
	{
		Buffer outBuffer; outBuffer.SetOffset(10);
		SendClientPacket(PacketID::DailyBonusRequest, outBuffer);
	}
}

void Asda2Proxy::HandleNPCButton(const NPCButtonData &args)
{
	//if (args._Std_ActionIndex > 0)
	//{
	//	MessageBox(NULL, L"", NULL, MB_OK);
	//	Buffer outBuffer; outBuffer.SetOffset(10);
	//	SendClientPacket(PacketID::MiningWarJoinRequest, outBuffer);
	//}
}