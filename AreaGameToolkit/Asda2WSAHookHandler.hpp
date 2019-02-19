#pragma once

// InjectMe
#include "IProxyHandler.hpp"
#include "IWSAHookHandler.hpp"

// WinAPI
#include <Windows.h>

namespace InjectMe::Hook::WSA
{
	// ����� ����������� ��������� WSA ��� Asda 2
	class Asda2WSAHookHandler : public IWSAHookHandler, public Network::IProxyHandler
	{
		// ��������� ������
		static Asda2WSAHookHandler *s_instance;

		// ���������� ������� ���������� ������
		HANDLE m_event;

		// ����������� ������
		Asda2WSAHookHandler();

	public:

		// ���������� ��������� ������
		static Asda2WSAHookHandler* Instance();

		// ���������� ��������� WSAConnect()
		void HandleWSAConnect(WSAConnectData *data) final;

		// ���������� ������� ���������� ������
		void HandleReady() final;
	};
}