#pragma once
#include "IPattern.h"
#include "PlayerBullet.h"
#include "PlayerBulletSpriteResource.h"
#include "PlayerBulletInitializationFailedException.h"

/// <summary>
/// Klasa nadrzêdna dla wzorów gracza
/// </summary>
class PlayerPattern : public IPattern
{
protected:
	/// Definicja kolejki wrogich pocisków
	typedef std::deque<PlayerBullet*> PBulletQue;

	//// POCISKI
	PBulletQue bullet;

	// definicja wspólnego wskaŸnika na tor
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;

	// Kontrola czasowa
	float elapsedTime;

	// wskaŸnik pozycjê wzoru
	D3DXVECTOR2 * position;

	// Informuje czy gracz aktualnie strzela, czy te¿ nie.
	bool isKeyPressed;

	// Template'owy sprajt, do którego bêdziemy siêgaæ zamiast do pliku
	typedef std::shared_ptr<Sprite> SpritePtr;
	SpritePtr templateSprite;

public:
	PlayerPattern();
	virtual ~PlayerPattern();
	
	// przekazanie uchwytu
	void SetPositionPtr(D3DXVECTOR2 * const position) override;

	// narysowanie wszystkich pocisków
	void Draw(RECT const & rect) override;
	
	// W³aœciwa metoda aktualizuj¹ca pociski dla patternów gracza.
	void Update(float const time) override;

	void SetKeyPressed(bool isKeyPressed);

	void virtual LoadSprite(PlayerBulletSpriteResource & pbsResource) = 0;

	/// <summary>
	/// Zwrócenie wszystkich przycisków.
	/// </summary>
	/// <returns></returns>
	inline PBulletQue & GetBullets()
	{
		return bullet;
	};
	
	/// <summary>
	/// Czy klawisz strza³u zosta³ wciœniêty.
	/// </summary>
	/// <returns></returns>
	inline bool const IsKeyPressed()
	{
		return this->isKeyPressed;
	};

protected:
	void LoadBulletType(SpritePtr & sprite, std::string const & file, PlayerBulletSpriteResource & pbsResource);
};

