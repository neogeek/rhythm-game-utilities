> [!CAUTION]
> This package is in early development and should not be used in production.

# Rhythm Game Utilities

[![Tests](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/test.workflow.yml/badge.svg)](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/test.workflow.yml)
[![Build](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/build.workflow.yml/badge.svg)](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/build.workflow.yml)
[![Join the chat at https://discord.gg/nNtFsfd](https://img.shields.io/badge/discord-join%20chat-7289DA.svg)](https://discord.gg/nNtFsfd)

This library is a collection of utilities for creating rhythm games like Tap Tap Revenge, Guitar Hero, and Rock Band. It is meant to be used within any game engine that supports loading C++ libraries, such as Unity, Unreal, and Godot.

![](screenshot.png)
_Prototype game built using these utilities._

## Social

- Star [this repo on GitHub](https://github.com/neogeek/rhythm-game-utilities) for updates
- Follow me on [Bluesky](https://bsky.app/profile/scottdoxey.com) or [Twitter](https://twitter.com/neogeek)
- Join the [Discord](https://discord.gg/nNtFsfd)
- Follow me on [GitHub](https://github.com/neogeek/)

## Table of Contents

- [Install](#install)
- [Platforms](#platforms)
- [Usage](#usage)
- [Architecture](#architecture)
- [Git Hooks](#git-hooks)
- [Testing](#testing)
- [Build](#build)
- [Contributing](#contributing)
- [Community Roadmap](#community-roadmap)
- [License](#license)

## Install

### Unity

Add package via git URL `https://github.com/neogeek/rhythm-game-utilities.git?path=/UnityPackage`.

### Unreal

Coming soon.

### Godot

Coming soon.

### HandcrankEngine

Coming soon.

## Platforms

This library aims to offer support for multiple platforms through a single codebase. This is highly ambitious, so if you run into an issue with your platform of choice during development, please leave a detailed bug report with as much information as possible. Also, as this library is relatively new, mobile platforms will be fully supported after all other platforms are complete.

| Engine                                                                | Platform | Tested |
| --------------------------------------------------------------------- | -------- | :----: |
| [Unity](https://unity.com/)                                           | macOS    |   ✅   |
| [Unity](https://unity.com/)                                           | Windows  |   ✅   |
| [Unity](https://unity.com/)                                           | WebGL    |   ❌   |
| [Unreal](https://www.unrealengine.com/)                               | macOS    |   -    |
| [Unreal](https://www.unrealengine.com/)                               | Windows  |   -    |
| [Godot 4](https://godotengine.org/)                                   | macOS    |   -    |
| [Godot 4](https://godotengine.org/)                                   | Windows  |   -    |
| [Godot 4](https://godotengine.org/)                                   | WebGL    |   -    |
| [HandcrankEngine](https://github.com/HandcrankEngine/HandcrankEngine) | macOS    |   ⏳   |
| [HandcrankEngine](https://github.com/HandcrankEngine/HandcrankEngine) | Windows  |   ⏳   |

## Usage

### `Audio`

#### `Audio.ConvertSamplesToWaveform`

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

#### `Common.Lerp`

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

#### `Common.InverseLerp`

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

### `Parsers`

Read more about `.chart` files: <https://github.com/TheNathannator/GuitarGame_ChartFormats/blob/main/doc/FileFormats/.chart/Core%20Infrastructure.md>

#### `Parsers.ParseSectionsFromChart`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var sections = Parsers.ParseSectionsFromChart(contents);

Console.WriteLine(sections.Count); // 4
```

#### `Parsers.ParseMetaDataFromChartSection`

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
#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    auto metaData = ParseMetaDataFromChartSections(sections);

    std::cout << metaData["Name"] << std::endl; // Example Song
    std::cout << metaData["Resolution"] << std::endl; // 192
    std::cout << metaData["MusicStream"] << std::endl; // Example Song.ogg

    return 0;
}
```

#### `Parsers.ParseTimeSignaturesFromChartSection`

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
#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    auto timeSignatures = ParseTimeSignaturesFromChartSections(sections);

    std::cout << size(timeSignatures) << std::endl; // 4

    return 0;
}
```

#### `Parsers.ParseBpmFromChartSection`

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
#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    auto bpm = ParseBpmFromChartSections(sections);

    std::cout << size(bpm) << std::endl; // 7

    return 0;
}
```

#### `Parsers.ParseNotesFromChartSection`

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
#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    auto notes = ParseNotesFromChartSections(sections, Expert);

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

#### `Parsers.ParseLyricsFromChartSection`

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
#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    auto lyrics = ParseLyricsFromChartSections(sections);

    std::cout << size(lyrics) << std::endl; // 12

    return 0;
}
```

### Utilities

#### `Utilities.ConvertTickToPosition`

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

#### `Utilities.ConvertSecondsToTicks`

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

#### `Utilities.IsOnTheBeat`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int bpm = 120;
const int currentTime = 10;

if (Utilities.IsOnTheBeat(bpm, currentTime))
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
    const int currentTime = 10;

    if (IsOnTheBeat(bpm, currentTime))
    {
        std::cout << "Is on the beat!" << std::endl;
    }

    return 0;
}
```

#### `Utilities.RoundUpToTheNearestMultiplier`

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

#### `Utilities.CalculateAccuracyRatio`

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

#### `Utilities.CalculateBeatBarsInternal`

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

## Architecture

```mermaid
graph LR;
    chartFile["Chart File"]
    chartFileParserCpp["Chart File Parser"]
    chartFileParserCsharp["Chart File Parser"]
    chartFileRender["Chart File Renderer"]

    audioFile["Audio File"]
    audioFileWaveformParserCpp["Audio File Waveform Parser"]
    audioFileWaveformParserCsharp["Audio File Waveform Parser"]
    audioFileWaveformRenderer["Audio File Waveform Renderer"]

    trackRenderer["Track Renderer"]

    userInput["User Input"]
    userInputCheck["User Input Check"]

    subgraph cpp ["C++"]
        chartFileParserCpp
        audioFileWaveformParserCpp
    end

    subgraph csharp ["C#"]
        chartFileParserCsharp
        audioFileWaveformParserCsharp
    end

    subgraph unity ["Unity"]
        chartFileRender
        audioFileWaveformRenderer
        trackRenderer
        userInput
        userInputCheck
    end

    chartFile-->chartFileParserCsharp
    audioFile-->audioFileWaveformParserCsharp

    chartFileParserCpp-->chartFileParserCsharp
    chartFileParserCsharp-->chartFileRender
    audioFileWaveformParserCpp-->audioFileWaveformParserCsharp
    audioFileWaveformParserCsharp-->audioFileWaveformRenderer

    chartFileRender-->trackRenderer
    audioFileWaveformRenderer-->trackRenderer

    userInput-->userInputCheck
    chartFileParserCsharp-->userInputCheck
```

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
