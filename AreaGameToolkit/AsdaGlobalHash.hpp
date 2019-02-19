#pragma once

namespace InjectMe::Hook::AsdaGlobal
{
	// Выполняет хеширование данных
	void AsdaGlobalHash(char *const BUF, const unsigned long HSH_OFS, const unsigned long DAT_LEN, const unsigned long DAT_OFS);
}