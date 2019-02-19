// InjectMe
#include "D3D9Hook.hpp"
#include "Logger.hpp"
#include "TextureFactory.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::UI;

// Detours
#include "Detours/Detours.h"

// ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

// C
#include <intrin.h>

// Оконная процедура перехвата целевого окна
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace InjectMe::Hook::D3D9
{
	// Оконная процедура целевого окна
	WNDPROC WndProc = NULL;

	LRESULT CALLBACK HookWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
			if (ImGui::GetIO().WantCaptureMouse == true)
				return true;
			break;
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			if (ImGui::GetIO().WantCaptureMouse == true)
				return true;
			break;
		case WM_MOUSEWHEEL:
			if (ImGui::GetIO().WantCaptureMouse == true)
				return true;
			break;
		case WM_MOUSEHWHEEL:
			if (ImGui::GetIO().WantCaptureMouse == true)
				return true;
			break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			if (ImGui::IsAnyWindowFocused())
				return true;
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			if (ImGui::IsAnyWindowFocused() == true)
				return true;
			break;
		case WM_CHAR:
			if (ImGui::IsAnyItemActive() == true)
				return true;
			break;
		case WM_SETCURSOR:
			break;
		}

		return CallWindowProc(WndProc, hWnd, msg, wParam, lParam);
	}

	// Поток перехвата COM-интерфейса
	DWORD WINAPI COMHookThread(LPVOID lpParam);

	// Обработчик событий перехвата Direct3D 9
	ID3D9HookHandler *d3d9HookHandler = nullptr;

	// Reset detour context
	typedef HRESULT(WINAPI *ResetProc) (
		LPDIRECT3DDEVICE9     Direct3D9Device,
		D3DPRESENT_PARAMETERS *pPresentationParameters
		);

	// Reset detour
	HRESULT WINAPI _My_Reset(
		LPDIRECT3DDEVICE9     Direct3D9Device,
		D3DPRESENT_PARAMETERS *pPresentationParameters
	);

	// Reset detour context
	ResetProc _Std_Reset;
	PDWORD pdw_My_Reset;

	// EndScene detour context
	typedef HRESULT(WINAPI *EndSceneProc) (
		LPDIRECT3DDEVICE9     Direct3D9Device
		);

	// EndScene detour
	HRESULT WINAPI _My_EndScene(
		LPDIRECT3DDEVICE9     Direct3D9Device
	);

	// EndScene detour context
	EndSceneProc _Std_EndScene;
	PDWORD pdw_My_EndScene;

	// CreateDevice detour context
	typedef HRESULT(WINAPI *CreateDeviceProc) (
		LPDIRECT3D9           Direct3D9,
		UINT                  Adapter,
		D3DDEVTYPE            DeviceType,
		HWND                  hFocusWindow,
		DWORD                 BehaviorFlags,
		D3DPRESENT_PARAMETERS *pPresentationParameters,
		IDirect3DDevice9      **ppReturnedDeviceInterface
		);

	// CreateDevice detour
	HRESULT WINAPI _My_CreateDevice(
		LPDIRECT3D9           Direct3D9,
		UINT                  Adapter,
		D3DDEVTYPE            DeviceType,
		HWND                  hFocusWindow,
		DWORD                 BehaviorFlags,
		D3DPRESENT_PARAMETERS *pPresentationParameters,
		IDirect3DDevice9      **ppReturnedDeviceInterface
	);

	// CreateDevice detour context
	CreateDeviceProc _Std_CreateDevice = NULL;
	PDWORD pdw_My_CreateDevice;
	LPDIRECT3DDEVICE9 _Std_CreateDevice_Device = NULL;
	PDWORD _Std_CreateDevice_COM = NULL;

	// Direct3DCreate9 detour context
	typedef IDirect3D9* (WINAPI *Direct3DCreate9Proc) (
		UINT SDKVersion
		);

	// Direct3DCreate9 detour
	IDirect3D9* WINAPI _My_Direct3DCreate9(
		UINT SDKVersion
	);

	// Direct3DCreate9 detour context
	Direct3DCreate9Proc _Std_Direct3DCreate9;
	PDWORD _Std_Direct3DCreate9_VFT;

	// Reset detour
	HRESULT WINAPI _My_Reset(
		LPDIRECT3DDEVICE9     Direct3D9Device,
		D3DPRESENT_PARAMETERS *pPresentationParameters
	)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		TextureFactory::Instance()->ReleaseTextures();

		auto result = _Std_Reset(
			Direct3D9Device,
			pPresentationParameters
		);

		ImGui_ImplDX9_CreateDeviceObjects();

		return result;
	}

	// EndScene detour
	HRESULT WINAPI _My_EndScene(
		LPDIRECT3DDEVICE9     Direct3D9Device
	)
	{
		auto returnAddress = reinterpret_cast<size_t>(_ReturnAddress());
		if (d3d9HookHandler != nullptr && d3d9HookHandler->CanHandleNewFrame(returnAddress))
		{
			// Начало фрейма ImGui
			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			d3d9HookHandler->HandleNewFrame();

			// Рендеринг
			ImGui::EndFrame();
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		}

		return _Std_EndScene(
			Direct3D9Device
		);
	}

	// CreateDevice detour
	HRESULT WINAPI _My_CreateDevice(
		LPDIRECT3D9           Direct3D9,
		UINT                  Adapter,
		D3DDEVTYPE            DeviceType,
		HWND                  hFocusWindow,
		DWORD                 BehaviorFlags,
		D3DPRESENT_PARAMETERS *pPresentationParameters,
		IDirect3DDevice9      **ppReturnedDeviceInterface
	)
	{
		Logger::GetInstance()->printf("_My_CreateDevice()");

		// Вызов оригинальной функции CreateDevice
		auto result = _Std_CreateDevice(
			Direct3D9,
			Adapter,
			DeviceType,
			hFocusWindow,
			BehaviorFlags,
			pPresentationParameters,
			ppReturnedDeviceInterface
		);

		// Модификация оригинального значения из таблицы виртуальных функций
		Detours::EditMemory(
			&_Std_Direct3DCreate9_VFT[16], &_Std_CreateDevice, sizeof(PDWORD)
		);

		// Получение указателя на устройство Direct3D 9
		_Std_CreateDevice_Device = *ppReturnedDeviceInterface;

		// Перехват оконной процедуры целевого окна
		WndProc = (WNDPROC)GetWindowLong(hFocusWindow, GWL_WNDPROC);
		SetWindowLong(hFocusWindow, GWL_WNDPROC, (LONG)HookWndProc);

		// Установка ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.IniFilename = NULL;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
		ImGui_ImplWin32_Init(hFocusWindow);
		ImGui_ImplDX9_Init(_Std_CreateDevice_Device);

		// Установка стиля
		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		style.AntiAliasedFill = true;
		style.AntiAliasedLines = true;

		// Получение адреса COM-интерфейса
		_Std_CreateDevice_COM = reinterpret_cast<PDWORD>(
			*reinterpret_cast<PDWORD>(*ppReturnedDeviceInterface)
			);

		// Получение значения из COM-интерфейса
		Detours::ReadMemory(
			&_Std_CreateDevice_COM[16], &_Std_Reset, sizeof(PDWORD)
		);

		// Получение значения из COM-интерфейса
		Detours::ReadMemory(
			&_Std_CreateDevice_COM[42], &_Std_EndScene, sizeof(PDWORD)
		);

		// Запуск потока для периодической модификации COM-интерфейса
		CreateThread(NULL, 0, COMHookThread, NULL, 0, NULL);

		return result;
	}

	// Direct3DCreate9 detour
	IDirect3D9* WINAPI _My_Direct3DCreate9(
		UINT SDKVersion
	)
	{
		Logger::GetInstance()->printf("_My_Direct3DCreate9()");

		// Вызов оригинальной функции Direct3DCreate9
		auto result = _Std_Direct3DCreate9(
			SDKVersion
		);

		// Получение адреса таблицы виртуальных функций
		_Std_Direct3DCreate9_VFT = reinterpret_cast<PDWORD>(
			*reinterpret_cast<PDWORD>(result)
			);

		// Получение оригинального значения из таблицы виртуальных функций
		Detours::ReadMemory(
			&_Std_Direct3DCreate9_VFT[16], &_Std_CreateDevice, sizeof(PDWORD)
		);

		// Модификация оригинального значения из таблицы виртуальных функций
		Detours::EditMemory(
			&_Std_Direct3DCreate9_VFT[16], &pdw_My_CreateDevice, sizeof(PDWORD)
		);

		return result;
	}

	DWORD WINAPI COMHookThread(LPVOID lpParam)
	{
		Logger::GetInstance()->printf("COMHookThread()");

		// Снятие защиты памяти
		DWORD flOldProtect;

		VirtualProtect(
			&_Std_CreateDevice_COM[16], sizeof(PDWORD) * (42 - 16 + 1), PAGE_READWRITE, &flOldProtect
		);

		// Модификация COM-интерфейса
		for (;;)
		{
			memcpy_s(
				&_Std_CreateDevice_COM[16], sizeof(PDWORD), &pdw_My_Reset, sizeof(PDWORD)
			);

			memcpy_s(
				&_Std_CreateDevice_COM[42], sizeof(PDWORD), &pdw_My_EndScene, sizeof(PDWORD)
			);

			Sleep(1);
		}

		// Восстановление защиты памяти
		VirtualProtect(
			&_Std_CreateDevice_COM[16], sizeof(PDWORD) * (42 - 16 + 1), flOldProtect, NULL
		);

		return TRUE;
	}

	DWORD WINAPI D3D9HookThread(LPVOID lpParam)
	{
		Logger::GetInstance()->printf("D3D9HookThread()");

		while (GetModuleHandle(TEXT("d3d9.dll")) == NULL);

		auto detourResult = Detours::HookFunction(
			GetProcAddress(GetModuleHandle(TEXT("d3d9.dll")), "Direct3DCreate9"),
			_My_Direct3DCreate9, reinterpret_cast<void**>(&_Std_Direct3DCreate9));

		Logger::GetInstance()->printf("D3D9HookThread(): detourResult = %d", static_cast<int>(detourResult));

		return TRUE;
	}

	void StartD3D9Hook(ID3D9HookHandler *handler)
	{
		Logger::GetInstance()->printf("StartD3D9Hook()");

		d3d9HookHandler = handler;
		pdw_My_Reset = reinterpret_cast<PDWORD>(_My_Reset);
		pdw_My_EndScene = reinterpret_cast<PDWORD>(_My_EndScene);
		pdw_My_CreateDevice = reinterpret_cast<PDWORD>(_My_CreateDevice);
		D3D9HookThread(NULL);
	}

	LPDIRECT3DDEVICE9 GetCurrentDevice()
	{
		return _Std_CreateDevice_Device;
	}
}