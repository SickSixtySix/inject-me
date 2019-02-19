#pragma once

// InjectMe
#include "Buffer.hpp"

namespace Addon::UI::MiningWar
{
	// Вход
	void HandleJoinResponse(InjectMe::Utils::Buffer &buffer);

	// Обновление фазы добычи
	void HandleMiningUpdate(InjectMe::Utils::Buffer &buffer);

	// Обновление фазы битвы
	void HandleBattleUpdate(InjectMe::Utils::Buffer &buffer);

	// Начало битвы
	void HandleBattleStarted(InjectMe::Utils::Buffer &buffer);

	// Конец битвы
	void HandleBattleStopped(InjectMe::Utils::Buffer &buffer);

	// Обновление времени начала битвы
	void HandleBattleStartTimeUpdate(InjectMe::Utils::Buffer &buffer);

	// Интерфейс
	void MiningWar();
}