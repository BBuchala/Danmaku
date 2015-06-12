#ifndef EX_DIRECT3D_INIT_FAILED_H
#define EX_DIRECT3D_INIT_FAILED_H

#include "IException.h"

/// <summary>
/// Wyj¹tek wyrzucany gry nie uda³o siê zainicjalizowaæ Direct3D
/// </summary>
class Direct3DInitializationFailedException: public IException
{
public:
	// zwrócenie komunikatu
	std::string ToString() const override;

	// pokazanie message boxa
	void ToMessageBox() override;
};


#endif