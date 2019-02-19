#pragma once

// InjectMe
#include "WSAConnectData.hpp"

namespace InjectMe::Hook::WSA
{
	// Интерфейс обработчика перехвата WSA
	class IWSAHookHandler
	{
	public:

		// Обработчик перехвата WSAConnect()
		virtual void HandleWSAConnect(WSAConnectData *data) = 0;
	};
}