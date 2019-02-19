#pragma once

namespace InjectMe::Hook::D3D9
{
	// ��������� ����������� ��������� Direct3D 9
	class ID3D9HookHandler
	{
	public:

		// ���������� ���� ��������� ������ ������
		virtual bool CanHandleNewFrame(unsigned long ebpValue) = 0;

		// ���������� ������ ������
		virtual void HandleNewFrame() = 0;
	};
}