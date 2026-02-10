#### `Midi.ReadTempoChangesFromMidiData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./song.mid");

var tempoChanges = Midi.ReadTempoChangesFromMidiData(bytes);

Console.WriteLine(tempoChanges.Length); // 7
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto bytes = ReadBytesFromFile("./song.mid");

    auto tempoChanges = ReadTempoChangesFromMidiData(bytes);

    std::cout << size(tempoChanges) << std::endl; // 7

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file = FileAccess.open("res://song.mid", FileAccess.READ)
	var bytes = file.get_buffer(file.get_length())

	var tempo_changes = rhythm_game_utilities.read_tempo_changes_from_midi_data(bytes)

	print(tempo_changes)
```
