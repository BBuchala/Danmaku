#ifndef EX_H
#define EX_H

#include <string>
#include <Windows.h>

/// <summary>
/// Wzór dla wyj¹tku
/// </summary>
class IException
{
public:
	virtual ~IException() = 0 {};

	// zwrócenie komunikatu
	virtual std::string ToString() const = 0;

	// pokazanie message boxa
	virtual void ToMessageBox() = 0;
};

#endif