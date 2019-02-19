#pragma once

#include <Windows.h>

namespace Detours
{
	enum DETOUR_RESULT
	{
		DETOURED_OK,
		ERROR_ORIGINAL_MISSING,
		ERROR_TRAMPOLINE_MISSING,
		ERROR_INVALID_FUNCTION_BODY,
		ERROR_INSUFFICIENT_MEMORY,
		ERROR_UNEXPECTED_FAILURE,
		ERROR_CODE_INJECTION_FAILED
	};

	/* Reads a memory location pointed with lpMemory to buffer pointed with lpBuffer. Size of buffer to copy located in szBuffer. */
	bool ReadMemory(void* lpMemory, void* lpBuffer, size_t szBuffer);

	/* Copies buffer pointed with lpBuffer to a memory location pointed with lpMemory. Size of buffer to copy located in szBuffer. */
	bool EditMemory(void* lpMemory, const void* lpBuffer, size_t szBuffer);

	/* Compares buffer pointed with lpBuffer with a memory location pointed with lpMemory. Size of buffer to copy located in szBuffer. */
	bool CompareMemory(void* lpMemory, const void* lpBuffer, size_t szBuffer);

	/* Set hook to function pointed with lpFunc, so all requests for it will be redirected to function pointed with lpDetour.
	* To call original function should use functon pointer in lppOriginalFunctionTrampoline. */
	DETOUR_RESULT HookFunction(void* lpFunc, void* lpDetour, void** lppOriginalFunctionTrampoline);

	/* Set hook to function pointed with lpFunc, so all requests for it will be redirected to function pointed with lpDetour.
	* To call original function should use functon pointer in lppOriginalFunctionTrampoline. */
	DETOUR_RESULT HookFunction(void* lpFunc, const void* lpPrologue, size_t szPrologue, void* lpDetour, void** lppOriginalFunctionTrampoline);

	/* Removes hook from the function pointed with lpFunc. This address is same that use in HookFunction. */
	void UnhookFunction(void* lpFunc);
}
