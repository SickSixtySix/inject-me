#pragma once

// InjectMe
#include "IProxyHandler.hpp"
#include "IWSAHookHandler.hpp"

// WinAPI
#include <Windows.h>

namespace InjectMe::Hook::WSA
{
	// Класс обработчика перехвата WSA для Asda 2
	class AsdaGlobalWSAHookHandler : public IWSAHookHandler, public Network::IProxyHandler
	{
		// Экземпляр класса
		static AsdaGlobalWSAHookHandler *s_instance;

		// Дескриптор события готовности прокси
		HANDLE m_event;

		// Конструктор класса
		AsdaGlobalWSAHookHandler();

	public:

		// Возвращает экземпляр класса
		static AsdaGlobalWSAHookHandler* Instance();

		// Обработчик перехвата WSAConnect()
		void HandleWSAConnect(WSAConnectData *data) final;

		// Обработчик события готовности прокси
		void HandleReady() final;
	};
}