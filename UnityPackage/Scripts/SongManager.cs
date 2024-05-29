using System;
using System.Collections.Generic;
using System.Linq;

namespace RhythmGameUtilities
{

    public class SongManager
    {

        public Stats stats { get; protected set; }

        public Song song { get; protected set; }

        protected readonly List<Note> _remainingNotes = new();

        protected int _tick;

        public SongManager(Song song, Difficulty difficulty, float comboStep = Stats.DefaultComboStep)
        {
            this.song = song;

            stats = new Stats { difficulty = difficulty, comboStep = comboStep };

            _remainingNotes = GetAllNotes(difficulty).Where(note => note.HandPosition < 5).ToList();
        }

        public Note[] GetAllNotes(Difficulty difficulty)
        {
            if (song.Difficulties?[difficulty] == null)
            {
                throw new InvalidOperationException($"{difficulty} difficulty not found in song!");
            }

            if (!song.Difficulties.TryGetValue(difficulty, out var notes))
            {
                throw new InvalidOperationException($"No notes found for the {difficulty} difficulty!");
            }

            return notes;
        }

        public List<Note> GetRemainingNotes()
        {
            return _remainingNotes.ToList();
        }

        public List<Note> GetActiveNotes(float tickBuffer)
        {
            var activeNotes = GetRemainingNotes().Where(note =>
                _tick > note.Position - tickBuffer / 2 && _tick < note.Position + tickBuffer / 2).ToList();

            return activeNotes;
        }

        protected void ClearMissedNotes()
        {
            var notesToClear = GetRemainingNotes().Where(note => note.Position + song.BaseBPM / 2 < _tick);

            foreach (var note in notesToClear)
            {
                ClearMissedNote(note);
            }
        }

        protected virtual void ClearMissedNote(Note note)
        {
            stats.AddJudgment(JudgmentType.MISS);
            stats.ClearCombo();
        }

        protected virtual void HitNoteHandler(Note note, float accuracy, JudgmentType judgmentType)
        {
            Console.WriteLine($"Hit note with {accuracy} accuracy and a hit note type of {judgmentType}!");
        }

        protected virtual void MissNoteHandler(Note note)
        {
            Console.WriteLine("Missed note!");
        }

        protected virtual JudgmentType CalculateJudgmentTypeFromAccuracy(float accuracy)
        {
            return accuracy switch
            {
                > 0.8f => JudgmentType.PERFECT,
                > 0.6f => JudgmentType.NICE,
                > 0.3f => JudgmentType.GOOD,
                > 0 => JudgmentType.OK,
                _ => JudgmentType.MISS
            };
        }

        protected virtual int CalculateScoreForHitNoteType(JudgmentType judgmentType)
        {
            return judgmentType switch
            {
                JudgmentType.PERFECT => 1000,
                JudgmentType.NICE => 500,
                JudgmentType.GOOD => 200,
                JudgmentType.OK => 100,
                _ => 0
            };
        }

        public virtual void Tick(float time)
        {
            _tick = Utilities.ConvertSecondsToTicks(time, song.Resolution, song.BaseBPM);
        }

        public virtual void Cleanup()
        {
            ClearMissedNotes();
        }

    }

}
