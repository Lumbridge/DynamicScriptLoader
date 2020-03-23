#pragma once
#include "ScriptableFunction.h"
#include "ScriptParser.h"
#include "FunctionManager.h"
#include "ScriptableFunctions.h"
#include "FileManager.h"

/**
 * \brief Helper for managing dynamic functions.
 */
class FunctionManager
{
public:
	/**
	 * \brief This constructor adds some dynamically callable functions to our functionContainer map.
	 */
	FunctionManager();

	/**
	 * \brief Default deconstructor.
	 */
	~FunctionManager();
	
	/**
	 * \brief Dynamically run a function which exists in the functionContainer map by passing it's name & args.
	 * \param functionName Name of the dynamic function to run (must exist in the functionContainer)
	 * \param args List of arguments to pass into the function.
	 */
	void Invoke(const std::string& functionName, std::vector<std::string>& args);

	/**
	 * \brief Dynamically run a function which exists in the functionContainer map by passing it's name & args.
	 * \param scriptableFunction Name of the dynamic function to run (must exist in the functionContainer)
	 * \param args List of arguments to pass into the function.
	 */
	void Invoke(const ScriptableFunction& scriptableFunction);

	/**
	 * \brief Runs all functions in the functionObject collection.
	 */
	void InvokeAll();
		
	/**
	 * \brief Parses and runs all functions in a script file.
	 * \param scriptPath The path on disk where the script can be found.
	 */
	void RunScript(const std::string& scriptPath);
		
	/**
	 * \brief Dynamically run a function which exists in the functionContainer map by passing it an actual ScriptableFunction object.
	 * \param event_function ScriptableFunction to dynamically run.
	 */
	std::vector<ScriptableFunction*> functionObjects;

	/**
	 * \brief Contains dynamic variables available to scripts.
	 */
	std::map<std::string, std::string> variableMap;
private:
	/**
	 * \brief Generic template type for adding dynamic methods to a map.
	 */
	typedef void (*genericTemplate)();
		
	/**
	 * \brief Map definition of dynamic functions that can be called.
	 */
	std::map<std::string, genericTemplate> functionContainer;	
};