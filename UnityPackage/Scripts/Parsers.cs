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

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
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
            return section.ToDictionary(item => item.Key, x => x.Value.First());
        }

        public static Dictionary<int, int[]> ParseTimeSignaturesFromChartSection(
            KeyValuePair<string, string[]>[] section)
        {
            return section
                .Where(item => item.Value[0] == TypeCode.TimeSignatureMarker)
                .Select(item =>
                    new KeyValuePair<int, int[]>(int.Parse(item.Key), item.Value.Skip(1).Select(int.Parse).ToArray()))
                .ToDictionary(item => item.Key, x => x.Value);
        }

        public static Dictionary<int, int> ParseBpmFromChartSection(
            KeyValuePair<string, string[]>[] section)
        {
            return section
                .Where(item => item.Value[0] == TypeCode.BPM_Marker)
                .Select(item => new KeyValuePair<int, int>(int.Parse(item.Key), int.Parse(item.Value.Skip(1).First())))
                .OrderBy(item => item.Key)
                .ToDictionary(item => item.Key, x => x.Value);
        }

        public static Note[] ParseNotesFromChartSection(KeyValuePair<string, string[]>[] section)
        {
            return section
                .Where(item => item.Value.Length == 3 && item.Value.First() == TypeCode.NoteMarker).Select(
                    item => new Note
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
                .Where(item => item.Value.First() == TypeCode.EventMarker)
                .Select(
                    item => new KeyValuePair<int, string>(int.Parse(item.Key),
                        JSON_VALUE_PATTERN.Matches(item.Value.Skip(1).First()).Select(part => part.Value.Trim('"'))
                            .First()))
                .Where(item => item.Value.StartsWith("lyric"))
                .ToDictionary(item => item.Key, x => x.Value);
        }

    }

}
