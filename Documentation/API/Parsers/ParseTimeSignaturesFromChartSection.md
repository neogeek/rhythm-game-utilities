#### `Parsers.ParseTimeSignaturesFromChartSection`

> Languages: `C#` `C++` `GDScript`

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

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file = FileAccess.open("res://song.txt", FileAccess.READ)
	var content = file.get_as_text()

	var sections = rhythm_game_utilities.parse_sections_from_chart(content)

	var time_signatures = rhythm_game_utilities.parse_time_signatures_from_chart_section(sections["SyncTrack"])

	print(time_signatures)
```
