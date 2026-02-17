#### `Utilities.CalculateTiming`

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

var timing = Utilities.CalculateTiming(note.Position, currentPosition, positionDelta);

Console.WriteLine(timing); // Hit
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

    auto timing =
        CalculateTiming(note->Position, currentPosition, positionDelta);

    std::cout << ToString(timing) << std::endl; // Hit

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

	var timing = rhythm_game_utilities.calculate_timing(750, current_position, position_delta)

	match timing:
		rhythm_game_utilities.Miss:
			print("Miss")
		rhythm_game_utilities.Hit:
			print("Hit")
		rhythm_game_utilities.Early:
			print("Early")
		rhythm_game_utilities.Late:
			print("Late")
```
