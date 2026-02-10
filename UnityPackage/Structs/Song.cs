using System.Linq;

namespace RhythmGameUtilities
{

    public class Song
    {

        public int resolution;

        public Tempo[] tempoChanges;

        public TimeSignature[] timeSignatureChanges;

        public Note[] notes;

        public BeatBar[] beatBars;

        public Song()
        {

        }

        public Song(int resolution, Tempo[] tempoChanges, TimeSignature[] timeSignatureChanges,
            Note[] notes)
        {
            this.resolution = resolution;
            this.tempoChanges = tempoChanges;
            this.timeSignatureChanges = timeSignatureChanges;
            this.notes = notes;
        }

        public static Song FromChartData(string contents, Difficulty difficulty)
        {
            var tempoChanges = Chart.ReadTempoChangesFromChartData(contents);

            return new Song
            {
                resolution = Chart.ReadResolutionFromChartData(contents),
                tempoChanges = tempoChanges,
                timeSignatureChanges = Chart.ReadTimeSignatureChangesFromChartData(contents),
                notes = Chart.ReadNotesFromChartData(contents, difficulty),
                beatBars = Utilities.CalculateBeatBars(tempoChanges, includeHalfNotes : true)
            };
        }

        public static Song FromMidiData(byte[] data)
        {
            var tempoChanges = Midi.ReadTempoChangesFromMidiData(data);

            return new Song
            {
                resolution = Midi.ReadResolutionFromMidiData(data),
                tempoChanges = tempoChanges,
                timeSignatureChanges = Midi.ReadTimeSignatureChangesFromMidiData(data),
                notes = Midi.ReadNotesFromMidiData(data),
                beatBars = Utilities.CalculateBeatBars(tempoChanges, includeHalfNotes : true)
            };
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
