#include "ScriptParser.h"
#include "ScriptableFunction.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
/**
 * \brief Parse method which turns a single line into a single ScriptableFunction.
 * \param line String of text to parse into a ScriptableFunction object.
 * \param variableMap
 * \return Object of type ScriptableFunction.
 */
ScriptableFunction* ScriptParser::Parse(std::string line, const std::map<std::string, std::string>& variableMap) const
{
	// this is a commented line of script
	if (line[0] == '#')
		return nullptr;

	// container for the result of the parse operation
	auto result = new ScriptableFunction();

	auto innerLine = line;

	// get all script variables from the script line
	const auto scriptVariables = GetScriptVariables(line);

	// replace all script variables with their in-memory value
	innerLine = SetScriptVariables(line, scriptVariables, variableMap);

	// split up the script line
	auto lineParts = Split(innerLine, '(');

	// store the function name in the result
	result->FunctionName = lineParts[0];

	// store the arg part of the string to be manipulated
	auto argString = lineParts[1];

	// remove trailing bracket from the arg part of the string
	argString.pop_back();

	// split Arguments on commas (if there are any)
	auto argStringParts = Split(argString, ',', '\\');

	// create a container to store the arguments
	std::vector<std::string> argVector;

	// reserve the vector size to increase performance in the loop
	argVector.reserve(argStringParts.size());

	// add each arg to the vector
	for (const auto& arg : argStringParts)
		argVector.push_back(arg);

	// store the vector in the result
	result->Arguments = argVector;

	// return the result
	return result;
}

/**
 * \brief Parse method which turns a number of lines into a list of ScriptableFunctions.
 * \param lines List of strings to parse into ScriptableFunction objects.
 * \param variableMap
 * \return Vector of type ScriptableFunction.
 */
std::vector<ScriptableFunction*> ScriptParser::Parse(std::vector<std::string>& lines, const std::map<std::string, std::string>& variableMap) const
{
	std::vector<ScriptableFunction*> functions;
	// reserve the vector size to increase performance in the loop
	functions.reserve(lines.size());
	// loop all lines in the script
	for (int i = 0; i < lines.size(); i++)
	{
		// get a scoped version of the line we want to process
		auto line = lines[i];
		// if statement processing
		// check if the line starts with "if"
		if (line.substr(0, 2) == "if")
		{
			// replace all {{ScriptVariables}} in the line with their in-memory value e.g. {{PlayerName}} gets replaced with Ryan.
			line = SetScriptVariables(line, GetScriptVariables(line), variableMap);
			// get the left comparative variable from the script line
			std::string left = line.substr(3, line.find_first_of("==") - 3);
			// get the right comparative variable from the script line
			std::string right = line.substr(line.find_first_of("==") + 2, line.find_first_of(')') - line.find_first_of("==") - 2);
			// remove any quotes from the right comparative
			right = Replace(right, "\"", "");

			// check if the comparatives are equal or not
			if (right != left)
			{
				// if the comparatives aren't equal then mark the branches script lines as "Do Not Run" or {{+DNR+}}.
				auto currentIterator = i;
				// continue while we are still reading indented lines after the if statement
				while (true)
				{
					// if we've reached the end of the script then break out
					if (currentIterator == lines.size() - 1) break;  // NOLINT(clang-diagnostic-sign-compare)
					// get the current next line under the failed if statement
					auto currentLine = lines[currentIterator + 1];
					// if the line is not indented then we're done
					if (currentLine[0] != '\t') break;
					// mark the indented line as "Do Not Run" or {{+DNR+}}.
					line = line.insert(0, "{{+DNR+}}");
					// replace the original line in the lines vector
					std::replace(lines.begin(), lines.end(), lines[currentIterator + 1], line);
					// move onto the next line
					currentIterator++;
				}
			}
		}
		// normal script line processing
		else
		{
			if (line.substr(0, 10) == "\t{{+DNR+}}")
				continue;
			if (line[0] == '\t')
				line = line.substr(1, line.size() - 1);
			// store the result in the result list
			functions.push_back(Parse(line, variableMap));
		}
	}
	return functions;
}

/**
 * \brief Captures all of the {{ScriptVariables}} from a line of script and returns them in a list.
 * \param line Script line to get the script variables from.
 * \return List of script variables on the line.
 */
std::vector<std::string> ScriptParser::GetScriptVariables(const std::string& line)
{
	return Split(line, "{{", "}}");
}

/**
 * \brief Updates a line of script and replaces the {{ScriptVariables}} with their in-memory value.
 * \param line The line of script to replace the script variables on.
 * \param scriptVariables The list of script variables from the line of script.
 * \param variableMap The map of in-memory variable values.
 * \return The same line of script except the {{ScriptVariables}} are replaced with their in-memory value.
 */
std::string ScriptParser::SetScriptVariables(std::string line, const std::vector<std::string>& scriptVariables, const std::map<std::string, std::string>& variableMap)
{
	// loop through each of the script variables and replace them with the current value in memory
	for (const auto& scriptVar : scriptVariables)
	{
		for (const auto& mapVar : variableMap) {
			if (mapVar.first == scriptVar)
			{
				line = Replace(line, "{{" + scriptVar + "}}", mapVar.second);  // NOLINT(performance-inefficient-string-concatenation)
			}
		}
	}
	return line;
}

/**
 * \brief Splits up a string on a delimeter e.g. splitting PrintDialogue("Hello this is some dialogue") with delimeter '(' would yield ["PrintDialogue(", "\"Hello this is some dialogue\")"].
 * \param stringToSplit The whole string to split up.
 * \param delimeter The delimeter to split the string on.
 * \return Vector containing the split up string.
 */
std::vector<std::string> ScriptParser::Split(const std::string& stringToSplit, char delimeter) const
{
	std::stringstream ss(stringToSplit);
	std::string item;
	std::vector<std::string> strings;
	while (std::getline(ss, item, delimeter))
	{
		if (item[0])
			strings.push_back(item);
	}
	return strings;
}

std::vector<std::string> ScriptParser::Split(const std::string& stringToSplit, char delimeter, char escape) const
{
	std::vector<std::string> output;
	std::string token;

	auto inEsc = false;
	for (auto ch : stringToSplit) {
		if (inEsc) {
			inEsc = false;
		}
		else if (ch == escape) {
			inEsc = true;
			continue;
		}
		else if (ch == delimeter) {
			output.push_back(token);
			token = "";
			continue;
		}
		token += ch;
	}

	if (inEsc) {
		throw new std::exception("Invalid terminal escape");
	}

	output.push_back(token);
	return output;
}

/**
 * \brief Splits up a string on a startDelimeter e.g. splitting PrintDialogue("Hello this is some dialogue") with startDelimeter '(' would yield ["PrintDialogue(", "\"Hello this is some dialogue\")"].
 * \param stringToSplit The whole string to split up.
 * \param startDelimeter The startDelimeter to split the string on.
 * \param endDelimeter The endDelimeter to split the string on.
 * \return Vector containing the split up string.
 */
std::vector<std::string> ScriptParser::Split(const std::string& stringToSplit, const std::string& startDelimeter, const std::string& endDelimeter)
{
	std::string item;
	std::vector<std::string> strings;
	size_t last = 0; size_t next = 0;
	while ((next = stringToSplit.find(startDelimeter, last)) != std::string::npos) {
		auto str = stringToSplit.substr(last, next - last);
		str = str.substr(0, str.find(endDelimeter, 0));
		strings.push_back(str);
		last = next + startDelimeter.length();
	}
	auto str = stringToSplit.substr(last);
	str = str.substr(0, str.find(endDelimeter, 0));
	strings.push_back(str);
	strings.erase(strings.begin());
	return strings;
}

/**
 * \brief Replaces all instances of a target substring with a replacement substring.
 * \param line The line to perform the replacement on.
 * \param target The substring target to replace.
 * \param replacement The substring which will replace the target.
 * \return String with instances of the target substring replaced with the chosen replacement string.
 */
std::string ScriptParser::Replace(std::string line, const std::string& target, const std::string& replacement)
{
	size_t index = 0;
	while (true) {
		// locate the substring to replace
		index = line.find(target, index);
		// if we reached the end of the string then break out
		if (index == std::string::npos)
			break;
		// make the replacement
		line.replace(index, target.length(), replacement);
		// advance index forward so the next iteration doesn't pick it up as well
		index += index + replacement.length();
	}
	return line;
}
