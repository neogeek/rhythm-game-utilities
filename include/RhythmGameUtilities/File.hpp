#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace RhythmGameUtilities
{

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
