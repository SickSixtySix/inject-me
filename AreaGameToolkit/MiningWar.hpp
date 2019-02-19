#pragma once

// InjectMe
#include "Buffer.hpp"

namespace Addon::UI::MiningWar
{
	// ����
	void HandleJoinResponse(InjectMe::Utils::Buffer &buffer);

	// ���������� ���� ������
	void HandleMiningUpdate(InjectMe::Utils::Buffer &buffer);

	// ���������� ���� �����
	void HandleBattleUpdate(InjectMe::Utils::Buffer &buffer);

	// ������ �����
	void HandleBattleStarted(InjectMe::Utils::Buffer &buffer);

	// ����� �����
	void HandleBattleStopped(InjectMe::Utils::Buffer &buffer);

	// ���������� ������� ������ �����
	void HandleBattleStartTimeUpdate(InjectMe::Utils::Buffer &buffer);

	// ���������
	void MiningWar();
}