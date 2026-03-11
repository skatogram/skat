#pragma once
Discord* g_Discord;
std::string userauth;
std::string passauth;
std::string steamidis;
static std::string selected_cfg = "";
static char config_name[256]{};
Vector2 screen_size = { 0, 0 };
float bigBulletSize = 0;
namespace menu
{
	bool menuopen = false;
	bool rus = false;
	bool unload = false;
	bool cheat_init = false;
}


namespace funcs
{
	namespace weapon {
		bool fakeshots = false;
		bool customhitsound = false;
		bool antiaimfix = false;
		int fakeshotskey = 0;
		bool recoilas = false;
		float norecoil = 100.f;
		float ROT = 2.f;
		float ROT2 = 2.f;
		float spread = 1.f;
		bool automatic = false;
		bool lowvelocity = false;
		float bulletspeed = 1.f;
		float dsfv = 1.f;
		bool instaeoka = false;
		bool fastbow = false;
		bool instchargecompound = false;
		bool silentreload = false;
		bool thickbullet = false;
		bool vlonetpeleport = false;
		bool bulletteleport = false;
		bool hitscan = false;
		bool manipulatorhitscan = false;
		int hitscantype = 0;
		bool rapidfire = false;
		bool helimagic = false;
		bool hitoverride = false;
		bool silentmelee = false;
		bool fakelags1 = false;
		bool modelfck = false;
		bool silestlootstash = false;
		bool silestlootcorpes = false;
		bool silestlootmine = false;
		bool meleeradius = false;
		int meleeradiustype = 0;
		bool pierce = false;
		int hitboxoverride = 0;
		bool patrolhelihitboxoverride = false;
		bool bullettracer = false;
		float bullettracercol[] = { 1.f, 1.f,1.f,1.f };
		bool reloadindicator = false;
		bool hitmaterial = false;
		bool hamerdrawing = false;
		bool showtrajectory = false;
		bool aimhelper = false;
	}
	namespace localplayer
	{
		bool hitmarker = false;
		bool damagemarker = false;
		bool istrueadmin = false;
		bool fakeadmin = false;
		bool interactivedebug = false;
		int interactivedebugkey = 0;
		bool noplayercollision = false;
		int ignoreanyfly = 0;
		bool nosprintrestriction = false;
		bool nofalldamage = false;
		bool nojumprestriction = false;
		bool spiderman = false;
		bool instaloot = false;
		bool walkonwater = false;
		bool teleporttohead = false;
		int teleporttoheadkey = 0;
		bool antiaim = false;
		bool instapickup = false;
		bool autocollect = false;
		bool silentfarm = false;
		float fov = 90.f;
		float zoomamount = 5.f;
		bool zoomhack = false;
		bool customerfov = false;
		int zoom = 0;
		int die = 0;
		bool aspect = false;
		float aspectvalue = 5.f;
		bool noattackrestriction = false;
		bool gravity = false;
		float gravityfloat = 2.5;
		bool ambient = false;
		bool customtime = false;
		float timechander = 10.f;
		float lagsam = 0.4f;
		bool dot = false;
		bool teleportsphere = false;
		int teleportspherekey = 0;
		float teleportspherecol[] = { 1.f, 1.f,1.f,1.f };
		bool movementline = false;
		float movementlinecol[] = { 1.f, 1.f,1.f,1.f };
		bool heandchams = false;
		bool weaponchams = false;
		bool droptedchams = false;
		int handchamstype = 0;
		int weaponchamstype = 0;
		int itemschamstype = 0;
		bool suicide = false;
		bool removebob = false;
		bool removelower = false;
		bool removeattackanim = false;
		bool modelstate = false;
		int modelstatetype = 0;
		bool speedhack;
		float speedhackfloat = 50.f;
		int speedhackkey = 0;
		bool bhop = false;
		int bhopkey = 0;
		bool instaheal = false;
		
	}
	namespace psilent
	{
		bool psilent = false;
		bool locktarget = false;
		int autoshottype = 0;
		int key{ };
		int targetlockkey{ };
		int a_spot = 0;
		float fov = 100.f;
		bool drawfov = false;
		bool sleepers = false;
		bool woundead = false;
		bool frendly = false;
		float fovcolor[] = { 1.f, 1.f,1.f ,1.f };
		bool target_name = false;
		bool target_line = false;
	}
	namespace manipulator
	{
		bool manipulated = false;
		int desyncmode = 0;
		Vector3 m_manipulate = Vector3::Zero();
		float desync = 0.0f;
		bool manipulator = false;
		int manipulatorkey = 0;
		bool desyncindicator = false;
		float maxdesyncfloat = 0.6f;
		bool burstshot = false;
	}
	namespace flyhack
	{
		bool flyhack = false;
		bool flyhackindicator = false;
		bool antiflyhack = false;
		float flyhackfloat = 0.f;
		float hor_flyhack = 0.f;
	}
	namespace visuals
	{
		bool names = false;
		bool wounded = false;
		bool teamid = false;
		bool box = false;
		int boxstyle = 0;
		bool healtbar = false;
		bool distance = false;
		int distanceposition = 0;
		bool sleepers = false;
		bool skeleton = false;
		bool friendlycoloroverride = false;
		bool outofarrrows = false;
		bool helditems = false;
		int itemnametype = 0;
		bool chams = false;
		int chamstype = 0;
		bool radar = false;
		bool looking_direction = false;
		bool npc = false;
		bool enemycoloroverride = false;
		bool nightambientmultiplier = false;
		float nightambient = 0.5f;
		float npccolor[] = { 1.f, 1.f,1.f ,1.f };
		float sleeperscolor[] = { 0.5f, 0.5f,0.5f ,1.f };
		float playercolor[] = { 1.f, 1.f,1.f ,1.f };
		float chamsvisible[] = { 0.f, 1.f,1.f ,1.f };
		float chamsinvisible[] = { 1.f, 0.f,0.f ,1.f };
		float teameate[] = { 0.f, 1.f,0.f ,1.f };
		float ambientcolor[] = { 0.8f, 0.8f, 0.8f, 0.8f };
		float itemschamsvisible[] = { 0.f, 1.f,1.f ,1.f };
		float itemschamsinvisible[] = { 1.f, 0.f,0.f ,1.f };
		float handchams[] = { 0.f, 1.f,1.f ,1.f };
		float weaponchams[] = { 0.f, 1.f,1.f ,1.f };
		bool SkyChanger = false;
		float SkyCol[] = { 0.f,1.f,0.f,1.f };
	}
	namespace objects
	{
		bool ores = false;
		bool helicorper = false;
		bool corpses = false;
		bool clad = false;
		bool droppeditems = false;
		bool debug = false;
		bool home = false;
		bool stashes = false;
		bool traps = false;
		bool hemp = false;
		bool vehicles = false;
		bool raidesp = false;
	}
	namespace other
	{
		bool can_insta = false;
		int acrestrict = 0;
		Vector3 BulletPos = Vector3(0, 0, 0);
	}
}

uintptr_t game_assembly = 0;
uintptr_t discord_hook = 0;
uintptr_t unity_player = 0;