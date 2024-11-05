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

##### Godot

```gdscript
extends Node

func _ready() -> void:
	var resolution = 192;
	var timeSignature = 4;

	var bpmChanges = {
		0: 88000, 3840: 112000, 9984: 89600,
		22272: 112000, 33792: 111500, 34560: 112000,
		42240: 111980
	}

	var beatBars = rhythm_game_utilities.calculate_beat_bars(bpmChanges, resolution, timeSignature, true);

	print(beatBars)
```
