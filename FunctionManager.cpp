#include "FunctionManager.h"

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
    // check if the function name exists in the map
    if (functionContainer.find(functionName) == functionContainer.end())
        return;
    // invoke the function
    reinterpret_cast<void(*)(std::vector<std::string>)>(functionContainer[functionName])(args);
}

/**
 * \brief Dynamically run a function which exists in the functionContainer map by passing it an actual ScriptableFunction object.
 * \param scriptableFunction ScriptableFunction to dynamically run.
 */
void FunctionManager::Invoke(const ScriptableFunction & scriptableFunction)
{
    // check if the object is valid
    if (&scriptableFunction == nullptr)  // NOLINT(clang-diagnostic-tautological-undefined-compare)
        return;
    // check if the function name exists in the map
    if (functionContainer.find(scriptableFunction.FunctionName) == functionContainer.end())
        return;
    // invoke the function
    reinterpret_cast<void(*)(std::vector<std::string>)>(functionContainer[scriptableFunction.FunctionName])(scriptableFunction.Arguments);
}

/**
 * \brief Runs all functions in the functionObject collection.
 */
void FunctionManager::InvokeAll()
{
    // run all the dynamic functions
    for (auto function : functionObjects) {
        Invoke(*function);
    }
}

/**
 * \brief Parses and runs all functions in a script file.
 * \param scriptPath The path on disk where the script can be found.
 */
void FunctionManager::RunScript(const std::string & scriptPath)
{
    const ScriptParser scriptParser;
    const FileManager fileManager;

    auto lines = fileManager.GetFileLines("test.txt");

    // load our script objects from the file
    functionObjects = scriptParser.Parse(lines, variableMap);

    // run all the dynamic functions
    InvokeAll();
}