#pragma once
#include "IPattern.h"
#include "PlayerBullet.h"

class PPattern : public IPattern
{
protected:
	/// Definicja kolejki wrogich pocisk�w
	typedef std::deque<PlayerBullet*> PBulletQue;

	//// POCISKI
	PBulletQue bullet;

	// definicja wsp�lnego wska�nika na tor
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;

	// Kontrola czasowa
	float elapsedTime;

	// uchyt do diwajsa, dla generacji nowych pocisk�w w czasie
	LPDIRECT3DDEVICE9 device;

	// pozycja wzoru
	D3DXVECTOR2 position;

	// Informuje czy gracz aktualnie strzela, czy te� nie.
	bool isKeyPressed;

	// Template'owy sprajt, do kt�rego b�dziemy si�ga� zamiast do pliku
	typedef std::shared_ptr<Sprite> SpritePtr;
	SpritePtr templateSprite;

public:
	PPattern();
	virtual ~PPattern();
	
	// przekazanie uchwytu
	virtual void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position );

	//virtual void SetPosition(D3DXVECTOR2 const & pos);

	// narysowanie wszystkich pocisk�w
	void Draw(RECT const & rect) override;
	
	// Musowa implementacja z IPattern, nie u�ywana.
	// Jak nie jak TAK XD
	// W�a�ciwa metoda aktualizuj�ca pociski dla pattern�w gracza.
	void Update(float const time, D3DXVECTOR2 const & position) override;

	void SetKeyPressed(bool isKeyPressed);

	void virtual LoadSprite();

	inline PBulletQue & GetBullets()
	{
		return bullet;
	};
	
	inline bool const IsKeyPressed()
	{
		return this->isKeyPressed;
	};

};

