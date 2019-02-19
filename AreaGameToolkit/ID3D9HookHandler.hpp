#pragma once

namespace InjectMe::Hook::D3D9
{
	// Интерфейс обработчика перехвата Direct3D 9
	class ID3D9HookHandler
	{
	public:

		// Возвращает флаг обработки нового фрейма
		virtual bool CanHandleNewFrame(unsigned long ebpValue) = 0;

		// Обработчик нового фрейма
		virtual void HandleNewFrame() = 0;
	};
}