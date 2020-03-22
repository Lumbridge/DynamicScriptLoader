#include "ScriptParser.h"
#include "ScriptableFunction.h"

/**
 * \brief Parse method which turns a single line into a single ScriptableFunction.
 * \param line String of text to parse into a ScriptableFunction object.
 * \return Object of type ScriptableFunction.
 */
ScriptableFunction* ScriptParser::Parse(std::string line) const
{
	// container for the result of the parse operation
	auto result = new ScriptableFunction();
	// split up the script line
	auto lineParts = Split(std::move(line), '(');
	// store the function name in the result
	result->FunctionName = lineParts[0];
	// store the arg part of the string to be manipulated
	auto argString = lineParts[1];
	// remove trailing bracket from the arg part of the string
	argString.pop_back(); 
	// split Arguments on commas (if there are any)
	auto argStringParts = Split(argString, ',');
	// create a container to store the arguments
	std::vector<std::string> argVector;
	// reserve the vector size to increase performance in the loop
	argVector.reserve(argStringParts.size());
	// add each arg to the vector
	for(const auto& arg: argStringParts)				
		argVector.push_back(arg);	
	// store the vector in the result
	result->Arguments = argVector;
	// return the result
	return result;
}

/**
 * \brief Parse method which turns a number of lines into a list of ScriptableFunctions.
 * \param lines List of strings to parse into ScriptableFunction objects.
 * \return Vector of type ScriptableFunction.
 */
std::vector<ScriptableFunction*> ScriptParser::Parse(const std::vector<std::string>& lines) const
{
	std::vector<ScriptableFunction*> functions;
	// reserve the vector size to increase performance in the loop
	functions.reserve(lines.size());
	for (const auto& line : lines)
		// store the result in the result list
		functions.push_back(Parse(line));
	return functions;
}

/**
 * \brief Splits up a string on a delimeter e.g. splitting PrintDialogue("Hello this is some dialogue") with delimeter '(' would yield ["PrintDialogue(", "\"Hello this is some dialogue\")"].
 * \param stringToSplit The whole string to split up.
 * \param delimeter The delimeter to split the string on.
 * \return Vector containing the split up string.
 */
std::vector<std::string> ScriptParser::Split(std::string stringToSplit, char delimeter) const
{
	std::stringstream ss(stringToSplit);
	std::string item;
	std::vector<std::string> strings;
	while (std::getline(ss, item, delimeter))
	{
		strings.push_back(item);
	}
	return strings;
}
