#pragma once

// InjectMe
#include "AsdaGlobalData.hpp"

namespace InjectMe::Hook::AsdaGlobal
{
	// ��������� ������ ����������������� ������
	void AsdaGlobalSync(char *const BUF, const unsigned long OFS, const AsdaGlobalData &data);
}