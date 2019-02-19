#pragma once

// InjectMe
#include "ID3D9HookHandler.hpp"

// Direct3D 9
#include <d3d9.h>

namespace InjectMe::Hook::D3D9
{
	// Запускает механизм перехвата Direct3D 9
	void StartD3D9Hook(ID3D9HookHandler *handler);

	// Получает текущее устройство
	LPDIRECT3DDEVICE9 GetCurrentDevice();
}