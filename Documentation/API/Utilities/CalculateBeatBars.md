#### `Utilities.CalculateBeatBars`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
var tempoChanges = new Tempo[]
{
    new() { Position = 0, BPM = 88000 }, new() { Position = 3840, BPM = 112000 },
    new() { Position = 9984, BPM = 89600 }, new() { Position = 22272, BPM = 112000 },
    new() { Position = 33792, BPM = 111500 }, new() { Position = 34560, BPM = 112000 },
    new() { Position = 42240, BPM = 111980 }
};

var beatBars = Utilities.CalculateBeatBars(tempoChanges);

Console.WriteLine(beatBars.Length); // 440
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

    std::vector<Tempo> tempoChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    auto beatBars =
        CalculateBeatBars(tempoChanges, resolution, timeSignature, true);

    std::cout << size(beatBars) << std::endl; // 440

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var resolution = 192
	var time_signature = 4

	var tempo_changes = [
		{"position": 0, "bpm": 8800 },
		{"position": 3840, "bpm": 112000 },
		{"position": 9984, "bpm": 89600 },
		{"position": 22272, "bpm": 112000 },
		{"position": 33792, "bpm": 111500 },
		{"position": 34560, "bpm": 112000 },
		{"position": 42240, "bpm": 111980 }
	]

	var beat_bars = rhythm_game_utilities.calculate_beat_bars(tempo_changes, resolution, time_signature, true)

	print(beat_bars)
```
