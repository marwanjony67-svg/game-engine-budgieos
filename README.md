# BudgieOS Engine 1.0 — Ultimate Edition Starter

A native C++20 game-engine/editor starter for Windows, branded with BudgieOS Blue. This is an original engine project, not Unreal Engine and not a finished commercial engine.

## Current build

- Native Windows desktop editor shell (Win32 API)
- C++20 engine core and scene/entity model
- Basic editor layout: menu, viewport grid, hierarchy, inspector and content panel
- Windows EXE build through GitHub Actions
- CMake project structure for future renderer and tools

## Build on Windows

Requirements: Visual Studio 2022 with **Desktop development with C++**, CMake 3.20+.

```powershell
cmake -S . -B build -A x64
cmake --build build --config Release
```

Executable: `build\Release\BudgieOS-Engine.exe`

## Build on Linux (core validation)

```bash
cmake -S . -B build
cmake --build build
```

The native Win32 editor shell is Windows-only. Linux currently validates the portable engine core.

## Download the EXE

1. Open the repository's **Actions** tab.
2. Run or open **Build BudgieOS Engine**.
3. Wait for the Windows build job to pass.
4. Download the `BudgieOS-Engine-Windows-x64` artifact.

The EXE is not available until the workflow completes successfully.

## About the “100 GB” target

100 GB is treated as a future project/content-library capacity goal (large games, assets, sample projects), **not** the size of the engine executable. The editor itself should remain much smaller. This starter does not download or include 100 GB of assets.

## Roadmap

1. DirectX 12 renderer and Vulkan backend
2. PBR materials, model/texture import and asset database
3. Physics, animation and audio systems
4. C# editor scripting/tools
5. Scene editor, material editor, animation editor and build manager
6. Project templates and packaging pipeline

## Current limitations

This is an early editor/engine foundation. It does not yet include a production renderer, physics engine, asset importer, complete game runtime, or finished installer. The viewport is currently a native editor preview with a grid.

BudgieOS is an independent project.
