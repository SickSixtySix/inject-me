// InjectMe
#include "AsdaGlobalPacketFactory.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;

AsdaGlobalPacketFactory *AsdaGlobalPacketFactory::s_instance = nullptr;

AsdaGlobalPacketFactory::AsdaGlobalPacketFactory() {}

AsdaGlobalPacketFactory* AsdaGlobalPacketFactory::Instance()
{
	if (s_instance == nullptr)
		s_instance = new AsdaGlobalPacketFactory();

	return s_instance;
}

Buffer AsdaGlobalPacketFactory::MakePacket(sf::Uint16 packetID)
{
	sf::Uint8 *tpl = nullptr; size_t len;

	if (packetID == 1000)
	{
#include "1000"
		tpl = tpl1000; len = sizeof(tpl1000);
	}
	else if (packetID == 1003)
	{
#include "1003"
		tpl = tpl1003; len = sizeof(tpl1003);
	}
	else if (packetID == 1005)
	{
#include "1005"
		tpl = tpl1005; len = sizeof(tpl1005);
	}
	else if (packetID == 1012)
	{
#include "1012"
		tpl = tpl1012; len = sizeof(tpl1012);
	}
	else if (packetID == 1016)
	{
#include "1016"
		tpl = tpl1016; len = sizeof(tpl1016);
	}
	else if (packetID == 4001)
	{
#include "4001"
		tpl = tpl4001; len = sizeof(tpl4001);
	}
	else if (packetID == 5041)
	{
#include "5041"
		tpl = tpl5041; len = sizeof(tpl5041);
	}
	else if (packetID == 5043)
	{
#include "5043"
		tpl = tpl5043; len = sizeof(tpl5043);
	}
	else if (packetID == 5056)
	{
#include "5056"
		tpl = tpl5056; len = sizeof(tpl5056);
	}
	else if (packetID == 5058)
	{
#include "5058"
		tpl = tpl5058; len = sizeof(tpl5058);
	}
	else if (packetID == 9915)
	{
#include "9915"
		tpl = tpl9915; len = sizeof(tpl9915);
	}
	else if (packetID == 20000)
	{
#include "20000"
		tpl = tpl20000; len = sizeof(tpl20000);
	}

	Buffer buffer;

	if (tpl)
		buffer.Write(tpl, len);

	return buffer;
}