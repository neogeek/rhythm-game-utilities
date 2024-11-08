#### `Utilities.ConvertTickToPosition`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int tick = 2784;
const int resolution = 192;

var position = Utilities.ConvertTickToPosition(tick, resolution);

Console.WriteLine(position); // 14.5
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    const int tick = 2784;
    const int resolution = 192;

    auto position = ConvertTickToPosition(tick, resolution);

    std::cout << position << std::endl; // 14.5

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var tick = 2784
	var resolution = 192

	var position = rhythm_game_utilities.convert_tick_to_position(tick, resolution)

	print(position) # 14.5
```
