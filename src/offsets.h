#pragma once
#include <windows.h>
#include <cstdint>

namespace Offsets {
    // RVAs from GameAssembly.dll
    constexpr uintptr_t playerList = 0x2D6AB0;
    constexpr uintptr_t otherPlayers = 0x2D6A10;
    constexpr uintptr_t _CreateShot = 0x630520;

    // Field Offsets
    constexpr uintptr_t walkSpeed = 0xBC;
    constexpr uintptr_t mOtherPlayerListCopy = 0x78;
    constexpr uintptr_t mPlayerListCopy = 0x80;
    constexpr uintptr_t _camPos = 0x2C0;
}
