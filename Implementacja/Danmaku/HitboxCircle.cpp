#include "HitboxCircle.h"

HitboxCircle::HitboxCircle( Hitbox::Size size, float radius, D3DXVECTOR2 * const position ) : Hitbox(position)
{
	float divisor = GetDivisor(size);
	_radius = radius / divisor;
};


void HitboxCircle::Scale( float const scale )
{
	_radius *= scale;
};


bool HitboxCircle::TestCollision(Hitbox * collider, USHORT grazeDistance)
{
	HitboxCircle * hCircle = dynamic_cast<HitboxCircle*>(collider);
	if (hCircle != NULL)
	{
		float distance = Vector::Length(*_position, collider->GetPosition());
		if (distance <= _radius + hCircle->GetRadius() + grazeDistance)
		{
			return true;
		}
		return false;
	}
	HitboxElipse * hElipse = dynamic_cast<HitboxElipse*>(collider);
	if (hElipse != NULL)
	{
		float distance = Vector::Length(hElipse->GetPosition(), *_position);
		float angle = Vector::Angle( *_position, hElipse->GetPosition());
		float radialLength = hElipse->GetRadialLength(angle);
		float maxDistance = _radius + radialLength + grazeDistance;
		if (distance <= maxDistance)
		{
			return true;
		}
		return false;
	}
	return false;
};


Hitbox * HitboxCircle::Clone()
{
	return new HitboxCircle(*this);
};
