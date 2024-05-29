using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using Newtonsoft.Json;

namespace RhythmGameUtilities
{

    public class Stats
    {

        public const float DefaultComboStep = 0.25f;

        public Difficulty difficulty { get; internal set; }

        public float comboStep { get; internal set; } = DefaultComboStep;

        public int score { get; private set; }

        public float combo { get; private set; } = 1;

        public int comboMultiplier => (int)Math.Floor(combo);

        private readonly Dictionary<JudgmentType, int> _judgmentTypeCount = new();

        public ReadOnlyDictionary<JudgmentType, int> judgmentTypeCount => new(_judgmentTypeCount);

        public void AddToScore(int points)
        {
            combo += comboStep;
            score += points * comboMultiplier;
        }

        public void ClearCombo()
        {
            combo = 1;
        }

        public void AddJudgment(JudgmentType judgmentType, int count = 1)
        {
            if (!_judgmentTypeCount.TryAdd(judgmentType, count))
            {
                _judgmentTypeCount[judgmentType] += count;
            }
        }

        public string ToJSON()
        {
            return JsonConvert.SerializeObject(this);
        }

        public static Song FromJSON(string input)
        {
            return JsonConvert.DeserializeObject<Song>(input);
        }

        public override string ToString()
        {
            var output = new StringBuilder();

            foreach (var judgment in Enum.GetValues(typeof(JudgmentType)))
            {
                if (_judgmentTypeCount.TryGetValue((JudgmentType)judgment, out var count))
                {
                    output.AppendLine($"{(JudgmentType)judgment}: {count}");
                }
            }

            return output.ToString().Trim();
        }

    }

}
