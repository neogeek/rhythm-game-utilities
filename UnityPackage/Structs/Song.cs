using System;
using System.Collections.Generic;
using System.Linq;
using Newtonsoft.Json;

namespace RhythmGameUtilities
{

    public struct Song
    {

        /// <summary>
        /// Title of the song.
        /// </summary>
        [JsonProperty]
        public string Name { get; internal set; }

        /// <summary>
        /// Artist(s) or band(s) behind the song.
        /// </summary>
        [JsonProperty]
        public string Artist { get; internal set; }

        /// <summary>
        /// Title of the album the song is featured in.
        /// </summary>
        [JsonProperty]
        public string Album { get; internal set; }

        /// <summary>
        /// Genre of the song.
        /// </summary>
        [JsonProperty]
        public string Genre { get; internal set; }

        /// <summary>
        /// Year of the song’s release.<br/>Typically preceded by a comma and space, for example `, 2002`, to make importing into GHTCP quicker.
        /// </summary>
        [JsonProperty]
        public string Year { get; internal set; }

        /// <summary>
        /// Community member who charted the song.
        /// </summary>
        [JsonProperty]
        public string Charter { get; internal set; }

        /// <summary>
        /// (Required) Number of positional ticks between each 1/4th note in the chart.
        /// </summary>
        [JsonProperty]
        public int Resolution { get; internal set; }

        /// <summary>
        /// Estimated difficulty of the song.
        /// </summary>
        [JsonProperty]
        public int Difficulty { get; internal set; }

        /// <summary>
        /// Start time of the audio, in seconds.<br/>A higher value makes the audio start sooner.
        /// </summary>
        [JsonProperty]
        public double Offset { get; internal set; }

        /// <summary>
        /// Time of the song, in seconds, where the song preview should start.
        /// </summary>
        [JsonProperty]
        public double PreviewStart { get; internal set; }

        /// <summary>
        /// Time of the song, in seconds, where the song preview should end.
        /// </summary>
        [JsonProperty]
        public double PreviewEnd { get; internal set; }

        /// <summary>
        /// The main audio stream.<br/>When other audio stems are present, this is background audio not in the other tracks and/or instruments not charted.
        /// </summary>
        [JsonProperty]
        public string MusicStream { get; internal set; }

        [JsonProperty]
        public Dictionary<int, string> Lyrics { get; internal set; }

        [JsonProperty]
        public Dictionary<Difficulty, Note[]> Difficulties { get; internal set; }

        [JsonProperty]
        public Dictionary<int, int> BPM { get; internal set; }

        [JsonProperty]
        public int BaseBPM { get; internal set; }

        public static Song FromChartFile(string input)
        {

            var sections = Parsers.ParseSectionsFromChart(input);

            var data = sections[NamedSection.Song]
                .ToDictionary(item => item.Key, x => x.Value);

            var bpm = Parsers.ParseBpmFromChartChartSection(sections[NamedSection.SyncTrack]);

            var song = new Song
            {
                Name = data.TryGetValue("Name", out var nameValue) ? nameValue[0] : null,
                Artist = data.TryGetValue("Artist", out var artistValue) ? artistValue[0] : null,
                Album = data.TryGetValue("Album", out var albumValue) ? albumValue[0] : null,
                Genre = data.TryGetValue("Genre", out var genreValue) ? genreValue[0] : null,
                Year = data.TryGetValue("Year", out var yearValue) ? yearValue[0] : null,
                Charter = data.TryGetValue("Charter", out var charterValue) ? charterValue[0] : null,
                Resolution = int.TryParse(data["Resolution"][0], out var resolutionValue) ? resolutionValue : 0,
                Difficulty = int.TryParse(data["Difficulty"][0], out var difficultyValue) ? difficultyValue : 0,
                Offset =
                    double.TryParse(data["Offset"][0], out var offsetValue) ? offsetValue : 0,
                PreviewStart =
                    double.TryParse(data["PreviewStart"][0], out var previewStartValue) ? previewStartValue : 0,
                PreviewEnd = double.TryParse(data["PreviewEnd"][0], out var previewEndValue) ? previewEndValue : 0,
                MusicStream =
                    data.TryGetValue("MusicStream", out var musicStreamValue) ? musicStreamValue[0] : null,
                Lyrics = Parsers.ParseLyricsFromChartSection(sections[NamedSection.SyncTrack]),
                Difficulties = Enum.GetValues(typeof(Difficulty))
                    .Cast<Difficulty>()
                    .Where(difficulty => sections.ToDictionary(item => item.Key, x => x.Value)
                        .ContainsKey($"{difficulty}Single"))
                    .ToDictionary(difficulty => difficulty,
                        difficulty => Parsers.ParseNotesFromChartSection(sections[$"{difficulty}Single"])),
                BPM = bpm,
                BaseBPM = bpm.First().Value / 1000
            };

            return song;
        }

        public string ToJSON()
        {
            return JsonConvert.SerializeObject(this);
        }

        public static Song FromJSON(string input)
        {
            return JsonConvert.DeserializeObject<Song>(input);
        }

        public int GetCurrentBPM(Note note)
        {
            return BPM.Last(item => item.Key <= note.Position).Value / 1000;
        }

    }

}
