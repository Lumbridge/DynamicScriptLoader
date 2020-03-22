#include "ScriptableFunction.h"

/**
 * \brief Parameterless constructor.
 */
ScriptableFunction::ScriptableFunction() = default;

/**
 * \brief Main constructor.
 * \param function_name Name of the function (must match one from the FunctionManager's map).
 * \param args List of arguments to pass into the dynamic function.
 */
ScriptableFunction::ScriptableFunction(const std::string & function_name, std::vector<std::string> args)
{
	FunctionName = function_name;
	Arguments = std::move(args);
}