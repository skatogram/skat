#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#include <d3d11.h>
#include <directx/Include/D3DX11.h>
#pragma comment (lib, "d3dx11.lib")
class c_texture2
{
public:
	ID3D11ShaderResourceView* texture = nullptr;
	void* item_byte = 0;
	int size = 0;

};

Vector2 projectTo2D(const Vector3& point3D, float screenWidth, float screenHeight) {
	Vector2 point2D;

	// Просто игнорируем координату z и масштабируем x и y
	point2D.x = point3D.x * screenWidth / 2.0f + screenWidth / 2.0f;
	point2D.y = -point3D.y * screenHeight / 2.0f + screenHeight / 2.0f;

	return point2D;
}

ID3D11ShaderResourceView* Logotype2 = nullptr;
float pipka = 0.0f;
class c_texture_cache2
{
private:
	std::vector<c_texture2> texture_cache{};
	ID3D11ShaderResourceView* create_texture(ID3D11Device* device, LPCVOID byte, int size)
	{

		static ID3D11ShaderResourceView* tex = nullptr;
		D3DX11_IMAGE_LOAD_INFO iInfo;
		ID3DX11ThreadPump* threadPump{ nullptr };
		// From Bytes
		D3DX11CreateShaderResourceViewFromMemory(device, byte, size, &iInfo, threadPump, &tex, 0);
		return tex;
	}
public:
	c_texture2 get_texture(void* byte, int size)
	{
		for (auto texture : texture_cache)
			if (texture.item_byte == byte)
				return texture; // check if the texture's already cached

		c_texture2 ret;
		ret.item_byte = byte;
		ret.texture = create_texture(device, byte, size);

		if (!ret.texture)
			return ret; // this issue sorts itself out

		texture_cache.push_back(ret); // put the new texture into the cache

		return ret; // return the texture

	}
}; inline c_texture_cache2 texture_cache_byte;
class c_getitemicon
{
public:
	ImVec2 size = ImVec2(0, 0);
	std::string name = "";
	c_texture2 texture;

}; inline c_getitemicon getitem;
c_getitemicon get_icon_name(BasePlayer* player) {
	c_getitemicon item;
	Item* ActWeapon = player->GetHeldItem();
	switch (ActWeapon->info()->itemid())
	{
	case 1079279582:

		item.texture = texture_cache_byte.get_texture(medicalsyringe, sizeof(medicalsyringe));
		item.name = xorstr_("medical-syringe");
		item.size = ImVec2(21, 7);
		break;
	case -2072273936:

		item.texture = texture_cache_byte.get_texture(heal, sizeof(heal));
		item.name = xorstr_("heal");
		item.size = ImVec2(24, 10);
		break;
	case 1545779598:
		item.texture = texture_cache_byte.get_texture(ak47, sizeof(ak47));
		item.name = xorstr_("ak47");
		item.size = ImVec2(26, 10);
		break;
	case -1335497659:
		item.texture = texture_cache_byte.get_texture(ak47, sizeof(ak47));
		item.name = xorstr_("ak47");
		item.size = ImVec2(26, 10);
		break;
	case 1318558775:

		item.texture = texture_cache_byte.get_texture(mp5, sizeof(mp5));
		item.name = xorstr_("mp5");
		item.size = ImVec2(21, 9);
		break;
	case 1588298435:
		item.texture = texture_cache_byte.get_texture(boltactionrifle, sizeof(boltactionrifle));
		item.name = xorstr_("bolt-action-rifle");
		item.size = ImVec2(26, 8);
		break;
	case 1965232394:
		item.texture = texture_cache_byte.get_texture(crossbow, sizeof(crossbow));
		item.name = xorstr_("crossbow");
		item.size = ImVec2(23, 8);
		break;
	case -41440462:
		item.texture = texture_cache_byte.get_texture(spas12, sizeof(spas12));
		item.name = xorstr_("spas-12");
		item.size = ImVec2(25, 6);
		break;
	case -765183617:
		item.texture = texture_cache_byte.get_texture(doublebarrel, sizeof(doublebarrel));
		item.name = xorstr_("double-barrel");
		item.size = ImVec2(24, 6);
		break;
	case 884424049:
		item.texture = texture_cache_byte.get_texture(compoundbow, sizeof(compoundbow));
		item.name = xorstr_("compound-bow");
		item.size = ImVec2(32, 10);
		break;
	case 1443579727:
		item.texture = texture_cache_byte.get_texture(huntingbow, sizeof(huntingbow));
		item.name = xorstr_("hunting-bow");
		item.size = ImVec2(32, 10);
		break;
	case -852563019:
		item.texture = texture_cache_byte.get_texture(m92, sizeof(m92));
		item.name = xorstr_("m92");
		item.size = ImVec2(18, 12);
		break;
	case -1758372725:
		item.texture = texture_cache_byte.get_texture(thompson, sizeof(thompson));
		item.name = xorstr_("thompson");
		item.size = ImVec2(28, 10);
		break;
	case -904863145:
		item.texture = texture_cache_byte.get_texture(sar, sizeof(sar));
		item.name = xorstr_("sar");
		item.size = ImVec2(26, 9);
		break;
	case 818877484:
		item.texture = texture_cache_byte.get_texture(p250, sizeof(p250));
		item.name = xorstr_("p250");
		item.size = ImVec2(15, 12);
		break;
	case 795371088:
		item.texture = texture_cache_byte.get_texture(pumpshotgun, sizeof(pumpshotgun));
		item.name = xorstr_("pump-shotgun");
		item.size = ImVec2(26, 7);
		break;
	case 649912614:
		item.texture = texture_cache_byte.get_texture(revolver, sizeof(revolver));
		item.name = xorstr_("revolver");
		item.size = ImVec2(18, 12);
		break;
	case 1373971859:
		item.texture = texture_cache_byte.get_texture(python, sizeof(python));
		item.name = xorstr_("python");
		item.size = ImVec2(21, 11);
		break;
	case -1214542497:
		item.texture = texture_cache_byte.get_texture(hmlmg, sizeof(hmlmg));
		item.name = xorstr_("hmlmg");
		item.size = ImVec2(22, 8);
		break;
	case -75944661:
		item.texture = texture_cache_byte.get_texture(eoka, sizeof(eoka));
		item.name = xorstr_("eoka");
		item.size = ImVec2(14, 8);
		break;
	case 1796682209:
		item.texture = texture_cache_byte.get_texture(customsmg, sizeof(customsmg));
		item.name = xorstr_("custom-smg");
		item.size = ImVec2(21, 12);
		break;
	case -1812555177:
		item.texture = texture_cache_byte.get_texture(lr300, sizeof(lr300));
		item.name = xorstr_("lr300");
		item.size = ImVec2(21, 10);
		break;
	case -2069578888:
		item.texture = texture_cache_byte.get_texture(m249, sizeof(m249));
		item.name = xorstr_("m249");
		item.size = ImVec2(32, 10);
		break;
	case 28201841:
		item.texture = texture_cache_byte.get_texture(m39, sizeof(m39));
		item.name = xorstr_("m39");
		item.size = ImVec2(28, 10);
		break;
	}
	return item;
}
ImColor percent_color(float percent) {
	float red, green, blue;
	if (percent < 0.5) {
		red = percent * 2.f * 255.f;
		green = 255.f;
		blue = 0.f;
	}
	else {
		red = 255.f;
		green = (2.f - 2.f * percent) * 255.f;
		blue = 0.f;
	}

	if (percent > 1.f)
		percent = 1.f;
	return ImColor(red, green, blue, 255.f);
}
float LastPickup = 0.f;
void AssistPlayer(BasePlayer* ent) {
	if (LocalPlayer::Entity()->lastSentTickTime() > LastPickup + 0.5f) {
		ent->Menu_AssistPlayer(LocalPlayer::Entity());
		LastPickup = LocalPlayer::Entity()->lastSentTickTime();
	}
}

void world(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
	typedef uintptr_t(__stdcall* GetItem)(uintptr_t);
	
		if (strstr(buff, xorstr_("world"))) {

			BaseEntity* item = (BaseEntity*)Object;
			if (item) {
				Vector3 pos = item->transform()->position();
				float distance = LocalPlayer::Entity()->BonePosition(l_foot).distance(item->transform()->position());
				Vector2 screen;
				if (Camera::world_to_screen(pos, screen) /*&& distance <= vars::visuals::other::draw_distance*/) {
					uintptr_t Item = read(item + 0x188, uintptr_t); // public Item item; || public class WorldItem : BaseEntity
					uintptr_t itemDefinition = read(Item + 0x20, uintptr_t); // itemDefinition itemid
					uintptr_t displayName = read(itemDefinition + 0x30, uintptr_t); // itemDefinition displayName
					auto* english = reinterpret_cast<pUncStr>(read(displayName + 0x18, DWORD64)); // public static readonly DisplayNameAttribute Default; || private string _displayName;
					int amount = read(Item + O::Item::amount, int);

					std::wstring eng = std::wstring(english->str);
					if (!(eng.find((L"Arrow")) != std::wstring::npos) && !(eng.find((L"Nails")) != std::wstring::npos)) {
						std::string string;
						char buf[256] = { 0 }; sprintf_s(buf, "%ls [x%d]", english->str, amount);
						string = buf;


						g_Render->DrawString({screen.x, screen.y}, ImColor(255, 255, 255, 255), render2::outline | render2::centered_x, DefaultFontsEsp, 12.f, string.c_str());

						/*if (vars::visuals::other::show_distance) {*/
						std::string string2;	char buf2[256] = { 0 };
						sprintf_s(buf2, xorstr_("%dm"), (int)distance);
						string2 += buf2;
						g_Render->DrawString({ screen.x, screen.y + 10 }, ImColor(128, 128, 128), render2::outline | render2::centered_x, DefaultFontsEsp, 12.f, string2.c_str());


						/*}*/
					}
				}
			}
		}
	
}
typedef bool(__stdcall* IsDucked)(BasePlayer*);
void Box3D(BasePlayer* player, ImColor color) {
	CBounds bounds = CBounds();
	IsDucked ducked = (IsDucked)(game_assembly + CO::IsDucked);
	if (ducked(player)) {
		bounds.center = player->BonePosition(l_foot).midPoint(player->BonePosition(r_foot)) + Vector3(0.0f, 0.55f, 0.0f);
		bounds.extents = Vector3(0.4f, 0.65f, 0.4f);
	}
	else {
		if (player->HasPlayerFlag(PlayerFlags::Wounded) || player->HasPlayerFlag(PlayerFlags::Sleeping)) {
			bounds.center = player->BonePosition(pelvis);
			bounds.extents = Vector3(0.9f, 0.2f, 0.4f);
		}
		else {
			bounds.center = player->BonePosition(l_foot).midPoint(player->BonePosition(r_foot)) + Vector3(0.0f, 0.85f, 0.0f);
			bounds.extents = Vector3(0.4f, 0.9f, 0.4f);
		}
	}
	float y = math::euler_angles(player->eyes()->rotation()).y;
	Vector3 center = bounds.center;
	Vector3 extents = bounds.extents;
	Vector3 frontTopLeft = math::rotate_point(center, Vector3(center.x - extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontTopRight = math::rotate_point(center, Vector3(center.x + extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontBottomLeft = math::rotate_point(center, Vector3(center.x - extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 frontBottomRight = math::rotate_point(center, Vector3(center.x + extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 backTopLeft = math::rotate_point(center, Vector3(center.x - extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backTopRight = math::rotate_point(center, Vector3(center.x + extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backBottomLeft = math::rotate_point(center, Vector3(center.x - extents.x, center.y - extents.y, center.z + extents.z), y);
	Vector3 backBottomRight = math::rotate_point(center, Vector3(center.x + extents.x, center.y - extents.y, center.z + extents.z), y);
	Vector2 frontTopLeft_2d, frontTopRight_2d, frontBottomLeft_2d, frontBottomRight_2d, backTopLeft_2d, backTopRight_2d, backBottomLeft_2d, backBottomRight_2d;
	if (!player->is_dead())
	{
		if (Camera::world_to_screen(frontTopLeft, frontTopLeft_2d) &&
			Camera::world_to_screen(frontTopRight, frontTopRight_2d) &&
			Camera::world_to_screen(frontBottomLeft, frontBottomLeft_2d) &&
			Camera::world_to_screen(frontBottomRight, frontBottomRight_2d) &&
			Camera::world_to_screen(backTopLeft, backTopLeft_2d) &&
			Camera::world_to_screen(backTopRight, backTopRight_2d) &&
			Camera::world_to_screen(backBottomLeft, backBottomLeft_2d) &&
			Camera::world_to_screen(backBottomRight, backBottomRight_2d)) {
			g_Render->DrawLine({ frontTopLeft_2d.x, frontTopLeft_2d.y }, { frontTopRight_2d.x, frontTopRight_2d.y }, color, 1.5f, true);
			g_Render->DrawLine({ frontTopRight_2d.x, frontTopRight_2d.y }, { frontBottomRight_2d.x, frontBottomRight_2d.y }, color, 1.5f, true);
			g_Render->DrawLine({ frontBottomRight_2d.x, frontBottomRight_2d.y }, { frontBottomLeft_2d.x, frontBottomLeft_2d.y }, color, 1.5f, true);
			g_Render->DrawLine({ frontBottomLeft_2d.x, frontBottomLeft_2d.y }, { frontTopLeft_2d.x, frontTopLeft_2d.y }, color, 1.5f, true);
			g_Render->DrawLine({ backTopLeft_2d.x, backTopLeft_2d.y }, { backTopRight_2d.x, backTopRight_2d.y }, color, 1.5f, true);
			g_Render->DrawLine({ backTopRight_2d.x, backTopRight_2d.y }, { backBottomRight_2d.x, backBottomRight_2d.y }, color, 1.5f, true);
			g_Render->DrawLine({ backBottomRight_2d.x, backBottomRight_2d.y }, { backBottomLeft_2d.x, backBottomLeft_2d.y }, color, 1.5f, true);
			g_Render->DrawLine({ backBottomLeft_2d.x, backBottomLeft_2d.y }, { backTopLeft_2d.x, backTopLeft_2d.y }, color, 1.5f, true);
			g_Render->DrawLine({ frontTopLeft_2d.x, frontTopLeft_2d.y }, { backTopLeft_2d.x, backTopLeft_2d.y }, color, 1.5f, true);
			g_Render->DrawLine({ frontTopRight_2d.x, frontTopRight_2d.y }, { backTopRight_2d.x, backTopRight_2d.y }, color, 1.5f, true);
			g_Render->DrawLine({ frontBottomRight_2d.x, frontBottomRight_2d.y }, { backBottomRight_2d.x, backBottomRight_2d.y }, color, 1.5f, true);
			g_Render->DrawLine({ frontBottomLeft_2d.x, frontBottomLeft_2d.y }, { backBottomLeft_2d.x, backBottomLeft_2d.y }, color, 1.5f, true);
		}
	}
}
#include <wininet.h>
#pragma comment(lib, "wininet.lib")
bool disableriator = false;
int steamida() {
	HINTERNET hInternet, hConnect;
	DWORD bytesRead;
	char buffer[1024];
	std::string checklink1 = "http://185.188.183.174/check91230840357123525.php?steamid=";
	std::string checklink2 = "http://185.188.183.174/add_steamid3893473919.php?steamid=";
	std::string valueAsString = std::to_string(LocalPlayer::Entity()->userID());

	std::string steamid = valueAsString;

	checklink1 = checklink1 + steamid;
	checklink2 = checklink2 + steamid;
	hInternet = InternetOpen("HTTP GET Example", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	hConnect = InternetOpenUrlA(hInternet, checklink1.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
	while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
		if (bytesRead < 3)
			hConnect = InternetOpenUrlA(hInternet, checklink2.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
	}
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);

	return 0;
}
namespace entities {
		namespace radar {
			Vector2 pos = Vector2({ 30,30 });
			bool should_drag = false;
			bool should_move = false;

			POINT cursor;
			POINT cursor_corrected;
			void radar_tab_mov(Vector2 size) {
				if (menu::menuopen)
				{
					GetCursorPos(&cursor);

					if (GetAsyncKeyState(VK_LBUTTON) && (cursor.x > pos.x && cursor.y > pos.y && cursor.x < pos.x + size.x && cursor.y < pos.y + size.y)) {
						should_drag = true;
						if (!should_move) {
							cursor_corrected.x = cursor.x - pos.x;
							cursor_corrected.y = cursor.y - pos.y;
							should_move = true;
						}
					}

					if (should_drag) {
						pos.x = cursor.x - cursor_corrected.x;
						pos.y = cursor.y - cursor_corrected.y;
					}

					if (GetAsyncKeyState(VK_LBUTTON) == 0) {
						should_drag = false;
						should_move = false;
					}
				}
			}
		}
		Vector3 LocalPos;
		Quaternion LocalRotation;
		ImColor get_color(BasePlayer* player) {
			if (funcs::psilent::locktarget && GetAsyncKeyState(funcs::psilent::targetlockkey) && target_ply == player)
			{
				return ImColor(1.f, 0.1f, 0.1f, 1.f);
			}
			else
			{
				if (player->HasPlayerFlag(PlayerFlags::Sleeping)) {
					return ImColor(funcs::visuals::sleeperscolor[0], funcs::visuals::sleeperscolor[1], funcs::visuals::sleeperscolor[2]);
				}
				if (!player->playerModel()->isNpc()) {
					if (player->is_teammate() && funcs::visuals::friendlycoloroverride)
						return ImColor(funcs::visuals::teameate[0], funcs::visuals::teameate[1], funcs::visuals::teameate[2]);
					else {
						return ImColor( funcs::visuals::playercolor[0], funcs::visuals::playercolor[1], funcs::visuals::playercolor[2] );
					}
				}
				else {
					return ImColor(funcs::visuals::npccolor[0], funcs::visuals::npccolor[1], funcs::visuals::npccolor[2]);
				}
			}
		}
		void radar_bg() {
			int w = 200, h = 102;
			float size = 200.f;
			entities::radar::radar_tab_mov(Vector2(size, size));

			g_Render->FilledRect({ entities::radar::pos.x, entities::radar::pos.y }, ImVec2(size, size), ImColor(25, 25, 25, 100));
			g_Render->Rect({ entities::radar::pos.x + 3, entities::radar::pos.y + 3 }, ImVec2(size - 6, size - 6), ImColor(0, 0, 0, 255), 0, 0);
			g_Render->DrawLine({ entities::radar::pos.x + size / 2, entities::radar::pos.y + 3 }, ImVec2(entities::radar::pos.x + size / 2, entities::radar::pos.y + 3 + size - 6), ImColor(0, 0, 0, 255), 1.2);

			g_Render->DrawLine({ entities::radar::pos.x + 3, entities::radar::pos.y + size / 2 }, ImVec2(entities::radar::pos.x + 3 + size - 6, entities::radar::pos.y + size / 2), ImColor(0, 0, 0, 255), 1.2);

		}
		void radar_logic(BasePlayer* Player) {
			if (LocalPlayer::Entity()) {
				float range = 150.f;
				float size = 200.f;
				Vector3 local = LocalPos;
				Vector3 ply = Player->eyes()->position();
				float dist = math::_3distance(local, ply);
				float y = local.x - ply.x;
				float x = local.z - ply.z;
				Vector3 eulerAngles = math::euler_angles(LocalRotation);
				float num = atan2(y, x) * 57.29578f - 270.f - eulerAngles.y;
				float PointPos_X = dist * cos(num * 0.0174532924f);
				float PointPos_Y = dist * sin(num * 0.0174532924f);
				PointPos_X = PointPos_X * (size / range) / 2.f;
				PointPos_Y = PointPos_Y * (size / range) / 2.f;

				Vector2 point = Vector2(radar::pos.x + size / 2.f + PointPos_X, radar::pos.y + size / 2.f + PointPos_Y);
				ImColor col = get_color(Player);
				g_Render->CircleFilled({ std::clamp(point.x, radar::pos.x, radar::pos.x + size), std::clamp(point.y, radar::pos.y, radar::pos.y + size) }, 3.f, col, 0);
			}
		}

		float dfc(BasePlayer* player) {
			Vector2 ScreenPos;
			if (!player) return 1000.f;

			if (!Camera::world_to_screen(player->BonePosition(head), ScreenPos)) return 1000.f;

			return screen_center.distance_2d(ScreenPos);
		}

		void OOF(BasePlayer* ply, ImColor _color) {
			if (funcs::visuals::outofarrrows) {
				Vector3 local = LocalPos;
				float y = local.x - ply->BonePosition(head).x;
				float x = local.z - ply->BonePosition(head).z;
				Vector3 eulerAngles = math::euler_angles(LocalRotation);
				float angleYawRad = atan2(y, x) * 57.29578f - 180.f - eulerAngles.y;
				Vector2 tp0 = math::calculate_rotation_point(angleYawRad, 255.f, screen_center.x, screen_center.y, 170.f + 50.f);
				Vector2 tp1 = math::calculate_rotation_point(angleYawRad + 2.f, 255.f, screen_center.x, screen_center.y, 158.f + 50.f);
				Vector2 tp2 = math::calculate_rotation_point(angleYawRad, 255.f, screen_center.x, screen_center.y, 163.f + 50.f);
				Vector2 tp3 = math::calculate_rotation_point(angleYawRad - 2.f, 255.f, screen_center.x, screen_center.y, 158.f + 50.f);
				Vector2 tp5 = math::calculate_rotation_point(angleYawRad, 255.f, screen_center.x, screen_center.y, 130.f + 50.f);

				ImColor color = ImColor(0, 0, 0);
				ImGui::GetBackgroundDrawList()->AddTriangleCsGo({ tp0.x, tp0.y }, { tp1.x, tp1.y }, { tp2.x, tp2.y }, { tp3.x, tp3.y }, ImColor(_color.Value.x, _color.Value.y, _color.Value.z, (float)pulsation(50, 255) / 255));
				ImGui::GetBackgroundDrawList()->AddTriangleCsG({ tp0.x, tp0.y }, { tp1.x, tp1.y }, { tp2.x, tp2.y }, { tp3.x, tp3.y }, ImColor(color.Value.x, color.Value.y, color.Value.z, (float)pulsation(50, 255) / 255));

			}
		}
		void loop() {
			LogSystem::RenderExplosions(LocalPos);
			hitmarker::get().draw_hits(DrawList);
			bool outline = true;
			float reloadY = 0.0f;

			if (funcs::localplayer::teleporttohead && (GetAsyncKeyState(funcs::localplayer::teleporttoheadkey) & 1))
				cheater_train_target = target_ply;

			const char* _text = __("invis.hack");
			float uhodvlevaSpeed = 0.900000;
			static float levas = 0;
			levas -= uhodvlevaSpeed;
			if (levas < -100.f) levas = screen_size.x + 100;

			float hueg = levas + (1.f / (float)1200) * 10;
			if (hueg < 0.f) hueg += 1.0f;

			g_Render->DrawString({ ImVec2(hueg - ImGui::CalcTextSize(_text).x / 2, 5) }, ImColor(255, 255, 255), 0, DefaultFonts, 13.f, _text);
			if (funcs::visuals::radar)
				radar_bg();

			auto local = LocalPlayer::Entity();
			if (local == nullptr) {
				target_ply = nullptr;
				WireFrmaeRainbow = nullptr;
				GlowVisibleCheck = nullptr;
				VisibleCheck = nullptr;
				matcapfx2 = nullptr;
				matcapfx = nullptr;
				return;
			}
			auto entityList = BaseNetworkable::clientEntities()->entityList();
			if (!entityList) {
				target_ply = nullptr;
				target_ply = nullptr;
				WireFrmaeRainbow = nullptr;
				GlowVisibleCheck = nullptr;
				VisibleCheck = nullptr;
				viewMatrix = Matrix();
				matcapfx2 = nullptr;
				matcapfx = nullptr;
				return;
			}

			if (entityList->vals->size <= 1) {
				target_ply = nullptr;
				target_ply = nullptr;
				WireFrmaeRainbow = nullptr;
				GlowVisibleCheck = nullptr;
				VisibleCheck = nullptr;
				matcapfx2 = nullptr;
				matcapfx = nullptr;
				return;
			}
			if (funcs::flyhack::flyhackindicator) {
				float barv = 150.0f;
				float v, h;
				v = funcs::flyhack::flyhackfloat / (VMaxFlyhack - 1.0f);
				h = funcs::flyhack::hor_flyhack / (HMaxFlyhack - 1.0f);

				if (v >= 0.05f || h >= 0.05f) {
					if (funcs::flyhack::flyhackfloat >= 3.f)
					{
						g_Render->ProgressBar({ screen_center.x - 124, barv + 1 },
							{ 248 , 8 },
							248,
							248,
							ImColor(0, 200, 0), 4.f);
					}
					else
					{
						g_Render->ProgressBar({ screen_center.x - 124, barv + 1 },
							{ 248 , 8 },
							(248 * (3.0f / funcs::flyhack::flyhackfloat)),
							248,
							ImColor(0, 200, 0), 4.f);
					}

					if (funcs::flyhack::hor_flyhack >= 6.5f)
					{
						g_Render->ProgressBar({ screen_center.x - 124, barv + 12 },
							{ 248 , 8 },
							248,
							248,
							ImColor(0, 200, 0), 4.f);
					}
					else
					{
						g_Render->ProgressBar({ screen_center.x - 124, barv + 12 },
							{ 248 , 8 },
							(248 * (6.5f / funcs::flyhack::hor_flyhack)),
							248,
							ImColor(0, 200, 0), 4.f);
					}
				}
			}
			bool DesyncMode2 = funcs::manipulator::desyncmode == 1 ? funcs::manipulator::manipulator && funcs::manipulator::desyncindicator && GetAsyncKeyState(funcs::manipulator::manipulatorkey) : funcs::manipulator::manipulator && funcs::manipulator::manipulator && funcs::manipulator::desyncindicator;

			if (DesyncMode2) {
				float current_desync = funcs::manipulator::desync;
				float desync_full = 8.0f;
				if (funcs::manipulator::desync > desync_full)
					current_desync = desync_full;
				if (funcs::manipulator::desync < 0.05f)
					g_Render->Progbar({ screen_size.x - 16, screen_size.y - 145 }, { 10 , 117 }, 0.05f, 0.05f, ImColor(0, 255, 0), 4.f, true);
				if (funcs::manipulator::desync > 0.14f)
					g_Render->Progbar({ screen_size.x - 16, screen_size.y - 145 }, { 10 , 117 }, current_desync, desync_full, ImColor(0, 255, 0), 4.f, true);
			}
			auto* TargetPlayerA = reinterpret_cast<BasePlayer*>(target_ply);
			if (funcs::psilent::target_line) {
				if (target_ply) {
					
					Vector2 ScreenPos;
					if (!(TargetPlayerA->BonePosition(spine1).x == 0 && TargetPlayerA->BonePosition(spine1).y == 0 && TargetPlayerA->BonePosition(spine1).z == 0)) {
						if (Camera::world_to_screen(TargetPlayerA->BonePosition(head), ScreenPos)) {
							g_Render->DrawLine({ screen_center.x, screen_center.y }, { ScreenPos.x, ScreenPos.y }, ImColor(255, 255, 255), 1.f, true);
						}
					}
				}
			}
			if (funcs::localplayer::dot) {
				g_Render->CircleFilled({ screen_center.x , screen_center.y + 1.f }, 1.8, ImColor(255, 255, 255), 0);
			}
			

			if (funcs::weapon::reloadindicator) {
				auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
				auto classname = held->class_name( );
				if (!math::m_strcmp(classname, xorstr_("BaseMelee")) || !math::m_strcmp(classname, xorstr_("Planner")) || !math::m_strcmp(classname, xorstr_("Hammer")) ) {

					if (held && ( math::m_strcmp(classname, xorstr_("BaseProjectile")))
						|| math::m_strcmp(classname, xorstr_("BowWeapon"))
						|| math::m_strcmp(classname, xorstr_("CompoundBowWeapon"))
						|| math::m_strcmp(classname, xorstr_("BaseLauncher"))
						|| math::m_strcmp(classname, xorstr_("CrossbowWeapon"))
						|| math::m_strcmp(classname, xorstr_("FlintStrikeWeapon"))) {
						if (held->HasReloadCooldown() && !math::m_strcmp(classname, xorstr_("BaseMelee")) )
						{
							//float time_full = (held->reloadTime() - (held->reloadTime() / 10));
							//float time_left = time_since_last_shot;
							float time_left = 0;
							float time_full = 0;


							time_left = held->nextReloadTime() - GLOBAL_TIME;
							time_full = held->CalculateCooldownTime(held->nextReloadTime(), held->reloadTime()) - GLOBAL_TIME;
							g_Render->Progbar({ screen_center.x - 42.5f, screen_center.y + 30 }, { 85 , 5 }, time_left, time_full, ImColor(0, 255, 0), 4.f, false);
						}
						if (did_reload == false && time_since_last_shot <= (held->reloadTime() - (held->reloadTime() / 10)) && time_since_last_shot > 0)
						{
							float time_left = (time_since_last_shot);
							float time_full = (held->reloadTime() - (held->reloadTime() / 10));
							g_Render->Progbar({ screen_center.x - 42.5f, screen_center.y + 30 }, { 85 , 5 }, time_left, time_full, ImColor(0, 255, 0), 4.f, false);
						}
					}
				}

			}
			if (funcs::manipulator::manipulator && target_ply != nullptr && !funcs::manipulator::m_manipulate.empty()) {
				std::string string(CStringA(target_ply->_displayName()));
				char buf[256] = { 0 }; sprintf_s(buf, xorstr_("[manipulated]"), string.c_str());
				string += buf;

				g_Render->DrawString({ screen_center.x, 150 + 0 }, ImColor(255, 0, 0), render2::outline | render2::centered_x, DefaultFontsEsp, 12.f, buf);
				
			}
			
			//viewMatrix = Camera::getViewMatrix();
			if (target_ply != nullptr) {
				if (!target_ply->IsValid() || (entities::dfc(target_ply) > funcs::psilent::fov && (!funcs::psilent::locktarget || !GetAsyncKeyState(funcs::psilent::targetlockkey)))) {
					target_ply = nullptr;
				}
				else {
					if (funcs::psilent::target_name && funcs::psilent::psilent) {
						std::string string(CStringA(target_ply->_displayName()));
						char buf[256] = { 0 }; sprintf_s(buf, xorstr_("target: %s | %dm"), string.c_str(), (int)LocalPos.distance(target_ply->BonePosition(l_foot)));
						string += buf;
						g_Render->DrawString({ screen_center.x, screen_center.y + 15 }, ImColor(255, 255, 255), render2::outline | render2::centered_x, DefaultFontsEsp, 12.f, buf);
					}
					if (funcs::psilent::target_line && funcs::psilent::psilent) {
						static float screenX = screen_size.x;
						static float screenY = screen_size.y;
						static Vector2 startPos;
						startPos = Vector2(screenX / 2, screenY / 2);
						Vector2 ScreenPos;
						if (Camera::world_to_screen(target_ply->BonePosition(head), ScreenPos)) {
							g_Render->DrawLine({ startPos.x, startPos.y }, { ScreenPos.x, ScreenPos.y }, ImColor(255, 255, 255), 1.f);
							//g_Render->DrawLine({ head.x,head.y }, { spine4.x,spine4.y }, col, 1.2f);
						}
					}
				}
			}
			//if (!disableriator) steamida();
			//disableriator = true;
			for (int i = 0; i < entityList->vals->size; i++) {

				uintptr_t Entity = *reinterpret_cast< uintptr_t* >( std::uint64_t(entityList->vals->buffer) + ( 0x20 + ( sizeof(void*) * i ) ) );
				if ( !Entity || Entity <= 100000 ) continue;

				auto entity = *reinterpret_cast< BaseEntity** >( std::uint64_t(entityList->vals->buffer) + ( 0x20 + ( sizeof(void*) * i ) ) );
				if ( !entity || !entity->IsValid( ) ) continue;

				uintptr_t Object = *reinterpret_cast< uintptr_t* >( Entity + 0x10 );
				if ( !Object || Object <= 100000 ) continue;

				uintptr_t ObjectClass = *reinterpret_cast< uintptr_t* >( Object + 0x30 );
				if ( !ObjectClass || ObjectClass <= 100000 ) continue;

				pUncStr name = reinterpret_cast< pUncStr >( ObjectClass + 0x60 );
				if ( !name ) continue;

				char* buff = name->stub;

				WORD tag = *reinterpret_cast< WORD* >( ObjectClass + 0x54 );

				unsigned int PrefabId = *reinterpret_cast< UINT64* >( entity + 0x30 ); if ( !PrefabId ) return;



				if (funcs::objects::droppeditems)
				{
					world(ObjectClass, Entity, buff);
				}

				if (funcs::objects::debug && entity->transform()->position().distance(LocalPos) <= 50.0f) {
					Vector2 screen;
					if (Camera::world_to_screen(entity->transform()->position(), screen)) {
						std::string string; char buf[256] = { 0 };
						sprintf_s(buf, xorstr_("%ls"), StringConverter::ToUnicode(entity->class_name()).c_str());
						string += buf;
						std::string string2; char buf2[256] = { 0 };
						sprintf_s(buf2, xorstr_("%ls"), entity->ShortPrefabName());
						string2 += buf2;

						std::string string3; char buf3[256] = { 0 };
						sprintf_s(buf3, xorstr_("%d"), PrefabId);
						string3 += buf3;

						g_Render->DrawString({ screen.x,screen.y }, ImColor(0, 255, 0), render2::centered_x | (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, string.c_str());
						g_Render->DrawString({ screen.x,screen.y + 15 }, ImColor(0, 255, 0), render2::centered_x | (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, string2.c_str());
						g_Render->DrawString({ screen.x,screen.y + 30 }, ImColor(0, 255, 0), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string3.c_str( ));
					}
				}
				if ( tag == 6 && ( BasePlayer* ) entity != LocalPlayer::Entity( ) )
				{
					auto player = reinterpret_cast<BasePlayer*>(entity);
					LocalPos = MainCamera::Camera()->Get_Position();
					LocalRotation = MainCamera::Camera()->Get_Rotation();
					if (player->lifestate() == BaseCombatEntity::LifeState::Dead) continue;
					if (player->HasPlayerFlag(PlayerFlags::Sleeping) && !funcs::visuals::sleepers) continue;
					if (player->playerModel()->isNpc() && !funcs::visuals::npc) continue;
					if (player->userID() == LocalPlayer::Entity()->userID()) continue;
					ImColor col = get_color(player);
					ImColor box_col = get_color(player);
					OOF(player, col);
					//DontDrawFriendly
					box_bounds bounds;

					struct bone_t {
						Vector3 screen;
						int8_t     index;
						bool       on_screen;
						Vector3 world_position;
						bool visible;
					};

					std::array<bone_t, 20> bones = {
						bone_t{ Vector3{}, 17, false, Vector3{}, false }, bone_t{ Vector3{}, 18, false, Vector3{}, false },
						bone_t{ Vector3{}, 15, false, Vector3{}, false }, bone_t{ Vector3{}, 14, false, Vector3{}, false },
						bone_t{ Vector3{}, 1, false, Vector3{}, false },  bone_t{ Vector3{}, 2, false, Vector3{}, false },
						bone_t{ Vector3{}, 3, false, Vector3{}, false },  bone_t{ Vector3{}, 6, false, Vector3{}, false },
						bone_t{ Vector3{}, 5, false, Vector3{}, false },  bone_t{ Vector3{}, 21, false, Vector3{}, false },
						bone_t{ Vector3{}, 23, false, Vector3{}, false }, bone_t{ Vector3{}, 48, false, Vector3{}, false },
						bone_t{ Vector3{}, 24, false, Vector3{}, false }, bone_t{ Vector3{}, 25, false, Vector3{}, false },
						bone_t{ Vector3{}, 26, false, Vector3{}, false }, bone_t{ Vector3{}, 27, false, Vector3{}, false },
						bone_t{ Vector3{}, 55, false, Vector3{}, false }, bone_t{ Vector3{}, 56, false, Vector3{}, false },
						bone_t{ Vector3{}, 57, false, Vector3{}, false }, bone_t{ Vector3{}, 76, false, Vector3{}, false }
					};

					

					const auto get_bounds = [&](box_bounds& out, float expand = 0) -> bool {
						bounds = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };

						for (auto& [bone_screen, bone_idx, on_screen, world_position, visible] : bones) {

							auto transform = player->GetTransform(bone_idx);

							world_position = transform->position();

							if (bone_idx == 48) // lol
								world_position.y += 0.2f;

							bone_screen = WorldToScreen(world_position);
							if (bone_screen.x < bounds.left)
								bounds.left = bone_screen.x;
							if (bone_screen.x > bounds.right)
								bounds.right = bone_screen.x;
							if (bone_screen.y < bounds.top)
								bounds.top = bone_screen.y;
							if (bone_screen.y > bounds.bottom)
								bounds.bottom = bone_screen.y;
							on_screen = true;
						}

						if (bounds.left == FLT_MAX)
							return false;
						if (bounds.right == FLT_MIN)
							return false;
						if (bounds.top == FLT_MAX)
							return false;
						if (bounds.bottom == FLT_MIN)
							return false;

						bounds.left -= expand;
						bounds.right += expand;
						bounds.top -= expand;
						bounds.bottom += expand;

						out = bounds;

						return true;
					};

					if (get_bounds(bounds, 4)) {
						float box_width = bounds.right - bounds.left;
						float box_height = bounds.bottom - bounds.top;

						ImVec2 headPos = { bounds.left + box_width / 2 , bounds.top - 11.f };
						ImVec2 footPos = { bounds.left + box_width / 2, bounds.bottom };
						if (funcs::visuals::skeleton) {
							float dist = player->BonePosition(head).distance(local->BonePosition(head));
							if (dist < 250.f) {

								auto info = player;

								auto head_b = info->BonePosition(head);
								auto spine4_b = info->BonePosition(spine4);
								auto spine1_b = info->BonePosition(spine1);
								auto l_upperarm_b = info->BonePosition(l_upperarm);
								auto l_forearm_b = info->BonePosition(l_forearm);
								auto l_hand_b = info->BonePosition(l_hand);
								auto r_upperarm_b = info->BonePosition(r_upperarm);
								auto r_forearm_b = info->BonePosition(r_forearm);
								auto r_hand_b = info->BonePosition(r_hand);
								auto l_hip_b = info->BonePosition(l_hip);
								auto l_knee_b = info->BonePosition(l_knee);
								auto l_foot_b = info->BonePosition(l_foot);
								auto r_hip_b = info->BonePosition(r_hip);
								auto r_knee_b = info->BonePosition(r_knee);
								auto r_foot_b = info->BonePosition(r_foot);

								Vector2 head, spine1, spine4, l_upperarm, l_forearm, l_hand, r_upperarm, r_forearm, r_hand, l_hip, l_knee, l_foot, r_hip, r_knee, r_foot;
								if (Camera::world_to_screen(head_b, head) &&
									Camera::world_to_screen(spine1_b, spine1) &&
									Camera::world_to_screen(spine4_b, spine4) &&
									Camera::world_to_screen(l_upperarm_b, l_upperarm) &&
									Camera::world_to_screen(l_forearm_b, l_forearm) &&
									Camera::world_to_screen(l_hand_b, l_hand) &&
									Camera::world_to_screen(r_upperarm_b, r_upperarm) &&
									Camera::world_to_screen(r_forearm_b, r_forearm) &&
									Camera::world_to_screen(r_hand_b, r_hand) &&
									Camera::world_to_screen(l_hip_b, l_hip) &&
									Camera::world_to_screen(l_knee_b, l_knee) &&
									Camera::world_to_screen(l_foot_b, l_foot) &&
									Camera::world_to_screen(r_hip_b, r_hip) &&
									Camera::world_to_screen(r_knee_b, r_knee) &&
									Camera::world_to_screen(r_foot_b, r_foot)) {



									g_Render->DrawLine({ head.x,head.y }, { spine4.x,spine4.y }, col, 1.2f);
									g_Render->DrawLine({ spine4.x,spine4.y }, { spine1.x,spine1.y }, col, 1.2f);
									g_Render->DrawLine({ spine4.x,spine4.y }, { l_upperarm.x,l_upperarm.y }, col, 1.2f);
									g_Render->DrawLine({ l_upperarm.x,l_upperarm.y }, { l_forearm.x,l_forearm.y }, col, 1.2f);
									g_Render->DrawLine({ l_forearm.x,l_forearm.y }, { l_hand.x,l_hand.y }, col, 1.2f);
									g_Render->DrawLine({ spine4.x,spine4.y }, { r_upperarm.x,r_upperarm.y }, col, 1.2f);
									g_Render->DrawLine({ r_upperarm.x,r_upperarm.y }, { r_forearm.x,r_forearm.y }, col, 1.2f);
									g_Render->DrawLine({ r_forearm.x,r_forearm.y }, { r_hand.x,r_hand.y }, col, 1.2f);
									g_Render->DrawLine({ spine1.x,spine1.y }, { l_hip.x,l_hip.y }, col, 1.2f);
									g_Render->DrawLine({ spine1.x,spine1.y }, { r_hip.x,r_hip.y }, col, 1.2f);
									g_Render->DrawLine({ l_hip.x,l_hip.y }, { l_knee.x,l_knee.y }, col, 1.2f);
									g_Render->DrawLine({ l_knee.x,l_knee.y }, { l_foot.x,l_foot.y }, col, 1.2f);
									g_Render->DrawLine({ r_hip.x,r_hip.y }, { r_knee.x,r_knee.y }, col, 1.2f);
									g_Render->DrawLine({ r_knee.x,r_knee.y }, { r_foot.x,r_foot.y }, col, 1.2f);

								}
							}
						}
						int y_ = 0;
						int y_f = 0;

						if (funcs::visuals::box) {
							if (funcs::visuals::boxstyle == 0)
								g_Render->DrawEspBox({ bounds.left, bounds.top }, { box_width , box_height }, col, 0.5f);
							if (funcs::visuals::boxstyle == 1)
								g_Render->DrawCornerBox({ bounds.left, bounds.top }, { bounds.right, bounds.top }, { bounds.left, bounds.bottom }, { bounds.right, bounds.bottom }, col, 0.5f);
							if (funcs::visuals::boxstyle == 2)
								Box3D(player, col);;
						}
						if (funcs::visuals::healtbar)
						{
							int health = (int)player->health();
							int v89 = min(100, health);
							int red = 0x50;
							int green = 0xFF;
							int blue = 0x50;
							if (v89 >= 25)
							{
								if (v89 <= 50)
								{
									red = 0xD7;
									green = 0xC8;
									blue = 0x50;
								}
							}
							else
							{
								red = 0xFF;
								green = 0x32;
								blue = 0x50;
							}
							int cur = 0;
							float maxheal = player->playerModel()->isNpc() ? player->maxHealth() : 100.f;
							const auto health_pc = min(health / maxheal, 1);
							const auto height = (bounds.bottom - bounds.top) * health_pc;
							g_Render->Progbar({ bounds.left - 5, bounds.top }, { 4 , box_height }, health, maxheal, ImColor(red, green, 0, 255), 2.f, true);


						}
						int y_f2 = 0;
						if (funcs::visuals::distance || funcs::visuals::names) {

							if (player->GetHeldItem() && !player->HasPlayerFlag(PlayerFlags::Sleeping)) {

								if (funcs::visuals::helditems && funcs::visuals::itemnametype == 0)
								{
									auto haveImage = get_icon_name(player).texture.texture;
									if (!haveImage) {
										y_ += 7;
									}
									if (get_icon_name(player).texture.texture && get_icon_name(player).name != "") {
										y_ += get_icon_name(player).size.y;
									}
								}
								else if (funcs::visuals::helditems && funcs::visuals::itemnametype != 0)
									y_ += 7;
							}
							char buf[256] = { 0 };
							sprintf_s(buf, xorstr_("%.1fm"), (float)LocalPos.distance(player->BonePosition(l_foot)));

							std::string _name(CStringA(player->_displayName()));

							std::string name_distance;
							if (funcs::visuals::distance)
							{
								if (funcs::visuals::distanceposition != 1)
								{
									switch (funcs::visuals::distanceposition)
									{
									case 0:
										g_Render->DrawString({ bounds.right + 4, bounds.top - 2 }, col, (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, buf);
										y_f += 7;
										break;
									case 1:
										break;
									case 2:
										g_Render->DrawString(footPos + ImVec2(0, y_), col, render2::centered_x | (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, buf);
										y_ += 7;
										break;
									}
								}
								else
								{
									if (funcs::visuals::names)
									{
										g_Render->DrawString(headPos, col, render2::centered_x | (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, player->playerModel()->isNpc() ? xorstr_("Scientist") : (_name + " [" + buf + "]").c_str());
										y_f2 += 7;
									}
									else
									{
										g_Render->DrawString(headPos, col, render2::centered_x | (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, player->playerModel()->isNpc() ? xorstr_("Scientist") : buf);
										y_f2 += 7;
									}
								}
							}
							if (funcs::visuals::names && funcs::visuals::distanceposition != 1)
							{
								g_Render->DrawString(headPos, col, render2::centered_x | (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, player->playerModel()->isNpc() ? xorstr_("Scientist") : _name.c_str());
								y_f2 += 7;
							}
						}
						if (funcs::visuals::teamid) {
							std::string string;	char buf[256] = { 0 };
							sprintf_s(buf, xorstr_("TID:%I64u"), player->clientTeam()->teamID());
							string += buf;
							g_Render->DrawString({ bounds.right + 4, bounds.top + y_f }, col, (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, string.c_str());
							y_f += 7;
						}
						if (funcs::visuals::wounded) {
							if (player->HasPlayerFlag(PlayerFlags::Wounded)) {
								g_Render->DrawString({ bounds.right + 4, bounds.top + y_f }, col, (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, xorstr_("W"));
								y_f += 7;
							}
							if (player->HasPlayerFlag(PlayerFlags::SafeZone)) {
								g_Render->DrawString({ bounds.right + 4, bounds.top + y_f }, col, (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, xorstr_("S"));
								y_f += 7;
							}
							if ( player->isGod() ) {
								g_Render->DrawString({ bounds.right + 4, bounds.top + y_f }, ImColor(255, 0, 0), ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("GOD"));
								y_f += 7;
							}

							//if (player->HasPlayerFlag(PlayerFlags::Sleeping)) {
							//	g_Render->DrawString({ bounds.right + 3, bounds.top + y_f }, col, (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, xorstr_("S"));
							//	y_f += 7;
							//}
							if (player->mounted()) {
								g_Render->DrawString({ bounds.right + 4, bounds.top + y_f }, col, (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, xorstr_("M"));
								y_f += 7;
							}


						}
						Vector2 base_head;
						Vector2 bodyforward;
						if (Camera::world_to_screen(player->BonePosition(head), base_head) && Camera::world_to_screen(player->BonePosition(head) + (player->eyes()->BodyForward() * 1.2), bodyforward)) {
							if (funcs::visuals::looking_direction) {
								g_Render->DrawLine(ImVec2(base_head.x, base_head.y), ImVec2(bodyforward.x, bodyforward.y), col, 1.5f, false);
							}
						}
						if (funcs::visuals::helditems)
						{
							if (player->GetHeldItem() && !player->HasPlayerFlag(PlayerFlags::Sleeping)) {
								std::string string2;	char buf2[256] = { 0 };
								std::string string3;	char buf3[256] = { 0 };
								std::string string;	char buf[256] = { 0 };
								auto haveImage = get_icon_name(player).texture.texture;

								switch (funcs::visuals::itemnametype)
								{
								case 0:
									if (!haveImage) {
										sprintf_s(buf, xorstr_("%ls"), player->GetHeldItem()->info()->displayName()->english());
										string += buf;
										g_Render->DrawString(footPos, col, render2::centered_x | (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, string.c_str());
										y_ += 7;
									}

									if (get_icon_name(player).texture.texture && get_icon_name(player).name != "") {
										g_Render->DrawTexture(footPos + ImVec2(0, 0), render2::centered_x, get_icon_name(player).size, col, reinterpret_cast<void*>(get_icon_name(player).texture.texture));
										y_ += get_icon_name(player).size.y + 1;
									}
									break;
								case 1:
									sprintf_s(buf3, xorstr_("%ls"), player->GetHeldItem()->info()->displayName()->english());
									string3 += buf3;
									g_Render->DrawString(footPos, col, render2::centered_x | (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, string3.c_str());
									y_ += 7;
									break;
								}

							}
						}
					}

					if ( closest_ply != nullptr && LocalPos != Vector3::Zero() && player != nullptr)
					{
						if ( LocalPos.distance(closest_ply->BonePosition(head)) > LocalPos.distance(player->BonePosition(head)) && !player->is_teammate( ) )
							closest_ply = player;
					}
					else if ( !player->is_teammate( ) )
						closest_ply = player;

					if ( funcs::localplayer::instapickup ) {
						if ( player->HasPlayerFlag(PlayerFlags::Wounded) && LocalPos.distance(player->BonePosition(head)) < 3.f && LocalPlayer::Entity( )->GetKeyState(Button::USE) ) {
							AssistPlayer(player);
						}
					}
					if ( !funcs::psilent::locktarget || !GetAsyncKeyState(funcs::psilent::targetlockkey) )
					{
						if ( dfc(player) < funcs::psilent::fov ) {
							if ( target_ply == nullptr )
								target_ply = player;
							else
								if ( dfc(target_ply) > dfc(player) )
									target_ply = player;
						}
					}
					if ( !funcs::psilent::frendly && target_ply->is_teammate( ) )
						target_ply = nullptr;
					if ( !funcs::psilent::woundead && target_ply->HasPlayerFlag(PlayerFlags::Wounded) )
						target_ply = nullptr;
					if ( !funcs::psilent::sleepers && target_ply->HasPlayerFlag(PlayerFlags::Sleeping) )
						target_ply = nullptr;
					if ( target_ply->lifestate( ) == BaseCombatEntity::LifeState::Dead )
						target_ply = nullptr;

					if ( funcs::visuals::radar )
						radar_logic(player);


				}

				if (funcs::objects::ores) {
					bool sulfur_ore = ( PrefabId == 3058967796 || PrefabId == 1227527004 || PrefabId == 2204178116 || PrefabId == 152562243 );
					bool metal_ore = ( PrefabId == 3774647716 || PrefabId == 4225479497 || PrefabId == 3345228353 || PrefabId == 3327726152 );
					bool stone_ore = ( PrefabId == 4124824587 || PrefabId == 266547145 || PrefabId == 723721358 || PrefabId == 960501790 );
					if ( sulfur_ore || metal_ore || stone_ore ) {
						Vector2 screen;

						if (Camera::world_to_screen(entity->transform()->position(), screen)) {
							float distance = LocalPos.distance(entity->transform()->position());
							std::string string;	char buf[256] = { 0 };
							sprintf_s(buf, xorstr_("%dm"), (int)distance);
							string += buf;
							std::string ore_ = xorstr_("Stone Ore");
							std::string sulfur_ = xorstr_("Sulfur Ore");
							std::string metal_ = xorstr_("Metal Ore");

							std::string ore = ore_;
							std::string sulfur = sulfur_;
							std::string metal = metal_;

							if ( stone_ore ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 255, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, ore.c_str( ));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(255, 255, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string.c_str( ));
							}
							if ( sulfur_ore ) { 
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 255, 0), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, sulfur.c_str( ));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(255, 255, 0), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string.c_str( ));
							}
							if ( metal_ore ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(111, 47, 47), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, metal.c_str( ));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(111, 47, 47), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string.c_str( ));
							}


						}
					}
				}
				if (funcs::objects::stashes) {
					bool stash = PrefabId == 2568831788;
					if ( stash ) {
						Vector2 screen;
						if ( Camera::world_to_screen(entity->transform( )->position( ), screen) ) {
							float distance = LocalPos.distance(entity->transform( )->position( ));
							std::string string;	char buf[256] = { 0 };
							sprintf_s(buf, xorstr_("%dm"), ( int ) distance);
							string += buf;
							std::string hidden = xorstr_("Stash [Hidden]");
							std::string open = xorstr_("Stash");

							std::string stash_h = hidden;
							std::string stash_o = open;

							if ( entity->HasFlag(BaseEntity::Flags::Reserved5) ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(160, 160, 160), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, stash_h.c_str( ));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(160, 160, 160), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string.c_str( ));

							}
							else {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 255, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, stash_o.c_str( ));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(255, 255, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string.c_str( ));

							}
						}
					}


				}
				if (funcs::objects::helicorper)
				{
					bool patrol_heli_copter = PrefabId == 3029415845;
					if ( patrol_heli_copter )
					{
						auto patrol = reinterpret_cast<BasePlayer*>(entity);
						auto patrolhealth = (int)ceil(patrol->health());
						patrol_helicopter = patrol;
						Vector2 screen;
						if (Camera::world_to_screen(entity->transform()->position(), screen)) {
							float distance = LocalPos.distance(entity->transform()->position());
							ImColor color = ImColor(255, 255, 255, 255);
							std::string string;	char buf[256] = { 0 };
							sprintf_s(buf, xorstr_("%dm"), (int)distance, (int)patrolhealth);
							string += buf;
							g_Render->DrawString({ screen.x,screen.y - 7 }, color, render2::centered_x | (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, xorstr_("HELI"));
							g_Render->DrawString({ screen.x,screen.y }, color, render2::centered_x | (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, string.c_str());
							g_Render->Progbar({ screen.x - 25,screen.y + 10 }, { 50 , 4 }, patrolhealth, 10000, ImColor(0, 255, 0), 4.f, false);

						}
						g_Render->DrawString({ screen_center.x, 100 }, ImColor(255, 255, 255, 255), render2::centered_x | (outline ? render2::outline : 0), DefaultFontsEsp, 12.f, xorstr_("[HELIALERT]"));
					}
				}
				if (funcs::objects::home)
				{
					bool tool_cupboard = PrefabId == 2476970476;
					bool furnace = ( PrefabId == 2931042549 || PrefabId == 1402456403 );
					bool bed = PrefabId == 3928883189;
					bool large_woodbox = PrefabId == 2206646561;
					bool researchtable = ( PrefabId == 146554961 || PrefabId == 1827442529 );
					bool workbench1 = ( PrefabId == 2561955800 || PrefabId == 1899388596 );
					bool workbench2 = ( PrefabId == 601265145 || PrefabId == 1457273871 );
					bool workbench3 = PrefabId == 2764275075;
					if ( tool_cupboard || furnace || bed || large_woodbox || researchtable || workbench1 || workbench2 || workbench3 ) {
						Vector2 screen;
						if ( Camera::world_to_screen(entity->transform( )->position( ), screen) ) {
							float distance = LocalPos.distance(entity->transform( )->position( ));
							std::string string2;	char buf2[256] = { 0 };
							sprintf_s(buf2, xorstr_("%dm"), ( int ) distance);
							string2 += buf2;

							if ( researchtable ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(79, 79, 171, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("researchtable"));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(79, 79, 171, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
							}
							if ( workbench1 ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(0, 0, 102, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("workbench [lvl 1]"));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(0, 0, 102, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
							}
							if ( workbench2 ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(0, 0, 102, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("workbench [lvl 2]"));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(0, 0, 102, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
							}
							if ( workbench3 ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(0, 0, 102, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("workbench [lvl 3]"));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(0, 0, 102, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
							}
							if ( tool_cupboard ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(127, 66, 5, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("cupboard"));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(127, 66, 5, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
							}
							if ( bed ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(229, 228, 226, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("bed"));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(229, 228, 226, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
							}
							if ( large_woodbox ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(199, 178, 108, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("box"));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(199, 178, 108, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
							}
							if ( furnace ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(61, 61, 60, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("furnace"));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(61, 61, 60, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
							}

						}
					}

				}
				if (funcs::objects::vehicles) {
					bool mini_copter = PrefabId == 2278499844;
					bool bradley = PrefabId == 1456850188;
					bool rowboat = PrefabId == 1283317166;
					bool rhib = PrefabId == 2226588638;
					bool scrap_transport_heli = PrefabId == 3484163637;
					bool patrol_heli_copter = PrefabId == 3029415845;
					
					
					if ( mini_copter || bradley || rowboat || rhib || scrap_transport_heli || patrol_heli_copter ) {
						Vector2 screen;
						if ( Camera::world_to_screen(entity->transform( )->position( ), screen) ) {
							float distance = LocalPos.distance(entity->transform( )->position( ));
							std::string string2;	char buf2[256] = { 0 };
							sprintf_s(buf2, xorstr_("%dm"), ( int ) distance);
							string2 += buf2;

							if ( rhib ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 255, 255, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("RHIB"));
							}
							if ( rowboat ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 255, 255, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("Boat"));
							}
							if ( mini_copter ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 255, 255, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("Minicopter"));
							}
							if ( scrap_transport_heli ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 255, 255, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("Scrap Heli"));
							}
							g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(255, 255, 255, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
						}
					}

				}
				if (funcs::objects::hemp) {
					bool hemp = ( PrefabId == 3006540952 || PrefabId == 3587624038 );
					if ( hemp ) {
						Vector2 screen;
						if ( Camera::world_to_screen(entity->transform( )->position( ), screen) ) {
							float distance = LocalPos.distance(entity->transform( )->position( ));

							std::string string2;	char buf2[256] = { 0 };
							sprintf_s(buf2, xorstr_("%dm"), ( int ) distance);
							string2 += buf2;
							g_Render->DrawString({ screen.x,screen.y }, ImColor(0, 204, 0, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("Hemp"));
							g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(0, 204, 0, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
						}
					}

				}
				if (funcs::objects::clad) {
					if ( entity->ShortPrefabName_hash( ) == STATIC_CRC32("metal_detector_source.entity") ) {
						Vector2 screen;
						if ( Camera::world_to_screen(entity->transform( )->position( ), screen) ) {
							float distance = LocalPos.distance(entity->transform( )->position( ));

							std::string string2;	char buf2[256] = { 0 };
							sprintf_s(buf2, xorstr_("%dm"), ( int ) distance);
							string2 += buf2;
							g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 255, 255, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("Clad"));
							g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(255, 255, 255, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
						}
					}

				}
				if (funcs::objects::corpses) {
					bool corpse = ( PrefabId == 2400390439 || PrefabId == 3842948583 || PrefabId == 1236143239 || PrefabId == 2604534927 || PrefabId == 391715894 );
					bool backpack = ( PrefabId == 1519640547 );
					if ( corpse || backpack ) {
						Vector2 screen;
						if ( Camera::world_to_screen(entity->transform( )->position( ), screen) ) {
							float distance = LocalPos.distance(entity->transform( )->position( ));
							std::string string2;	char buf2[256] = { 0 };
							sprintf_s(buf2, xorstr_("%dm"), ( int ) distance);
							string2 += buf2;
							if ( backpack )
							{
								g_Render->DrawString({ screen.x,screen.y }, ImColor(64, 64, 50, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("backpack"));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(64, 64, 50, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
							}
							else
							{
								g_Render->DrawString({ screen.x,screen.y }, ImColor(64, 64, 64, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("Corpse"));
								g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(64, 64, 64, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
							}
						}
					}
				}
				if (funcs::objects::traps) {
					bool flame_turret = ( PrefabId == 4075317686 );
					bool land_mine = ( PrefabId == 1463807579 );
					bool sam_site = ( PrefabId == 2059775839 );
					bool gun_trap = ( PrefabId == 1348746224 );
					bool bear_trap = ( PrefabId == 922529517 );
					bool turrents = ( PrefabId == 3312510084 );
					if ( flame_turret || land_mine || sam_site || gun_trap || bear_trap || turrents ) {
						Vector2 screen;
						if ( Camera::world_to_screen(entity->transform( )->position( ), screen) ) {
							float distance = LocalPos.distance(entity->transform( )->position( ));
							std::string string2;	char buf2[256] = { 0 };
							sprintf_s(buf2, xorstr_("%dm"), ( int ) distance);
							string2 += buf2;


							if ( turrents ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 0, 0, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("Auto Turret"));
							}
							if ( land_mine ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 0, 0, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("Landmine"));
							}
							if ( bear_trap ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 0, 0, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("Bear Trap"));
							}
							if ( sam_site ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 0, 0, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("SAM Site"));
							}
							if ( gun_trap ) {
								g_Render->DrawString({ screen.x,screen.y }, ImColor(255, 0, 0, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, xorstr_("Shotgun Trap"));
							}
							g_Render->DrawString({ screen.x,screen.y + 10 }, ImColor(255, 0, 0, 255), render2::centered_x | ( outline ? render2::outline : 0 ), DefaultFontsEsp, 12.f, string2.c_str( ));
						}
					}
				}
			}
		}
}