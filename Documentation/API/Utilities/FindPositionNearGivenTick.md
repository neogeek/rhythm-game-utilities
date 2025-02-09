#### `Utilities.FindPositionNearGivenTick`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
var notes = new Note[]
{
    new() { Position = 768 }, new() { Position = 960 }, new() { Position = 1152 },
    new() { Position = 1536 }, new() { Position = 1728 }, new() { Position = 1920 },
    new() { Position = 2304 }, new() { Position = 2496 }, new() { Position = 2688 },
    new() { Position = 3072 }, new() { Position = 3264 }
};

var note = Utilities.FindPositionNearGivenTick(notes, 750);

if (note != null)
{
    Console.Write(note.Value.Position); // 768
}
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    std::vector<Note> notes = {{768, 0, 0},  {960, 0, 0},  {1152, 0, 0},
                               {1536, 0, 0}, {1728, 0, 0}, {1920, 0, 0},
                               {2304, 0, 0}, {2496, 0, 0}, {2688, 0, 0},
                               {3072, 0, 0}, {3264, 0, 0}};

    auto note = FindPositionNearGivenTick(notes, 750);

    if (note)
    {
        std::cout << note->Position << std::endl; // 768
    }

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var seconds = 5
	var resolution = 192

	var notes = [
		{"position": 768 }, {"position": 960 }, {"position": 1152 },
		{"position": 1536 }, {"position": 1728 }, {"position": 1920 },
		{"position": 2304 }, {"position": 2496 }, {"position": 2688 },
		{"position": 3072 }, {"position": 3264 }
	]

	var note = rhythm_game_utilities.find_position_near_given_tick(notes, 750);

	print(note["position"]) # 768
```
