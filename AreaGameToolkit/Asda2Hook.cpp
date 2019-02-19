// AreaGameTookit
#include "Asda2Hook.hpp"

using namespace InjectMe::Hook::Asda2;

// Detours
#include "Detours\Detours.h"

// WinAPI
#include <Windows.h>

// C++
#include <forward_list>
#include <vector>

namespace InjectMe::Hook::Asda2
{
	//#define ASAD2DETOURS_DEBUG

#ifdef ASAD2DETOURS_DEBUG
#define ASAD2DETOURS_DEBUG_MSG(X) MessageBox(NULL, X, "Asda2Detours debug message", MB_OK)
#else
#define ASAD2DETOURS_DEBUG_MSG(X)
#endif

// Asda 2 context
	size_t _eax, _ebx, _ecx, _edx;
	size_t _ebp, _esp, _esi, _edi;

#define SaveAsda2Context()	\
	__asm mov _eax, eax	\
	__asm mov _ebx, ebx	\
	__asm mov _ecx, ecx	\
	__asm mov _edx, edx	\
	__asm mov _ebp, ebp	\
	__asm mov _esp, esp	\
	__asm mov _esi, esi	\
	__asm mov _edi, edi

#define LoadAsda2Context()	\
	__asm mov eax, _eax	\
	__asm mov ebx, _ebx	\
	__asm mov ecx, _ecx	\
	__asm mov edx, _edx	\
	__asm mov ebp, _ebp	\
	__asm mov esp, _esp	\
	__asm mov esi, _esi \
	__asm mov edi, _edi

	// Misc detour context
	typedef void(*MiscButtonProc) ();

	// Misc detour
	void _My_MiscButton();

	// Misc detour context
	bool _Std_MiscButtonDetour = false;
	MiscButtonProc _Std_MiscButton;
	size_t _Std_MiscButtonAddress;
	unsigned char _Std_MiscButtonPrologue[] = { 0x89, 0x45, 0xf8, 0x83, 0x7d, 0xf8, 0x10 };
	size_t _Std_MiscButtonPrologueSize = sizeof(_Std_MiscButtonPrologue) / sizeof(_Std_MiscButtonPrologue[0]);
	MiscButtonData _Std_MiscButtonEventArgs = { static_cast<size_t>(-1) };
	HANDLE _Std_MiscButtonEvent;
	std::forward_list<IMiscButtonHandler*> _Std_MiscButtonEventHandlerList;

	// Misc detour
	void _My_MiscButton()
	{
		SaveAsda2Context();

		__asm
		{
			mov _Std_MiscButtonEventArgs._Std_MiscIndex, eax
		}

		SetEvent(_Std_MiscButtonEvent);

		LoadAsda2Context();

		_Std_MiscButton();
	}

	// NPC button detour context
	typedef void(*NPCButtonProc) ();

	// NPC button detour
	void _My_NPCButton();

	// NPC button detour context
	bool _Std_NPCButtonDetour = false;
	NPCButtonProc _Std_NPCButton;
	size_t _Std_NPCButtonAddress;
	unsigned char _Std_NPCButtonPrologue[] = { 0x89, 0x85, 0x78, 0xFE, 0xFF, 0xFF };
	size_t _Std_NPCButtonPrologueSize = sizeof(_Std_NPCButtonPrologue) / sizeof(_Std_NPCButtonPrologue[0]);
	NPCButtonData _Std_NPCButtonEventArgs = { static_cast<size_t>(-1) };
	HANDLE _Std_NPCButtonEvent;
	std::forward_list<INPCButtonHandler*> _Std_NPCButtonEventHandlerList;

	// NPC button detour
	void _My_NPCButton()
	{
		SaveAsda2Context();

		__asm
		{
			mov _Std_NPCButtonEventArgs._Std_ActionIndex, eax
		}

		SetEvent(_Std_NPCButtonEvent);

		LoadAsda2Context();

		_Std_NPCButton();
	}

	// Локаль Asda 2
	Asda2Locale asda2Locale = Asda2Locale::Unknown;

	DWORD WINAPI Asda2HookThread(LPVOID lpParam)
	{
		switch (asda2Locale)
		{
		case Asda2Locale::English:
		case Asda2Locale::Russian:
			_Std_MiscButtonAddress = 0x0079E2CC;
			_Std_MiscButtonDetour = true;
			_Std_NPCButtonAddress = 0x006B5691;
			_Std_NPCButtonDetour = true;
			break;
		case Asda2Locale::Arabian:
			_Std_MiscButtonAddress = 0x007BA34C;
			_Std_MiscButtonDetour = true;
			_Std_NPCButtonAddress = 0x006C2EA3;
			_Std_NPCButtonDetour = true;
			break;
		default:
			_Std_MiscButtonDetour = false;
			_Std_NPCButtonDetour = false;
		}

		Detours::DETOUR_RESULT detourResult;

		if (_Std_MiscButtonDetour == true)
		{
			detourResult = Detours::HookFunction(
				reinterpret_cast<void*>(_Std_MiscButtonAddress),
				_Std_MiscButtonPrologue, _Std_MiscButtonPrologueSize,
				_My_MiscButton, reinterpret_cast<void**>(&_Std_MiscButton));

#ifdef ASAD2DETOURS_DEBUG

			char sDetourResult[256];

			int iDetourResult = static_cast<Detours::DETOUR_RESULT>(detourResult);

			sprintf_s(sDetourResult, sizeof(sDetourResult), "MiscHandler detourResult = %d", iDetourResult);

			MessageBox(NULL, sDetourResult, "DEBUG", MB_OK);

#endif
		}

		if (_Std_NPCButtonDetour)
		{
			detourResult = Detours::HookFunction(
				reinterpret_cast<void*>(_Std_NPCButtonAddress),
				_Std_NPCButtonPrologue, _Std_NPCButtonPrologueSize,
				_My_NPCButton, reinterpret_cast<void**>(&_Std_NPCButton));

#ifdef ASAD2DETOURS_DEBUG

			char sDetourResult[256];

			int iDetourResult = static_cast<Detours::DETOUR_RESULT>(detourResult);

			sprintf_s(sDetourResult, sizeof(sDetourResult), "NPCButtonHandler detourResult = %d", iDetourResult);

			MessageBox(NULL, sDetourResult, "DEBUG", MB_OK);

#endif
		}

		_Std_MiscButtonEvent = CreateEvent(
			NULL,
			FALSE,
			FALSE,
			NULL
		);

		_Std_NPCButtonEvent = CreateEvent(
			NULL,
			FALSE,
			FALSE,
			NULL
		);

		HANDLE lpHandles[] =
		{
			_Std_MiscButtonEvent,
			_Std_NPCButtonEvent,
		};

		auto nCount = sizeof(lpHandles) / sizeof(lpHandles[0]);

		for (;;)
		{
			auto dwWaitResult = WaitForMultipleObjects(
				nCount,
				lpHandles,
				FALSE,
				INFINITE
			);

			switch (dwWaitResult)
			{
			case WAIT_OBJECT_0 + 0:
			{
				for (auto handler : _Std_MiscButtonEventHandlerList)
				{
					handler->HandleMiscButton(_Std_MiscButtonEventArgs);
				}

				break;
			}
			case WAIT_OBJECT_0 + 1:
				for (auto handler : _Std_NPCButtonEventHandlerList)
				{
					handler->HandleNPCButton(_Std_NPCButtonEventArgs);
				}

				break;
			default:
				return 0;
			}
		}

		return TRUE;
	}

	void AppendMiscButtonHandler(IMiscButtonHandler *handler)
	{
		_Std_MiscButtonEventHandlerList.push_front(handler);
	}

	void RemoveMiscButtonHandler(IMiscButtonHandler *handler)
	{
		_Std_MiscButtonEventHandlerList.remove(handler);
	}

	void AppendNPCButtonHandler(INPCButtonHandler *handler)
	{
		_Std_NPCButtonEventHandlerList.push_front(handler);
	}

	void RemoveNPCButtonHandler(INPCButtonHandler *handler)
	{
		_Std_NPCButtonEventHandlerList.remove(handler);
	}

	void StartAsda2Hook()
	{
		CreateThread(NULL, 0, Asda2HookThread, NULL, 0, NULL);
	}

	void SetAsda2Locale(const Asda2Locale &locale)
	{
		asda2Locale = locale;
	}

	const Asda2Locale& GetAsda2Locale()
	{
		return asda2Locale;
	}

	Utils::LocaleType GetAsda2TranslatorLocale()
	{
		switch (asda2Locale)
		{
		case Asda2Locale::Russian:
			return Utils::LocaleType::RU;
		case Asda2Locale::English:
		case Asda2Locale::Arabian:
		default:
			return Utils::LocaleType::EN;
		}
	}
}