#### `Midi.ReadResolutionFromMidiData`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using System.IO;
using RhythmGameUtilities;

var contents = File.ReadAllBytes("./song.mid");

var resolution = Midi.ReadResolutionFromMidiData(contents);

Console.WriteLine(resolution); // 192
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto contents = ReadByteFromfile("./song.mid");

    auto resolution = ReadResolutionFromMidiData(contents);

    std::cout << resolution << std::endl;

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var file = FileAccess.open("res://song.mid", FileAccess.READ)
	var contents = file.get_buffer(file.get_length())

	var resolution = rhythm_game_utilities.read_resolution_from_midi_data(contents)

	print(resolution)
```
