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
	/// Definicja pary do mapy trajektorii
	typedef std::pair<std::string, TrajectoryPtr> TrajectoryPair;

	//// POCISKI
	EBulletQue _bullet;

	/// Sk³adowe potrzebne do generowania pocisków
	float _number;
	float _interval;

	/// W³aœciwoœci generowanych pocisków
	std::string _bulletImage;
	float _bulletSpeed;
	BYTE _bulletWidth;
	BYTE _bulletHeight;
	Hitbox::Shape _hitboxShape;
	Hitbox::Size _hitboxSize;

	/// Odstêp czasowy pomiêdzy pociskami
	float _bulletTime;

	// Kontrola czasowa
	float _elapsedTime;

	// uchyt do diwajsa, dla generacji nowych pocisków w czasie
	LPDIRECT3DDEVICE9 _device;

	// pozycja wzoru
	D3DXVECTOR2 _position;

public:
	EPattern();
	virtual ~EPattern();
	
	// przekazanie uchwytu
	virtual void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position );
	void InitializeBullets(std::string bulletImage, float bulletSpeed, BYTE bulletWidth, BYTE bulletHeight, Hitbox::Shape hitboxShape, Hitbox::Size hitboxSize);

	virtual void SetPosition(D3DXVECTOR2 const & pos);

	// narysowanie wszystkich pocisków
	void Draw(RECT const & rect) override;

	inline EBulletQue & GetBullets()
	{
		return _bullet;
	};

	inline D3DXVECTOR2 & GetPosition()
	{
		return _position;
	}

};

