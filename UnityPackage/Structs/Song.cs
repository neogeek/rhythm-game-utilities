using System;
using System.Collections.Generic;
using System.Linq;

namespace RhythmGameUtilities
{

    public class Song
    {

        private readonly Dictionary<string, KeyValuePair<string, string[]>[]> _sections;

        public Dictionary<string, string> metaData { get; }

        public int resolution { get; }

        public Tempo[] tempoChanges { get; private set; }

        public TimeSignature[] timeSignatureChanges { get; }

        public Dictionary<Difficulty, Note[]> difficulties { get; private set; }

        public BeatBar[] beatBars { get; private set; }

        public Song(int resolution, Tempo[] tempoChanges, TimeSignature[] timeSignatureChanges,
            Dictionary<Difficulty, Note[]> difficulties)
        {
            this.resolution = resolution;
            this.tempoChanges = tempoChanges;
            this.timeSignatureChanges = timeSignatureChanges;
            this.difficulties = difficulties;
        }

        public Song(string contents)
        {
            _sections = Parsers.ParseSectionsFromChart(contents);

            metaData = Parsers.ParseMetaDataFromChartSection(_sections
                .First(section => section.Key == NamedSection.Song)
                .Value);

            resolution = int.Parse(metaData["Resolution"]);

            tempoChanges = Parsers.ParseTempoChangesFromChartSection(_sections
                .First(section => section.Key == NamedSection.SyncTrack)
                .Value);

            timeSignatureChanges = Parsers.ParseTimeSignatureChangesFromChartSection(_sections[NamedSection.SyncTrack]);

            difficulties = Enum.GetValues(typeof(Difficulty))
                .Cast<Difficulty>()
                .Where(difficulty => _sections.ToDictionary(item => item.Key, item => item.Value)
                    .ContainsKey($"{difficulty}Single"))
                .ToDictionary(difficulty => difficulty,
                    difficulty => Parsers.ParseNotesFromChartSection(_sections[$"{difficulty}Single"]));

            beatBars = Utilities.CalculateBeatBars(tempoChanges, includeHalfNotes : true);
        }

        public void RecalculateBeatBarsWithSongLength(float songLength)
        {
            var lastTick = Utilities.ConvertSecondsToTicks(songLength, resolution, tempoChanges, timeSignatureChanges);

            beatBars = Utilities.CalculateBeatBars(tempoChanges.Concat(new Tempo[]
                {
                    new()
                    {
                        Position = Utilities.RoundUpToTheNearestMultiplier(lastTick, resolution),
                        BPM = tempoChanges.Last().BPM
                    }
                })
                .ToArray(), includeHalfNotes : true);
        }

    }

}
