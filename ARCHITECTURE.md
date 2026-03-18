engine/
├── ARCHITECTURE.md
├── CONVENTIONS.md
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── core/
│   ├── platform/
│   ├── systems/
│   ├── fs/
│   └── lua/
├── boot/
├── libs/
└── games/


Init flow:
main()
 │
 ├── 1. Platform::init()          // detect OS/hardware, set up allocator
 │
 ├── 2. Log::init()              
 │
 ├── 3. VFS::init()               // Virtual file system
 │
 ├── 4. IWindow::create()         // create window (SDL_Init, WiiScreen_Init, etc.)
 │
 ├── 5. IRenderer::create()       // needs window to exist first
 │
 ├── 6. IAudio::create()          // independent but log if it fails, don't crash
 │
 ├── 7. IInput::create()          // same — soft fail
 │
 ├── 8. INetwork::create()        // soft fail, just flag unavailable
 │
 ├── 9. LuaEngine::init()         // VM up, bind all C systems to Lua
 │        ├── bind(renderer)
 │        ├── bind(audio)
 │        ├── bind(input)
 │        └── bind(network)
 │
 ├── 10. LuaEngine::run("boot/main.lua")   // hands control to Lua
 │         ├── checks.lua                  // probe each system
 │         ├── animation.lua               // intro (degrades if systems failed)
 │         └── launcher.lua               // scan /games, user picks one
 │
 └── 11. Game loop until quit → shutdown in reverse order