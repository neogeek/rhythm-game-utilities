using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using RhythmGameUtilities;
using UnityEngine;
using UnityEngine.Networking;

public class RenderSong : MonoBehaviour
{

    [SerializeField]
    private string _songPath = "Samples/Rhythm Game Utilities/1.0.0/Sample Song/StreamingAssets/Songs/Demo 1";

    [SerializeField]
    private Mesh _mesh;

    [SerializeField]
    private Material _material;

    [SerializeField]
    private Material[] _materials;

    [SerializeField]
    private AudioSource _audioSource;

    [SerializeField]
    private float _scale = 2;

    [SerializeField]
    private float _distance = 50;

    private Song _song;

    private readonly Vector3 _noteScale = new(0.5f, 0.25f, 0.5f);

    private readonly Vector3 _noteScaleFlat = new(0.5f, 0.05f, 0.5f);

    private readonly Vector3 _beatBarScale = new(5, 0.03f, 0.03f);

    private Dictionary<int, List<Note>> _notesGroupedByHandPosition;

    private async void Start()
    {
        _song = Song.FromChartFile(
            await LoadTextFileFromPath(
                $"file://{Path.Join(Application.dataPath, _songPath, "notes.chart")}"));

        _audioSource.clip = await LoadAudioFileFromPath(
            $"file://{Path.Join(Application.dataPath, _songPath, "song.ogg")}");

        var lastTick = Utilities.ConvertSecondsToTicks(_audioSource.clip.length, _song.Resolution, _song.BPM);

        _song.BPM.TryAdd(Utilities.RoundUpToTheNearestMultiplier(lastTick, _song.Resolution), _song.BPM.Last().Value);

        _notesGroupedByHandPosition = _song.Difficulties[Difficulty.Expert]
            .Where(note => note.HandPosition < 5)
            .GroupBy(note => note.HandPosition)
            .ToDictionary(group => group.Key, group => group.ToList());

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
        if (_song == null || _notesGroupedByHandPosition == null)
        {
            return;
        }

        var tickOffset = Utilities.ConvertSecondsToTicks(_audioSource.time, _song.Resolution, _song.BPM);

        for (var x = 0; x < _notesGroupedByHandPosition.Count; x += 1)
        {
            if (!_notesGroupedByHandPosition.ContainsKey(x))
            {
                continue;
            }

            var noteMatrix = new List<Matrix4x4>
            {
                Matrix4x4.TRS(new Vector3(x + 0.5f, 0, 0), Quaternion.identity, _noteScaleFlat)
            };

            foreach (var note in _notesGroupedByHandPosition[x])
            {
                var position = Utilities.ConvertTickToPosition(note.Position - tickOffset, _song.Resolution) * _scale;

                if (position > _distance)
                {
                    break;
                }

                if (position < 0)
                {
                    continue;
                }

                noteMatrix.Add(Matrix4x4.TRS(new Vector3(note.HandPosition + 0.5f, 0, position),
                    Quaternion.identity, _noteScale));
            }

            Graphics.DrawMeshInstanced(_mesh, 0, _materials[x], noteMatrix);
        }

        var beatBarMatrix = new List<Matrix4x4>();

        foreach (var beatBar in _song.BeatBars)
        {
            var position = Utilities.ConvertTickToPosition(beatBar.Position - tickOffset, _song.Resolution) * _scale;

            if (position > _distance)
            {
                break;
            }

            if (position < 0)
            {
                continue;
            }

            beatBarMatrix.Add(Matrix4x4.TRS(new Vector3(2.5f, 0, position), Quaternion.identity, _beatBarScale));
        }

        Graphics.DrawMeshInstanced(_mesh, 0, _material, beatBarMatrix);
    }

}
