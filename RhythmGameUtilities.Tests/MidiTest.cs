using System.IO;
using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class MidiTest
    {

        [Test]
        public void TestReadResolutionFromMidiData()
        {
            var directory = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            var path = Path.GetFullPath(Path.Combine(directory, "../../../Mocks/song.mid"));

            var content = File.ReadAllBytes(path);

            var resolution = Midi.ReadResolutionFromMidiData(content);

            Assert.That(resolution, Is.EqualTo(480));
        }

        [Test]
        public void TestReadTempoChangesFromMidiData()
        {
            var directory = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            var path = Path.GetFullPath(Path.Combine(directory, "../../../Mocks/song.mid"));

            var content = File.ReadAllBytes(path);

            var tempoChanges = Midi.ReadTempoChangesFromMidiData(content);

            Assert.That(tempoChanges.Length, Is.EqualTo(1));
            Assert.That(tempoChanges[0].Position, Is.EqualTo(0));
            Assert.That(tempoChanges[0].BPM, Is.EqualTo(120000));
        }

        [Test]
        public void TestReadTimeSignatureChangesFromMidiData()
        {
            var directory = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            var path = Path.GetFullPath(Path.Combine(directory, "../../../Mocks/song.mid"));

            var content = File.ReadAllBytes(path);

            var timeSignatureChanges = Midi.ReadTimeSignatureChangesFromMidiData(content);

            Assert.That(timeSignatureChanges.Length, Is.EqualTo(1));
            Assert.That(timeSignatureChanges[0].Position, Is.EqualTo(0));
            Assert.That(timeSignatureChanges[0].Numerator, Is.EqualTo(4));
            Assert.That(timeSignatureChanges[0].Denominator, Is.EqualTo(4));
        }

        [Test]
        public void TestReadNotesFromMidiData()
        {
            var directory = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            var path = Path.GetFullPath(Path.Combine(directory, "../../../Mocks/song.mid"));

            var content = File.ReadAllBytes(path);

            var notes = Midi.ReadNotesFromMidiData(content);

            Assert.That(notes.Length, Is.EqualTo(10));

            Assert.That(notes[0].Position, Is.EqualTo(0));
            Assert.That(notes[0].HandPosition, Is.EqualTo(48));

            Assert.That(notes[1].Position, Is.EqualTo(480));
            Assert.That(notes[1].HandPosition, Is.EqualTo(50));

            Assert.That(notes[2].Position, Is.EqualTo(960));
            Assert.That(notes[2].HandPosition, Is.EqualTo(52));

            Assert.That(notes[3].Position, Is.EqualTo(1440));
            Assert.That(notes[3].HandPosition, Is.EqualTo(54));

            Assert.That(notes[4].Position, Is.EqualTo(1920));
            Assert.That(notes[4].HandPosition, Is.EqualTo(56));

            Assert.That(notes[5].Position, Is.EqualTo(2400));
            Assert.That(notes[5].HandPosition, Is.EqualTo(48));

            Assert.That(notes[6].Position, Is.EqualTo(2400));
            Assert.That(notes[6].HandPosition, Is.EqualTo(50));

            Assert.That(notes[7].Position, Is.EqualTo(2400));
            Assert.That(notes[7].HandPosition, Is.EqualTo(52));

            Assert.That(notes[8].Position, Is.EqualTo(2400));
            Assert.That(notes[8].HandPosition, Is.EqualTo(54));

            Assert.That(notes[9].Position, Is.EqualTo(2400));
            Assert.That(notes[9].HandPosition, Is.EqualTo(56));
        }

    }

}
