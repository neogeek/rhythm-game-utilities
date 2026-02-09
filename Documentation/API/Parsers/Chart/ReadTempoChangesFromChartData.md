#### `Chart.ReadTempoChangesFromChartData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var contents = File.ReadAllText(path);

var tempoChanges = Chart.ReadTempoChangesFromChartData(contents);

Console.WriteLine(tempoChanges.Length); // 7
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Chart.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto contents = ReadStringFromFile("./song.chart");

    auto tempoChanges = ReadTempoChangesFromChartData(contents.c_str());

    std::cout << size(tempoChanges) << std::endl; // 7

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents = file.get_as_text()

	var tempo_changes = rhythm_game_utilities.read_tempo_changes_from_chart_data(contents)

	print(tempo_changes)
```
