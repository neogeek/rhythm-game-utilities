#### `Parsers.ParseTimeSignatureChangesFromChartSection`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var sections = Parsers.ParseSectionsFromChart(contents);

var timeSignatureChanges = Parsers.ParseTimeSignatureChangesFromChartSection(sections[NamedSection.SyncTrack]);

Console.WriteLine(timeSignatureChanges.Length); // 4
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

    auto timeSignatureChanges = ParseTimeSignatureChangesFromChartSection(
        sections.at(ToString(NamedSection::SyncTrack)));

    std::cout << size(timeSignatureChanges) << std::endl; // 4

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

	var time_signature_changes = rhythm_game_utilities.parse_time_signature_changes_from_chart_section(sections["SyncTrack"])

	print(time_signature_changes)
```
