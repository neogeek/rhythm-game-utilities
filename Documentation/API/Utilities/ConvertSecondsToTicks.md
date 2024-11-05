#### `Utilities.ConvertSecondsToTicks`

> Languages: `C#` `C++` `GDScript`

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

##### Godot

```gdscript
extends Node

func _ready() -> void:
	var seconds = 5;
	var resolution = 192;

	var bpmChanges = {
		0: 88000, 3840: 112000, 9984: 89600,
		22272: 112000, 33792: 111500, 34560: 112000,
		42240: 111980
	}

	var ticks = rhythm_game_utilities.convert_seconds_to_ticks(seconds, resolution, bpmChanges);

	print(ticks) # 1408
```
