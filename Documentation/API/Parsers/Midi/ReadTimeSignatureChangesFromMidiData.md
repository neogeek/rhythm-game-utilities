#### `Midi.ReadTimeSignatureChangesFromMidiData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using System.IO;
using RhythmGameUtilities;

var bytes = File.ReadAllBytes("./song.mid");

var timeSignatureChanges = Midi.ReadTimeSignatureChangesFromMidiData(bytes);

Console.WriteLine(timeSignatureChanges.Length); // 4
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

    auto timeSignatureChanges = ReadTimeSignatureChangesFromMidiData(bytes);

    std::cout << size(timeSignatureChanges) << std::endl; // 4

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file = FileAccess.open("res://song.mid", FileAccess.READ)
	var bytes = file.get_buffer(file.get_length())

	var time_signature_changes = rhythm_game_utilities.read_time_signature_changes_from_midi_data(bytes)

	print(time_signature_changes)
```
