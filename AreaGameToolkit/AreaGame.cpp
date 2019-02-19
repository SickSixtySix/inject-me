// AddonUtils
#include "../AddonUtils/Logger.hpp"

// AddonNetBypass
#include "../AddonNetBypass/WSABypass.hpp"

// AddonUI
#include "../AddonUI/UI.hpp"

// AddonAreaGame
#include "AreaGame.hpp"
#include "ImGuiHandler.hpp"
#include "Protection.hpp"
#include "WSABypassHandler.hpp"

#include "../AddonUtils/Memory.hpp"

// WinAPI
#include <io.h>
#include <fcntl.h>
#include <windows.h>

void StartAreaGame()
{
	Logger::GetInstance()->printf(
		"StartAreaGame()"
	);

	ChainInit();

	Protection();

	// Запуск графического интерфейса пользователя
	StartUI(
		new ImGuiHandler()
	);

	// Запуск механизма перехвата WSA
	StartWSABypass(
		new WSABypassHandler()
	);
}