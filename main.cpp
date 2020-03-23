#include "FunctionManager.h"
#include "FileManager.h"
#include "ScriptParser.h"
#include "ScriptableFunction.h"

int main()
{
	// setup our helpers
	const FileManager fileManager;
	const ScriptParser scriptParser;
	FunctionManager functionManager;

	// load our script objects from the file
	functionManager.functionObjects = scriptParser.Parse(fileManager.GetFileLines("test.txt"));

	functionManager.variableMap["StarterPokemon"] = "Mudkip";
	
	// run all the dynamic functions
	for (auto function : functionManager.functionObjects) {
		functionManager.Invoke(*function);
	}
	
	return 0;
}