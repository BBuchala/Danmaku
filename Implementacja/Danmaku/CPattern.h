#pragma once

#include "IPattern.h"

//// konkretna klasa ka¿dego Patternu
class CPattern : public IPattern
{
protected:
	//// POCISKI
	EBulletQue bullet;

	// definicja wspólnego wskaŸnika na tor
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;

	// Kontrola czasowa
	float elapsedTime;

	// uchyt do diwajsa, dla generacji nowych pocisków w czasie
	LPDIRECT3DDEVICE9 device;

public:
	CPattern();
	virtual ~CPattern();
	
	// przekazanie uchwytu
	void Initialize(LPDIRECT3DDEVICE9 device);

	// narysowanie wszystkich pocisków
	void Draw( short const x, short const y, short const width, short const height ) override;

	inline EBulletQue const & GetBullets() const override
	{
		return bullet;
	};

};

