// Cheat
#include "Sniffer.hpp"

using namespace Cheat::Sniffer;

using namespace InjectMe::Utils;
using namespace InjectMe::Network;

// ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_memory_editor.h"

// SFML
#include <SFML/System/Lock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Thread.hpp>

// C++
#include <functional>
#include <string>
#include <utility>

void PushProxyColor(Proxy *proxy)
{
	auto hash = std::hash<Proxy*>()(proxy);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(
		0.5f + 0.5f * (hash >> 0x08 & 0xFF) / 255.f,
		0.5f + 0.5f * (hash >> 0x10 & 0xFF) / 255.f,
		0.5f + 0.5f * (hash >> 0x18 & 0xFF) / 255.f, 1.0f));
}

void PopProxyColor()
{
	ImGui::PopStyleColor();
}

void transferFunction(Sniffer::Transfer *transfer)
{
	while (transfer->current < transfer->total)
	{
		if (!transfer->suspend)
		{
			auto copy = transfer->packet.buffer;
			switch (transfer->packet.direction)
			{
			case 0:
			case 2:
				transfer->packet.proxy->SendClientPacket(transfer->packet.packetID, copy);
				break;
			case 1:
			case 3:
				transfer->packet.proxy->SendServerPacket(transfer->packet.packetID, copy);
				break;
			}

			++transfer->current;
		}

		sf::sleep(sf::milliseconds(5));
	}
}

Sniffer *Sniffer::s_sniffer = nullptr;

struct Sniffer::MemoryEditorImpl
{
	MemoryEditor editor;
};

Sniffer::Sniffer() : m_editor(new MemoryEditorImpl()) {}

Sniffer* Sniffer::Instance()
{
	if (s_sniffer == nullptr)
		s_sniffer = new Sniffer();

	return s_sniffer;
}

void Sniffer::LogFromClientToServer(Proxy *proxy, sf::Uint16 packetID, const Buffer &buffer)
{
	sf::Lock lock(m_historyMutex); m_history.push_back({ proxy, 0, packetID, buffer });
}

void Sniffer::LogFromServerToClient(Proxy *proxy, sf::Uint16 packetID, const Buffer &buffer)
{
	sf::Lock lock(m_historyMutex); m_history.push_back({ proxy, 1, packetID, buffer });
}

void Sniffer::LogFromProxyToServer(Proxy *proxy, sf::Uint16 packetID, const Buffer &buffer)
{
	sf::Lock lock(m_historyMutex); m_history.push_back({ proxy, 2, packetID, buffer });
}

void Sniffer::LogFromProxyToClient(Proxy *proxy, sf::Uint16 packetID, const Buffer &buffer)
{
	sf::Lock lock(m_historyMutex); m_history.push_back({ proxy, 3, packetID, buffer });
}
	
void Sniffer::ImGui()
{
	sf::Lock lock(m_historyMutex);

	ImGui::Begin("Sniffer", 0, ImGuiWindowFlags_AlwaysAutoResize);

#pragma region Список пакетов

	ImGui::BeginChild("##sniffer_history", ImVec2(192, 384), true);
	ImGui::Columns(3);
	ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() * 0.45f);
	ImGui::SetColumnWidth(1, ImGui::GetWindowWidth() * 0.20f);
	ImGui::SetColumnWidth(2, ImGui::GetWindowWidth() * 0.35f);
	ImGui::Separator();
	ImGui::Text("Pr"); ImGui::NextColumn();
	ImGui::Text("Dr"); ImGui::NextColumn();
	ImGui::Text("ID"); ImGui::NextColumn();
	ImGui::Separator();
	for (size_t i = 0; i < m_history.size(); i++)
	{
		m_proxies.insert(m_history[i].proxy);
		m_packetIDs.insert(m_history[i].packetID);

		if (m_filterProxy != nullptr && m_history[i].proxy != m_filterProxy)
			continue;

		if (m_filterPacket != 0 && m_history[i].packetID != m_filterPacket)
			continue;

		char label[64];
		sprintf(label, "%p##%u", m_history[i].proxy, i);
		PushProxyColor(m_history[i].proxy);
		if (ImGui::Selectable(label, m_editPacket == i, ImGuiSelectableFlags_SpanAllColumns))
		{
			m_editPacket = i;
			m_editor->editor.Open = true;
		}
		sprintf_s(label, "##packet_%u_context_menu", i);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
		if (ImGui::BeginPopupContextItem(label))
		{
			if (ImGui::BeginMenu("Send To Client..."))
			{
				for (auto proxy : m_proxies)
				{
					sprintf_s(label, "%p##send_to_client_%p", proxy, proxy);
					PushProxyColor(proxy);
					if (ImGui::MenuItem(label))
					{
						auto copy = m_history[i];
						copy.proxy = proxy;
						copy.direction = 3;
						m_transfers.push_back(new Transfer { copy, 0, 1, false });
						(new sf::Thread(&transferFunction, m_transfers[m_transfers.size() - 1]))->launch();
						ImGui::CloseCurrentPopup();
					}
					PopProxyColor();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Send To Server..."))
			{
				for (auto proxy : m_proxies)
				{
					sprintf_s(label, "%p##send_to_server_%p", proxy, proxy);
					PushProxyColor(proxy);
					if (ImGui::MenuItem(label))
					{
						auto copy = m_history[i];
						copy.proxy = proxy;
						copy.direction = 2;
						m_transfers.push_back(new Transfer{ copy, 0, 1, false });
						(new sf::Thread(&transferFunction, m_transfers[m_transfers.size() - 1]))->launch();
						ImGui::CloseCurrentPopup();
					}
					PopProxyColor();
				}
				ImGui::EndMenu();
			}

			if (ImGui::Button("Save To File"))
			{
				char filename[16];
				sprintf_s(filename, "%u", m_history[i].packetID);
				m_history[i].buffer.Save(filename);
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		PopProxyColor();
		ImGui::NextColumn();

		switch (m_history[i].direction)
		{
		case 0: sprintf_s(label, "<-"); break;
		case 1: sprintf_s(label, "->"); break;
		case 2: sprintf_s(label, "<<"); break;
		case 3: sprintf_s(label, ">>"); break;
		}
		ImGui::Text(label); ImGui::NextColumn();

		sprintf_s(label, "%u", m_history[i].packetID);
		ImGui::Text(label); ImGui::NextColumn();
		ImGui::PopStyleColor();
	}
	ImGui::EndChild();

#pragma endregion

#pragma region Фильтрация по прокси

	ImGui::SameLine();
	ImGui::BeginChild("##sniffer_proxy_filter", ImVec2(128, 0));
	ImGui::Text("Filter by proxy");
	if (ImGui::Button("Reset"))
		m_filterProxy = nullptr;
	ImGui::BeginChild("##domain_1", ImVec2(0, 0), true);
	for (auto proxy : m_proxies)
	{
		char sProxy[64];
		sprintf_s(sProxy, "%p", proxy);
		if (ImGui::Selectable(sProxy, m_filterProxy == proxy))
			m_filterProxy = proxy;
	}
	ImGui::EndChild();
	ImGui::EndChild();

#pragma endregion

#pragma region Фильтрация по пакетам

	ImGui::SameLine();
	ImGui::BeginChild("##sniffer_packet_filter", ImVec2(128, 0));
	ImGui::Text("Filter by packet");
	if (ImGui::Button("Reset"))
		m_filterPacket = 0;
	ImGui::SameLine();

	static char sFilterPacket[16];
	int tempFilterPacket = -1;
	sscanf_s(sFilterPacket, "%d", &tempFilterPacket);

	if (ImGui::Button("+") && tempFilterPacket != -1)
	{
		m_packetIDs.insert(tempFilterPacket);
		m_filterPacket = tempFilterPacket;
	}
		
	ImGui::SameLine();
	ImGui::InputText("##ID", sFilterPacket, sizeof(sFilterPacket));

	ImGui::BeginChild("##domain_2", ImVec2(0, 0), true);
	for (auto packetID : m_packetIDs)
	{
		char sPacketID[64];
		sprintf_s(sPacketID, "%u", packetID);
		if (ImGui::Selectable(sPacketID, m_filterPacket == packetID))
			m_filterPacket = packetID;
	}
	ImGui::EndChild();
	ImGui::EndChild();

#pragma endregion

#pragma region Активные передачи

	ImGui::SameLine();
	ImGui::BeginChild("##sniffer_transfers", ImVec2(128, 0));
	ImGui::Text("Active Transfers");
	ImGui::Button("Reset");
	ImGui::BeginChild("##domain_3", ImVec2(0, 0), true);
	for (auto transfer : m_transfers)
	{
		ImGui::ProgressBar(transfer->current / (float)transfer->total);
		char label[64];
		sprintf_s(label, "##transfer_%p_context_menu", transfer);
		if (transfer->current != transfer->total && ImGui::BeginPopupContextItem(label))
		{
			if (!transfer->suspend && ImGui::Button("Suspend"))
			{
				transfer->suspend = true;
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::Button("Stop"))
			{
				transfer->current = transfer->total;
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::Button("Wake"))
			{
				transfer->suspend = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
	ImGui::EndChild();
	ImGui::EndChild();

#pragma endregion

	ImGui::End();

	// Редактор памяти
	if (m_editPacket != -1 && m_history.size() > 0 && m_editor->editor.Open)
	{
		if (m_history.size() - 1 < m_editPacket)
			m_editPacket = 0;

		m_editor->editor.DrawWindow("Editor", reinterpret_cast<MemoryEditor::u8*>(m_history[m_editPacket].buffer.GetMemory().lpAddress), m_history[m_editPacket].buffer.GetOffset());
	}
}