#### `Parsers.ParseSectionsFromChart`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var sections = Parsers.ParseSectionsFromChart(contents);

Console.WriteLine(sections.Count); // 4
```

##### C++

```cpp
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers.hpp"

using namespace RhythmGameUtilities;

int main()
{
    auto content = ReadFromFile("./tests/Mocks/song.chart");

    auto sections = ParseSectionsFromChart(content.c_str());

    std::cout << size(sections) << std::endl; // 4

    return 0;
}
```
