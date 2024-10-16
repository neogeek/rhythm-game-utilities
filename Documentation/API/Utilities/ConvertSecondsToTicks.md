#### `Utilities.ConvertSecondsToTicks`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int seconds = 5;
const int resolution = 192;

var bpmChanges = new Dictionary<int, int>
{
    { 0, 88000 },
    { 3840, 112000 },
    { 9984, 89600 },
    { 22272, 112000 },
    { 33792, 111500 },
    { 34560, 112000 },
    { 42240, 111980 }
};

var ticks = Utilities.ConvertSecondsToTicks(seconds, resolution, bpmChanges);

Console.WriteLine(ticks); // 1408
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    const int seconds = 5;
    const int resolution = 192;

    std::map<int, int> bpmChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    auto ticks = ConvertSecondsToTicks(seconds, resolution, bpmChanges);

    std::cout << ticks << std::endl; // 1408

    return 0;
}
```
