#### `Parsers.ParseBpmFromChartSection`

> Languages: `C#` `C++`

##### C#

```csharp
using System;
using RhythmGameUtilities;

var sections = Parsers.ParseSectionsFromChart(contents);

var bpm = Parsers.ParseBpmFromChartSection(sections[NamedSection.SyncTrack]);

Console.WriteLine(bpm.Count); // 7
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

    auto bpm = ParseBpmFromChartSection(
        sections.at(ToString(NamedSection::SyncTrack)));

    std::cout << size(bpm) << std::endl; // 7

    return 0;
}
```
