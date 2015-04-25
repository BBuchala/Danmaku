/* ======================================================== *\
 *  @IException.h
 *  @Opis: Interfejs dla wyjątków
 *  @Utworzona: 21.03.2015 19:02
 *  @Autor: Mateusz Forczmański
\* ======================================================== */

#ifndef EX_H
#define EX_H

#include <string>

class IException
{
public:
	virtual ~IException() {};

	// zwrócenie komunikatu
	virtual const std::string ToString() const = 0;

	// pokazanie message boxa
	virtual void ToMessageBox() = 0;
};

#endif