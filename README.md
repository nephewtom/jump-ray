# Jump Ray
[Jump King](https://store.steampowered.com/app/1061090/Jump_King/) clone, written in C/C++ and Raylib, for learning purposes.

![gameplay](showcase.gif)

## Compiling
```
git clone --recurse-submodules https://github.com/nephewtom/jump-ray.git
cd jump-ray/raylib
make PLATFORM=PLATFORM_DESKTOP
cd ..
```
### Windows
```
build.bat
```
### Mac
```
build.sh
```

## Features
- Tilemap VS Box collision resolution (position based, clips velocity)
- Player movement
  - jumping, charging jumps, walking
- Simple tile-based levels
  - Levels are defined using strings
- Rendering a basic tileset
