// InjectMe
#include "D3D9Hook.hpp"
#include "AsdaGlobalD3D9HookHandler.hpp"
#include "AsdaGlobalWSAHookHandler.hpp"
#include "Memory.hpp"
#include "WSAHook.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Hook::WSA;
using namespace InjectMe::Hook::D3D9;

// Addon
#include "Cheat.hpp"

void StartCheat()
{
	// ������������� ������
	ChainInit();

	// ������ ��������� ��������� Direct3D 9
	StartD3D9Hook(AsdaGlobalD3D9HookHandler::Instance());

	// ������ ��������� ��������� WSA
	StartWSAHook(AsdaGlobalWSAHookHandler::Instance());
}