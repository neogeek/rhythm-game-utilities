#### `Utilities.IsOnTheBeat`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int bpm = 120;
const float currentTime = 10f;
const float delta = 0.05f;

var isOnTheBeat = Utilities.IsOnTheBeat(bpm, currentTime, delta);

Console.WriteLine(isOnTheBeat ? "Is on the beat!" : "Is not on the beat!"); // "Is on the beat!"
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    const int bpm = 120;
    const float currentTime = 10;
    const float delta = 0.05f;

    auto isOnTheBeat = IsOnTheBeat(bpm, currentTime, delta);

    std::cout << (isOnTheBeat ? "Is on the beat!" : "Is not on the beat!")
              << std::endl; // "Is on the beat!"

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var bpm = 120
	var current_time = 10
	var delta = 0.05

	var isOnTheBeat = rhythm_game_utilities.is_on_the_beat(bpm, current_time, delta)

	if isOnTheBeat: # "Is on the beat!"
		print("Is on the beat!")
	else:
		print("Is not on the beat!")
```
