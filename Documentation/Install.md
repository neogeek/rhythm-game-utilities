## Install

### Unity

1. Add package via git URL
   ```
   https://github.com/rhythm-game-utilities/rhythm-game-utilities.git?path=/UnityPackage
   ```
1. Import the sample project (optional)
   - Check the materials to make sure they work in the version of Unity and render pipeline you selected.

### Unreal

1. Clone this repo locally (using either a tagged release or the main development branch).
1. Add the include path to your `<project>.Build.cs` file.
   ```csharp
   PublicIncludePaths.AddRange(new string[] { "D:/git/github/rhythm-game-utilities/include" });
   ```

### Godot

#### GDScript

Download and install the latest release from <https://github.com/rhythm-game-utilities/godot-plugin>.

#### C#

Install the nuget package [com.neogeek.rhythm-game-utilities](https://www.nuget.org/packages/com.neogeek.rhythm-game-utilities/) via the CLI or from within your IDE.

```bash
dotnet add package com.neogeek.rhythm-game-utilities --version 1.0.0-alpha.5
```

### SDL

1. Clone this repo locally (using either a tagged release or the main development branch).
1. Add the include path to your project.
   - VS Code: `.vscode/c_cpp_properties.json`
     ```json
     "includePath": [
         "${workspaceFolder}/**",
         "${HOME}/git/github/rhythm-game-utilities/include/**"
     ]
     ```
1. Add the include path to your build command.
   - `g++`
     ```bash
     g++ -std=c++17 -o build/output src/*.cpp -Isrc \
         -I"${HOME}/git/github/rhythm-game-utilities/include/" \
         -I/opt/homebrew/Cellar/sdl2/2.30.8/include/SDL2 -L/opt/homebrew/Cellar/sdl2/2.30.8/lib \
         -lSDL2
     ```
1. Add the include path to your CMAKE `CMakeLists.txt` file.
   ```cmake
   include_directories($ENV{HOME}/git/github/rhythm-game-utilities/include/)
   ```

### MonoGame

Install the nuget package [com.neogeek.rhythm-game-utilities](https://www.nuget.org/packages/com.neogeek.rhythm-game-utilities/) via the CLI or from within your IDE.

```bash
dotnet add package com.neogeek.rhythm-game-utilities --version 1.0.0-alpha.5
```
