#include "FileManager.h"

/**
 * \brief  Reads a text file and returns all lines as a string vector.
 * \param fileName Path & Name of the text file to read from.
 * \return List of lines as strings from the text file.
 */
std::vector<std::string> FileManager::GetFileLines(const std::string& fileName) const
{
	std::vector<std::string> lines;
	std::ifstream src(fileName);
	if (!src)
	{
		perror("Error opening file ");
		system("pause");
		return lines;
	}
	std::string line;
	while (std::getline(src, line))
	{
		lines.push_back(line);
	}
	return lines;
}