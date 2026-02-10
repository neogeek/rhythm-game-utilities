#### `Chart.ReadNotesFromChartData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./song.chart");

var notes = Chart.ReadNotesFromChartData(contents, Difficulty.Expert);

Console.WriteLine(notes.Length); // 8
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

    auto notes = ReadNotesFromChartData(contents.c_str(), Difficulty::Expert);

    for (const auto &note : notes)
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

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents = file.get_as_text()

	var notes = rhythm_game_utilities.read_notes_from_chart_data(contents, rhythm_game_utilities.Expert)

	print(notes)
```
