#pragma once

// InjectMe
#include "IProxyHandler.hpp"
#include "IWSAHookHandler.hpp"

// WinAPI
#include <Windows.h>

namespace InjectMe::Hook::WSA
{
	// ����� ����������� ��������� WSA ��� Asda 2
	class AsdaGlobalWSAHookHandler : public IWSAHookHandler, public Network::IProxyHandler
	{
		// ��������� ������
		static AsdaGlobalWSAHookHandler *s_instance;

		// ���������� ������� ���������� ������
		HANDLE m_event;

		// ����������� ������
		AsdaGlobalWSAHookHandler();

	public:

		// ���������� ��������� ������
		static AsdaGlobalWSAHookHandler* Instance();

		// ���������� ��������� WSAConnect()
		void HandleWSAConnect(WSAConnectData *data) final;

		// ���������� ������� ���������� ������
		void HandleReady() final;
	};
}