#pragma once

// InjectMe
#include "IWSAHookHandler.hpp"

namespace InjectMe::Hook::WSA
{
	// Запускает механизм перехвата WSA
	void StartWSAHook(IWSAHookHandler *handler);
}