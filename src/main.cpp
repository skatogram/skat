#include <windows.h>
#include <d3d11.h>
#include <iostream>
#include <vector>
#include <thread>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "MinHook.h"

#include "offsets.h"
#include "unity.h"

#define PI 3.1415926535f

// Il2Cpp Structures
struct PlayerScript {
    char pad_00[0xBC];
    float walkSpeed;    // 0xBC
    char pad_C0[0x38];  // gap to 0xF8
    float rotationY;    // 0xF8
    float rotationX;    // 0xFC
    float rotationZ;    // 0x100
    char pad_104[0x8]; 
    void* cameraComp;   // 0x108 (Camera)
    void* fpsCam;       // 0x110 (FPSCamera)
    char pad_118[0x158];
    int health;         // 0x278 (Simplified ObscuredInt)
    char pad_27C[0x8];
    int armor;          // 0x284 (Simplified ObscuredInt)
    char pad_288[0x8];
    int team;           // 0x290
};

struct Il2CppArray {
    void* klass;
    void* monitor;
    void* bounds;
    int32_t max_length;
    PlayerScript* vector[0];
};

typedef Il2CppArray* (*tGetPlayerList)();

// Global Variables
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
HWND g_hWnd = nullptr;

typedef HRESULT(__stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Present oPresent = nullptr;

bool g_ShowMenu = true;
bool g_Aimbot = true;
bool g_Esp = true;
float g_WalkSpeed = 5.0f;
float g_Smooth = 3.0f;

PlayerScript* GetLocalPlayer() {
    uintptr_t gameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
    // Usually, the first player in certain lists or a static
    // For now, we'll try to find a player with islocal = true if needed
    // But most cheats use the get_FPSCamera to find the active camera/player context
    return nullptr; 
}

void AimAt(PlayerScript* local, Vector3 target) {
    if (!local) return;

    // Based on camPos or transform position
    Vector3 localPos = Memory::Read<Vector3>((uintptr_t)local + 0x2C0); // _camPos
    Angle targetAngle = CalculateAngle(localPos, target);

    // Write to rotation fields
    if (g_Smooth > 1.0f) {
        float currentX = local->rotationX;
        float currentY = local->rotationY;
        
        local->rotationX += (targetAngle.pitch - currentX) / g_Smooth;
        local->rotationY += (targetAngle.yaw - currentY) / g_Smooth;
    } else {
        local->rotationX = targetAngle.pitch;
        local->rotationY = targetAngle.yaw;
    }
}

WNDPROC oWndProc;
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (g_ShowMenu && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    if (!g_pd3dDevice) {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3dDevice))) {
            g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            g_hWnd = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(g_hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            ImGui_ImplWin32_Init(g_hWnd);
            ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
        }
        else return oPresent(pSwapChain, SyncInterval, Flags);
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (GetAsyncKeyState(VK_INSERT) & 1) g_ShowMenu = !g_ShowMenu;

    if (g_ShowMenu) {
        ImGui::Begin("Kuboom Cheat", &g_ShowMenu);
        ImGui::Checkbox("Aimbot", &g_Aimbot);
        ImGui::SliderFloat("Smoothness", &g_Smooth, 1.0f, 10.0f);
        ImGui::Checkbox("ESP", &g_Esp);
        ImGui::SliderFloat("Walk Speed", &g_WalkSpeed, 1.0f, 20.0f);
        ImGui::End();
    }

    if (g_Esp) {
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 30), IM_COL32(255, 255, 0, 255), "ESP: ACTIVE (HOLD RBUTTON TO AIM)");
        
        uintptr_t gameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
        auto getOtherPlayers = (tGetPlayerList)(gameAssembly + Offsets::otherPlayers);
        typedef bool (*tIsLocal)(void*);
        auto isLocalFn = (tIsLocal)(gameAssembly + 0x63AAE0);

        Il2CppArray* list = getOtherPlayers();
        if (list && list->max_length > 0) {
            PlayerScript* localPlayer = nullptr;
            for (int i = 0; i < list->max_length; i++) {
                if (isLocalFn(list->vector[i])) {
                    localPlayer = list->vector[i];
                    break;
                }
            }

            for (int i = 0; i < list->max_length; i++) {
                PlayerScript* player = list->vector[i];
                if (!player || player == localPlayer) continue;

                // Simple Visual Indicator (Until WorldToScreen is fully mapped)
                ImU32 color = (localPlayer && player->team == localPlayer->team) ? 
                              IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255);
                
                // For now, we print health/team info in the corner as a HUD
                char buf[64];
                sprintf_s(buf, "Player %d | Team: %d | HP: %d", i, player->team, player->health);
                ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 60 + i * 20), color, buf);
            }
        }
    }

    ImGui::Render();
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
}

void CheatThread(HMODULE hModule) {
    uintptr_t gameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
    
    // Simple hook finding (using a dummy swapchain)
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = GetForegroundWindow();
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    ID3D11Device* pDevice = nullptr;
    ID3D11DeviceContext* pContext = nullptr;
    IDXGISwapChain* pSwapChain = nullptr;

    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
    if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &sd, &pSwapChain, &pDevice, NULL, &pContext))) {
        return;
    }

    void** pVTable = *reinterpret_cast<void***>(pSwapChain);
    oPresent = (Present)pVTable[8]; // Present is index 8 in IDXGISwapChain

    pDevice->Release();
    pContext->Release();
    pSwapChain->Release();

    if (MH_Initialize() == MH_OK) {
        MH_CreateHook(oPresent, hkPresent, (LPVOID*)&oPresent);
        MH_EnableHook(oPresent);
    }

    typedef bool (*tIsLocal)(void*);
    auto isLocalFn = (tIsLocal)(gameAssembly + 0x63AAE0); // islocal getter RVA

    while (!(GetAsyncKeyState(VK_END) & 1)) {
        auto getOtherPlayers = (tGetPlayerList)(gameAssembly + Offsets::otherPlayers);
        Il2CppArray* list = getOtherPlayers();
        
        if (list && list->max_length > 0) {
            PlayerScript* localPlayer = nullptr;

            // 1. Find local player first to know team/pos
            for (int i = 0; i < list->max_length; i++) {
                if (isLocalFn(list->vector[i])) {
                    localPlayer = list->vector[i];
                    break;
                }
            }

            if (localPlayer) {
                // Application of Speedhack
                if (g_WalkSpeed > 5.0f) localPlayer->walkSpeed = g_WalkSpeed;

                // 2. Aimbot Logic
                if (g_Aimbot && GetAsyncKeyState(VK_RBUTTON)) {
                    float closestDist = 9999.0f;
                    Vector3 bestTarget = {0,0,0};
                    bool found = false;

                    for (int i = 0; i < list->max_length; i++) {
                        PlayerScript* enemy = list->vector[i];
                        if (!enemy || enemy == localPlayer) continue;

                        // Team check
                        if (enemy->team == localPlayer->team) continue;

                        // Health check (if health is 0, skip)
                        if (enemy->health <= 0) continue;

                        Vector3 localPos = Memory::Read<Vector3>((uintptr_t)localPlayer + 0x2C0);
                        Vector3 enemyPos = Memory::Read<Vector3>((uintptr_t)enemy + 0x2C0); // Using _camPos/Pos

                        float dist = localPos.Distance(enemyPos);
                        if (dist < closestDist) {
                            closestDist = dist;
                            bestTarget = enemyPos;
                            found = true;
                        }
                    }

                    if (found) AimAt(localPlayer, bestTarget);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    MH_DisableHook(oPresent);
    MH_Uninitialize();
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)CheatThread, hModule, 0, nullptr);
    }
    return TRUE;
}
