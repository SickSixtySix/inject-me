#pragma once

// InjectMe
#include "NPCButtonData.hpp"

namespace InjectMe::Hook::Asda2
{
	// ��������� ����������� ������� ������� ������ � ������� � NPC
	class INPCButtonHandler
	{
	public:

		// ���������� ������� ������� ������ � ������� � NPC
		virtual void HandleNPCButton(const NPCButtonData &args) = 0;
	};
}