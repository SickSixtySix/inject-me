#pragma once

// InjectMe
#include "MiscButtonData.hpp"

namespace InjectMe::Hook::Asda2
{
	// ��������� ����������� ������� ������� ������ � �������������� ����
	class IMiscButtonHandler
	{
	public:

		// ���������� ������� ������� ������ � �������������� ����
		virtual void HandleMiscButton(const MiscButtonData &args) = 0;
	};
}