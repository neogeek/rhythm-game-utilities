using System.Collections.Generic;
using System.IO;
using System.Web;
using UnityEngine;

namespace RhythmGameUtilities
{

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

        [SerializeField]
        private int _trackLaneCount = 5;

        private readonly Vector3 _noteScale = new(0.5f, 0.1f, 0.35f);

        private readonly Vector3 _noteScaleFlat = new(0.5f, 0.05f, 0.35f);

        private readonly Vector3 _beatBarScaleFull = new(0, 0.03f, 0.1f);

        private readonly Vector3 _beatBarScaleHalf = new(0, 0.03f, 0.05f);

        private readonly Vector3 _beatBarScaleQuarter = new(0, 0.03f, 0.01f);

        private Song _song;

        private async void Start()
        {
            var path = Path.Join(Application.dataPath, _songPath);

            var contents =
                await CommonUtilities.LoadTextFileFromPath(
                    $"file://{HttpUtility.UrlPathEncode(Path.Join(path, "notes.chart"))}");

            _song = new Song(contents);

            _audioSource.clip =
                await CommonUtilities.LoadAudioFileFromPath(
                    $"file://{HttpUtility.UrlPathEncode(Path.Join(path, _song.metaData["MusicStream"]))}");

            _song.RecalculateBeatBarsWithSongLength(_audioSource.clip.length);

            _audioSource.Play();
        }

        private void Update()
        {
            RenderTrack();
            RenderHitNotes();

            if (_song?.difficulties?[Difficulty.Easy] == null)
            {
                return;
            }

            var tickOffset =
                Utilities.ConvertSecondsToTicks(_audioSource.time, _song.resolution, _song.tempoChanges,
                    _song.timeSignatureChanges);

            RenderNotes(_song.difficulties[Difficulty.Easy], _song.resolution, tickOffset);
            RenderBeatBars(_song.beatBars, _song.resolution, tickOffset);
        }

        private void RenderTrack()
        {
            var trackWidth = _trackLaneCount * 1f;

            var trackSeparators = 2 + _trackLaneCount - 1;

            Graphics.DrawMesh(_mesh,
                Matrix4x4.TRS(new Vector3(0, -0.05f, _distance / 2), Quaternion.identity,
                    new Vector3(trackWidth, 0.1f, _distance)),
                _trackMaterial, 0);

            for (var i = 0; i < trackSeparators; i += 1)
            {
                Graphics.DrawMesh(_mesh,
                    Matrix4x4.TRS(new Vector3(-(trackWidth / 2) + 0.05f + (i * 1), -0.025f, _distance / 2),
                        Quaternion.identity,
                        new Vector3(i == 0 || i == trackSeparators - 1 ? 0.1f : 0.05f, 0.15f, _distance)),
                    _beatBarMaterial, 0);
            }
        }

        private void RenderHitNotes()
        {
            var trackWidth = _trackLaneCount * 1f;

            for (var x = 0; x < _trackLaneCount; x += 1)
            {
                Graphics.DrawMesh(_mesh,
                    Matrix4x4.TRS(new Vector3(-(trackWidth / 2) + x + 0.5f, 0.025f, 0), Quaternion.identity,
                        _noteScaleFlat),
                    _materials[x], 0);
            }
        }

        private void RenderNotes(Note[] notes, int resolution, int tickOffset)
        {
            var trackWidth = _trackLaneCount * 1f;

            var laneArray = new Dictionary<int, List<Matrix4x4>>();

            for (var x = 0; x < 5; x += 1)
            {
                laneArray.Add(x, new List<Matrix4x4>());
            }

            for (var i = 0; i < notes.Length; i += 1)
            {
                if (notes[i].HandPosition > 5) continue;

                var position = Utilities.ConvertTickToPosition(notes[i].Position - tickOffset,
                    resolution) * _scale;

                if (position > 0 && position < _distance)
                {
                    laneArray[notes[i].HandPosition].Add(Matrix4x4.TRS(
                        new Vector3(-(trackWidth / 2) + notes[i].HandPosition + 0.5f, 0.05f, position),
                        Quaternion.identity, _noteScale));
                }
            }

            for (var x = 0; x < 5; x += 1)
            {
                Graphics.DrawMeshInstanced(_mesh, 0, _materials[x], laneArray[x]);
            }
        }

        private void RenderBeatBars(BeatBar[] beatBars, int resolution, int tickOffset)
        {
            var trackWidth = _trackLaneCount * 1f;

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
                    beatBarMatrix.Add(Matrix4x4.TRS(new Vector3(0, 0.015f, position), Quaternion.identity,
                        _beatBarScaleFull + new Vector3(trackWidth, 0, 0)));
                }
                else if (x % 2 == 0)
                {
                    beatBarHalfMatrix.Add(Matrix4x4.TRS(new Vector3(0, 0.015f, position), Quaternion.identity,
                        _beatBarScaleHalf + new Vector3(trackWidth, 0, 0)));
                }
                else
                {
                    beatBarQuarterMatrix.Add(Matrix4x4.TRS(new Vector3(0, 0.015f, position), Quaternion.identity,
                        _beatBarScaleQuarter + new Vector3(trackWidth, 0, 0)));
                }
            }

            Graphics.DrawMeshInstanced(_mesh, 0, _beatBarMaterial, beatBarMatrix);
            Graphics.DrawMeshInstanced(_mesh, 0, _beatBarHalfMaterial, beatBarHalfMatrix);
            Graphics.DrawMeshInstanced(_mesh, 0, _beatBarQuarterMaterial, beatBarQuarterMatrix);
        }

    }

}
