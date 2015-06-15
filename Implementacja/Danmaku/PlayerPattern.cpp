#include "PlayerPattern.h"


/// <summary>
/// Tworzy now� instacj� klasy <see cref="PlayerPattern"/>.
/// </summary>
PlayerPattern::PlayerPattern(): elapsedTime(0.0f)
{
}

/// <summary>
/// Niszczy instancj� klasy <see cref="PlayerPattern"/>.
/// </summary>
PlayerPattern::~PlayerPattern(void)
{
	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		delete *it;
	}
}

/// <summary>
/// Przekazuj�c wzorowi wska�nik do pozycji, z kt�rej zawsze ma strzela�.
/// </summary>
/// <param name="position">Pozycja strzelania.</param>
void PlayerPattern::SetPositionPtr(D3DXVECTOR2 * const position)
{
	this->position = position;
};

/// <summary>
/// Narysowanie
/// </summary>
/// <param name="rect">Protok�t w kt�rym sprajt mo�e by� rysowany.</param>
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
/// <param name="time">Pr�bka czasu.</param>
void PlayerPattern::Update(float const time)
{
	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
};


/// <summary>
/// Ustaw czy przycisk strza�u zosta� wci�ni�ty lub nie.
/// </summary>
/// <param name="isKeyPressed">Je�li tak, to zosta� wci�ni�ty.</param>
void PlayerPattern::SetKeyPressed(bool isKeyPressed)
{
	this->isKeyPressed = isKeyPressed;
};

/// <summary>
/// Za�adowanie sprajt�w dla typu pocisk�w we wzorze.
/// </summary>
/// <param name="sprite">Sprajt.</param>
/// <param name="name">Nazwa sprajtu.</param>
/// <param name="pbsResource">�r�d�o sprajt�w.</param>
void PlayerPattern::LoadBulletType(SpritePtr & sprite, std::string const & name, PlayerBulletSpriteResource & pbsResource)
{
	SpritePtr spt = pbsResource[name];
	if (spt != nullptr)
		sprite = pbsResource[name];
	else
		throw PlayerBulletInitializationFailedException();
};
