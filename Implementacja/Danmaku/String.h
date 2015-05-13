#pragma once

#include <algorithm>
#include <cctype>
#include <string>

class String
{
public:
	static bool isNumber(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it))
			++it;
		return !s.empty() && it == s.end();
	}
};
