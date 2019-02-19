// InjectMe
#include "D3D9Hook.hpp"
#include "Asda2D3D9HookHandler.hpp"
#include "Asda2WSAHookHandler.hpp"
#include "Logger.hpp"
#include "Memory.hpp"
#include "WSAHook.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Hook::WSA;
using namespace InjectMe::Hook::D3D9;

// Addon
#include "Addon.hpp"

// ImGui
#include "ImGui/imgui.h"

void StartAddon()
{
	Logger::GetInstance()->printf("StartAddon()");

	// Инициализация памяти
	ChainInit();

	// Запуск механизма перехвата Direct3D 9
	StartD3D9Hook(Asda2D3D9HookHandler::Instance());

	// Запуск механизма перехвата WSA
	StartWSAHook(Asda2WSAHookHandler::Instance());
}