
static inline ImVec2  operator*(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
static inline ImVec2  operator/(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
static inline ImVec2  operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2  operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2  operator*(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline ImVec2  operator/(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
static inline ImVec2& operator*=(ImVec2& lhs, const float rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const float rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
static inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
static inline ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
static inline ImVec2& operator*=(ImVec2& lhs, const ImVec2& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const ImVec2& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }
static inline ImVec4  operator+(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
static inline ImVec4  operator-(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
static inline ImVec4  operator*(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

static float pulsation(float minVal, float maxVal, float speed = 2) {
	static float startTime = -1.0f; // Начальное время анимации
	if (startTime < 0.0f) {
		startTime = ImGui::GetTime(); // Установить начальное время, если оно не установлено
	}

	float currentTime = ImGui::GetTime(); // Текущее время
	float elapsedTime = fmod(currentTime - startTime, 2.0f / speed); // Прошедшее время с учетом скорости

	// Вычислить текущее значение анимации на основе прошедшего времени
	if (elapsedTime < 1.0f / speed) {
		return minVal + elapsedTime * speed * (maxVal - minVal);
	}
	else {
		return maxVal - (elapsedTime - 1.0f / speed) * speed * (maxVal - minVal);
	}
}

ImFont* DefaultFonts;
ImFont* DefaultFontsEsp;
ImFont* BigDefaultFonts;
ImFont* SmallDefaultFonts;
ImVec2 pos;
ImDrawList* draw;
int tab_count = 0;
#define __ xorstr_

std::vector<std::string> config_list{};
std::vector<std::string> empty_list = { xor_str("Config folder is empty!") };

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


void generalmenu() //разделение на войды чтобы компил был быстрее
{
	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Основное") : __("Main"), (ImVec2(237, 480)));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Аим") : __("Aim"), &funcs::psilent::psilent);
			if (funcs::psilent::autoshottype == 1) 
				ImGui::Keybind(menu::rus ? __(u8"Бинд Аимбота") : __("Aim bind"), &funcs::psilent::key, 0);
			ImGui::Checkbox(menu::rus ? __(u8"Аим хелпер") : __("Aim Helper"), &funcs::weapon::aimhelper);
			if ( funcs::weapon::aimhelper )
			{
				ImGui::Checkbox(menu::rus ? __(u8"Показывать траекторию") : __("Show Trajectory"), &funcs::weapon::showtrajectory);
			}
			ImGui::Combo(menu::rus ? __(u8"Точка Аиминга") : __("Aim Spot"), &funcs::psilent::a_spot, menu::rus ? __(u8"Голова\0Тело\0Случайная\0Случайная без головы\0Голова/Тело\0") : __("Head\0Body\0Random All\0Random with no head\0Head / Body\0"));
			ImGui::Checkbox(menu::rus ? __(u8"Рисовать радиус фова") : __("Draw Fov Circle"), &funcs::psilent::drawfov);
			if (funcs::psilent::drawfov)
			{
				ImGui::ColorEdit4(menu::rus ? __(u8"Цвет фова") : __("Fov Color"), (float*)&funcs::psilent::fovcolor, ImGuiColorEditFlags_NoInputs);
			}
			ImGui::SliderFloat(menu::rus ? __(u8"Фов") : __("Fov"), &funcs::psilent::fov, 0.f, 2500.f, __("%.2f"));
			ImGui::Combo(menu::rus ? __(u8"Включить автошот если") : __("Autoshot enable if"), &funcs::psilent::autoshottype, menu::rus ? __(u8"Выключен\0При зажатии бинда аима\0При зажатии манипулятора\0") : __("Disabled\0If aim bind pressed\0If manipulator pressed\0"));
			ImGui::Checkbox(menu::rus ? __(u8"Изменение хитбокса") : __("Hitbox Override"), &funcs::weapon::hitoverride);
			if (funcs::weapon::hitoverride)
				ImGui::Combo(menu::rus ? __(u8"Менять хитбокс на") : __("Override Hitbox"), &funcs::weapon::hitboxoverride, menu::rus ? __(u8"Выключен\0Голова\0Тело\0Случайный\0Случайный без головы\0Голова/Тело\0") : __("Disabled\0Head\0Body\0Random All\0Random with no head\0Head/body\0"));
			ImGui::Checkbox(menu::rus ? __(u8"Приоритетная цель") : __("Target lock"), &funcs::psilent::locktarget);
			if (funcs::psilent::locktarget)
				ImGui::Keybind(menu::rus ? __(u8"Бинд приоритета") : __("Targen lock bind"), &funcs::psilent::targetlockkey, 0);
			ImGui::Checkbox(menu::rus ? __(u8"Имя таргета") : __("Target Name"), &funcs::psilent::target_name);
			ImGui::Checkbox(menu::rus ? __(u8"Линия до таргета") : __("Target Line"), &funcs::psilent::target_line);
			ImGui::Checkbox(menu::rus ? __(u8"Буллет Телепорт на вертолёт") : __("Patrol Heli bullet tp"), &funcs::weapon::helimagic);
			ImGui::Checkbox(menu::rus ? __(u8"Максимальный урон вертолёту") : __("Patrol Heli max damage"), &funcs::weapon::patrolhelihitboxoverride);
			ImGui::Checkbox(menu::rus ? __(u8"Аим хелпер") : __("Aim Helper"), &funcs::weapon::aimhelper);
			ImGui::Checkbox(menu::rus ? __(u8"Прострел сквозь объекты") : __("Penetrate available objects"), &funcs::weapon::pierce);
		}
		ImGui::EndChild();
	}
	ImGui::EndGroup();

	ImGui::SameLine();

	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Цель") : __("Targeting"), ImVec2(237, 140));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Таргетить спящих") : __("Target Sleepers"), &funcs::psilent::sleepers);
			ImGui::Checkbox(menu::rus ? __(u8"Таргетить раненых") : __("Target Woundead"), &funcs::psilent::woundead);
			ImGui::Checkbox(menu::rus ? __(u8"Таргетить тиммейтов") : __("Target Friendly"), &funcs::psilent::frendly);
		}
		ImGui::EndChild();

		ImGui::BeginChild(menu::rus ? __(u8"Манипулятор ") : __("Manipulator "), ImVec2(237, 325));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Манипулятор") : __("Manipulator"), &funcs::manipulator::manipulator);
			ImGui::Combo(menu::rus ? __(u8"Включение манипулятора") : __("Manipulator enable"), &funcs::manipulator::desyncmode, menu::rus ? __(u8"Всегда\0На бинд\0") : __("Always\0On Key\0"));
			if (funcs::manipulator::desyncmode == 1) {
				ImGui::Keybind(menu::rus ? __(u8"Манипулятор бинд") : __("Manipulator Key"), &funcs::manipulator::manipulatorkey, 0);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Выстрелить неск. пуль") : __("Burst Shot"), &funcs::manipulator::burstshot);
			ImGui::Checkbox(menu::rus ? __(u8"Индикатор манипулятора") : __("Desync indicator"), &funcs::manipulator::desyncindicator);
			ImGui::SliderFloat(menu::rus ? __(u8"Максимальный радиус") : __("Max Radius"), &funcs::manipulator::maxdesyncfloat, 0.05f, 1.f, __("%.2f"));
		}
		ImGui::EndChild();
	}
	ImGui::EndGroup();

	ImGui::SameLine();

	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Оружие") : __("Weapon"), ImVec2(237, 480));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Настройка отдачи") : __("Recoil control"), &funcs::weapon::recoilas);
			if (funcs::weapon::recoilas)
			{
				ImGui::SliderFloat(menu::rus ? __(u8"Отдача") : __("Recoil"), &funcs::weapon::norecoil, 0.f, 100.f, __("%.2f"));
				ImGui::SliderFloat(menu::rus ? __(u8"Разброс") : __("Spread"), &funcs::weapon::spread, 0.f, 1.f, __("%.2f"));
			}	
			ImGui::Checkbox(menu::rus ? __(u8"Скорость пули") : __("Bullet Velocity"), &funcs::weapon::lowvelocity);
			if (funcs::weapon::lowvelocity) {
				ImGui::SliderFloat(menu::rus ? __(u8"скорость") : __("Velocity"), &funcs::weapon::bulletspeed, 0.1f, 1.5f);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Момент. Йока") : __("Instant Eoka"), &funcs::weapon::instaeoka);
			ImGui::Checkbox(menu::rus ? __(u8"Быстрый лук") : __("Fast Bow"), &funcs::weapon::fastbow);
			ImGui::Checkbox(menu::rus ? __(u8"Быстрая блочка") : __("Instant Compound Charge"), &funcs::weapon::instchargecompound);
			ImGui::Checkbox(menu::rus ? __(u8"Быстрая стрельба") : __("Rapid Fire"), &funcs::weapon::rapidfire);
			ImGui::Checkbox(menu::rus ? __(u8"Автоматик") : __("Force Automatic Fire"), &funcs::weapon::automatic);
			//ImGui::Checkbox(menu::rus ? __(u8"Скипать дистацию пули") : __("Projectile Skip"), &funcs::weapon::vlonetpeleport);
			ImGui::Checkbox(menu::rus ? __(u8"Телепорт пули в игрока") : __("Bullet Teleport"), &funcs::weapon::bulletteleport);
			if (funcs::weapon::bulletteleport)
			{
				ImGui::Checkbox(menu::rus ? __(u8"Сканирование цели") : __("Hitscan"), &funcs::weapon::hitscan);
				if (funcs::weapon::hitscan)
				{
					ImGui::Checkbox(menu::rus ? __(u8"Сканирование манипулятором") : __("Manipulator scan"), &funcs::weapon::manipulatorhitscan);
					//ImGui::Combo(menu::rus ? __(u8"тип сканирования") : __("Bullet TP Scan"), &funcs::weapon::hitscantype, menu::rus ? __(u8"минимальные углы\0средние углы\0максимальные углы\0") : __("Default\0Average\0Extended\0"));
				}
				//ImGui::Checkbox(menu::rus ? __(u8"фикс антиаима") : __("antiaimfix"), &funcs::weapon::antiaimfix);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Большая пуля") : __("Thick Bullet"), &funcs::weapon::thickbullet);
			ImGui::Checkbox(menu::rus ? __(u8"Траектория пули") : __("Bullet tracer"), &funcs::weapon::bullettracer);
			if (funcs::weapon::bullettracer)
			{
				ImGui::ColorEdit4(menu::rus ? __(u8"Цвет траектории пули") : __("Bullet Tracer Color"), (float*)&funcs::weapon::bullettracercol, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Изменение хитматериала") : __("Change hitmaterial"), & funcs::weapon::hitmaterial);
			ImGui::Checkbox(menu::rus ? __(u8"Интересный рисунок киянкой") : __("Hamer Draw =)"), & funcs::weapon::hamerdrawing);
			ImGui::Checkbox(menu::rus ? __(u8"Фейк выстрелы") : __("Fake Shots"), & funcs::weapon::fakeshots);
			if (funcs::weapon::fakeshots)
			{
				ImGui::Keybind(menu::rus ? __(u8"Бинд фейк выстрелов") : __("Fake Shots Key"), &funcs::weapon::fakeshotskey, 0);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Хитсаунд") : __("Hitsound"), & funcs::weapon::customhitsound);
		}
		ImGui::EndChild();
	}
	ImGui::EndGroup();
}

void projectilemenu()
{
	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Передвижение") : __("Movement"), ImVec2(237, 480));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Админка") : __("FakeAdmin"), &funcs::localplayer::fakeadmin);
			if (funcs::localplayer::fakeadmin)
			{
				ImGui::Checkbox(menu::rus ? __(u8"Если настоящий админ") : __("If true admin"), &funcs::localplayer::istrueadmin);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Быстрый лут") : __("InstaLoot"), &funcs::localplayer::instaloot);
			ImGui::Checkbox(menu::rus ? __(u8"Ходьба по воде") : __("Walk on water"), &funcs::localplayer::walkonwater);
			ImGui::Checkbox(menu::rus ? __(u8"Бесконечный прыжок") : __("Infinity Jump"), &funcs::localplayer::nojumprestriction);
			ImGui::Checkbox(menu::rus ? __(u8"Лазанье по стенам") : __("Spiderman"), &funcs::localplayer::spiderman);
			ImGui::Checkbox(menu::rus ? __(u8"Убрать дамаг от падения") : __("No Fall Damage"), &funcs::localplayer::nofalldamage);
			ImGui::Checkbox(menu::rus ? __(u8"Бег во все стороны") : __("Omni-Sprint"), &funcs::localplayer::nosprintrestriction);
			if (funcs::localplayer::nosprintrestriction)
			{
				ImGui::Checkbox(menu::rus ? __(u8"Cпидхак") : __("Speedhack"), &funcs::localplayer::speedhack);
				if (funcs::localplayer::speedhack)
				{
					ImGui::SliderFloat(menu::rus ? __(u8"Cкорость спидхака") : __("Speedhack %"), &funcs::localplayer::speedhackfloat, 0.f, 100.f, __("%.2f"));
					ImGui::Keybind(menu::rus ? __(u8"Rнопка скорости") : __("Speedhack key"), &funcs::localplayer::speedhackkey, 0);
				}
			}
			ImGui::Checkbox(menu::rus ? __(u8"Флайхак индикатор") : __("Flyhack indicator"), &funcs::flyhack::flyhackindicator);
			ImGui::Checkbox(menu::rus ? __(u8"Антикик флайхака") : __("Anti FlyHack Kick"), &funcs::flyhack::antiflyhack);
			if (funcs::flyhack::antiflyhack)
			{
				ImGui::Keybind(menu::rus ? __(u8"Игнор стопера") : __("Stopper ignoring"), &funcs::localplayer::ignoreanyfly, 0);
			}
			
			ImGui::Checkbox(menu::rus ? __(u8"Убрать колизию") : __("No Collision"), &funcs::localplayer::noplayercollision);

			ImGui::Checkbox(menu::rus ? __(u8"Интерактив дебаг") : __("Interactive Debug"), &funcs::localplayer::interactivedebug);
			if (funcs::localplayer::interactivedebug)
			{
				ImGui::Keybind(menu::rus ? __(u8"Кнопка дебага") : __("Debug key"), &funcs::localplayer::interactivedebugkey, 0);
			}

			ImGui::Checkbox(menu::rus ? __(u8"Телепорт на голову") : __("TP to Head Player"), &funcs::localplayer::teleporttohead);
			if (funcs::localplayer::teleporttohead)
			{
				ImGui::Keybind(menu::rus ? __(u8"Бинд телепорта") : __("Tp key  "), &funcs::localplayer::teleporttoheadkey, 0);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Держать оружие всегда") : __("Can Hold Items"), &funcs::localplayer::noattackrestriction);
			ImGui::Checkbox(menu::rus ? __(u8"Изменять гравитацию") : __("Change gravity"), &funcs::localplayer::gravity);
			if (funcs::localplayer::gravity)
			{
				ImGui::SliderFloat(menu::rus ? __(u8"Гравитация") : __("Gravity float"), &funcs::localplayer::gravityfloat, 0.f, 3.f);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Убрать Тряску рук") : __("Remove Bob"), &funcs::localplayer::removebob);
			ImGui::Checkbox(menu::rus ? __(u8"Убрать Опускание рук") : __("Remove Lower"), &funcs::localplayer::removelower);
			ImGui::Checkbox(menu::rus ? __(u8"Убрать анимацию стрельбы") : __("Remove Attack Anim"), &funcs::localplayer::removeattackanim);
		}
		ImGui::EndChild();
	}
	ImGui::EndGroup();
	ImGui::SameLine();

	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Визуалы") : __("Visuals"), ImVec2(237, 480));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Прицел") : __("Crosshair"), &funcs::localplayer::dot);
			ImGui::Checkbox(menu::rus ? __(u8"Хитмаркер") : __("Hitmarker"), &funcs::localplayer::hitmarker);
			ImGui::Checkbox(menu::rus ? __(u8"Маркер урона") : __("Damage Marker"), &funcs::localplayer::damagemarker);
			ImGui::Checkbox(menu::rus ? __(u8"Кастомный фов") : __("Custom fov"), &funcs::localplayer::customerfov);
			if (funcs::localplayer::customerfov)
			{
				ImGui::SliderFloat(menu::rus ? __(u8"фов") : __("FOV Changer"), &funcs::localplayer::fov, 0.f, 130.f, __("%.2f"));
				ImGui::Checkbox(menu::rus ? __(u8"Приближение") : __("Zoom Hack"), &funcs::localplayer::zoomhack);
				if (funcs::localplayer::zoomhack)
				{
					ImGui::Keybind(menu::rus ? __(u8"Кнопка активации") : __("Zoom"), &funcs::localplayer::zoom, 0);
					ImGui::SliderFloat(menu::rus ? __(u8"Увеличить на") : __("Zoom Hack Amount"), &funcs::localplayer::zoomamount, 1.f, 15.f, __("%.2f"));
				}
			}
			ImGui::Checkbox(menu::rus ? __(u8"Телепорт сфера") : __("Visual Sphere"), &funcs::localplayer::teleportsphere);
			if (funcs::localplayer::teleportsphere)
			{
				ImGui::Keybind(menu::rus ? __(u8"Кнопка телепорта") : __("Teleport button"), &funcs::localplayer::teleportspherekey, 0);
				ImGui::ColorEdit4(menu::rus ? __(u8"Цвет сферы") : __("Sphere Color"), (float*)&funcs::localplayer::teleportspherecol, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Траектория движения") : __("Movement line"), &funcs::localplayer::movementline);
			if (funcs::localplayer::movementline)
			{
				ImGui::ColorEdit4(menu::rus ? __(u8"цвет траектории") : __("Mov line color"), (float*)&funcs::localplayer::movementlinecol, ImGuiColorEditFlags_NoInputs);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Изменять модельку") : __("Modelstate changer"), &funcs::localplayer::modelstate);
			if (funcs::localplayer::modelstate)
			{
				ImGui::Combo(menu::rus ? __(u8"Тип модели") : __("Modelstate type"), & funcs::localplayer::modelstatetype, menu::rus ? __(u8"на лестнице\0лежачий\0на земле\0") : __("OnLadder\0Ducked\0OnGround\0"));
			}
			ImGui::Checkbox(menu::rus ? __(u8"Заливка рук") : __("Hands chams"), &funcs::localplayer::heandchams);
			if (funcs::localplayer::heandchams)
			{
				ImGui::Combo(menu::rus ? __(u8"Тип заливки") : __("View Model Hand Chams"), &funcs::localplayer::handchamstype, menu::rus ? __(u8"Фрейм\0Видимые/невидимые\0Видимые/невидимые 2\0Триппи\0Золотые\0") : __("WireFrame\0Solid Glow Visible/Invisible\0Solid Visible/Invisible\0Trippy\0Golden Transparent\0"));
				if (funcs::localplayer::handchamstype == 1 || funcs::localplayer::handchamstype == 2) {
					ImGui::ColorEdit4(menu::rus ? __(u8"цвет заливки") : __("Hand chams Color"), (float*)&funcs::visuals::handchams, ImGuiColorEditFlags_NoInputs);
				}
			}
			ImGui::Checkbox(menu::rus ? __(u8"Заливка оружия") : __("Weapon chams"), &funcs::localplayer::weaponchams);
			if (funcs::localplayer::weaponchams)
			{
				ImGui::Combo(menu::rus ? __(u8"тип заливки оружия") : __("View Model Weapon Chams"), &funcs::localplayer::weaponchamstype, menu::rus ? __(u8"Фрейм\0Видимые/невидимые\0Видимые/невидимые 2\0Триппи\0Золотые\0") : __("WireFrame\0Solid Glow Visible/Invisible\0Solid Visible/Invisible\0Trippy\0Golden Transparent\0"));
				if (funcs::localplayer::weaponchamstype == 2 || funcs::localplayer::weaponchamstype == 3) {
					ImGui::ColorEdit4(menu::rus ? __(u8"цвет оружия") : __("Gun chams Color"), (float*)&funcs::visuals::weaponchams, ImGuiColorEditFlags_NoInputs);
				}
			}
			ImGui::Checkbox(menu::rus ? __(u8"Самоубийство") : __("Suicide"), & funcs::localplayer::suicide);
			if (funcs::localplayer::suicide)
			{
				ImGui::Keybind(menu::rus ? __(u8"бинд кила") : __("Suicide bind"), &funcs::localplayer::die, 0);
			}
			/*ImGui::Checkbox(menu::rus ? __(u8"Сдвиг экрана") : __("AspectRatio"), & funcs::localplayer::aspect);
			if (funcs::localplayer::aspect)
			{
				ImGui::SliderFloat(menu::rus ? __(u8"Значение") : __("AspectRatio float"), & funcs::localplayer::aspectvalue, 0.1f, 5.f);
			}*/
		}
		ImGui::EndChild();

	}
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Авто-функции") : __("Automatic"), ImVec2(237, 480));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Авто прыжки") : __("Bhop"), & funcs::localplayer::bhop);
			if (funcs::localplayer::bhop)
			{
				ImGui::Keybind(menu::rus ? __(u8"кнопка прыжков") : __("Bhop key"), &funcs::localplayer::bhopkey, 0);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Авто хил") : __("Instaheal"), &funcs::localplayer::instaheal);
			ImGui::Checkbox(menu::rus ? __(u8"Авто поднятие игроков") : __("Insta Pickup Player"), & funcs::localplayer::instapickup);
			ImGui::Checkbox(menu::rus ? __(u8"Авто поднятие предметов") : __("AutoCollect"), & funcs::localplayer::autocollect);
			ImGui::Checkbox(menu::rus ? __(u8"Авто фарм") : __("SilentFarm"), & funcs::localplayer::silentfarm);
			ImGui::Checkbox(menu::rus ? __(u8"Анти аим") : __("AntiAim"), & funcs::localplayer::antiaim);
			
			ImGui::Checkbox(menu::rus ? __(u8"Авто перезарядка") : __("Auto Reload"), & funcs::weapon::silentreload);
			if (funcs::weapon::silentreload)
			{
				ImGui::Checkbox(menu::rus ? __(u8"индикатор перезарядки") : __("Reload indicator"), & funcs::weapon::reloadindicator);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Фейк лаги") : __("Fake lags"), & funcs::weapon::fakelags1);
			if (funcs::weapon::fakelags1) {
				ImGui::SliderFloat(menu::rus ? __(u8"Лаги") : __("Lags"), &funcs::localplayer::lagsam, 0.4f, 0.8f);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Лутать стеши") : __("Slient loot stash"), & funcs::weapon::silestlootstash);
			//ImGui::Checkbox(menu::rus ? __(u8"Лутать трупы") : __("Slient loot Corpse"), & funcs::weapon::silestlootcorpes);
			ImGui::Checkbox(menu::rus ? __(u8"Разминировать мины") : __("Slient loot mine"), & funcs::weapon::silestlootmine);

			ImGui::Checkbox(menu::rus ? __(u8"Авто атака с ближних орудий") : __("Silent Melee"), & funcs::weapon::silentmelee);
			if (funcs::weapon::silentmelee)
			{
				ImGui::Checkbox(menu::rus ? __(u8"Радиус ближней атаки") : __("Melee atack radius"), & funcs::weapon::meleeradius);
				if (funcs::weapon::meleeradius)
				{
					ImGui::Combo(menu::rus ? __(u8"тип круга") : __("Circle type"), & funcs::weapon::meleeradiustype, menu::rus ? __(u8"полосы\0исчезновение\0rgb\0") : __("stripes\0disappearing\0rgb\0"));
				}
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndGroup();
}

void miscmenu()
{
	
	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Игроки") : __("Player"), ImVec2(237, 480));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Имя") : __("Names"), &funcs::visuals::names);
			ImGui::Checkbox(menu::rus ? __(u8"Флаги") : __("Flags"), &funcs::visuals::wounded);
			ImGui::Checkbox(menu::rus ? __(u8"Айди тимы") : __("Team ID"), &funcs::visuals::teamid);
			ImGui::Checkbox(menu::rus ? __(u8"Бокс") : __("Box"), &funcs::visuals::box);
			if (funcs::visuals::box)
			{
				ImGui::Combo(menu::rus ? __(u8"Тип квадрата") : __("Box style"), &funcs::visuals::boxstyle, menu::rus ? __(u8"Квадрат\0Корер\0 3д\0") : __("Box\0Corner\0 3D box\0"));
			}
			ImGui::Checkbox(menu::rus ? __(u8"Хп бар") : __("HealthBar"), &funcs::visuals::healtbar);
			ImGui::Checkbox(menu::rus ? __(u8"Дистанция") : __("Distance"), &funcs::visuals::distance);
			if (funcs::visuals::distance)
			{
				ImGui::Combo(menu::rus ? __(u8"Позиция дистанции") : __("Distance Position"), &funcs::visuals::distanceposition, menu::rus ? __(u8"Справа\0Сверху\0Снизу\0") : __("Box Right\0Box Up\0Box Bottom\0"));
			}
			
			ImGui::Checkbox(menu::rus ? __(u8"Скелет") : __("Skeleton"), &funcs::visuals::skeleton);

			ImGui::Checkbox(menu::rus ? __(u8"Активное оружие") : __("Active item"), &funcs::visuals::helditems);
			if (funcs::visuals::helditems)
			{
				ImGui::Combo(menu::rus ? __(u8"Тип отображения") : __("Item Name Type"), &funcs::visuals::itemnametype, menu::rus ? __(u8"Иконки\0Мини название\0Дефолт\0") : __("Icons\0Short Name\0Default\0"));
			}
			ImGui::Checkbox(menu::rus ? __(u8"Направление взгляда") : __("Looking Direction"), &funcs::visuals::looking_direction);
			ImGui::Checkbox(menu::rus ? __(u8"Чамсы") : __("Chams"), &funcs::visuals::chams);
			if (funcs::visuals::chams)
			{
				ImGui::Combo(menu::rus ? __(u8"Тип чамсов") : __("Type Chams"), &funcs::visuals::chamstype, menu::rus ? __(u8"Фрейм\0Видимые/невидимые\0Видимые/невидимые 2\0Триппи\0Золотые\0") : __("WireFrame\0Solid Glow Visible/Invisible\0Solid Visible/Invisible\0Trippy\0Golden Transparent\0"));
				if (funcs::visuals::chamstype == 1 || funcs::visuals::chamstype == 2) {
					ImGui::ColorEdit4(menu::rus ? __(u8"Цвет видимых") : __("Visible Color"), (float*)&funcs::visuals::chamsvisible, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4(menu::rus ? __(u8"Цвет невидимых") : __("Invisible Color"), (float*)&funcs::visuals::chamsinvisible, ImGuiColorEditFlags_NoInputs);
				}
			}

			ImGui::Checkbox(menu::rus ? __(u8"Спящие") : __("Sleepers"), &funcs::visuals::sleepers);
			
			ImGui::Checkbox(menu::rus ? __(u8"Боты") : __("Npc"), &funcs::visuals::npc);
		}
		ImGui::EndChild();

	}

	ImGui::EndGroup();

	ImGui::SameLine();
	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Остальное") : __(" Other"), ImVec2(237, 232));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Кастомное время") : __("Custom Time"), &funcs::localplayer::customtime);
			if (funcs::localplayer::customtime)
			{
				ImGui::SliderFloat(menu::rus ? __(u8"время") : __("Time"), &funcs::localplayer::timechander, -1.f, 12.f);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Изменять цвет земли") : __("Change Night	 Color"), &funcs::localplayer::ambient);
			if (funcs::localplayer::ambient)
			{
				ImGui::ColorEdit4(menu::rus ? __(u8"цвет земли") : __("Ambient Color"), (float*)&funcs::visuals::ambientcolor, ImGuiColorEditFlags_NoInputs);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Ночной цвет") : __("Night Ambient"), &funcs::visuals::nightambientmultiplier);
			if (funcs::visuals::nightambientmultiplier)
			{
				ImGui::SliderFloat(menu::rus ? __(u8"цвет ночи") : __("night color"), &funcs::visuals::nightambient, 0.f, 10.f);
			}

			ImGui::Checkbox(menu::rus ? __(u8"Цветное небо") : __("Colored sky"), &funcs::visuals::SkyChanger);
			if (funcs::visuals::SkyChanger)
			{
				ImGui::ColorEdit4(menu::rus ? __(u8"Цвет неба") : __("Sky Color"), (float*)&funcs::visuals::SkyCol, ImGuiColorEditFlags_NoInputs);
			}
			ImGui::Checkbox(menu::rus ? __(u8"Радар") : __("Radar"), &funcs::visuals::radar);
			ImGui::Checkbox(menu::rus ? __(u8"Стрелочки") : __("Out Of Fov Arrows"), &funcs::visuals::outofarrrows);
		}
		ImGui::EndChild();

		ImGui::BeginChild(menu::rus ? __(u8"Цвета") : __("Colors"), ImVec2(237, 233));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Изменять цвет людей") : __("Enemy Color Override"), &funcs::visuals::enemycoloroverride);
			if (funcs::visuals::enemycoloroverride)
			{
				ImGui::ColorEdit4(menu::rus ? __(u8"Цвет игрока") : __("Player Color"), (float*)&funcs::visuals::playercolor, ImGuiColorEditFlags_NoInputs);
			}
			ImGui::ColorEdit4(menu::rus ? __(u8"Цвет спящих") : __("Sleepers Color"), (float*)&funcs::visuals::sleeperscolor, ImGuiColorEditFlags_NoInputs);

			ImGui::ColorEdit4(menu::rus ? __(u8"Цвет нпс") : __("Npc Color"), (float*)&funcs::visuals::npccolor, ImGuiColorEditFlags_NoInputs);
			
			ImGui::Checkbox(menu::rus ? __(u8"Изменять цвет тиммейтов") : __("Friendly Color Override"), &funcs::visuals::friendlycoloroverride);
			if (funcs::visuals::friendlycoloroverride)
			{
				ImGui::ColorEdit4(menu::rus ? __(u8"Цветь тиммейтов") : __("Friendly Color"), (float*)&funcs::visuals::teameate, ImGuiColorEditFlags_NoInputs);
			}
		}
		ImGui::EndChild();

	}
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
	{

		ImGui::BeginChild(menu::rus ? __(u8"Объекты") : __("Objects"), ImVec2(237, 480));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Камни") : __("Ore"), &funcs::objects::ores);
			ImGui::Checkbox(menu::rus ? __(u8"Трупы") : __("Corpses"), &funcs::objects::corpses);
			ImGui::Checkbox(menu::rus ? __(u8"Клады (мега)") : __("Clad"), &funcs::objects::clad);
			ImGui::Checkbox(menu::rus ? __(u8"патрульный вертолёт") : __("patrol helicorper"), &funcs::objects::helicorper);
			ImGui::Checkbox(menu::rus ? __(u8"Выпавший предмет") : __("Dropped Items"), &funcs::objects::droppeditems);
			ImGui::Checkbox(menu::rus ? __(u8"Конопля") : __("Hemp"), &funcs::objects::hemp);
			ImGui::Checkbox(menu::rus ? __(u8"Стеш") : __("Stashes"), &funcs::objects::stashes);
			ImGui::Checkbox(menu::rus ? __(u8"Ловушки") : __("Traps"), &funcs::objects::traps);
			ImGui::Checkbox(menu::rus ? __(u8"Транспорт") : __("Vehicles"), &funcs::objects::vehicles);
			ImGui::Checkbox(menu::rus ? __(u8"Рейды") : __("Raid Esp"), &funcs::objects::raidesp);
			ImGui::Checkbox(menu::rus ? __(u8"Дебаг") : __("Debug"), &funcs::objects::debug);
			ImGui::Checkbox(menu::rus ? __(u8"Обьекты дома") : __("Home Objects"), &funcs::objects::home);
		}
		ImGui::EndChild();

	}
	ImGui::EndGroup();
}

void cfgmenu()
{
	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Функции") : __("Funcs"), ImVec2(237, 480));
		{
			ImGui::Checkbox(menu::rus ? __(u8"Русский язык") : __("Russian language"), &menu::rus);
			//ImGui::SliderFloat(menu::rus ? __(u8"Desync forgiveness") : __("Desync forgiveness"), &funcs::weapon::dsfv, 0.0f, 3.5f);
			ImGui::Combo(menu::rus ? __(u8"Обход Античита") : __("ServerSide AC Restrictions"), &funcs::other::acrestrict, menu::rus ? __("without\0XAntiCheat\0") : __("without\0XAntiCheat\0"));
			if (ImGui::Button(menu::rus ? __(u8"Выгрузить чит") : __("Unload Cheat")))
				menu::unload = true;
		}
		ImGui::EndChild();

	}
	ImGui::EndGroup();

	ImGui::SameLine();

	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Луа") : __("Lua"), ImVec2(237, 480));
		{

		}
		ImGui::EndChild();

	}
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Конфиг") : __("Configs"), ImVec2(237, 480));
		{
			if (ImGui::BeginListBox("List Box Cfg", ImGui::GetWindowSize() - ImVec2(32, 260)))
			{
				for (auto cfg : config::GetConfigList())
					if (ImGui::Selectable(cfg.c_str(), cfg == selected_cfg))
						selected_cfg = cfg;

				ImGui::EndListBox();
			}

			ImGui::InputText(xorstr_("Config name"), config_name, 256);
			if (ImGui::Button(xorstr_("Create"))) {
				config::create(config_name);
				refresh_configs();
			}
			if (ImGui::Button(xorstr_("Load"))) {
				config::load(selected_cfg.c_str());
			}
			if (ImGui::Button(xorstr_("Save"))) {
				config::create(selected_cfg.c_str());
			}
			if (ImGui::Button(xorstr_("Delete"))) {
				config::erase(selected_cfg.c_str());
				refresh_configs();
			}
			if (ImGui::Button(xorstr_("Open Folder"))) {
				static TCHAR path[MAX_PATH]{};
				std::string folder = "";
				if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path))) {
					folder = std::string(path) + xorstr_("\\invis.v2\\");
				}
				ShellExecuteA(NULL, NULL, folder.c_str(), NULL, NULL, SW_SHOWNORMAL);
			}
		}
		ImGui::EndChild();

	}
	ImGui::EndGroup();
}

void settingsmenu()
{
	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"Цвет окна") : __("window color"), ImVec2(237, 480));
		{
			ImGui::ColorEdit4(menu::rus ? __(u8"Обводка меню") : __("window background"), (float*)&colors::window_background, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"контур меню") : __("window outline"), (float*)&colors::window_outline, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"Правая сторона") : __("right side"), (float*)&colors::window_right_side, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"правый текст") : __("group text"), (float*)&colors::window_group_text, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"обводка чилдов") : __("child background"), (float*)&colors::child_background, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"контур наводки чилдов") : __("child outline hovered"), (float*)&colors::child_outline_hovered, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"контур чилдов") : __("child outline default"), (float*)&colors::child_outline_default, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"текст при наведении") : __("child text hovered"), (float*)&colors::child_text_hovered, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"текст чилдов") : __("child text default"), (float*)&colors::child_text_default, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"текст активных табов") : __("tab text active"), (float*)&colors::tab_text_active, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"текст наведённых табов") : __("tab text hovered"), (float*)&colors::tab_text_hovered, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"текст табов") : __("tab text default"), (float*)&colors::tab_text_default, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			/*if (ImGui::ColorEdit4(menu::rus ? __(u8"UI Цвет") : __("UI Color"), color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview))
			{
				colors::accent.x = color[0];
				colors::accent.y = color[1];
				colors::accent.z = color[2];
			}*/
		}
		ImGui::EndChild();

	}
	ImGui::EndGroup();

	ImGui::SameLine();

	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"в меню") : __("in menu"), ImVec2(237, 480));
		{
			ImGui::ColorEdit4(menu::rus ? __(u8"текст чебоксов") : __("checkbox text"), (float*)&colors::checkbox_text, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"круг чебоксов") : __("checkbox circle"), (float*)&colors::checkbox_circle, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"квадрат чебоксов") : __("checkbox rect"), (float*)&colors::checkbox_rect, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"текст слайдеров") : __("slider text"), (float*)&colors::slider_text, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"значение слайдеров") : __("slider value"), (float*)&colors::slider_value, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"круг слайдеров") : __("slider circle"), (float*)&colors::slider_circle, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"квадрат слайдеров") : __("slider rect"), (float*)&colors::slider_rect, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

			ImGui::ColorEdit4(menu::rus ? __(u8"текст комбов") : __("combo text"), (float*)&colors::combo_text, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"стрелка комбов") : __("combo arrow"), (float*)&colors::combo_arrow, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"обводка комбов") : __("combo outline"), (float*)&colors::combo_outline, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"квадрат комбов") : __("combo rect"), (float*)&colors::combo_rect, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"окно комбов") : __("combo window"), (float*)&colors::combo_window, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

			ImGui::ColorEdit4(menu::rus ? __(u8"выбраный текст активен") : __("selectable text active"), (float*)&colors::selectable_text_active, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"выбраный текст") : __("selectable text default"), (float*)&colors::selectable_text_default, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

			ImGui::ColorEdit4(menu::rus ? __(u8"квадрат ввода") : __("input rect"), (float*)&colors::input_rect, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"текст ввода") : __("input text"), (float*)&colors::input_text, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"буфер ввода") : __("input buf"), (float*)&colors::input_buf, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

			ImGui::ColorEdit4(menu::rus ? __(u8"текст кнопки") : __("button text"), (float*)&colors::button_text, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"обводка кнопки") : __("button outline"), (float*)&colors::button_outline, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"квадрат кнопки") : __("button rect"), (float*)&colors::button_rect, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

			ImGui::ColorEdit4(menu::rus ? __(u8"обводка листа") : __("list outline"), (float*)&colors::list_outline, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"квадрат листа") : __("list rect"), (float*)&colors::list_rect, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

			ImGui::ColorEdit4(menu::rus ? __(u8"обводка эдитацвета") : __("color outline"), (float*)&colors::color_outline, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"квадрат эдитацвета") : __("color rect"), (float*)&colors::color_rect, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"текст эдитацвета") : __("color text"), (float*)&colors::color_text, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

			ImGui::ColorEdit4(menu::rus ? __(u8"текст бинда") : __("key text"), (float*)&colors::key_text, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"обводка бинда") : __("key outline"), (float*)&colors::key_outline, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"квадрат бинда") : __("key rect"), (float*)&colors::key_rect, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"окно бинда") : __("key window"), (float*)&colors::key_window, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(menu::rus ? __(u8"обводка окна бинда") : __("key window outline"), (float*)&colors::key_window_outline, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

		}
		ImGui::EndChild();

	}
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
	{
		ImGui::BeginChild(menu::rus ? __(u8"фон") : __("bground"), ImVec2(237, 480));
		{
			//ImGui::Combo(menu::rus ? __(u8"фон") : __("background"), &menu::background, menu::rus ? __(u8"круги\0дождь\0") : __("dotdraw\0rain\0"));

		}
		ImGui::EndChild();

	}
	ImGui::EndGroup();
}
int visibleCharacters = 0;
float animationTime = 0.0f;
void MainMenu()
{
	ImGui::SetNextWindowSize(ImVec2(925, 585));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin(__("Window"), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground);
	{

		draw = ImGui::GetWindowDrawList();
		pos = ImGui::GetWindowPos();
		ImGuiStyle* style = &ImGui::GetStyle();
		{
			style->WindowPadding = ImVec2(0, 0);
			style->FramePadding = ImVec2(0, 0);
			style->WindowBorderSize = 0.f;
			style->ItemSpacing = ImVec2(7, 7);
			style->ScrollbarSize = 2.f;
		}
		{
			ImGui::PushFont(DefaultFonts);
			draw->AddRectFilled(pos + ImVec2(0, 35), pos + ((ImVec2(925, 505) + ImVec2(0, 35))), ImGui::GetColorU32(colors::window_background), 8.f, ImDrawFlags_RoundCornersAll); // background
			draw->AddRectFilled(pos + ((ImVec2(2, 2) + ImVec2(0, 35))), pos + ((ImVec2(160, 503) + ImVec2(0, 35))), ImGui::GetColorU32(colors::window_left_side), 8.f, ImDrawFlags_RoundCornersLeft); // left side
			draw->AddRectFilled(pos + ((ImVec2(161, 2) + ImVec2(0, 35))), pos + ((ImVec2(923, 503) + ImVec2(0, 35))), ImGui::GetColorU32(colors::window_right_side), 8.f, ImDrawFlags_RoundCornersBottomRight); // right side
			draw->AddRect(pos + ((ImVec2(1, 1) + ImVec2(0, 35))), pos + ((ImVec2(924, 504) + ImVec2(0, 35))), ImGui::GetColorU32(colors::window_outline), 8.f, ImDrawFlags_RoundCornersAll); // outline
			draw->AddLine(pos + ((ImVec2(160, 2) + ImVec2(0, 35))), pos + ((ImVec2(160, 503) + ImVec2(0, 35))), ImGui::GetColorU32(colors::window_outline)); // line
			draw->AddText(pos + ((ImVec2(15, 15) + ImVec2(0, 70))), ImGui::GetColorU32(colors::window_group_text), __("Main")); // one group text
			draw->AddText(pos + ((ImVec2(15, 115) + ImVec2(0, 70))), ImGui::GetColorU32(colors::window_group_text), __("Other")); // two group text 115
			//draw->AddText(pos + ((ImVec2(15, 265) + ImVec2(0, 70))), ImGui::GetColorU32(colors::window_group_text), "Miscellaneous"); // three group text 315
			draw->AddLine(pos + ((ImVec2(110, 23) + ImVec2(0, 70))), pos + ((ImVec2(150, 23) + ImVec2(0, 70))), ImGui::GetColorU32(colors::window_outline)); // one group line
			draw->AddLine(pos + ((ImVec2(73, 123) + ImVec2(0, 70))), pos + ((ImVec2(150, 123) + ImVec2(0, 70))), ImGui::GetColorU32(colors::window_outline)); // two group line 173
			//draw->AddLine(pos + ((ImVec2(120, 273) + ImVec2(0, 70))), pos + ((ImVec2(150, 273) + ImVec2(0, 70))), ImGui::GetColorU32(colors::window_outline)); // three group line 323
			ImGui::PushFont(BigDefaultFonts);
			const char* text = __("INVIS HACK");
			draw->AddText(ImVec2(pos.x + ((162 - ImGui::CalcTextSize(text).x) * 0.5f), pos.y + 50), ImColor(200, 200, 200), text);
			ImGui::PushFont(SmallDefaultFonts);
			std::string curuser = __("user: ") + std::string(userauth);
			std::string curuser1 = curuser.substr(0, visibleCharacters);
			animationTime += ImGui::GetIO().DeltaTime;
			if (animationTime >= 0.2f)
			{
				animationTime = 0.0f;
				visibleCharacters = (visibleCharacters + 1);
			}
			draw->AddText(pos + ((ImVec2(5, 490) + ImVec2(0, 35))), ImColor(100, 100, 100), curuser1.c_str());
			draw->AddText(pos + ((ImVec2(830, 490) + ImVec2(0, 36))), ImColor(100, 100, 100), ( __("Online Users: ") + bluedream_api.data.numOnlineUsers).c_str());
			ImGui::PopFont();
		}

		ImGui::PushFont(DefaultFonts);
		ImGui::SetCursorPos((ImVec2(8, 38) + ImVec2(0, 70)));
		ImGui::BeginGroup();
		{
			if (ImGui::Tab(menu::rus ? ( __(u8"Оружие")) : __("Weapon"), general_texture, 0 == tab_count))
				/*search2[0] = '\0',*/ tab_count = 0;
			if (ImGui::Tab(menu::rus ? ( __(u8"Другое")) : __("Other"), projectile_texture, 1 == tab_count))
				/*search2[0] = '\0',*/ tab_count = 1;
		}
		ImGui::EndGroup();
		ImGui::SetCursorPos((ImVec2(8, 138) + ImVec2(0, 70)));
		ImGui::BeginGroup();
		{
			if (ImGui::Tab(menu::rus ? (__(u8"Визуалы")) : __("Visuals"), world_texture, 2 == tab_count))
				/*search2[0] = '\0',*/ tab_count = 2;

			
			//if (ImGui::Tab(menu::rus ? (u8"Игроки") : ("Players"), players_texture, 2 == tab_count))

			//	if (ImGui::Tab(menu::rus ? (u8"Персонаж") : ("View"), eye_texture, 3 == tab_count))
			//		/*search2[0] = '\0',*/ tab_count = 3;
			//	if (ImGui::Tab(menu::rus ? (u8"Объекты") : ("Objects"), movement_texture, 4 == tab_count))
			//		/*search2[0] = '\0',*/ tab_count = 4;
			//}
			//ImGui::EndGroup();
			//ImGui::SetCursorPos((ImVec2(8, 288) + ImVec2(0, 70)));
			//ImGui::BeginGroup();
			//{world_texture
			//if (ImGui::Tab(menu::rus ? (u8"Мир") : ("World"), world_texture, 5 == tab_count))
			//	/*search2[0] = '\0',*/ tab_count = 5;
			if (ImGui::Tab(menu::rus ? ( __(u8"Настройки")) : __("Settings"), exploits_texture, 6 == tab_count))
				/*search2[0] = '\0',*/ tab_count = 6;
			if (ImGui::Tab(menu::rus ? ( __(u8"Меню")) : __("Menu"), settings_texture, 7 == tab_count))
				/*search2[0] = '\0',*/ tab_count = 7;
		}
		ImGui::EndGroup();

		ImGui::SetCursorPos((ImVec2(171, 12) + ImVec2(0, 35)));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));
		ImGui::DefaultBeginChild(__("content"), ImVec2(742, 481), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse /*| ImGuiWindowFlags_NoBringToFrontOnFocus*/);
		{
			/*if (g_Search.find && search2[0] != '\0' && strlen(search2) >= 1)
			{
				ImGui::BeginGroup();
				{
					ImGui::BeginChild(menu::rus ? __(u8"поиск") : __(u8"search"), ImVec2(741, 480));
					{
						g_Search.drawqueryresults(search2);
					}
					ImGui::EndChild();
				}
				ImGui::EndGroup();
			}
			else
			{*/
				switch (tab_count)
				{
				case 0: generalmenu();  break;
				case 1: projectilemenu();  break;
				case 2: miscmenu(); break;
				/*case 3: players();  break;
				case 4: world(); break;*/
				//case 5: world(); break;
				case 6: refresh_configs(), cfgmenu(); break;
				case 7: settingsmenu(); break;
				}
			//}
		}
		ImGui::DefaultEndChild();
		ImGui::PopStyleVar();
		ImGui::PopFont();
	}
	ImGui::End();
}
