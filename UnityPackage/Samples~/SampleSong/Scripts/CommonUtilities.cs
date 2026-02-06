using System;
using System.IO;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.Networking;

namespace RhythmGameUtilities
{

    public static class CommonUtilities
    {

        private static string GetAbsoluteUrl(string path)
        {
            if (Application.platform == RuntimePlatform.WebGLPlayer)
            {
                return path;
            }

            return path.Contains("://") ? path : $"file://{path}";
        }

        public static async Task<byte[]> LoadDataFileFromPath(string path)
        {
            using var request = UnityWebRequest.Get(GetAbsoluteUrl(path));

            var operation = request.SendWebRequest();

            while (!operation.isDone) await Task.Yield();

            return request.result == UnityWebRequest.Result.Success
                ? request.downloadHandler.data
                : throw new Exception($"Failed to load data: {request.error}");
        }

        public static async Task<string> LoadTextFileFromPath(string path)
        {
            using var request = UnityWebRequest.Get(GetAbsoluteUrl(path));

            var operation = request.SendWebRequest();

            while (!operation.isDone) await Task.Yield();

            return request.result == UnityWebRequest.Result.Success
                ? request.downloadHandler.text
                : throw new Exception($"Failed to load text: {request.error}");
        }

        public static async Task<AudioClip> LoadAudioFileFromPath(string path)
        {
            using var request =
                UnityWebRequestMultimedia.GetAudioClip(GetAbsoluteUrl(path), GetAudioTypeFromPath(path));

            var operation = request.SendWebRequest();

            while (!operation.isDone) await Task.Yield();

            return request.result == UnityWebRequest.Result.Success
                ? DownloadHandlerAudioClip.GetContent(request)
                : throw new Exception($"Failed to load audio: {request.error}");
        }

        public static AudioType GetAudioTypeFromPath(string path)
        {
            var extension = Path.GetExtension(path);

            return extension switch { ".wav" => AudioType.WAV, ".mp3" => AudioType.MPEG, var _ => AudioType.OGGVORBIS };
        }

    }

}
