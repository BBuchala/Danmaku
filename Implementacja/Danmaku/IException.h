/* ======================================================== *\
 *  @IException.h
 *  @Opis: Interfejs dla wyj�tk�w
 *  @Utworzona: 21.03.2015 19:02
 *  @Autor: Mateusz Forczma�ski
\* ======================================================== */

#ifndef EX_H
#define EX_H

class IException
{
public:
	virtual ~IException() {};

	// zwr�cenie komunikatu
	virtual const char * ToString() = 0;

	// pokazanie message boxa
	virtual void ToMessageBox() = 0;
};

#endif