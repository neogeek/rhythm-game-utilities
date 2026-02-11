## Architecture

The current architecture for this project looks like this:

### C++ Library / C# Plugin

```mermaid
graph LR;
    chart_file[/"song.chart"/]
    midi_file[/"song.mid"/]

    subgraph audioGraph ["Audio"]
        convertSamplesToWaveform["ConvertSamplesToWaveform()"]
    end

    subgraph commonGraph ["Common"]
        inverseLerp["InverseLerp()"]
        lerp["Lerp()"]
    end

    subgraph parsersGraph ["Parsers"]
        readResolutionFromChartData["ReadResolutionFromChartData()"]
        readTempoChangesFromChartData["ReadTempoChangesFromChartData()"]
        readTimeSignatureChangesFromChartData["ReadTimeSignatureChangesFromChartData()"]
        readNotesFromChartData["ReadNotesFromChartData()"]

        chart_file-->readResolutionFromChartData
        chart_file-->readTempoChangesFromChartData
        chart_file-->readTimeSignatureChangesFromChartData
        chart_file-->readNotesFromChartData

        readResolutionFromMidiData["ReadResolutionFromMidiData()"]
        readTempoChangesFromMidiData["ReadTempoChangesFromMidiData()"]
        readTimeSignatureChangesFromMidiData["ReadTimeSignatureChangesFromMidiData()"]
        readNotesFromMidiData["ReadNotesFromMidiData()"]

        midi_file-->readResolutionFromMidiData
        midi_file-->readTempoChangesFromMidiData
        midi_file-->readTimeSignatureChangesFromMidiData
        midi_file-->readNotesFromMidiData
    end

    subgraph utilitiesGraph ["Utilities"]
        calculateAccuracyRatio["CalculateAccuracyRatio()"]
        calculateBeatBars["CalculateBeatBars()"]
        convertSecondsToTicks["ConvertSecondsToTicks()"]
        convertTickToPosition["ConvertTickToPosition()"]
        isOnTheBeat["IsOnTheBeat()"]
        roundUpToTheNearestMultiplier["RoundUpToTheNearestMultiplier()"]
    end

    convertSecondsToTicks-->calculateAccuracyRatio

    readTempoChangesFromChartData-->calculateBeatBars
    readTempoChangesFromChartData-->convertSecondsToTicks

    readTempoChangesFromMidiData-->calculateBeatBars
    readTempoChangesFromMidiData-->convertSecondsToTicks

    readTimeSignatureChangesFromChartData-->convertSecondsToTicks

    readTimeSignatureChangesFromMidiData-->convertSecondsToTicks

    readNotesFromChartData-->calculateAccuracyRatio

    readNotesFromMidiData-->calculateAccuracyRatio
```

### Unity Plugin

The Unity plugin includes compiled C++ libraries (macOS, Windows and Linux) and wraps the internal calls in native C# functions. These functions pass and retrieve the data from the C++ library and clean up memory upon completion.

### Unreal Plugin

There isn't a custom wrapper or plugin for Unreal, as the C++ library works as is when included as a header-only library.

### Godot Plugin

Coming soon.

### SDL Library

There isn't a custom wrapper or plugin for SDL, as the C++ library works as is when included as a header-only library.
