#pragma once
#include "IPattern.h"
#include "PlayerBullet.h"
#include "PlayerBulletSpriteResource.h"
#include "PlayerBulletInitializationFailedException.h"

/// <summary>
/// Klasa nadrz�dna dla wzor�w gracza
/// </summary>
class PlayerPattern : public IPattern
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

	// wska�nik pozycj� wzoru
	D3DXVECTOR2 * position;

	// Informuje czy gracz aktualnie strzela, czy te� nie.
	bool isKeyPressed;

	// Template'owy sprajt, do kt�rego b�dziemy si�ga� zamiast do pliku
	typedef std::shared_ptr<Sprite> SpritePtr;
	SpritePtr templateSprite;

public:
	PlayerPattern();
	virtual ~PlayerPattern();
	
	// przekazanie uchwytu
	void SetPositionPtr(D3DXVECTOR2 * const position) override;

	// narysowanie wszystkich pocisk�w
	void Draw(RECT const & rect) override;
	
	// W�a�ciwa metoda aktualizuj�ca pociski dla pattern�w gracza.
	void Update(float const time) override;

	void SetKeyPressed(bool isKeyPressed);

	void virtual LoadSprite(PlayerBulletSpriteResource & pbsResource) = 0;

	/// <summary>
	/// Zwr�cenie wszystkich przycisk�w.
	/// </summary>
	/// <returns></returns>
	inline PBulletQue & GetBullets()
	{
		return bullet;
	};
	
	/// <summary>
	/// Czy klawisz strza�u zosta� wci�ni�ty.
	/// </summary>
	/// <returns></returns>
	inline bool const IsKeyPressed()
	{
		return this->isKeyPressed;
	};

protected:
	void LoadBulletType(SpritePtr & sprite, std::string const & file, PlayerBulletSpriteResource & pbsResource);
};

