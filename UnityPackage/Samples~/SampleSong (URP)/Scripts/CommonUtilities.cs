using System.IO;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.Networking;

namespace RhythmGameUtilities
{

    public static class CommonUtilities
    {

        public static async Task<string> LoadTextFileFromPath(string path)
        {
            using var request = UnityWebRequest.Get(path);

            request.downloadHandler = new DownloadHandlerBuffer();

            await request.SendWebRequest();

            if (request.result == UnityWebRequest.Result.Success)
            {
                return request.downloadHandler.text;
            }

            throw new FileNotFoundException(request.result.ToString());
        }

        public static async Task<AudioClip> LoadAudioFileFromPath(string path,
            AudioType audioType = AudioType.OGGVORBIS)
        {
            using var request =
                UnityWebRequestMultimedia.GetAudioClip(path, audioType);

            await request.SendWebRequest();

            if (request.result == UnityWebRequest.Result.Success)
            {
                return DownloadHandlerAudioClip.GetContent(request);
            }

            throw new FileNotFoundException(request.result.ToString());
        }

    }

}
