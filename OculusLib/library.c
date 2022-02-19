#include <Windows.h>

void ThreadMain(HMODULE hModule) {
    Sleep(100);
    MessageBox(0, "While this message box is open, the Oculus lag won't occur :-)", "Win11OculusFix", MB_ICONINFORMATION);
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulCallReason, LPVOID lpReserved) {
    if (ulCallReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadMain, hModule, 0, NULL);
    }
    return TRUE;
}
