#pragma once
#include "Common.h"

/**
 * \brief Contains the actual definitions of dynamic functions that can be scripted.
 */
class ScriptableFunctions
{
public:
	/**
	 * \brief Stub for simulating moving to a grid coordinate.
	 * \param args 2 integers, 1st = X coordinate, 2nd = Y coordinate.
	 */
	static void MoveToXY(std::vector<std::string> args);

	/**
	 * \brief Stub for simulating dialogue being printed.
	 * \param args 1 string of dialogue that should be displayed.
	 */
	static void PrintDialogue(std::vector<std::string> args);

	/**
	 * \brief 
	 * \param args 
	 */
	static void SetDynamicVariable(std::vector<std::string> args);
};