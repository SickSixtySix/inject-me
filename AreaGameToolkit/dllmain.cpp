// dllmain.cpp: определяет точку входа для приложения DLL.
#include "stdafx.h"

// Toolkit
#include "Logger.hpp"

using namespace InjectMe::Utils;

#if defined(ADDON_DLL)

// Addon
#include "Addon.hpp"

#elif defined(CHEAT_DLL)

// Cheat
#include "Cheat.hpp"

#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

		Logger::GetInstance()->printf("DllMain(): DLL_PROCESS_ATTACH");

#if defined(ADDON_DLL)

		StartAddon();

#elif defined (CHEAT_DLL)

		StartCheat();

#endif

		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

