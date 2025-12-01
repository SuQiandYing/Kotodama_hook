#pragma once
#include <windows.h>

namespace Utils {
    BOOL LoadCustomFont(HMODULE hModule);
    void ShowStartupPopup();
    void CheckPassword();
    BOOL DeployLeFiles(HMODULE hModule);
    void CleanupLeFiles();
    void Log(const char* format, ...);
    void InitConsole();
}
