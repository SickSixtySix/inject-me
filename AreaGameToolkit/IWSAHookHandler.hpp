#pragma once

// InjectMe
#include "WSAConnectData.hpp"

namespace InjectMe::Hook::WSA
{
	// ��������� ����������� ��������� WSA
	class IWSAHookHandler
	{
	public:

		// ���������� ��������� WSAConnect()
		virtual void HandleWSAConnect(WSAConnectData *data) = 0;
	};
}