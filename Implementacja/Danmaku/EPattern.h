#pragma once

#include "IPattern.h"
#include "EnemyBullet.h"

//// konkretna klasa ka¿dego Patternu
class EPattern : public IPattern
{
protected:
	/// Definicja kolejki wrogich pocisków
	typedef std::deque<EnemyBullet*> EBulletQue;
	// definicja wspólnego wskaŸnika na tor
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;
	/// Definicja mapy trajektorii
	typedef std::map<std::string, TrajectoryPtr> TrajectoryMap;
	/// Definicja oary do mapy trajektorii
	typedef std::pair<std::string, TrajectoryPtr> TrajectoryPair;

	//// POCISKI
	EBulletQue bullet;

	// Kontrola czasowa
	float elapsedTime;

	// uchyt do diwajsa, dla generacji nowych pocisków w czasie
	LPDIRECT3DDEVICE9 device;

	// pozycja wzoru
	D3DXVECTOR2 position;

public:
	EPattern();
	virtual ~EPattern();
	
	// przekazanie uchwytu
	virtual void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position );

	virtual void SetPosition(D3DXVECTOR2 const & pos);

	// narysowanie wszystkich pocisków
	void Draw(RECT const & rect) override;

	inline EBulletQue const & GetBullets() const
	{
		return bullet;
	};

};

