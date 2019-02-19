#pragma once

// AddonNetEmu
#include "AddonNetEmu.hpp"

// SFML
#include <SFML/Config.hpp>

// ��������� ������ ��� �������� ����� ������
struct ADDONNETEMU_API PacketOptions
{
	// ���� ������ ����������������� ������ ������
	bool Sync;

	// ���� ������ ��������� ������ ������
	bool Hash;

	// ���� ������ ��������� ����� ������
	bool Post;

	// �������� ������ ������
	long RealSize;
};