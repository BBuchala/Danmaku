#include "HitboxElipse.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="HitboxElipse"/>.
/// </summary>
/// <param name="size">Rozmiar.</param>
/// <param name="radiusA">Pierwsza pó³-oœ.</param>
/// <param name="radiusB">Druga pó³-oœ.</param>
/// <param name="position">Pozycja.</param>
HitboxElipse::HitboxElipse(  Hitbox::Size size, float radiusA, float radiusB, D3DXVECTOR2 * const position )
	 : Hitbox(position)
{
	float divisor = GetDivisor(size);
	_radiusA = radiusA / divisor;
	_radiusB = radiusB / divisor;
};


/// <summary>
/// Skaluje hitbox
/// </summary>
/// <param name="scale">skala.</param>
void HitboxElipse::Scale( float const scale )
{
	_radiusA *= scale;
	_radiusB *= scale;
};

/// <summary>
/// Sprawdza czy nast¹pi³a kolizja z przekazanym hitboxem
/// </summary>
/// <param name="collider">Drugi hitbox.</param>
/// <param name="grazeDistance">Grejz dystans.</param>
/// <returns></returns>
bool HitboxElipse::TestCollision(Hitbox * collider, USHORT grazeDistance)
{
	HitboxCircle * hCircle = dynamic_cast<HitboxCircle*>(collider);
	if (hCircle != NULL)
	{
		float distance = Vector::Length(*_position, hCircle->GetPosition());
		float angle = Vector::Angle(*_position, hCircle->GetPosition());
		float radialLength = this->GetRadialLength(angle);
		float maxDistance = radialLength + hCircle->GetRadius() + grazeDistance;
		if (distance <= maxDistance)
		{
			return true;
		}
		return false;
	}
	HitboxElipse * hElipse = dynamic_cast<HitboxElipse*>(collider);
	if (hElipse != NULL)
	{
		float distance = Vector::Length(*_position, hElipse->GetPosition());
		float angle = Vector::Angle(hElipse->GetPosition(), *_position);
		float radialLengthThis = this->GetRadialLength(angle);
		float radialLengthOther = hElipse->GetRadialLength(angle);
		float maxDistance = radialLengthThis + radialLengthOther + grazeDistance;
		if (distance <= maxDistance)
		{
			return true;
		}
		return false;
	}
	return false;
};


/// <summary>
/// Klonuje ten hitbox
/// </summary>
/// <returns></returns>
Hitbox * HitboxElipse::Clone()
{
	return new HitboxElipse(*this);
};
