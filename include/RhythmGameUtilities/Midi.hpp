#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Structs/Note.hpp"

namespace RhythmGameUtilities
{

template <typename T> T ByteSwap(T value, int length = 8)
{
    return (value >> length) | (value << length);
}

template <typename T> T ReadChunk(std::ifstream &file, int length = sizeof(T))
{
    T chunk{};
    file.read(reinterpret_cast<char *>(&chunk), length);
    return chunk;
}

std::string ReadString(std::ifstream &file, int length)
{
    std::string chunk(length, '\0');
    file.read(&chunk[0], length);
    return file.gcount() == length ? chunk : "";
}

uint32_t ReadVarLen(std::ifstream &file)
{
    uint32_t value = 0;
    uint8_t byte = 0;
    do
    {
        byte = ReadChunk<uint8_t>(file);
        value = (value << 7) | (byte & 0x7F);
    } while (byte & 0x80);
    return value;
}

auto STATUS_NOTE_EVENT = 0x90;
auto STATUS_META_EVENT = 0xFF;
auto TYPE_END_OF_TRACK = 0x2F;

std::vector<Note> ReadMidiFile(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open MIDI file");
    }

    if (ReadString(file, 4) != "MThd")
    {
        throw std::runtime_error("Invalid MIDI file header");
    }

    auto headerLength = ByteSwap(ReadChunk<uint32_t>(file));
    auto format = ByteSwap(ReadChunk<uint16_t>(file));
    auto tracks = ByteSwap(ReadChunk<uint16_t>(file));
    auto resolution = ByteSwap(ReadChunk<uint16_t>(file));

    std::vector<Note> notes;

    for (int t = 0; t < tracks; t += 1)
    {
        if (ReadString(file, 4) != "MTrk")
        {
            throw std::runtime_error("Invalid track header");
        }

        auto trackLength = ByteSwap(ReadChunk<uint32_t>(file));

        uint32_t absoluteTick = 0;

        while (true)
        {
            absoluteTick += ReadVarLen(file);

            auto status = ReadChunk<uint8_t>(file);

            if ((status & 0xF0) == STATUS_NOTE_EVENT)
            {
                Note note{.Position = static_cast<int>(absoluteTick),
                          .HandPosition = ReadChunk<uint8_t>(file)};

                auto velocity = ReadChunk<uint8_t>(file);

                notes.push_back(note);
            }
            else if (status == STATUS_META_EVENT)
            {
                auto type = ReadChunk<uint8_t>(file);

                auto length = ReadVarLen(file);

                file.seekg(length, std::ios::cur);

                if (type == TYPE_END_OF_TRACK)
                {
                    break;
                }
            }
            else if ((status & 0xF0) == 0xC0 || (status & 0xF0) == 0xD0)
            {
                file.seekg(1, std::ios::cur);
            }
            else
            {
                file.seekg(2, std::ios::cur);
            }
        }
    }

    return notes;
}

} // namespace RhythmGameUtilities
