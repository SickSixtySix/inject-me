// InjectMe
#include "Translator.hpp"

using namespace InjectMe::Utils;

// SFML
#include <SFML/System/Lock.hpp>

Translator *Translator::s_instance = nullptr;

sf::Mutex Translator::s_instanceMutex;

std::string Translator::s_emptyEntry = "<null>";

Translator::Translator()
{
	//// ����� ������ (RU)
	//AddEntry(RU, OK, "��");
	//AddEntry(RU, CANCEL, "������");

	//// ������ ����� ���� (RU)
	//AddEntry(RU, NEXT_WAR_TIME_TEXT, "����� ��������� �����");
	//AddEntry(RU, NEXT_WAR_TIME, "����������� � 9:00 � � 21:00");
	//AddEntry(RU, DOESNT_BELONG_TO_ANY_GUILD_TEXT, "�� ����������� �� ����� �������");
	//AddEntry(RU, N_PLAYERS, "�������");
	//AddEntry(RU, LIGHT, "����");
	//AddEntry(RU, DARK, "����");
	//AddEntry(RU, CHAOS, "����");
	//AddEntry(RU, YOU_HAVE_WON, "�� ��������");
	//AddEntry(RU, YOU_HAVE_LOSE, "�� ���������");
	//AddEntry(RU, ADDITIONAL_REWARD, "�������������� �������");
	//AddEntry(RU, HONOR_POINT, "���� ������");
	//AddEntry(RU, NEXT_BATTLE_TIME, "����� ��������� �����");
	//AddEntry(RU, MONDAY, "�����������");
	//AddEntry(RU, TUESDAY, "�������");
	//AddEntry(RU, WEDNESDAY, "�����");
	//AddEntry(RU, THURSDAY, "�������");
	//AddEntry(RU, FRIDAY, "�������");
	//AddEntry(RU, SATURDAY, "�������");
	//AddEntry(RU, SUNDAY, "�����������");

	//// ����� ������ (EN)
	//AddEntry(EN, OK, "OK");
	//AddEntry(EN, CANCEL, "Cancel");

	//// ������ ����� ���� (EN)
	//AddEntry(EN, NEXT_WAR_TIME_TEXT, "Next war time");
	//AddEntry(EN, NEXT_WAR_TIME, "Monday AM/PM 9:00");
	//AddEntry(EN, DOESNT_BELONG_TO_ANY_GUILD_TEXT, "Doesn't belong to any guild.");
	//AddEntry(EN, N_PLAYERS, "Players");
	//AddEntry(EN, LIGHT, "Light");
	//AddEntry(EN, DARK, "Dark");
	//AddEntry(EN, CHAOS, "Chaos");
	//AddEntry(EN, YOU_HAVE_WON, "You Have Won");
	//AddEntry(EN, YOU_HAVE_LOSE, "You Have Lose");
	//AddEntry(EN, ADDITIONAL_REWARD, "Additional reward");
	//AddEntry(EN, HONOR_POINT, "Honor Point");
	//AddEntry(EN, NEXT_BATTLE_TIME, "Next Battle Time");
	//AddEntry(EN, MONDAY, "Monday");
	//AddEntry(EN, TUESDAY, "Tuesday");
	//AddEntry(EN, WEDNESDAY, "Wednesday");
	//AddEntry(EN, THURSDAY, "Thursday");
	//AddEntry(EN, FRIDAY, "Friday");
	//AddEntry(EN, SATURDAY, "Saturday");
	//AddEntry(EN, SUNDAY, "Sunday");
}

Translator* Translator::GetInstance()
{
	{
		sf::Lock lock(s_instanceMutex);
		if (s_instance == nullptr)
			s_instance = new Translator();
	}

	return s_instance;
}

void Translator::AddEntry(const LocaleType& locale, const EntryType& type, const std::string& value)
{
	m_entries[std::pair(locale, type)] = value;
}

const std::string& Translator::GetEntry(const LocaleType& locale, const EntryType& type) const
{
	auto it = m_entries.find(std::pair(locale, type));

	if (m_entries.end() != it)
		return it->second;

	return s_emptyEntry;
}