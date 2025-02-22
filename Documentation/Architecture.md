## Architecture

The current architecture for this project looks like this:

### C++ Library / C# Plugin

```mermaid
graph LR;
    file[/"song.chart"/]

    subgraph audioGraph ["Audio"]
        convertSamplesToWaveform["ConvertSamplesToWaveform()"]
    end

    subgraph commonGraph ["Common"]
        inverseLerp["InverseLerp()"]
        lerp["Lerp()"]
    end

    subgraph parsersGraph ["Parsers"]
        parseSectionsFromChart["ParseSectionsFromChart()"]
        parseTempoChangesFromChartSection["ParseTempoChangesFromChartSection()"]
        parseLyricsFromChartSection["ParseLyricsFromChartSection()"]
        parseMetaDataFromChartSection["ParseMetaDataFromChartSection()"]
        parseNotesFromChartSection["ParseNotesFromChartSection()"]
        parseTimeSignaturesChangesFromChartSection["ParseTimeSignatureChangesFromChartSection()"]

        parseSectionsFromChart-->parseTempoChangesFromChartSection
        parseSectionsFromChart-->parseLyricsFromChartSection
        parseSectionsFromChart-->parseMetaDataFromChartSection
        parseSectionsFromChart-->parseNotesFromChartSection
        parseSectionsFromChart-->parseTimeSignaturesChangesFromChartSection
    end

    subgraph utilitiesGraph ["Utilities"]
        calculateAccuracyRatio["CalculateAccuracyRatio()"]
        calculateBeatBars["CalculateBeatBars()"]
        convertSecondsToTicks["ConvertSecondsToTicks()"]
        convertTickToPosition["ConvertTickToPosition()"]
        isOnTheBeat["IsOnTheBeat()"]
        roundUpToTheNearestMultiplier["RoundUpToTheNearestMultiplier()"]
    end

    file-->parseSectionsFromChart

    parseMetaDataFromChartSection-->calculateAccuracyRatio
    parseNotesFromChartSection-->calculateAccuracyRatio
    convertSecondsToTicks-->calculateAccuracyRatio

    parseMetaDataFromChartSection-->calculateBeatBars
    parseTempoChangesFromChartSection-->calculateBeatBars

    parseMetaDataFromChartSection-->convertSecondsToTicks
    parseTempoChangesFromChartSection-->convertSecondsToTicks
    parseTimeSignaturesChangesFromChartSection-->convertSecondsToTicks

    parseMetaDataFromChartSection-->convertTickToPosition

    parseMetaDataFromChartSection-->isOnTheBeat
```

### Unity Plugin

The Unity plugin includes compiled C++ libraries (macOS, Windows and Linux) and wraps the internal calls in native C# functions. These functions pass and retrieve the data from the C++ library and clean up memory upon completion.

### Unreal Plugin

There isn't a custom wrapper or plugin for Unreal, as the C++ library works as is when included as a header-only library.

### Godot Plugin

Coming soon.

### SDL Library

There isn't a custom wrapper or plugin for SDL, as the C++ library works as is when included as a header-only library.
