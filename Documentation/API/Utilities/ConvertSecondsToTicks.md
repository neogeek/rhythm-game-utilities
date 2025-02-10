#### `Utilities.ConvertSecondsToTicks`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int seconds = 5;
const int resolution = 192;

var bpmChanges = new Tempo[]
{
    new() { Position = 0, BPM = 88000 }, new() { Position = 3840, BPM = 112000 },
    new() { Position = 9984, BPM = 89600 }, new() { Position = 22272, BPM = 112000 },
    new() { Position = 33792, BPM = 111500 }, new() { Position = 34560, BPM = 112000 },
    new() { Position = 42240, BPM = 111980 }
};

var timeSignatureChanges = new TimeSignature[] { new() { Position = 0, Numerator = 4, Denominator = 2 } };

var ticks = Utilities.ConvertSecondsToTicks(seconds, resolution, bpmChanges, timeSignatureChanges);

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

    std::vector<Tempo> bpmChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    std::vector<TimeSignature> timeSignatureChanges = {{0, 4, 2}};

    auto ticks = ConvertSecondsToTicks(seconds, resolution, bpmChanges,
                                       timeSignatureChanges);

    std::cout << ticks << std::endl; // 1408

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var seconds = 5
	var resolution = 192

	var bpm_changes = [
		{"position": 0, "bpm": 88000 },
		{"position": 3840, "bpm": 112000 },
		{"position": 9984, "bpm": 89600 },
		{"position": 22272, "bpm": 112000 },
		{"position": 33792, "bpm": 111500 },
		{"position": 34560, "bpm": 112000 },
		{"position": 42240, "bpm": 111980 }
	]

	var time_signature_changes = [
		{"position": 0, "numerator": 4, "denominator": 2 }
	]

	var current_position = rhythm_game_utilities.convert_seconds_to_ticks(seconds, resolution, bpm_changes, time_signature_changes)

	print(current_position) # 1408
```
