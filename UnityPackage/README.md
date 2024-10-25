> [!CAUTION]
> This package is in early development and should not be used in production.

# Rhythm Game Utilities

[![Tests](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/test.workflow.yml/badge.svg)](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/test.workflow.yml)
[![Build](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/build.workflow.yml/badge.svg)](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/build.workflow.yml)
[![Join the chat at https://discord.gg/nNtFsfd](https://img.shields.io/badge/discord-join%20chat-7289DA.svg)](https://discord.gg/nNtFsfd)

This library is a collection of utilities for creating rhythm games like Tap Tap Revenge, Guitar Hero, and Rock Band. It is meant to be used within any game engine that supports loading C++ libraries, such as Unity, Unreal, Godot and SDL.

![](screenshot.png)
_Prototype game built using these utilities._

## Features

- 🎵 Parse `.chart` and `.midi` song files
- 🎼 Calculate position to render notes
- 💯 Calculate hit accuracy
- 🥁 Determine if the current time is on the beat
- 💫 And more!

## Social

- Star [this repo on GitHub](https://github.com/neogeek/rhythm-game-utilities) for updates
- Follow me on [Bluesky](https://bsky.app/profile/scottdoxey.com) or [Twitter](https://twitter.com/neogeek)
- Join the [Discord](https://discord.gg/nNtFsfd)
- Follow me on [GitHub](https://github.com/neogeek/)

## Table of Contents

- [Platforms](#platforms)
- [Install](#install)
- [API](#api)

  1. [Audio](#audio)
     1. [ConvertSamplesToWaveform](#audioconvertsamplestowaveform)
  1. [Common](#common)
     1. [InverseLerp](#commoninverselerp)
     1. [Lerp](#commonlerp)
  1. [Parsers](#parsers)
     1. [ParseBpmFromChartSection](#parsersparsebpmfromchartsection)
     1. [ParseLyricsFromChartSection](#parsersparselyricsfromchartsection)
     1. [ParseMetaDataFromChartSection](#parsersparsemetadatafromchartsection)
     1. [ParseNotesFromChartSection](#parsersparsenotesfromchartsection)
     1. [ParseSectionsFromChart](#parsersparsesectionsfromchart)
     1. [ParseTimeSignaturesFromChartSection](#parsersparsetimesignaturesfromchartsection)
  1. [Utilities](#utilities)
     1. [CalculateAccuracyRatio](#utilitiescalculateaccuracyratio)
     1. [CalculateBeatBars](#utilitiescalculatebeatbars)
     1. [ConvertSecondsToTicks](#utilitiesconvertsecondstoticks)
     1. [ConvertTickToPosition](#utilitiesconvertticktoposition)
     1. [IsOnTheBeat](#utilitiesisonthebeat)
     1. [RoundUpToTheNearestMultiplier](#utilitiesrounduptothenearestmultiplier)

- [Architecture](#architecture)
- [Git Hooks](#git-hooks)
- [Testing](#testing)
- [Build](#build)
- [Contributing](#contributing)
- [Community Roadmap](#community-roadmap)
- [License](#license)

## Platforms

This library aims to offer support for multiple platforms through a single codebase. This is highly ambitious, so if you run into an issue with your platform of choice during development, please leave a detailed bug report with as much information as possible. Also, as this library is relatively new, mobile platforms will be fully supported after all other platforms are complete.

| Engine                                  | Language | Platform |                  Version                  | Tested | Stable |
| --------------------------------------- | -------- | -------- | :---------------------------------------: | :----: | :----: |
| [Unity](https://unity.com/)             | C#       | macOS    | 6000.0.22f1<br>2022.3.50f1<br>2021.3.44f1 |   ✅   |   ❌   |
| [Unity](https://unity.com/)             | C#       | Windows  | 6000.0.22f1<br>2022.3.50f1<br>2021.3.44f1 |   ✅   |   ❌   |
| [Unreal](https://www.unrealengine.com/) | C++      | macOS    |                   5.4.4                   |   ✅   |   ❌   |
| [Unreal](https://www.unrealengine.com/) | C++      | Windows  |                   5.4.4                   |   ✅   |   ❌   |
| [Godot 4](https://godotengine.org/)     | GDScript | macOS    |                     -                     |   -    |   -    |
| [Godot 4](https://godotengine.org/)     | GDScript | Windows  |                     -                     |   -    |   -    |
| [Godot 4](https://godotengine.org/)     | C#       | macOS    |                    4.3                    |   ✅   |   ❌   |
| [Godot 4](https://godotengine.org/)     | C#       | Windows  |                    4.3                    |   ✅   |   ❌   |
| [SDL](https://www.libsdl.org/)          | C++      | macOS    |                  2.30.8                   |   ✅   |   ❌   |
| [SDL](https://www.libsdl.org/)          | C++      | Windows  |                     -                     |   -    |   -    |

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
       Include="$(HOME)/git/github/rhythm-game-utilities/RhythmGameUtilities/RhythmGameUtilities.csproj" />
   </ItemGroup>
   ```

1. Add config to your `.csproj` file to copy the library files before a build:

   ```xml
   <ItemGroup Condition="$([MSBuild]::IsOSPlatform('Windows'))">
       <None
           Include="$(HOME)/git/github/rhythm-game-utilities/RhythmGameUtilities/Libs/Windows/libRhythmGameUtilities.dll">
           <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
       </None>
   </ItemGroup>

   <ItemGroup Condition="$([MSBuild]::IsOSPlatform('OSX'))">
       <None
           Include="$(HOME)/git/github/rhythm-game-utilities/RhythmGameUtilities/Libs/macOS/libRhythmGameUtilities.dylib">
           <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
       </None>
   </ItemGroup>

   <ItemGroup Condition="$([MSBuild]::IsOSPlatform('Linux'))">
       <None
           Include="$(HOME)/git/github/rhythm-game-utilities/RhythmGameUtilities/Libs/Linux/libRhythmGameUtilities.so">
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

## API

### `Audio`

#### `Audio.ConvertSamplesToWaveform`

> Languages: `C#`

```csharp
using RhythmGameUtilities;

var samples = new float[_audioSource.clip.samples * _audioSource.clip.channels];

_audioSource.clip.GetData(samples, 0);

var color = Color.red;
var transparentColor = new Color(0, 0, 0, 0);

var waveform = Audio.ConvertSamplesToWaveform(samples, _texture2D.width, _texture2D.height);

for (var x = 0; x < waveform.Length; x += 1)
{
    for (var y = 0; y < waveform[x].Length; y += 1)
    {
        _texture2D.SetPixel(x, y, waveform[x][y] == 1 ? color : transparentColor);
    }
}

_texture2D.Apply();
```

### Common

#### `Common.InverseLerp`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var value = Common.InverseLerp(0, 10, 5);

Console.WriteLine(value); // 0.5
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Common.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto value = InverseLerp(0, 10, 5);

    std::cout << value << std::endl; // 0.5

    return 0;
}
```

#### `Common.Lerp`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var value = Common.Lerp(0, 10, 0.5f);

Console.WriteLine(value); // 5
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Common.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto value = Lerp(0, 10, 0.5f);

    std::cout << value << std::endl; // 5

    return 0;
}
```

### `Parsers`

Read more about `.chart` files: <https://github.com/TheNathannator/GuitarGame_ChartFormats/blob/main/doc/FileFormats/.chart/Core%20Infrastructure.md>

#### `Parsers.ParseBpmFromChartSection`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var sections = Parsers.ParseSectionsFromChart(contents);

var bpm = Parsers.ParseBpmFromChartSection(sections[NamedSection.SyncTrack]);

Console.WriteLine(bpm.Count); // 7
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    auto bpm = ParseBpmFromChartSection(
        sections.at(ToString(NamedSection::SyncTrack)));

    std::cout << size(bpm) << std::endl; // 7

    return 0;
}
```

#### `Parsers.ParseLyricsFromChartSection`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var sections = Parsers.ParseSectionsFromChart(contents);

var lyrics = Parsers.ParseLyricsFromChartSection(sections[NamedSection.Events]);

Console.WriteLine(notes.Count); // 12
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    auto lyrics = ParseLyricsFromChartSection(
        sections.at(ToString(NamedSection::Events)));

    std::cout << size(lyrics) << std::endl; // 12

    return 0;
}
```

#### `Parsers.ParseMetaDataFromChartSection`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var sections = Parsers.ParseSectionsFromChart(contents);

var metaData = Parsers.ParseMetaDataFromChartSection(sections[NamedSection.Song]);

Console.WriteLine(metaData["Name"]); // Example Song
Console.WriteLine(metaData["Resolution"]); // 192
Console.WriteLine(metaData["MusicStream"]); // Example Song.ogg
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    auto metaData = ParseMetaDataFromChartSection(
        sections.at(ToString(NamedSection::Song)));

    std::cout << metaData["Name"] << std::endl; // Example Song
    std::cout << metaData["Resolution"] << std::endl; // 192
    std::cout << metaData["MusicStream"] << std::endl; // Example Song.ogg

    return 0;
}
```

#### `Parsers.ParseNotesFromChartSection`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var sections = Parsers.ParseSectionsFromChart(contents);

var notes = Parsers.ParseNotesFromChartSection(sections[$"{Difficulty.Expert}Single"]);

Console.WriteLine(notes.Count); // 8
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    auto notes = ParseNotesFromChartSection(
        sections.at(ToString(Difficulty::Expert) + "Single"));

    for (auto &note : notes)
    {
        if (note.HandPosition > 5)
        {
            continue;
        }

        std::cout << note.Position << " " << note.HandPosition << std::endl;
    }

    return 0;
}
```

#### `Parsers.ParseSectionsFromChart`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var sections = Parsers.ParseSectionsFromChart(contents);

Console.WriteLine(sections.Count); // 4
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    std::cout << size(sections) << std::endl; // 4

    return 0;
}
```

#### `Parsers.ParseTimeSignaturesFromChartSection`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var sections = Parsers.ParseSectionsFromChart(contents);

var timeSignatures = Parsers.ParseTimeSignaturesFromChartSection(sections[NamedSection.SyncTrack]);

Console.WriteLine(timeSignatures.Count); // 4
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    auto timeSignatures = ParseTimeSignaturesFromChartSection(
        sections.at(ToString(NamedSection::SyncTrack)));

    std::cout << size(timeSignatures) << std::endl; // 4

    return 0;
}
```

### Utilities

#### `Utilities.CalculateAccuracyRatio`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int seconds = 2;
const int resolution = 192;
const int positionDelta = 50;

var bpmChanges = new Dictionary<int, int> { { 0, 120000 } };

var note = new Note { Position = 750 };
var currentPosition = Utilities.ConvertSecondsToTicks(seconds, resolution, bpmChanges);

var value = Utilities.CalculateAccuracyRatio(note.Position, currentPosition, positionDelta);

Console.WriteLine(value); // 0.64
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    const int seconds = 2;
    const int resolution = 192;
    const int positionDelta = 50;

    std::map<int, int> bpmChanges = {{0, 120000}};

    auto note = new Note{750};
    auto currentPosition =
        ConvertSecondsToTicks(seconds, resolution, bpmChanges);

    auto value =
        CalculateAccuracyRatio(note->Position, currentPosition, positionDelta);

    std::cout << value << std::endl; // 0.64

    return 0;
}
```

#### `Utilities.CalculateBeatBars`

> Languages: `C#` `C++`

##### C#

```csharp
const int resolution = 192;
const int timeSignature = 4;

var bpmChanges = new Dictionary<int, int>
{
    { 0, 88000 },
    { 3840, 112000 },
    { 9984, 89600 },
    { 22272, 112000 },
    { 33792, 111500 },
    { 34560, 112000 },
    { 42240, 111980 }
};

var beatBars = Utilities.CalculateBeatBars(bpmChanges, resolution, timeSignature, true);

Console.WriteLine(beatBars.Count); // 440
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    const int resolution = 192;
    const int timeSignature = 4;

    std::map<int, int> bpmChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    auto beatBars =
        CalculateBeatBars(bpmChanges, resolution, timeSignature, true);

    std::cout << size(beatBars) << std::endl; // 440

    return 0;
}
```

#### `Utilities.ConvertSecondsToTicks`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int seconds = 5;
const int resolution = 192;

var bpmChanges = new Dictionary<int, int>
{
    { 0, 88000 },
    { 3840, 112000 },
    { 9984, 89600 },
    { 22272, 112000 },
    { 33792, 111500 },
    { 34560, 112000 },
    { 42240, 111980 }
};

var ticks = Utilities.ConvertSecondsToTicks(seconds, resolution, bpmChanges);

Console.WriteLine(ticks); // 1408
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    const int seconds = 5;
    const int resolution = 192;

    std::map<int, int> bpmChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    auto ticks = ConvertSecondsToTicks(seconds, resolution, bpmChanges);

    std::cout << ticks << std::endl; // 1408

    return 0;
}
```

#### `Utilities.ConvertTickToPosition`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int tick = 2784;
const int resolution = 192;

var position = Utilities.ConvertTickToPosition(tick, resolution);

Console.WriteLine(position); // 14.5
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    const int tick = 2784;
    const int resolution = 192;

    auto position = ConvertTickToPosition(tick, resolution);

    std::cout << position << std::endl; // 14.5

    return 0;
}
```

#### `Utilities.IsOnTheBeat`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int bpm = 120;
const float currentTime = 10f;
const float delta = 0.05f;

if (Utilities.IsOnTheBeat(bpm, currentTime, delta))
{
    Console.WriteLine("Is on the beat!");
}
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    const int bpm = 120;
    const float currentTime = 10f;
    const float delta = 0.05f;

    if (IsOnTheBeat(bpm, currentTime, delta))
    {
        std::cout << "Is on the beat!" << std::endl;
    }

    return 0;
}
```

#### `Utilities.RoundUpToTheNearestMultiplier`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var value = Utilities.RoundUpToTheNearestMultiplier(12, 10);

Console.WriteLine(value); // 20
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto value = RoundUpToTheNearestMultiplier(12, 10);

    std::cout << value << std::endl; // 20

    return 0;
}
```

## Architecture

The current architecture for this project looks like this:

### C++ Library / C# Plugin

```mermaid
graph LR;
    file[/"song.chart"/]

    subgraph audioGraph ["Audio"]
        convertSamplesToWaveform["ConvertSamplesToWaveform()"]
    end

    subgraph commonGraph ["Common"]
        inverseLerp["InverseLerp()"]
        lerp["Lerp()"]
    end

    subgraph parsersGraph ["Parsers"]
        parseSectionsFromChart["ParseSectionsFromChart()"]
        parseBpmFromChartSection["ParseBpmFromChartSection()"]
        parseLyricsFromChartSection["ParseLyricsFromChartSection()"]
        parseMetaDataFromChartSection["ParseMetaDataFromChartSection()"]
        parseNotesFromChartSection["ParseNotesFromChartSection()"]
        parseTimeSignaturesFromChartSection["ParseTimeSignaturesFromChartSection()"]

        parseSectionsFromChart-->parseBpmFromChartSection
        parseSectionsFromChart-->parseLyricsFromChartSection
        parseSectionsFromChart-->parseMetaDataFromChartSection
        parseSectionsFromChart-->parseNotesFromChartSection
        parseSectionsFromChart-->parseTimeSignaturesFromChartSection
    end

    subgraph utilitiesGraph ["Utilities"]
        calculateAccuracyRatio["CalculateAccuracyRatio()"]
        calculateBeatBars["CalculateBeatBars()"]
        convertSecondsToTicks["ConvertSecondsToTicks()"]
        convertTickToPosition["ConvertTickToPosition()"]
        isOnTheBeat["IsOnTheBeat()"]
        roundUpToTheNearestMultiplier["RoundUpToTheNearestMultiplier()"]
    end

    file-->parseSectionsFromChart

    parseMetaDataFromChartSection-->calculateAccuracyRatio
    parseNotesFromChartSection-->calculateAccuracyRatio
    convertSecondsToTicks-->calculateAccuracyRatio

    parseBpmFromChartSection-->calculateBeatBars
    parseMetaDataFromChartSection-->calculateBeatBars

    parseMetaDataFromChartSection-->convertSecondsToTicks
    parseBpmFromChartSection-->convertSecondsToTicks

    parseMetaDataFromChartSection-->convertTickToPosition

    parseMetaDataFromChartSection-->isOnTheBeat
```

### Unity Plugin

The Unity plugin includes compiled C++ libraries (macOS, Windows and Linux) and wraps the internal calls in native C# functions. These functions pass and retrieve the data from the C++ library and clean up memory upon completion.

### Unreal Plugin

There isn't a custom wrapper or plugin for Unreal, as the C++ library works as is when included as a header-only library.

### Godot Plugin

Coming soon.

### SDL Library

There isn't a custom wrapper or plugin for SDL, as the C++ library works as is when included as a header-only library.

## Git Hooks

The git hooks that run are quick file checks to ensure the files in the dotnet project and the UnityProject are the same and that the build files haven't changed.

```bash
$ git config --local core.hooksPath .githooks/
```

## Testing

Run all tests via `make test`.

- Tests for the C++ library are authored using the C++ native library `cassert`.
- Tests are run automatically via GitHub Actions on each new PR.
- For you add a new feature or fix a bug, please include the benchmark output in the PR along with your device stats.

If you want to test the projecet from within Unity, add the test namespace to your project by adding the following to your `Packages/manifest.json` file:

```json
{
...
    "testables": ["com.scottdoxey.rhythm-game-utilities"]
...
}
```

## Build

> [!WARNING]
> Do not commit any build changes to the repo. The build files are automatically generated via GitHub Actions.

### macOS

When developing on macOS, make sure that **Mac** is selected in the bottom right-hand corner of Visual Studio Code or C++ Intellisense will not work.

```bash
./bin/build.sh
```

### Windows

When developing on Windows, make sure that **Win32** is selected in the bottom right-hand corner of Visual Studio Code or C++ Intellisense will not work.

Run from **x64 Native Tools Command Prompt for VS**:

```cmd
call "./bin/build.bat"
```

## Contributing

Be sure to review the [Contributing Guidelines](./CONTRIBUTING.md) before logging an issue or making a pull request.

## Community Roadmap

This project aims to help you build your rhythm game as fast as possible without needing to learn the complexities of a new library. Instead, you can utilize comprehensive examples and simple code recipes If you have feature requests or bugs, please create an issue and tag them with the appropriate tag. If an issue already exists, vote for it with 👍.

- [Feature Requests](https://github.com/neogeek/rhythm-game-utilities/labels/enhancement)
- [Bugs](https://github.com/neogeek/rhythm-game-utilities/labels/bug)

## License

[The MIT License (MIT)](./LICENSE)

