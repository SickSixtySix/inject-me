#pragma once

// InjectMe
#include "Asda2Locale.hpp"
#include "IMiscBUttonHandler.hpp"
#include "INPCButtonHandler.hpp"
#include "Translator.hpp"

namespace InjectMe::Hook::Asda2
{
	// Добавляет обработчик события нажатия кнопки в дополнительном меню
	void AppendMiscButtonHandler(IMiscButtonHandler *handler);

	// Удаляет обработчик события нажатия кнопки в дополнительном меню
	void RemoveMiscButtonHandler(IMiscButtonHandler *handler);

	// Добавляет обработчик события нажатия кнопки в диалоге с NPC
	void AppendNPCButtonHandler(INPCButtonHandler *handler);

	// Удаляет обработчик события нажатия кнопки в диалоге с NPC
	void RemoveNPCButtonHandler(INPCButtonHandler *handler);

	// Запускает механизм перехвата Asda 2
	void StartAsda2Hook();

	// Устанавливает локаль Asda 2
	void SetAsda2Locale(const Asda2Locale &locale);

	// Возвращает локаль Asda 2
	const Asda2Locale& GetAsda2Locale();

	// Возвращает локализацию Asda2 для переводчика
	Utils::LocaleType GetAsda2TranslatorLocale();
}