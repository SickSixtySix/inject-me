#pragma once

// InjectMe
#include "AsdaGlobalData.hpp"

namespace InjectMe::Hook::AsdaGlobal
{
	// Выполняет запись временной метки
	void AsdaGlobalPost(char *BUF, unsigned long *LEN, bool syncAdded, bool hashAdded, const AsdaGlobalData &data);
}