#include "ScriptableFunctions.h"

/**
 * \brief Stub for simulating moving to a grid coordinate.
 * \param args 2 integers, 1st = X coordinate, 2nd = Y coordinate.
 */
void ScriptableFunctions::MoveToXY(std::vector<std::string> args)
{
	auto arguments = static_cast<std::vector<std::string>*>(&args)[0];
	const auto x = std::stoi(arguments[0]);
	const auto y = std::stoi(arguments[1]);
	std::cout << "Moved to grid XY: (" << x << ", " << y << ")" << std::endl;
}

/**
 * \brief Stub for simulating dialogue being printed.
 * \param args 1 string of dialogue that should be displayed.
 */
void ScriptableFunctions::PrintDialogue(std::vector<std::string> args)
{
	auto arguments = static_cast<std::vector<std::string>*>(&args)[0];
	const auto dialogueText = arguments[0];
	std::cout << "Print Dialogue: " << dialogueText << std::endl;
}