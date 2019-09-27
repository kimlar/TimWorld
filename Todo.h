#pragma once

#include <fstream>
#include <string>

#include "SystemUtils.h"

static void TodoBegin()
{
	std::ofstream todoFile("Todo.txt", std::ofstream::out | std::ofstream::trunc);
	todoFile << "============  Start of todo  ============" << SystemUtils::newline;
	todoFile.flush();
	todoFile.close();
}

static void TodoEnd()
{
	std::ofstream todoFile("Todo.txt", std::ofstream::out | std::ofstream::app);
	todoFile << "=============  End of todo  =============" << SystemUtils::newline;
	todoFile.flush();
	todoFile.close();
}

static void Todo(std::string todomsg)
{
	std::ofstream todoFile("Todo.txt", std::ofstream::out | std::ofstream::app);
	todoFile << "TODO: " << todomsg << SystemUtils::newline;
	todoFile.flush();
	todoFile.close();
}
