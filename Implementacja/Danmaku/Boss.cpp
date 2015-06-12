#pragma once

#include "Boss.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="Boss"/>.
/// </summary>
/// <param name="position">Pozycja.</param>
/// <param name="life">¯ycie.</param>
/// <param name="name">Imiê.</param>
Boss::Boss( D3DXVECTOR2 const & position, USHORT const life, std::string const & name )
		: GameObject(position), isShooting_(true), waitTime_(3.0f), currentSc_(1), name_(name), MAX_LIFE(life), life_(life), scId(1)
{
}
/// <summary>
/// Niszczy instancjê klasy <see cref="Boss"/>.
/// </summary>
Boss::~Boss()
{
}

/// <summary>
/// Narysowanie bossa
/// </summary>
/// <param name="rect">Protok¹t w którym sprajt mo¿e byæ rysowany.</param>
void Boss::Draw(RECT const & rect)
{
	GameObject::Draw(rect);
}

/// <summary>
/// Aktualizuje stan
/// </summary>
/// <param name="time">Próbka czasu.</param>
void Boss::Update( float const time )
{
	GameObject::Update(time);
	if (isShooting_)
	{
		if (_spellcard[currentSc_])
			if (_spellcard[currentSc_]->IsSpellcardFinished())
			{
				//delete _spellcard[currentSc_++];
			}
	}
}

/// <summary>
/// Zwraca spellcard.
/// </summary>
/// <returns></returns>
Spellcard * Boss::GetSpellcard()
{
	return _spellcard[currentSc_];
}

/// <summary>
/// Otrzymuje obra¿enia i odejmuje ich wartoœæ od punktów ¿ycia.
/// </summary>
/// <param name="damage">Obra¿enia.</param>
void Boss::TakeDamage( USHORT const damage )
{
	if (life_ - damage < 0  )
		life_ = 0;
	else
		life_ -= damage;
}

/// <summary>
/// Ustawia czy boss aktualnie strzela.
/// </summary>
/// <param name="isShooting">Czy strzela.</param>
void Boss::SetIsShooting(bool const isShooting)
{
	isShooting_ = isShooting;
}

/// <summary>
/// Dodaje spellcard do zbioru.
/// </summary>
/// <param name="spellcard">The spellcard.</param>
void Boss::AddSpellcard(Spellcard * const spellcard)
{
	_spellcard[scId] = spellcard;
	_spellcard[scId]->Activate(this->GetCenterPoint());
	scId++;
}

/// <summary>
/// Inicjalizacja patternów.
/// </summary>
/// <returns>Czy siê uda³o</returns>
bool Boss::InitializePatterns()
{
	for (SpellcardMap::const_iterator it = _spellcard.begin(); it != _spellcard.end(); ++it)
	{
		(*it).second->Initialize(this->GetCenterPoint());
	}
	return true;
};