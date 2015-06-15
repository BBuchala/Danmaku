#include "EnemyPattern.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="EnemyPattern"/>.
/// </summary>
/// <param name="activationTime">Czas po kt�rym wz�r zostaje aktywowany.</param>
EnemyPattern::EnemyPattern(float const activationTime) : _activationTime(activationTime), _activated(false),
	 _bulletScale(1.0f), _bulletRotate(0.0f), _scaleStep(1.0f), _rotateStep(0.0f)
{
	_translate = D3DXVECTOR2(0.0f, 0.0f);
	_rotate = 0.0f;
	_scale = 1.0f;
};

/// <summary>
/// <summary>
/// Tworzy kopi� instacji klasy <see cref="EnemyPattern"/>.
/// </summary>
/// <param name="pattern">Obiekt do skopiowania</param>
EnemyPattern::EnemyPattern(EnemyPattern const & pattern)
{
	_translate = pattern._translate;
	_rotate = pattern._rotate;
	_scale = pattern._scale;
	_activationTime = pattern._activationTime;
	_activated = pattern._activated;
	_bulletScale = pattern._bulletScale;
	_bulletRotate = pattern._bulletRotate;
	_scaleStep = pattern._scaleStep;
	_rotateStep = pattern._rotateStep;
	_position = pattern._position;
	_bulletSprite = pattern._bulletSprite;
	_bulletSpeed = pattern._bulletSpeed;
	_bulletAcc = pattern._bulletAcc;
	_bulletWidth = pattern._bulletWidth;
	_bulletHeight = pattern._bulletHeight;
	_hitboxShape = pattern._hitboxShape;
	_hitboxSize = pattern._hitboxSize;
	_scaleStep = pattern._scaleStep;
	_rotateStep = pattern._rotateStep;
	_bulletScale = pattern._bulletScale;
	_bulletRotate = pattern._bulletRotate;
	_number = pattern._number;
	_interval = pattern._interval;
};

/// <summary>
/// Niszczy instancj� klasy <see cref="EnemyPattern"/>.
/// </summary>
EnemyPattern::~EnemyPattern()
{
	for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
	{
		delete *it;
	}
};

/// <summary>
/// Przekazuj�c wzorowi wska�nik do pozycji, z kt�rej zawsze ma strzela�.
/// </summary>
/// <param name="position">Pozycja strzelania.</param>
void EnemyPattern::SetPositionPtr(D3DXVECTOR2 * const position)
{
	_position = position;
};

/// <summary>
/// Inicjalizuje pociski odpowiednimi warto�ciami.
/// </summary>
/// <param name="bulletSprite">Sprajt dla pocisk�w.</param>
/// <param name="bulletSpeed">Pr�dko�� pocisk�w.</param>
/// <param name="bulletAcc">Przyspieszenie pocisk�w.</param>
/// <param name="bulletWidth">Szeroko�� sprajtu pocisk�w.</param>
/// <param name="bulletHeight">Wysoko�� sprajtu pocisk�w.</param>
/// <param name="hitboxShape">Kszta�t hitboxa.</param>
/// <param name="hitboxSize">Rozmiar hitboxa.</param>
/// <param name="bulletScale">Skala dla pocisk�ws.</param>
/// <param name="bulletRotate">Pocz�tkowy obr�t pocisk�w.</param>
void EnemyPattern::InitializeBullets(std::shared_ptr<Sprite> bulletSprite, float bulletSpeed, float bulletAcc,
								 BYTE bulletWidth, BYTE bulletHeight, Hitbox::Shape hitboxShape,
								 Hitbox::Size hitboxSize, float bulletScale, float bulletRotate)
{
	_bulletSprite = bulletSprite;
	_bulletSpeed = bulletSpeed;
	_bulletAcc = bulletAcc;
	_bulletWidth = bulletWidth;
	_bulletHeight = bulletHeight;
	_hitboxShape = hitboxShape;
	_hitboxSize = hitboxSize;
	_bulletScale = bulletScale;
	_bulletRotate = bulletRotate;
};

/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">Pr�bka czasu.</param>
void EnemyPattern::Update(float const time)
{
	this->_scale += _scaleStep;
	this->_rotate += _rotateStep;
	for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
	{
		(*it)->Scale(_bulletScale);
		(*it)->Rotate(_bulletRotate);
		(*it)->Update(time);
	}
};

/// <summary>
/// Narysowanie
/// </summary>
/// <param name="rect">Protok�t w kt�rym sprajt mo�e by� rysowany.</param>
void EnemyPattern::Draw( RECT const & rect )
{
	for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
	{
		(*it)->Draw(rect);
	}
};


/// <summary>
/// Przesuwa obiekt.
/// </summary>
/// <param name="dv">Przesuni�cie.</param>
void EnemyPattern::Translate(D3DXVECTOR2 const & translate)
{
	_translate += translate;
};

/// <summary>
/// Zmienia rozmiar wg skali.
/// </summary>
/// <param name="scale">Skala.</param>
void EnemyPattern::Scale(float const scale)
{
	_scale *= scale;
};

/// <summary>
/// Obraca obiekt o wskazany k�t.
/// </summary>
/// <param name="angle">K�t.</param>
void EnemyPattern::Rotate(float const rotate)
{
	_rotate += rotate;
};

/// <summary>
/// Ustawia nowe przesuni�cie dla wzoru.
/// </summary>
/// <param name="dv">Przesuni�cie.</param>
void EnemyPattern::SetTranslation(D3DXVECTOR2 const & translate)
{
	_translate = translate;
};

/// <summary>
/// Ustawia now� skal� dla wzoru.
/// </summary>
/// <param name="dv">Skala.</param>
void EnemyPattern::SetScale(float const scale)
{
	_scale = scale;
};

/// <summary>
/// Ustawia nowy obr�t dla wzoru.
/// </summary>
/// <param name="angle">K�t.</param>
void EnemyPattern::SetRotation(float const rotate)
{
	_rotate = rotate;
};

/// <summary>
/// Ustawia now� skal� dla pocisk�w.
/// </summary>
/// <param name="dv">Pozycja.</param>
void EnemyPattern::SetBulletScale(float scale)
{
	_bulletScale = scale;
};

/// <summary>
/// Ustawia nowy obr�t dla pocisk�w.
/// </summary>
/// <param name="angle">K�t.</param>
void EnemyPattern::SetBulletRotation(float rotate)
{
	_bulletRotate = rotate;
};


/// <summary>
/// Aktywacja wzoru je�li przekazany czas jest wi�kszy od czasu aktywacji.
/// </summary>
/// <param name="actTime">Aktualny czas aktywacji.</param>
void EnemyPattern::Activate(float const actTime)
{
	if (!_activated && actTime >= _activationTime)
	{
		this->StartBullets();
		_activated = true;
	}
};
