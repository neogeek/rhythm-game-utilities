#pragma once

#include <iostream>

#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Structs/Note.hpp"

namespace RhythmGameUtilities
{

template <typename T> inline auto ByteSwap(T value, int length = 8) -> T
{
    return (value >> length) | (value << length);
}

template <typename T>
inline auto ReadChunk(std::istringstream &stream, int length = sizeof(T)) -> T
{
    T chunk{};
    stream.read(reinterpret_cast<char *>(&chunk), length);
    return chunk;
}

inline auto ReadString(std::istringstream &stream, int length) -> std::string
{
    std::string chunk(length, '\0');
    stream.read(chunk.data(), length);
    return stream.gcount() == length ? chunk : "";
}

inline auto ReadVarLen(std::istringstream &stream) -> uint32_t
{
    uint32_t value = 0;
    uint8_t byte = 0;
    do
    {
        byte = ReadChunk<uint8_t>(stream);
        value = (value << 7) | (byte & 0x7F);
    } while ((byte & 0x80) > 0);
    return value;
}

const auto TYPE_END_OF_TRACK = 0x2F;

const auto SYSTEM_COMMAND = 0xF0;
const auto NOTE_OFF_COMMAND = 0x80;
const auto NOTE_ON_COMMAND = 0x90;
const auto CONTROL_CHANGE_COMMAND = 0xB0;
const auto PROGRAM_CHANGE_COMMAND = 0xC0;
const auto CHANNEL_PRESSURE_COMMAND = 0xD0;

inline auto ReadMidiData(const std::vector<uint8_t> &data) -> std::vector<Note>
{
    std::istringstream stream(std::string(data.begin(), data.end()),
                              std::ios::binary);

    if (ReadString(stream, 4) != "MThd")
    {
        throw std::runtime_error("Invalid MIDI file header");
    }

    auto headerLength = ByteSwap(ReadChunk<uint32_t>(stream));
    auto format = ByteSwap(ReadChunk<uint16_t>(stream));
    auto tracks = ByteSwap(ReadChunk<uint16_t>(stream));
    auto resolution = ByteSwap(ReadChunk<uint16_t>(stream));

    std::vector<Note> notes;

    for (int t = 0; t < tracks; t += 1)
    {
        if (ReadString(stream, 4) != "MTrk")
        {
            throw std::runtime_error("Invalid track header");
        }

        auto trackLength = ByteSwap(ReadChunk<uint32_t>(stream));

        uint32_t absoluteTick = 0;

        while (true)
        {
            absoluteTick += ReadVarLen(stream);

            auto status = ReadChunk<uint8_t>(stream);

            if ((status & SYSTEM_COMMAND) == NOTE_ON_COMMAND)
            {
                Note note{.Position = static_cast<int>(absoluteTick),
                          .HandPosition = ReadChunk<uint8_t>(stream)};

                auto velocity = ReadChunk<uint8_t>(stream);

                notes.push_back(note);
            }
            else if ((status & SYSTEM_COMMAND) == SYSTEM_COMMAND)
            {
                auto type = ReadChunk<uint8_t>(stream);

                auto length = ReadVarLen(stream);

                stream.seekg(length, std::ios::cur);

                if (type == TYPE_END_OF_TRACK)
                {
                    break;
                }
            }
            else if ((status & SYSTEM_COMMAND) == PROGRAM_CHANGE_COMMAND ||
                     (status & SYSTEM_COMMAND) == CHANNEL_PRESSURE_COMMAND)
            {
                stream.seekg(1, std::ios::cur);
            }
            else
            {
                stream.seekg(2, std::ios::cur);
            }
        }
    }

    return notes;
}

auto ReadMidiFile(const std::string &path) -> std::vector<Note>
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open MIDI file");
    }

    auto fileSize = file.tellg();

    std::vector<uint8_t> buffer(static_cast<size_t>(fileSize));

    file.seekg(0, std::ios::beg);

    file.read(reinterpret_cast<char *>(buffer.data()), fileSize);

    return ReadMidiData(buffer);
}

} // namespace RhythmGameUtilities
