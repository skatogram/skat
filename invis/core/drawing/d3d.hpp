//Оксинем сын шлюшки
#include <d3d11.h>
#include <string>
#pragma comment(lib,"d3d11.lib")
bool menu_init = false;


#define COMPUTE_BUILD_YEAR \
    ( \
        (__DATE__[ 7] - '0') * 1000 + \
        (__DATE__[ 8] - '0') *  100 + \
        (__DATE__[ 9] - '0') *   10 + \
        (__DATE__[10] - '0') \
    )


#define COMPUTE_BUILD_DAY \
    ( \
        ((__DATE__[4] >= '0') ? (__DATE__[4] - '0') * 10 : 0) + \
        (__DATE__[5] - '0') \
    )


#define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
#define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
#define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
#define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
#define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')


#define COMPUTE_BUILD_MONTH \
    ( \
        (BUILD_MONTH_IS_JAN) ?  1 : \
        (BUILD_MONTH_IS_FEB) ?  2 : \
        (BUILD_MONTH_IS_MAR) ?  3 : \
        (BUILD_MONTH_IS_APR) ?  4 : \
        (BUILD_MONTH_IS_MAY) ?  5 : \
        (BUILD_MONTH_IS_JUN) ?  6 : \
        (BUILD_MONTH_IS_JUL) ?  7 : \
        (BUILD_MONTH_IS_AUG) ?  8 : \
        (BUILD_MONTH_IS_SEP) ?  9 : \
        (BUILD_MONTH_IS_OCT) ? 10 : \
        (BUILD_MONTH_IS_NOV) ? 11 : \
        (BUILD_MONTH_IS_DEC) ? 12 : \
         99 \
    )

#define COMPUTE_BUILD_HOUR ((__TIME__[0] - '0') * 10 + __TIME__[1] - '0')
#define COMPUTE_BUILD_MIN  ((__TIME__[3] - '0') * 10 + __TIME__[4] - '0')
#define COMPUTE_BUILD_SEC  ((__TIME__[6] - '0') * 10 + __TIME__[7] - '0')

//
#define BUILD_DATE_IS_BAD (__DATE__[0] == '?')

#define BUILD_YEAR  ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_YEAR)
#define BUILD_MONTH ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_MONTH)
#define BUILD_DAY   ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_DAY)

#define BUILD_TIME_IS_BAD (__TIME__[0] == '?')

#define BUILD_HOUR  ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_HOUR)
#define BUILD_MIN   ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_MIN)
#define BUILD_SEC   ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_SEC)

// this code is not stolen from stackoverflow \\
	
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace d3d {
	LRESULT WndProcHook(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	/*	static auto is_down = true;
		static auto is_clicked = false;
		auto g = IdaLovesMe::Gui_Ctx;
		if (uMsg == WM_MOUSEWHEEL) {
			if (g)
				g->MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +0.3f : -0.3f;
		}
		hWnd2 = hWnd;
		if (GetAsyncKeyState(VK_INSERT))
		{
			is_clicked = false;
			is_down = true;
		}
		else if (!GetAsyncKeyState(VK_INSERT) && is_down)
		{
			is_clicked = true;
			is_down = false;
		}
		else
		{
			is_clicked = false;
			is_down = false;
		}

		if (is_clicked)
		{
			MenuOpen = !CMenu::get()->is_menu_opened();
			CMenu::get()->set_menu_opened(!CMenu::get()->is_menu_opened());

		}

		auto pressed_buttons = false;
		auto pressed_menu_key = uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_MOUSEWHEEL;

		if (!pressed_menu_key && !CMenu::get()->SelectedItem)
			pressed_buttons = true;

		if (!pressed_buttons && CMenu::get()->is_menu_opened() && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		if (CMenu::get()->is_menu_opened() && (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_MOUSEMOVE))
			return false;

		return CallWindowProc(original_windowproc, hWnd, uMsg, wParam, lParam);*/
		//	g_KeyManager::HandleMessage(uMsg, wParam);


		if (menu::menuopen && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		static auto is_down = true;
		static auto is_clicked = false;
		if (GetAsyncKeyState(VK_INSERT))
		{
			is_clicked = false;
			is_down = true;
		}
		else if (!GetAsyncKeyState(VK_INSERT) && is_down)
		{
			is_clicked = true;
			is_down = false;
		}
		else
		{
			is_clicked = false;
			is_down = false;
		}

		if (is_clicked)
		{
			menu::menuopen = !menu::menuopen;
		}
		auto pressed_buttons = false;
		auto pressed_menu_key = uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_MOUSEWHEEL;

		if (!pressed_menu_key)
			pressed_buttons = true;
		if (!pressed_buttons && menu::menuopen && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		return CallWindowProc(original_windowproc, hWnd, uMsg, wParam, lParam);
	}
	float BOG_TO_GRD(float BOG) {
		return (180 / M_PI) * BOG;
	}

	float GRD_TO_BOG(float GRD) {
		return (M_PI / 180) * GRD;
	}

	void FreeStringsInModule(HMODULE hModule) {
		HMODULE hKernel32 = GetModuleHandle("Kernel32");
		if ( hKernel32 != NULL ) {
			// Получаем адрес функции FreeLibrary
			FARPROC pfnFreeLibrary = GetProcAddress(hKernel32, "FreeLibrary");
			if ( pfnFreeLibrary != NULL ) {
				// Вызываем FreeLibrary для выгрузки DLL модуля из памяти
				( ( void(__stdcall*)( HMODULE ) )pfnFreeLibrary )( hModule );
			}
		}
	}


	HRESULT present_hook(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
		static Vector2 text_size = Vector2(0, 0);
		if (!device) {
			swapChain->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device));
			device->GetImmediateContext(&immediate_context);
			ID3D11Texture2D* renderTarget = nullptr;
			swapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<PVOID*>(&renderTarget));
			device->CreateRenderTargetView(renderTarget, nullptr, &render_target_view);
			renderTarget->Release( );
			ImGui::CreateContext();

			ImGui_ImplWin32_Init(game_window);
			ImGui_ImplDX11_Init(device, immediate_context);
			ImGuiStyle& style = ImGui::GetStyle();
			ImGuiIO& io = ImGui::GetIO();

			arrow = io.Fonts->AddFontFromMemoryTTF(arrow_binary, sizeof(arrow_binary), 10.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

			D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };
			if (general_texture == nullptr)D3DX11CreateShaderResourceViewFromMemory(device, general_binary, sizeof(general_binary), &info, pump, &general_texture, 0);
			if (projectile_texture == nullptr)D3DX11CreateShaderResourceViewFromMemory(device, projectile_binary, sizeof(projectile_binary), &info, pump, &projectile_texture, 0);
			if (settings_texture == nullptr)D3DX11CreateShaderResourceViewFromMemory(device, settings_binary, sizeof(settings_binary), &info, pump, &settings_texture, 0);
			if (players_texture == nullptr)D3DX11CreateShaderResourceViewFromMemory(device, players_binary, sizeof(players_binary), &info, pump, &players_texture, 0);
			if (world_texture == nullptr)D3DX11CreateShaderResourceViewFromMemory(device, world_binary, sizeof(world_binary), &info, pump, &world_texture, 0);
			if (eye_texture == nullptr)D3DX11CreateShaderResourceViewFromMemory(device, eye_binary, sizeof(eye_binary), &info, pump, &eye_texture, 0);
			if (movement_texture == nullptr)D3DX11CreateShaderResourceViewFromMemory(device, movement_binary, sizeof(movement_binary), &info, pump, &movement_texture, 0);
			if (exploits_texture == nullptr)D3DX11CreateShaderResourceViewFromMemory(device, exploits_binary, sizeof(exploits_binary), &info, pump, &exploits_texture, 0);
			if (info_texture == nullptr)D3DX11CreateShaderResourceViewFromMemory(device, info_binary, sizeof(info_binary), &info, pump, &info_texture, 0);

			//if (DefaultFonts == nullptr) DefaultFonts = io.Fonts->AddFontFromMemoryTTF(TopFontff, sizeof(TopFontff), 13.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
			//if (SmallDefaultFonts == nullptr) SmallDefaultFonts = io.Fonts->AddFontFromMemoryTTF(TopFontff, sizeof(TopFontff), 13.f * 0.85, NULL, io.Fonts->GetGlyphRangesCyrillic());
			//if (BigDefaultFonts == nullptr) BigDefaultFonts = io.Fonts->AddFontFromMemoryTTF(TopFontff, sizeof(TopFontff), 13.f * 1.60, NULL, io.Fonts->GetGlyphRangesCyrillic());
			if ( DefaultFonts == nullptr ) DefaultFonts = io.Fonts->AddFontFromMemoryTTF(TopFontff, sizeof(TopFontff), 13.f, NULL, io.Fonts->GetGlyphRangesCyrillic( ));
			if ( DefaultFontsEsp == nullptr ) DefaultFontsEsp = io.Fonts->AddFontFromMemoryTTF(TopFontff, sizeof(TopFontff), 12.f, NULL, io.Fonts->GetGlyphRangesCyrillic( ));
			if ( SmallDefaultFonts == nullptr ) SmallDefaultFonts = io.Fonts->AddFontFromMemoryTTF(TopFontff, sizeof(TopFontff), 13.f * 0.85, NULL, io.Fonts->GetGlyphRangesCyrillic( ));
			if ( BigDefaultFonts == nullptr ) BigDefaultFonts = io.Fonts->AddFontFromMemoryTTF(TopFontff, sizeof(TopFontff), 13.f * 1.60, NULL, io.Fonts->GetGlyphRangesCyrillic( ));

		}
		immediate_context->OMSetRenderTargets(1, &render_target_view, nullptr);
		immediate_context->RSGetViewports(&vps, &viewport);
		screen_size = { viewport.Width, viewport.Height };
		screen_center = { viewport.Width / 2.0f, viewport.Height / 2.0f };

		
		if ( !menu::unload ) {
			ImGui_ImplDX11_NewFrame( );
			ImGui_ImplWin32_NewFrame( );
			ImGui::NewFrame( );
			DrawList = ImGui::GetBackgroundDrawList( );
			g_Render->BeginScene( );
			g_Render->EndScene( );
			if ( menu::menuopen ) MainMenu( );

			
			ImGui::Render( );
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData( ));
		}
		else {
			static bool once = false;
			if (!once) {
				g_Discord->Shutdown();
				funcs::localplayer::fov = 90;
				if(LocalPlayer::Entity())
					LocalPlayer::Entity()->playerFlags() &= ~PlayerFlags::IsAdmin;
				MH_DisableHook(MH_ALL_HOOKS);
				TerminateThread(mainthread, -1);
				TerminateThread(preloadthread, -1);
				CloseHandle(mainthread);
				CloseHandle(preloadthread);
				//FreeStringsInModule(dllmain);
				//FreeLibrary(dllmain);
				once = true;
			}
		}

		return present_original(swapChain, syncInterval, flags);
	}

	HRESULT resize_hook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
		//Renderer::reset_canvas( );

		if (render_target_view)
			render_target_view->Release( );

		if (immediate_context)
			immediate_context->Release( );

		if (device)
			device->Release( );

		device = nullptr;
		return resize_original(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
	}

	bool init() {
		while (!game_window)
		{
			EnumWindows([](HWND hWnd, LPARAM lParam) -> BOOL {
				DWORD pid = 0;
				GetWindowThreadProcessId(hWnd, &pid);
				if (pid == GetCurrentProcessId()) {
					*reinterpret_cast<HWND*>(lParam) = hWnd;
					return FALSE;
				}

				return TRUE;
				}, reinterpret_cast<LPARAM>(&game_window));
		}

		unity_player = (uintptr_t)GetModuleHandleA(xorstr_("UnityPlayer.dll"));
		game_assembly = (uintptr_t)GetModuleHandleA(xorstr_("GameAssembly.dll"));
		//discord_hook = (uintptr_t)GetModuleHandleA(xorstr_("DiscordHook64.dll"));

		auto addr = mem::find_pattern(unity_player, (PBYTE)"\x48\x8B\x05\x00\x00\x00\x00\x48\x85\xC0\x74\x08\x48\x8B\x80\x00\x00\x00\x00", xorstr_("xxx????xxxxxxxx????"));


		if (!addr)
			return false;

		/*auto swapchain = reinterpret_cast<IDXGISwapChain * (__fastcall*)()>(unity_player + 0x10AB520)();*/
		auto swapchain = reinterpret_cast<IDXGISwapChain * (__fastcall*)()>(addr)();

		if (swapchain) {
			auto table = *reinterpret_cast<PVOID**>(swapchain);
			original_windowproc = (WNDPROC)SetWindowLongPtrW(game_window, GWLP_WNDPROC, (LONG_PTR)WndProcHook);

			/*hookengine::hook((void*)(*(uintptr_t*)(discord_hook + 0x00E9090)), (void**)&present_original, present_hook);*/
			hookengine::hook(( void* )table[8], ( void** ) &present_original, present_hook);
			hookengine::hook((void*)table[13], (void**)&resize_original, resize_hook);
			//hookengine::hook((void*)(discord_hook + 0x00179B0), (void**)&resize_original, resize_hook);

			return true;
		}
		return false;
	}

}
void ImGuiRendering::BeginScene()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::Begin("##Backbuffer", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

	ImGui::SetWindowPos(ImVec2(0, 0), 0);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), 0);

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->PushClipRectFullScreen();


	if (menu::cheat_init)
		entities::loop();

	if (funcs::psilent::drawfov)
		g_Render->DrawCircle({ screen_center.x,screen_center.y }, funcs::psilent::fov, 1.f, ImColor(funcs::psilent::fovcolor[0], funcs::psilent::fovcolor[1], funcs::psilent::fovcolor[2]));

}

void ImGuiRendering::EndScene()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->PopClipRect();

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
}

