#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include "offsets.h"

#define PI 3.1415926535f

struct Vector3 {
    float x, y, z;
    float Distance(Vector3 v) {
        return sqrtf(powf(v.x - x, 2) + powf(v.y - y, 2) + powf(v.z - z, 2));
    }
};

struct PhotonPlayer {
    // Fill based on offsets provided
    // walkSpeed is at 0xBC
    // We can assume transform is somewhere
    char pad[0xBC];
    float walkSpeed;
};

struct Il2CppArray {
    void* klass;
    void* monitor;
    void* bounds;
    int32_t max_length;
    PhotonPlayer* vector[0];
};

uintptr_t gameAssembly = 0;

typedef Il2CppArray* (*tGetPlayerList)();

// Simple Math for Aimbot
struct Angle { float yaw, pitch; };

Angle CalculateAngle(Vector3 local, Vector3 target) {
    Vector3 delta = { target.x - local.x, target.y - local.y, target.z - local.z };
    float hypers = sqrtf(delta.x * delta.x + delta.z * delta.z);
    return {
        atan2f(delta.z, delta.x) * (180.0f / PI),
        atan2f(-delta.y, hypers) * (180.0f / PI)
    };
}

void CheatThread(HMODULE hModule) {
    gameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
    if (!gameAssembly) return;

    auto getOtherPlayers = (tGetPlayerList)(gameAssembly + Offsets::otherPlayers);

    while (!(GetAsyncKeyState(VK_INSERT) & 1)) {
        if (GetAsyncKeyState(VK_RBUTTON)) {
            Il2CppArray* list = getOtherPlayers();
            if (list && list->max_length > 0) {
                // Iterating through other players
                for (int i = 0; i < list->max_length; i++) {
                    PhotonPlayer* player = list->vector[i];
                    if (!player) continue;
                    
                    // Example: Set walk speed
                    player->walkSpeed = 5.0f; 

                    // Aim logic would go here
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)CheatThread, hModule, 0, nullptr));
        break;
    }
    return TRUE;
}
