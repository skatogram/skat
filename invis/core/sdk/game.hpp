#pragma once// float = Single  int = Int32 ref = &
#pragma optimize( "", off )

#define _(str) System::String::New((char*)str);
class StringIl
{
public:
	char pad_0000[0x10];
	int len;
	wchar_t buffer[0];

	static StringIl* New(const char* str)
	{
		return call<StringIl*, const char*>(xorstr_("il2cpp_string_new"), str);
	}
	bool Contains(StringIl* value) {
		static auto off = METHOD("mscorlib::System::String::Contains(String): Boolean");
		return reinterpret_cast<bool(__fastcall*)(StringIl*, StringIl*)>(off)(this, value);
	}
};

inline UINT_PTR GetGameObjectComponent(UINT_PTR type, UINT_PTR pointer) {
	typedef UINT_PTR getComp(UINT_PTR, UINT_PTR);
	return ((getComp*)(game_assembly + CO::GetGameObjectComponent))(pointer, type);
}

inline static UINT_PTR GUIDToObject(String* guid) {
	typedef UINT_PTR GUIDToObject(String*);
	return ((GUIDToObject*)(game_assembly + CO::GUIDToObject))(guid);
}

inline UINT_PTR GetClassObject(UINT_PTR pointer) {
	String* guid = *reinterpret_cast<String**>(pointer + 0x10);
	UINT_PTR _cachedObject = GUIDToObject(guid);
	return _cachedObject;
}

Color3 RGB_RAINBOW = Color3(255, 0, 0);

class SafeExecution {
public:
	static int fail(unsigned int code, struct _EXCEPTION_POINTERS* ep) {
		if (code == EXCEPTION_ACCESS_VIOLATION) {
			return EXCEPTION_EXECUTE_HANDLER;
		}
		else {
			return EXCEPTION_CONTINUE_SEARCH;
		};
	}
public:
	template<typename T = void*, typename R = void*, typename... Args>
	static T Execute(uint64_t ptr, R ret, Args... args) {
		__try {
			return reinterpret_cast<T(__stdcall*)(Args...)>(ptr)(args...);
		}
		__except (fail(GetExceptionCode(), GetExceptionInformation())) {
			return ret;
		}
	}
};

template <typename T>
T Read(DWORD64 address) {
	if (address > 0x40000 && (address + sizeof(T)) < 0x7FFFFFFF0000) {
		return *(T*)(address);
	}
	else {
		return T{};
	}
}
template <typename T>
void Write(DWORD64 address, T data) {
	if (address > 0x40000 && (address + sizeof(T)) < 0x7FFFFFFF0000) {
		*(T*)(address) = data;
	}
}
#define read(Addr, Type) Read<Type>((DWORD64)Addr)

using namespace System;

enum class KeyCode : int {
	None = 0,
	Backspace = 8,
	Delete = 127,
	Tab = 9,
	Clear = 12,
	Return = 13,
	Pause = 19,
	Escapee = 27,
	Space = 32,
	Keypad0 = 256,
	Keypad1 = 257,
	Keypad2 = 258,
	Keypad3 = 259,
	Keypad4 = 260,
	Keypad5 = 261,
	Keypad6 = 262,
	Keypad7 = 263,
	Keypad8 = 264,
	Keypad9 = 265,
	KeypadPeriod = 266,
	KeypadDivide = 267,
	KeypadMultiply = 268,
	KeypadMinus = 269,
	KeypadPlus = 270,
	KeypadEnter = 271,
	KeypadEquals = 272,
	UpArrow = 273,
	DownArrow = 274,
	RightArrow = 275,
	LeftArrow = 276,
	Insert = 277,
	Home = 278,
	End = 279,
	PageUp = 280,
	PageDown = 281,
	F1 = 282,
	F2 = 283,
	F3 = 284,
	F4 = 285,
	F5 = 286,
	F6 = 287,
	F7 = 288,
	F8 = 289,
	F9 = 290,
	F10 = 291,
	F11 = 292,
	F12 = 293,
	F13 = 294,
	F14 = 295,
	F15 = 296,
	Alpha0 = 48,
	Alpha1 = 49,
	Alpha2 = 50,
	Alpha3 = 51,
	Alpha4 = 52,
	Alpha5 = 53,
	Alpha6 = 54,
	Alpha7 = 55,
	Alpha8 = 56,
	Alpha9 = 57,
	Exclaim = 33,
	DoubleQuote = 34,
	Hash = 35,
	Dollar = 36,
	Percent = 37,
	Ampersand = 38,
	Quote = 39,
	LeftParen = 40,
	RightParen = 41,
	Asterisk = 42,
	Plus = 43,
	Comma = 44,
	Minus = 45,
	Period = 46,
	Slash = 47,
	Colon = 58,
	Semicolon = 59,
	Less = 60,
	Equals = 61,
	Greater = 62,
	Question = 63,
	At = 64,
	LeftBracket = 91,
	Backslash = 92,
	RightBracket = 93,
	Caret = 94,
	Underscore = 95,
	BackQuote = 96,
	A = 97,
	B = 98,
	C = 99,
	D = 100,
	E = 101,
	F = 102,
	G = 103,
	H = 104,
	I = 105,
	J = 106,
	K = 107,
	L = 108,
	M = 109,
	N = 110,
	O = 111,
	P = 112,
	Q = 113,
	R = 114,
	S = 115,
	T = 116,
	U = 117,
	V = 118,
	W = 119,
	X = 120,
	Y = 121,
	Z = 122,
	LeftCurlyBracket = 123,
	Pipe = 124,
	RightCurlyBracket = 125,
	Tilde = 126,
	Numlock = 300,
	CapsLock = 301,
	ScrollLock = 302,
	RightShift = 303,
	LeftShift = 304,
	RightControl = 305,
	LeftControl = 306,
	RightAlt = 307,
	LeftAlt = 308,
	LeftCommand = 310,
	LeftApple = 310,
	LeftWindows = 311,
	RightCommand = 309,
	RightApple = 309,
	RightWindows = 312,
	AltGr = 313,
	Help = 315,
	Print = 316,
	SysReq = 317,
	Break = 318,
	Menu = 319,
	Mouse0 = 323,
	Mouse1 = 324,
	Mouse2 = 325,
	Mouse3 = 326,
	Mouse4 = 327,
	Mouse5 = 328,
	Mouse6 = 329
};
enum class PlayerFlags : int {
	Unused1 = 1,
	Unused2 = 2,
	IsAdmin = 4,
	ReceivingSnapshot = 8,
	Sleeping = 16,
	Spectating = 32,
	Wounded = 64,
	IsDeveloper = 128,
	Connected = 256,
	ThirdPersonViewmode = 1024,
	EyesViewmode = 2048,
	ChatMute = 4096,
	NoSprint = 8192,
	Aiming = 16384,
	DisplaySash = 32768,
	Relaxed = 65536,
	SafeZone = 131072,
	ServerFall = 262144,
	Workbench1 = 1048576,
	Workbench2 = 2097152,
	Workbench3 = 4194304,
};
enum class Event_Type : int
{
	mouse_down = 0,
	mouse_up = 1,
	mouse_drag = 3,
	key_down = 4,
	key_up = 5,
	repaint = 7
};
PlayerFlags operator &(PlayerFlags lhs, PlayerFlags rhs) {
	return static_cast<PlayerFlags> (
		static_cast<std::underlying_type<PlayerFlags>::type>(lhs) &
		static_cast<std::underlying_type<PlayerFlags>::type>(rhs)
		);
}
PlayerFlags operator ^(PlayerFlags lhs, PlayerFlags rhs) {
	return static_cast<PlayerFlags> (
		static_cast<std::underlying_type<PlayerFlags>::type>(lhs) ^
		static_cast<std::underlying_type<PlayerFlags>::type>(rhs)
		);
}
PlayerFlags operator ~(PlayerFlags rhs) {
	return static_cast<PlayerFlags> (
		~static_cast<std::underlying_type<PlayerFlags>::type>(rhs)
		);
}
PlayerFlags& operator |=(PlayerFlags& lhs, PlayerFlags rhs) {
	lhs = static_cast<PlayerFlags> (
		static_cast<std::underlying_type<PlayerFlags>::type>(lhs) |
		static_cast<std::underlying_type<PlayerFlags>::type>(rhs)
		);

	return lhs;
}
PlayerFlags& operator &=(PlayerFlags& lhs, PlayerFlags rhs) {
	lhs = static_cast<PlayerFlags> (
		static_cast<std::underlying_type<PlayerFlags>::type>(lhs) &
		static_cast<std::underlying_type<PlayerFlags>::type>(rhs)
		);

	return lhs;
}

class Object {
public:

};
class Type {
public:
	// pass as "Namespace.Classname, Assembly.Name"
	static Type* GetType(const char* qualified_name) {
		static auto off = METHOD("mscorlib::System::Type::GetType(String): Type");
		return reinterpret_cast<Type * (__cdecl*)(System::String*)>(off)(System::String::New(qualified_name));
	}
	static Type* SkinnedMeshRenderer() {
		Type* type = GetType(xorstr_("UnityEngine.SkinnedMeshRenderer, UnityEngine.CoreModule"));
		return type;
	}
	static Type* Renderer() {
		Type* type = GetType(xorstr_("UnityEngine.Renderer, UnityEngine.CoreModule"));
		return type;
	}
	static Type* Shader() {
		Type* type = GetType(xorstr_("UnityEngine.Shader, UnityEngine.CoreModule"));
		return type;
	}
	static Type* Projectile() {
		Type* type = GetType(xorstr_("Projectile, Assembly-CSharp"));
		return type;
	}
	static Type* ItemModProjectile() {
		Type* type = GetType(xorstr_("ItemModProjectile, Assembly-CSharp"));
		return type;
	}
};

class GameObject;
class Component {
public:
	
	float GetRandVel() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::ItemModProjectile::GetRandomVelocity(): Single");
		return reinterpret_cast<float(__fastcall*)(Component*)>(off)(this);
	}
	
	Transform* transform( ) {
		if ( !this ) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_transform(): Transform");
		return reinterpret_cast< Transform * ( __fastcall* )( Component* ) >( off )( this );
	}
	template<typename T = Component>
	T* GetComponent(Type* type) {
		if ( !this || !type ) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::GetComponent(Type): Component");
		return reinterpret_cast< T * ( __fastcall* )( Component*, Type* ) >( off )( this, type );
	}
	template<typename T = Component>
	Array<T*>* GetComponentsInChildren(Type* type) {
		if (!this || !type) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::GetComponentsInChildren(Type): Component[]");
		return reinterpret_cast< Array<T*>* ( __fastcall* )( Component*, Type* ) >( off )( this, type );
	}
	GameObject* gameObject( ) {
		if ( !this ) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_gameObject(): GameObject");
		return reinterpret_cast< GameObject * ( __fastcall* )( Component* ) >( off )( this );
	}

	char* class_name() {
		if (!this) return __("");
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return __("");
		return *reinterpret_cast<char**>(oc + 0x10);
	}

	uint32_t class_name_hash() {
		if (!this) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		if (!*reinterpret_cast<char**>(oc + 0x10)) return 0;
		const char* name = *reinterpret_cast<char**>(oc + 0x10);
		if (!name) return 0;
		return RUNTIME_CRC32(name);

	}
	uint32_t _class_name_hash() {
		if (!this) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		const char* name = *reinterpret_cast<char**>(oc + 0x10);
		return RUNTIME_CRC32(name);
	}

	bool IsPlayer() {
		if (!this) return false;

		return !strcmp(this->class_name(), xorstr_("BasePlayer")) ||
			!strcmp(this->class_name(), xorstr_("NPCPlayerApex")) ||
			!strcmp(this->class_name(), xorstr_("NPCMurderer")) ||
			!strcmp(this->class_name(), xorstr_("NPCPlayer")) ||
			!strcmp(this->class_name(), xorstr_("HumanNPC")) ||
			!strcmp(this->class_name(), xorstr_("Scientist")) ||
			!strcmp(this->class_name(), xorstr_("TunnelDweller")) ||
			!strcmp(this->class_name(), xorstr_("HTNPlayer")) ||
			!strcmp(this->class_name(), xorstr_("ScientistNPC")) ||
			!strcmp(this->class_name(), xorstr_("NPCShopKeeper"));
	}
};
class PathFinder {
public:
	class Points {
	public:
		//STATIC_FUNCTION("Assembly-CSharp::PathFinder::Point::Point(Int32,Int32): Void", Point, void(int, int));
	};
	class Node {
	public:

	};
	//STATIC_FUNCTION("Assembly-CSharp::BasePathFinder::GetRandomPatrolPoint(): Vector3", GetRandomPatrolPoint, Vector3());
	STATIC_FUNCTION("Assembly-CSharp::PathFinder::FindPath(Point,Point,Int32): Node", FindPath, Node(Points*, Points*, int));
};
class Renderer_;
class GameObject : public Component {
public:
	int layer() {
		if (!this) return 0;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::GameObject::get_layer(): Int32");
		return reinterpret_cast<int(__fastcall*)(GameObject*)>(off)(this);
	}
	const wchar_t* tag() {
		if (!this) return 0;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::GameObject::get_tag(): String");
		return reinterpret_cast<System::String * (__fastcall*)(GameObject*)>(off)(this)->buffer;
	}
	const wchar_t* name()
	{
		if (!this) return 0;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Object::get_name(): String");
		return reinterpret_cast<System::String * (__fastcall*)(GameObject*)>(off)(this)->buffer;
	}
	std::uint32_t name2() {
		static auto auto_ShortPrefabName_hash = METHOD("UnityEngine.CoreModule::UnityEngine::Object::get_name(): String");
		return name_hashtry(auto_ShortPrefabName_hash);
	}

	std::uint32_t name_hashtry(static uintptr_t auto_ShortPrefabName_hash) {
		__try {
			if (!reinterpret_cast<System::String * (__fastcall*)(GameObject*)>(auto_ShortPrefabName_hash)(this)->buffer
				|| !this
				|| !auto_ShortPrefabName_hash) return 0;
			return RUNTIME_CRC32_W(reinterpret_cast<System::String * (__fastcall*)(GameObject*)>(auto_ShortPrefabName_hash)(this)->buffer);
		}
		__except (SafeExecution::fail(GetExceptionCode(), GetExceptionInformation())) { return 0; };
	}
	StringIl* get_name()
	{
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Object::get_name(): String");
		return reinterpret_cast<StringIl * (__fastcall*)(GameObject*)>(off)(this);
	}
	template<typename T = GameObject>
	T* GetComponent(Type* type) {
		if ( !this || !type ) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::GameObject::GetComponent(Type): Component");
		return reinterpret_cast< T * ( __fastcall* )( GameObject*, Type* ) >( off )( this, type );
	}


	Component* AddComponent(Type* type)
	{
		if (!this || !type) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::GameObject::AddComponent(Type): Component");
		return reinterpret_cast< Component * ( __fastcall* )( GameObject*, Type* ) >( off )( this, type );
		//if (!this) return nullptr;

	//	const auto add_component = reinterpret_cast<UnityEngine::Component * (*)(GameObject*, System::Type*)>(*reinterpret_cast<uintptr_t*>((uintptr_t)CIl2Cpp::FindMethod(this->StaticClass(), HASH("AddComponent"), 1)));
		//return memory::Call<UnityEngine::Component*>((uintptr_t)add_component, this, type);
	}
};
class Transform : public Component {
public:
	Matrix get_localToWorldMatrix()
	{
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_localToWorldMatrix(): Matrix4x4");
		return reinterpret_cast<Matrix(__fastcall*)(Transform*)>(off)(this);
	}
	Quaternion get_rotation() {
		if (!this) return Quaternion();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_rotation(): Quaternion");
		return reinterpret_cast<Quaternion(__fastcall*)(Transform*)>(off)(this);
	}
	Vector3 position( ) {
		if ( !this ) return Vector3::Zero( );
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_position(): Vector3");
		return SafeExecution::Execute<Vector3>(off, Vector3::Zero( ), this);
	}
	Vector3 localPosition() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_localPosition(): Vector3");
		return reinterpret_cast< Vector3(__fastcall*)( Transform* ) >( off )( this );
	}
	Vector3 get_forward() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_forward(): Vector3");
		return reinterpret_cast< Vector3(__fastcall*)( Transform* ) >( off )( this );
	}
	Vector3 up() {
		if (!this)
			return Vector3::Zero();

		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_up(): Vector3");
		return reinterpret_cast< Vector3(__fastcall*)( Transform* ) >( off )( this );
	}
	void set_position(Vector3 value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::set_position(Vector3): Void");
		reinterpret_cast<void(__fastcall*)(Transform*, Vector3)>(off)(this, value);
	}
	void set_rotation(Quaternion value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::set_rotation(Quaternion): Void");
		reinterpret_cast< void(__fastcall*)( Transform*, Quaternion ) >( off )( this, value );
	}
	void set_scale(Vector3 value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::set_localScale(Vector3): Void");
		reinterpret_cast<void(__fastcall*)(Transform*, Vector3)>(off)(this, value);
	}
	Vector3 InverseTransformPoint(Vector3 position) {
		if (!this) return Vector3::Zero();

		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::InverseTransformPoint(Vector3): Vector3");

		return reinterpret_cast<Vector3(__fastcall*)(Transform*, Vector3)>(off)(this, position);
	}

	Vector3 InverseTransformDirection(Vector3 position) {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::InverseTransformDirection(Vector3): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(Transform*, Vector3)>(off)(this, position);
	}
};
class BasePlayer;
class LocalPlayer {
public:
	static BasePlayer* Entity() {
		static auto clazz = CLASS("Assembly-CSharp::LocalPlayer");
		return *reinterpret_cast<BasePlayer**>(std::uint64_t(clazz->static_fields));
	}
};
class MainCamera
{
public:
	Vector3 Get_Position() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::MainCamera::get_position(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(MainCamera*)>(off)(this);
	}
	Vector3 Get_Forward() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::MainCamera::get_forward(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(MainCamera*)>(off)(this);
	}
	Quaternion Get_Rotation() {
		if (!this) return Quaternion();
		static auto off = METHOD("Assembly-CSharp::MainCamera::get_rotation(): Quaternion");
		return reinterpret_cast<Quaternion(__fastcall*)(MainCamera*)>(off)(this);
	}
	static MainCamera* Camera() {
		static auto clazz = CLASS("Assembly-CSharp::MainCamera");
		return *reinterpret_cast<MainCamera**>(std::uint64_t(clazz->static_fields));
	}
};
class Networkable
{
public:
	FIELD("Facepunch.Network::Network::Networkable::ID", ID, uint32_t);
};

namespace ProtoBuf {
	class BaseNetworkable {
	public:
		FIELD("Rust.Data::ProtoBuf::BaseNetworkable::uid", uid, uint32_t);
	};
	class BasePlayer {
	public:
		FIELD("Rust.Data::ProtoBuf::BasePlayer::userid", userid, uint64_t);
		FIELD("Rust.Data::ProtoBuf::BasePlayer::playerFlags", playerFlags, PlayerFlags);

		bool HasPlayerFlag(PlayerFlags flag)
		{
			if (!this) return false;

			return (this->playerFlags() & flag) == flag;
		}
	};

	class baseCombat {
	public:
		FIELD("Rust.Data::ProtoBuf::BaseCombat::health", health, float);

	};

	class Entity {
	public:
		FIELD("Rust.Data::ProtoBuf::Entity::baseNetworkable", baseNetworkable, ProtoBuf::BaseNetworkable*);
		FIELD("Rust.Data::ProtoBuf::Entity::basePlayer", basePlayer, ProtoBuf::BasePlayer*);
		FIELD("Rust.Data::ProtoBuf::Entity::baseCombat", baseCombat, ProtoBuf::baseCombat*);
	};
}

class BaseEntity;
class BaseNetworkable : public Component
{
public:
	struct LoadInfo
	{
		ProtoBuf::Entity* msg;
		bool fromDisk;
	};

	class EntityRealm {
	public:
		template<typename T = BaseNetworkable*> T Find(uint32_t uid) {
			static auto off = METHOD("Assembly-CSharp::EntityRealm::Find(NetworkableId): BaseNetworkable");
			return reinterpret_cast<T(__fastcall*)(EntityRealm*, uint32_t)>(off)(this, uid);
		}
		template<typename T = BaseNetworkable*>
		T FindClosest(const char* hash, BaseNetworkable* targetEnt, float dist)
		{
			T ent = nullptr;

			auto entityList = this->entityList();
			if (entityList)
			{
				for (int i = 1; i < entityList->vals->size; i++) {
					auto baseNetworkable = *reinterpret_cast<BaseNetworkable**>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
					if (!baseNetworkable) continue;
					if (!baseNetworkable->IsValid()) continue;
					auto classname = baseNetworkable->class_name( );
					if ( !math::m_strcmp(classname, hash) ) continue;

					if (baseNetworkable->transform()->position().distance(targetEnt->transform()->position()) <= dist) {
						ent = reinterpret_cast<T>(baseNetworkable);
						break;
					}
				}
			}

			return ent;
		}
		FIELD("Assembly-CSharp::EntityRealm::entityList", entityList, ListDictionary*);
	};


	bool isClient() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::BaseNetworkable::get_isClient(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(BaseNetworkable*)>(off)(this);
	}

	bool IsDestroyed() {
		if (!this) return true;
		static auto off = OFFSET("Assembly-CSharp::BaseNetworkable::<IsDestroyed>k__BackingField");
		return *reinterpret_cast<bool*>(this + off);
	}

	bool IsValid() {
		if (!this) return false;
		return !this->IsDestroyed() && this->net() != nullptr;
	}

	static EntityRealm* clientEntities() {
		static auto clazz = CLASS("Assembly-CSharp::BaseNetworkable");
		return *reinterpret_cast<EntityRealm**>(std::uint64_t(clazz->static_fields));
	}

	const wchar_t* ShortPrefabName() {
		static auto off = METHOD("Assembly-CSharp::BaseNetworkable::get_ShortPrefabName(): String");
		return ShortPrefabNametry(off);
	}
	const wchar_t* PrefabName() {
		static auto off = METHOD("Assembly-CSharp::BaseNetworkable::get_PrefabName(): String");
		return ShortPrefabNametry(off);
	}

	const wchar_t* ShortPrefabNametry(static uintptr_t off) {
		__try {
			if (!this) return L"";
			if (!reinterpret_cast<System::String * (__fastcall*)(BaseNetworkable*)>(off)(this)->buffer) return 0;

			return reinterpret_cast<System::String * (__fastcall*)(BaseNetworkable*)>(off)(this)->buffer;
		}
		__except (SafeExecution::fail(GetExceptionCode(), GetExceptionInformation())) { return 0; };
	}

	std::uint32_t ShortPrefabName_hash() {
		static auto auto_ShortPrefabName_hash = METHOD("Assembly-CSharp::BaseNetworkable::get_ShortPrefabName(): String");
		return ShortPrefabName_hashtry(auto_ShortPrefabName_hash);
	}

	std::uint32_t ShortPrefabName_hashtry(static uintptr_t auto_ShortPrefabName_hash) {
		__try {
			if (!reinterpret_cast<System::String * (__fastcall*)(BaseNetworkable*)>(auto_ShortPrefabName_hash)(this)->buffer
				|| !this
				|| !auto_ShortPrefabName_hash) return 0;
			return RUNTIME_CRC32_W(reinterpret_cast<System::String * (__fastcall*)(BaseNetworkable*)>(auto_ShortPrefabName_hash)(this)->buffer);
		}
		__except (SafeExecution::fail(GetExceptionCode(), GetExceptionInformation())) { return 0; };
	}
	FIELD("Assembly-CSharp::BaseNetworkable::<JustCreated>k__BackingField", JustCreated, bool);
	FIELD("Assembly-CSharp::BaseNetworkable::net", net, Networkable*);
	FIELD("Assembly-CSharp::BaseNetworkable::parentEntity", parentEntity, BaseEntity*);
	FIELD("Assembly-CSharp::BaseNetworkable::prefabID", prefabID, uint64_t);
};
class Material;
class Skinnable {
public:
	FIELD("Assembly-CSharp::Skinnable::_sourceMaterials", _sourceMaterials, Array<Material*>*);
};
class ItemSkin {
public:
	FIELD("Assembly-CSharp::ItemSkin::Skinnable", _Skinnable, Skinnable*);
	FIELD("Assembly-CSharp::ItemSkin::Materials", Materials, Array<Material*>*);
};
class Model;
class Shader;
class Renderer_;
class Material;
class Shader {
public:
	static Shader* Find(char* name) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Shader::Find(String): Shader");
		return reinterpret_cast<Shader * (__fastcall*)(System::String*)>(off)(System::String::New(name));
	}
	static int PropertyToID(char* name) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Shader::PropertyToID(String): Int32");
		return reinterpret_cast<int(__fastcall*)(System::String*)>(off)(System::String::New(name));
	}
};

class Material : public GameObject {
public:
	void SetColor(int proper, Color value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetColor(Int32,Color): Void");
		return reinterpret_cast<void(__fastcall*)(Material*, int, Color)>(off)(this, proper, value);
	}
	void SetColor(char* proper, Color value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetColor(String,Color): Void");
		return reinterpret_cast<void(__fastcall*)(Material*, System::String*, Color)>(off)(this, System::String::New(proper), value);
	}
	void SetInt(char* name, int value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetInt(String,Int32): Void");
		return reinterpret_cast<void(__fastcall*)(Material*, System::String*, int)>(off)(this, System::String::New(name), value);
	}
	void SetFloat(char* name, float value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetFloat(String,Single): Void");
		return reinterpret_cast<void(__fastcall*)(Material*, System::String*, float)>(off)(this, System::String::New(name), value);
	}
	Shader* shader() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::get_shader(): Shader");
		return reinterpret_cast<Shader * (__fastcall*)(Material*)>(off)(this);
	}
	void set_shader(Shader* val, static uintptr_t off) {
		static int exceptionCounter = 0;
		__try {
			if (exceptionCounter <= 10) {
				exceptionCounter++;
				return;
			}
			if (!this || !val || !off) return;

			return reinterpret_cast<void(__fastcall*)(Material*, Shader*)>(off)(this, val);
		}
		__except (SafeExecution::fail(GetExceptionCode(), GetExceptionInformation())) {
			exceptionCounter = 0;
		};
	}
};
class Renderer_ {
public:
	Material* material() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_material(): Material");
		return reinterpret_cast<Material * (__fastcall*)(Renderer_*)>(off)(this);
	}
	void set_material(Material* value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::set_material(Material): Void");
		return reinterpret_cast<void(__fastcall*)(Renderer_*, Material*)>(off)(this, value);
	}
	bool isVisible() {
		if (!this) return false;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_isVisible(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Renderer_*)>(off)(this);
	}
	Array<Material*>* materials() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_materials(): Material[]");
		return reinterpret_cast<Array<Material*>*(__fastcall*)(Renderer_*)>(off)(this);
	}
};

Material* WireFrmaeRainbow;
Material* skybox;
Shader* GlowVisibleCheck;
Shader* VisibleCheck;
Material* matcapfx2;
Material* matcapfx;
class Item;
class BaseEntity : public BaseNetworkable {
public:

	static inline void( *Health_ )(  ) = nullptr;
	
	
	//STATIC_FUNCTION("Assembly-CSharp::BaseEntity::GetEntity(): BaseEntity", GetEntity, BaseEntity* ());
	enum class Signal {
		Attack,
		Alt_Attack,
		DryFire,
		Reload,
		Deploy,
		Flinch_Head,
		Flinch_Chest,
		Flinch_Stomach,
		Flinch_RearHead,
		Flinch_RearTorso,
		Throw,
		Relax,
		Gesture,
		PhysImpact,
		Eat,
		Startled
	};
	enum class Flags
	{
		Placeholder = 1,
		On = 2,
		OnFire = 4,
		Open = 8,
		Locked = 16,
		Debugging = 32,
		Disabled = 64,
		Reserved1 = 128,
		Reserved2 = 256,
		Reserved3 = 512,
		Reserved4 = 1024,
		Reserved5 = 2048,
		Broken = 4096,
		Busy = 8192,
		Reserved6 = 16384,
		Reserved7 = 32768,
		Reserved8 = 65536,
		Reserved9 = 131072,
		Reserved10 = 262144
	};

	FIELD("Assembly-CSharp::BaseEntity::flags", flags, BaseEntity::Flags)
		static inline void(*OnSkinChanged_)(BaseEntity*, long, long) = nullptr;
	void OnSkinChanged(long oldskin, long newskin) {
		OnSkinChanged_(this, oldskin, newskin);
	}
	bool HasFlag(BaseEntity::Flags f);
	Vector3 GetParentVelocity() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BaseEntity::GetParentVelocity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BaseEntity*)>(off)(this);
	}
	float Distance(Vector3 pos1) {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::Distance(Vector3): Single");
		return reinterpret_cast<float(__fastcall*)(BaseEntity*, Vector3)>(off)(this, pos1);
	}
	float BoundsPadding() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::BoundsPadding(): Single");
		return reinterpret_cast<float(__fastcall*)(BaseEntity*)>(off)(this);
	}
	void ServerRPC(const char* funcName) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::ServerRPC(String): Void");
		reinterpret_cast<void(__stdcall*)(BaseEntity*, System::String*)>(off)(this, System::String::New(funcName));
	}
	Vector3 GetWorldVelocity() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BaseEntity::GetWorldVelocity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BaseEntity*)>(off)(this);
	}
	Vector3 ClosestPoint(Vector3 p) {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BaseEntity::ClosestPoint(Vector3): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BaseEntity*, Vector3)>(off)(this, p);
	}
	void SendSignalBroadcast(Signal a, char* str = xorstr_("")) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::SendSignalBroadcast(Signal,String): Void");
		return reinterpret_cast<void(__fastcall*)(BaseEntity*, Signal, System::String*)>(off)(this, a, System::String::New(str));
	}
	FIELD("Assembly-CSharp::BaseEntity::model", model, Model*);
	FIELD("Assembly-CSharp::BaseEntity::itemSkin", itemSkin, ItemSkin*);
	FIELD("Assembly-CSharp::BaseEntity::skinID", skinID, long);
	FIELD("Assembly-CSharp::WorldItem::item", item, Item*);
	FIELD("Assembly-CSharp::BaseEntity::Health", health, float);
	const wchar_t* _name() {
		static auto off = OFFSET("Assembly-CSharp::BaseEntity::_name");
		return (*reinterpret_cast<System::String**>(this + off))->buffer;
	}
	void ChamsItems(BaseEntity* a1)
	{
		if (!this) return;
		auto renderers = a1->GetComponentsInChildren(Type::Renderer());
		for (int i = 0; i < renderers->size(); i++)
		{
			Renderer_* renderer = reinterpret_cast<Renderer_*>(renderers->get(i));
			if (!renderer) continue;
			if (!renderer->material()) continue;
			auto material = renderer->material();
			auto shader = material->shader();
			if (material)
			{
				static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::set_shader(Shader): Void");
				if (funcs::localplayer::itemschamstype == 0)
				{
					renderer->set_material(WireFrmaeRainbow);
				}
				else if (funcs::localplayer::itemschamstype == 1)
				{
					material->set_shader(GlowVisibleCheck, off);
					material->SetColor(Shader::PropertyToID(xorstr_("_ColorVisible")), Color({ funcs::visuals::itemschamsvisible[0], funcs::visuals::itemschamsvisible[1], funcs::visuals::itemschamsvisible[2], 10 }));
					material->SetColor(Shader::PropertyToID(xorstr_("_ColorBehind")), Color({ funcs::visuals::itemschamsinvisible[0], funcs::visuals::itemschamsinvisible[1], funcs::visuals::itemschamsinvisible[2], 10 }));
				}
				else if (funcs::localplayer::itemschamstype == 2)
				{
					material->set_shader(VisibleCheck, off);
					material->SetColor(Shader::PropertyToID(xorstr_("_ColorVisible")), Color({ funcs::visuals::itemschamsvisible[0], funcs::visuals::itemschamsvisible[1], funcs::visuals::itemschamsvisible[2], 1 }));
					material->SetColor(Shader::PropertyToID(xorstr_("_ColorBehind")), Color({ funcs::visuals::itemschamsinvisible[0], funcs::visuals::itemschamsinvisible[1], funcs::visuals::itemschamsinvisible[2], 1 }));
				}
				else if (funcs::localplayer::itemschamstype == 3)
				{
					renderer->set_material(matcapfx2);
				}
				else if (funcs::localplayer::itemschamstype == 4)
				{
					renderer->set_material(matcapfx);
				}
			}
		}
	}

};

BaseEntity::Flags operator &(BaseEntity::Flags lhs, BaseEntity::Flags rhs) {
	return static_cast<BaseEntity::Flags> (
		static_cast<std::underlying_type<BaseEntity::Flags>::type>(lhs) &
		static_cast<std::underlying_type<BaseEntity::Flags>::type>(rhs)
		);
}
BaseEntity::Flags operator ^(BaseEntity::Flags lhs, BaseEntity::Flags rhs) {
	return static_cast<BaseEntity::Flags> (
		static_cast<std::underlying_type<BaseEntity::Flags>::type>(lhs) ^
		static_cast<std::underlying_type<BaseEntity::Flags>::type>(rhs)
		);
}
BaseEntity::Flags operator ~(BaseEntity::Flags rhs) {
	return static_cast<BaseEntity::Flags> (
		~static_cast<std::underlying_type<BaseEntity::Flags>::type>(rhs)
		);
}
BaseEntity::Flags& operator |=(BaseEntity::Flags& lhs, BaseEntity::Flags rhs) {
	lhs = static_cast<BaseEntity::Flags> (
		static_cast<std::underlying_type<BaseEntity::Flags>::type>(lhs) |
		static_cast<std::underlying_type<BaseEntity::Flags>::type>(rhs)
		);

	return lhs;
}
BaseEntity::Flags& operator &=(BaseEntity::Flags& lhs, BaseEntity::Flags rhs) {
	lhs = static_cast<BaseEntity::Flags> (
		static_cast<std::underlying_type<BaseEntity::Flags>::type>(lhs) &
		static_cast<std::underlying_type<BaseEntity::Flags>::type>(rhs)
		);

	return lhs;
}

bool BaseEntity::HasFlag(BaseEntity::Flags f)
{
	return (this->flags() & f) == f;
}
enum class LayerMask : int {
	Deployed = 256,
	Construction = 2097152
};

class RaycastHit {
public:
	Vector3 point;
	Vector3 normal;

	RaycastHit()
	{
		point = Vector3::Zero();
		normal = Vector3::Zero();
	}

};

class GamePhysics {
public:
	enum class QueryTriggerInteraction {
		UseGlobal = 0,
		Ignore = 1,
		Collide = 2,
	};
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::Verify(RaycastHit,BaseEntity): Boolean", Verify, bool(RaycastHit, float));
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::LineOfSightRadius(Vector3,Vector3,Int32,Single,BaseEntity): Boolean", LineOfSightRadius, bool(Vector3, Vector3, int, float, float));
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::LineOfSight(Vector3,Vector3,Int32,BaseEntity): Boolean", LineOfSight, bool(Vector3, Vector3, int, float));
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::CheckCapsule(Vector3,Vector3,Single,Int32,QueryTriggerInteraction): Boolean", CheckCapsule, bool(Vector3, Vector3, float, int, QueryTriggerInteraction));
};
bool LineOfSight(Vector3 a, Vector3 b) {
	bool result = false;
	if (a != Vector3::Zero() && b != Vector3::Zero())
	{
		int mask = funcs::weapon::pierce ? 2162688 | 8388608 | 134217728  : 1503731969 | 2162688 | 8388608 | 2097152 | 1 | 2097152 | 32768 | 65536; // projectile los, flyhack mask, intellisense reload
		result = GamePhysics::LineOfSight(a, b, mask, 0.f) && GamePhysics::LineOfSight(b, a, mask, 0.f);
	}
	return result;
}
bool LineOfSightRadius(Vector3 p0, Vector3 p1, int layerMask, float radius) {
	bool result = GamePhysics::LineOfSightRadius(p0, p1, layerMask, radius, 0.f) && GamePhysics::LineOfSightRadius(p1, p0, layerMask, radius, 0.f);
	return result;
}
class Time {
public:
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_timeScale(): Single", get_timeScale, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_time(): Single", time, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_deltaTime(): Single", deltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_fixedTime(): Single", fixedTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_unscaledTime(): Single", unscaledTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_unscaledDeltaTime(): Single", unscaledDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_fixedDeltaTime(): Single", fixedDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_maximumDeltaTime(): Single", maximumDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_smoothDeltaTime(): Single", smoothDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::set_timeScale(Single): Void", set_timeScale, void(float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_frameCount(): Int32", frameCount, int());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_renderedFrameCount(): Int32", renderedFrameCount, int());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_realtimeSinceStartup(): Single", realtimeSinceStartup, float());
};
class DamageTypeList {
public:
	float Total() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::Rust::DamageTypeList::Total(): Single");
		return reinterpret_cast<float(__fastcall*)(DamageTypeList*)>(off)(this);
	}
};
class HitInfo {
public:
	static HitInfo* New()
	{
		HitInfo* hitTest = il2cpp_object_new<HitInfo*>(CLASS("Assembly-CSharp::HitInfo"));
		return hitTest;
	}

	FIELD("Assembly-CSharp::HitInfo::Initiator", Initiator, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::WeaponPrefab", WeaponPrefab, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::DoHitEffects", DoHitEffects, bool);
	FIELD("Assembly-CSharp::HitInfo::DoDecals", DoDecals, bool);
	FIELD("Assembly-CSharp::HitInfo::IsPredicting", IsPredicting, bool);
	FIELD("Assembly-CSharp::HitInfo::UseProtection", UseProtection, bool);
	FIELD("Assembly-CSharp::HitInfo::DidHit", DidHit, bool);
	FIELD("Assembly-CSharp::HitInfo::HitEntity", HitEntity, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::HitBone", HitBone, uint32_t);
	FIELD("Assembly-CSharp::HitInfo::HitPart", HitPart, uint32_t);
	FIELD("Assembly-CSharp::HitInfo::HitMaterial", HitMaterial, System::String*);
	FIELD("Assembly-CSharp::HitInfo::HitPositionWorld", HitPositionWorld, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitPositionLocal", HitPositionLocal, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitNormalWorld", HitNormalWorld, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitNormalLocal", HitNormalLocal, Vector3);
	FIELD("Assembly-CSharp::HitInfo::PointStart", PointStart, Vector3);
	FIELD("Assembly-CSharp::HitInfo::PointEnd", PointEnd, Vector3);
	FIELD("Assembly-CSharp::HitInfo::ProjectileID", ProjectileID, int);
	FIELD("Assembly-CSharp::HitInfo::ProjectileDistance", ProjectileDistance, float);
	FIELD("Assembly-CSharp::HitInfo::ProjectileVelocity", ProjectileVelocity, Vector3);
	FIELD("Assembly-CSharp::HitInfo::damageTypes", damageTypes, DamageTypeList*);

	Vector3 PositionOnRay(Vector3 position) {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::HitInfo::PositionOnRay(Vector3): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(HitInfo*, Vector3)>(off)(this, position);
	}

	bool isHeadshot() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::HitInfo::get_isHeadshot(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(HitInfo*)>(off)(this);
	}
};
float GLOBAL_TIME = 0.f;
class Projectile;

class CursorManager {
public:
	static inline void( *Update_ )( CursorManager* ) = nullptr;
	void Update() {
		return Update_(this);
	}
	static void set_visible(bool value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Cursor::set_visible(Boolean): Void");
		return reinterpret_cast< void(__fastcall*)( bool ) >( off )( value );
	}
	static void set_lockstate(int value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Cursor::set_lockState(CursorLockMode): Void");
		return reinterpret_cast< void(__fastcall*)( int ) >( off )( value );
	}

};
class BaseCombatEntity : public BaseEntity {
public:
	

	
	enum class LifeState {
		Alive = 0,
		Dead = 1
	};
	/*/uint32_t ClassNameHash() {
	if (!this) return 0;
	auto oc = *reinterpret_cast<uint64_t*>(this);
	if (!oc) return 0;
	const char* name = *reinterpret_cast<char**>(oc + 0x10);
	return RUNTIME_CRC32(name);
}*/
	FIELD("Assembly-CSharp::BaseCombatEntity::_health", health, float);
	FIELD("Assembly-CSharp::BaseCombatEntity::_maxHealth", maxHealth, float);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsHitNotification", sendsHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", sendsMeleeHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", lastNotifyFrame, int);
	FIELD("Assembly-CSharp::BaseCombatEntity::lifestate", lifestate, LifeState);
	bool is_dead() {
		if (!this) return false;
		return this->lifestate() == LifeState::Dead;
	}
	static inline void(*DoHitNotify_)(BaseCombatEntity*, HitInfo*, Projectile*) = nullptr;
	void DoHitNotify(BaseCombatEntity* entity, HitInfo* info, Projectile* prj) {
		return DoHitNotify_(entity, info, prj);
	}
	static inline void(*OnAttacked_)(BaseCombatEntity*, HitInfo*) = nullptr;
	void OnAttacked(HitInfo* info) {
		return OnAttacked_(this, info);
	}
};
class ConsoleSystem {
public:
	struct Option {
		static Option* Client() {
			static auto off = METHOD("Facepunch.Console::Option::get_Client(): Option");
			return reinterpret_cast<Option * (__fastcall*)()>(off)();
		}
		bool IsFromServer() {
			return *reinterpret_cast<bool*>(this + 0x6);
		}
		static Option* Quiet() {
			static auto off = METHOD("Facepunch.Console::Option::Quiet(): Option");
			return reinterpret_cast<Option * (__fastcall*)()>(off)();
		}
	};

	static void WriteLine(System::String* value) {
		static auto off = METHOD("mscorlib::System::Console::WriteLine(String): Void");
		return reinterpret_cast<void(__fastcall*)( System::String* ) >( off )( value );
	}

	static inline System::String* (*Run_)(Option*, System::String*, Array<System::Object_*>*) = nullptr;
	static System::String* Run(Option* option, System::String* command, Array<System::Object_*>* args) {
		return Run_(option, command, args);
	}
};
class BaseMountable : public BaseCombatEntity {
public:
	FIELD("Assembly-CSharp::BaseMountable::canWieldItems", canWieldItems, bool);

	BaseMountable* GetVehicleParent() {
		if (!this) return {};
		static auto off = METHOD("Assembly-CSharp::BaseVehicleMountPoint::VehicleParent(): BaseVehicle");
		return reinterpret_cast<BaseMountable * (*)(BaseMountable*)>(off)(this);
	}

	static inline Vector3(*EyePositionForPlayer_)(BaseMountable*, BasePlayer*, Quaternion) = nullptr;
	Vector3 EyePositionForPlayer(BasePlayer* ply, Quaternion rot) {
		return EyePositionForPlayer_(this, ply, rot);
	}
};

class RigidBody {
public:
	Vector3 velocity() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.PhysicsModule::UnityEngine::Rigidbody::get_velocity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(RigidBody*)>(off)(this);
	}
	void set_velocity(Vector3 value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.PhysicsModule::UnityEngine::Rigidbody::set_velocity(Vector3): Void");
		return reinterpret_cast<void(__fastcall*)(RigidBody*, Vector3)>(off)(this, value);
	}
};
class BaseMovement {
public:
	FIELD("Assembly-CSharp::BaseMovement::adminCheat", adminCheat, bool);
	FIELD("Assembly-CSharp::BaseMovement::<TargetMovement>k__BackingField", TargetMovement, Vector3);
	FIELD("Assembly-CSharp::BaseMovement::<Running>k__BackingField", Running, float);
	FIELD("Assembly-CSharp::BaseMovement::<Grounded>k__BackingField", Grounded, float);
	FIELD("Assembly-CSharp::BaseMovement::<Ducking>k__BackingField", Ducking, float);
};
class ModelState;
class CapsuleCollider {
public:
	void set_radius(float value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.PhysicsModule::UnityEngine::CapsuleCollider::set_radius(Single): Void");
		return reinterpret_cast<void(__fastcall*)(CapsuleCollider*, float)>(off)(this, value);
	}
};
class PlayerWalkMovement : public BaseMovement {
public:
	FIELD("Assembly-CSharp::PlayerWalkMovement::flying", flying, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::body", body, RigidBody*);
	FIELD("Assembly-CSharp::PlayerWalkMovement::maxAngleWalking", maxAngleWalking, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::maxVelocity", maxVelocity, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundAngle", groundAngle, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundAngleNew", groundAngleNew, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundNormal", groundNormal, Vector3);
	FIELD("Assembly-CSharp::PlayerWalkMovement::capsule", capsule, CapsuleCollider*);

	FIELD("Assembly-CSharp::PlayerWalkMovement::jumpTime", jumpTime, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::landTime", landTime, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundTime", groundTime, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::gravityMultiplier", gravityMultiplier, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::climbing", climbing, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::sliding", sliding, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::grounded", grounded, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::jumping", jumping, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::swimming", swimming, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::ladder", ladder, void*);
	void TeleportTo(Vector3 pos)
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::PlayerWalkMovement::TeleportTo(Vector3,BasePlayer): Void");
		return reinterpret_cast<void(__fastcall*)(PlayerWalkMovement*, Vector3, BasePlayer*)>(off)(this, pos, LocalPlayer::Entity());
	}
	//STATIC_FUNCTION("Assembly-CSharp::PlayerWalkMovement::TeleportTo(Vector3,BasePlayer): Void", TeleportTo, void(Vector3, BasePlayer*));
	static inline void(*UpdateVelocity_)(PlayerWalkMovement*) = nullptr;
	void UpdateVelocity() {
		return UpdateVelocity_(this);
	}
	static inline void(*HandleJumping_)(PlayerWalkMovement*, ModelState*, bool, bool) = nullptr;
	void HandleJumping(ModelState* modelState, bool wantsJump, bool jumpInDirection = false) {
		return HandleJumping_(this, modelState, wantsJump, jumpInDirection);
	}
	static inline void(*HandleRunDuckCrawl_)(PlayerWalkMovement*, ModelState*, bool, bool, bool) = nullptr;
	void HandleRunDuckCrawl(ModelState* state, bool wantsRun, bool wantsDuck, bool wantsCrawl) {
		return HandleRunDuckCrawl_(this, state, wantsRun, wantsDuck, wantsCrawl);
	}
	void Jump(ModelState* state)
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::PlayerWalkMovement::Jump(ModelState,Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(PlayerWalkMovement*, ModelState*, bool)>(off)(this, state, false);
	}
};
class Phrase {
public:
	const wchar_t* english() {
		try {
			static auto off = OFFSET("Rust.Localization::Phrase::english");
			if (!this) return L"";

			if (!(*reinterpret_cast<System::String**>(this + off))
				|| !(*reinterpret_cast<System::String**>(this + off))->buffer
				) return L"";
			return (*reinterpret_cast<System::String**>(this + off))->buffer;
		}
		catch (...) {};
	}
};
class Renderer_;
class SkinnedMeshRenderer;
class Wearable : public Component {
public:
	FIELD("Assembly-CSharp::Wearable::renderers", renderers, List<Renderer_*>*);
	FIELD("Assembly-CSharp::Wearable::skinnedRenderers", skinnedRenderers, List<SkinnedMeshRenderer*>*);
};
class ItemModWearable {
public:
	Wearable* targetWearable() {
		if (!this) return nullptr;
		static auto off = METHOD("Assembly-CSharp::ItemModWearable::get_targetWearable(): Wearable");
		return reinterpret_cast<Wearable * (__fastcall*)(ItemModWearable*)>(off)(this);
	}
};
class WaterLevel {
public:
	STATIC_FUNCTION("Assembly-CSharp::WaterLevel::Test(Vector3,Boolean,Boolean,BaseEntity): Boolean", Test, bool(Vector3, bool, bool, BaseEntity*));
};
enum class EnvironmentType : int {
	Building = 2,
	Elevator = 8,
	Outdoor = 4,
	PlayerConstruction = 16,
	Submarine = 128,
	TrainTunnels = 32,
	Underground = 1,
	UnderwaterLab = 64
};

class ItemDefinition : public Component {
public:
	FIELD("Assembly-CSharp::ItemDefinition::displayName", displayName, Phrase*);
	FIELD("Assembly-CSharp::ItemDefinition::itemid", itemid, int);
	FIELD("Assembly-CSharp::ItemDefinition::<ItemModWearable>k__BackingField", itemModWearable, ItemModWearable*);
	const wchar_t* shortname() {
		if (!this) return L"";
		static auto off = OFFSET("Assembly-CSharp::ItemDefinition::shortname");
		return (*reinterpret_cast<System::String**>(this + off))->buffer;
	}
};
struct Ammo {
	int id[2];
	float speed;
};
struct Weapon_M {
	int id;
	const char* name;
	Ammo ammo[4];
	int category; //-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
};
Weapon_M infom_t[]{
Weapon_M{1090916276, xorstr_("Pitchfork"), {Ammo{{0}, 25}}, 1 },
Weapon_M{1540934679, xorstr_("Wooden Spear"), {Ammo{{0}, 25}}, 1 },
Weapon_M{1814288539, xorstr_("Bone Knife"), {Ammo{{0}, 20}}, 1 },
Weapon_M{-363689972, xorstr_("Snowball"), {Ammo{{0}, 20}}, 1 },
Weapon_M{1789825282, xorstr_("Candy Cane Club"), {Ammo{{0}, 20}}, 1 },
Weapon_M{-1137865085, xorstr_("Machete"), {Ammo{{0}, 20}}, 1 },
Weapon_M{1711033574, xorstr_("Bone Club"), {Ammo{{0}, 20}}, 1 },
Weapon_M{-1966748496, xorstr_("Mace"), {Ammo{{0}, 18}}, 1 },
Weapon_M{-194509282, xorstr_("Butcher Knife"), {Ammo{{0}, 20}}, 1 },
Weapon_M{1326180354, xorstr_("Salvaged Sword"), {Ammo{{0}, 20}}, 1 },
Weapon_M{-1469578201, xorstr_("Longsword"), {Ammo{{0}, 18}}, 1 },
Weapon_M{-1978999529, xorstr_("Salvaged Cleaver"), {Ammo{{0}, 18}}, 1 },
Weapon_M{1602646136, xorstr_("Stone Spear"), {Ammo{{0}, 30}}, 1 },
Weapon_M{2040726127, xorstr_("Combat Knife"), {Ammo{{0}, 30}}, 1 },
Weapon_M{963906841, xorstr_("Rock"), {Ammo{{0}, 18}}, 1 },
};

class Texture {

};

class Texture2D : public Texture {
public:
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Texture2D::get_whiteTexture(): Texture2D", white, Texture2D* ());
};

class Sprite {
public:
	FIELD("UnityEngine.CoreModule::UnityEngine::Sprite::texture", texture, Texture*);
	FIELD("UnityEngine.CoreModule::UnityEngine::Sprite::textureRect", textureRect, Rect);
};

class Item {
public:
	FIELD("Assembly-CSharp::Item::uid", uid, uint32_t);
	FIELD("Assembly-CSharp::Item::amount", amount, int);
	FIELD("Assembly-CSharp::Item::info", info, ItemDefinition*);

	template<typename T = void*>
	T* heldEntity() {
		if (!this) return nullptr;
		static auto off = OFFSET("Assembly-CSharp::Item::heldEntity");
		return *reinterpret_cast<T**>(this + off);
	}
	int GetID() {
		DWORD64 Info = read((DWORD64)this + O::Item::info, DWORD64); // public ItemDefinition info;
		int ID = read(Info + O::ItemDefinition::itemid, int); // public int itemid; //ItemDefinition
		return ID;
	}
	Weapon_M infom_() {
		int ID = info()->itemid();
		for (Weapon_M k : infom_t) {
			if (k.id == ID) {
				return k;
			}
		}
		return Weapon_M{ 0 };
	}
};
class ItemContainer {
public:
	FIELD("Assembly-CSharp::ItemContainer::itemList", itemList, List<Item*>*);
};
class PlayerInventory {
public:
	FIELD("Assembly-CSharp::PlayerInventory::containerBelt", containerBelt, ItemContainer*);
	FIELD("Assembly-CSharp::PlayerInventory::containerWear", containerWear, ItemContainer*);
	FIELD("Assembly-CSharp::PlayerInventory::containerMain", containerMain, ItemContainer*);
};
class PlayerEyes : public Component {
public:
	FIELD("Assembly-CSharp::PlayerEyes::viewOffset", viewOffset, Vector3);
	FIELD("Assembly-CSharp::PlayerEyes::<bodyRotation>k__BackingField", bodyRotation, Quaternion);
	static Vector3 EyeOffset() {
		static auto clazz = CLASS("Assembly-CSharp::PlayerEyes");
		return *reinterpret_cast<Vector3*>(std::uint64_t(clazz->static_fields));
	}
	Vector3 position() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_position(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 center() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_center(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Quaternion rotation() {
		if (!this) return Quaternion{};
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_rotation(): Quaternion");
		return reinterpret_cast<Quaternion(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 MovementForward() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::MovementForward(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 MovementRight() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::MovementRight(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 BodyForward() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::BodyForward(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Ray BodyRay() {
		if (!this) return Ray();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::BodyRay(): Ray");
		return reinterpret_cast<Ray(__fastcall*)(PlayerEyes*)>(off)(this);
	}

	static inline Vector3(*BodyLeanOffset_)(PlayerEyes*) = nullptr;
	Vector3 BodyLeanOffset() {
		return BodyLeanOffset_(this);
	}
	static inline void(*DoFirstPersonCamera_)(PlayerEyes*, Component*) = nullptr;
	void DoFirstPersonCamera(Component* cam) {
		return DoFirstPersonCamera_(this, cam);
	}
};


class ModelState {
public:
	enum class Flags : uint32_t {
		Ducked = 1,
		Jumped = 2,
		OnGround = 4,
		Sleeping = 8,
		Sprinting = 16,
		OnLadder = 32,
		Flying = 64,
		Aiming = 128,
		Prone = 256,
		Mounted = 512,
		Relaxed = 1024,
		OnPhone = 2048,
	};
	FIELD("Rust.Data::ModelState::flags", flags, int);
	void set_jumped(bool value) {
		if (!this) return;
		static auto off = METHOD("Rust.Data::ModelState::set_jumped(Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(ModelState*, bool)>(off)(this, value);
	}
	void set_ducked(bool value) {
		if (!this) return;
		static auto off = METHOD("Rust.Data::ModelState::set_ducked(Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(ModelState*, bool)>(off)(this, value);
	}
	void set_mounted(bool value) {
		if (!this) return;
		static auto off = METHOD("Rust.Data::ModelState::set_mounted(Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(ModelState*, bool)>(off)(this, value);
	}
	FIELD("Rust.Data::ModelState::poseType", poseType, int);

	bool mounted() {
		if (!this) return false;
		static auto ptr = METHOD("Rust.Data::ModelState::get_mounted(): Boolean");
		return reinterpret_cast<bool(*)(ModelState*)>(ptr)(this);
	}
	static inline void(*set_flying_)(ModelState*, bool) = nullptr;
	void set_flying(bool state) {
		set_flying_(this, state);
	}
	void RemoveFlag(ModelState::Flags flag) {
		int flags = Read<int>((DWORD64)this + 0x20);
		flags &= ~(int)flag;
		Write<int>((DWORD64)this + 0x20, flags);
	}

	void SetFlag(ModelState::Flags flag) {
		int flags = Read<int>((DWORD64)this + 0x20);
		Write<int>((DWORD64)this + 0x20, flags |= (int)flag);
	}
};
class ViewmodelBob {
public:
	FIELD("Assembly-CSharp::ViewmodelBob::bobSpeedWalk", bobSpeedWalk, float);
	FIELD("Assembly-CSharp::ViewmodelBob::bobSpeedRun", bobSpeedRun, float);
	FIELD("Assembly-CSharp::ViewmodelBob::bobAmountWalk", bobAmountWalk, float);
	FIELD("Assembly-CSharp::ViewmodelBob::bobAmountRun", bobAmountRun, float);
	FIELD("Assembly-CSharp::ViewmodelBob::leftOffsetRun", leftOffsetRun, float);


	static inline void(*Apply_)(ViewmodelBob*, uintptr_t, float) = nullptr;
	void Apply(uintptr_t vm, float fov) {
		Apply_(this, vm, fov);
	}
};
class ViewmodelSway {
public:
	static inline void(*Apply_)(ViewmodelSway*, uintptr_t) = nullptr;
	void Apply(uintptr_t vm) {
		Apply_(this, vm);
	}
};
class ViewmodelLower {
public:
	FIELD("Assembly-CSharp::ViewmodelLower::lowerOnSprint", lowerOnSprint, bool);
	FIELD("Assembly-CSharp::ViewmodelLower::lowerWhenCantAttack", lowerWhenCantAttack, bool);
	FIELD("Assembly-CSharp::ViewmodelLower::lowerScale", lowerScale, float);
	FIELD("Assembly-CSharp::ViewmodelLower::shouldLower", shouldLower, bool);
	static inline void(*Apply_)(ViewmodelLower*, uintptr_t) = nullptr;
	void Apply(uintptr_t vm) {
		Apply_(this, vm);
	}
};
class UIPaintableImage {
public:

	FIELD("Assembly-CSharp::UIPaintableImage::texture", texture_ui, Texture2D*);

	static inline void( *Update_ )( UIPaintableImage* ) = nullptr;
	void Update(uintptr_t byte) {
		return Update_(this);
	}


};
class ViewmodelClothing {
public:
	FIELD("Assembly-CSharp::ViewmodelClothing::SkeletonSkins", SkeletonSkins, Array<uintptr_t>*);
	static inline void(*CopyToSkeleton_)(ViewmodelClothing*, uintptr_t, GameObject*, Item*) = nullptr;
	void CopyToSkeleton(uintptr_t skel, GameObject* parent, Item* item) {
		CopyToSkeleton_(this, skel, parent, item);
	}
};
class BaseViewModel : public Component {
public:
	FIELD("Assembly-CSharp::BaseViewModel::bob", bob, ViewmodelBob*);
	FIELD("Assembly-CSharp::BaseViewModel::lower", lower, ViewmodelLower*);
	static List<BaseViewModel*>* ActiveModels() {
		static auto clazz = CLASS("Assembly-CSharp::BaseViewModel");
		return *reinterpret_cast<List<BaseViewModel*>**>(std::uint64_t(clazz->static_fields) + 0x8);
	}
	static auto ActiveModel() -> BaseViewModel* {
		static auto off = METHOD("Assembly-CSharp::BaseViewModel::get_ActiveModel(): BaseViewModel");
		return reinterpret_cast<BaseViewModel * (__fastcall*)()>(off)();
	}
	FIELD("Assembly-CSharp::BaseViewModel::model", model, Model*);
};
class ViewModel : public Component {
public:
	FIELD("Assembly-CSharp::ViewModel::instance", instance, BaseViewModel*);
	FIELD("Assembly-CSharp::ViewModel::viewModelPrefab", viewModelPrefab, Component*);
	static inline void(*Play_)(ViewModel*, System::String*, int) = nullptr;
	void Play(System::String* name, int layer = 0) {
		Play_(this, name, layer);
	}
};
class HeldEntity : public BaseEntity {
public:
	FIELD("Assembly-CSharp::HeldEntity::viewModel", viewModel, ViewModel*);
	static inline void(*AddPunch_)(HeldEntity*, Vector3, float) = nullptr;
	void AddPunch(Vector3 amount, float duration) {
		return AddPunch_(this, amount, duration);
	}
	Item* GetItem() {
		if (!this) return nullptr;
		static auto off = METHOD("Assembly-CSharp::HeldEntity::GetItem(): Item");
		return reinterpret_cast<Item * (__fastcall*)(HeldEntity*)>(off)(this);
	}
};

enum class EventType : int {
	Zero = 0,
	Repaint = 7
};
class Event {
public:
	STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::Event::get_current(): Event", get_current, Event* ());
	EventType get_type() {
		if (!this) return EventType::Zero;
		static auto off = METHOD("UnityEngine.IMGUIModule::UnityEngine::Event::get_type(): EventType");
		return reinterpret_cast<EventType(__fastcall*)(Event*)>(off)(this);
	}
};
class GameManifest
{
public:
	static Object* GUIDToObject(System::String* guid) {
		static auto ptr = METHOD("Assembly-CSharp::GameManifest::GUIDToObject(String): Object");
		return reinterpret_cast<Object * (__fastcall*)(System::String*)>(ptr)(guid);
	}
};
template<typename T = Object>
class ResourceRef {
public:
	T* Get() {
		if (!this) return nullptr;
		System::String* guid = *reinterpret_cast<System::String**>(this + 0x10);
		T* _cachedObject = (T*)GameManifest::GUIDToObject(guid);

		return _cachedObject;
	}
};
class SkinnedMeshRenderer : public Renderer_ {
public:

};
class ItemModProjectile {
public:
	static inline float(*GetRandomVelocity_)(ItemModProjectile*) = nullptr;

	float GetRandomVelocity() {
		return GetRandomVelocity_(this);
	}
	FIELD("Assembly-CSharp::ItemModProjectile::numProjectiles", numProjectiles, int);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileVelocity", projectileVelocity, float);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileSpread", projectileSpread, float);
	FIELD("Assembly-CSharp::ItemModProjectile::ammoType", ammoType, int);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileVelocitySpread", projectileVelocitySpread, float);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileObject", projectileObject, ResourceRef<GameObject>*);


};
class StringPool {
public:
	static uint32_t Get(const char* str) {
		static auto off = METHOD("Assembly-CSharp::StringPool::Get(String): UInt32");
		return reinterpret_cast<uint32_t(__fastcall*)(System::String*)>(off)(System::String::New(str));
	}

	static System::String* Get(uint32_t i) {
		static auto off = METHOD("Assembly-CSharp::StringPool::Get(UInt32): String");
		return reinterpret_cast<System::String * (__fastcall*)(uint32_t)>(off)(i);
	}
};
class Attack;
class HitTest {
public:
	static HitTest* New()
	{
		HitTest* hitTest = il2cpp_object_new<HitTest*>(CLASS("Assembly-CSharp::HitTest"));

		return hitTest;
	}
	FIELD("Assembly-CSharp::HitTest::type", type, Type);
	FIELD("Assembly-CSharp::HitTest::Radius", Radius, float);
	FIELD("Assembly-CSharp::HitTest::Forgiveness", Forgiveness, float);
	FIELD("Assembly-CSharp::HitTest::MaxDistance", MaxDistance, float);
	FIELD("Assembly-CSharp::HitTest::MultiHit", MultiHit, bool);
	FIELD("Assembly-CSharp::HitTest::BestHit", BestHit, bool);
	FIELD("Assembly-CSharp::HitTest::AttackRay", AttackRay, Ray);
	FIELD("Assembly-CSharp::HitTest::DidHit", DidHit, bool);
	FIELD("Assembly-CSharp::HitTest::gameObject", gameObject, GameObject*);
	FIELD("Assembly-CSharp::HitTest::ignoreEntity", ignoreEntity, BaseEntity*);
	FIELD("Assembly-CSharp::HitTest::HitEntity", HitEntity, BaseNetworkable*);
	FIELD("Assembly-CSharp::HitTest::HitPoint", HitPoint, Vector3);
	FIELD("Assembly-CSharp::HitTest::HitNormal", HitNormal, Vector3);
	FIELD("Assembly-CSharp::HitTest::HitDistance", HitDistance, float);
	FIELD("Assembly-CSharp::HitTest::HitTransform", HitTransform, Transform*);
	FIELD("Assembly-CSharp::HitTest::HitPart", HitPart, uint32_t);
	FIELD("Assembly-CSharp::HitTest::HitMaterial", HitMaterial, System::String*);

	Vector3 HitPointWorld() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::HitTest::HitPointWorld(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(HitTest*)>(off)(this);
	}

	Vector3 HitNormalWorld() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::HitTest::HitNormalWorld(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(HitTest*)>(off)(this);
	}
	static inline Attack* (*BuildAttackMessage_)(HitTest*, BaseEntity*) = nullptr;
	Attack* BuildAttackMessage(BaseEntity* a1) {
		return BuildAttackMessage_(this, a1);
	}
};
enum QueryTriggerInteraction {
	UseGlobal = 0,
	Ignore = 1,
	Collide = 2,
};
TickInterpolator ticks;
Vector3 cLastTickPos{};
class FPS {
public:
	/*STATIC_FUNCTION("Assembly-CSharp::ConVar::FPS::set_graph(Int32): Void", set_graph, void(int));*/
};
class Physics {
public:
	/*Vector3 get_gravity()
	{
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.PhysicsModule::UnityEngine::Physics::gravity::get_gravity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(Physics*)>(off)(this);
	}*/
	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::Raycast(Vector3,Vector3,RaycastHit&,Single,Int32,QueryTriggerInteraction): Boolean",
		RaycastQTI,
		bool(Vector3,
			Vector3,
			RaycastHit*,
			float,
			int,
			QueryTriggerInteraction));
	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::Raycast(Ray,Single,Int32): Boolean",
		Raycast,
		bool(Ray,
			float,
			int));
	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::Raycast(Vector3,Vector3,RaycastHit&,Single): Boolean",
		RaycastG,
		bool(Vector3,
			Vector3,
			RaycastHit*,
			float));
	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::SphereCast(Ray,Single,Single,Int32): Boolean", SphereCast, bool(Ray, float, float, int));
	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::get_gravity(): Vector3", get_gravity, Vector3());
	static void IgnoreLayerCollision(int layer1, int layer2, bool ignore) {
		__try {
			return reinterpret_cast<void(*)(int, int, bool)>(il2cpp_resolve_icall(xorstr_("UnityEngine.Physics::IgnoreLayerCollision")))(layer1, layer2, ignore);
		}
		__except (SafeExecution::fail(GetExceptionCode(), GetExceptionInformation())) {
			return;
		};
	}

};
class unk {
public:

};

class Input {
public:
	STATIC_FUNCTION("UnityEngine.InputLegacyModule::UnityEngine::Input::GetKeyDown(KeyCode): Boolean", GetKeyDown, bool(KeyCode));
	STATIC_FUNCTION("UnityEngine.InputLegacyModule::UnityEngine::Input::GetKey(KeyCode): Boolean", GetKey, bool(KeyCode));
};
class Projectile : public Component {
public:
	FIELD("Assembly-CSharp::ItemModProjectile::ammoType", ammoType, int);
	FIELD("Assembly-CSharp::Projectile::integrity", _integrity, float);
	FIELD("Assembly-CSharp::Projectile::initialDistance", _initialDistance, float);
	FIELD("Assembly-CSharp::Projectile::penetrationPower", penetrationPower, float);
	FIELD("Assembly-CSharp::Projectile::swimRandom", swimRandom, float);
	FIELD("Assembly-CSharp::Projectile::swimScale", swimScale, Vector3);
	FIELD("Assembly-CSharp::Projectile::swimSpeed", swimSpeed, Vector3);
	FIELD("Assembly-CSharp::Projectile::tumbleAxis", tumbleAxis, Vector3);
	FIELD("Assembly-CSharp::Projectile::tumbleSpeed", tumbleSpeed, float);
	FIELD("Assembly-CSharp::Projectile::traveledTime", traveledTime, float);
	FIELD("Assembly-CSharp::Projectile::previousTraveledTime", previousTraveledTime, float);
	FIELD("Assembly-CSharp::Projectile::launchTime", launchTime, float);
	FIELD("Assembly-CSharp::Projectile::closeFlybyDistance", closeFlybyDistance, float);
	FIELD("Assembly-CSharp::Projectile::drag", drag, float);
	FIELD("Assembly-CSharp::Projectile::thickness", thickness, float);
	FIELD("Assembly-CSharp::Projectile::projectileID", projectileID, int);
	FIELD("Assembly-CSharp::Projectile::mod", mod, ItemModProjectile*);
	FIELD("Assembly-CSharp::Projectile::traveledDistance", traveledDistance, float);
	FIELD("Assembly-CSharp::Projectile::initialDistance", initialDistance, float);
	FIELD("Assembly-CSharp::Projectile::integrity", integrity, float);
	FIELD("Assembly-CSharp::Projectile::ricochetChance", ricochetChance, float);
	FIELD("Assembly-CSharp::Projectile::currentPosition", currentPosition, Vector3);
	FIELD("Assembly-CSharp::Projectile::hitTest", hitTest, HitTest*);
	FIELD("Assembly-CSharp::Projectile::currentVelocity", currentVelocity, Vector3);
	FIELD("Assembly-CSharp::Projectile::gravityModifier", gravityModifier, float);
	FIELD("Assembly-CSharp::Projectile::previousVelocity", previousVelocity, Vector3);
	FIELD("Assembly-CSharp::Projectile::previousPosition", previousPosition, Vector3);
	FIELD("Assembly-CSharp::Projectile::initialVelocity", initialVelocity, Vector3);
	static inline void(*Launch_)(Projectile*) = nullptr;
	void Launch() {
		return Launch_(this);
	}
	static inline void(*DoMovement_)(Projectile*, float) = nullptr;
	void DoMovement(float deltaTime) {
		this->swimScale() = Vector3(0.f, 0.f, 0.f);
		this->swimSpeed( ) = Vector3(0.f, 0.f, 0.f);/* we dont want random ass projectile spread */
		return DoMovement_(this, deltaTime);
	}
	static inline void(*Update_)(Projectile*) = nullptr;
	void Update() {
		return Update_(this);
	}
	static inline void(*Retire_)(Projectile*) = nullptr;
	void Retire() {
		return Retire_(this);
	}
	static inline bool(*Refract_)(Projectile*, uint64_t&, Vector3, Vector3, float) = nullptr;
	bool Refract(Projectile* prj, uint64_t& seed, Vector3 point, Vector3 normal, float resistance) {
		return Refract_(this, seed, point, normal, resistance);
	}
	static inline void(*SetEffectScale_)(Projectile*, float) = nullptr;
	void SetEffectScale(float sca) {
		return SetEffectScale_(this, sca);
	}
	static inline bool(*DoHit_)(Projectile*, HitTest*, Vector3, Vector3) = nullptr;
	bool DoHit(HitTest* test, Vector3 point, Vector3 world) {
		if (funcs::weapon::hitmaterial)
		{
			test->HitMaterial() = System::String::New(xorstr_("Gingerbread"));
		}
		return DoHit_(this, test, point, world);
	}

	void UpdateFUNC()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::Projectile::Update(): Void");
		return reinterpret_cast<void(__fastcall*)(Projectile*)>(off)(this);
	}
	void UpdateVelocity(float delta) {
		static auto off = METHOD("Assembly-CSharp::Projectile::UpdateVelocity(Single): Void");
		return reinterpret_cast<void(__fastcall*)(Projectile*, float)>(off)(this, delta);
	}
	bool isAuthoritative() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::Projectile::get_isAuthoritative(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Projectile*)>(off)(this);
	}
	bool isAlive() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::Projectile::get_isAlive(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Projectile*)>(off)(this);
	}
};
class AttackEntity : public BaseEntity {
public:
	void StartAttackCooldown(float cooldown)
	{
		if (!this) return;

		static auto off = METHOD("Assembly-CSharp::AttackEntity::StartAttackCooldown(Single): Void");

		return reinterpret_cast<void(__fastcall*)(AttackEntity*, float)>(off)(this, cooldown);
	}
	bool HasAttackCooldown()
	{
		if (!this) return false;

		static auto off = METHOD("Assembly-CSharp::AttackEntity::HasAttackCooldown(): Boolean");

		return reinterpret_cast<bool(__fastcall*)(AttackEntity*)>(off)(this);
	}
	FIELD("Assembly-CSharp::AttackEntity::lastTickTime", lastTickTime, float);
	FIELD("Assembly-CSharp::AttackEntity::repeatDelay", repeatDelay, float);
	FIELD("Assembly-CSharp::AttackEntity::deployDelay", deployDelay, float);
	FIELD("Assembly-CSharp::AttackEntity::timeSinceDeploy", timeSinceDeploy, float);
	FIELD("Assembly-CSharp::AttackEntity::nextAttackTime", nextAttackTime, float);
};
class ItemIcon {
public:
	FIELD("Assembly-CSharp::ItemIcon::queuedForLooting", queuedForLooting, bool);

	static inline void (*StartCoroutine_)(ItemIcon*) = nullptr;
	void TryToMove() {
		return StartCoroutine_(this);
	}

	void RunTimedAction() {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::ItemIcon::RunTimedAction(): Void");
		return reinterpret_cast<void(__fastcall*)(ItemIcon*)>(off)(this);
	}
};
class BaseMelee : public AttackEntity {
public:
	//STATIC_FUNCTION("Assembly-CSharp::BaseMelee::ProcessAttack(HitTest): Void", ProcessAttack, void(HitTest*));
	void StartAttackCooldown(float cooldown)
	{
		if (!this) return;

		static auto off = METHOD("Assembly-CSharp::AttackEntity::StartAttackCooldown(Single): Void");

		return reinterpret_cast<void(__fastcall*)(AttackEntity*, float)>(off)(this, cooldown);
	}

	void DoAttack(HitTest* test)
	{
		if (!this) return;

		static auto off = METHOD("Assembly-CSharp::BaseMelee::ProcessAttack(HitTest): Void");

		return reinterpret_cast<void(__fastcall*)(BaseMelee*, HitTest*)>(off)(this, test);
	}
	void DoThrow()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseMelee::DoThrow(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseMelee*)>(off)(this);
	}
	bool get_CanThrow()
	{
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::BaseMelee::get_CanThrow(): Boolean");
		return reinterpret_cast<bool(*)(BaseMelee*)>(off)(this);
	}
	static inline void (*ProcessAttack_)(BaseMelee*, HitTest*) = nullptr;
	FIELD("Assembly-CSharp::BaseMelee::maxDistance", maxDistance, float);
	void ProcessAttack(HitTest* test) {
		return ProcessAttack_(this, test);
	}
};
class Misc {
public:
	static float Magnitude(Vector3 a)
	{
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Vector3::Magnitude(Vector3): Single");
		return reinterpret_cast<float(*)(Vector3)>(off)(a);
	}
	static float Magnitude2D(Vector3 v)
	{
		static auto off = METHOD("Rust.Global::UnityEngine::Vector3Ex::Magnitude2D(Vector3): Single");
		return reinterpret_cast<float(*)(Vector3)>(off)(v);
	}
};
class Speargun {
public:
	static inline bool (*CanAttack_)(Speargun*) = nullptr;
	bool CanAttack() {
		return CanAttack_(this);
	}
};
class BaseProjectile : public AttackEntity {
public:
	class Magazine {
	public:
		FIELD("Assembly-CSharp::Magazine::ammoType", ammoType, ItemDefinition*);
		FIELD("Assembly-CSharp::Magazine::contents", contents, int);
		FIELD("Assembly-CSharp::Magazine::capacity", capacity, int);
	};
	static inline Projectile* (*CreateProjectile_)(BaseProjectile*, System::String*, Vector3, Vector3, Vector3) = nullptr;
	Projectile* CreateProjectile(System::String* prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity) {
		Projectile* projectile = CreateProjectile_(this, prefabPath, pos, forward, velocity);
		return projectile;
	}
	//static inline Projectile* (*DoReload_)(BaseProjectile*) = nullptr;
	//Projectile* DoReload(BaseProjectile*) {
	//	return DoReload_(this);
	//}
	FIELD("Assembly-CSharp::BaseProjectile::primaryMagazine", primaryMagazine, Magazine*);
	FIELD("Assembly-CSharp::BaseProjectile::projectileVelocityScale", projectileVelocityScale, float);
	FIELD("Assembly-CSharp::BaseProjectile::aimCone", aimCone, float);
	FIELD("Assembly-CSharp::BaseProjectile::hipAimCone", hipAimCone, float);
	FIELD("Assembly-CSharp::BaseProjectile::nextReloadTime", nextReloadTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::lastShotTime", lastShotTime, float);

	FIELD("Assembly-CSharp::BaseProjectile::reloadTime", reloadTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::automatic", automatic, bool);
	FIELD("Assembly-CSharp::BaseProjectile::aimSway", aimSway, float);
	FIELD("Assembly-CSharp::BaseProjectile::aimSwaySpeed", aimSwaySpeed, float);
	FIELD("Assembly-CSharp::BaseProjectile::isReloading", isReloading, bool);
	FIELD("Assembly-CSharp::BowWeapon::arrowBack", arrowBack, float);
	FIELD("Assembly-CSharp::BowWeapon::attackReady", attackReady, bool);
	//STATIC_FUNCTION("Assembly-CSharp::BaseProjectile::DoReload(): Void", DoReload);

	void DoAttack() {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::DoAttack(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void ShotFired()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::ShotFired(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void UpdateAmmoDisplay()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::UpdateAmmoDisplay(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void ResetReloadCooldown()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::ResetReloadCooldown(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void DidAttackClientside()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::DidAttackClientside(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void BeginCycle()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::BeginCycle(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	bool Empty() {
		if (!this) return true;
		if (!this->primaryMagazine()) return true;

		return this->primaryMagazine()->contents() <= 0;
	}
	bool HasReloadCooldown() {
		return GLOBAL_TIME < this->nextReloadTime();
	}
	void LaunchProjectile()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::LaunchProjectile(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	float CalculateCooldownTime(float nextTime, float cooldown) {
		float num = GLOBAL_TIME;
		float num2 = 0.f;

		float ret = nextTime;

		if (ret < 0.f) {
			ret = std::max(0.f, num + cooldown - num2);
		}
		else if (num - ret <= num2) {
			ret = std::min(ret + cooldown, num + cooldown);
		}
		else {
			ret = std::max(ret + cooldown, num + cooldown - num2);
		}
		return ret;
	}
};
class BaseLauncher : public BaseProjectile {
public:
	void LaunchRocket()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseLauncher::LaunchProjectile(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseLauncher*)>(off)(this);
	}
};
namespace ConVar {
	class Graphics {
	public:
		static float& _fov() {
			static auto clazz = CLASS("Assembly-CSharp::ConVar::Graphics");
			return *reinterpret_cast<float*>(std::uint64_t(clazz->static_fields) + 0x18);
		}
		static bool& chamsfix() {
			static auto clazz = CLASS("Assembly-CSharp::ConVar::Graphics");
			return *reinterpret_cast<bool*>(std::uint64_t(clazz->static_fields) + 0x85);
		}
	};


}
typedef struct _UncStr {
	char stub[0x10];
	int len;
	wchar_t str[1];
} *pUncStr;
class Effect {
public:
	//FIELD("Facepunch.Network::Network::Networkable::ID", ID, uint32_t);
	FIELD("Assembly-CSharp::Effect::worldPos", worldPos, Vector3);
	FIELD("Assembly-CSharp::Effect::reusableInstace", reusableInstace, Effect*);
	FIELD("Assembly-CSharp::Effect::pooledString", pooledString, System::String*);
};
class EffectNetwork {
public:
	static Effect* effect() {
		static auto c = CLASS("Assembly-CSharp::EffectNetwork");
		return *reinterpret_cast<Effect**>(std::uint64_t(c->static_fields));
	}
};
class EffectLibrary {
public:
	/*
	static inline void(*ClientUpdate_)(BasePlayer*) = nullptr;
	void ClientUpdate( ) {
		return ClientUpdate_(this);
	}*/
	static inline GameObject* (*CreateEffect_)(pUncStr, Effect*) = nullptr;
	GameObject* CreateEffect(pUncStr p, Effect* e)
	{
		return CreateEffect_(p, e);
	}
};
class CompoundBowWeapon {
public:
	FIELD("Assembly-CSharp::CompoundBowWeapon::currentHoldProgress", currentHoldProgress, float);

	float GetProjectileVelocityScale(bool getmax = false) {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::CompoundBowWeapon::GetProjectileVelocityScale(Boolean): Single");
		return reinterpret_cast<float(__fastcall*)(CompoundBowWeapon*, bool)>(off)(this, getmax);
	}
};
class FlintStrikeWeapon : public BaseProjectile {
public:
	FIELD("Assembly-CSharp::FlintStrikeWeapon::successFraction", successFraction, float);
	FIELD("Assembly-CSharp::FlintStrikeWeapon::_didSparkThisFrame", _didSparkThisFrame, bool);

	static inline void(*DoAttack_)(FlintStrikeWeapon*) = nullptr;
	void DoAttack() {
		return DoAttack_(this);
	}
};
class PlayerModel;
class Renderer_;
class SkinnedMultiMesh {
public:
	List<Renderer_*>* Renderers() {
		if (!this) return nullptr;
		static auto off = OFFSET("Assembly-CSharp::SkinnedMultiMesh::<Renderers>k__BackingField");
		return *reinterpret_cast<List<Renderer_*>**>(this + off);
	}
	static inline void(*RebuildModel_)(SkinnedMultiMesh*, PlayerModel*, bool) = nullptr;
	void RebuildModel(PlayerModel* model, bool reset) {
		return RebuildModel_(this, model, reset);
	}
};
class SkinSet {
public:
	FIELD("Assembly-CSharp::SkinSet::BodyMaterial", BodyMaterial, Material*);
	FIELD("Assembly-CSharp::SkinSet::HeadMaterial", HeadMaterial, Material*);
	FIELD("Assembly-CSharp::SkinSet::EyeMaterial", EyeMaterial, Material*);
};
class SkinSetCollection {
public:
	FIELD("Assembly-CSharp::SkinSetCollection::Skins", Skins, Array<SkinSet*>*);
};
class Mathf {
public:
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::FloorToInt(Single): Int32", FloorToInt, int(float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Max(Single,Single): Single", Max, float(float, float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Min(Single,Single): Single", Min, float(float, float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Clamp(Single,Single,Single): Single", Clamp, float(float, float, float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Abs(Single): Single", Abs, float(float));
};
class Mathx {
public:
	STATIC_FUNCTION("Rust.Global::Mathx::Decrement(Single): Single", Decrement, float(float));
	STATIC_FUNCTION("Rust.Global::Mathx::Increment(Single): Single", Increment, float(float));
	STATIC_FUNCTION("Rust.Global::Mathx::Max(Single,Single,Single): Single", Max, float(float, float, float));
};
class PlayerModel {
public:
	Vector3 newVelocity() {
		if (!this) return Vector3::Zero();
		static auto off = OFFSET("Assembly-CSharp::PlayerModel::newVelocity");
		return *reinterpret_cast<Vector3*>(this + off);
	}
	bool isNpc() {
		if (!this) return false;
		static auto off = OFFSET("Assembly-CSharp::PlayerModel::<IsNpc>k__BackingField");//OFFSET("Assembly-CSharp::PlayerModel::<IsNpc>k__BackingField");
		return *reinterpret_cast<bool*>(this + off);
	}


	void RebuildAll()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::PlayerModel::RebuildAll(): Void");
		return reinterpret_cast<void(__fastcall*)(PlayerModel*)>(off)(this);
	}

	void PlayCinematic(System::String* name, float overrideSpeed = 1)
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::PlayerModel::PlayCinematic(String,Single): Void");
		return reinterpret_cast<void(__fastcall*)(PlayerModel*, System::String*, float)>(off)(this, name, overrideSpeed);
	}

	FIELD("Assembly-CSharp::PlayerModel::_multiMesh", _multiMesh, SkinnedMultiMesh*);
	FIELD("Assembly-CSharp::PlayerModel::MaleSkin", MaleSkin, SkinSetCollection*);
	FIELD("Assembly-CSharp::PlayerModel::FemaleSkin", FemaleSkin, SkinSetCollection*);
	FIELD("Assembly-CSharp::PlayerModel::position", position, Vector3);
};
class TOD_AtmosphereParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_AtmosphereParameters::RayleighMultiplier", RayleighMultiplier, float);
	FIELD("Assembly-CSharp-firstpass::TOD_AtmosphereParameters::Fogginess", Fogginess, float);
};
class TOD_NightParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_NightParameters::AmbientMultiplier", AmbientMultiplier, float);
};
class TOD_SunParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_SunParameters::MeshSize", MeshSize, float);
	FIELD("Assembly-CSharp-firstpass::TOD_SunParameters::MeshBrightness", MeshBrightness, float);
	FIELD("Assembly-CSharp-firstpass::TOD_SunParameters::MeshContrast", MeshContrast, float);
};
class TOD_StarParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_StarParameters::Size", Size, float);
	FIELD("Assembly-CSharp-firstpass::TOD_StarParameters::Brightness", Brightness, float);
};
enum TOD_FogType {
	None = 0,
	Atmosphere = 1,
	Directional = 2,
	//Gradient = 3
};
class TOD_FogParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_FogParameters::Mode", Mode, TOD_FogType);
	FIELD("Assembly-CSharp-firstpass::TOD_FogParameters::HeightBias", HeightBias, float);
};
class TOD_CloudParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_CloudParameters::Size", Size, float);
	FIELD("Assembly-CSharp-firstpass::TOD_CloudParameters::Opacity", Opacity, float);
	FIELD("Assembly-CSharp-firstpass::TOD_CloudParameters::Coverage", Coverage, float);
	FIELD("Assembly-CSharp-firstpass::TOD_CloudParameters::Brightness", Brightness, float);
};
class TOD_DayParameters {
public:
	//FIELD("Assembly-CSharp-firstpass::TOD_DayParameters::", AmbientColor, );
	FIELD("Assembly-CSharp-firstpass::TOD_DayParameters::AmbientMultiplier", AmbientMultiplier, float);
	FIELD("Assembly-CSharp-firstpass::TOD_DayParameters::ReflectionMultiplier", ReflectionMultiplier, float);
};
class TOD_CycleParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_CycleParameters::Hour", Hour, float);
};
enum AmbientMode
{
	Skybox,
	Trilight,
	Flat,
	Custom
};
class RenderSettings {
public: 
	static inline void( *set_skybox_ )( RenderSettings* ) = nullptr;
	void set_skybox( ) {
		return set_skybox_(this);
	}
};


class TOD_Sky {
public:
	enum class AmbientMode {
		Skybox,
		Trilight,
		Flat,
		Custom
	};
	static List<TOD_Sky*>* instances() {
		static auto clazz = CLASS("Assembly-CSharp-firstpass::TOD_Sky");
		return *reinterpret_cast<List<TOD_Sky*>**>(std::uint64_t(clazz->static_fields));
	}
	static inline void(*UpdateAmbient_)(TOD_Sky*) = nullptr;
	void UpdateAmbient() {
		return UpdateAmbient_(this);
	}
	static inline void( *UpdateRenderSettings_ )( TOD_Sky* ) = nullptr;
	void UpdateRenderSettings( ) {
		return UpdateRenderSettings_(this);
	}
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Atmosphere", Atmosphere, TOD_AtmosphereParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Night", Night, TOD_NightParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Sun", Sun, TOD_SunParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Day", Day, TOD_DayParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Cycle", Cycle, TOD_CycleParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Stars", Stars, TOD_StarParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Clouds", Clouds, TOD_CloudParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Fog", Fog, TOD_FogParameters*);
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientMode(Rendering.AmbientMode): Void", set_ambientMode, void(AmbientMode));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientIntensity(Single): Void", set_ambientIntensity, void(float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientLight(Color): Void", set_ambientLight, void(Color));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_skybox(Material): Void", set_skybox, void(Material*));
};

class MonoBehaviour {
public:
	static inline System::Object_* (*StartCoroutine_)(MonoBehaviour*, System::Object_*) = nullptr;
	System::Object_* StartCoroutine(System::Object_* routine) {
		return StartCoroutine_(this, routine);
	}
};

class Attack {
public:
	FIELD("Rust.Data::ProtoBuf::Attack::hitID", hitID, uint32_t);
	FIELD("Rust.Data::ProtoBuf::Attack::hitBone", hitBone, uint32_t);
	FIELD("Rust.Data::ProtoBuf::Attack::hitMaterialID", hitMaterialID, uint32_t);
	FIELD("Rust.Data::ProtoBuf::Attack::hitPositionWorld", hitPositionWorld, Vector3);
	FIELD("Rust.Data::ProtoBuf::Attack::hitNormalWorld", hitNormalWorld, Vector3);
	FIELD("Rust.Data::ProtoBuf::Attack::pointStart", pointStart, Vector3);
	FIELD("Rust.Data::ProtoBuf::Attack::pointEnd", pointEnd, Vector3);
};
class PlayerAttack {
public:
	FIELD("Rust.Data::ProtoBuf::PlayerAttack::attack", attack, Attack*);
};
class PlayerProjectileAttack {
public:
	//FIELD("");
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileAttack::playerAttack", playerAttack, PlayerAttack*);
};
class InputMessage {
public:
	FIELD("Rust.Data::InputMessage::buttons", buttons, int);
	FIELD("Rust.Data::InputMessage::mouseDelta", mouseDelta, Vector3);
	FIELD("Rust.Data::InputMessage::aimAngles", aimAngles, Vector3);
	FIELD("Rust.Data::InputMessage::ShouldPool", ShouldPool, bool);
	FIELD("Rust.Data::InputMessage::_disposed", _disposed, bool);
};

class InputState {
public:
	FIELD("Assembly-CSharp::InputState::current", current, InputMessage*);
	FIELD("Assembly-CSharp::InputState::previous", previous, InputMessage*);
	static inline bool(*IsDown_)(InputState*, Button) = nullptr;
	bool IsDown(Button btn) {
		return IsDown_(this, btn);
	}
};
class TeamMember {
public:
	bool online() {
		return *reinterpret_cast<bool*>(this + 0x30);
	}
	uint64_t& userID() {
		return *reinterpret_cast<uint64_t*>(this + 0x18);
	}
	Vector3& position() {
		return *reinterpret_cast<Vector3*>(this + 0x24);
	}
	const wchar_t* displayName() {
		if (!this) return L"";
		return (*reinterpret_cast<System::String**>(this + 0x10))->buffer;
	}
};
class PlayerTeam {
public:
	FIELD("Assembly-CSharp::PlayerTeam::teamID", teamID, uint64_t);
	//	public ulong teamID; // 0x10

	List<TeamMember*>* members() {
		return *reinterpret_cast<List<TeamMember*>**>(this + 0x28);
	}
};

class Stream;

class PlayerTick
{
public:
	static inline void(*WriteToStreamDelta_)(PlayerTick*, Stream*, PlayerTick*) = nullptr;

	void WriteToStreamDelta(Stream* stream, PlayerTick* previous)
	{
		return WriteToStreamDelta_(this, stream, previous);
	}

	FIELD("Rust.Data::PlayerTick::position", position, Vector3);
};
class PlayerInput {
public:
	FIELD("Assembly-CSharp::PlayerInput::state", state, InputState*);
};
class BasePlayer;
class PlayerProjectileUpdate {
public:
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::projectileID", projectileId, int);
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::curPosition", curPosition, Vector3);
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::curVelocity", curVelocity, Vector3);
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::travelTime", travelTime, float);
	static PlayerProjectileUpdate* New()
	{
		return il2cpp_object_new<PlayerProjectileUpdate*>(CLASS("Rust.Data::ProtoBuf::PlayerProjectileUpdate"));
	}
};
struct Hammer : BaseMelee {
	void DoAttackShared(HitInfo* test)
	{
		if (!this) return;

		static auto off = METHOD("Assembly-CSharp::Hammer::DoAttackShared(HitInfo): Void");

		return reinterpret_cast<void(__fastcall*)(Hammer*, HitInfo*)>(off)(this, test);
	}
};
BasePlayer* target_ply = nullptr;
BasePlayer* cheater_train_target = nullptr;
BasePlayer* patrol_helicopter = nullptr;
BasePlayer* closest_ply = nullptr;
Bone_List AimSpotInt = head;

class BasePlayer : public BaseCombatEntity {
public:
	static inline bool(*CanAttack_)(BasePlayer*) = nullptr;
	static inline void(*OnLand_)(BasePlayer*, float) = nullptr;
	static inline void(*ClientInput_)(BasePlayer*, uintptr_t) = nullptr;
	static inline void(*Load_)(BasePlayer*, BaseNetworkable::LoadInfo*) = nullptr;


	static inline void( *Load2_ )( BasePlayer*, BaseNetworkable::LoadInfo* ) = nullptr;

	void Load(BaseNetworkable::LoadInfo* info)
	{
		return Load_(this, info);
	}

	void Load2(BaseNetworkable::LoadInfo* info)
	{
		return Load2_(this, info);
	}


	static inline void(*Loadbc_)(BasePlayer*, BaseNetworkable::LoadInfo*) = nullptr;

	void Loadbc(BaseNetworkable::LoadInfo* info)
	{
		return Loadbc_(this, info);
	}

	void OnLand(float fVelocity) {
		return OnLand_(this, fVelocity);
	}
	void ClientInput(uintptr_t unk) {
		return ClientInput_(this, unk);
	}
	bool CanAttack() {
		return CanAttack_(this);
	}
	static inline void(*ClientUpdate_)(BasePlayer*) = nullptr;
	void ClientUpdate() {
		return ClientUpdate_(this);
	}
	static inline void(*VisUpdateUsingCulling_)(BasePlayer*, float, bool) = nullptr;
	void VisUpdateUsingCulling(float a1, bool a2) {
		return VisUpdateUsingCulling_(this, a1, a2);
	}
	static inline void(*SendProjectileAttack_)(BasePlayer*, PlayerProjectileAttack*) = nullptr;
	void SendProjectileAttack(PlayerProjectileAttack* attack) {
		return SendProjectileAttack_(this, attack);
	}
	static inline void(*ClientUpdate_Sleeping_)(BasePlayer*) = nullptr;
	void ClientUpdate_Sleeping() {
		return ClientUpdate_Sleeping_(this);
	}
	static inline void(*SendClientTick_)(BasePlayer*) = nullptr;
	void SendClientTick() {
		return SendClientTick_(this);
	}

	/*static inline void(*ClientTick_)(BasePlayer*) = nullptr;
	void ClientTick() {
		return ClientTick_(this);
	}*/

	const wchar_t* _displayName() {
		if (!this) return L"";
		static auto off = OFFSET("Assembly-CSharp::BasePlayer::_displayName");
		return (*reinterpret_cast<System::String**>(this + off))->buffer;
	}

	void Drink()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::Drink(BasePlayer): Void");
		return reinterpret_cast<void(__fastcall*)(BasePlayer*)>(off)(this);
	}

	FIELD("Assembly-CSharp::BasePlayer::clothingWaterSpeedBonus", clothingWaterSpeedBonus, float);
	FIELD("Assembly-CSharp::BasePlayer::userID", userID, uint64_t);
	//	public ulong teamID; // 0x10
	FIELD("Assembly-CSharp::BasePlayer::mounted", mounted, BaseMountable*);
	FIELD("Assembly-CSharp::BasePlayer::movement", movement, PlayerWalkMovement*);
	FIELD("Assembly-CSharp::BasePlayer::modelState", modelState, ModelState*);
	FIELD("Assembly-CSharp::BasePlayer::playerModel", playerModel, PlayerModel*);
	FIELD("Assembly-CSharp::BasePlayer::input", input, PlayerInput*);
	FIELD("Assembly-CSharp::BasePlayer::clientTeam", clientTeam, PlayerTeam*);
	FIELD("Assembly-CSharp::BasePlayer::playerFlags", playerFlags, PlayerFlags);
	FIELD("Assembly-CSharp::BasePlayer::inventory", inventory, PlayerInventory*);
	FIELD("Assembly-CSharp::BasePlayer::clActiveItem", clActiveItem, uint32_t);
	FIELD("Assembly-CSharp::BasePlayer::maxProjectileID", maxProjectileID, int);
	FIELD("Assembly-CSharp::BasePlayer::eyes", eyes, PlayerEyes*);
	FIELD("Assembly-CSharp::BasePlayer::lastHeadshotSoundTime", lastHeadshotSoundTime, float);
	FIELD("Assembly-CSharp::BasePlayer::lastSentTickTime", lastSentTickTime, float);
	FIELD("Assembly-CSharp::BasePlayer::lastSentTick", lastSentTick, PlayerTick*);
	FIELD("Assembly-CSharp::BasePlayer::clientTickRate", clientTickRate, int);
	FIELD("Assembly-CSharp::BasePlayer::clientTickInterval", clientTickInterval, float);
	//FIELD("Assembly-CSharp::BasePlayer::SendClientTick", SendClientTick, void);
	//STATIC_FUNCTION("Assembly-CSharp::BasePlayer::SendClientTick(): Void", SendClientTick);
	bool GetKeyState(Button b) {
		return ((input()->state()->current()->buttons() & (int)b) == (int)b);
	}
	Vector3 GetCenter(bool ducked)
	{
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetCenter(Boolean): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BasePlayer*, bool)>(off)(this, ducked);
	}

	void consolemsg(System::String* value)
	{
		static auto off = METHOD("Assembly-CSharp::BasePlayer::ConsoleMessage(String): Void");
		return reinterpret_cast< void(__fastcall*)( BasePlayer*, System::String*) >( off )( this, value );
	}

	bool IsDucked() { // lad don't fancy calling functions in a non-game thread, eh, thy lad shall recreate it.
		if (!this) return false;

		if (this->movement() != nullptr)
			return this->movement()->Ducking() > 0.5f;

		return this->modelState() != nullptr && this->modelState()->flags() & 1;
	}
	Item* GetWeaponInfo(int Id) {
		DWORD64 Inventory = read(this + O::BasePlayer::inventory, DWORD64);
		DWORD64 Belt = read(Inventory + O::PlayerInventory::containerBelt, DWORD64); // containerBelt
		DWORD64 ItemList = read(Belt + O::ItemContainer::itemList, DWORD64);// public List<Item> itemList;
		DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (Item*)read(Items + 0x20 + (Id * 0x8), DWORD64);
	}
	List<Item*>* item_list_b() {
		DWORD64 Inventory = read(this + O::BasePlayer::inventory, DWORD64);
		DWORD64 Belt = read(Inventory + O::PlayerInventory::containerBelt, DWORD64); // containerBelt
		return read(Belt + O::ItemContainer::itemList, List<Item*>*);// public List<Item> itemList;
	}
	Item* GetClothesInfo(int Id) {
		DWORD64 Inventory = read(this + O::BasePlayer::inventory, DWORD64);
		DWORD64 Belt = read(Inventory + O::PlayerInventory::containerWear, DWORD64); // containerWear
		DWORD64 ItemList = read(Belt + O::ItemContainer::itemList, DWORD64);// public List<Item> itemList;
		DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (Item*)read(Items + 0x20 + (Id * 0x8), DWORD64);
	}
	List<Item*>* item_list_w() {
		DWORD64 Inventory = read(this + O::BasePlayer::inventory, DWORD64);
		DWORD64 Belt = read(Inventory + O::PlayerInventory::containerWear, DWORD64); // containerWear
		return read(Belt + O::ItemContainer::itemList, List<Item*>*);// public List<Item> itemList;
	}
	Item* GetActiveWeapon() {
		int ActUID = read(this + O::BasePlayer::clActiveItem, int);
		if (!ActUID) return nullptr;
		Item* ActiveWeapon;
		for (int i = 0; i < 6; i++)
			if (ActUID == (ActiveWeapon = GetWeaponInfo(i))->uid())
				return ActiveWeapon;
		return nullptr;
	}
	Transform* GetTransform(Bone_List bone) {
		uintptr_t player_model = read(this + O::BaseEntity::model, uintptr_t);// public Model model
		uintptr_t boneTransforms = read(player_model + O::Model::boneTransforms, uintptr_t);//public Transform[] boneTransforms;
		Transform* transform = read(boneTransforms + 0x20 + bone * 0x8, Transform*);
		return transform;
	}
	Transform* GetTransform(int bone) {
		uintptr_t player_model = read(this + O::BaseEntity::model, uintptr_t);// public Model model
		uintptr_t boneTransforms = read(player_model + O::Model::boneTransforms, uintptr_t);//public Transform[] boneTransforms;
		Transform* transform = read(boneTransforms + 0x20 + bone * 0x8, Transform*);
		return transform;
	}
	Vector3 BonePosition(Bone_List bone) {
		uintptr_t player_model = read(this + O::BaseEntity::model, uintptr_t);// public Model mode
		if ( !player_model ) return Vector3::Zero( );
		uintptr_t boneTransforms = read(player_model + O::Model::boneTransforms, uintptr_t);//public Transform[] boneTransforms;
		if ( !boneTransforms ) return Vector3::Zero( );
		Transform* transform = read(boneTransforms + 0x20 + bone * 0x8, Transform*);
		if ( !transform ) return Vector3::Zero( );
		return transform->position();
	}

	static float& Admintime() {
		static auto clazz = CLASS("Assembly-CSharp::ConVar::Admin");
		return *reinterpret_cast<float*>(std::uint64_t(clazz->static_fields) + 0x0);
	}
	// ret type is bone, found

	void add_modelstate_flag(ModelState::Flags flag) {
		int flags = this->modelState()->flags();

		this->modelState()->flags() = flags |= (int)flag;
	}
	void remove_modelstate_flag(ModelState::Flags flag) {
		int flags = this->modelState()->flags();

		flags &= ~(int)flag;

		this->modelState()->flags() = flags;
	}
	bool HasPlayerFlag(PlayerFlags flag) {
		if (!this) return false;

		return (playerFlags() & flag) == flag;
	}
	auto MaxEyeVelocity() -> float
	{
		if (!this) return 0.0f;

		float speed = this->GetMaxSpeed();

		const auto mounted = this->mounted();
		if (mounted)
		{
			return speed * 4.0f;
		}
		return speed;
	}

	//GetMountVelocity
	Vector3 GetMountVelocity() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetMountVelocity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BasePlayer*)>(off)(this);
	}
	//SendProjectileUpdate
	void SendProjectileUpdate(PlayerProjectileUpdate* a1) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::SendProjectileUpdate(PlayerProjectileUpdate): Void");
		return reinterpret_cast<void(__fastcall*)(BasePlayer*, PlayerProjectileUpdate*)>(off)(this, a1);
	}
	bool OnLadder() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::OnLadder(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(BasePlayer*)>(off)(this);
	}
	bool isGod( ) {
		if ( !this ) return false;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::IsGod(): Boolean");
		return reinterpret_cast< bool(__fastcall*)( BasePlayer* ) >( off )( this );
	}
	void Menu_AssistPlayer(BasePlayer* Player) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::Menu_AssistPlayer(BasePlayer): Void");
		return reinterpret_cast<void(__fastcall*)(BasePlayer*, BasePlayer*)>(off)(this, Player);
	}
	bool IsCrawling() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::IsCrawling(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(BasePlayer*)>(off)(this);
	}
	float GetRadius() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetRadius(): Single");
		return reinterpret_cast<float(__fastcall*)(BasePlayer*)>(off)(this);
	}
	float GetJumpHeight() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetJumpHeight(): Single");
		if (!off) return 0.f;
		return reinterpret_cast<float(__fastcall*)(BasePlayer*)>(off)(this);
	}
	float GetMaxSpeed() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetMaxSpeed(): Single");
		return reinterpret_cast<float(__fastcall*)(BasePlayer*)>(off)(this);
	}
	float MaxVelocity() {
		if (!this) return 0.f;

		if (this->mounted())
			return this->GetMaxSpeed() * 4;

		return this->GetMaxSpeed();
	}
	float GetHeight() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetHeight(Boolean): Single");
		return reinterpret_cast<float(__fastcall*)(BasePlayer*, bool)>(off)(this, this->IsDucked());
	}
	float GetHeight(bool ducked) {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetHeight(Boolean): Single");
		return reinterpret_cast<float(__fastcall*)(BasePlayer*, bool)>(off)(this, ducked);
	}
	static ListDictionary* visiblePlayerList() {
		static auto clazz = CLASS("Assembly-CSharp::BasePlayer");
		return *reinterpret_cast<ListDictionary**>(std::uint64_t(clazz->static_fields) + 0x8);
	}
	bool in_minicopter() {
		if (!this)
			return false;

		if (!this->mounted())
			return false;

		if (this->mounted()->GetVehicleParent()->class_name_hash() == STATIC_CRC32("MiniCopter")) {

			return true;
		}

		return false;
	}


	bool on_horse() {
		if (!this)
			return false;

		if (!this->mounted())
			return false;

		if (this->mounted()->GetVehicleParent()->class_name_hash() == STATIC_CRC32("Horse")) {
			return true;
		}

		return false;
	}
	bool is_target() {
		if (!target_ply)
			return false;

		if (!this)
			return false;

		return this->userID() == target_ply->userID();
	}

	bool is_teammate() {
		if (!this)
			return false;

		auto team = LocalPlayer::Entity()->clientTeam();
		if (team) {
			auto list = team->members();
			if (list) {
				for (int i = 0; i < list->size; i++) {
					auto member = reinterpret_cast<TeamMember*>(list->get(i));
					if (!member) continue;

					if (member->userID() == this->userID()) {
						return true;
					}
				}
			}
		}

		return false;
	}


	template<typename T = HeldEntity>
	T* GetHeldEntity() {
		if (!this) return nullptr;

		auto inventory = this->inventory();
		if (!inventory) return nullptr;

		auto belt = inventory->containerBelt();
		if (!belt) return nullptr;

		auto item_list = belt->itemList();
		if (!item_list) return nullptr;

		for (int i = 0; i < item_list->size; i++) {
			auto item = reinterpret_cast<Item*>(item_list->get(i));
			if (!item) continue;

			if (item->uid() == this->clActiveItem())
				return item->heldEntity<T>();
		}

		return nullptr;
	}
	Item* GetHeldItem() {
		if (!this) return nullptr;

		auto inventory = this->inventory();
		if (!inventory) return nullptr;

		auto belt = inventory->containerBelt();
		if (!belt) return nullptr;

		auto item_list = belt->itemList();
		if (!item_list) return nullptr;

		for (int i = 0; i < item_list->size; i++) {
			auto item = reinterpret_cast<Item*>(item_list->get(i));
			if (!item) continue;

			if (item->uid() == this->clActiveItem())
				return item;
		}

		return nullptr;
	}

	void HandChams()
	{
		if (!this) return;
		if (this->health() <= 5.0f || this->lifestate() == BaseCombatEntity::LifeState::Dead) return;

		if (!this->playerModel()) return;
		if (!this->playerModel()->_multiMesh()) return;
		if (!this->playerModel()->_multiMesh()->Renderers()) return;
		auto renderers = BaseViewModel::ActiveModel()->GetComponentsInChildren(Type::Renderer());
		for (int i = 0; i < renderers->size(); i++)
		{
			Renderer_* renderer = reinterpret_cast<Renderer_*>(renderers->get(i));
			if (!renderer) continue;
			if (!renderer->material()) continue;
			auto material = renderer->material();
			auto shader = material->shader();
			if (material)
			{
				//		printf("%ls\n", material->get_name()->buffer);

				static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::set_shader(Shader): Void");
				if (funcs::localplayer::heandchams)
				{
					if (material->get_name()->Contains(StringIl::New(xorstr_("Hand"))) || material->get_name()->Contains(StringIl::New(xorstr_("Arm"))) || material->get_name()->Contains(StringIl::New(xorstr_("DiverSuit_Gloves"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("Suit_Blue"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("ArcticHazmat_Body"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("BoneArmour"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("Jumpsuit"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("BunnyOnesie"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("BurlapHandWraps"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("shirt.burlap"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("Wetsuit"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("MakeshiftHazmat_torso"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("HeavyPlateGloves"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("hoodie.red"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("jacket.vagabond"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("gloves.leather"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("tshirt.long.blue"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("lumberjack_hoodie"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("Lumberjack_hazmat_torso"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("ninja_suit_viewmodel"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("NomadSuit_torso"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("RoadsignGloves"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("Wetsuit"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("jacket_snow"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("TacticalGloves"))) ||
						material->get_name()->Contains(StringIl::New(xorstr_("Surgeon_Outfit_main"))))
					{
						if (funcs::localplayer::handchamstype == 0)
						{
							renderer->set_material(WireFrmaeRainbow);
						}
						else if (funcs::localplayer::handchamstype == 1)
						{
							material->set_shader(GlowVisibleCheck, off);
							material->SetColor(Shader::PropertyToID(xorstr_("_ColorVisible")), Color({ funcs::visuals::handchams[0], funcs::visuals::handchams[1], funcs::visuals::handchams[2], 5 }));
							material->SetColor(Shader::PropertyToID(xorstr_("_ColorBehind")), Color({ funcs::visuals::chamsinvisible[0], funcs::visuals::chamsinvisible[1], funcs::visuals::chamsinvisible[2], 5 }));

						}
						else if (funcs::localplayer::handchamstype == 2)
						{
							material->set_shader(VisibleCheck, off);
							material->SetColor(Shader::PropertyToID(xorstr_("_ColorVisible")), Color({ funcs::visuals::handchams[0], funcs::visuals::handchams[1], funcs::visuals::handchams[2], 1 }));
							material->SetColor(Shader::PropertyToID(xorstr_("_ColorBehind")), Color({ funcs::visuals::chamsinvisible[0], funcs::visuals::chamsinvisible[1], funcs::visuals::chamsinvisible[2], 1 }));

						}
						else if (funcs::localplayer::handchamstype == 3)
						{
							renderer->set_material(matcapfx2);

						}
						else if (funcs::localplayer::handchamstype == 4)
						{
							renderer->set_material(matcapfx);
						}
					}
				}
				if (funcs::localplayer::weaponchams)
				{
					if ( material->get_name( )->Contains(StringIl::New(xorstr_("ak47_barrel"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("ak47_main"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("ak47_maggrip"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("ak47_stock"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("ak47_barrel_ice"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("ak47_main_ice"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("ak47_stock_ice"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("w_med_syringe"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("rock"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_torch"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("BaseballBat"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("beancan_grenade"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_bolt_rifle"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("boneclub"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("b_knife_dif"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("ButcherKnife"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("candy_cane_club"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("b_knife_dif"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Knife"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("CompoundBow"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Arrow"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("crossbow"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Stock_Barrel"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("pistol_shell"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("smg_basic"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("grip_mag"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Stock_Barrel"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("stock"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("barrel"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("DiverAssaultRifleParts1"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("DiverAssaultRifle_Body_Skin"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("DiverAssaultRifle_MagGrip_Skin"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("vfx_water_droplet"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("shotgun_shell"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_eoka_pistol"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("rock_colour"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_grenade"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_grenade"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("ft_part1"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("FlameJet"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("flame-pilotlight"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("flame_fireball"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("flame_fireball"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("flashbang_glass_outer"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("HMLMG"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("HMLMG Ammo"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Bow"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("L96"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_melee_set_wp_1_dif"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("body"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("barrel"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("receiver"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("M39 EMR"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_melee_set_wp_3_dif"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_melee_set_wp_5_dif"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("molotov_cocktail_Liquid"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("GrenadeLauncher"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("GLAmmo"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("AmmoNG"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("NailGun"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("KayakPaddle"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Pitchfork"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Glock a"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("GlockMagazine"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Sawnoff_shotgun"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("revolver"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("rocketlauncher"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("rpg"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_melee_set_wp_4"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_melee_set_wp_6"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("semi auto pistol"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("SAR_main"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("SAR_Stock"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("SAR_barrel"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("SAR_gripmag"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("GL Blizzard Blaster"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("SpearGun"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("stone_spear"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_thompson"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("WaterPipeShotgun"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Shotgunshell"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("wooden_spear"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("DiverHatchet"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("DiverHatchet Rope"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("DiverPickaxe"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("DiverTorch Off"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("DiverTorch Bulb"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Binoculars"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("flame-candle"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("birthday_cake_modular_09"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("sparks1"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("tracers-1"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("flecks_wood"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("bloodsplatter-1"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_ConcreteHatchet"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_ConcretePickaxe"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("cultist_deer_torch"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("flare_dif"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_flashlight"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("toolgun"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("GeigerCounter"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_hammer"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("fishing_rod_dif"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_axe_mat"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("JackHammer"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_pickaxe"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_lumberjack_axe"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_lumberjack_pick"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Detonator"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("rock"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_salvaged_axe"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("salvaged_hammer"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("salvaged_icepick"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("beancan_grenade"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("m18_SmokeGrenade"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("SprayPaintCan"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("stone_hatchet"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("Stone_pickaxe"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("surveyCharge"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("c4charge"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("v_torch"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("bucket_water"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("w_med_syringe"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("bandages"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("access_card_blue"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("access_card_red"))) ||
						material->get_name( )->Contains(StringIl::New(xorstr_("access_card_green"))) )
					{
						if (funcs::localplayer::weaponchamstype == 0)
						{
							renderer->set_material(WireFrmaeRainbow);
						}
						else if (funcs::localplayer::weaponchamstype == 1)
						{
							material->set_shader(GlowVisibleCheck, off);
							material->SetColor(Shader::PropertyToID(xorstr_("_ColorVisible")), Color({ funcs::visuals::weaponchams[0], funcs::visuals::weaponchams[1], funcs::visuals::weaponchams[2], 5 }));
							material->SetColor(Shader::PropertyToID(xorstr_("_ColorBehind")), Color({ funcs::visuals::chamsinvisible[0], funcs::visuals::chamsinvisible[1], funcs::visuals::chamsinvisible[2], 5 }));

						}
						else if (funcs::localplayer::weaponchamstype == 2)
						{
							material->set_shader(VisibleCheck, off);
							material->SetColor(Shader::PropertyToID(xorstr_("_ColorVisible")), Color({ funcs::visuals::weaponchams[0], funcs::visuals::weaponchams[1], funcs::visuals::weaponchams[2], 1 }));
							material->SetColor(Shader::PropertyToID(xorstr_("_ColorBehind")), Color({ funcs::visuals::chamsinvisible[0], funcs::visuals::chamsinvisible[1], funcs::visuals::chamsinvisible[2], 1 }));

						}
						else if (funcs::localplayer::weaponchamstype == 3)
						{
							renderer->set_material(matcapfx2);

						}
						else if (funcs::localplayer::weaponchamstype == 4)
						{
							renderer->set_material(matcapfx);
						}
					}
				}

			}
		}
	}

	void Chams(Color visibleColor, Color invisibleColor)
	{
		if (funcs::visuals::chams)
		{
			if (!this) return;
			if (this->health() <= 5.0f || this->lifestate() == BaseCombatEntity::LifeState::Dead) return;

			if (!this->playerModel()) return;
			if (!this->playerModel()->_multiMesh()) return;
			if (!this->playerModel()->_multiMesh()->Renderers()) return;

			List<Renderer_*>* renderers = this->playerModel()->_multiMesh()->Renderers();


			for (int i = 0; i < renderers->size; i++)
			{
				Renderer_* renderer = reinterpret_cast<Renderer_*>(renderers->get(i));
				if (!renderer) continue;
				if (!renderer->material()) continue;

				auto material = renderer->material();

				auto shader = material->shader();

				if (material)
				{
					static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::set_shader(Shader): Void");
					if (funcs::visuals::chamstype == 0)
					{
						renderer->set_material(WireFrmaeRainbow);
					}
					else if (funcs::visuals::chamstype == 1)
					{
						material->set_shader(GlowVisibleCheck, off);
						material->SetColor(Shader::PropertyToID(xorstr_("_ColorVisible")), Color({ funcs::visuals::chamsvisible[0], funcs::visuals::chamsvisible[1], funcs::visuals::chamsvisible[2], 5 }));
						material->SetColor(Shader::PropertyToID(xorstr_("_ColorBehind")), Color({ funcs::visuals::chamsinvisible[0], funcs::visuals::chamsinvisible[1], funcs::visuals::chamsinvisible[2], 5 }));
					}
					else if (funcs::visuals::chamstype == 2)
					{
						material->set_shader(VisibleCheck, off);
						material->SetColor(Shader::PropertyToID(xorstr_("_ColorVisible")), Color({ funcs::visuals::chamsvisible[0], funcs::visuals::chamsvisible[1], funcs::visuals::chamsvisible[2], 1 }));
						material->SetColor(Shader::PropertyToID(xorstr_("_ColorBehind")), Color({ funcs::visuals::chamsinvisible[0], funcs::visuals::chamsinvisible[1], funcs::visuals::chamsinvisible[2], 1 }));
					}
					else if (funcs::visuals::chamstype == 3)
					{
						renderer->set_material(matcapfx2);
					}
					else if (funcs::visuals::chamstype == 4)
					{
						renderer->set_material(matcapfx);
					}
				}
			}
		}
	}
};

class Vector3_ {
public:
	static inline Vector3(*MoveTowards_)(Vector3, Vector3, float) = nullptr;

	static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta) {
		return MoveTowards_(current, target, maxDistanceDelta);
	}
	//STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Vector3::Normalize", Normalize, Vector3(Vector3));
};
class Client {
public:
	static inline BaseEntity(*CreateOrUpdateEntity_)(ProtoBuf::Entity*, long) = nullptr;

	static BaseEntity CreateOrUpdateEntity(ProtoBuf::Entity* entity, long looong) {
		return CreateOrUpdateEntity_(entity, looong);
	}
};
class BuildingBlock {
public:
	enum class BuildingGrades {
		Twigs,
		Wood,
		Stone,
		Metal,
		TopTier
	};

};
enum class TextAnchor : int
{
	None = 0,
	Centered = 4
};
class GUIStyle {
public:
	void set_fontSize(int size)
	{
		if (!this) return;
		static auto off = METHOD("UnityEngine.IMGUIModule::UnityEngine::GUIStyle::set_fontSize(Int32): Void");
		return reinterpret_cast<void(__fastcall*)(GUIStyle*, int)>(off)(this, size);
	}
	void set_alignment(TextAnchor anchor)
	{
		if (!this) return;
		static auto off = METHOD("UnityEngine.IMGUIModule::UnityEngine::GUIStyle::set_fontSize(Int32): Void");
		return reinterpret_cast<void(__fastcall*)(GUIStyle*, TextAnchor)>(off)(this, anchor);
	}
	//STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::GUIStyle::set_fontSize(Int32): Void", set_fontSize, void(int));
	//STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::GUIStyle::set_alignment(TextAnchor): Void", set_alignment, void(TextAnchor*));
};
class GUISkin {
public:

};

GUIStyle* labelstyle;
class RendererTest {
public:
	STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::GUI::set_color(Color): Void", set_color, void(Color));
	STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::GUI::Label(Rect,String,GUIStyle): Void", Label, void(Rect, System::String*, GUIStyle*));
	STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::GUI::get_skin(): GUISkin", get_skin, GUISkin* ());
	//STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::GUI::DrawTexture(Rect,Texture): Void", DrawTexture, void(Rect, Texture));
	static inline void DrawTexture(RendererTest a0, Rect a1, Texture a2)
	{
		static auto off = METHOD("UnityEngine.IMGUIModule::UnityEngine::GUI::DrawTexture(Rect,Texture): Void");
		return reinterpret_cast<void(__fastcall*)(RendererTest, Rect, Texture)>(off)(a0, a1, a2);
	}
	static inline void init()
	{
		auto skin = RendererTest::get_skin();
		labelstyle = Read<GUIStyle*>((DWORD64)(skin + 0x38));

		labelstyle->set_alignment(TextAnchor::None);
		labelstyle->set_fontSize(15);
		RendererTest::set_color(Color(1, 1, 1, 1));
	}
	static inline void Text(Rect pos, System::String* text, float size = 0.0F)
	{
		labelstyle->set_fontSize(size);
		Label(pos, text, labelstyle);
	}
};
/*/class DDraw {
public:
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Line(Vector3,Vector3,Color,Single,Boolean,Boolean): Void", Line, void(Vector3, Vector3, Color, float, bool, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Sphere(Vector3,Single,Color,Single,Boolean): Void", Sphere, void(Vector3, float, Color, float, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Get(): DDraw", Get, DDraw*());
	static inline void(*OnGUI_)(DDraw*) = nullptr;
	void OnGUI() {
		return OnGUI_(this);
	}
};//*/

class MainMenuSystem : public Component
{
public:
	static inline void(*Update_)(MainMenuSystem*) = nullptr;
	void Update() {
		return Update_(this);
	}

};
class ExplosionsFPS
{
public:

	static inline void(*OnGUI_)(ExplosionsFPS*) = nullptr;
	void OnGUI() {
		return OnGUI_(this);
	}
};

//class Quaternion_ {
//public:
//	Quaternion LookRotation(Vector3 forward) {
//		if (!this) return Quaternion();
//		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Quaternion::LookRotation(Vector3): Quaternion");
//		return reinterpret_cast<Quaternion(__fastcall*)(Quaternion_*, Vector3)>(off)(this, forward);
//	}
//};


class Quaternion_ {
public:
	static Quaternion LookRotation(Vector3 forward) {
		//if (!this) return Quaternion();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Quaternion::LookRotation(Vector3): Quaternion");
		return reinterpret_cast<Quaternion(__fastcall*)(Vector3)>(off)(forward);
	}
};

class DDraw {
public:
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Line(Vector3,Vector3,Color,Single,Boolean,Boolean): Void", Line, void(Vector3, Vector3, Color, float, bool, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Sphere(Vector3,Single,Color,Single,Boolean,Boolean): Void", Sphere, void(Vector3, float, Color, float, bool, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Arrow(Vector3,Vector3,Single,Color,Single,Boolean,Boolean): Void", Arrow, void(Vector3, Vector3, float, Color, float));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Capsule(Vector3,Quaternion,Single,Single,Color,Single,Boolean,Boolean): Void", Capsule, void(Vector3, Quaternion, float, float, Color, float, bool, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Get(): DDraw", Get, DDraw* ());
	STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::GUI::get_color(): Color", get_color, Color());
	STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::GUI::set_color(Color): Void", set_color, void(Color));

	STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::GUI::DrawTexture(Rect,Texture): Void", DrawTexture, void(Rect, Texture*));

	static inline void(*OnGui_)(DDraw*) = nullptr;
	void OnGui() {
		return OnGui_(this);
	}
};

class AssetBundle {
public:
	Array<System::String*>* GetAllAssetNames() {
		if (!this) return {};
		static auto off = METHOD("UnityEngine.AssetBundleModule::UnityEngine::AssetBundle::GetAllAssetNames(): String[]");
		return reinterpret_cast<Array<System::String*>*(*)(AssetBundle*)>(off)(this);
	}
	template<typename T = Object>
	T* LoadAsset(char* name, Type* type) {
		if (!this) return {};
		static auto off = METHOD("UnityEngine.AssetBundleModule::UnityEngine::AssetBundle::LoadAsset(String,Type): Object");
		return reinterpret_cast<T * (*)(AssetBundle*, System::String*, Type*)>(off)(this, System::String::New(name), type);
	}
	static AssetBundle* LoadFromFile(const char* path) {
		static auto off = METHOD("UnityEngine.AssetBundleModule::UnityEngine::AssetBundle::LoadFromFile(String): AssetBundle");
		return reinterpret_cast<AssetBundle * (*)(System::String*)>(off)(System::String::New(path));
	}
};
std::array<int, 20> valid_bones = {
		1, 2, 3, 5, 6, 14, 15, 17, 18, 21, 23, 24, 25, 26, 27, 48, 55, 56, 57, 76
};
class Model : public Component {
public:
	//STATIC_FUNCTION()
	FIELD("Assembly-CSharp::Model::boneTransforms", boneTransforms, Array<Transform*>*);
	FIELD("Assembly-CSharp::Model::boneNames", boneNames, Array<System::String*>*);

	std::pair<Transform*, bool> find_bone(Vector3 from) {
		try {

			std::pair<Transform*, bool> ret = std::pair<Transform*, bool>(nullptr, false);
			if (!this || !std::uint64_t(this))	return ret;// < std::uint64_t(GetModuleHandleA("GameAssembly.dll"))) return ret;

			std::vector<std::pair<Transform*, float>> distances = std::vector<std::pair<Transform*, float>>();

			auto arr = this->boneTransforms();
			if (!arr)
				return ret;

			for (auto j : valid_bones) {
				if (!j || !arr)
					continue;
				auto bone = arr->get(j);
				if (!bone)
					continue;

				float dist = bone->position().distance(from);

				distances.push_back({ bone, dist });
			}


			// find smallest from float (second)
			std::pair<Transform*, float> temp = { nullptr, 99999.f };
			for (int i = 0; i < distances.size(); i++) {
				if (distances[i].second < temp.second) {
					temp.first = distances[i].first;
					temp.second = distances[i].second;
				}
			}

			ret.first = temp.first;
			ret.second = true;

			return ret;
		}
		catch (...) { return std::pair<Transform*, bool>(nullptr, false); };
		//__except (SafeExecution::fail(GetExceptionCode(), GetExceptionInformation())) { return std::pair<Transform*, bool>(nullptr, false);; };
	}
};
class Connection {
public:
	FIELD("Facepunch.Network::Network::Connection::username", username, System::String*);
	FIELD("Facepunch.Network::Network::Connection::userid", userid, long);
	FIELD("Facepunch.Network::Network::Connection::ownerid", ownerid, long);
	FIELD("Facepunch.Network::Network::Connection::authLevel", authLevel, unsigned int);
	static inline void(*Update_)(Connection*) = nullptr;
	void OnDissconected() {
		return Update_(this);
	}
};
namespace Network {
	enum class MessageType {
		auth = 2,
		requestuserinformation = 17,
		giveuserinformation = 18
	};

	class BaseNetwork {

	};
	class NetWrite : public BaseNetwork {
	public:
		static bool Start() {
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::Start(): Boolean");
			return reinterpret_cast<bool (*)()>(off)();
		}
		/*Array<String*>* GetAllAssetNames( ) {
		if (!this) return {};
		static auto off = METHOD("UnityEngine.AssetBundleModule::UnityEngine::AssetBundle::GetAllAssetNames(): String[]");
		return reinterpret_cast<Array<String*>*(*)(AssetBundle*)>(off)(this);
	}

		static auto off = METHOD("Assembly-CSharp::StringPool::Get(UInt32): String");
	*/
		void PacketID(char val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::PacketID(Message.Type): Void");
			return reinterpret_cast<void(*)(NetWrite*, char)>(off)(this, val);
		}

		void UInt8(char val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::UInt8(UInt8): Void");
			return reinterpret_cast<void(*)(NetWrite*, char)>(off)(this, val);
		}

		void UInt16(uint16_t val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::UInt16(UInt16): Void");
			return reinterpret_cast<void(*)(NetWrite*, uint16_t)>(off)(this, val);
		}

		void UInt32(uint32_t val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::UInt32(UInt32): Void");
			return reinterpret_cast<void(*)(NetWrite*, uint32_t)>(off)(this, val);
		}

		void UInt64A(uint64_t val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::UInt64(UInt64): Void");
			return reinterpret_cast<void(*)(NetWrite*, uint64_t)>(off)(this, val);
		}

		void _String(System::String* val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::String(String): Void");
			return reinterpret_cast<void (*)(NetWrite*, System::String*)>(off)(this, val);
		}

		static inline void(*UInt64_)(NetWrite*, uint64_t) = nullptr;
		void UInt64(uint64_t val) {
			return UInt64_(this, val);
		}
	};
	class Message {
	public:
		FIELD("Facepunch.Network::Network::Message::write", write, NetWrite*);
	};
	class AuthTicket {

	};
	class Client {
	public:
		static inline void(*OnNetworkMessage_)(Client*, Message*) = nullptr;
		void OnNetworkMessage(Message* m) {
			return OnNetworkMessage_(this, m);
		}

		AuthTicket* GetAuthTicket() {
			if (!this) return nullptr;
			static auto off = METHOD("Facepunch.Network::Network::Client::GetAuthTicket(): Auth.Ticket");
			return reinterpret_cast<AuthTicket * (__fastcall*)(Client*)>(off)(this);
		}
		bool IsConnected() {
			if (!this) return false;
			static auto off = METHOD("Facepunch.Network::Network::Client::IsConnected(): Boolean");
			return reinterpret_cast<bool(__fastcall*)(Client*)>(off)(this);
		}
		System::String* ConnectedAddress() {
			return *reinterpret_cast<System::String**>(this + 0x40);
		}

		static inline void(*OnRequestUserInformation_)(Client*, Message*) = nullptr;
		void OnRequestUserInformation(Message* packet) {
			return OnRequestUserInformation_(this, packet);
		}
	};
	class Net {
	public:
		static Client* cl() {
			static auto clazz = CLASS("Facepunch.Network::Network::Net");
			return *reinterpret_cast<Client**>(std::uint64_t(clazz->static_fields));
		}
	};
}
class AimConeUtil {
public:
	static inline Vector3(*GetModifiedAimConeDirection_)(float, Vector3, bool) = nullptr;
	static Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = true) {
		return GetModifiedAimConeDirection_(aimCone, inputVec, anywhereInside);
	}
};
Matrix viewMatrix = {};

class Camera {
public:
	static char* memstr(char* haystack, const char* needle, int size) {
		char* p;
		char needlesize = strlen(needle);

		for (p = haystack; p <= (haystack - needlesize + size); p++) {
			if (memcmp(p, needle, needlesize) == 0)
				return p; /* found */
		}

		return NULL;
	}
	static uintptr_t get_main_camera() {

		return reinterpret_cast<uintptr_t(*)()>(il2cpp_resolve_icall(xorstr_("UnityEngine.Camera::get_main()")))();
	}
	static Camera* get_main_camera2( ) {

		return reinterpret_cast< Camera*( * )( ) >( il2cpp_resolve_icall( xorstr_( "UnityEngine.Camera::get_main()" ) ) )( );
	}
	Vector3 w2s_get( Vector3 position ) {
		static auto addr = METHOD( "UnityEngine.CoreModule::UnityEngine::Camera::WorldToScreenPoint(Vector3): Vector3" );
		auto vec = reinterpret_cast< Vector3( __fastcall* )( Camera*, Vector3 ) >( addr )( this, position );
		return vec;
	}
	static uint64_t GetCamera() {
		__try {
			const auto base = (uint64_t)GetModuleHandleA(xorstr_("UnityPlayer.dll"));

			if (!base)
				return 0;

			const auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
			const auto nt_header = reinterpret_cast<IMAGE_NT_HEADERS64*>(base + dos_header->e_lfanew);

			uint64_t data_base;
			uint64_t data_size;

			for (int i = 0;;) {
				const auto section = reinterpret_cast<IMAGE_SECTION_HEADER*>(
					base + dos_header->e_lfanew + // nt_header base 
					sizeof(IMAGE_NT_HEADERS64) +  // start of section headers
					(i * sizeof(IMAGE_SECTION_HEADER))); // section header at our index

				if (strcmp((char*)section->Name, xorstr_(".data")) == 0) {
					data_base = section->VirtualAddress + base;
					data_size = section->SizeOfRawData;
					break;
				}

				i++;

				if (i >= nt_header->FileHeader.NumberOfSections) {
					return 0;
				}
			}

			uint64_t camera_table = 0;

			const auto camera_string = memstr((char*)data_base, xorstr_("AllCameras"), data_size);
			for (auto walker = (uint64_t*)camera_string; walker > (uint64_t*)0; walker -= 1) {
				if (*walker > 0x100000 && *walker < 0xF00000000000000) {
					// [[[[unityplayer.dll + ctable offset]]] + 0x30] = Camera
					camera_table = *walker;
					break;
				}
			}

			if (camera_table)
				return camera_table;

			return 0;
		}
		__except (SafeExecution::fail(GetExceptionCode(), GetExceptionInformation())) { return 0; };
	}
	static float Dot(const Vector3& Vec1, const Vector3& Vec2) {
		return Vec1[0] * Vec2[0] + Vec1[1] * Vec2[1] + Vec1[2] * Vec2[2];
	}
	Rect GetPixelRect( )
	{
		static auto addr = METHOD( "UnityEngine.CoreModule::UnityEngine::Camera::get_pixelRect(): Rect" );
		return reinterpret_cast< Rect( __fastcall* )( Camera* ) >( addr )( this );
		
	}
	static bool world_to_screen( const Vector3& EntityPos, Vector2& ScreenPos )
	{
		auto matrix = find_matrix( );
		if ( !matrix ) return false;

		Vector3 TransVec = Vector3( matrix->_14, matrix->_24, matrix->_34 );
		Vector3 RightVec = Vector3( matrix->_11, matrix->_21, matrix->_31 );
		Vector3 UpVec = Vector3( matrix->_12, matrix->_22, matrix->_32 );
		float w = Dot( TransVec, EntityPos ) + matrix->_44;
		if ( w < 0.098f ) return false;

		float y = Dot( UpVec, EntityPos ) + matrix->_42;
		float x = Dot( RightVec, EntityPos ) + matrix->_41;
		ScreenPos = Vector2( ( screen_center.x + x / w * screen_center.x ), ( screen_center.y - y / w * screen_center.y ) );
		return true;
	}

	//static bool Camera::world_to_screen(Vector3 world, Vector2& screen) {
	//	const auto matrix = viewMatrix.transpose();

	//	const Vector3 translation = { matrix[3][0], matrix[3][1], matrix[3][2] };
	//	const Vector3 up = { matrix[1][0], matrix[1][1], matrix[1][2] };
	//	const Vector3 right = { matrix[0][0], matrix[0][1], matrix[0][2] };

	//	const auto w = translation.dot_product(world) + matrix[3][3];

	//	if (w < 0.1f)
	//		return false;

	//	const auto x = right.dot_product(world) + matrix[0][3];
	//	const auto y = up.dot_product(world) + matrix[1][3];

	//	screen =
	//	{
	//		screen_center.x * (1.f + x / w),
	//		screen_center.y * (1.f - y / w)
	//	};

	//	return true;
	//}
	//static Vector3 WorldToScreen(Vector3 position)
	//{
	//	Vector3 out;
	//	const auto temp = viewMatrix.transpose();

	//	auto translation_vector = Vector3{ temp[3][0], temp[3][1], temp[3][2] };
	//	auto up = Vector3{ temp[1][0], temp[1][1], temp[1][2] };
	//	auto right = Vector3{ temp[0][0], temp[0][1], temp[0][2] };

	//	float w = translation_vector.dot_product(position) + temp[3][3];

	//	if (w < 0.098f) {
	//		return Vector3(0, 0, 0);
	//	}

	//	float x = up.dot_product(position) + temp._24;
	//	float y = right.dot_product(position) + temp._14;

	//	out.x = (static_cast<float>(screen_center.x)) * (1 + y / w);
	//	out.y = (static_cast<float>(screen_center.y)) * (1 - x / w);
	//	out.z = w;

	//	return out;
	//}
	static Matrix4x4* find_matrix() {
		auto entity = *reinterpret_cast<DWORD64*>(get_main_camera() + 0x10);
		Matrix4x4* pViewMatrix = (Matrix4x4*)(entity + 0x30C);
		return pViewMatrix;
	}
	//static Matrix getViewMatrix() {
	//	static auto camera_list = GetCamera();
	//	if (!camera_list) return Matrix();

	//	auto camera_table = *reinterpret_cast<uint64_t*>(camera_list);
	//	auto cam = *reinterpret_cast<uint64_t*>(camera_table);

	//	return *reinterpret_cast<Matrix*>(cam + 0x2E4);
	//}
};

Vector3 WorldToScreen( Vector3 position )
{
	Vector2 to_return;
	if ( Camera::world_to_screen( position, to_return ) )
	{
		return Vector3( to_return.x, to_return.y, 0 );
	}
	return Vector3( 0, 0, 0 );
}

float timee = 120.f;

struct Explosion {
public:
	std::string name;
	float timeSince;
	Vector3 position;
};
class LogSystem {
public:
	static inline int max_entries = 10;

	static void draw_text(Vector2, std::string, ImColor col = ImColor(255, 255, 255), int timer = 0);

	struct LogEntry {
	public:
		std::string message;
		float startedAt;
		float duration;

		LogEntry(std::string message, float duration) {
			this->message = message;
			this->duration = duration;
			this->startedAt = get_time_since_startup();
		}
	};

	static inline std::vector<LogEntry> logs = std::vector<LogEntry>();
	static inline std::vector<Explosion> loggedExplosions = std::vector<Explosion>();

	static void Log(std::string message, float duration) {
		if (logs.size() >= max_entries)
			logs.erase(logs.begin());

		logs.push_back(LogEntry(message, duration));
	}
	static void LogExplosion(std::string type, Vector3 pos) {
		bool explosionCollision = false;
		std::vector<Explosion>::iterator it;
		for (it = loggedExplosions.begin(); it != loggedExplosions.end(); it++) {
			Vector2 explPos;
			if (it->position.distance(pos) <= 25.0f) {
				explosionCollision = true;
				break;
			}
		}
		if (!explosionCollision) {
			Explosion explosion = Explosion();
			explosion.name = StringFormat::format(xorstr_("%s Raid"), type.c_str());
			explosion.position = pos;
			explosion.timeSince = get_time_since_startup();
			loggedExplosions.push_back(explosion);
		}
	}

	static void Render() {
		float yPos = 5.f;
		for (int i = 0; i < logs.size(); i++) {
			LogEntry entry = logs[i];
			if ((get_time_since_startup() - entry.startedAt) >= entry.duration) {
				logs.erase(logs.begin() + i);
				continue;
			}
			draw_text(Vector2(5, yPos), entry.message, ImColor(255, 255, 255));
			yPos += 25.0f;
		}
	}
	static void RenderExplosions(Vector3 localcamera) {
		for (int i = 0; i < LogSystem::loggedExplosions.size(); i++) {
			if ((get_time_since_startup() - LogSystem::loggedExplosions[i].timeSince) >= timee) {
				LogSystem::loggedExplosions.erase(LogSystem::loggedExplosions.begin() + i);
				continue;
			}
			Explosion explosion = LogSystem::loggedExplosions.at(i);

			Vector2 explPos;
			if (Camera::world_to_screen(explosion.position, explPos)) {


				std::string string;
				char buf[256] = { 0 }; sprintf_s(buf, xorstr_("%s[%dm][%d]"), explosion.name.c_str(), (int)localcamera.distance(explosion.position), (int)(timee - (get_time_since_startup() - LogSystem::loggedExplosions[i].timeSince)));
				string += buf;
				g_Render->DrawString({ explPos.x,explPos.y }, ImColor(255, 0, 0), render2::outline | render2::centered_x, DefaultFonts, 12.f, string.c_str());
			}
		}
	}
};
void LogSystem::draw_text(Vector2 pos, std::string str, ImColor col, int timer) {
	g_Render->DrawString({ pos.x,pos.y }, ImColor(255, 255, 255), render2::outline, DefaultFonts, 12.f, str.c_str());
}
std::map<uint64_t, BaseNetworkable*> projectile_targets = std::map<uint64_t, BaseNetworkable*>();
class TerrainMeta {
public:

	static inline void(*ctor_)(TerrainMeta*) = nullptr;
	void ctor() {
		return ctor_(this);
	}

	Vector3 get_Position()
	{
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::TerrainMeta::get_Position(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(TerrainMeta*)>(off)(this);
	}
};
class TerrainHeightMap {
public:
	static inline void(*ctor_)(TerrainHeightMap*) = nullptr;
	void ctor() {
		return ctor_(this);
	}
	float GetHeight(Vector3 imo)
	{
		if (!this) return 0.0f;
		static auto off = METHOD("Assembly-CSharp::TerrainHeightMap::GetHeight(Vector3): Single");
		return reinterpret_cast<float(__fastcall*)(TerrainHeightMap*, Vector3)>(off)(this, imo);
	}
};
class TerrainCollision {
public:

	static inline void(*ctor_)(TerrainCollision*) = nullptr;
	void ctor() {
		return ctor_(this);
	}

	bool GetIgnore(Vector3 imo, float flot)
	{
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::TerrainCollision::GetIgnore(Vector3,Single): Boolean");
		return reinterpret_cast<bool(__fastcall*)(TerrainCollision*, Vector3, float)>(off)(this, imo, flot);
	}
};
class Terrain {
public:

	static inline void(*ctor_)(Terrain*) = nullptr;
	void ctor() {
		return ctor_(this);
	}
	float SampleHeight(Vector3 imo)
	{
		if (!this) return 0.0f;
		static auto off = METHOD("UnityEngine.TerrainModule::UnityEngine::Terrain::SampleHeight(Vector3): Single");
		return reinterpret_cast<float(__fastcall*)(Terrain*, Vector3)>(off)(this, imo);
	}
};
TerrainHeightMap* TerrainMap;
TerrainMeta* Terrainmeta;
TerrainCollision* Terraincollision;
Terrain* terrain;
class AntiHack {
private:
	//STATIC_FUNCTION("UnityEngine.TerrainModule::UnityEngine::Terrain::SampleHeight(Vector3): Single", SampleHeight, float(Vector3));

	static bool TestInsideTerrain(Vector3 pos)
	{
		if (!TerrainMap) return false;
		if (!Terrainmeta) return false;
		if (!Terraincollision) return false;
		if (!terrain) return false;

		static float terrain_padding = 0.3f;
		float height = TerrainMap->GetHeight(pos);

		if (pos.y > (height - terrain_padding))
		{
			return false;
		}
		float num = Terrainmeta->get_Position().y + terrain->SampleHeight(pos);
		return pos.y <= num - terrain_padding && !Terraincollision->GetIgnore(pos, 0.01f);
	}
public:
	static bool IsInsideTerrain(BasePlayer* player)
	{
		bool result = TestInsideTerrain(player->transform()->position());
		return result;
	}
};

class ServerBrowserList {
public:
	static inline void(*Update_)(ServerBrowserList*) = nullptr;
	void Update() {
		return Update_(this);
	}
	FIELD("Assembly-CSharp::ServerBrowserList::players", players, int);
};
class Zipline : BaseMountable {
public:
	static inline void(*UpdatePlayerModel_)(Zipline*) = nullptr;
	void UpdatePlayerModel() {
		return UpdatePlayerModel_(this);
	}
};

void initialize_cheat() {
	init_classes();
	init_fields();
	init_methods();
	DDraw::Get();
	menu::cheat_init = true;
}
#pragma optimize( "", on )