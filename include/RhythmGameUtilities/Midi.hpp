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

const auto END_OF_TRACK = 0x2F;

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
        return {};
    }

    std::vector<Note> notes;

    auto headerLength = ByteSwap(ReadChunk<uint32_t>(stream));
    auto format = ByteSwap(ReadChunk<uint16_t>(stream));
    auto tracks = ByteSwap(ReadChunk<uint16_t>(stream));
    auto resolution = ByteSwap(ReadChunk<uint16_t>(stream));

    for (int t = 0; t < tracks; t += 1)
    {
        if (ReadString(stream, 4) != "MTrk")
        {
            return notes;
        }

        auto trackLength = ByteSwap(ReadChunk<uint32_t>(stream));

        uint32_t absoluteTick = 0;

        while (true)
        {
            absoluteTick += ReadVarLen(stream);

            auto status = ReadChunk<uint8_t>(stream);

            if ((status & SYSTEM_COMMAND) == NOTE_ON_COMMAND)
            {
                Note note{static_cast<int>(absoluteTick),
                          ReadChunk<uint8_t>(stream)};

                auto velocity = ReadChunk<uint8_t>(stream);

                notes.push_back(note);
            }
            else if ((status & SYSTEM_COMMAND) == SYSTEM_COMMAND)
            {
                auto type = ReadChunk<uint8_t>(stream);

                auto length = ReadVarLen(stream);

                stream.seekg(length, std::ios::cur);

                if (type == END_OF_TRACK)
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
        return {};
    }

    auto fileSize = file.tellg();

    std::vector<uint8_t> buffer(static_cast<size_t>(fileSize));

    file.seekg(0, std::ios::beg);

    file.read(reinterpret_cast<char *>(buffer.data()), fileSize);

    return ReadMidiData(buffer);
}

} // namespace RhythmGameUtilities
