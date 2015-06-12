#include "String.h"

/* ---- is Number
   ------------------------------------------------------------------------------------------- */
/// <summary>
/// Czy napis jest liczb¹.
/// </summary>
/// <param name="s">Napis.</param>
/// <returns></returns>
bool String::isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
};
