// InjectMe
#include "AsdaGlobalEncryption.hpp"
#include "AsdaGlobalProxy.hpp"
#include "AsdaGlobalWSAHookHandler.hpp"

using namespace InjectMe::Network;
using namespace InjectMe::Hook::WSA;

// WinAPI
#include <Windows.h>

AsdaGlobalWSAHookHandler *AsdaGlobalWSAHookHandler::s_instance = nullptr;

AsdaGlobalWSAHookHandler::AsdaGlobalWSAHookHandler() {}

AsdaGlobalWSAHookHandler* AsdaGlobalWSAHookHandler::Instance()
{
	if (s_instance == nullptr)
		s_instance = new AsdaGlobalWSAHookHandler();

	return s_instance;
}

void AsdaGlobalWSAHookHandler::HandleWSAConnect(WSAConnectData *data)
{
	m_event = CreateEvent(NULL, FALSE, FALSE, NULL);

	data->SourcePort = 4010;
	auto proxy = new AsdaGlobalProxy(
		sf::IpAddress(data->b1, data->b2, data->b3, data->b4), data->DestinationPort, data->SourcePort, "samprplover1", "jv^9m^bk", 0x0000BE50, 0x000D, 256, 256, this, AsdaGlobalEncryption::Instance()
	);
	//auto proxy = new AsdaGlobalProxy(
	//	sf::IpAddress(data->b1, data->b2, data->b3, data->b4), data->DestinationPort, data->SourcePort, "Samuel267", "due?_r6q", 0x0000BEF9, 0x000A, 256, 256, this, AsdaGlobalEncryption::Instance()
	//);

	//char msg[256];
	//sprintf_s(msg, "%s:%u", sf::IpAddress(data->b1, data->b2, data->b3, data->b4).toString().c_str(), data->DestinationPort);
	//MessageBoxA(NULL, msg, NULL, MB_OK);

	WaitForSingleObject(m_event, INFINITE);
}

void AsdaGlobalWSAHookHandler::HandleReady()
{
	SetEvent(m_event);
}