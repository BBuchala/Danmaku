/* ======================================================== *\
 *  @IException.h
 *  @Opis: Interfejs dla wyj¹tków
 *  @Utworzona: 21.03.2015 19:02
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#ifndef EX_H
#define EX_H

class IException
{
public:
	virtual ~IException() {};

	// zwrócenie komunikatu
	virtual const char * ToString() = 0;

	// pokazanie message boxa
	virtual void ToMessageBox() = 0;
};

#endif