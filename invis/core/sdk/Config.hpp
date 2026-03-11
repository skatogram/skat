#include <ShlObj.h>
#include <fstream>
#include "core/sdk/utils/json.hpp"
typedef Json::Value json;
#define xor_str_s(s) xorstr_(s)
#define xor_c_s(s) xorstr_(s)

#define xor_str(s) xorstr_(s)
#define xor_c(s) xorstr_(s)

#define xor_int(n) (n)

#define xor_wstr(s) xorstr_(s)
#define xor_wc(s) (s)
namespace config {
	void create_config_folder();
	void create(const std::string& config_name);
	void erase(const std::string& config_name);
	void load(const std::string& config_name);
}
constexpr int CFG_XOR_KEY = 0x5EF;

__forceinline void save_uint(json& j, std::string name, unsigned int v) {
	j[name] = v;
}

__forceinline void save_float(json& j, std::string name, float v) {
	j[name] = v;
}

__forceinline void save_int(json& j, std::string name, int v) {
	j[name] = v;
}

__forceinline void save_bool(json& j, std::string name, bool v) {
	j[name] = v;
}

__forceinline void save_string(json& j, std::string name, std::string v) {
	j[name] = v;
}

inline void load_uint(const json& j, std::string name, unsigned int& v) {
	if (j[name].empty())
		return;

	v = j[name].asUInt();
}

inline void load_int(const json& j, std::string name, int& v) {
	if (j[name].empty())
		return;

	v = j[name].asInt();
}

inline void load_bool(const json& j, std::string name, bool& v) {
	if (j[name].empty())
		return;

	v = j[name].asBool();
}

inline void load_float(const json& j, std::string name, float& v) {
	if (j[name].empty())
		return;

	v = j[name].asFloat();
}

inline void load_string(json& j, std::string name, char* v) {
	if (j[name].empty())
		return;

	std::string value = j[name].asString();
	std::strcpy(v, value.data());
}

inline bool is_dir(const TCHAR* dir) {
	uintptr_t flag = GetFileAttributesA(dir);
	if (flag == 0xFFFFFFFFUL) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
			return false;
	}
	if (!(flag & FILE_ATTRIBUTE_DIRECTORY))
		return false;
	return true;
}

__forceinline std::string file_to_string(const std::string& path) {
	std::ifstream input_file(path);
	if (!input_file.is_open())
		return "";
	return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

namespace config {

	std::string folder = xorstr_("");

	void create_config_folder() {
		static TCHAR path[MAX_PATH] = {};

		if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path)))
			folder = std::string(path) + xorstr_("\\invis.v2\\");

		if (!is_dir(folder.c_str()))
			CreateDirectoryA(folder.c_str(), NULL);

	}
	std::vector<std::string> config_list{};
	typedef void (*LPSEARCHFUNC)(LPCTSTR lpszFileName);
	BOOL search_files(LPCTSTR lpszFileName, LPSEARCHFUNC lpSearchFunc, BOOL bInnerFolders) {
		LPTSTR part;
		char tmp[MAX_PATH];
		char name[MAX_PATH];

		HANDLE hSearch = NULL;
		WIN32_FIND_DATA wfd;
		memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

		if (bInnerFolders) {
			if (GetFullPathNameA(lpszFileName, MAX_PATH, tmp, &part) == 0) return FALSE;
			strcpy(name, part);
			strcpy(part, xorstr_("*.*"));
			wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
			if (!((hSearch = FindFirstFileA(tmp, &wfd)) == INVALID_HANDLE_VALUE))
				do {
					if (!strncmp(wfd.cFileName, xorstr_("."), 1) || !strncmp(wfd.cFileName, xorstr_(".."), 2))
						continue;

					if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
						char next[MAX_PATH];
						if (GetFullPathNameA(lpszFileName, MAX_PATH, next, &part) == 0) return FALSE;
						strcpy(part, wfd.cFileName);
						strcat(next, xorstr_("\\"));
						strcat(next, name);

						search_files(next, lpSearchFunc, TRUE);
					}
				} while (FindNextFileA(hSearch, &wfd));
				FindClose(hSearch);
		}

		if ((hSearch = FindFirstFileA(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE)
			return TRUE;
		do
			if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				char file[MAX_PATH];
				if (GetFullPathNameA(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
				strcpy(part, wfd.cFileName);

				lpSearchFunc(wfd.cFileName);
			}
		while (FindNextFileA(hSearch, &wfd));
		FindClose(hSearch);
		return TRUE;
	}

	void read_configs(LPCTSTR lpszFileName) {
		config_list.push_back(lpszFileName);
	}

	void refresh_configs() {
		static TCHAR path[MAX_PATH];
		std::string folder, file;

		if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path))) {
			config_list.clear();
			std::string config_dir = std::string(path) + xorstr_("\\invis.v2\\*");
			search_files(config_dir.c_str(), read_configs, FALSE);
		}
	}

	std::vector < std::string > GetConfigList()
	{

		std::vector < std::string > m_ConfigList;
		for (const auto& p : std::filesystem::recursive_directory_iterator((folder)))
		{
			if (!std::filesystem::is_directory(p) /*&& p.path().extension().string() == (".inv")*/)
			{
				auto file = p.path().filename().string();
				m_ConfigList.push_back(file.substr(0, file.size()));
			}
		}

		return m_ConfigList;
	}

	void create(const std::string& config_name) {
		json json_obj = {};

		auto& rage = json_obj[xor_c("rage")]; {
			save_bool(rage, xor_c("Aim"), funcs::psilent::psilent);
			save_int(rage, xor_c("Enable key"), funcs::psilent::key);
			save_bool(rage, xor_c("locktarget"), funcs::psilent::locktarget);
			save_int(rage, xor_c("targetlock key"), funcs::psilent::targetlockkey);
			save_bool(rage, xor_c("manipulatorhitscan"), funcs::weapon::manipulatorhitscan);
			save_int(rage,xor_c("Aim Spot"), funcs::psilent::a_spot);
			save_bool(rage,xor_c("Draw Fov Circle"), funcs::psilent::drawfov);
			save_float(rage,xor_c("Fov"), funcs::psilent::fov);
			save_int(rage, xor_c("autoshottype"), funcs::psilent::autoshottype);
			save_bool(rage,xor_c("Target Name"), funcs::psilent::target_name);
			save_bool(rage,xor_c("FakeShots"), funcs::weapon::fakeshots);
			save_int(rage,xor_c("FakeShots Key"), funcs::weapon::fakeshotskey);
			save_bool(rage,xor_c("Target Sleepers"), funcs::psilent::sleepers);
			save_bool(rage,xor_c("Target Woundead"), funcs::psilent::woundead);
			save_bool(rage,xor_c("Target Friendly"), funcs::psilent::frendly);
			save_bool(rage,xor_c("Manipuator"), funcs::manipulator::manipulator);
			save_int(rage,xor_c("Manipuator Mode"), funcs::manipulator::desyncmode);
			save_int(rage,xor_c("Manipuator Key"), funcs::manipulator::manipulatorkey);
			save_bool(rage,xor_c("Desync indicator"), funcs::manipulator::desyncindicator);
			save_bool(rage, xor_c("target line"), funcs::psilent::target_line);
			save_float(rage,xor_c("Max Desync Time"), funcs::manipulator::maxdesyncfloat);
			save_bool(rage,xor_c("Recoil control"), funcs::weapon::recoilas);
			save_float(rage,xor_c("Recoil"), funcs::weapon::norecoil);
			save_float(rage,xor_c("Aim Cone"), funcs::weapon::spread);
			save_float(rage,xor_c("bullet speed"), funcs::weapon::bulletspeed);

			save_bool(rage, xor_c("Flowvelocity"), funcs::weapon::lowvelocity);

			save_bool(rage,xor_c("Insta Eoka"), funcs::weapon::instaeoka);
			save_bool(rage,xor_c("Fast Bow"), funcs::weapon::fastbow);
			save_bool(rage,xor_c("Instant Compound Charge"), funcs::weapon::instchargecompound);
			save_bool(rage,xor_c("RapidFire"), funcs::weapon::rapidfire);
			save_bool(rage,xor_c("Bullet TP"), funcs::weapon::bulletteleport);
			save_bool(rage, xor_c("Vloneport"), funcs::weapon::vlonetpeleport);
			save_bool(rage,xor_c("hitscan"), funcs::weapon::hitscan);
			save_bool(rage, xor_c("antiaimfix"), funcs::weapon::antiaimfix);
			save_int(rage,xor_c("Bullet TP Scan"), funcs::weapon::hitscantype);
			save_bool(rage,xor_c("Patrol Heli Bullet TP"), funcs::weapon::helimagic);
			save_bool(rage,xor_c("ThickBullet"), funcs::weapon::thickbullet);
			save_bool(rage,xor_c("Better Pentretion"), funcs::weapon::pierce);
			save_bool(rage,xor_c("Hit Override"), funcs::weapon::hitoverride);
			save_int(rage,xor_c("Hit Override Hitbox"), funcs::weapon::hitboxoverride);
			save_bool(rage,xor_c("Hit Override Patrol Heli"), funcs::weapon::patrolhelihitboxoverride);
			save_bool(rage,xor_c("bullet tracer"), funcs::weapon::bullettracer);
			save_bool(rage, xor_c("hitmaterial"), funcs::weapon::hitmaterial);
			save_bool(rage, xor_c("hamerdrawing"), funcs::weapon::hamerdrawing);
			save_bool(rage, xor_c("showtrajectory"), funcs::weapon::showtrajectory);
			save_bool(rage, xor_c("aimhelper"), funcs::weapon::aimhelper);
			save_bool(rage,xor_c("Infinity Jump"), funcs::localplayer::nojumprestriction);
			save_bool(rage,xor_c("No Fall Damage"), funcs::localplayer::nofalldamage);
			save_bool(rage,xor_c("Omni-Sprint"), funcs::localplayer::nosprintrestriction);
			save_bool(rage, xor_c("spiderman"), funcs::localplayer::spiderman);
			save_bool(rage,xor_c("speedhack"), funcs::localplayer::speedhack);
			save_float(rage,xor_c("speedhack float"), funcs::localplayer::speedhackfloat);
			save_int(rage,xor_c("speedhack key"), funcs::localplayer::speedhackkey);
			save_bool(rage,xor_c("Flyhack indicator"), funcs::flyhack::flyhackindicator);
			save_bool(rage,xor_c("Anti FlyHack Kick"), funcs::flyhack::antiflyhack);
			save_int(rage,xor_c("stopper ignoring"), funcs::localplayer::ignoreanyfly);

			save_bool(rage,xor_c("No Player Collision"), funcs::localplayer::noplayercollision);

			save_bool(rage,xor_c("InteractiveDebug"), funcs::localplayer::interactivedebug);
			save_int(rage,xor_c("debug key"), funcs::localplayer::interactivedebugkey);
			save_bool(rage,xor_c("FakeAdmin"), funcs::localplayer::fakeadmin);
			save_bool(rage,xor_c("istrueadmin"), funcs::localplayer::istrueadmin);
			save_bool(rage,xor_c("InstaLoot"), funcs::localplayer::instaloot);
			save_bool(rage, xor_c("walkonwater"), funcs::localplayer::walkonwater);
			save_bool(rage,xor_c("TP to Head Player"), funcs::localplayer::teleporttohead);
			save_int(rage,xor_c("Tp key  "), funcs::localplayer::teleporttoheadkey);
			save_bool(rage,xor_c("Can Hold Items"), funcs::localplayer::noattackrestriction);
			save_bool(rage, xor_c("gravity"), funcs::localplayer::gravity);
			save_float(rage, xor_c("gravityfloat"), funcs::localplayer::gravityfloat);
			save_bool(rage,xor_c("Hitmarker"), funcs::localplayer::hitmarker);
			save_bool(rage,xor_c("Damage Marker"), funcs::localplayer::damagemarker);
			save_bool(rage,xor_c("custom fov"), funcs::localplayer::customerfov);
			save_float(rage,xor_c("FOV Chander"), funcs::localplayer::fov);
			save_bool(rage,xor_c("Zoom Hack"), funcs::localplayer::zoomhack);
			save_int(rage,xor_c("Zoom"), funcs::localplayer::zoom);
			save_float(rage,xor_c("Zoom Hack Amount"), funcs::localplayer::zoomamount);
			save_bool(rage,xor_c("Custom Time"), funcs::localplayer::customtime);
			save_float(rage,xor_c("Time"), funcs::localplayer::timechander);
			save_bool(rage,xor_c("Change Night Ambient Color"), funcs::localplayer::ambient);
			save_bool(rage,xor_c("Night Ambient"), funcs::visuals::nightambientmultiplier);
			save_float(rage, xor_c("night color"), funcs::visuals::nightambient);
			save_bool(rage, xor_c("SkyChanger"), funcs::visuals::SkyChanger);
			save_bool(rage,xor_c("Crosshair"), funcs::localplayer::dot);
			save_bool(rage,xor_c("teleport Sphere"), funcs::localplayer::teleportsphere);
			save_int(rage,xor_c("Teleport button"), funcs::localplayer::teleportspherekey);
			save_bool(rage,xor_c("movementline"), funcs::localplayer::movementline);
			save_bool(rage,xor_c("modelstate"), funcs::localplayer::modelstate);
			save_int(rage,xor_c("modelstate type"), funcs::localplayer::modelstatetype);
			save_bool(rage,xor_c("hands chams"), funcs::localplayer::heandchams);
			save_int(rage,xor_c("View Model Hand Chams"), funcs::localplayer::handchamstype);
			save_bool(rage,xor_c("weapon chams"), funcs::localplayer::weaponchams);
			save_int(rage,xor_c("View Model Weapon Chams"), funcs::localplayer::weaponchamstype);
			save_bool(rage,xor_c("dropred items chams"), funcs::localplayer::droptedchams);
			save_int(rage,xor_c("Dropped Items Chams"), funcs::localplayer::itemschamstype);
			save_bool(rage,xor_c("suicide"), funcs::localplayer::suicide);
			save_int(rage, xor_c("die"), funcs::localplayer::die);
			save_bool(rage,xor_c("Remove Bob"), funcs::localplayer::removebob);
			save_bool(rage,xor_c("Remove Lower"), funcs::localplayer::removelower);
			save_bool(rage,xor_c("Remove Attack Anim"), funcs::localplayer::removeattackanim);
			save_bool(rage,xor_c("bhop"), funcs::localplayer::bhop);
			save_int(rage,xor_c("bhop key"), funcs::localplayer::bhopkey);
			save_bool(rage,xor_c("instaheal"), funcs::localplayer::instaheal);
			save_bool(rage,xor_c("Insta Pickup Player"), funcs::localplayer::instapickup);
			save_bool(rage,xor_c("AutoCollect"), funcs::localplayer::autocollect);
			save_bool(rage,xor_c("SilentFarm"), funcs::localplayer::silentfarm);
			save_bool(rage,xor_c("AntiAim"), funcs::localplayer::antiaim);
			save_bool(rage,xor_c("Force Automatic Fire"), funcs::weapon::automatic);
			save_bool(rage,xor_c("Auto Reload"), funcs::weapon::silentreload);
			save_bool(rage,xor_c("Reload indicator"), funcs::weapon::reloadindicator);
			save_bool(rage,xor_c("Silent Melee"), funcs::weapon::silentmelee);
			save_bool(rage, xor_c("silest loot stash"), funcs::weapon::silestlootstash);
			save_bool(rage, xor_c("silest loot corpes"), funcs::weapon::silestlootcorpes);
			save_bool(rage, xor_c("silest loot mine"), funcs::weapon::silestlootmine);
			save_bool(rage,xor_c("Melee atack radius"), funcs::weapon::meleeradius);
			save_int(rage,xor_c("circle type"), funcs::weapon::meleeradiustype);
			save_bool(rage,xor_c("Names"), funcs::visuals::names);
			save_bool(rage,xor_c("Flags"), funcs::visuals::wounded);
			save_bool(rage, xor_c("teamid"), funcs::visuals::teamid);
			save_bool(rage,xor_c("Box"), funcs::visuals::box);
			save_int(rage, xor_c("Box Style"), funcs::visuals::boxstyle);
			save_bool(rage,xor_c("HealtBar"), funcs::visuals::healtbar);
			save_bool(rage,xor_c("Distance"), funcs::visuals::distance);
			save_int(rage,xor_c("Distance Position"), funcs::visuals::distanceposition);
			save_bool(rage,xor_c("Skeleton"), funcs::visuals::skeleton);
			save_bool(rage,xor_c("Enemy Color Override"), funcs::visuals::enemycoloroverride);
			save_bool(rage,xor_c("Active item"), funcs::visuals::helditems);
			save_int(rage,xor_c("Item Name Type"), funcs::visuals::itemnametype);
			save_bool(rage,xor_c("Looking Direction"), funcs::visuals::looking_direction);
			save_bool(rage,xor_c("chams"), funcs::visuals::chams);
			save_int(rage,xor_c("type Chams"), funcs::visuals::chamstype);
			save_bool(rage,xor_c("Sleepers"), funcs::visuals::sleepers);
			save_bool(rage,xor_c("npc"), funcs::visuals::npc);
			save_bool(rage,xor_c("Friendly Color Override"), funcs::visuals::friendlycoloroverride);
			save_bool(rage,xor_c("Ore"), funcs::objects::ores);
			save_bool(rage,xor_c("Corpses"), funcs::objects::corpses);
			save_bool(rage,xor_c("patrol helicorper"), funcs::objects::helicorper);
			save_bool(rage,xor_c("Dropped Items"), funcs::objects::droppeditems);
			save_bool(rage,xor_c("Hemp"), funcs::objects::hemp);
			save_bool(rage,xor_c("Stashes"), funcs::objects::stashes);
			save_bool(rage,xor_c("Traps"), funcs::objects::traps);
			save_bool(rage,xor_c("Vehicles"), funcs::objects::vehicles);
			save_bool(rage,xor_c("Raid Esp"), funcs::objects::raidesp);
			save_bool(rage,xor_c("Debug"), funcs::objects::debug);
			save_bool(rage,xor_c("home"), funcs::objects::home);
			save_bool(rage,xor_c("Radar"), funcs::visuals::radar);
			save_bool(rage,xor_c("Out Of Fov Arrows"), funcs::visuals::outofarrrows);
			save_bool(rage,xor_c("Rus language"), menu::rus);


			save_float(rage, xor_c("Fov Color 0"), funcs::psilent::fovcolor[0]);
			save_float(rage, xor_c("Fov Color 1"), funcs::psilent::fovcolor[1]);
			save_float(rage, xor_c("Fov Color 2"), funcs::psilent::fovcolor[2]);

			save_float(rage, xor_c("bullet Line Color 0"), funcs::weapon::bullettracercol[0]);
			save_float(rage, xor_c("bullet Line Color 1"), funcs::weapon::bullettracercol[1]);
			save_float(rage, xor_c("bullet Line Color 2"), funcs::weapon::bullettracercol[2]);

			save_float(rage, xor_c("Friendly Color 0"), funcs::visuals::teameate[0]);
			save_float(rage, xor_c("Friendly Color 1"), funcs::visuals::teameate[1]);
			save_float(rage, xor_c("Friendly Color 2"), funcs::visuals::teameate[2]);

			save_float(rage, xor_c("Npc Color 0"), funcs::visuals::npccolor[0]);
			save_float(rage, xor_c("Npc Color 1"), funcs::visuals::npccolor[1]);
			save_float(rage, xor_c("Npc Color 2"), funcs::visuals::npccolor[2]);

			save_float(rage, xor_c("Visible Color 0"), funcs::visuals::chamsvisible[0]);
			save_float(rage, xor_c("Visible Color 1"), funcs::visuals::chamsvisible[1]);
			save_float(rage, xor_c("Visible Color 2"), funcs::visuals::chamsvisible[2]);

			save_float(rage, xor_c("Invisible Color 0"), funcs::visuals::chamsinvisible[0]);
			save_float(rage, xor_c("Invisible Color 1"), funcs::visuals::chamsinvisible[1]);
			save_float(rage, xor_c("Invisible Color 2"), funcs::visuals::chamsinvisible[2]);

			save_float(rage, xor_c("Visible Color 0"), funcs::visuals::itemschamsvisible[0]);
			save_float(rage, xor_c("Visible Color 1"), funcs::visuals::itemschamsvisible[1]);
			save_float(rage, xor_c("Visible Color 2"), funcs::visuals::itemschamsvisible[2]);

			save_float(rage, xor_c("Invisible Color 0"), funcs::visuals::itemschamsinvisible[0]);
			save_float(rage, xor_c("Invisible Color 1"), funcs::visuals::itemschamsinvisible[1]);
			save_float(rage, xor_c("Invisible Color 2"), funcs::visuals::itemschamsinvisible[2]);

			save_float(rage, xor_c("Sleepers Color 0"), funcs::visuals::sleeperscolor[0]);
			save_float(rage, xor_c("Sleepers Color 1"), funcs::visuals::sleeperscolor[1]);
			save_float(rage, xor_c("Sleepers Color 2"), funcs::visuals::sleeperscolor[2]);

			save_float(rage, xor_c("Player Color 0"), funcs::visuals::playercolor[0]);
			save_float(rage, xor_c("Player Color 1"), funcs::visuals::playercolor[1]);
			save_float(rage, xor_c("Player Color 2"), funcs::visuals::playercolor[2]);

			save_float(rage, xor_c("gun chams Color 0"), funcs::visuals::weaponchams[0]);
			save_float(rage, xor_c("gun chams Color 1"), funcs::visuals::weaponchams[1]);
			save_float(rage, xor_c("gun chams Color 2"), funcs::visuals::weaponchams[2]);

			save_float(rage, xor_c("hand chams Color 0"), funcs::visuals::handchams[0]);
			save_float(rage, xor_c("hand chams Color 1"), funcs::visuals::handchams[1]);
			save_float(rage, xor_c("hand chams Color 2"), funcs::visuals::handchams[2]);

			save_float(rage, xor_c("mov line color 0"), funcs::localplayer::movementlinecol[0]);
			save_float(rage, xor_c("mov line color 1"), funcs::localplayer::movementlinecol[1]);
			save_float(rage, xor_c("mov line color 2"), funcs::localplayer::movementlinecol[2]);

			save_float(rage, xor_c("Sphere Color 0"), funcs::localplayer::teleportspherecol[0]);
			save_float(rage, xor_c("Sphere Color 1"), funcs::localplayer::teleportspherecol[1]);
			save_float(rage, xor_c("Sphere Color 2"), funcs::localplayer::teleportspherecol[2]);

			save_float(rage, xor_c("Ambient Color 0"), funcs::visuals::ambientcolor[0]);
			save_float(rage, xor_c("Ambient Color 1"), funcs::visuals::ambientcolor[1]);
			save_float(rage, xor_c("Ambient Color 2"), funcs::visuals::ambientcolor[2]);

			save_float(rage, xor_c("SkyCol 0"), funcs::visuals::SkyCol[0]);
			save_float(rage, xor_c("SkyCol 1"), funcs::visuals::SkyCol[1]);
			save_float(rage, xor_c("SkyCol 2"), funcs::visuals::SkyCol[2]);

			save_float(rage, xor_c("window_background x"), colors::window_background.x);
			save_float(rage, xor_c("window_background y"), colors::window_background.y);
			save_float(rage, xor_c("window_background z"), colors::window_background.z);

			save_float(rage, xor_c("window_outline x"), colors::window_outline.x);
			save_float(rage, xor_c("window_outline y"), colors::window_outline.y);
			save_float(rage, xor_c("window_outline z"), colors::window_outline.z);

			save_float(rage, xor_c("window_left_side x"), colors::window_left_side.x);
			save_float(rage, xor_c("window_left_side y"), colors::window_left_side.y);
			save_float(rage, xor_c("window_left_side z"), colors::window_left_side.z);

			save_float(rage, xor_c("window_right_side x"), colors::window_right_side.x);
			save_float(rage, xor_c("window_right_side y"), colors::window_right_side.y);
			save_float(rage, xor_c("window_right_side z"), colors::window_right_side.z);

			save_float(rage, xor_c("window_group_text x"), colors::window_group_text.x);
			save_float(rage, xor_c("window_group_text y"), colors::window_group_text.y);
			save_float(rage, xor_c("window_group_text z"), colors::window_group_text.z);

			save_float(rage, xor_c("child_background x"), colors::child_background.x);
			save_float(rage, xor_c("child_background y"), colors::child_background.y);
			save_float(rage, xor_c("child_background z"), colors::child_background.z);

			save_float(rage, xor_c("child_outline_hovered x"), colors::child_outline_hovered.x);
			save_float(rage, xor_c("child_outline_hovered y"), colors::child_outline_hovered.y);
			save_float(rage, xor_c("child_outline_hovered z"), colors::child_outline_hovered.z);

			save_float(rage, xor_c("child_outline_default x"), colors::child_outline_default.x);
			save_float(rage, xor_c("child_outline_default y"), colors::child_outline_default.y);
			save_float(rage, xor_c("child_outline_default z"), colors::child_outline_default.z);

			save_float(rage, xor_c("child_text_hovered x"), colors::child_text_hovered.x);
			save_float(rage, xor_c("child_text_hovered y"), colors::child_text_hovered.y);
			save_float(rage, xor_c("child_text_hovered z"), colors::child_text_hovered.z);

			save_float(rage, xor_c("child_text_default x"), colors::child_text_default.x);
			save_float(rage, xor_c("child_text_default y"), colors::child_text_default.y);
			save_float(rage, xor_c("child_text_default z"), colors::child_text_default.z);

			save_float(rage, xor_c("tab_text_active x"), colors::tab_text_active.x);
			save_float(rage, xor_c("tab_text_active y"), colors::tab_text_active.y);
			save_float(rage, xor_c("tab_text_active z"), colors::tab_text_active.z);

			save_float(rage, xor_c("tab_text_hovered x"), colors::tab_text_hovered.x);
			save_float(rage, xor_c("tab_text_hovered y"), colors::tab_text_hovered.y);
			save_float(rage, xor_c("tab_text_hovered z"), colors::tab_text_hovered.z);

			save_float(rage, xor_c("tab_text_default x"), colors::tab_text_default.x);
			save_float(rage, xor_c("tab_text_default y"), colors::tab_text_default.y);
			save_float(rage, xor_c("tab_text_default z"), colors::tab_text_default.z);

			save_float(rage, xor_c("checkbox_text x"), colors::checkbox_text.x);
			save_float(rage, xor_c("checkbox_text y"), colors::checkbox_text.y);
			save_float(rage, xor_c("checkbox_text z"), colors::checkbox_text.z);

			save_float(rage, xor_c("checkbox_circle x"), colors::checkbox_circle.x);
			save_float(rage, xor_c("checkbox_circle y"), colors::checkbox_circle.y);
			save_float(rage, xor_c("checkbox_circle z"), colors::checkbox_circle.z);

			save_float(rage, xor_c("checkbox_rect x"), colors::checkbox_rect.x);
			save_float(rage, xor_c("checkbox_rect y"), colors::checkbox_rect.y);
			save_float(rage, xor_c("checkbox_rect z"), colors::checkbox_rect.z);

			save_float(rage, xor_c("slider_text x"), colors::slider_text.x);
			save_float(rage, xor_c("slider_text y"), colors::slider_text.y);
			save_float(rage, xor_c("slider_text z"), colors::slider_text.z);

			save_float(rage, xor_c("slider_value x"), colors::slider_value.x);
			save_float(rage, xor_c("slider_value y"), colors::slider_value.y);
			save_float(rage, xor_c("slider_value z"), colors::slider_value.z);

			save_float(rage, xor_c("slider_circle x"), colors::slider_circle.x);
			save_float(rage, xor_c("slider_circle y"), colors::slider_circle.y);
			save_float(rage, xor_c("slider_circle z"), colors::slider_circle.z);

			save_float(rage, xor_c("slider_rect x"), colors::slider_rect.x);
			save_float(rage, xor_c("slider_rect y"), colors::slider_rect.y);
			save_float(rage, xor_c("slider_rect z"), colors::slider_rect.z);

			save_float(rage, xor_c("combo_text x"), colors::combo_text.x);
			save_float(rage, xor_c("combo_text y"), colors::combo_text.y);
			save_float(rage, xor_c("combo_text z"), colors::combo_text.z);

			save_float(rage, xor_c("combo_arrow x"), colors::combo_arrow.x);
			save_float(rage, xor_c("combo_arrow y"), colors::combo_arrow.y);
			save_float(rage, xor_c("combo_arrow z"), colors::combo_arrow.z);

			save_float(rage, xor_c("combo_outline x"), colors::combo_outline.x);
			save_float(rage, xor_c("combo_outline y"), colors::combo_outline.y);
			save_float(rage, xor_c("combo_outline z"), colors::combo_outline.z);

			save_float(rage, xor_c("combo_rect x"), colors::combo_rect.x);
			save_float(rage, xor_c("combo_rect y"), colors::combo_rect.y);
			save_float(rage, xor_c("combo_rect z"), colors::combo_rect.z);

			save_float(rage, xor_c("combo_window x"), colors::combo_window.x);
			save_float(rage, xor_c("combo_window y"), colors::combo_window.y);
			save_float(rage, xor_c("combo_window z"), colors::combo_window.z);

			save_float(rage, xor_c("selectable_text_active x"), colors::selectable_text_active.x);
			save_float(rage, xor_c("selectable_text_active y"), colors::selectable_text_active.y);
			save_float(rage, xor_c("selectable_text_active z"), colors::selectable_text_active.z);

			save_float(rage, xor_c("selectable_text_default x"), colors::selectable_text_default.x);
			save_float(rage, xor_c("selectable_text_default y"), colors::selectable_text_default.y);
			save_float(rage, xor_c("selectable_text_default z"), colors::selectable_text_default.z);

			save_float(rage, xor_c("input_rect x"), colors::input_rect.x);
			save_float(rage, xor_c("input_rect y"), colors::input_rect.y);
			save_float(rage, xor_c("input_rect z"), colors::input_rect.z);

			save_float(rage, xor_c("input_text x"), colors::input_text.x);
			save_float(rage, xor_c("input_text y"), colors::input_text.y);
			save_float(rage, xor_c("input_text z"), colors::input_text.z);

			save_float(rage, xor_c("input_buf x"), colors::input_buf.x);
			save_float(rage, xor_c("input_buf y"), colors::input_buf.y);
			save_float(rage, xor_c("input_buf z"), colors::input_buf.z);

			save_float(rage, xor_c("button_text x"), colors::button_text.x);
			save_float(rage, xor_c("button_text y"), colors::button_text.y);
			save_float(rage, xor_c("button_text z"), colors::button_text.z);

			save_float(rage, xor_c("button_outline x"), colors::button_outline.x);
			save_float(rage, xor_c("button_outline y"), colors::button_outline.y);
			save_float(rage, xor_c("button_outline z"), colors::button_outline.z);

			save_float(rage, xor_c("button_rect x"), colors::button_rect.x);
			save_float(rage, xor_c("button_rect y"), colors::button_rect.y);
			save_float(rage, xor_c("button_rect z"), colors::button_rect.z);

			save_float(rage, xor_c("list_outline x"), colors::list_outline.x);
			save_float(rage, xor_c("list_outline y"), colors::list_outline.y);
			save_float(rage, xor_c("list_outline z"), colors::list_outline.z);

			save_float(rage, xor_c("list_rect x"), colors::list_rect.x);
			save_float(rage, xor_c("list_rect y"), colors::list_rect.y);
			save_float(rage, xor_c("list_rect z"), colors::list_rect.z);

			save_float(rage, xor_c("color_outline x"), colors::color_outline.x);
			save_float(rage, xor_c("color_outline y"), colors::color_outline.y);
			save_float(rage, xor_c("color_outline z"), colors::color_outline.z);

			save_float(rage, xor_c("color_rect x"), colors::color_rect.x);
			save_float(rage, xor_c("color_rect y"), colors::color_rect.y);
			save_float(rage, xor_c("color_rect z"), colors::color_rect.z);

			save_float(rage, xor_c("color_text x"), colors::color_text.x);
			save_float(rage, xor_c("color_text y"), colors::color_text.y);
			save_float(rage, xor_c("color_text z"), colors::color_text.z);

			save_float(rage, xor_c("key_text x"), colors::key_text.x);
			save_float(rage, xor_c("key_text y"), colors::key_text.y);
			save_float(rage, xor_c("key_text z"), colors::key_text.z);

			save_float(rage, xor_c("key_outline x"), colors::key_outline.x);
			save_float(rage, xor_c("key_outline y"), colors::key_outline.y);
			save_float(rage, xor_c("key_outline z"), colors::key_outline.z);

			save_float(rage, xor_c("key_rect x"), colors::key_rect.x);
			save_float(rage, xor_c("key_rect y"), colors::key_rect.y);
			save_float(rage, xor_c("key_rect z"), colors::key_rect.z);

			save_float(rage, xor_c("key_window x"), colors::key_window.x);
			save_float(rage, xor_c("key_window y"), colors::key_window.y);
			save_float(rage, xor_c("key_window z"), colors::key_window.z);

			save_float(rage, xor_c("key_window_outline x"), colors::key_window_outline.x);
			save_float(rage, xor_c("key_window_outline y"), colors::key_window_outline.y);
			save_float(rage, xor_c("key_window_outline z"), colors::key_window_outline.z);
		}

		std::string file = folder + config_name;
		auto str = json_obj.toStyledString();
		for (int i = 0; i < str.size(); ++i)
			str[i] ^= CFG_XOR_KEY;

		std::ofstream file_out(file);
		if (file_out.good())
			file_out << str;
		file_out.close();
	}

	void erase(const std::string& config_name) {
		std::string file = folder + config_name;
		remove(file.c_str());
	}

	void load(const std::string& config_name) {
		std::string file = folder + config_name;

		auto str = file_to_string(file);
		if (str.empty())
			return;

		for (int i = 0; i < str.size(); ++i)
			str[i] ^= CFG_XOR_KEY;

		std::stringstream stream{};
		stream << str;

		json json_obj{};
		stream >> json_obj;

		if (!json_obj.isMember(xor_c("rage")))
			return;

		auto& rage = json_obj[xor_c("rage")]; {
			load_bool(rage, xor_c("Aim"), funcs::psilent::psilent);
			load_int(rage, xor_c("Enable key"), funcs::psilent::key);
			load_bool(rage, xor_c("locktarget"), funcs::psilent::locktarget);
			load_int(rage, xor_c("targetlock key"), funcs::psilent::targetlockkey);
			load_bool(rage, xor_c("manipulatorhitscan"), funcs::weapon::manipulatorhitscan);
			load_int(rage, xor_c("Aim Spot"), funcs::psilent::a_spot);
			load_bool(rage, xor_c("Draw Fov Circle"), funcs::psilent::drawfov);
			load_float(rage, xor_c("Fov"), funcs::psilent::fov);
			load_int(rage, xor_c("autoshottype"), funcs::psilent::autoshottype);
			load_bool(rage, xor_c("Target Name"), funcs::psilent::target_name);
			load_bool(rage, xor_c("FakeShots"), funcs::weapon::fakeshots);
			load_int(rage, xor_c("FakeShots Key"), funcs::weapon::fakeshotskey);
			load_bool(rage, xor_c("Target Sleepers"), funcs::psilent::sleepers);
			load_bool(rage, xor_c("Target Woundead"), funcs::psilent::woundead);
			load_bool(rage, xor_c("Target Friendly"), funcs::psilent::frendly);
			load_bool(rage, xor_c("Manipuator"), funcs::manipulator::manipulator);
			load_int(rage, xor_c("Manipuator Mode"), funcs::manipulator::desyncmode);
			load_int(rage, xor_c("Manipuator Key"), funcs::manipulator::manipulatorkey);
			load_bool(rage, xor_c("Desync indicator"), funcs::manipulator::desyncindicator);
			load_bool(rage, xor_c("target line"), funcs::psilent::target_line);
			load_float(rage, xor_c("Max Desync Time"), funcs::manipulator::maxdesyncfloat);
			load_bool(rage, xor_c("Recoil control"), funcs::weapon::recoilas);
			load_float(rage, xor_c("Recoil"), funcs::weapon::norecoil);
			load_float(rage, xor_c("Aim Cone"), funcs::weapon::spread);
			load_float(rage, xor_c("bullet speed"), funcs::weapon::bulletspeed);
			load_bool(rage, xor_c("Flowvelocity"), funcs::weapon::lowvelocity);
			load_bool(rage, xor_c("Insta Eoka"), funcs::weapon::instaeoka);
			load_bool(rage, xor_c("Fast Bow"), funcs::weapon::fastbow);
			load_bool(rage, xor_c("Instant Compound Charge"), funcs::weapon::instchargecompound);
			load_bool(rage, xor_c("RapidFire"), funcs::weapon::rapidfire);
			load_bool(rage, xor_c("Bullet TP"), funcs::weapon::bulletteleport);
			load_bool(rage, xor_c("Vloneport"), funcs::weapon::vlonetpeleport);
			load_bool(rage, xor_c("hitscan"), funcs::weapon::hitscan);
			load_bool(rage, xor_c("antiaimfix"), funcs::weapon::antiaimfix);
			load_int(rage, xor_c("Bullet TP Scan"), funcs::weapon::hitscantype);
			load_bool(rage, xor_c("Patrol Heli Bullet TP"), funcs::weapon::helimagic);
			load_bool(rage, xor_c("ThickBullet"), funcs::weapon::thickbullet);
			load_bool(rage, xor_c("Better Pentretion"), funcs::weapon::pierce);
			load_bool(rage, xor_c("Hit Override"), funcs::weapon::hitoverride);
			load_int(rage, xor_c("Hit Override Hitbox"), funcs::weapon::hitboxoverride);
			load_bool(rage, xor_c("Hit Override Patrol Heli"), funcs::weapon::patrolhelihitboxoverride);
			load_bool(rage, xor_c("bullet tracer"), funcs::weapon::bullettracer);
			load_bool(rage, xor_c("hitmaterial"), funcs::weapon::hitmaterial);
			load_bool(rage, xor_c("hamerdrawing"), funcs::weapon::hamerdrawing);
			load_bool(rage, xor_c("showtrajectory"), funcs::weapon::showtrajectory);
			load_bool(rage, xor_c("aimhelper"), funcs::weapon::aimhelper);
			load_bool(rage, xor_c("Infinity Jump"), funcs::localplayer::nojumprestriction);
			load_bool(rage, xor_c("No Fall Damage"), funcs::localplayer::nofalldamage);
			load_bool(rage, xor_c("Omni-Sprint"), funcs::localplayer::nosprintrestriction);
			load_bool(rage, xor_c("spiderman"), funcs::localplayer::spiderman);
			load_bool(rage, xor_c("speedhack"), funcs::localplayer::speedhack);
			load_float(rage, xor_c("speedhack float"), funcs::localplayer::speedhackfloat);
			load_int(rage, xor_c("speedhack key"), funcs::localplayer::speedhackkey);
			load_bool(rage, xor_c("Flyhack indicator"), funcs::flyhack::flyhackindicator);
			load_bool(rage, xor_c("Anti FlyHack Kick"), funcs::flyhack::antiflyhack);
			load_int(rage, xor_c("stopper ignoring"), funcs::localplayer::ignoreanyfly);

			load_bool(rage, xor_c("No Player Collision"), funcs::localplayer::noplayercollision);

			load_bool(rage, xor_c("InteractiveDebug"), funcs::localplayer::interactivedebug);
			load_int(rage, xor_c("debug key"), funcs::localplayer::interactivedebugkey);
			load_bool(rage, xor_c("FakeAdmin"), funcs::localplayer::fakeadmin);
			load_bool(rage, xor_c("istrueadmin"), funcs::localplayer::istrueadmin);
			load_bool(rage, xor_c("InstaLoot"), funcs::localplayer::instaloot);
			load_bool(rage, xor_c("walkonwater"), funcs::localplayer::walkonwater);
			load_bool(rage, xor_c("TP to Head Player"), funcs::localplayer::teleporttohead);
			load_int(rage, xor_c("Tp key  "), funcs::localplayer::teleporttoheadkey);
			load_bool(rage, xor_c("Can Hold Items"), funcs::localplayer::noattackrestriction);
			load_bool(rage, xor_c("gravity"), funcs::localplayer::gravity);
			load_float(rage, xor_c("gravityfloat"), funcs::localplayer::gravityfloat);
			load_bool(rage, xor_c("Hitmarker"), funcs::localplayer::hitmarker);
			load_bool(rage, xor_c("Damage Marker"), funcs::localplayer::damagemarker);
			load_bool(rage, xor_c("custom fov"), funcs::localplayer::customerfov);
			load_float(rage, xor_c("FOV Chander"), funcs::localplayer::fov);
			load_bool(rage, xor_c("Zoom Hack"), funcs::localplayer::zoomhack);
			load_int(rage, xor_c("Zoom"), funcs::localplayer::zoom);
			load_float(rage, xor_c("Zoom Hack Amount"), funcs::localplayer::zoomamount);
			load_bool(rage, xor_c("Custom Time"), funcs::localplayer::customtime);
			load_float(rage, xor_c("Time"), funcs::localplayer::timechander);
			load_bool(rage, xor_c("Change Night Ambient Color"), funcs::localplayer::ambient);
			load_bool(rage, xor_c("Night Ambient"), funcs::visuals::nightambientmultiplier);
			load_float(rage, xor_c("night color"), funcs::visuals::nightambient);
			load_bool(rage, xor_c("SkyChanger"), funcs::visuals::SkyChanger);
			load_bool(rage, xor_c("Crosshair"), funcs::localplayer::dot);
			load_bool(rage, xor_c("teleport Sphere"), funcs::localplayer::teleportsphere);
			load_int(rage, xor_c("Teleport button"), funcs::localplayer::teleportspherekey);
			load_bool(rage, xor_c("movementline"), funcs::localplayer::movementline);
			load_bool(rage, xor_c("modelstate"), funcs::localplayer::modelstate);
			load_int(rage, xor_c("modelstate type"), funcs::localplayer::modelstatetype);
			load_bool(rage, xor_c("hands chams"), funcs::localplayer::heandchams);
			load_int(rage, xor_c("View Model Hand Chams"), funcs::localplayer::handchamstype);
			load_bool(rage, xor_c("weapon chams"), funcs::localplayer::weaponchams);
			load_int(rage, xor_c("View Model Weapon Chams"), funcs::localplayer::weaponchamstype);
			load_bool(rage, xor_c("dropred items chams"), funcs::localplayer::droptedchams);
			load_int(rage, xor_c("Dropped Items Chams"), funcs::localplayer::itemschamstype);
			load_bool(rage, xor_c("suicide"), funcs::localplayer::suicide);
			load_int(rage, xor_c("die"), funcs::localplayer::die);
			load_bool(rage, xor_c("Remove Bob"), funcs::localplayer::removebob);
			load_bool(rage, xor_c("Remove Lower"), funcs::localplayer::removelower);
			load_bool(rage, xor_c("Remove Attack Anim"), funcs::localplayer::removeattackanim);
			load_bool(rage, xor_c("bhop"), funcs::localplayer::bhop);
			load_int(rage, xor_c("bhop key"), funcs::localplayer::bhopkey);
			load_bool(rage, xor_c("instaheal"), funcs::localplayer::instaheal);
			load_bool(rage, xor_c("Insta Pickup Player"), funcs::localplayer::instapickup);
			load_bool(rage, xor_c("AutoCollect"), funcs::localplayer::autocollect);
			load_bool(rage, xor_c("SilentFarm"), funcs::localplayer::silentfarm);
			load_bool(rage, xor_c("AntiAim"), funcs::localplayer::antiaim);
			load_bool(rage, xor_c("Force Automatic Fire"), funcs::weapon::automatic);
			load_bool(rage, xor_c("Auto Reload"), funcs::weapon::silentreload);
			load_bool(rage, xor_c("Reload indicator"), funcs::weapon::reloadindicator);
			load_bool(rage, xor_c("Silent Melee"), funcs::weapon::silentmelee);
			load_bool(rage, xor_c("silest loot stash"), funcs::weapon::silestlootstash);
			load_bool(rage, xor_c("silest loot corpes"), funcs::weapon::silestlootcorpes);
			load_bool(rage, xor_c("silest loot mine"), funcs::weapon::silestlootmine);
			load_bool(rage, xor_c("Melee atack radius"), funcs::weapon::meleeradius);
			load_int(rage, xor_c("circle type"), funcs::weapon::meleeradiustype);
			load_bool(rage, xor_c("Names"), funcs::visuals::names);
			load_bool(rage, xor_c("Flags"), funcs::visuals::wounded);
			load_bool(rage, xor_c("teamid"), funcs::visuals::teamid);
			load_bool(rage, xor_c("Box"), funcs::visuals::box);
			load_int(rage, xor_c("Box Style"), funcs::visuals::boxstyle);
			load_bool(rage, xor_c("HealtBar"), funcs::visuals::healtbar);
			load_bool(rage, xor_c("Distance"), funcs::visuals::distance);
			load_int(rage, xor_c("Distance Position"), funcs::visuals::distanceposition);
			load_bool(rage, xor_c("Skeleton"), funcs::visuals::skeleton);
			load_bool(rage, xor_c("Enemy Color Override"), funcs::visuals::enemycoloroverride);
			load_bool(rage, xor_c("Active item"), funcs::visuals::helditems);
			load_int(rage, xor_c("Item Name Type"), funcs::visuals::itemnametype);
			load_bool(rage, xor_c("Looking Direction"), funcs::visuals::looking_direction);
			load_bool(rage, xor_c("chams"), funcs::visuals::chams);
			load_int(rage, xor_c("type Chams"), funcs::visuals::chamstype);
			load_bool(rage, xor_c("Sleepers"), funcs::visuals::sleepers);
			load_bool(rage, xor_c("npc"), funcs::visuals::npc);
			load_bool(rage, xor_c("Friendly Color Override"), funcs::visuals::friendlycoloroverride);
			load_bool(rage, xor_c("Ore"), funcs::objects::ores);
			load_bool(rage, xor_c("Corpses"), funcs::objects::corpses);
			load_bool(rage, xor_c("patrol helicorper"), funcs::objects::helicorper);
			load_bool(rage, xor_c("Dropped Items"), funcs::objects::droppeditems);
			load_bool(rage, xor_c("Hemp"), funcs::objects::hemp);
			load_bool(rage, xor_c("Stashes"), funcs::objects::stashes);
			load_bool(rage, xor_c("Traps"), funcs::objects::traps);
			load_bool(rage, xor_c("Vehicles"), funcs::objects::vehicles);
			load_bool(rage, xor_c("Raid Esp"), funcs::objects::raidesp);
			load_bool(rage, xor_c("Debug"), funcs::objects::debug);
			load_bool(rage, xor_c("home"), funcs::objects::home);
			load_bool(rage, xor_c("Radar"), funcs::visuals::radar);
			load_bool(rage, xor_c("Out Of Fov Arrows"), funcs::visuals::outofarrrows);
			load_bool(rage, xor_c("Rus language"), menu::rus);


			load_float(rage, xor_c("Fov Color"), funcs::psilent::fovcolor[0]);
			load_float(rage, xor_c("Fov Color"), funcs::psilent::fovcolor[1]);
			load_float(rage, xor_c("Fov Color"), funcs::psilent::fovcolor[2]);

			load_float(rage, xor_c("bullet Line Color"), funcs::weapon::bullettracercol[0]);
			load_float(rage, xor_c("bullet Line Color"), funcs::weapon::bullettracercol[1]);
			load_float(rage, xor_c("bullet Line Color"), funcs::weapon::bullettracercol[2]);

			load_float(rage, xor_c("Friendly Color"), funcs::visuals::teameate[0]);
			load_float(rage, xor_c("Friendly Color"), funcs::visuals::teameate[1]);
			load_float(rage, xor_c("Friendly Color"), funcs::visuals::teameate[2]);

			load_float(rage, xor_c("Npc Color"), funcs::visuals::npccolor[0]);
			load_float(rage, xor_c("Npc Color"), funcs::visuals::npccolor[1]);
			load_float(rage, xor_c("Npc Color"), funcs::visuals::npccolor[2]);

			load_float(rage, xor_c("Visible Color"), funcs::visuals::chamsvisible[0]);
			load_float(rage, xor_c("Visible Color"), funcs::visuals::chamsvisible[1]);
			load_float(rage, xor_c("Visible Color"), funcs::visuals::chamsvisible[2]);

			load_float(rage, xor_c("Invisible Color"), funcs::visuals::chamsinvisible[0]);
			load_float(rage, xor_c("Invisible Color"), funcs::visuals::chamsinvisible[1]);
			load_float(rage, xor_c("Invisible Color"), funcs::visuals::chamsinvisible[2]);

			load_float(rage, xor_c("Visible Color"), funcs::visuals::itemschamsvisible[0]);
			load_float(rage, xor_c("Visible Color"), funcs::visuals::itemschamsvisible[1]);
			load_float(rage, xor_c("Visible Color"), funcs::visuals::itemschamsvisible[2]);

			load_float(rage, xor_c("Invisible Color"), funcs::visuals::itemschamsinvisible[0]);
			load_float(rage, xor_c("Invisible Color"), funcs::visuals::itemschamsinvisible[1]);
			load_float(rage, xor_c("Invisible Color"), funcs::visuals::itemschamsinvisible[2]);

			load_float(rage, xor_c("Sleepers Color"), funcs::visuals::sleeperscolor[0]);
			load_float(rage, xor_c("Sleepers Color"), funcs::visuals::sleeperscolor[1]);
			load_float(rage, xor_c("Sleepers Color"), funcs::visuals::sleeperscolor[2]);

			load_float(rage, xor_c("Player Color"), funcs::visuals::playercolor[0]);
			load_float(rage, xor_c("Player Color"), funcs::visuals::playercolor[1]);
			load_float(rage, xor_c("Player Color"), funcs::visuals::playercolor[2]);

			load_float(rage, xor_c("gun chams Color"), funcs::visuals::weaponchams[0]);
			load_float(rage, xor_c("gun chams Color"), funcs::visuals::weaponchams[1]);
			load_float(rage, xor_c("gun chams Color"), funcs::visuals::weaponchams[2]);

			load_float(rage, xor_c("hand chams Color"), funcs::visuals::handchams[0]);
			load_float(rage, xor_c("hand chams Color"), funcs::visuals::handchams[1]);
			load_float(rage, xor_c("hand chams Color"), funcs::visuals::handchams[2]);

			load_float(rage, xor_c("mov line color"), funcs::localplayer::movementlinecol[0]);
			load_float(rage, xor_c("mov line color"), funcs::localplayer::movementlinecol[1]);
			load_float(rage, xor_c("mov line color"), funcs::localplayer::movementlinecol[2]);

			load_float(rage, xor_c("Sphere Color"), funcs::localplayer::teleportspherecol[0]);
			load_float(rage, xor_c("Sphere Color"), funcs::localplayer::teleportspherecol[1]);
			load_float(rage, xor_c("Sphere Color"), funcs::localplayer::teleportspherecol[2]);

			load_float(rage, xor_c("Ambient Color"), funcs::visuals::ambientcolor[0]);
			load_float(rage, xor_c("Ambient Color"), funcs::visuals::ambientcolor[1]);
			load_float(rage, xor_c("Ambient Color"), funcs::visuals::ambientcolor[2]);

			load_float(rage, xor_c("SkyCol 0"), funcs::visuals::SkyCol[0]);
			load_float(rage, xor_c("SkyCol 1"), funcs::visuals::SkyCol[1]);
			load_float(rage, xor_c("SkyCol 2"), funcs::visuals::SkyCol[2]);

			load_float(rage, xor_c("window_background x"), colors::window_background.x);
			load_float(rage, xor_c("window_background y"), colors::window_background.y);
			load_float(rage, xor_c("window_background z"), colors::window_background.z);

			load_float(rage, xor_c("window_outline x"), colors::window_outline.x);
			load_float(rage, xor_c("window_outline y"), colors::window_outline.y);
			load_float(rage, xor_c("window_outline z"), colors::window_outline.z);

			load_float(rage, xor_c("window_left_side x"), colors::window_left_side.x);
			load_float(rage, xor_c("window_left_side y"), colors::window_left_side.y);
			load_float(rage, xor_c("window_left_side z"), colors::window_left_side.z);

			load_float(rage, xor_c("window_right_side x"), colors::window_right_side.x);
			load_float(rage, xor_c("window_right_side y"), colors::window_right_side.y);
			load_float(rage, xor_c("window_right_side z"), colors::window_right_side.z);

			load_float(rage, xor_c("window_group_text x"), colors::window_group_text.x);
			load_float(rage, xor_c("window_group_text y"), colors::window_group_text.y);
			load_float(rage, xor_c("window_group_text z"), colors::window_group_text.z);

			load_float(rage, xor_c("child_background x"), colors::child_background.x);
			load_float(rage, xor_c("child_background y"), colors::child_background.y);
			load_float(rage, xor_c("child_background z"), colors::child_background.z);

			load_float(rage, xor_c("child_outline_hovered x"), colors::child_outline_hovered.x);
			load_float(rage, xor_c("child_outline_hovered y"), colors::child_outline_hovered.y);
			load_float(rage, xor_c("child_outline_hovered z"), colors::child_outline_hovered.z);

			load_float(rage, xor_c("child_outline_default x"), colors::child_outline_default.x);
			load_float(rage, xor_c("child_outline_default y"), colors::child_outline_default.y);
			load_float(rage, xor_c("child_outline_default z"), colors::child_outline_default.z);

			load_float(rage, xor_c("child_text_hovered x"), colors::child_text_hovered.x);
			load_float(rage, xor_c("child_text_hovered y"), colors::child_text_hovered.y);
			load_float(rage, xor_c("child_text_hovered z"), colors::child_text_hovered.z);

			load_float(rage, xor_c("child_text_default x"), colors::child_text_default.x);
			load_float(rage, xor_c("child_text_default y"), colors::child_text_default.y);
			load_float(rage, xor_c("child_text_default z"), colors::child_text_default.z);

			load_float(rage, xor_c("tab_text_active x"), colors::tab_text_active.x);
			load_float(rage, xor_c("tab_text_active y"), colors::tab_text_active.y);
			load_float(rage, xor_c("tab_text_active z"), colors::tab_text_active.z);

			load_float(rage, xor_c("tab_text_hovered x"), colors::tab_text_hovered.x);
			load_float(rage, xor_c("tab_text_hovered y"), colors::tab_text_hovered.y);
			load_float(rage, xor_c("tab_text_hovered z"), colors::tab_text_hovered.z);

			load_float(rage, xor_c("tab_text_default x"), colors::tab_text_default.x);
			load_float(rage, xor_c("tab_text_default y"), colors::tab_text_default.y);
			load_float(rage, xor_c("tab_text_default z"), colors::tab_text_default.z);

			load_float(rage, xor_c("checkbox_text x"), colors::checkbox_text.x);
			load_float(rage, xor_c("checkbox_text y"), colors::checkbox_text.y);
			load_float(rage, xor_c("checkbox_text z"), colors::checkbox_text.z);

			load_float(rage, xor_c("checkbox_circle x"), colors::checkbox_circle.x);
			load_float(rage, xor_c("checkbox_circle y"), colors::checkbox_circle.y);
			load_float(rage, xor_c("checkbox_circle z"), colors::checkbox_circle.z);

			load_float(rage, xor_c("checkbox_rect x"), colors::checkbox_rect.x);
			load_float(rage, xor_c("checkbox_rect y"), colors::checkbox_rect.y);
			load_float(rage, xor_c("checkbox_rect z"), colors::checkbox_rect.z);

			load_float(rage, xor_c("slider_text x"), colors::slider_text.x);
			load_float(rage, xor_c("slider_text y"), colors::slider_text.y);
			load_float(rage, xor_c("slider_text z"), colors::slider_text.z);

			load_float(rage, xor_c("slider_value x"), colors::slider_value.x);
			load_float(rage, xor_c("slider_value y"), colors::slider_value.y);
			load_float(rage, xor_c("slider_value z"), colors::slider_value.z);

			load_float(rage, xor_c("slider_circle x"), colors::slider_circle.x);
			load_float(rage, xor_c("slider_circle y"), colors::slider_circle.y);
			load_float(rage, xor_c("slider_circle z"), colors::slider_circle.z);

			load_float(rage, xor_c("slider_rect x"), colors::slider_rect.x);
			load_float(rage, xor_c("slider_rect y"), colors::slider_rect.y);
			load_float(rage, xor_c("slider_rect z"), colors::slider_rect.z);

			load_float(rage, xor_c("combo_text x"), colors::combo_text.x);
			load_float(rage, xor_c("combo_text y"), colors::combo_text.y);
			load_float(rage, xor_c("combo_text z"), colors::combo_text.z);

			load_float(rage, xor_c("combo_arrow x"), colors::combo_arrow.x);
			load_float(rage, xor_c("combo_arrow y"), colors::combo_arrow.y);
			load_float(rage, xor_c("combo_arrow z"), colors::combo_arrow.z);

			load_float(rage, xor_c("combo_outline x"), colors::combo_outline.x);
			load_float(rage, xor_c("combo_outline y"), colors::combo_outline.y);
			load_float(rage, xor_c("combo_outline z"), colors::combo_outline.z);

			load_float(rage, xor_c("combo_rect x"), colors::combo_rect.x);
			load_float(rage, xor_c("combo_rect y"), colors::combo_rect.y);
			load_float(rage, xor_c("combo_rect z"), colors::combo_rect.z);

			load_float(rage, xor_c("combo_window x"), colors::combo_window.x);
			load_float(rage, xor_c("combo_window y"), colors::combo_window.y);
			load_float(rage, xor_c("combo_window z"), colors::combo_window.z);

			load_float(rage, xor_c("selectable_text_active x"), colors::selectable_text_active.x);
			load_float(rage, xor_c("selectable_text_active y"), colors::selectable_text_active.y);
			load_float(rage, xor_c("selectable_text_active z"), colors::selectable_text_active.z);

			load_float(rage, xor_c("selectable_text_default x"), colors::selectable_text_default.x);
			load_float(rage, xor_c("selectable_text_default y"), colors::selectable_text_default.y);
			load_float(rage, xor_c("selectable_text_default z"), colors::selectable_text_default.z);

			load_float(rage, xor_c("input_rect x"), colors::input_rect.x);
			load_float(rage, xor_c("input_rect y"), colors::input_rect.y);
			load_float(rage, xor_c("input_rect z"), colors::input_rect.z);

			load_float(rage, xor_c("input_text x"), colors::input_text.x);
			load_float(rage, xor_c("input_text y"), colors::input_text.y);
			load_float(rage, xor_c("input_text z"), colors::input_text.z);

			load_float(rage, xor_c("input_buf x"), colors::input_buf.x);
			load_float(rage, xor_c("input_buf y"), colors::input_buf.y);
			load_float(rage, xor_c("input_buf z"), colors::input_buf.z);

			load_float(rage, xor_c("button_text x"), colors::button_text.x);
			load_float(rage, xor_c("button_text y"), colors::button_text.y);
			load_float(rage, xor_c("button_text z"), colors::button_text.z);

			load_float(rage, xor_c("button_outline x"), colors::button_outline.x);
			load_float(rage, xor_c("button_outline y"), colors::button_outline.y);
			load_float(rage, xor_c("button_outline z"), colors::button_outline.z);

			load_float(rage, xor_c("button_rect x"), colors::button_rect.x);
			load_float(rage, xor_c("button_rect y"), colors::button_rect.y);
			load_float(rage, xor_c("button_rect z"), colors::button_rect.z);

			load_float(rage, xor_c("list_outline x"), colors::list_outline.x);
			load_float(rage, xor_c("list_outline y"), colors::list_outline.y);
			load_float(rage, xor_c("list_outline z"), colors::list_outline.z);

			load_float(rage, xor_c("list_rect x"), colors::list_rect.x);
			load_float(rage, xor_c("list_rect y"), colors::list_rect.y);
			load_float(rage, xor_c("list_rect z"), colors::list_rect.z);

			load_float(rage, xor_c("color_outline x"), colors::color_outline.x);
			load_float(rage, xor_c("color_outline y"), colors::color_outline.y);
			load_float(rage, xor_c("color_outline z"), colors::color_outline.z);

			load_float(rage, xor_c("color_rect x"), colors::color_rect.x);
			load_float(rage, xor_c("color_rect y"), colors::color_rect.y);
			load_float(rage, xor_c("color_rect z"), colors::color_rect.z);

			load_float(rage, xor_c("color_text x"), colors::color_text.x);
			load_float(rage, xor_c("color_text y"), colors::color_text.y);
			load_float(rage, xor_c("color_text z"), colors::color_text.z);

			load_float(rage, xor_c("key_text x"), colors::key_text.x);
			load_float(rage, xor_c("key_text y"), colors::key_text.y);
			load_float(rage, xor_c("key_text z"), colors::key_text.z);

			load_float(rage, xor_c("key_outline x"), colors::key_outline.x);
			load_float(rage, xor_c("key_outline y"), colors::key_outline.y);
			load_float(rage, xor_c("key_outline z"), colors::key_outline.z);

			load_float(rage, xor_c("key_rect x"), colors::key_rect.x);
			load_float(rage, xor_c("key_rect y"), colors::key_rect.y);
			load_float(rage, xor_c("key_rect z"), colors::key_rect.z);

			load_float(rage, xor_c("key_window x"), colors::key_window.x);
			load_float(rage, xor_c("key_window y"), colors::key_window.y);
			load_float(rage, xor_c("key_window z"), colors::key_window.z);

			load_float(rage, xor_c("key_window_outline x"), colors::key_window_outline.x);
			load_float(rage, xor_c("key_window_outline y"), colors::key_window_outline.y);
			load_float(rage, xor_c("key_window_outline z"), colors::key_window_outline.z);
		}

	}
}