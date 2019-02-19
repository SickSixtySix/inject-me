#pragma once

// InjectMe
#include "ID3D9HookHandler.hpp"

namespace InjectMe::Hook::D3D9
{
	// ��������� ����������� ��������� Direct3D 9 ��� Asda 2
	class Asda2D3D9HookHandler : public ID3D9HookHandler
	{
		// ��������� ������
		static Asda2D3D9HookHandler *s_instance;

		// ����������� ������
		Asda2D3D9HookHandler();

	public:

		// ���������� ��������� ������
		static Asda2D3D9HookHandler* Instance();

		// ���������� ���� ��������� ������ ������
		bool CanHandleNewFrame(unsigned long ebpValue) final;

		// ���������� ������ ������
		void HandleNewFrame() final;
	};
}