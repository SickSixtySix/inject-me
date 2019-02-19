#pragma once

// InjectMe
#include "MiscButtonData.hpp"

namespace InjectMe::Hook::Asda2
{
	// Интерфейс обработчика события нажатия кнопки в дополнительном меню
	class IMiscButtonHandler
	{
	public:

		// Обработчик события нажатия кнопки в дополнительном меню
		virtual void HandleMiscButton(const MiscButtonData &args) = 0;
	};
}