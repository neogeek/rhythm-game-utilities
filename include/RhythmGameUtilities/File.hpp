#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace RhythmGameUtilities
{

/**
 * Reads the entire contents of a file as a byte array.
 *
 * @param path The path of the file to read.
 * @public
 */

inline auto ReadBytesFromFile(const char *path) -> std::vector<uint8_t>
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        std::cerr << "Failed to open " << path << ".\n";
    }

    auto fileSize = file.tellg();

    std::vector<uint8_t> buffer(static_cast<size_t>(fileSize));

    file.seekg(0, std::ios::beg);

    file.read(reinterpret_cast<char *>(buffer.data()), fileSize);

    return buffer;
}

/**
 * Reads the entire contents of a file as a string.
 *
 * @param path The path of the file to read.
 * @public
 */

inline auto ReadStringFromFile(const char *path) -> std::string
{
    std::ifstream file(path);

    if (!file)
    {
        std::cerr << "Failed to open " << path << ".\n";

        return "";
    }

    return {(std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()};
}

} // namespace RhythmGameUtilities
