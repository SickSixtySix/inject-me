#pragma once

// SFML
#include <SFML/System/Mutex.hpp>

// C++
#include <map>
#include <string>

namespace InjectMe::Utils
{
	// ��� ����������� �����������
	enum LocaleType
	{
		EN,
		RU
	};

	// ��� ������ �����������
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

	// ����� �����������
	class Translator
	{
	private:

		// ��������� �����������
		static Translator *s_instance;

		// ������� ���������� �����������
		static sf::Mutex s_instanceMutex;

		// ������ ������ �����������
		static std::string s_emptyEntry;

		// ������ ������� �����������
		std::map<std::pair<LocaleType, EntryType>, std::string> m_entries;

		// ����������� �����������
		Translator();

	public:

		// �������� ��������� �����������
		static Translator* GetInstance();

		// ��������� ������ � ������ ������� �����������
		void AddEntry(const LocaleType& locale, const EntryType& type, const std::string& value);

		// ���������� ������ �� ������ ������� �����������
		const std::string& GetEntry(const LocaleType& locale, const EntryType& type) const;
	};
}