#pragma once
#include <fstream>

bool OpenFileStream(std::fstream& fileStream, const std::string& fileName, std::ios_base::openmode mode);
