// InjectMe
#include "Logger.hpp"
#include "Memory.hpp"

// C++
#include <vector>

namespace InjectMe::Utils
{
	// ���������� ������ ������ � ���������
#define MEMORY_BLOCK_COUNT MEMORY_BLOCK_COUNT_X * MEMORY_BLOCK_COUNT_Y

	// ���� ������������ ��������� ���������
	BOOL bInit = FALSE;

	// ���������� � ���������� ������ ������
	LPMEMORY_STORAGE_INFO lpMemoryStorageInfo;

	// ����������� ������ �������� ������ ������
	CRITICAL_SECTION criticalSection;

	// ���������� �������� ������ ������
	DWORD dwMemoryStorageCount = 0;

	VOID CreateMemoryStorage()
	{
		// ���� � ����������� ������
		EnterCriticalSection(&criticalSection);

		// ������������� ����������� ������ ��������� ������ ������
		InitializeCriticalSection(&lpMemoryStorageInfo[dwMemoryStorageCount].criticalSection);

		// ������������� �������� ��������������� ������ ������
		lpMemoryStorageInfo[dwMemoryStorageCount].dwChainIDCounter = 0;

		// �������� �������������� �������� ��� ������ ������
		lpMemoryStorageInfo[dwMemoryStorageCount].lpBlockInfo = (LPMEMORY_BLOCK_INFO)VirtualAlloc(NULL, sizeof(MEMORY_BLOCK_INFO) * MEMORY_BLOCK_COUNT, MEM_COMMIT, PAGE_READWRITE);
		VirtualLock(lpMemoryStorageInfo[dwMemoryStorageCount].lpBlockInfo, sizeof(MEMORY_BLOCK_INFO) * MEMORY_BLOCK_COUNT);

		// ���������� �������������� �������� ��� ������ ������
		int j;
		for (j = 0; j < MEMORY_BLOCK_COUNT; j++)
			lpMemoryStorageInfo[dwMemoryStorageCount].lpBlockInfo[j].bFree = TRUE;

		// �������� ������� ������ ��� ������ ������
		lpMemoryStorageInfo[dwMemoryStorageCount].lpBlockAddress = VirtualAlloc(NULL, MEMORY_BLOCK_SIZE * MEMORY_BLOCK_COUNT, MEM_COMMIT, PAGE_READWRITE);
		VirtualLock(lpMemoryStorageInfo[dwMemoryStorageCount].lpBlockAddress, MEMORY_BLOCK_SIZE * MEMORY_BLOCK_COUNT);

		// ���������� ���������� �������� ������ ������
		++dwMemoryStorageCount;

		// ����� �� ����������� ������
		LeaveCriticalSection(&criticalSection);
	}

	VOID ChainInit()
	{
		Logger::GetInstance()->printf("ChainInit()");

		// ������������� ����������� ������ �������� ��������� ������ ������
		InitializeCriticalSection(&criticalSection);

		// �������� �������������� �������� ��� �������� ������ ������
		lpMemoryStorageInfo = (LPMEMORY_STORAGE_INFO)VirtualAlloc(NULL, sizeof(MEMORY_STORAGE_INFO) * MEMORY_STORAGE_COUNT, MEM_COMMIT, PAGE_READWRITE);
		VirtualLock(lpMemoryStorageInfo, sizeof(MEMORY_STORAGE_INFO) * MEMORY_STORAGE_COUNT);

		// �������� ��������� ������ ������
		CreateMemoryStorage();
	}

	BOOL ChainAlloc(SIZE_T dwSize, PMEMORY_BLOCK_CHAIN pMemoryBlockChain)
	{
		// ���� � ����������� ������
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
					// ������ ���� � �������
					if (bFirst)
					{
						dwSizeCopy = dwSize;
						startBlock = j;
						blockCount = 0;
						bFirst = FALSE;
					}

					++blockCount;

					// ��������� ���� � �������
					if (MEMORY_BLOCK_SIZE >= dwSizeCopy)
					{
						// ������� ������ ������ ��������� �������
						for (k = startBlock; k < startBlock + blockCount; k++)
						{
							lpMemoryStorageInfo[i].lpBlockInfo[k].dwChainID = lpMemoryStorageInfo[i].dwChainIDCounter;
							lpMemoryStorageInfo[i].lpBlockInfo[k].bFree = FALSE;
						}

						// ���������� �������� ��������������� ������� ������ ������
						++lpMemoryStorageInfo[i].dwChainIDCounter;

						// ���������� ������ ��������� �������
						pMemoryBlockChain->dwStorage = (DWORD)i;
						pMemoryBlockChain->dwStartBlock = (DWORD)startBlock;
						pMemoryBlockChain->dwBlockCount = (DWORD)blockCount;
						pMemoryBlockChain->lpAddress = (CHAR*)lpMemoryStorageInfo[i].lpBlockAddress + MEMORY_BLOCK_SIZE * startBlock;
						pMemoryBlockChain->dwSize = MEMORY_BLOCK_SIZE * blockCount;

						// ����� �� ����������� ������
						LeaveCriticalSection(&criticalSection);

						return TRUE;
					}

					dwSizeCopy -= MEMORY_BLOCK_SIZE;
				}
				else
					bFirst = TRUE;

			// �������� ��������������� ��������� ������ ������
			if (i == dwMemoryStorageCount - 1)
				CreateMemoryStorage();
		}

		// ����� �� ����������� ������
		LeaveCriticalSection(&criticalSection);

		return FALSE;
	}

	BOOL ChainReAlloc(SIZE_T dwSize, PMEMORY_BLOCK_CHAIN pMemoryBlockChain)
	{
		// ���� � ����������� ������
		EnterCriticalSection(&criticalSection);

		// ����������� ���������� � ������� ������ ������
		MEMORY_BLOCK_CHAIN copy;
		memcpy_s(&copy, sizeof(MEMORY_BLOCK_CHAIN), pMemoryBlockChain, sizeof(MEMORY_BLOCK_CHAIN));

		// ��������� ����� ������� ������ ������ �� ��������� � ����������� ������
		ChainAlloc(dwSize, pMemoryBlockChain);
		memcpy_s((CHAR*)lpMemoryStorageInfo[pMemoryBlockChain->dwStorage].lpBlockAddress + MEMORY_BLOCK_SIZE * pMemoryBlockChain->dwStartBlock, MEMORY_BLOCK_SIZE * pMemoryBlockChain->dwBlockCount, (CHAR*)lpMemoryStorageInfo[copy.dwStorage].lpBlockAddress + MEMORY_BLOCK_SIZE * copy.dwStartBlock, MEMORY_BLOCK_SIZE * copy.dwBlockCount);

		// ����������� ������ ������� ������ ������ � ���������
		ChainFree(copy);

		// ����� �� ����������� ������
		LeaveCriticalSection(&criticalSection);

		return TRUE;
	}

	VOID ChainFree(MEMORY_BLOCK_CHAIN memoryBlockChain)
	{
		// ���� � ����������� ������
		EnterCriticalSection(&criticalSection);

		// ������������ ������ ������ ��������� �������
		DWORD i;
		for (i = memoryBlockChain.dwStartBlock; i < memoryBlockChain.dwStartBlock + memoryBlockChain.dwBlockCount; i++)
			lpMemoryStorageInfo[memoryBlockChain.dwStorage].lpBlockInfo[i].bFree = TRUE;

		// ����� �� ����������� ������
		LeaveCriticalSection(&criticalSection);
	}

	VOID ChainProfile(PMEMORY_PROFILE pMemoryProfile)
	{
		// ���� � ����������� ������
		EnterCriticalSection(&criticalSection);

		// ������������� �������
		pMemoryProfile->lpStorageProfile = (LPMEMORY_STORAGE_PROFILE)malloc(sizeof(MEMORY_STORAGE_PROFILE) * dwMemoryStorageCount);
		pMemoryProfile->dwStorageCount = dwMemoryStorageCount;

		DWORD i;
		for (i = 0; i < dwMemoryStorageCount; i++)
		{
			// ��������� ������ � ����������� ������
			pMemoryProfile->lpStorageProfile[i].lpBlockInfo = (LPMEMORY_BLOCK_INFO)malloc(sizeof(MEMORY_BLOCK_INFO) * MEMORY_BLOCK_COUNT);
			memcpy_s(pMemoryProfile->lpStorageProfile[i].lpBlockInfo, sizeof(MEMORY_BLOCK_INFO) * MEMORY_BLOCK_COUNT, lpMemoryStorageInfo[i].lpBlockInfo, sizeof(MEMORY_BLOCK_INFO) * MEMORY_BLOCK_COUNT);
		}

		// ����� �� ����������� ������
		LeaveCriticalSection(&criticalSection);
	}
}