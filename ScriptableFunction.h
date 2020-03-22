#pragma once
#include "Common.h"

/**
 * \brief Script lines from the text file will be parsed into this object structure.
 */
class ScriptableFunction
{
public:
	/**
	 * \brief Parameterless constructor.
	 */
	ScriptableFunction();

	/**
	 * \brief Main constructor.
	 * \param function_name Name of the function (must match one from the FunctionManager's map).
	 * \param args List of arguments to pass into the dynamic function.
	 */
	ScriptableFunction(const std::string& function_name, std::vector<std::string> args); // constructor which populates our members

	/**
	 * \brief Name of the function (must match one from the FunctionManager's map).
	 */
	std::string FunctionName;

	/**
	 * \brief List of arguments to pass into a dynamic function.
	 */
	std::vector<std::string> Arguments;
};

