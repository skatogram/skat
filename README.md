# Kuboom Cheat DLL

Simple Internal Cheat for Kuboom (Il2Cpp).

## Features
- **Aimbot Framework**: Basic calculation logic and player list iteration.
- **Offsets**: Uses provided RVAs and field offsets.
- **GitHub Workflow**: Automatically builds the DLL to `.dll` on every push.

## How to use
1. Push this project to your GitHub repository.
2. Go to the **Actions** tab in your repository.
3. Once the build is finished, download the artifact (KuboomCheat-DLL).
4. Inject `KuboomCheat.dll` into the game using any injector (e.g., Extreme Injector, Process Hacker).
5. **Insert** to unload the cheat.
6. **Right Click** (Hold) to activate aim logic (template).

## Building Locally
1. Install [CMake](https://cmake.org/).
2. Open terminal in the project folder.
3. Run:
   ```bash
   cmake -B build
   cmake --build build --config Release
   ```
