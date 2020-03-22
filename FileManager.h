#pragma once
#include "Common.h"

/**
 * \brief Helper for managing file IO.
 */
class FileManager
{
public:	
	/**
	 * \brief  Reads a text file and returns all lines as a string vector.
	 * \param fileName Path & Name of the text file to read from.
	 * \return List of lines as strings from the text file.
	 */
	std::vector<std::string> GetFileLines(const std::string& fileName) const;
};
