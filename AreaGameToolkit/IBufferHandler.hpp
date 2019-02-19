#pragma once

namespace InjectMe::Utils
{
	// ��������������� ���������� ������ ������
	class Buffer;

	// ��������� ����������� ������� ������
	class IBufferHandler
	{
	public:

		// ���������� ������� ������ �������� �� ������
		virtual void HandleRead(const Buffer &buffer, void *data, size_t offset, size_t length) = 0;

		// ���������� ������� ������ �������� � �����
		virtual void HandleWrite(Buffer &buffer, char *data, size_t offset, size_t length) = 0;
	};
}