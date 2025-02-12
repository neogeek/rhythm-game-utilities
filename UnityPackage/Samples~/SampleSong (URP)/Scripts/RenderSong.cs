using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Web;
using RhythmGameUtilities;
using UnityEngine;
using UnityEngine.Networking;

public class RenderSong : MonoBehaviour
{

    [SerializeField]
    private string _songPath = "Samples/Rhythm Game Utilities/1.0.0/Sample Song (URP)/StreamingAssets/Songs/Demo 1";

    [SerializeField]
    private Mesh _mesh;

    [SerializeField]
    private Material _trackMaterial;

    [SerializeField]
    private Material _beatBarMaterial;

    [SerializeField]
    private Material _beatBarHalfMaterial;

    [SerializeField]
    private Material _beatBarQuarterMaterial;

    [SerializeField]
    private Material[] _materials;

    [SerializeField]
    private AudioSource _audioSource;

    [SerializeField]
    private float _scale = 2;

    [SerializeField]
    private float _distance = 50;

    private readonly Vector3 _noteScale = new(0.5f, 0.25f, 0.35f);

    private readonly Vector3 _noteScaleFlat = new(0.5f, 0.05f, 0.35f);

    private readonly Vector3 _beatBarScaleFull = new(5, 0.03f, 0.1f);

    private readonly Vector3 _beatBarScaleHalf = new(5, 0.03f, 0.05f);

    private readonly Vector3 _beatBarScaleQuarter = new(5, 0.03f, 0.01f);

    public int resolution { get; set; } = 192;

    public Tempo[] bpmChanges { get; set; }

    public TimeSignature[] timeSignatureChanges { get; set; }

    public Dictionary<Difficulty, Note[]> difficulties { get; set; }

    public Dictionary<int, List<Note>> notesGroupedByHandPosition { get; set; }

    public BeatBar[] beatBars { get; set; }

    private async void Start()
    {
        var path = Path.Join(Application.dataPath, _songPath, "notes.chart");

        var contents = await LoadTextFileFromPath($"file://{HttpUtility.UrlPathEncode(path)}");

        var sections = Parsers.ParseSectionsFromChart(contents);

        var metadata = Parsers.ParseMetaDataFromChartSection(sections
            .First(section => section.Key == NamedSection.Song)
            .Value);

        _audioSource.clip =
            await LoadAudioFileFromPath(
                $"file://{HttpUtility.UrlPathEncode(Path.Join(Path.GetDirectoryName(path), metadata["MusicStream"]))}");

        resolution = int.Parse(metadata["Resolution"]);

        bpmChanges = Parsers.ParseBpmFromChartSection(sections.First(section => section.Key == NamedSection.SyncTrack)
            .Value);

        timeSignatureChanges = Parsers.ParseTimeSignaturesFromChartSection(sections[NamedSection.SyncTrack]);

        var lastTick =
            Utilities.ConvertSecondsToTicks(_audioSource.clip.length, resolution, bpmChanges, timeSignatureChanges);

        bpmChanges = bpmChanges.Concat(new Tempo[]
            {
                new()
                {
                    Position = Utilities.RoundUpToTheNearestMultiplier(lastTick, resolution),
                    BPM = bpmChanges.Last().BPM
                }
            })
            .ToArray();

        difficulties = Enum.GetValues(typeof(Difficulty))
            .Cast<Difficulty>()
            .Where(difficulty => sections.ToDictionary(item => item.Key, x => x.Value)
                .ContainsKey($"{difficulty}Single"))
            .ToDictionary(difficulty => difficulty,
                difficulty => Parsers.ParseNotesFromChartSection(sections[$"{difficulty}Single"]));

        notesGroupedByHandPosition = difficulties[Difficulty.Expert]
            .Where(note => note.HandPosition < 5)
            .GroupBy(note => note.HandPosition)
            .ToDictionary(group => group.Key, group => group.ToList());

        beatBars = Utilities.CalculateBeatBars(bpmChanges, includeHalfNotes : true);

        _audioSource.Play();
    }

    public static async Task<string> LoadTextFileFromPath(string path)
    {
        using var request = UnityWebRequest.Get(path);

        request.downloadHandler = new DownloadHandlerBuffer();

        request.SendWebRequest();

        while (!request.isDone)
        {
            await Task.Yield();
        }

        if (request.result == UnityWebRequest.Result.Success)
        {
            return request.downloadHandler.text;
        }

        throw new FileNotFoundException(request.result.ToString());
    }

    public static async Task<AudioClip> LoadAudioFileFromPath(string path, AudioType audioType = AudioType.OGGVORBIS)
    {
        using var request =
            UnityWebRequestMultimedia.GetAudioClip(path, audioType);

        request.SendWebRequest();

        while (!request.isDone)
        {
            await Task.Yield();
        }

        if (request.result == UnityWebRequest.Result.Success)
        {
            return DownloadHandlerAudioClip.GetContent(request);
        }

        throw new FileNotFoundException(request.result.ToString());
    }

    private void Update()
    {
        RenderTrack();

        if (notesGroupedByHandPosition == null)
        {
            return;
        }

        var tickOffset =
            Utilities.ConvertSecondsToTicks(_audioSource.time, resolution, bpmChanges, timeSignatureChanges);

        RenderHitNotes(notesGroupedByHandPosition);

        RenderNotes(notesGroupedByHandPosition, resolution, tickOffset);
        RenderBeatBars(beatBars, resolution, tickOffset);
    }

    private void RenderTrack()
    {
        Graphics.DrawMesh(_mesh,
            Matrix4x4.TRS(new Vector3(2.5f, -0.05f, _distance / 2), Quaternion.identity,
                new Vector3(5f, 0.1f, _distance)),
            _trackMaterial, 0);
    }

    private void RenderHitNotes(Dictionary<int, List<Note>> notesGroupedByHandPosition)
    {
        for (var x = 0; x < notesGroupedByHandPosition.Count; x += 1)
        {
            Graphics.DrawMesh(_mesh,
                Matrix4x4.TRS(new Vector3(x + 0.5f, 0, 0), Quaternion.identity, _noteScaleFlat),
                _materials[x], 0);
        }
    }

    private void RenderNotes(Dictionary<int, List<Note>> notesGroupedByHandPosition, int resolution, int tickOffset)
    {
        for (var x = 0; x < notesGroupedByHandPosition.Count; x += 1)
        {
            if (!notesGroupedByHandPosition.ContainsKey(x))
            {
                continue;
            }

            var noteMatrix = new List<Matrix4x4>
            {
                Matrix4x4.TRS(new Vector3(x + 0.5f, 0, 0), Quaternion.identity, _noteScaleFlat)
            };

            for (var y = 0; y < notesGroupedByHandPosition[x].Count; y += 1)
            {
                var position = Utilities.ConvertTickToPosition(notesGroupedByHandPosition[x][y].Position - tickOffset,
                    resolution) * _scale;

                if (position > _distance)
                {
                    break;
                }

                if (position < 0)
                {
                    continue;
                }

                noteMatrix.Add(Matrix4x4.TRS(
                    new Vector3(notesGroupedByHandPosition[x][y].HandPosition + 0.5f, 0, position),
                    Quaternion.identity, _noteScale));
            }

            Graphics.DrawMeshInstanced(_mesh, 0, _materials[x], noteMatrix);
        }
    }

    private void RenderBeatBars(BeatBar[] beatBars, int resolution, int tickOffset)
    {
        var beatBarMatrix = new List<Matrix4x4>();
        var beatBarHalfMatrix = new List<Matrix4x4>();
        var beatBarQuarterMatrix = new List<Matrix4x4>();

        for (var x = 0; x < beatBars.Length; x += 1)
        {
            var position = Utilities.ConvertTickToPosition(beatBars[x].Position - tickOffset, resolution) *
                           _scale;

            if (position > _distance)
            {
                break;
            }

            if (position < 0)
            {
                continue;
            }

            if (x % 8 == 0)
            {
                beatBarMatrix.Add(Matrix4x4.TRS(new Vector3(2.5f, 0, position), Quaternion.identity,
                    _beatBarScaleFull));
            }
            else if (x % 2 == 0)
            {
                beatBarHalfMatrix.Add(Matrix4x4.TRS(new Vector3(2.5f, 0, position), Quaternion.identity,
                    _beatBarScaleHalf));
            }
            else
            {
                beatBarQuarterMatrix.Add(Matrix4x4.TRS(new Vector3(2.5f, 0, position), Quaternion.identity,
                    _beatBarScaleQuarter));
            }
        }

        Graphics.DrawMeshInstanced(_mesh, 0, _beatBarMaterial, beatBarMatrix);
        Graphics.DrawMeshInstanced(_mesh, 0, _beatBarHalfMaterial, beatBarHalfMatrix);
        Graphics.DrawMeshInstanced(_mesh, 0, _beatBarQuarterMaterial, beatBarQuarterMatrix);
    }

}
