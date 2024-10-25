#### `Utilities.IsOnTheBeat`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int bpm = 120;
const float currentTime = 10f;
const float delta = 0.05f;

if (Utilities.IsOnTheBeat(bpm, currentTime, delta))
{
    Console.WriteLine("Is on the beat!");
}
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    const int bpm = 120;
    const float currentTime = 10f;
    const float delta = 0.05f;

    if (IsOnTheBeat(bpm, currentTime, delta))
    {
        std::cout << "Is on the beat!" << std::endl;
    }

    return 0;
}
```
