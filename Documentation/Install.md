## Install

### Unity

1. Add package via git URL
   ```
   https://github.com/neogeek/rhythm-game-utilities.git?path=/UnityPackage
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

#### C#

1. Clone this repo locally (using either a tagged release or the main development branch).
1. Update your `.csproj` file to include a reference to the project:

   ```xml
   <ItemGroup>
       <ProjectReference
       Include="../../github/rhythm-game-utilities/RhythmGameUtilities/RhythmGameUtilities.csproj" />
   </ItemGroup>
   ```

1. Add config to your `.csproj` file to copy the library files before a build:

   ```xml
   <ItemGroup Condition="$([MSBuild]::IsOSPlatform('Windows'))">
       <None
           Include="../../github/rhythm-game-utilities/RhythmGameUtilities/Libs/Windows/libRhythmGameUtilities.dll">
           <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
       </None>
   </ItemGroup>

   <ItemGroup Condition="$([MSBuild]::IsOSPlatform('OSX'))">
       <None
           Include="../../github/rhythm-game-utilities/RhythmGameUtilities/Libs/macOS/libRhythmGameUtilities.dylib">
           <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
       </None>
   </ItemGroup>

   <ItemGroup Condition="$([MSBuild]::IsOSPlatform('Linux'))">
       <None
           Include="../../github/rhythm-game-utilities/RhythmGameUtilities/Libs/Linux/libRhythmGameUtilities.so">
           <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
       </None>
   </ItemGroup>
   ```

1. Create a new script for telling Godot where the library files are located:

   ```csharp
   using System;
   using System.IO;
   using System.Runtime.InteropServices;
   using Godot;

   public partial class AutoSetupRhythmGameUtilities : Node
   {
       public override void _Ready()
       {
           NativeLibrary.SetDllImportResolver(typeof(RhythmGameUtilities.Common).Assembly,
               (name, assembly, path) =>
               {
                   var libDir = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Libs");

                   return name switch
                   {
                       "libRhythmGameUtilities.dll" =>
                           NativeLibrary.Load(Path.Combine(libDir, "Windows", name)),
                       "libRhythmGameUtilities.dylib" =>
                           NativeLibrary.Load(Path.Combine(libDir, "macOS", name)),
                       "libRhythmGameUtilities.so" =>
                           NativeLibrary.Load(Path.Combine(libDir, "Linux", name)),
                       _ => NativeLibrary.Load(name, assembly, path)
                   };
               });
       }
   }
   ```

1. Open **Project** > **Project Settings** >> **Globals** and add the script from above to the top of the list.

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
