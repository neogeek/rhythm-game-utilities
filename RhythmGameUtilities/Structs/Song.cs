using System;
using System.Collections.Generic;
using System.Linq;

namespace RhythmGameUtilities
{

    public struct Song
    {

        /// <summary>
        /// Title of the song.
        /// </summary>
        public string Name;

        /// <summary>
        /// Artist(s) or band(s) behind the song.
        /// </summary>
        public string Artist;

        /// <summary>
        /// Title of the album the song is featured in.
        /// </summary>
        public string Album;

        /// <summary>
        /// Genre of the song.
        /// </summary>
        public string Genre;

        /// <summary>
        /// Year of the song’s release.<br>Typically preceded by a comma and space, for example `, 2002`, to make importing into GHTCP quicker.
        /// </summary>
        public string Year;

        /// <summary>
        /// Community member who charted the song.
        /// </summary>
        public string Charter;

        /// <summary>
        /// (Required) Number of positional ticks between each 1/4th note in the chart.
        /// </summary>
        public int Resolution;

        /// <summary>
        /// Estimated difficulty of the song.
        /// </summary>
        public int Difficulty;

        /// <summary>
        /// Start time of the audio, in seconds.<br>A higher value makes the audio start sooner.
        /// </summary>
        public float Offset;

        /// <summary>
        /// Time of the song, in seconds, where the song preview should start.
        /// </summary>
        public float PreviewStart;

        /// <summary>
        /// Time of the song, in seconds, where the song preview should end.
        /// </summary>
        public float PreviewEnd;

        /// <summary>
        /// The main audio stream.<br>When other audio stems are present, this is background audio not in the other tracks and/or instruments not charted.
        /// </summary>
        public string MusicStream;

        public Dictionary<int, string> Lyrics;

        public Dictionary<Difficulty, Note[]> Difficulties;

        public Dictionary<int, int> BPM;

        public Song(string contents)
        {
            var sections = Parsers.ParseSectionsFromChart(contents);

            var song = sections[NamedSection.Song]
                .ToDictionary(item => item.Key, x => x.Value);

            Name = song.TryGetValue("Name", out var nameValue) ? nameValue[0] : null;
            Artist = song.TryGetValue("Artist", out var artistValue) ? artistValue[0] : null;
            Album = song.TryGetValue("Album", out var albumValue) ? albumValue[0] : null;
            Genre = song.TryGetValue("Genre", out var genreValue) ? genreValue[0] : null;
            Year = song.TryGetValue("Year", out var yearValue) ? yearValue[0] : null;
            Charter = song.TryGetValue("Charter", out var charterValue) ? charterValue[0] : null;

            int.TryParse(song["Resolution"][0], out Resolution);
            int.TryParse(song["Difficulty"][0], out Difficulty);

            float.TryParse(song["Offset"][0], out Offset);
            float.TryParse(song["PreviewStart"][0], out PreviewStart);

            float.TryParse(song["PreviewEnd"][0], out PreviewEnd);

            MusicStream = song.TryGetValue("MusicStream", out var musicStreamValue) ? musicStreamValue[0] : null;

            Lyrics = Parsers.ParseLyricsFromChartSection(sections[NamedSection.SyncTrack]);

            Difficulties = new Dictionary<Difficulty, Note[]>();

            Difficulties = new Dictionary<Difficulty, Note[]>();

            foreach (var difficulty in Enum.GetValues(typeof(Difficulty)).Cast<Difficulty>()
                         .Where(difficulty =>
                             sections.ToDictionary(item => item.Key, x => x.Value).ContainsKey($"{difficulty}Single")))
            {
                Difficulties.Add(difficulty, Parsers.ParseNotesFromChartSection(sections[$"{difficulty}Single"]));
            }

            BPM = Parsers.ParseBpmFromChartChartSection(sections[NamedSection.SyncTrack]);

        }

    }

}
