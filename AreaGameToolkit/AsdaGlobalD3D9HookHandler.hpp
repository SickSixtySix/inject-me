#pragma once

// InjectMe
#include "ID3D9HookHandler.hpp"

namespace InjectMe::Hook::D3D9
{
	// Интерфейс обработчика перехвата Direct3D 9 для Asda Global
	class AsdaGlobalD3D9HookHandler : public ID3D9HookHandler
	{
		// Экземпляр класса
		static AsdaGlobalD3D9HookHandler *s_instance;

		// Конструктор класса
		AsdaGlobalD3D9HookHandler();

	public:

		// Возвращает экземпляр класса
		static AsdaGlobalD3D9HookHandler* Instance();

		// Возвращает флаг обработки нового фрейма
		bool CanHandleNewFrame(unsigned long ebpValue) final;

		// Обработчик нового фрейма
		void HandleNewFrame() final;
	};
}