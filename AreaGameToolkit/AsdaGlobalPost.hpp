#pragma once

// InjectMe
#include "AsdaGlobalData.hpp"

namespace InjectMe::Hook::AsdaGlobal
{
	// ��������� ������ ��������� �����
	void AsdaGlobalPost(char *BUF, unsigned long *LEN, bool syncAdded, bool hashAdded, const AsdaGlobalData &data);
}