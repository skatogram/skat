#pragma once
#include <windows.h>
#include <cstdint>

namespace Offsets {
    // RVAs from GameAssembly.dll
    constexpr uintptr_t playerList = 0x2D6AB0;
    constexpr uintptr_t otherPlayers = 0x2D6A10;
    constexpr uintptr_t _CreateShot = 0x630520;
    constexpr uintptr_t get_FPSCamera = 0x639A90;

    // Field Offsets (PlayerScript)
    constexpr uintptr_t walkSpeed = 0xBC;
    constexpr uintptr_t rotationY = 0xF8;
    constexpr uintptr_t rotationX = 0xFC;
    constexpr uintptr_t team = 0x290;
    constexpr uintptr_t _fpsCam = 0x110;
    constexpr uintptr_t _health = 0x278;
    constexpr uintptr_t _armor = 0x284;

    // Field Offsets (FPSCamera)
    constexpr uintptr_t cameraComp = 0x28; // Camera component
}
