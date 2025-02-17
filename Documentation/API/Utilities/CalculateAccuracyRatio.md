#### `Utilities.CalculateAccuracyRatio`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int seconds = 2;
const int resolution = 192;
const int positionDelta = 50;

var tempoChanges = new Tempo[] { new() { Position = 0, BPM = 120000 } };

var timeSignatureChanges = new TimeSignature[] { new() { Position = 0, Numerator = 4, Denominator = 2 } };

var note = new Note { Position = 750 };

var currentPosition =
    Utilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges, timeSignatureChanges);

var value = Utilities.CalculateAccuracyRatio(note.Position, currentPosition, positionDelta);

Console.WriteLine(value); // 0.64
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    const int seconds = 2;
    const int resolution = 192;
    const int positionDelta = 50;

    std::vector<Tempo> tempoChanges = {{0, 120000}};
    std::vector<TimeSignature> timeSignatureChanges = {{0, 4}};

    auto note = new Note{750};
    auto currentPosition = ConvertSecondsToTicks(
        seconds, resolution, tempoChanges, timeSignatureChanges);

    auto value =
        CalculateAccuracyRatio(note->Position, currentPosition, positionDelta);

    std::cout << value << std::endl; // 0.64

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var seconds = 2
	var resolution = 192
	var position_delta = 50

	var tempo_changes = [
		{"position": 0, "bpm": 120000 }
	]

	var time_signature_changes = [
		{"position": 0, "numerator": 4, "denominator": 2 }
	]

	var current_position = rhythm_game_utilities.convert_seconds_to_ticks(seconds, resolution, tempo_changes, time_signature_changes)

	var value = rhythm_game_utilities.calculate_accuracy_ratio(750, current_position, position_delta)

	print(round(value * 100) / 100.0) # 0.64
```
