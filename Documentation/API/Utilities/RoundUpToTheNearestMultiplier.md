#### `Utilities.RoundUpToTheNearestMultiplier`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var value = Utilities.RoundUpToTheNearestMultiplier(12, 10);

Console.WriteLine(value); // 20
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto value = RoundUpToTheNearestMultiplier(12, 10);

    std::cout << value << std::endl; // 20

    return 0;
}
```

##### Godot

```gdscript
extends Node

func _ready() -> void:
	var value = rhythm_game_utilities.round_up_to_the_nearest_multiplier(12, 10);

	print(value) # 20
```
