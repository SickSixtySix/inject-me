// InjectMe
#include "Logger.hpp"
#include "Memory.hpp"

// C++
#include <vector>

namespace InjectMe::Utils
{
	// Количество блоков памяти в хранилище
#define MEMORY_BLOCK_COUNT MEMORY_BLOCK_COUNT_X * MEMORY_BLOCK_COUNT_Y

	// Флаг инициализции механизма выделения
	BOOL bInit = FALSE;

	// Информация о хранилищах блоков памяти
	LPMEMORY_STORAGE_INFO lpMemoryStorageInfo;

	// Критическая секция хранилищ блоков памяти
	CRITICAL_SECTION criticalSection;

	// Количество хранилищ блоков памяти
	DWORD dwMemoryStorageCount = 0;

	VOID CreateMemoryStorage()
	{
		// Вход в критическую секцию
		EnterCriticalSection(&criticalSection);

		// Инициализация критической секции хранилища блоков памяти
		InitializeCriticalSection(&lpMemoryStorageInfo[dwMemoryStorageCount].criticalSection);

		// Инициализация счетчика идентификаторов блоков памяти
		lpMemoryStorageInfo[dwMemoryStorageCount].dwChainIDCounter = 0;

		// Создание информационных структур для блоков памяти
		lpMemoryStorageInfo[dwMemoryStorageCount].lpBlockInfo = (LPMEMORY_BLOCK_INFO)VirtualAlloc(NULL, sizeof(MEMORY_BLOCK_INFO) * MEMORY_BLOCK_COUNT, MEM_COMMIT, PAGE_READWRITE);
		VirtualLock(lpMemoryStorageInfo[dwMemoryStorageCount].lpBlockInfo, sizeof(MEMORY_BLOCK_INFO) * MEMORY_BLOCK_COUNT);

		// Заполнение информационных структур для блоков памяти
		int j;
		for (j = 0; j < MEMORY_BLOCK_COUNT; j++)
			lpMemoryStorageInfo[dwMemoryStorageCount].lpBlockInfo[j].bFree = TRUE;

		// Создание страниц памяти для блоков памяти
		lpMemoryStorageInfo[dwMemoryStorageCount].lpBlockAddress = VirtualAlloc(NULL, MEMORY_BLOCK_SIZE * MEMORY_BLOCK_COUNT, MEM_COMMIT, PAGE_READWRITE);
		VirtualLock(lpMemoryStorageInfo[dwMemoryStorageCount].lpBlockAddress, MEMORY_BLOCK_SIZE * MEMORY_BLOCK_COUNT);

		// Увеличение количества хранилищ блоков памяти
		++dwMemoryStorageCount;

		// Выход из критической секции
		LeaveCriticalSection(&criticalSection);
	}

	VOID ChainInit()
	{
		Logger::GetInstance()->printf("ChainInit()");

		// Инициализация критической секции создания хранилища блоков памяти
		InitializeCriticalSection(&criticalSection);

		// Создание информационных структур для хранилищ блоков памяти
		lpMemoryStorageInfo = (LPMEMORY_STORAGE_INFO)VirtualAlloc(NULL, sizeof(MEMORY_STORAGE_INFO) * MEMORY_STORAGE_COUNT, MEM_COMMIT, PAGE_READWRITE);
		VirtualLock(lpMemoryStorageInfo, sizeof(MEMORY_STORAGE_INFO) * MEMORY_STORAGE_COUNT);

		// Создание хранилища блоков памяти
		CreateMemoryStorage();
	}

	BOOL ChainAlloc(SIZE_T dwSize, PMEMORY_BLOCK_CHAIN pMemoryBlockChain)
	{
		// Вход в критическую секцию
		EnterCriticalSection(&criticalSection);

		DWORD i, j, k;
		for (i = 0; i < dwMemoryStorageCount; i++)
		{
			SIZE_T dwSizeCopy;
			DWORD startBlock = -1, blockCount;
			BOOL bFirst = TRUE;
			for (j = 0; j < MEMORY_BLOCK_COUNT; j++)
				if (lpMemoryStorageInfo[i].lpBlockInfo[j].bFree)
				{
					// Первый блок в цепочке
					if (bFirst)
					{
						dwSizeCopy = dwSize;
						startBlock = j;
						blockCount = 0;
						bFirst = FALSE;
					}

					++blockCount;

					// Последний блок в цепочке
					if (MEMORY_BLOCK_SIZE >= dwSizeCopy)
					{
						// Занятие блоков памяти найденной цепочки
						for (k = startBlock; k < startBlock + blockCount; k++)
						{
							lpMemoryStorageInfo[i].lpBlockInfo[k].dwChainID = lpMemoryStorageInfo[i].dwChainIDCounter;
							lpMemoryStorageInfo[i].lpBlockInfo[k].bFree = FALSE;
						}

						// Увеличение счетчика идентификаторов цепочек блоков памяти
						++lpMemoryStorageInfo[i].dwChainIDCounter;

						// Заполнение данных найденной цепочки
						pMemoryBlockChain->dwStorage = (DWORD)i;
						pMemoryBlockChain->dwStartBlock = (DWORD)startBlock;
						pMemoryBlockChain->dwBlockCount = (DWORD)blockCount;
						pMemoryBlockChain->lpAddress = (CHAR*)lpMemoryStorageInfo[i].lpBlockAddress + MEMORY_BLOCK_SIZE * startBlock;
						pMemoryBlockChain->dwSize = MEMORY_BLOCK_SIZE * blockCount;

						// Выход из критической секции
						LeaveCriticalSection(&criticalSection);

						return TRUE;
					}

					dwSizeCopy -= MEMORY_BLOCK_SIZE;
				}
				else
					bFirst = TRUE;

			// Создание дополнительного хранилища блоков памяти
			if (i == dwMemoryStorageCount - 1)
				CreateMemoryStorage();
		}

		// Выход из критической секции
		LeaveCriticalSection(&criticalSection);

		return FALSE;
	}

	BOOL ChainReAlloc(SIZE_T dwSize, PMEMORY_BLOCK_CHAIN pMemoryBlockChain)
	{
		// Вход в критическую секцию
		EnterCriticalSection(&criticalSection);

		// Копирование информации о цепочке блоков памяти
		MEMORY_BLOCK_CHAIN copy;
		memcpy_s(&copy, sizeof(MEMORY_BLOCK_CHAIN), pMemoryBlockChain, sizeof(MEMORY_BLOCK_CHAIN));

		// Выделение новой цепочки блоков памяти из хранилища и копирование данных
		ChainAlloc(dwSize, pMemoryBlockChain);
		memcpy_s((CHAR*)lpMemoryStorageInfo[pMemoryBlockChain->dwStorage].lpBlockAddress + MEMORY_BLOCK_SIZE * pMemoryBlockChain->dwStartBlock, MEMORY_BLOCK_SIZE * pMemoryBlockChain->dwBlockCount, (CHAR*)lpMemoryStorageInfo[copy.dwStorage].lpBlockAddress + MEMORY_BLOCK_SIZE * copy.dwStartBlock, MEMORY_BLOCK_SIZE * copy.dwBlockCount);

		// Возвращение старой цепочки блоков памяти в хранилище
		ChainFree(copy);

		// Выход из критической секции
		LeaveCriticalSection(&criticalSection);

		return TRUE;
	}

	VOID ChainFree(MEMORY_BLOCK_CHAIN memoryBlockChain)
	{
		// Вход в критическую секцию
		EnterCriticalSection(&criticalSection);

		// Освобождение блоков памяти найденной цепочки
		DWORD i;
		for (i = memoryBlockChain.dwStartBlock; i < memoryBlockChain.dwStartBlock + memoryBlockChain.dwBlockCount; i++)
			lpMemoryStorageInfo[memoryBlockChain.dwStorage].lpBlockInfo[i].bFree = TRUE;

		// Выход из критической секции
		LeaveCriticalSection(&criticalSection);
	}

	VOID ChainProfile(PMEMORY_PROFILE pMemoryProfile)
	{
		// Вход в критическую секцию
		EnterCriticalSection(&criticalSection);

		// Инициализация профиля
		pMemoryProfile->lpStorageProfile = (LPMEMORY_STORAGE_PROFILE)malloc(sizeof(MEMORY_STORAGE_PROFILE) * dwMemoryStorageCount);
		pMemoryProfile->dwStorageCount = dwMemoryStorageCount;

		DWORD i;
		for (i = 0; i < dwMemoryStorageCount; i++)
		{
			// Выделение памяти и копирование данных
			pMemoryProfile->lpStorageProfile[i].lpBlockInfo = (LPMEMORY_BLOCK_INFO)malloc(sizeof(MEMORY_BLOCK_INFO) * MEMORY_BLOCK_COUNT);
			memcpy_s(pMemoryProfile->lpStorageProfile[i].lpBlockInfo, sizeof(MEMORY_BLOCK_INFO) * MEMORY_BLOCK_COUNT, lpMemoryStorageInfo[i].lpBlockInfo, sizeof(MEMORY_BLOCK_INFO) * MEMORY_BLOCK_COUNT);
		}

		// Выход из критической секции
		LeaveCriticalSection(&criticalSection);
	}
}