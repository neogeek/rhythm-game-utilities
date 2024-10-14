#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace RhythmGameUtilities
{

/**
 * Reads the entire contents of a file.
 *
 * @param path The path of the file to read.
 * @public
 */

std::string ReadFromFile(const char *path)
{
    std::ifstream file(path);

    if (!file)
    {
        std::cerr << "Failed to open " << path << "." << std::endl;

        return "";
    }

    return std::string((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
}

} // namespace RhythmGameUtilities
