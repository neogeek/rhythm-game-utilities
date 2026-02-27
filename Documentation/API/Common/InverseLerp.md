#### `Common.InverseLerp`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var value = Common.InverseLerp(0, 10, 5);

Console.WriteLine(value); // 0.5
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Common.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto value = InverseLerp(0, 10, 5);

    std::cout << value << std::endl; // 0.5

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var value = rhythm_game_utilities.inverse_lerp(0, 10, 5)

	print(value) # 0.5
```

##### Lua

```gdscript
local rhythmgameutilities = require("rhythmgameutilities")

local value = rhythmgameutilities.inverse_lerp(0, 10, 5);

print(value) -- 0.5
```
