#pragma once

#include <algorithm>
#include <cctype>
#include <string>

/// <summary>
/// Pomocniczna klasa, kt�ra przechowuje dodatkow� obs�uga string�w
/// </summary>
class String
{
public:
	static bool isNumber(const std::string& s);
};
