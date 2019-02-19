#pragma once

// WinAPI
#include <Windows.h>

namespace InjectMe::Utils
{
// ������������ ���������� �������� ������ ������
#define MEMORY_STORAGE_COUNT	4

// ���������� ������ ������ �� ����������� (� ������ ����� ����������� �������)
#define MEMORY_BLOCK_COUNT_X	64

// ���������� ������ ������ �� ��������� (� ������ ����� ����������� �������)
#define MEMORY_BLOCK_COUNT_Y	64

// ������ ����� ������
#define MEMORY_BLOCK_SIZE		1024

	// �������������� ��������� ����� ������
	typedef struct _MEMORY_BLOCK_INFO
	{
		// ������������� ������� ������ ������
		DWORD dwChainID;

		// ���� ����������� ����� ������
		BOOL bFree;
	} MEMORY_BLOCK_INFO, *PMEMORY_BLOCK_INFO, *LPMEMORY_BLOCK_INFO;

	// ��������� ����� ������
	typedef struct _MEMORY_BLOCK
	{
		// ����� ����� ������
		LPVOID lpAddress;

		// ������ ����� ������
		SIZE_T dwSize;
	} MEMORY_BLOCK;

	// ��������� ������� ������ ������
	typedef struct _MEMORY_BLOCK_CHAIN
	{
		// ������ ��������� ������ ������ �������
		DWORD dwStorage;

		// ������ ������� ����� ������ �������
		DWORD dwStartBlock;

		// ���������� ������ ������ �������
		DWORD dwBlockCount;

		// ����� ������ ������ �������
		PCHAR lpAddress;

		// ������ ������� ������ ������
		DWORD dwSize;
	} MEMORY_BLOCK_CHAIN, *PMEMORY_BLOCK_CHAIN;

	// �������������� ��������� ��������� ������ ������
	typedef struct _MEMORY_STORAGE_INFO
	{
		// ����������� ������ ��������� ������ ������
		CRITICAL_SECTION criticalSection;

		// ������� ��������������� ������� ������ ������
		DWORD dwChainIDCounter;

		// ����� ���������� ������ ������ ���������
		LPMEMORY_BLOCK_INFO lpBlockInfo;

		// ����� ������ ������ ���������
		LPVOID lpBlockAddress;
	} MEMORY_STORAGE_INFO, *PMEMORY_STORAGE_INFO, *LPMEMORY_STORAGE_INFO;

	typedef struct _MEMORY_STORAGE_PROFILE
	{
		// ����� ���������� ������ ������ ���������
		LPMEMORY_BLOCK_INFO lpBlockInfo;

		// ���������� ������ ������ ���������
		DWORD dwBlockCount;
	} MEMORY_STORAGE_PROFILE, *PMEMORY_STORAGE_PROFILE, *LPMEMORY_STORAGE_PROFILE;

	typedef struct _MEMORY_PROFILE
	{
		// ������� �������� ������ ������
		LPMEMORY_STORAGE_PROFILE lpStorageProfile;

		// ���������� �������� ������ ������
		DWORD dwStorageCount;
	} MEMORY_PROFILE, *PMEMORY_PROFILE, *LPMEMORY_PROFILE;

	// �������������� ������
	VOID ChainInit();

	// �������� ������� ������ ������ �� ���������
	BOOL ChainAlloc(SIZE_T dwSize, PMEMORY_BLOCK_CHAIN pMemoryBlockChain);

	// ���������������� ������� ������ ������ �� ���������
	BOOL ChainReAlloc(SIZE_T dwSize, PMEMORY_BLOCK_CHAIN pMemoryBlockChain);

	// ���������� ������� ������ ������ � ���������
	VOID ChainFree(MEMORY_BLOCK_CHAIN memoryBlockChain);

	// ��������� �������������� ������
	VOID ChainProfile(PMEMORY_PROFILE pMemoryProfile);
}