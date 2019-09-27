#pragma once

#include <stdlib.h>     /* exit, EXIT_FAILURE */

#include <fstream>
#include <string>

#include "SystemUtils.h"

static void LogBegin()
{
	std::ofstream logFile("Log.txt", std::ofstream::out | std::ofstream::trunc);
	logFile << "============  Start of log  ============" << SystemUtils::newline;
	logFile.flush();
	logFile.close();
}

static void LogEnd()
{
	std::ofstream logFile("Log.txt", std::ofstream::out | std::ofstream::app);
	logFile << "=============  End of log  =============" << SystemUtils::newline;
	logFile.flush();
	logFile.close();
}

static void Log(std::string logmsg)
{
	std::ofstream logFile("Log.txt", std::ofstream::out | std::ofstream::app);
	logFile << "LOG: " << logmsg << SystemUtils::newline;
	logFile.flush();
	logFile.close();
}

static void LogError(std::string errormsg, int errornum = EXIT_FAILURE)
{
	std::ofstream logFile("Log.txt", std::ofstream::out | std::ofstream::app);
	if(errornum == EXIT_FAILURE)
		logFile << "ERROR: " << errormsg << SystemUtils::newline;
	else
		logFile << "ERROR(" << errornum << "): " << errormsg << SystemUtils::newline;
	logFile << "*** Terminating ***" << SystemUtils::newline;
	logFile.flush();
	logFile.close();

	exit(errornum); // Terminate program now!
}

static void LogTest(bool test, std::string errormsg)
{
	if (test)
		LogError(errormsg);
}
