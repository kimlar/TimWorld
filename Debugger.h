#pragma once

#include <fstream>
#include <string>

#include "SystemUtils.h"

static void DebugBegin()
{
	std::ofstream debugFile("Debug.txt", std::ofstream::out | std::ofstream::trunc);
	debugFile << "============  Start of debug  ============" << SystemUtils::newline;
	debugFile.flush();
	debugFile.close();
}

static void DebugEnd()
{
	std::ofstream debugFile("Debug.txt", std::ofstream::out | std::ofstream::app);
	debugFile << "=============  End of debug  =============" << SystemUtils::newline;
	debugFile.flush();
	debugFile.close();
}

static void Debug(std::string debugmsg)
{
	std::ofstream debugFile("Debug.txt", std::ofstream::out | std::ofstream::app);
	debugFile << "Output: " << SystemUtils::newline;
	debugFile << debugmsg << SystemUtils::newline;
	debugFile.flush();
	debugFile.close();
}
