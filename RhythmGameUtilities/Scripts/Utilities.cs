using System;
using System.Collections.Generic;
using System.Linq;

namespace RhythmGameUtilities
{

    public static class Utilities
    {

        public const float SECONDS_PER_MINUTE = 60.0f;

        /// <summary>
        /// Convert a tick to a 2D/3D position.
        /// </summary>
        ///
        /// <param name="tick">The tick.</param>
        /// <param name="resolution">The resolution of the song.</param>
        public static float ConvertTickToPosition(int tick, int resolution)
        {
            return tick / (float)resolution;
        }

        /// <summary>
        /// Convert seconds to ticks.
        /// </summary>
        ///
        /// <param name="seconds">The seconds to generate ticks with.</param>
        /// <param name="resolution">The resolution of the song.</param>
        /// <param name="bpmChanges">All BPM changes within the song.</param>
        public static int ConvertSecondsToTicks(float seconds, int resolution, Dictionary<int, int> bpmChanges)
        {
            var totalTicks = 0;
            var remainingSeconds = seconds;
            var previousTick = 0;
            var previousBPM = bpmChanges.First().Value / 1000;

            foreach (var (currentTick, value) in bpmChanges)
            {
                var timeForSegment = (currentTick - previousTick) /
                                     (resolution * previousBPM / SECONDS_PER_MINUTE);

                if (remainingSeconds <= timeForSegment)
                {
                    totalTicks += (int)(remainingSeconds * previousBPM /
                        SECONDS_PER_MINUTE * resolution);

                    return totalTicks;
                }

                totalTicks += currentTick - previousTick;
                remainingSeconds -= timeForSegment;
                previousTick = currentTick;
                previousBPM = value / 1000;
            }

            totalTicks +=
                (int)(remainingSeconds * previousBPM / SECONDS_PER_MINUTE * resolution);

            return totalTicks;
        }

        /// <summary>
        /// Checks to see if the current time of a game or audio file is on the beat.
        /// </summary>
        ///
        /// <param name="bpm">The base BPM for a song.</param>
        /// <param name="currentTime">A timestamp to compare to the BPM.</param>
        /// <param name="delta">The plus/minus delta to test the current time against.</param>
        public static bool IsOnTheBeat(int bpm, float currentTime, float delta = 0.05f)
        {
            var beatInterval = SECONDS_PER_MINUTE / bpm;

            var beatFraction = currentTime / beatInterval;

            var difference = Math.Abs(beatFraction - Math.Round(beatFraction));

            var result = difference < delta;

            return result;
        }

        /// <summary>
        /// Rounds a value up the nearest multiplier.
        /// </summary>
        ///
        /// <param name="value">The value to round.</param>
        /// <param name="multiplier">The multiplier to round using.</param>
        public static int RoundUpToTheNearestMultiplier(int value, int multiplier)
        {
            return (int)Math.Ceiling((float)value / multiplier) * multiplier;
        }

        public static List<KeyValuePair<int, int>> GenerateAdjacentKeyPairs(Dictionary<int, int> keyValuePairs)
        {
            var adjacentKeyPairs = new List<KeyValuePair<int, int>>();

            var keys = new List<int>();

            foreach (var item in keyValuePairs)
            {
                keys.Add(item.Key);
            }

            keys.Sort();

            for (var i = 0; i < keys.Count - 1; i += 1)
            {
                adjacentKeyPairs.Add(new KeyValuePair<int, int>(keys[i], keys[i + 1]));
            }

            return adjacentKeyPairs;
        }

        public static List<BeatBar> CalculateBeatBars(Dictionary<int, int> bpmChanges, int resolution = 192, int ts = 4,
            bool includeHalfNotes = true)
        {
            var beatBars = new List<BeatBar>();

            var keyValuePairs = GenerateAdjacentKeyPairs(bpmChanges);

            foreach (var (startTick, endTick) in keyValuePairs)
            {
                for (var tick = startTick; tick < endTick; tick += resolution)
                {
                    beatBars.Add(new BeatBar { Position = tick, BPM = bpmChanges[startTick] });

                    if (includeHalfNotes && tick != endTick)
                    {
                        beatBars.Add(new BeatBar { Position = tick + resolution / 2, BPM = bpmChanges[startTick] });
                    }
                }
            }

            return beatBars;
        }

        public static Note? FindPositionNearGivenTick(List<Note> notes, int tick, int delta = 50)
        {
            var left = 0;
            var right = notes.Count - 1;

            while (left <= right)
            {
                var mid = (left + right) / 2;

                var currentPosition = notes[mid].Position;

                if (currentPosition + delta < tick)
                {
                    left = mid + 1;
                }
                else if (currentPosition - delta > tick)
                {
                    right = mid - 1;
                }
                else
                {
                    return notes[mid];
                }
            }

            return null;
        }

        /// <summary>
        /// Calculated the accuracy ratio of the current position against a static position.
        /// </summary>
        ///
        /// <param name="position">The position to test against.</param>
        /// <param name="currentPosition">The current position.</param>
        /// <param name="delta">The plus/minus delta to test the current position against.</param>
        public static float CalculateAccuracyRatio(int position, int currentPosition, int delta = 50)
        {
            var diff = position - currentPosition;

            var ratio = Common.InverseLerp(delta, 0, Math.Abs(diff));

            return ratio;
        }

    }

}
