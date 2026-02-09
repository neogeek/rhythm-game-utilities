#### `Midi.ReadNotesFromMidiData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var contents = File.ReadAllBytes(path);

var notes = Midi.ReadNotesFromMidiData(contents, Difficulty::Expert);

Console.WriteLine(notes.Length); // 8
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto contents = ReadBytesFromFile("./song.mid");

    auto notes = ReadNotesFromMidiData(contents, Difficulty::Expert);

    for (const auto &note : notes)
    {
        if (note.HandPosition > 5)
        {
            continue;
        }

        std::cout << note.Position << " " << note.HandPosition << std::endl;
    }

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file = FileAccess.open("res://song.mid", FileAccess.READ)
	var contents = file.get_buffer(file.get_length())

	var notes = rhythm_game_utilities.read_notes_from_midi_data(contents)

	print(notes)
```
