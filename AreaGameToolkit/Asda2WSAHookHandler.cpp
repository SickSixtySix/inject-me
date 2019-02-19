// InjectMe
#include "Asda2WSAHookHandler.hpp"
#include "Asda2Encryption.hpp"
#include "Asda2Proxy.hpp"
#include "Logger.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;
using namespace InjectMe::Hook::WSA;

// WinAPI
#include <Windows.h>

Asda2WSAHookHandler *Asda2WSAHookHandler::s_instance = nullptr;

Asda2WSAHookHandler::Asda2WSAHookHandler() {}

Asda2WSAHookHandler* Asda2WSAHookHandler::Instance()
{
	if (s_instance == nullptr)
		s_instance = new Asda2WSAHookHandler();

	return s_instance;
}

void Asda2WSAHookHandler::HandleWSAConnect(WSAConnectData *data)
{
	m_event = CreateEvent(NULL, FALSE, FALSE, NULL);

	Logger::GetInstance()->printf("Asda2WSAHookHandler::HandleWSAConnect(): %u.%u.%u.%u:%u -> 127.0.0.1:4010 (m_event = %p)", data->b1, data->b2, data->b3, data->b4, data->b4, data->DestinationPort, m_event);

	data->SourcePort = 4010;
	auto proxy = new Asda2Proxy(
		sf::IpAddress(data->b1, data->b2, data->b3, data->b4), data->DestinationPort, data->SourcePort, this, Asda2Encryption::Instance()
	);

	WaitForSingleObject(m_event, INFINITE);
}

void Asda2WSAHookHandler::HandleReady()
{
	Logger::GetInstance()->printf("Asda2WSAHookHandler::HandleReady() (m_event = %p)", m_event);

	SetEvent(m_event);
}