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
struct PhotonPlayer {
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

typedef Il2CppArray* (*tGetPlayerList)();

// Global Variables
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
HWND g_hWnd = nullptr;

typedef HRESULT(__stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Present oPresent = nullptr;

bool g_ShowMenu = true;
bool g_Aimbot = false;
bool g_Esp = false;
float g_WalkSpeed = 5.0f;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
        ImGui::Checkbox("ESP", &g_Esp);
        ImGui::SliderFloat("Walk Speed", &g_WalkSpeed, 1.0f, 20.0f);
        ImGui::End();
    }

    if (g_Esp) {
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 10), IM_COL32(255, 255, 0, 255), "ESP: ACTIVE (RIGHT CLICK TO AIM)");
        
        uintptr_t gameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
        auto getOtherPlayers = (tGetPlayerList)(gameAssembly + Offsets::otherPlayers);
        
        Il2CppArray* list = getOtherPlayers();
        if (list && list->max_length > 0) {
            for (int i = 0; i < list->max_length; i++) {
                PhotonPlayer* player = list->vector[i];
                if (!player) continue;

                // 1. Get Position (Usually via Transform)
                // Vector3 pos = GetPlayerPos(player); 
                
                // 2. World To Screen
                // Vector2 screen;
                // if (WorldToScreen(pos, screen, viewMatrix, width, height)) {
                //      ImGui::GetBackgroundDrawList()->AddRect(ImVec2(screen.x - 10, screen.y - 10), ImVec2(screen.x + 10, screen.y + 10), IM_COL32(255, 0, 0, 255));
                // }
                
                // Example modification (Speed)
                if (g_WalkSpeed > 5.0f) {
                    player->walkSpeed = g_WalkSpeed;
                }
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

    while (!(GetAsyncKeyState(VK_END) & 1)) {
        // Core hack logic (Aimbot/Speed)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
