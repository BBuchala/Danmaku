#include "PlayerPattern.h"


/// <summary>
/// Tworzy nowπ instacjÍ klasy <see cref="PlayerPattern"/>.
/// </summary>
PlayerPattern::PlayerPattern(): elapsedTime(0.0f)
{
}

/// <summary>
/// Niszczy instancjÍ klasy <see cref="PlayerPattern"/>.
/// </summary>
PlayerPattern::~PlayerPattern(void)
{
	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		delete *it;
	}
}

/// <summary>
/// Przekazujπc wzorowi wskaünik do pozycji, z ktÛrej zawsze ma strzelaÊ.
/// </summary>
/// <param name="position">Pozycja strzelania.</param>
void PlayerPattern::SetPositionPtr(D3DXVECTOR2 * const position)
{
	this->position = position;
};

/// <summary>
/// Narysowanie
/// </summary>
/// <param name="rect">Protokπt w ktÛrym sprajt moøe byÊ rysowany.</param>
void PlayerPattern::Draw( RECT const & rect )
{
	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Draw(rect);
	}
};

/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">PrÛbka czasu.</param>
void PlayerPattern::Update(float const time)
{
	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
};


/// <summary>
/// Ustaw czy przycisk strza≥u zosta≥ wciúniÍty lub nie.
/// </summary>
/// <param name="isKeyPressed">Jeúli tak, to zosta≥ wciúniÍty.</param>
void PlayerPattern::SetKeyPressed(bool isKeyPressed)
{
	this->isKeyPressed = isKeyPressed;
};

/// <summary>
/// Za≥adowanie sprajtÛw dla typu pociskÛw we wzorze.
/// </summary>
/// <param name="sprite">Sprajt.</param>
/// <param name="name">Nazwa sprajtu.</param>
/// <param name="pbsResource">èrÛd≥o sprajtÛw.</param>
void PlayerPattern::LoadBulletType(SpritePtr & sprite, std::string const & name, PlayerBulletSpriteResource & pbsResource)
{
	SpritePtr spt = pbsResource[name];
	if (spt != nullptr)
		sprite = pbsResource[name];
	else
		throw PlayerBulletInitializationFailedException();
};
