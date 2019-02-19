#pragma once

// InjectMe
#include "NPCButtonData.hpp"

namespace InjectMe::Hook::Asda2
{
	// Интерфейс обработчика события нажатия кнопки в диалоге с NPC
	class INPCButtonHandler
	{
	public:

		// Обработчик события нажатия кнопки в диалоге с NPC
		virtual void HandleNPCButton(const NPCButtonData &args) = 0;
	};
}