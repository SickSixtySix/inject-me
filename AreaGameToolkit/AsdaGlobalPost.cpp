#pragma warning(push, 0)

// InjectMe
#include "AsdaGlobalPost.hpp"

// IDA
#include "IDA/defs.h"

namespace InjectMe::Hook::AsdaGlobal
{
	void sub_1481030(char *BUF, unsigned long *LEN, bool syncAdded, bool hashAdded, _DWORD address1, _DWORD address2)
	{
		void *v28 = (void*)address1;
		signed short a4 = *LEN;
		if (syncAdded)
			a4 += 8;
		if (hashAdded)
			a4 += 16;
		unsigned short v29 = a4 + 10;

		*(_DWORD*)address2 += 11;
		int v19 = *(_DWORD*)address2 % 20;
		if (*(_DWORD*)address2 % 20 + v29 < 800)
		{
			void *v15 = BUF + v29;
			memcpy(v15, (char *)v28 + 4, 4 * ((unsigned int)v19 >> 2));
			const void *v20 = (char *)v28 + 4 * ((unsigned int)v19 >> 2) + 4;
			int v21 = v19 & 3;
			memcpy((char *)v15 + 4 * ((unsigned int)v19 >> 2), v20, v21);
			*((short*)&BUF[1]) = v19 + v29;
			*LEN = v19 + v29;
		}
	}

	void AsdaGlobalPost(char *BUF, unsigned long *LEN, bool syncAdded, bool hashAdded, const AsdaGlobalData &data)
	{
		sub_1481030(BUF, LEN, syncAdded, hashAdded, data.GetAddress1(), data.GetAddress2());
	}
}

#pragma warning(pop)