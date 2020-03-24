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
	 * \param variableMap
	 * \return Object of type ScriptableFunction.
	 */
	ScriptableFunction* Parse(std::string line, const std::map<std::string, std::string>& variableMap) const;
		
	/**
	 * \brief Parse method which turns a number of lines into a list of ScriptableFunctions.
	 * \param lines List of strings to parse into ScriptableFunction objects.
	 * \param variableMap
	 * \return Vector of type ScriptableFunction.
	 */
	std::vector<ScriptableFunction*> Parse(const std::vector<std::string>& lines, const std::map<std::string, std::string>& variableMap) const;
		
	/**
	 * \brief Splits up a string on a delimeter e.g. splitting PrintDialogue("Hello this is some dialogue") with delimeter '(' would yield ["PrintDialogue(", "\"Hello this is some dialogue\")"].
	 * \param stringToSplit The whole string to split up.
	 * \param delimeter The delimeter to split the string on.
	 * \return Vector containing the split up string.
	 */
	std::vector<std::string> Split(const std::string& stringToSplit, char delimeter) const; // helper method to split a string on a delimiter
	
	/**
	 * \brief Splits up a string on a startDelimeter e.g. splitting PrintDialogue("Hello this is some dialogue") with startDelimeter '(' would yield ["PrintDialogue(", "\"Hello this is some dialogue\")"].
	 * \param stringToSplit The whole string to split up.
	 * \param startDelimeter The startDelimeter to split the string on.
	 * \param endDelimeter
	 * \return Vector containing the split up string.
	 */
	static std::vector<std::string> Split(const std::string& stringToSplit, const std::string& startDelimeter, const std::string& endDelimeter);

	/**
	 * \brief
	 * \param base
	 * \param target
	 * \param replacement
	 * \return
	 */
	static std::string Replace(std::string base, const std::string& target, const std::string& replacement);
};
