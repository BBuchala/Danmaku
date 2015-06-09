#include "HitboxElipse.h"

HitboxElipse::HitboxElipse(  Hitbox::Size size, float radiusA, float radiusB, D3DXVECTOR2 * const position )
	 : Hitbox(position)
{
	float divisor = GetDivisor(size);
	_radiusA = radiusA / divisor;
	_radiusB = radiusB / divisor;
};


void HitboxElipse::Scale( float const scale )
{
	_radiusA *= scale;
	_radiusB *= scale;
};

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


Hitbox * HitboxElipse::Clone()
{
	return new HitboxElipse(*this);
};
