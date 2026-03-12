#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
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

// Forward declaration for ImGui Win32 handler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// --- Simple Math for Aimbot ---
struct Angle { float yaw, pitch; };
Angle CalculateAngle(Vector3 local, Vector3 target) {
    Vector3 delta = { target.x - local.x, target.y - local.y, target.z - local.z };
    float hypers = sqrtf(delta.x * delta.x + delta.z * delta.z);
    return {
        atan2f(delta.z, delta.x) * (180.0f / PI),
        atan2f(-delta.y, hypers) * (180.0f / PI)
    };
}

// --- Il2Cpp Structures ---
struct PlayerScript {
    char pad_00[0xBC];
    float walkSpeed;
    char pad_C0[0x38];
    float rotationY;
    float rotationX;
    float rotationZ;
    char pad_104[0x8]; 
    void* cameraComp;
    void* fpsCam;
    char pad_118[0x158];
    int health;
    char pad_27C[0x8];
    int armor;
    char pad_288[0x8];
    int team;
};

struct Il2CppArray {
    void* klass;
    void* monitor;
    void* bounds;
    int32_t max_length;
    PlayerScript* vector[0];
};

typedef Il2CppArray* (*tGetPlayerList)();

// --- Global Pointers ---
ID3D11Device* g_Device = nullptr;
ID3D11DeviceContext* g_Context = nullptr;
ID3D11RenderTargetView* g_RTV = nullptr;
HWND g_Window = nullptr;
WNDPROC oWndProc = nullptr;

typedef HRESULT(__stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Present oPresent = nullptr;

// --- Cheat States ---
bool g_MenuOpen = true;
bool g_Aimbot = true;
bool g_Esp = true;
float g_WalkSpeed = 5.0f;
float g_Smooth = 3.0f;
int g_SelectedTab = 0;

void ApplySkatStyle() {
    auto& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.ChildRounding = 0.0f;
    style.PopupRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.60f, 0.75f, 0.15f, 1.00f); // Skeet Green
    colors[ImGuiCol_SliderGrab] = ImVec4(0.60f, 0.75f, 0.15f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
}

void AimAt(PlayerScript* local, Vector3 target) {
    if (!local) return;
    Vector3 localPos = Memory::Read<Vector3>((uintptr_t)local + 0x2C0);
    Angle targetAngle = CalculateAngle(localPos, target);

    if (g_Smooth > 1.0f) {
        local->rotationX += (targetAngle.pitch - local->rotationX) / g_Smooth;
        local->rotationY += (targetAngle.yaw - local->rotationY) / g_Smooth;
    } else {
        local->rotationX = targetAngle.pitch;
        local->rotationY = targetAngle.yaw;
    }
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_KEYDOWN && wParam == VK_INSERT) {
        g_MenuOpen = !g_MenuOpen;
    }

    if (g_MenuOpen && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    if (!g_Device) {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_Device))) {
            g_Device->GetImmediateContext(&g_Context);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            g_Window = sd.OutputWindow;
            
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            g_Device->CreateRenderTargetView(pBackBuffer, NULL, &g_RTV);
            pBackBuffer->Release();

            oWndProc = (WNDPROC)SetWindowLongPtr(g_Window, GWLP_WNDPROC, (LONG_PTR)WndProc);

            ImGui::CreateContext();
            ApplySkatStyle();
            ImGui_ImplWin32_Init(g_Window);
            ImGui_ImplDX11_Init(g_Device, g_Context);
        }
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (g_Esp) {
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(10.0f, 10.0f), IM_COL32(255, 255, 255, 255), "Skatogram Internal | Kuboom");
    }

    if (g_MenuOpen) {
        ImGui::SetNextWindowSize(ImVec2(550, 420));
        ImGui::Begin("Skatogram Internal", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        
        ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + 550, ImGui::GetWindowPos().y + 2), IM_COL32(50, 150, 255, 255), IM_COL32(150, 50, 255, 255), IM_COL32(150, 50, 255, 255), IM_COL32(50, 150, 255, 255));

        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, 140);
        
        const char* tabs[] = { "Aimbot", "Visuals", "Misc", "Settings" };
        for (int i = 0; i < 4; i++) {
            if (ImGui::Selectable(tabs[i], g_SelectedTab == i, 0, ImVec2(0, 35))) g_SelectedTab = i;
        }
        
        ImGui::NextColumn();
        ImGui::BeginChild("Content", ImVec2(0, 0), true);
        if (g_SelectedTab == 0) {
            ImGui::Checkbox("Master Aimbot", &g_Aimbot);
            ImGui::SliderFloat("Smoothness Factor", &g_Smooth, 1.0f, 30.0f);
        } else if (g_SelectedTab == 1) {
            ImGui::Checkbox("Enable ESP", &g_Esp);
        } else if (g_SelectedTab == 2) {
            ImGui::SliderFloat("Walk Speed Multiplier", &g_WalkSpeed, 1.0f, 100.0f);
        }
        ImGui::EndChild();
        ImGui::End();
    }

    ImGui::Render();
    g_Context->OMSetRenderTargets(1, &g_RTV, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
}

void MainThread(HMODULE hModule) {
    uintptr_t gameAssembly = 0;
    while (!(gameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll"))) Sleep(100);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = GetForegroundWindow();
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    ID3D11Device* pDevice = nullptr;
    IDXGISwapChain* pSwapChain = nullptr;
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

    if (SUCCEEDED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &sd, &pSwapChain, &pDevice, NULL, NULL))) {
        void** pVTable = *reinterpret_cast<void***>(pSwapChain);
        oPresent = (Present)pVTable[8];
        pDevice->Release();
        pSwapChain->Release();
    }

    if (MH_Initialize() == MH_OK) {
        MH_CreateHook(oPresent, hkPresent, (LPVOID*)&oPresent);
        MH_EnableHook(oPresent);
    }

    typedef bool (*tIsLocal)(void*);
    auto isLocalFn = (tIsLocal)(gameAssembly + 0x63AAE0);

    while (!(GetAsyncKeyState(VK_END) & 1)) {
        auto getOtherPlayers = (tGetPlayerList)(gameAssembly + Offsets::otherPlayers);
        Il2CppArray* list = getOtherPlayers();
        
        if (list && list->max_length > 0) {
            PlayerScript* localPlayer = nullptr;
            for (int i = 0; i < list->max_length; i++) {
                if (isLocalFn(list->vector[i])) {
                    localPlayer = list->vector[i];
                    break;
                }
            }

            if (localPlayer) {
                if (g_WalkSpeed > 5.0f) localPlayer->walkSpeed = g_WalkSpeed;

                if (g_Aimbot && GetAsyncKeyState(VK_RBUTTON)) {
                    float closestDist = 9999.0f;
                    Vector3 bestTarget = {0,0,0};
                    bool found = false;

                    for (int i = 0; i < list->max_length; i++) {
                        PlayerScript* enemy = list->vector[i];
                        if (!enemy || enemy == localPlayer || enemy->team == localPlayer->team || enemy->health <= 0) continue;

                        Vector3 localPos = Memory::Read<Vector3>((uintptr_t)localPlayer + 0x2C0);
                        Vector3 enemyPos = Memory::Read<Vector3>((uintptr_t)enemy + 0x2C0);

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
        Sleep(5);
    }

    MH_DisableHook(oPresent);
    MH_Uninitialize();
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0));
    }
    return TRUE;
}
