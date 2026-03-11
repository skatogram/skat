#include "minhook/include/MinHook.h"

namespace hookengine {
	PBYTE FindPattern(const char* Pattern, const char* Module = nullptr)
	{
		//find pattern utils
#define InRange(x, a, b) (x >= a && x <= b) 
#define GetBits(x) (InRange(x, '0', '9') ? (x - '0') : ((x - 'A') + 0xA))
#define GetByte(x) ((BYTE)(GetBits(x[0]) << 4 | GetBits(x[1])))

//get module range
		PBYTE ModuleStart = ( PBYTE ) GetModuleHandleA(Module); if ( !ModuleStart ) return nullptr;
		PIMAGE_NT_HEADERS NtHeader = ( ( PIMAGE_NT_HEADERS ) ( ModuleStart + ( ( PIMAGE_DOS_HEADER ) ModuleStart )->e_lfanew ) );
		PBYTE ModuleEnd = ( PBYTE ) ( ModuleStart + NtHeader->OptionalHeader.SizeOfImage - 0x1000 ); ModuleStart += 0x1000;

		//scan pattern main
		PBYTE FirstMatch = nullptr;
		const char* CurPatt = Pattern;
		for ( ; ModuleStart < ModuleEnd; ++ModuleStart )
		{
			bool SkipByte = ( *CurPatt == '\?' );
			if ( SkipByte || *ModuleStart == GetByte(CurPatt) ) {
				if ( !FirstMatch ) FirstMatch = ModuleStart;
				SkipByte ? CurPatt += 2 : CurPatt += 3;
				if ( CurPatt[-1] == 0 ) return FirstMatch;
			}
			else if ( FirstMatch ) {
				ModuleStart = FirstMatch;
				FirstMatch = nullptr;
				CurPatt = Pattern;
			}
		}

		return nullptr;
	}
	
	
	void hook(void* Function, void** Original, void* Detour) {
		if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED) {
			return;
		}
		MH_CreateHook(Function, Detour, Original);
		MH_EnableHook(Function);
	}

}