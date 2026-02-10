#### `Chart.ReadResolutionFromChartData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllText("./song.chart");

var resolution = Chart.ReadResolutionFromChartData(contents);

Console.WriteLine(resolution); // 192
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

    auto resolution = ReadResolutionFromChartData(contents.c_str());

    std::cout << resolution << std::endl;

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file = FileAccess.open("res://song.chart", FileAccess.READ)
	var contents = file.get_as_text()

	var resolution = rhythm_game_utilities.read_resolution_from_chart_data(contents)

	print(resolution)
```
