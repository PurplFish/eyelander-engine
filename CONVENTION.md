# Conventions

## Naming
- Interfaces: `I` prefix + PascalCase → `IRenderer`
- Classes: PascalCase → `GameEngine`
- Methods: camelCase → `drawSprite()`
- Member variables: `m_` prefix → `m_window`
- Constants: `k_` prefix → `k_maxSprites`
- Files: match class name → `IRenderer.h`, `SDLRenderer.cpp`

## File Structure
- All interfaces live in `src/platform/`
- Platform backends in `src/platform/sdl/`, `src/platform/wii/`
- Lua bindings in `src/lua/`

## Rules
- Engine code never includes SDL headers directly — always go through the HAL
- src/platform/ headers are public contracts.
- src/platform/platform_*** has no headers unless the implementation needs to talk to itself.
- No raw `new`/`delete`