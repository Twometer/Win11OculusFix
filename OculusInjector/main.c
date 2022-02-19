#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>

DWORD FindProcessId(LPCSTR processName) {
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);

    do {
        if (!strcmp(processName, processInfo.szExeFile)) {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    } while (Process32Next(processesSnapshot, &processInfo));

    CloseHandle(processesSnapshot);
    return 0;
}

BOOL FileExists(LPCTSTR szPath) {
    DWORD dwAttrib = GetFileAttributes(szPath);

    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
            !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

int main() {
    // Find DLL
    LPCSTR dllName = "OculusLib.dll";
    CHAR dllPath[256];
    if (!GetFullPathNameA(dllName, 256, dllPath, NULL)) {
        printf("error: Failed to resolve library path\n");
        return 1;
    }

    if (!FileExists(dllName)) {
        printf("error: Failed to find library\n");
        return 1;
    }

    printf("Found DLL at %s\n", dllPath);

    // Find process
    DWORD processId = FindProcessId("OVRServer_x64.exe");
    printf("Injecting into Process ID %lu\n", processId);

    // Open process handle
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

    // Write DLL path to target process
    LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(hProcess, pDllPath, (LPVOID) dllPath, strlen(dllPath) + 1, 0);

    // Create thread in target process that loads the library and wait for loader to exit
    HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0,
                                            (LPTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandleA("Kernel32.dll"),
                                                                                    "LoadLibraryA"), pDllPath, 0, 0);
    WaitForSingleObject(hLoadThread, INFINITE);
    printf("Injected DLL\n");

    // Free process memory
    VirtualFreeEx(hProcess, pDllPath, strlen(dllPath) + 1, MEM_RELEASE);
    printf("Released memory\n");
    return 0;
}
