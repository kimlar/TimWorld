#pragma once

#include <ctype.h> //toupper()
#include <string>

namespace StringUtils
{
	/*
		Name: ToUpperCase
		Param 1: The text to be upper cased.
		Return: Upper cased text.
		Purpose: To upper case a line of text.
	*/
	static std::string ToUpperCase(std::string line)
	{
		if (line == "")
			return "";

		for (int i = 0; i < line.size(); i++)
			line[i] = toupper(line[i]);

		return line;
	}

	/*
		Name: RemoveWhiteSpaces
		Param 1: The text before operation.
		Return: The text after operation.
		Purpose: To remove white spaces from a line of text.
		Details: Removes spaces (' '), tabs ('\t'), return ('\r') and newline ('\n')
	*/
	static std::string RemoveWhiteSpaces(std::string line)
	{
		if (line == "")
			return "";

		std::string temp;
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ' || line[i] == '\t' || line[i] == '\r' || line[i] == '\n')
				continue;

			temp += line[i];
		}

		return temp;
	}
	
	/*
		Name: FindKeyWord
		Param 1: The keyword to find.
		Param 2: The line to search.
		Return: True if we found it, else false.
		Purpose: Tryies to find the keyword (only from the begining).
		Example: SkipIntro=0
				 ^^^^^^^^^
		If we search for keyword "SkipIntro" in "line" then we found it.
		Note 1: Does only search for keywords from the begining (does not find keyword in the middle).
		Note 2: It is case sensitive. Use ToUpperCase().
	*/
	static bool FindKeyword(std::string keyword, std::string line)
	{
		if (line.substr(0, keyword.length()) == keyword)
			return true; // Fount it!

		return false;
	}
	
	/*
		Name: ConvertToBool
		Param 1: The string value to determine if true or false.
		Return: True if words are "1", "true", "yes", "y" or "on". If not return false.
		Purpose: To determine if the value given is either positive or negative, then return that.
		Details: All values are upper cased to simplify the identification process.
		         Positive keywords are like: 1, true, True, TRUE, yes, Yes, YES y, Y, on, On, ON.
				 Also weird ones like: tRue, TrUe, yEs etc..
		Note 1: Default return value is false (if not found a positiv keyword).
		Note 2: If the value is empty it is presumed to be false (defaulted to false);
	*/
	static bool ConvertToBool(std::string value)
	{
		if (value == "1")
			return true;

		std::string upvalue = StringUtils::ToUpperCase(value);
		if (upvalue == "TRUE" || upvalue == "YES" || upvalue == "Y" || upvalue == "ON")
			return true;

		return false;
	}
}
