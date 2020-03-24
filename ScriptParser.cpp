#include "ScriptParser.h"
#include "ScriptableFunction.h"

/**
 * \brief Parse method which turns a single line into a single ScriptableFunction.
 * \param line String of text to parse into a ScriptableFunction object.
 * \param variableMap
 * \return Object of type ScriptableFunction.
 */
ScriptableFunction* ScriptParser::Parse(std::string line, const std::map<std::string, std::string>& variableMap) const
{
	// this is a commented line of script
	if(line[0] == '#') 
		return nullptr;
	
	// container for the result of the parse operation
	auto result = new ScriptableFunction();

	auto lin = line;
	auto dynamicVariables = Split(lin, "{{", "}}");
	for (const auto& scriptVar : dynamicVariables)
	{
		for (const auto& mapVar : variableMap) {
			if(mapVar.first == scriptVar)
			{
				lin = Replace(lin, "{{" + scriptVar + "}}", mapVar.second);
			}
		}
	}
			
	// split up the script line
	auto lineParts = Split(lin, '(');
	
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
 * \param variableMap
 * \return Vector of type ScriptableFunction.
 */
std::vector<ScriptableFunction*> ScriptParser::Parse(const std::vector<std::string>& lines, const std::map<std::string, std::string>& variableMap) const
{
	std::vector<ScriptableFunction*> functions;
	// reserve the vector size to increase performance in the loop
	functions.reserve(lines.size());
	for (const auto& line : lines)
		// store the result in the result list
		functions.push_back(Parse(line, variableMap));
	return functions;
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
		strings.push_back(item);
	}
	return strings;
}

/**
 * \brief Splits up a string on a startDelimeter e.g. splitting PrintDialogue("Hello this is some dialogue") with startDelimeter '(' would yield ["PrintDialogue(", "\"Hello this is some dialogue\")"].
 * \param stringToSplit The whole string to split up.
 * \param startDelimeter The startDelimeter to split the string on.
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
 * \brief
 * \param base
 * \param target
 * \param replacement
 * \return
 */
std::string ScriptParser::Replace(std::string base, const std::string& target, const std::string& replacement)
{
	size_t index = 0;
	while (true) {
		// locate the substring to replace
		index = base.find(target, index);
		
		if (index == std::string::npos) 
			break;
		
		// make the replacement
		base.replace(index, target.length(), replacement);
		
		// advance index forward so the next iteration doesn't pick it up as well
		index += index + replacement.length();
	}
	return base;
}