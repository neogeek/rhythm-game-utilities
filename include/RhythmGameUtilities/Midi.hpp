#pragma once

#include <cstdint>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "Structs/Note.hpp"

namespace RhythmGameUtilities
{

inline auto ByteSwap(uint16_t value) -> uint16_t
{
    return (value >> 8) | (value << 8);
}

inline auto ByteSwap(uint32_t value) -> uint32_t
{
    return ((value >> 24) & 0xFF) | ((value >> 8) & 0xFF00) |
           ((value << 8) & 0xFF0000) | ((value << 24) & 0xFF000000);
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
    auto chunk = std::string(length, '\0');
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

constexpr auto END_OF_TRACK = 0x2F;
constexpr auto SYSTEM_COMMAND = 0xF0;
constexpr auto NOTE_ON_COMMAND = 0x90;
constexpr auto PROGRAM_CHANGE_COMMAND = 0xC0;
constexpr auto CHANNEL_PRESSURE_COMMAND = 0xD0;

struct MidiHeader
{
    uint32_t length;
    uint16_t format;
    uint16_t trackCount;
    uint16_t resolution;
};

inline auto ReadMidiHeader(std::istringstream &stream)
    -> std::optional<MidiHeader>
{
    if (ReadString(stream, 4) != "MThd")
    {
        return std::nullopt;
    }

    return MidiHeader{ByteSwap(ReadChunk<uint32_t>(stream)),
                      ByteSwap(ReadChunk<uint16_t>(stream)),
                      ByteSwap(ReadChunk<uint16_t>(stream)),
                      ByteSwap(ReadChunk<uint16_t>(stream))};
}

inline auto ReadNoteOnEvent(std::istringstream &stream, uint32_t tick) -> Note
{
    auto noteValue = ReadChunk<uint8_t>(stream);
    auto velocity = ReadChunk<uint8_t>(stream);

    return Note{static_cast<int>(tick), noteValue};
}

inline auto HandleSystemEvent(std::istringstream &stream) -> bool
{
    auto type = ReadChunk<uint8_t>(stream);

    stream.seekg(ReadVarLen(stream), std::ios::cur);

    return type == END_OF_TRACK;
}

inline auto SkipMidiEvent(std::istringstream &stream, uint8_t status) -> void
{
    if ((status & SYSTEM_COMMAND) == PROGRAM_CHANGE_COMMAND ||
        (status & SYSTEM_COMMAND) == CHANNEL_PRESSURE_COMMAND)
    {
        stream.seekg(1, std::ios::cur);
    }
    else
    {
        stream.seekg(2, std::ios::cur);
    }
}

inline auto ReadResolutionFromMidiData(const std::vector<uint8_t> &data)
    -> uint16_t
{
    auto stream = std::istringstream(std::string(data.begin(), data.end()),
                                     std::ios::binary);

    auto header = ReadMidiHeader(stream);

    if (!header)
    {
        return 0;
    }

    return header->resolution;
}

inline auto ReadNotesFromMidiData(const std::vector<uint8_t> &data)
    -> std::vector<Note>
{
    auto stream = std::istringstream(std::string(data.begin(), data.end()),
                                     std::ios::binary);

    auto header = ReadMidiHeader(stream);

    if (!header)
    {
        return {};
    }

    auto notes = std::vector<Note>{};

    for (auto t = 0; t < header->trackCount; t += 1)
    {
        if (ReadString(stream, 4) != "MTrk")
        {
            return notes;
        }

        stream.seekg(4, std::ios::cur);

        uint32_t absoluteTick = 0;

        while (true)
        {
            absoluteTick += ReadVarLen(stream);

            auto status = ReadChunk<uint8_t>(stream);

            if ((status & SYSTEM_COMMAND) == NOTE_ON_COMMAND)
            {
                notes.push_back(ReadNoteOnEvent(stream, absoluteTick));
            }
            else if ((status & SYSTEM_COMMAND) == SYSTEM_COMMAND)
            {
                if (HandleSystemEvent(stream))
                {
                    break;
                }
            }
            else
            {
                SkipMidiEvent(stream, status);
            }
        }
    }

    return notes;
}

} // namespace RhythmGameUtilities
