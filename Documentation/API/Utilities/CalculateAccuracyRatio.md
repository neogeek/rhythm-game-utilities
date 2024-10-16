#### `Utilities.CalculateAccuracyRatio`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

const int seconds = 2;
const int resolution = 192;
const int positionDelta = 50;

var bpmChanges = new Dictionary<int, int> { { 0, 120000 } };

var note = new Note { Position = 750 };
var currentPosition = Utilities.ConvertSecondsToTicks(seconds, resolution, bpmChanges);

var value = Utilities.CalculateAccuracyRatio(note.Position, currentPosition, positionDelta);

Console.WriteLine(value); // 0.64
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

int main()
{
    const int seconds = 2;
    const int resolution = 192;
    const int positionDelta = 50;

    std::map<int, int> bpmChanges = {{0, 120000}};

    auto note = new Note{750};
    auto currentPosition =
        ConvertSecondsToTicks(seconds, resolution, bpmChanges);

    auto value =
        CalculateAccuracyRatio(note->Position, currentPosition, positionDelta);

    std::cout << value << std::endl; // 0.64

    return 0;
}
```
