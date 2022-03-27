#include "file_stream_utils.h"

bool OpenFileStream(std::fstream& fileStream, const std::string& fileName, std::ios_base::openmode mode)
{
	if (fileStream.is_open())
	{
		fileStream.close();
	}

	fileStream.open(fileName, mode);

	if (!fileStream.is_open())
	{
		return false;
	}
	
	return true;
}
