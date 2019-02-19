// InjectMe
#include "Asda2D3D9HookHandler.hpp"
#include "Asda2Hook.hpp"
#include "Asda2Proxy.hpp"
#include "TextureFactory.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;
using namespace InjectMe::Hook::D3D9;
using namespace InjectMe::Hook::Asda2;
using namespace InjectMe::UI;

// Addon
#include "DailyBonus.hpp"
#include "MiningWar.hpp"

using namespace Addon::UI::DailyBonus;
using namespace Addon::UI::MiningWar;

// ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_user.h"

#define AGEN_FONT MG_Basic_1_Uni.ttf
#define AGAR_FONT tahoma.ttf
#define AGRU_FONT arial.ttf

#define AGEN_FONT_SIZE 14
#define AGAR_FONT_SIZE 17
#define AGRU_FONT_SIZE 13

#define FONT_PATH_(X) "juidata\\font\\Base\\" #X
#define FONT_PATH(X) FONT_PATH_(X)

bool isFontLoaded = false;

Asda2D3D9HookHandler *Asda2D3D9HookHandler::s_instance = nullptr;

Asda2D3D9HookHandler::Asda2D3D9HookHandler() {}

Asda2D3D9HookHandler* Asda2D3D9HookHandler::Instance()
{
	if (s_instance == nullptr)
		s_instance = new Asda2D3D9HookHandler();

	return s_instance;
}

//#include <vector>
//#include <utility>
//
//std::map<size_t, size_t> ebpValues;

bool Asda2D3D9HookHandler::CanHandleNewFrame(unsigned long ebpValue)
{
	// RU/EN
	// 4351081

	// AR
	// 4341834

	//if (ebpValue != 4351081 && GetAsda2Locale() != Asda2Locale::Arabian)
	//	return false;
	//else if (ebpValue != 4341834 && GetAsda2Locale() == Asda2Locale::Arabian)
	//	return false;

	//ebpValues[ebpValue]++;

	return true;
}

extern Asda2Proxy *asda2Proxy;
extern sf::Int16 sessionID;

void Asda2D3D9HookHandler::HandleNewFrame()
{
	auto clientVersion = GetAsda2Locale();
	if (!isFontLoaded && clientVersion != Asda2Locale::Unknown)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		TextureFactory::Instance()->ReleaseTextures();

		switch (clientVersion)
		{
		case Asda2Locale::English:
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGEN_FONT), 13);
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGEN_FONT), 14);
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGEN_FONT), 15);
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGEN_FONT), 16);
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGEN_FONT), 17);
			break;
		case Asda2Locale::Arabian:
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGAR_FONT), 13);
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGAR_FONT), 14);
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGAR_FONT), 15);
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGAR_FONT), 16);
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGAR_FONT), 17);
			break;
		case Asda2Locale::Russian:
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGRU_FONT), 13, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGRU_FONT), 14, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGRU_FONT), 15, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGRU_FONT), 16, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_PATH(AGRU_FONT), 17, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			break;
		}

		ImGui_ImplDX9_CreateDeviceObjects();
		isFontLoaded = true;
	}

	//MEMORY_PROFILE memoryProfile;
	//ChainProfile(&memoryProfile);
	//for (DWORD i = 0; i < memoryProfile.dwStorageCount; i++)
	//{
	//	char name[256];
	//	sprintf_s(name, "Storage #%d", i);
	//	if (ImGui::Begin(name))
	//	{
	//		const float padX = ImGui::GetCursorPosX();
	//		const float padY = ImGui::GetCursorPosY();
	//		const float size = 10;
	//		auto x = ImGui::GetWindowPos().x + padX;
	//		auto y = ImGui::GetWindowPos().y + padY;
	//		ImGui::SetWindowSize(ImVec2(padX * 2 + MEMORY_BLOCK_COUNT_X * size, padY + MEMORY_BLOCK_COUNT_Y * size + 10));

	//		for (int j = 0; j < MEMORY_BLOCK_COUNT_X; j++)
	//			for (int k = 0; k < MEMORY_BLOCK_COUNT_Y; k++)
	//			{
	//				const auto& block = memoryProfile.lpStorageProfile[i].lpBlockInfo[k * MEMORY_BLOCK_COUNT_Y + j];

	//				ImU32 color = 0xFF222222;
	//				if (!block.bFree)
	//					color = 0xFF444444 + static_cast<ImU32>(0x00888888 * (block.dwChainID % 100) / 100.f);
	//					//color = 0xFFFFFFFF;

	//				ImVec2 a(x + j * size, y + k * size);
	//				ImGui::GetWindowDrawList()->AddRectFilled(a, ImVec2(a.x + size, a.y + size), color);
	//			}

	//		// Освобождение памяти
	//		free(memoryProfile.lpStorageProfile[i].lpBlockInfo);
	//	}
	//	ImGui::End();
	//}

	//// Освобождение памяти
	//free(memoryProfile.lpStorageProfile);

	DailyBonus();
	//MiningWar();

	//ImGui::Begin("EBP parser");
	//for (auto pair : ebpValues)
	//{
	//	ImGui::Text("%u -> %u", pair.first, pair.second);
	//}
	//ImGui::End();

#pragma region Fly-Camera

	// Структура области памяти
	struct Memory
	{
		// Указатель на область памяти для резервного копирования
		char *pBuffer;

		// Указатель на область памяти с резервной копией
		char *pBackup;

		// Размер области памяти
		size_t szSize;

		Memory(size_t address, size_t size)
		{
			pBuffer = reinterpret_cast<char*>(address);
			pBackup = new char[size];
			szSize = size;
		}

		// Отключает инструкции в заданной области памяти
		void Disable()
		{
			DWORD flOldProtect;
			VirtualProtect(pBuffer, szSize, PAGE_READWRITE, &flOldProtect);
			memcpy_s(pBackup, szSize, pBuffer, szSize);
			memset(pBuffer, 0x90, szSize);
			VirtualProtect(pBuffer, szSize, flOldProtect, NULL);
		}

		// Восстанавливает инструкции в заданной области памяти
		void Restore()
		{
			DWORD flOldProtect;
			VirtualProtect(pBuffer, szSize, PAGE_READWRITE, &flOldProtect);
			memcpy_s(pBuffer, szSize, pBackup, szSize);
			VirtualProtect(pBuffer, szSize, flOldProtect, NULL);
		}
	};
	
	static Memory pMemory[] =
	{
		Memory(0x0040A730, 0x05),	// 5 байтов
		Memory(0x00A30F92, 0x05),	// 5 байтов
		Memory(0x00A2B3E2, 0x10),	// 16 байтов
		Memory(0x0040A744, 0x05),	// 5 байтов
	};

	// Флаг включения камеры-полета
	static auto isFlyCameraEnabled = false;

	// Включение/отключение камеры клиента
	if (ImGui::IsKeyPressed(VK_NUMPAD0))
	{
		isFlyCameraEnabled = !isFlyCameraEnabled;
		for (size_t i = 0; i < sizeof(pMemory) / sizeof(pMemory[0]); i++)
			if (isFlyCameraEnabled)
				pMemory[i].Disable();
			else
				pMemory[i].Restore();
	}

	if (isFlyCameraEnabled)
	{
		// Указатели на данные камеры
		auto pCameraX = reinterpret_cast<float*>(0x00EED6F4);
		auto pCameraY = reinterpret_cast<float*>(0x00EED6F8);
		auto pCameraZ = reinterpret_cast<float*>(0x00EED6FC);
		auto pCameraPitch = reinterpret_cast<float*>(0x00EEDA68);
		auto pCameraYaw = reinterpret_cast<float*>(0x00EEDA6C);

		// Скорость камеры
		const static float cameraSpeed = 20;

		// Время с прошлого обновления
		auto deltaTime = ImGui::GetIO().DeltaTime;

		// Углы поворота камеры
		auto cameraPitch = *pCameraPitch;
		auto cameraYaw = *pCameraYaw;

		static auto lastMMB = false;
		static auto lastX = 0.f;
		static auto lastY = 0.f;
		if (ImGui::IsMouseDown(2))
		{
			if (lastMMB)
			{
				*pCameraPitch += ImGui::GetMouseDragDelta().y * 6 * deltaTime;
				*pCameraYaw += ImGui::GetMouseDragDelta().x * 6 * deltaTime;
			}

			lastMMB = true;
		}
		else
			lastMMB = false;

		// Направляющие векторы камеры
		auto cameraUpY = cameraSpeed * sin(cameraPitch);
		auto cameraForwardX = -sin(cameraYaw) * cameraSpeed * cos(cameraPitch);
		auto cameraForwardZ = -cos(cameraYaw) * cameraSpeed * cos(cameraPitch);
		auto cameraSideX = -cos(cameraYaw) * cameraSpeed;
		auto cameraSideZ = sin(cameraYaw) * cameraSpeed;

		// Нажатые клавиши
		auto isNumpad8Down = ImGui::IsKeyDown(VK_NUMPAD8);
		auto isNumpad2Down = ImGui::IsKeyDown(VK_NUMPAD2);
		auto isNumpad4Down = ImGui::IsKeyDown(VK_NUMPAD4);
		auto isNumpad6Down = ImGui::IsKeyDown(VK_NUMPAD6);

		if (isNumpad8Down || isNumpad2Down || isNumpad4Down || isNumpad6Down)
		{
			// Движение вперед
			if (isNumpad8Down)
			{
				*pCameraX += cameraForwardX;
				*pCameraZ += cameraForwardZ;
				*pCameraY += cameraUpY;
			}

			// Движение назад
			if (isNumpad2Down)
			{
				*pCameraX -= cameraForwardX;
				*pCameraZ -= cameraForwardZ;
				*pCameraY -= cameraUpY;
			}

			// Движение влево
			if (isNumpad4Down)
			{
				*pCameraX += cameraSideX;
				*pCameraZ += cameraSideZ;
			}

			// Движение вправо
			if (isNumpad6Down)
			{
				*pCameraX -= cameraSideX;
				*pCameraZ -= cameraSideZ;
			}
		}
	}

#pragma endregion

#pragma region Buff Test

	//ImGui::Begin("Buff Test");
	//ImGui::Text("%d", sessionID);
	//static int buffIdOffset = 0;
	//static int buffCount = 10;
	//ImGui::InputInt("Buff Id Offset", &buffIdOffset, 10);
	//ImGui::InputInt("Buff Count", &buffCount);

	//if (ImGui::Button("Send 5272"))
	//{
	//	for (int buffId = buffIdOffset; buffId < buffIdOffset + buffCount; buffId++)
	//	{
	//		Buffer outBuffer; outBuffer.SetOffset(10);
	//		outBuffer.Write(sessionID);
	//		outBuffer.Write<sf::Int16>(buffId);
	//		outBuffer.Write<sf::Int16>(buffId);
	//		outBuffer.Write<sf::Int16>(501);
	//		outBuffer.Write<sf::Int16>(1);
	//		outBuffer.Write<sf::Uint8>(1);
	//		outBuffer.Write<sf::Int16>(60);
	//		outBuffer.Write<sf::Uint8>(1);
	//		outBuffer.Write<sf::Int16>(1);
	//		asda2Proxy->SendServerPacket(5272, outBuffer);
	//	}
	//}

	//if (ImGui::Button("Send 5273"))
	//{
	//	for (int buffId = buffIdOffset; buffId < buffIdOffset + buffCount; buffId++)
	//	{
	//		Buffer outBuffer; outBuffer.SetOffset(10);
	//		outBuffer.Write(sessionID);
	//		outBuffer.Write<sf::Int16>(buffId);
	//		asda2Proxy->SendServerPacket(5273, outBuffer);
	//	}
	//}

	//ImGui::End();

#pragma endregion
}