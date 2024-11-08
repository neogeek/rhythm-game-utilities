#### `Common.Lerp`

> Languages: `C#` `C++` `GDScript`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var value = Common.Lerp(0, 10, 0.5f);

Console.WriteLine(value); // 5
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Common.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto value = Lerp(0, 10, 0.5f);

    std::cout << value << std::endl; // 5

    return 0;
}
```

##### GDScript

```gdscript
extends Node

func _ready() -> void:
	var value = rhythm_game_utilities.lerp(0, 10, 0.5)

	print(value) # 5
```
