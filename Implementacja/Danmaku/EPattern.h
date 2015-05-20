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

	/// Kontrolki przekszta³ceñ afinicznych
	D3DXVECTOR2 _translate;
	float _scale;
	float _rotate;

	/// W³aœciwoœci generowanych pocisków
	std::shared_ptr<Sprite> _bulletSprite;
	float _bulletSpeed;
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
	virtual ~EPattern();
	
	// przekazanie uchwytu
	virtual void Initialize(D3DXVECTOR2 const & position);
	void InitializeBullets(std::shared_ptr<Sprite> bulletSprite, float bulletSpeed, BYTE bulletWidth, BYTE bulletHeight, Hitbox::Shape hitboxShape, Hitbox::Size hitboxSize);

	// narysowanie wszystkich pocisków
	void Draw(RECT const & rect) override;


	virtual void StartBullets(D3DXVECTOR2 const & position) = 0;
	void Activate(float const actTime, D3DXVECTOR2 const & position)
	{
		if (!_activated && actTime >= _activationTime)
		{
			this->StartBullets(position);
			_activated = true;
		}
	}

	/// SETTERY
	virtual void SetPosition(D3DXVECTOR2 const & pos);

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

	/// PRZEKSZTA£CENIA AFINICZNE
	void Translate(D3DXVECTOR2 const & translate);
	void Scale(float const scale);
	void Rotate(float const rotate);

	/// Ustawienie wartoœci przekszta³ceñ afinicznych
	void SetTranslation(D3DXVECTOR2 const & translate);
	void SetScale(float const scale);
	void SetRotation(float const rotate);
};

