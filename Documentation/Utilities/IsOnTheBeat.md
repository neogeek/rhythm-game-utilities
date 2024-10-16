#### `Utilities.IsOnTheBeat`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int bpm = 120;
const int currentTime = 10;

if (Utilities.IsOnTheBeat(bpm, currentTime))
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
    const int currentTime = 10;

    if (IsOnTheBeat(bpm, currentTime))
    {
        std::cout << "Is on the beat!" << std::endl;
    }

    return 0;
}
```
