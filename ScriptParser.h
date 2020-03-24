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
	std::vector<ScriptableFunction*> Parse(std::vector<std::string>& lines, const std::map<std::string, std::string>& variableMap) const;

	/**
	 * \brief Captures all of the {{ScriptVariables}} from a line of script and returns them in a list.
	 * \param line Script line to get the script variables from.
	 * \return List of script variables on the line.
	 */
	static std::vector<std::string> GetScriptVariables(const std::string& line);

	/**
	 * \brief Updates a line of script and replaces the {{ScriptVariables}} with their in-memory value.
	 * \param line The line of script to replace the script variables on.
	 * \param scriptVariables The list of script variables from the line of script.
	 * \param variableMap The map of in-memory variable values.
	 * \return The same line of script except the {{ScriptVariables}} are replaced with their in-memory value.
	 */
	static std::string SetScriptVariables(std::string line, const std::vector<std::string>& scriptVariables, const std::map<std::string, std::string>& variableMap);

	/**
	 * \brief Splits up a string on a delimeter e.g. splitting PrintDialogue("Hello this is some dialogue") with delimeter '(' would yield ["PrintDialogue(", "\"Hello this is some dialogue\")"].
	 * \param stringToSplit The whole string to split up.
	 * \param delimeter The delimeter to split the string on.
	 * \return Vector containing the split up string.
	 */
	std::vector<std::string> Split(const std::string& stringToSplit, char delimeter) const; // helper method to split a string on a delimiter

	std::vector<std::string> Split(const std::string& stringToSplit, char delimeter, char escape) const; // helper method to split a string on a delimiter

	/**
	 * \brief Splits up a string on a startDelimeter e.g. splitting PrintDialogue("Hello this is some dialogue") with startDelimeter '(' would yield ["PrintDialogue(", "\"Hello this is some dialogue\")"].
	 * \param stringToSplit The whole string to split up.
	 * \param startDelimeter The startDelimeter to split the string on.
	 * \param endDelimeter
	 * \return Vector containing the split up string.
	 */
	static std::vector<std::string> Split(const std::string& stringToSplit, const std::string& startDelimeter, const std::string& endDelimeter);

	/**
	 * \brief Replaces all instances of a target substring with a replacement substring.
	 * \param line The line to perform the replacement on.
	 * \param target The substring target to replace.
	 * \param replacement The substring which will replace the target.
	 * \return String with instances of the target substring replaced with the chosen replacement string.
	 */
	static std::string Replace(std::string line, const std::string& target, const std::string& replacement);
};
