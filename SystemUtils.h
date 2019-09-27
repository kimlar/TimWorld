#pragma once

#if defined(_WIN32)
#include <Windows.h>
#endif

#include <string>

namespace SystemUtils
{
	
////////////////////////////////////////////////////////////
// Identify the operating system
// see http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
////////////////////////////////////////////////////////////
#if defined(_WIN32)
	// Windows (Both 32 bit and 64 bit)
	#define OS_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
	// Apple (all platforms)
	#define OS_MAC
	// TODO: Expand this
#elif defined(__unix__)
	// UNIX system
	#if defined(__linux__)
		// Linux
		#define OS_LINUX
	#endif
#else
	// Unknown operating system
	#error Unknown operating system
#endif


////////////////////////////////////////////////////////////
// Get the operating system
////////////////////////////////////////////////////////////
	enum OS { Unknown = 0, Windows, Mac, Linux };
	static OS GetOperatingSystem()
	{
#ifdef OS_WINDOWS
		return OS::Windows;
#elif OS_MAC
		return OS::Mac;
#elif OS_LINUX
		return OS::Linux;
#else
		return OS::Unknown;
#endif
	}


////////////////////////////////////////////////////////////
// Get the operating systems newline
////////////////////////////////////////////////////////////
	static std::string GetNewline()
	{
#ifdef OS_WINDOWS
		return "\r\n";
#else
		return "\n";
#endif
	}


////////////////////////////////////////////////////////////
// Get the operating systems newline (const version)
////////////////////////////////////////////////////////////
#ifdef OS_WINDOWS
	const std::string newline = "\r\n";
#else
	const std::string newline = "\n";
#endif


////////////////////////////////////////////////////////////
// Check if the application is the only instance running (avoid running multiple applications)
////////////////////////////////////////////////////////////
#ifdef OS_WINDOWS
#define __CHECK_FOR_MULTIPLE_INSTANCES__ \
	HANDLE m_Mutex_h = ::CreateMutex(NULL, FALSE, TEXT("TimWorld-8983-3453-4352-7234")); \
	if ((m_Mutex_h == NULL) || (GetLastError() == ERROR_ALREADY_EXISTS)) \
		return; // just quit
#else
	// TODO: Implement for other OS
#endif

}
