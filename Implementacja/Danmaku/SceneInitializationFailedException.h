#ifndef EX_SCENE_INIT_FAILED_H
#define EX_SCENE_INIT_FAILED_H

#include <Windows.h>
#include "IException.h"

class SceneInitializationFailedException : IException
{
public:
	// zwrócenie komunikatu
	const char * ToString() override;

	// pokazanie message boxa
	void ToMessageBox() override;
};


#endif