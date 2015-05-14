#pragma once

#include "EPattern.h"

class EnemyPatternEllipse: public EPattern
{
	/// Sk�adowe potrzebne do generowania pocisk�w
	float _radiusA;
	float _radiusB;

	bool _initialized;

public:
	EnemyPatternEllipse(float const radius, float const number, float const interval);
	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void InitializeBullets(std::string bulletImage, float bulletSpeed, BYTE bulletWidth, BYTE bulletHeight, Hitbox::Shape hitboxShape, Hitbox::Size hitboxSize);
	void Update(float const time, D3DXVECTOR2 const & position) override;

	void AddBullet(D3DXVECTOR2 const & position);
};

