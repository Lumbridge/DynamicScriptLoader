#include "FunctionManager.h"
#include "ScriptParser.h"

int main()
{
	FunctionManager functionManager;

	// add our variables to our variable map
	functionManager.variableMap["PlayerName"] = "Ryan";
	functionManager.variableMap["StarterPokemon"] = "Squirtle";

	functionManager.RunScript("test.txt");

	// switch variable value
	functionManager.variableMap["StarterPokemon"] = "Charmander";

	functionManager.RunScript("test.txt");
	
	return 0;
}