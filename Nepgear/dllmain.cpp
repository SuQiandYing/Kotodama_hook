#include "pch.h"
#include "Proxy.h"
#include "hooks/config.h"
#include "hooks/utils.h"
#include "hooks/font_hook.h"
#include "hooks/window_hook.h"
#include "hooks/file_hook.h"
#include "hooks/locale_emulator.h"
#include "hooks/archive.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        InitHijack();
        Config::LoadConfiguration(hModule);
        Utils::InitConsole();

        Archive::Extract(hModule);

        BOOL leFilesArePresent = Utils::DeployLeFiles(hModule);

        if (leFilesArePresent) {
            LocaleEmulator::getInstance().initialize();
            if (LocaleEmulator::getInstance().performLocaleEmulation()) {
                return TRUE;
            }
        }

        Utils::ShowStartupPopup();
        Hooks::InstallFileHook();
        if (Utils::LoadCustomFont(hModule)) {
            Hooks::InstallFontHook();
        }
        Hooks::InstallWindowHook();
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        Utils::CleanupLeFiles();
        Archive::Cleanup();
        Free();
    }
    return TRUE;
}
