#pragma once

// InjectMe
#include "Asda2Locale.hpp"
#include "IMiscBUttonHandler.hpp"
#include "INPCButtonHandler.hpp"
#include "Translator.hpp"

namespace InjectMe::Hook::Asda2
{
	// ��������� ���������� ������� ������� ������ � �������������� ����
	void AppendMiscButtonHandler(IMiscButtonHandler *handler);

	// ������� ���������� ������� ������� ������ � �������������� ����
	void RemoveMiscButtonHandler(IMiscButtonHandler *handler);

	// ��������� ���������� ������� ������� ������ � ������� � NPC
	void AppendNPCButtonHandler(INPCButtonHandler *handler);

	// ������� ���������� ������� ������� ������ � ������� � NPC
	void RemoveNPCButtonHandler(INPCButtonHandler *handler);

	// ��������� �������� ��������� Asda 2
	void StartAsda2Hook();

	// ������������� ������ Asda 2
	void SetAsda2Locale(const Asda2Locale &locale);

	// ���������� ������ Asda 2
	const Asda2Locale& GetAsda2Locale();

	// ���������� ����������� Asda2 ��� �����������
	Utils::LocaleType GetAsda2TranslatorLocale();
}