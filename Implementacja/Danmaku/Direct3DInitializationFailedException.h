#ifndef EX_DIRECT3D_INIT_FAILED_H
#define EX_DIRECT3D_INIT_FAILED_H

#include "IException.h"

/// <summary>
/// Wyj�tek wyrzucany gry nie uda�o si� zainicjalizowa� Direct3D
/// </summary>
class Direct3DInitializationFailedException: public IException
{
public:
	// zwr�cenie komunikatu
	std::string ToString() const override;

	// pokazanie message boxa
	void ToMessageBox() override;
};


#endif