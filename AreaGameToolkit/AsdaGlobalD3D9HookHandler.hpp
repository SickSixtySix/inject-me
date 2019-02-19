#pragma once

// InjectMe
#include "ID3D9HookHandler.hpp"

namespace InjectMe::Hook::D3D9
{
	// ��������� ����������� ��������� Direct3D 9 ��� Asda Global
	class AsdaGlobalD3D9HookHandler : public ID3D9HookHandler
	{
		// ��������� ������
		static AsdaGlobalD3D9HookHandler *s_instance;

		// ����������� ������
		AsdaGlobalD3D9HookHandler();

	public:

		// ���������� ��������� ������
		static AsdaGlobalD3D9HookHandler* Instance();

		// ���������� ���� ��������� ������ ������
		bool CanHandleNewFrame(unsigned long ebpValue) final;

		// ���������� ������ ������
		void HandleNewFrame() final;
	};
}