#pragma once
#include "Common.h"
#include "ScriptableFunction.h"

/**
 * \brief Helper class for parsing script lines into ScriptableFunction objects.
 */
class ScriptParser
{
public:
	/**
	 * \brief Parse method which turns a single line into a single ScriptableFunction.
	 * \param line String of text to parse into a ScriptableFunction object.
	 * \return Object of type ScriptableFunction.
	 */
	ScriptableFunction* Parse(std::string line) const;
		
	/**
	 * \brief Parse method which turns a number of lines into a list of ScriptableFunctions.
	 * \param lines List of strings to parse into ScriptableFunction objects.
	 * \return Vector of type ScriptableFunction.
	 */
	std::vector<ScriptableFunction*> Parse(const std::vector<std::string>& lines) const;
		
	/**
	 * \brief Splits up a string on a delimeter e.g. splitting PrintDialogue("Hello this is some dialogue") with delimeter '(' would yield ["PrintDialogue(", "\"Hello this is some dialogue\")"].
	 * \param stringToSplit The whole string to split up.
	 * \param delimeter The delimeter to split the string on.
	 * \return Vector containing the split up string.
	 */
	std::vector<std::string> Split(std::string stringToSplit, char delimeter) const; // helper method to split a string on a delimiter
};
