using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;

namespace RhythmGameUtilities
{

    [StructLayout(LayoutKind.Sequential)]
    internal struct KeyValuePairInternal
    {

        public IntPtr key;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public IntPtr[] values;

        public int valuesCount;

    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct ChartSectionInternal
    {

        public IntPtr name;

        public IntPtr lines;

        public int lineCount;

    }

    internal static class ParsersInternal
    {

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr ParseSectionsFromChartInternal(string contents, out int size);

    }

    public static class Parsers
    {

        private static readonly Regex JSON_VALUE_PATTERN = new(@"(""[^""]+""|\S+)");

        public static Dictionary<string, KeyValuePair<string, string[]>[]> ParseSectionsFromChart(
            string contents)
        {
            var ptrArray = ParsersInternal.ParseSectionsFromChartInternal(contents, out var size);

            var sections = new Dictionary<string, KeyValuePair<string, string[]>[]>();

            if (ptrArray == IntPtr.Zero)
            {
                return sections;
            }

            var chartSectionSize = Marshal.SizeOf(typeof(ChartSectionInternal));
            var keyValuePairSize = Marshal.SizeOf(typeof(KeyValuePairInternal));

            for (var i = 0; i < size; i += 1)
            {
                var chartSectionSizePtr = new IntPtr(ptrArray.ToInt64() + chartSectionSize * i);
                var chartSection = Marshal.PtrToStructure<ChartSectionInternal>(chartSectionSizePtr);

                var name = Marshal.PtrToStringAnsi(chartSection.name);

                var lines = new List<KeyValuePair<string, string[]>>();

                for (var j = 0; j < chartSection.lineCount; j += 1)
                {
                    var keyValuePairPtr = new IntPtr(chartSection.lines.ToInt64() + keyValuePairSize * j);
                    var keyValuePair = Marshal.PtrToStructure<KeyValuePairInternal>(keyValuePairPtr);

                    var key = Marshal.PtrToStringAnsi(keyValuePair.key);
                    var values = new string[keyValuePair.valuesCount];

                    for (var k = 0; k < keyValuePair.valuesCount; k += 1)
                    {
                        values[k] = Marshal.PtrToStringAnsi(keyValuePair.values[k]);

                        Marshal.FreeHGlobal(keyValuePair.values[k]);
                    }

                    Marshal.FreeHGlobal(keyValuePair.key);

                    lines.Add(new KeyValuePair<string, string[]>(key, values));
                }

                if (name != null)
                {
                    sections.TryAdd(name, lines.ToArray());
                }

                Marshal.FreeHGlobal(chartSection.name);
                Marshal.FreeHGlobal(chartSection.lines);
            }

            Marshal.FreeHGlobal(ptrArray);

            return sections;
        }

        public static Dictionary<string, string> ParseMetaDataFromChartSection(
            KeyValuePair<string, string[]>[] section)
        {
            return section.Where(item => item.Value.Length >= 1)
                .ToDictionary(item => item.Key, x => x.Value[0]);
        }

        public static TimeSignature[] ParseTimeSignatureChangesFromChartSection(
            KeyValuePair<string, string[]>[] section)
        {
            return section
                .Where(item => item.Value.Length >= 2 && item.Value[0] == TypeCode.TimeSignatureMarker)
                .OrderBy(item => int.Parse(item.Key)).Select(item => new TimeSignature
                {
                    Position = int.Parse(item.Key),
                    Numerator = int.Parse(item.Value.Skip(1).First()),
                    Denominator = item.Value.Length > 2 ? int.Parse(item.Value.Skip(2).First()) : 2
                }).ToArray();
        }

        public static Tempo[] ParseTempoChangesFromChartSection(
            KeyValuePair<string, string[]>[] section)
        {
            return section
                .Where(item => item.Value[0] == TypeCode.BPM_Marker)
                .Select(item => new KeyValuePair<int, int>(int.Parse(item.Key), int.Parse(item.Value.Skip(1).First())))
                .OrderBy(item => item.Key).Select(item => new Tempo { Position = item.Key, BPM = item.Value })
                .ToArray();
        }

        public static Note[] ParseNotesFromChartSection(KeyValuePair<string, string[]>[] section)
        {
            return section
                .Where(item => item.Value.Length == 3 && item.Value[0] == TypeCode.NoteMarker).Select(item =>
                    new Note
                    {
                        Position = int.Parse(item.Key),
                        HandPosition = int.Parse(item.Value.Skip(1).First()),
                        Length = int.Parse(item.Value.Skip(2).First())
                    }).ToArray();
        }

        public static Dictionary<int, string> ParseLyricsFromChartSection(
            KeyValuePair<string, string[]>[] section)
        {
            return section
                .Where(item => item.Value[0] == TypeCode.EventMarker)
                .Select(item => new KeyValuePair<int, string>(int.Parse(item.Key),
                    JSON_VALUE_PATTERN.Matches(item.Value.Skip(1).First()).Select(part => part.Value.Trim('"'))
                        .First()))
                .Where(item => item.Value.StartsWith("lyric"))
                .ToDictionary(item => item.Key, x => x.Value);
        }

    }

}
