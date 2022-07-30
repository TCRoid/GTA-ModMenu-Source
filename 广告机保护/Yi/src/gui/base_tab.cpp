#include "common.hpp"
#include "base_tab.h"
#include "imgui.h"
#include "script.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "ImGuiBitfield.h"
#include "features.hpp"
#include "fonts.hpp"
#include "script_global.hpp"
#include "gta\Vehicles.h"
#include "Ini.h"

void base_tab::render_base_tab()
{
	if (ImGui::BeginTabItem("���˵�"))
	{
		ImGui::Text("����ȷ��������:����Chat Ϊ��״̬");
		if (ImGui::InputText("������������", features::texts, 500)) {
			INI::WriteChar("C:\\ggj\\load.ini", features::texts, "Game", "GT");
		}
		if (ImGui::Button("���η���")) {
			int handle[13];
			for (int i{}; i < 32; i++) {
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
					int handle[13];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, handle, 13);
					NETWORK::NETWORK_SEND_TEXT_MESSAGE(features::texts, &handle[0]);
				}
			}
		}
		ImGui::Separator();
		if (ImGui::Checkbox("�һ�����", &features::sendbool)) {
			INI::WriteBool("C:\\ggj\\load.ini", features::sendbool, "Game", "GuaJi");
		}
		if (ImGui::InputInt("�л�ս��ʱ��(ms)", &features::time1)) {
			INI::WriteInt("C:\\ggj\\load.ini", features::time1, "Game", "Time1");
		}
		if (ImGui::InputInt("�����������(ms)", &features::time2)) {
			INI::WriteInt("C:\\ggj\\load.ini", features::time1, "Game", "Time2");
		}
		ImGui::Separator();
		ImGui::Checkbox("�޵�", &features::godmode);
		if (ImGui::Button("�ر�"))
		{
			g_running = false;
		}
		ImGui::EndTabItem();
	}
}
