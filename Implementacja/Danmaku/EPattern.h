#pragma once

#include "IPattern.h"
#include "EnemyBullet.h"
#include "Pattern.h"

// konkretna klasa ka�dego Patternu
class EPattern : public IPattern
{
protected:
	// Definicja kolejki wrogich pocisk�w
	typedef std::deque<EnemyBullet*> EBulletQue;
	// definicja wsp�lnego wska�nika na tor
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;
	// Definicja mapy trajektorii
	typedef std::map<std::string, TrajectoryPtr> TrajectoryMap;
	// Definicja pary do mapy trajektorii
	typedef std::pair<std::string, TrajectoryPtr> TrajectoryPair;

	// POCISKI
	EBulletQue _bullet;

	// Sk�adowe potrzebne do generowania pocisk�w
	float _number;
	float _interval;

	// Kontrolki przekszta�ce� afinicznych
	D3DXVECTOR2 _translate;
	float _scale;
	float _scaleStep;
	float _rotate;
	float _rotateStep;
	float _bulletScale;
	float _bulletRotate;

	// W�a�ciwo�ci generowanych pocisk�w
	std::shared_ptr<Sprite> _bulletSprite;
	float _bulletSpeed;
	float _bulletAcc;
	BYTE _bulletWidth;
	BYTE _bulletHeight;
	Hitbox::Shape _hitboxShape;
	Hitbox::Size _hitboxSize;

	// pozycja wzoru
	D3DXVECTOR2 _position;

	float _activationTime;
	bool _activated;

public:
	EPattern(float const activationTime);
	EPattern(EPattern const & pattern);
	virtual ~EPattern();
	
	// przekazanie uchwytu
	virtual void Initialize(D3DXVECTOR2 const & position);
	void InitializeBullets(std::shared_ptr<Sprite> bulletSprite, float bulletSpeed, float bulletAcc, BYTE bulletWidth,
		BYTE bulletHeight, Hitbox::Shape hitboxShape, Hitbox::Size hitboxSize, float bulletScale, float bulletRotate);

	// aktualizacja
	virtual void Update(float const time, D3DXVECTOR2 const & position);

	// narysowanie wszystkich pocisk�w
	void Draw(RECT const & rect) override;


	virtual void StartBullets(D3DXVECTOR2 const & position) = 0;
	void Activate(float const actTime, D3DXVECTOR2 const & position);


	/// SETTERY
	virtual void SetPosition(D3DXVECTOR2 const & pos);
	void SetBulletScale(float scale);
	void SetBulletRotation(float rotate);

	/// GETTERY
	inline EBulletQue * GetBullets()
	{
		return &_bullet;
	};

	inline D3DXVECTOR2 & GetPosition()
	{
		return _position;
	}

	inline bool IsInitialized() const
	{
		return _activated;
	}

	inline bool HasBulles() const
	{
		return _bullet.size() == 0 ? false : true;
	}

	/// PRZEKSZTA�CENIA AFINICZNE
	virtual void Translate(D3DXVECTOR2 const & translate);
	virtual void Scale(float const scale);
	virtual void Rotate(float const rotate);

	/// Ustawienie warto�ci przekszta�ce� afinicznych
	virtual void SetTranslation(D3DXVECTOR2 const & translate);
	virtual void SetScale(float const scale);
	virtual void SetRotation(float const rotate);

	void SetScaleStep(float scaleStep)
	{
		_scaleStep = scaleStep;
	}
	void SetRotationStep(float rotateStep)
	{
		_rotateStep = rotateStep;
	}
	void SetActivated(bool act)
	{
		this->_activated = act;
	}
	void ForceActivate(D3DXVECTOR2 const & position)
	{
		this->StartBullets(position);
		_activated = true;
	};

	virtual EPattern * Clone() const = 0;
};

