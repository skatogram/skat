#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <iostream>
#include <thread>
#include <vector>

// ImGui Headers
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_internal.h"
#include "MinHook.h"

// Project Headers
#include "offsets.h"
#include "unity.h"

#define PI 3.1415926535f

// --- Global Variables ---
ID3D11Device* g_Device = nullptr;
ID3D11DeviceContext* g_Context = nullptr;
ID3D11RenderTargetView* g_RTV = nullptr;
HWND g_Window = nullptr;
WNDPROC oWndProc = nullptr;

typedef HRESULT(__stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Present oPresent = nullptr;

// --- Cheat Settings (The "Fat" Part) ---
bool g_MenuOpen = true;
int g_SelectedTab = 0;

namespace Settings {
    bool Aimbot = true;
    float Smooth = 5.0f;
    float FOV = 90.0f;
    bool DrawFOV = true;

    bool EspBoxes = true;
    bool EspNames = true;
    bool EspHealth = true;

    float SpeedMult = 1.0f;
    bool Bunnyhop = false;
}

// --- Skeet Logic ---
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void SetupSkeetStyle() {
    auto& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.ChildRounding = 0.0f;
    style.PopupRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.WindowBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImColor(12, 12, 12, 255);
    colors[ImGuiCol_ChildBg] = ImColor(15, 15, 15, 255);
    colors[ImGuiCol_PopupBg] = ImColor(15, 15, 15, 255);
    colors[ImGuiCol_Border] = ImColor(40, 40, 40, 255);
    colors[ImGuiCol_FrameBg] = ImColor(20, 20, 20, 255);
    colors[ImGuiCol_FrameBgHovered] = ImColor(25, 25, 25, 255);
    colors[ImGuiCol_FrameBgActive] = ImColor(30, 30, 30, 255);
    colors[ImGuiCol_TitleBg] = ImColor(12, 12, 12, 255);
    colors[ImGuiCol_TitleBgActive] = ImColor(12, 12, 12, 255);
    colors[ImGuiCol_CheckMark] = ImColor(161, 255, 100, 255); // Skeet Green
    colors[ImGuiCol_SliderGrab] = ImColor(161, 255, 100, 255);
    colors[ImGuiCol_Button] = ImColor(20, 20, 20, 255);
    colors[ImGuiCol_ButtonHovered] = ImColor(25, 25, 25, 255);
    colors[ImGuiCol_ButtonActive] = ImColor(30, 30, 30, 255);
    colors[ImGuiCol_Header] = ImColor(161, 255, 100, 150);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_KEYDOWN) {
        if (wParam == VK_INSERT) {
            g_MenuOpen = !g_MenuOpen;
            return 0;
        }
    }

    if (g_MenuOpen && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

// --- Menu Rendering ---
void RenderMenu() {
    ImGui::SetNextWindowSize(ImVec2(600, 450));
    ImGui::Begin("Gamesense", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    
    ImDrawList* draw = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetWindowPos();

    // Skeet Gradient Line
    draw->AddRectFilledMultiColor(p, ImVec2(p.x + 600, p.y + 2), IM_COL32(50, 150, 255, 255), IM_COL32(150, 50, 255, 255), IM_COL32(150, 50, 255, 255), IM_COL32(50, 150, 255, 255));

    // Left Bar Tabs
    ImGui::BeginChild("Tabs", ImVec2(120, 0), true);
    const char* tabNames[] = { "LEGIT", "VISUALS", "MISC", "SKINS", "CONFIGS" };
    for (int i = 0; i < 5; i++) {
        if (ImGui::Selectable(tabNames[i], g_SelectedTab == i, 0, ImVec2(0, 40))) {
            g_SelectedTab = i;
        }
    }
    ImGui::EndChild();

    ImGui::SameLine();

    // Content Area
    ImGui::BeginChild("MainContent", ImVec2(0, 0), true);
    if (g_SelectedTab == 0) { // Legit
        ImGui::Text("Aimbot Configuration");
        ImGui::Separator();
        ImGui::Checkbox("Enabled", &Settings::Aimbot);
        ImGui::SliderFloat("Smoothness", &Settings::Smooth, 1.0f, 30.0f);
        ImGui::SliderFloat("Field of View", &Settings::FOV, 1.0f, 180.0f);
        ImGui::Checkbox("Draw FOV Circle", &Settings::DrawFOV);
    } 
    else if (g_SelectedTab == 1) { // Visuals
        ImGui::Text("ESP Options");
        ImGui::Separator();
        ImGui::Checkbox("Box ESP", &Settings::EspBoxes);
        ImGui::Checkbox("Name ESP", &Settings::EspNames);
        ImGui::Checkbox("Health Bar", &Settings::EspHealth);
    }
    else if (g_SelectedTab == 2) { // Misc
        ImGui::Text("Movement & Exploits");
        ImGui::Separator();
        ImGui::SliderFloat("Speed Hack", &Settings::SpeedMult, 1.0f, 10.0f);
        ImGui::Checkbox("Bhop", &Settings::Bunnyhop);
    }
    ImGui::EndChild();

    ImGui::End();
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
            SetupSkeetStyle();
            ImGui_ImplWin32_Init(g_Window);
            ImGui_ImplDX11_Init(g_Device, g_Context);
        }
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Watermark
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 10), IM_COL32(255, 255, 255, 200), "skatogram-internal | stable | msvc");

    if (g_MenuOpen) {
        RenderMenu();
    }

    ImGui::Render();
    g_Context->OMSetRenderTargets(1, &g_RTV, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
}

// --- Main Init ---
void MainThread(HMODULE hModule) {
    // Wait for the game to initialize
    while (!GetModuleHandleA("GameAssembly.dll")) Sleep(100);

    // SwapChain Hooking
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

    while (!(GetAsyncKeyState(VK_END) & 1)) Sleep(100);

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
