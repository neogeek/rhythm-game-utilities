using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

namespace RhythmGameUtilities
{

    public static class Parsers
    {

        private static readonly Regex CHART_PATTERN =
            new(@"\[(?<name>[a-z]+)\]\r?\n\{(?<data>[^\}]+)\}", RegexOptions.Multiline | RegexOptions.IgnoreCase);

        private static readonly Regex JSON_VALUE_PATTERN = new(@"(""[^""]+""|\S+)");

        public static Dictionary<string, KeyValuePair<string, string[]>[]> ParseSectionsFromChart(
            string contents)
        {
            var sections =
                CHART_PATTERN.Matches(contents).Select(match => match.Groups)
                    .Select(group =>
                    {
                        var name = group["name"].Value.Trim();
                        var data = group["data"].Value.Trim();

                        var lines = string.IsNullOrWhiteSpace(data)
                            ? Array.Empty<string>()
                            : Regex.Split(data, "\r?\n");

                        var linesTemp = lines.Select(line =>
                        {
                            var parts = line.Trim().Split('=').Select(part => part.Trim());

                            return new KeyValuePair<string, string[]>(parts.First(), JSON_VALUE_PATTERN
                                .Matches(parts.Skip(1).First()).Select(part => part.Value.Trim('"'))
                                .ToArray());
                        }).ToArray();

                        return new KeyValuePair<string, KeyValuePair<string, string[]>[]>(name, linesTemp);
                    }).ToDictionary(section => section.Key, section => section.Value);

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
