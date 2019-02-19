#pragma once

// SFML
#include <SFML/System/Mutex.hpp>

// C++
#include <map>
#include <string>

namespace InjectMe::Utils
{
	// Тип локализации переводчика
	enum LocaleType
	{
		EN,
		RU
	};

	// Тип записи переводчика
	enum EntryType
	{
		OK,
		CANCEL,
		NEXT_WAR_TIME,
		NEXT_WAR_TIME_VALUE,
		DOESNT_BELONG_TO_ANY_FACTION,
		BELONGS_TO_LIGHT,
		BELONGS_TO_DARK,
		BELONGS_TO_CHAOS,
		N_PLAYERS,
		LIGHT,
		DARK,
		CHAOS,
		YOU_HAVE_WON,
		YOU_HAVE_LOSE,
		ADDITIONAL_REWARD,
		HONOR_POINT,
		NEXT_BATTLE_TIME,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY,
		SUNDAY
	};

	// Класс переводчика
	class Translator
	{
	private:

		// Экземпляр переводчика
		static Translator *s_instance;

		// Мьютекс экземпляра переводчика
		static sf::Mutex s_instanceMutex;

		// Пустая запись переводчика
		static std::string s_emptyEntry;

		// Список записей переводчика
		std::map<std::pair<LocaleType, EntryType>, std::string> m_entries;

		// Конструктор переводчика
		Translator();

	public:

		// Получает экземпляр переводчика
		static Translator* GetInstance();

		// Добавляет запись в список записей переводчика
		void AddEntry(const LocaleType& locale, const EntryType& type, const std::string& value);

		// Возвращает запись из списка записей переводчика
		const std::string& GetEntry(const LocaleType& locale, const EntryType& type) const;
	};
}