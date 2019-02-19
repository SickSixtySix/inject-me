#pragma once

// InjectMe
#include "IProxyHandler.hpp"
#include "IWSAHookHandler.hpp"

// WinAPI
#include <Windows.h>

namespace InjectMe::Hook::WSA
{
	// Класс обработчика перехвата WSA для Asda 2
	class Asda2WSAHookHandler : public IWSAHookHandler, public Network::IProxyHandler
	{
		// Экземпляр класса
		static Asda2WSAHookHandler *s_instance;

		// Дескриптор события готовности прокси
		HANDLE m_event;

		// Конструктор класса
		Asda2WSAHookHandler();

	public:

		// Возвращает экземпляр класса
		static Asda2WSAHookHandler* Instance();

		// Обработчик перехвата WSAConnect()
		void HandleWSAConnect(WSAConnectData *data) final;

		// Обработчик события готовности прокси
		void HandleReady() final;
	};
}