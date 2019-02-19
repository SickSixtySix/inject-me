// InjectMe
#include "Logger.hpp"
#include "WSAHook.hpp"

using namespace InjectMe::Utils;

// WinAPI
#include <ws2tcpip.h>

// C
#include <stdio.h>

// C++
#include <map>

// Detours
#include "Detours/Detours.h"

namespace InjectMe::Hook::WSA
{
	// WSA hook handler
	IWSAHookHandler *wsaHookHandler = nullptr;

	//#define WSADETOURS_DEBUG

#ifdef WSADETOURS_DEBUG
#define WSADETOURS_DEBUG_MSG(X) MessageBox(NULL, X, "WSADetours debug message", MB_OK)
#else
#define WSADETOURS_DEBUG_MSG(X)
#endif

	// connect detour context
	typedef int (WSAAPI *connectProc) (
		SOCKET         s,
		const sockaddr *name,
		int            namelen
	);

	// connect (WSOCK32.dll) detour
	int WSAAPI _My_connect_WSOCK32(
		SOCKET         s,
		const sockaddr *name,
		int            namelen
	);

	// connect (WSOCK32.dll) detour context
	connectProc _Std_connect_WSOCK32;

	// connect (WSOCK32.dll) detour
	int WSAAPI _My_connect_WSOCK32(
		SOCKET         s,
		const sockaddr *name,
		int            namelen
	)
	{
		auto name_in =
			reinterpret_cast<struct sockaddr_in*>(
				const_cast<struct sockaddr*>(
					name
					)
				);

		Logger::GetInstance()->printf("_My_connect_WSOCK32(): %u.%u.%u.%u:%u -> 127.0.0.1:4010",
			name_in->sin_addr.S_un.S_un_b.s_b1,
			name_in->sin_addr.S_un.S_un_b.s_b2,
			name_in->sin_addr.S_un.S_un_b.s_b3,
			name_in->sin_addr.S_un.S_un_b.s_b4,
			ntohs(name_in->sin_port)
		);

		return _Std_connect_WSOCK32(s, name, namelen);
	}

	// connect (ws2_32.dll) detour
	int WSAAPI _My_connect_ws2_32(
		SOCKET         s,
		const sockaddr *name,
		int            namelen
	);

	// connect (ws2_32.dll) detour context
	connectProc _Std_connect_ws2_32;

	// connect (ws2_32.dll) detour
	int WSAAPI _My_connect_ws2_32(
		SOCKET         s,
		const sockaddr *name,
		int            namelen
	)
	{
		auto name_in =
			reinterpret_cast<struct sockaddr_in*>(
				const_cast<struct sockaddr*>(
					name
					)
				);

		Logger::GetInstance()->printf("_My_connect_ws2_32(): %u.%u.%u.%u:%u -> 127.0.0.1:4010",
			name_in->sin_addr.S_un.S_un_b.s_b1,
			name_in->sin_addr.S_un.S_un_b.s_b2,
			name_in->sin_addr.S_un.S_un_b.s_b3,
			name_in->sin_addr.S_un.S_un_b.s_b4,
			ntohs(name_in->sin_port)
		);

		return _Std_connect_ws2_32(s, name, namelen);
	}

	// WSAConnect detour context
	typedef int (WSAAPI *WSAConnectProc) (
		SOCKET                s,
		const struct sockaddr *name,
		int                   namelen,
		LPWSABUF              lpCallerData,
		LPWSABUF              lpCalleeData,
		LPQOS                 lpSQOS,
		LPQOS                 lpGQOS
	);

	// WSAConnect detour
	int WSAAPI _My_WSAConnect(
		SOCKET                s,
		const struct sockaddr *name,
		int                   namelen,
		LPWSABUF              lpCallerData,
		LPWSABUF              lpCalleeData,
		LPQOS                 lpSQOS,
		LPQOS                 lpGQOS
	);

	// WSAConnect detour context
	WSAConnectProc _Std_WSAConnect;
	SOCKET _Std_WSAConnectSocket;

	// WSAConnect detour
	int WSAAPI _My_WSAConnect(
		SOCKET                s,
		const struct sockaddr *name,
		int                   namelen,
		LPWSABUF              lpCallerData,
		LPWSABUF              lpCalleeData,
		LPQOS                 lpSQOS,
		LPQOS                 lpGQOS
	)
	{
#ifdef WSADETOURS_DEBUG

		WSADETOURS_DEBUG_MSG("_My_WSAConnect()");

#endif

		auto name_in =
			reinterpret_cast<struct sockaddr_in*>(
				const_cast<struct sockaddr*>(
					name
					)
				);

		WSAConnectData wsaBypassData = {
			name_in->sin_addr.S_un.S_un_b.s_b1,
			name_in->sin_addr.S_un.S_un_b.s_b2,
			name_in->sin_addr.S_un.S_un_b.s_b3,
			name_in->sin_addr.S_un.S_un_b.s_b4,
			ntohs(name_in->sin_port),
			0
		};

		Logger::GetInstance()->printf("_My_WSAConnect(): %u.%u.%u.%u:%u -> 127.0.0.1:4010",
			name_in->sin_addr.S_un.S_un_b.s_b1,
			name_in->sin_addr.S_un.S_un_b.s_b2,
			name_in->sin_addr.S_un.S_un_b.s_b3,
			name_in->sin_addr.S_un.S_un_b.s_b4,
			ntohs(name_in->sin_port)
		);

		wsaHookHandler->HandleWSAConnect(
			&wsaBypassData
		);

		name_in->sin_addr.S_un.S_un_b.s_b1 = static_cast<UCHAR>(0x7Fu);
		name_in->sin_addr.S_un.S_un_b.s_b2 = static_cast<UCHAR>(0x00u);
		name_in->sin_addr.S_un.S_un_b.s_b3 = static_cast<UCHAR>(0x00u);
		name_in->sin_addr.S_un.S_un_b.s_b4 = static_cast<UCHAR>(0x01u);
		name_in->sin_port = htons(wsaBypassData.SourcePort);

		_Std_WSAConnectSocket = s;

		return _Std_WSAConnect(s, name, namelen, lpCallerData, lpCalleeData, lpSQOS, lpGQOS);
	}

#include "Detours/Detours.h"

	DWORD WINAPI WSAHookThread(LPVOID lpParam)
	{
		Logger::GetInstance()->printf("WSAHookThread()");

		while (GetModuleHandle(TEXT("ws2_32.dll")) == NULL);

		auto detourResult = Detours::HookFunction(
			GetProcAddress(GetModuleHandle(TEXT("ws2_32.dll")), "WSAConnect"),
			_My_WSAConnect, reinterpret_cast<void**>(&_Std_WSAConnect));

		Logger::GetInstance()->printf("WSAHookThread(): WSAConnect detourResult = %d", static_cast<int>(detourResult));

		detourResult = Detours::HookFunction(
			GetProcAddress(GetModuleHandle(TEXT("ws2_32.dll")), "connect"),
			_My_connect_ws2_32, reinterpret_cast<void**>(&_Std_connect_ws2_32));

		Logger::GetInstance()->printf("WSAHookThread(): connect (ws2_32.dll) detourResult = %d", static_cast<int>(detourResult));

		while (GetModuleHandle(TEXT("WSOCK32.dll")) == NULL);
		detourResult = Detours::HookFunction(
			GetProcAddress(GetModuleHandle(TEXT("WSOCK32.dll")), "connect"),
			_My_connect_WSOCK32, reinterpret_cast<void**>(&_Std_connect_WSOCK32));

		Logger::GetInstance()->printf("WSAHookThread(): connect (WSOCK32.dll) detourResult = %d", static_cast<int>(detourResult));

		return TRUE;
	}

	void StartWSAHook(IWSAHookHandler *handler)
	{
		Logger::GetInstance()->printf("StartWSAHook()");

		wsaHookHandler = handler;
		CreateThread(NULL, 0, WSAHookThread, NULL, 0, NULL);
	}
}