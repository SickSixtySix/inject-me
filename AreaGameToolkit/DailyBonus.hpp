#pragma once

// InjectMe
#include "Buffer.hpp"

namespace Addon::UI::DailyBonus
{
	// Возвращает истину для открытого окна ежедневного бонуса
	bool IsDailyBonusActive();

	// Открывает окно ежедневного бонуса
	void OpenDailyBonus(InjectMe::Utils::Buffer &buffer);

	// Закрывает окно ежедневного бонуса
	void CloseDailyBonus();

	// Интерфейс
	void DailyBonus();
}