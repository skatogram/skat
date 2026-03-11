
namespace mem {
	uintptr_t find_pattern(uintptr_t base, const PBYTE Pattern, const char* Mask) {
		PBYTE Start = (PBYTE)base;
		PIMAGE_NT_HEADERS NTHead = (PIMAGE_NT_HEADERS)(Start + ((PIMAGE_DOS_HEADER)Start)->e_lfanew);
		DWORD Len = NTHead->OptionalHeader.SizeOfImage;

		for (PBYTE region_it = Start; region_it < (Start + Len); ++region_it) {
			if (*region_it == *Pattern) {
				bool found = true;
				const unsigned char* pattern_it = Pattern, * mask_it = (const PBYTE)Mask, * memory_it = region_it;
				for (; *mask_it && (memory_it < (Start + Len)); ++mask_it, ++pattern_it, ++memory_it) {
					if (*mask_it != 'x') continue;
					if (*memory_it != *pattern_it) {
						found = false;
						break;
					}
				}

				if (found)
					return (uintptr_t)region_it;
			}
		}

		return 0;
	}
	PBYTE FindPattern(const char* Pattern, const char* Module = nullptr)
	{
		//find pattern utils
#define InRange(x, a, b) (x >= a && x <= b) 
#define GetBits(x) (InRange(x, '0', '9') ? (x - '0') : ((x - 'A') + 0xA))
#define GetByte(x) ((BYTE)(GetBits(x[0]) << 4 | GetBits(x[1])))

//get module range
		PBYTE ModuleStart = (PBYTE)GetModuleHandleA(Module); if (!ModuleStart) return nullptr;
		PIMAGE_NT_HEADERS NtHeader = ((PIMAGE_NT_HEADERS)(ModuleStart + ((PIMAGE_DOS_HEADER)ModuleStart)->e_lfanew));
		PBYTE ModuleEnd = (PBYTE)(ModuleStart + NtHeader->OptionalHeader.SizeOfImage - 0x1000); ModuleStart += 0x1000;

		//scan pattern main
		PBYTE FirstMatch = nullptr;
		const char* CurPatt = Pattern;
		for (; ModuleStart < ModuleEnd; ++ModuleStart)
		{
			bool SkipByte = (CurPatt[0] == '?');
			if (SkipByte || *ModuleStart == GetByte(CurPatt)) {
				if (!FirstMatch)
					FirstMatch = ModuleStart;

				CurPatt += 3;

				if (CurPatt[-1] == 0)
					return FirstMatch;
			}

			else if (FirstMatch) {
				ModuleStart = FirstMatch;
				FirstMatch = nullptr;
				CurPatt = Pattern;
			}
		}

		return nullptr;
	}
	template<typename T = uintptr_t, typename A>
	T& read(A address) {
		auto addresss = (DWORD64)address;
		if (addresss > 0x40000 && (addresss + sizeof(T)) < 0x7FFFFFFF0000)
			return *(T*)addresss;

		auto n = nullptr;
		return reinterpret_cast<T&>(n);
	}
	template <typename T>
	void write(uintptr_t address, T data) {
		if (address > 0x40000 && (address + sizeof(T)) < 0x7FFFFFFF0000)
			*(T*)(address) = data;
	}
}