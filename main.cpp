#include "FunctionManager.h"
#include "ScriptParser.h"

int main()
{
	FunctionManager functionManager;

	// add our variables to our variable map
	functionManager.variableMap["PlayerName"] = "Ryan";
	functionManager.variableMap["StarterPokemon"] = "Torchic";

	functionManager.RunScript("test.txt");

	// switch variable value
	functionManager.variableMap["StarterPokemon"] = "Treecko";

	functionManager.RunScript("test.txt");

	return 0;
}