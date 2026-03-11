#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

DWORD FindPID(const char* name) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe = { sizeof(pe) };
    DWORD pid = 0;
    if (Process32First(snap, &pe))
        do { if (!_stricmp(pe.szExeFile, name)) { pid = pe.th32ProcessID; break; } }
        while (Process32Next(snap, &pe));
    CloseHandle(snap);
    return pid;
}

int main() {
    char proc[64], dll[MAX_PATH];
    printf("Process: "); scanf("%63s", proc);
    printf("DLL path: "); scanf("%259s", dll);

    DWORD pid = 0;
    printf("Waiting for %s...\n", proc);
    while (!(pid = FindPID(proc))) Sleep(500);
    printf("PID: %lu\n", pid);

    HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    LPVOID mem = VirtualAllocEx(hp, 0, strlen(dll)+1, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
    WriteProcessMemory(hp, mem, dll, strlen(dll)+1, 0);
    HANDLE ht = CreateRemoteThread(hp, 0, 0,
        (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"),
        mem, 0, 0);
    WaitForSingleObject(ht, 5000);
    CloseHandle(ht);
    CloseHandle(hp);

    printf("Done!\n");
    return 0;
}
