#pragma once

// InjectMe
#include "Buffer.hpp"

namespace Addon::UI::DailyBonus
{
	// ���������� ������ ��� ��������� ���� ����������� ������
	bool IsDailyBonusActive();

	// ��������� ���� ����������� ������
	void OpenDailyBonus(InjectMe::Utils::Buffer &buffer);

	// ��������� ���� ����������� ������
	void CloseDailyBonus();

	// ���������
	void DailyBonus();
}