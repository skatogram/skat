#pragma warning(disable : 4530)
#define NOMINMAX
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
//#include <MinHook.h>
#include "sound.h"
#include "auth.h"
#include "core/sdk/utils/xorstr.hpp"
#include <discord/main/discord_rpc_init.h>
#include <Windows.h>
#include <stdint.h>
#include <psapi.h>
#include <d3d11.h>
#include <string>
#include <codecvt>
#include <locale>
#include <cstdint>
#include <algorithm>
#include <random>
#pragma comment(lib, "urlmon.lib")
#include <iostream>
#include <iomanip>
#include <emmintrin.h>
#include <comdef.h>
#include <filesystem>
#include <vector>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <signal.h>
#include <sstream>
#include <lmcons.h>
#include <thread>
#include <chrono>
#include <map>
#include <shlobj.h>
#include "Imgui/imgui.h"
#include "Imgui/freetype/imgui_freetype.h"
#include "Imgui/imgui_impl_win32.h"
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/colors.h"
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Winmm.lib")
#include <dwmapi.h>
#include <array>
#include "winternl.h"
#include "time.h"
#include <cstringt.h>
#include <atlstr.h>
#include "offsets.h"

#pragma warning ( disable : 4172 )

float projectile_speed = 0.0f;

bool timer_initialized = false;

float timeSinceStartup = 0;
float timeFrequency = 0;
HANDLE mainthread = NULL;
HANDLE preloadthread = NULL;
HMODULE dllmain;
float VFlyhack = 0.0f;
float HFlyhack = 0.0f;
float VMaxFlyhack = 0.0f;
float HMaxFlyhack = 0.0f;
float flyhackPauseTime;
float flyhackDistanceVertical = 110.f;
float flyhackDistanceHorizontal = 110.f;
float real_vertical = 0.0f;

bool isreloading = false;
bool just_shot = false;
float fixed_time_last_shot = 0.0f;
bool did_reload = false;
float time_since_last_shot = 0.0f;

float get_time_since_startup()
{
	LARGE_INTEGER PerformanceCount;
	LARGE_INTEGER FrequencyCount;

	if (!timer_initialized)
	{
		timer_initialized = true;

		PerformanceCount.QuadPart = 0;
		QueryPerformanceCounter(&PerformanceCount);

		FrequencyCount.QuadPart = 0;
		QueryPerformanceFrequency(&FrequencyCount);

		timeFrequency = float(FrequencyCount.QuadPart);

		timeSinceStartup = float(PerformanceCount.QuadPart);
	}

	PerformanceCount.QuadPart = 0;
	QueryPerformanceCounter(&PerformanceCount);

	return float(PerformanceCount.QuadPart - timeSinceStartup) / timeFrequency;
}

#include "core/sdk/utils/string.hpp"
#include "core/sdk/utils/xorf.hpp"

using namespace KeyAuth;
std::string name = xorstr_("InvisDLC");
std::string ownerid = xorstr_("baknHf4R5Q");
std::string secret = xorstr_("8e208e382b88129e66f36ccc5b8dcd85e645ec5add41447330fc146c4d534d21");
std::string version = xorstr_("1.5");
std::string url = xorstr_("https://panel.bluedream.space/api/1.2/");
api bluedream_api(name, ownerid, secret, version, url);

ID3D11ShaderResourceView* general_texture = nullptr;
ID3D11ShaderResourceView* projectile_texture = nullptr;
ID3D11ShaderResourceView* settings_texture = nullptr;
ID3D11ShaderResourceView* players_texture = nullptr;
ID3D11ShaderResourceView* world_texture = nullptr;
ID3D11ShaderResourceView* eye_texture = nullptr;
ID3D11ShaderResourceView* movement_texture = nullptr;
ID3D11ShaderResourceView* exploits_texture = nullptr;
ID3D11ShaderResourceView* info_texture = nullptr;
inline ImDrawList* DrawList;
ImFont* arrow = nullptr;

#include "core/sdk/vector.hpp"
#include "settings.hpp"
#include "core/drawing/Fonts.hpp"
#include "core/sdk/Config.hpp"

#include "core/drawing/Menu/menu.hpp"


#include "core/stdafx.hpp"
#include "core/drawing/render.hpp"
#include "core/sdk/utils/hookengine.hpp"
#include "core/sdk/mem.hpp"
#include "core/sdk/utils/crc32.hpp"
#include "core/sdk/il2cpp/wrapper.hpp"
#include "core/sdk/il2cpp/dissector.hpp"
#include "core/sdk/structs.hpp"
#include "core/sdk/utils/math.hpp"
#include "core/sdk/game.hpp"
#include "core/drawing/Menu/HitMarker.h"
#include "core/main/entities.hpp"
#include "core/drawing/d3d.hpp"
#include "core/main/serverchecker.h"
#include "core/main/other.hpp"
#include "core/main/hooks.hpp"
#pragma warning(disable : 4996)
#include <keyauth/jsonauth.hpp>
#include <wininet.h>
int mainkraft() {
	HINTERNET hInternet, hConnect;
	DWORD bytesRead;
	char buffer[1024];
	std::string url = "http://185.188.183.174/invis_new.txt";
	std::vector<char> content;
	hInternet = InternetOpen("HTTP GET Example", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);

	while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
		for (DWORD i = 0; i < bytesRead; ++i) {
			content.push_back(buffer[i]);
		}
	}

	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);
	std::string contentString(content.begin(), content.end());
	steamidis = contentString;
}



void downloadbundles() {
	//URLDownloadToFileA(nullptr, xorstr_("https://cdn.discordapp.com/attachments/1113947360624640121/1156860800233914458/world.assets"), (xorstr_("world.assets")), 0, nullptr);
	//PlaySoundA((LPCSTR)done123, NULL, SND_MEMORY | SND_ASYNC);
}
void init_backend_web( ) {
	//name.clear( ); ownerid.clear( ); secret.clear( ); version.clear( ); url.clear( );
	//bluedream_api.init_keyauth( );
	/*if ( !bluedream_api.data.success ) {
		bluedream_api.log(xorstr_("[IN GAME] init error"));
		__fastfail(-1);
		exit(-1);
	}*/

	/*HKEY hKey;
	std::string token, pass;
	if ( RegOpenKeyExA(HKEY_CURRENT_USER, xorstr_("Software\\osu!\\conf"), 0, KEY_READ, &hKey) == ERROR_SUCCESS ) {
		char buffer[256], buffer2[256];
		DWORD bufferSize = sizeof(buffer), bufferSize2 = sizeof(buffer2);
		if ( RegQueryValueExA(hKey, xorstr_("pass"), nullptr, nullptr, ( LPBYTE ) buffer, &bufferSize) == ERROR_SUCCESS &&
			RegQueryValueExA(hKey, xorstr_("name"), nullptr, nullptr, ( LPBYTE ) buffer2, &bufferSize2) == ERROR_SUCCESS ) {
			pass = std::string(buffer);
			name = std::string(buffer2);

			bluedream_api.login(name, pass);
			if ( bluedream_api.data.success ) {
				userauth = name;
				pass.clear( ); name.clear( );
				bluedream_api.fetchonline( );
				bluedream_api.fetchstats( );

			}
			else {

				bluedream_api.log(xorstr_("[IN GAME] login error"));
				__fastfail(-1);
				exit(-1);
			}
		}
		else {
			bluedream_api.log(xorstr_("[IN GAME] login error2"));
			__fastfail(-1);
			exit(-1);
		}

		RegCloseKey(hKey);
	}
	else {
		__fastfail(-1);
		exit(-1);
	}*/

}
DWORD _stdcall NOmain_thread(LPVOID param) {

	//downloadbundles();
	get_time_since_startup();
	initialize_cheat();
	do_hooks();
	d3d::init();
	config::create_config_folder();

	return 1;
}

bool DllMain(HMODULE hMod, uint32_t call_reason, LPVOID reserved) {
	
	if (call_reason == DLL_PROCESS_ATTACH )
	{
		dllmain = hMod;
		//preloadthread = CreateThread(NULL, NULL, preload_thread, NULL, 0x40, NULL);
		preloadthread = CreateThread(NULL, NULL, NOmain_thread, NULL, 0x40, NULL);
	}
	return true;
}