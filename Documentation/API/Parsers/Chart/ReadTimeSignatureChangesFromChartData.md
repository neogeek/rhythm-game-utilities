#### `Chart.ReadTimeSignatureChangesFromChartData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./song.chart");

var timeSignatureChanges = Chart.ReadTimeSignatureChangesFromChartData(contents);

Console.WriteLine(timeSignatureChanges.Length); // 4
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

    auto timeSignatureChanges = ReadTimeSignatureChangesFromChartData(contents.c_str());

    std::cout << size(timeSignatureChanges) << std::endl; // 4

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents = file.get_as_text()

	var time_signature_changes = rhythm_game_utilities.read_time_signature_changes_from_chart_data(contents)

	print(time_signature_changes)
```
