#pragma once

namespace InjectMe::Hook::WSA
{
	// ��������� ������ ��� ����������� ��������� WSAConnect()
	struct WSAConnectData
	{
		// ������ ���� IP ������
		unsigned char b1;

		// ������ ���� IP ������
		unsigned char b2;

		// ������ ���� IP ������
		unsigned char b3;

		// ��������� ���� IP ������
		unsigned char b4;

		// ���� ����������
		unsigned short DestinationPort;

		// �������� ����
		unsigned short SourcePort;
	};
}