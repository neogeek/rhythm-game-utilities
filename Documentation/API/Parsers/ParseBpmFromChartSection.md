#### `Parsers.ParseBpmFromChartSection`

> Languages: `C#` `C++` `GDScript`

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
    auto content = ReadStringFromFile("./song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    auto bpm = ParseBpmFromChartSection(
        sections.at(ToString(NamedSection::SyncTrack)));

    std::cout << size(bpm) << std::endl; // 7

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file = FileAccess.open("res://song.chart", FileAccess.READ)
	var content = file.get_as_text()

	var sections = rhythm_game_utilities.parse_sections_from_chart(content)

	var bpm = rhythm_game_utilities.parse_bpm_from_chart_section(sections["SyncTrack"])

	print(bpm)
```
