using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;

namespace RhythmGameUtilities
{

    [StructLayout(LayoutKind.Sequential)]
    internal struct KeyValuePair
    {

        public IntPtr key;

        public IntPtr value;

    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct ChartSection
    {

        public IntPtr name;

        public IntPtr lines;

        public int lineCount;

    }

    internal static class ParsersInternal
    {

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr ParseSectionsFromChart(string contents, out int size);

    }

    public static class Parsers
    {

        private static readonly Regex JSON_VALUE_PATTERN = new Regex(@"(""[^""]+""|\S+)");

        public static Dictionary<string, IEnumerable<KeyValuePair<string, string[]>>> ParseSectionsFromChart(
            string contents)
        {
            var ptrArray = ParsersInternal.ParseSectionsFromChart(contents, out var size);

            var sections = new Dictionary<string, IEnumerable<KeyValuePair<string, string[]>>>();

            if (ptrArray == IntPtr.Zero)
            {
                return sections;
            }

            var chartSectionSize = Marshal.SizeOf(typeof(ChartSection));
            var keyValuePairSize = Marshal.SizeOf(typeof(KeyValuePair));

            for (var i = 0; i < size; i += 1)
            {
                var chartSectionSizePtr = new IntPtr(ptrArray.ToInt64() + chartSectionSize * i);
                var chartSection = Marshal.PtrToStructure<ChartSection>(chartSectionSizePtr);

                var name = Marshal.PtrToStringAnsi(chartSection.name);

                var lines = new List<KeyValuePair<string, string[]>>();

                for (var j = 0; j < chartSection.lineCount; j += 1)
                {
                    var keyValuePairPtr = new IntPtr(chartSection.lines.ToInt64() + keyValuePairSize * j);
                    var keyValuePair = Marshal.PtrToStructure<KeyValuePair>(keyValuePairPtr);

                    var key = Marshal.PtrToStringAnsi(keyValuePair.key);
                    var value = Marshal.PtrToStringAnsi(keyValuePair.value);

                    // TODO: Move this logic into C++
                    lines.Add(new KeyValuePair<string, string[]>(key, JSON_VALUE_PATTERN
                        .Matches(value).Select(part => part.Value.Trim('"'))
                        .ToArray()));

                    Marshal.FreeHGlobal(keyValuePair.key);
                    Marshal.FreeHGlobal(keyValuePair.value);
                }

                if (name != null)
                {
                    sections.TryAdd(name, lines);
                }

                Marshal.FreeHGlobal(chartSection.name);
                Marshal.FreeHGlobal(chartSection.lines);
            }

            Marshal.FreeHGlobal(ptrArray);

            return sections;
        }

        public static IEnumerable<TrackEvent> ParseTrackEventsFromChartSection(
            IEnumerable<KeyValuePair<string, string[]>> section,
            string typeCode)
        {
            return section
                .Where(item => item.Value[0] == typeCode)
                .Select(item => new TrackEvent
                {
                    Position = int.Parse(item.Key),
                    TypeCode = item.Value[0],
                    Values = item.Value.Skip(1).ToArray()
                }).ToArray();
        }

        public static Dictionary<int, int> ParseBpmFromChartChartSection(
            IEnumerable<KeyValuePair<string, string[]>> section)
        {
            return ParseTrackEventsFromChartSection(section, TypeCode.BPM)
                .Select(trackEvent => new KeyValuePair<int, int>(trackEvent.Position, int.Parse(trackEvent.Values[0])))
                .ToDictionary(item => item.Key, x => x.Value);
        }

        public static Note[] ParseNotesFromChartSection(IEnumerable<KeyValuePair<string, string[]>> section)
        {
            return ParseTrackEventsFromChartSection(section, TypeCode.Note)
                .Where(trackEvent => trackEvent.Values.Length == 2).Select(
                    trackEvent => new Note
                    {
                        Position = trackEvent.Position,
                        HandPosition = int.Parse(trackEvent.Values[0]),
                        Length = int.Parse(trackEvent.Values[1])
                    }).ToArray();
        }

        public static Dictionary<int, string> ParseLyricsFromChartSection(
            IEnumerable<KeyValuePair<string, string[]>> section)
        {
            return ParseTrackEventsFromChartSection(section, TypeCode.Event)
                .Select(
                    trackEvent => new KeyValuePair<int, string>(trackEvent.Position,
                        JSON_VALUE_PATTERN.Matches(trackEvent.Values[0]).Select(part => part.Value.Trim('"'))
                            .First()))
                .Where(trackEvent => trackEvent.Value.StartsWith("lyric"))
                .ToDictionary(item => item.Key, x => x.Value);
        }

    }

}
