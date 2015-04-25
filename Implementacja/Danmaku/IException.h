/* ======================================================== *\
 *  @IException.h
 *  @Opis: Interfejs dla wyj�tk�w
 *  @Utworzona: 21.03.2015 19:02
 *  @Autor: Mateusz Forczma�ski
\* ======================================================== */

#ifndef EX_H
#define EX_H

#include <string>

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