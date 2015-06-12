#ifndef EX_H
#define EX_H

#include <string>
#include <Windows.h>

/// <summary>
/// Wz�r dla wyj�tku
/// </summary>
class IException
{
public:
	virtual ~IException() = 0 {};

	// zwr�cenie komunikatu
	virtual std::string ToString() const = 0;

	// pokazanie message boxa
	virtual void ToMessageBox() = 0;
};

#endif