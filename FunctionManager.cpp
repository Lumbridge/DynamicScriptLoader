#include "FunctionManager.h"
#include "ScriptableFunctions.h"
#include "ScriptableFunction.h"

/**
 * \brief Helper for managing dynamic functions.
 */
FunctionManager::FunctionManager()
{
	functionContainer["MoveToXY"] = genericTemplate(ScriptableFunctions::MoveToXY);
	functionContainer["PrintDialogue"] = genericTemplate(ScriptableFunctions::PrintDialogue);
}

/**
 * \brief Default deconstructor.
 */
FunctionManager::~FunctionManager() = default;

/**
 * \brief Dynamically run a function which exists in the functionContainer map by passing it's name & args.
 * \param functionName Name of the dynamic function to run (must exist in the functionContainer)
 * \param args List of arguments to pass into the function.
 */
void FunctionManager::Invoke(const std::string & functionName, std::vector<std::string> & args)
{
	reinterpret_cast<void(*)(std::vector<std::string>)>(functionContainer[functionName])(args);
}

/**
 * \brief Dynamically run a function which exists in the functionContainer map by passing it an actual ScriptableFunction object.
 * \param functionName ScriptableFunction to dynamically run.
 */
void FunctionManager::Invoke(const ScriptableFunction & functionName)
{
	reinterpret_cast<void(*)(std::vector<std::string>)>(functionContainer[functionName.FunctionName])(functionName.Arguments);
}