﻿#include "common.hpp"
#include "features.hpp"
#include "fiber_pool.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"
#include"scripthookv.hpp"
#include"translate.hpp"
using namespace std;

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace big;
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;
		g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
			{
				while (!FindWindow(L"grcWindow", L"Grand Theft Auto V"))
					std::this_thread::sleep_for(1s);

				auto logger_instance = std::make_unique<logger>();
				try
				{
					LOG(RAW_GREEN_TO_CONSOLE) << u8R"kek(
_____                   _         _____   _
|  __ \                 | |       / ____| | |
| |  | |   __ _   _ __  | | __   | (___   | |_    __ _   _ __
| |  | |  / _` | | '__| | |/ /    \___ \  | __|  / _` | | '__|
| |__| | | (_| | | |    |   <     ____) | | |_  | (_| | | |
|_____/   \__,_| |_|    |_|\_\   |_____/   \__|  \__,_| |_|    )kek";
					auto pointers_instance = std::make_unique<pointers>();
					LOG(INFO) << "Pointers initialized.";

					auto renderer_instance = std::make_unique<renderer>();
					LOG(INFO) << "Renderer initialized.";

					auto fiber_pool_instance = std::make_unique<fiber_pool>(10);
					LOG(INFO) << "Fiber pool initialized.";

					auto hooking_instance = std::make_unique<hooking>();
					LOG(INFO) << "Hooking initialized.";

					//auto scripthookv_instance = std::make_unique<shv::ScriptHookV>();
					//LOG(INFO) << "ScriptHookV initialized.";

					g_settings.load();
					LOG(INFO) << "Settings Loaded.";

					std::string language = g_settings.options["language"].get<std::string>();
					g_translates.load(language);
					LOG(INFO) << "Language " << language << " Loaded.";

					g_script_mgr.add_script(std::make_unique<script>(&features::script_func));
					g_script_mgr.add_script(std::make_unique<script>(&gui::script_func));
					LOG(INFO) << "Scripts registered.";

					g_hooking->enable();
					LOG(INFO) << "Hooking enabled.";
					LOG(INFO) << "注入成功！游戏内按INS呼出/隐藏菜单.";

					while (g_running)
					{
						if (*g_pointers->m_is_session_started == false)
						{
							g_settings.mgr == nullptr;
						}
						std::this_thread::sleep_for(500ms);
					}

					g_hooking->disable();
					std::this_thread::sleep_for(1000ms);

					g_script_mgr.remove_all_scripts();
					LOG(INFO) << "Scripts unregistered.";

					//scripthookv_instance.reset();
					//LOG(INFO) << "ScriptHookV uninitialized.";

					hooking_instance.reset();
					LOG(INFO) << "Hooking uninitialized.";

					fiber_pool_instance.reset();
					LOG(INFO) << "Fiber pool uninitialized.";

					renderer_instance.reset();
					LOG(INFO) << "Renderer uninitialized.";

					pointers_instance.reset();
					LOG(INFO) << "Pointers uninitialized.";
				}
				catch (std::exception const& ex)
				{
					LOG(WARNING) << ex.what();
					MessageBoxA(nullptr, ex.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
				}
				logger_instance.reset();

				CloseHandle(g_main_thread);
				FreeLibraryAndExitThread(g_hmodule, 0);
			}, nullptr, 0, &g_main_thread_id);
	}

	return true;
}