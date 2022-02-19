#include <Windows.h>

void ThreadMain(HMODULE hModule) {
    Sleep(100);
    MessageBox(0, "Don't close this message box", "Oculus Injector", MB_ICONINFORMATION);
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulCallReason, LPVOID lpReserved) {
    if (ulCallReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadMain, hModule, 0, NULL);
    }
    return TRUE;
}
