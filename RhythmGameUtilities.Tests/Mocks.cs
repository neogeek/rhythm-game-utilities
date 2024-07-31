using System.IO;

namespace RhythmGameUtilities.Tests
{

    public static class Mocks
    {

        public static string ROOT_DIR => Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName;

        public static string SONG_CHART_PATH => Path.Combine(ROOT_DIR, "Mocks/song.chart");

        public static string SONG_CHART => File.ReadAllText(SONG_CHART_PATH);

        public static string SONG_JSON_PATH => Path.Combine(ROOT_DIR, "Mocks/song.json");

        public static string SONG_JSON => File.ReadAllText(SONG_JSON_PATH);

    }

}
