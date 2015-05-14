#pragma once

#include "EPattern.h"

class EnemyPatternEllipse: public EPattern
{
	/// Sk³adowe potrzebne do generowania pocisków
	float _radiusA;
	float _radiusB;

public:
	EnemyPatternEllipse(float const radiusA, float const radiusB, float const number, float const activationTime);
	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void InitializeBullets(std::string bulletImage, float bulletSpeed, BYTE bulletWidth, BYTE bulletHeight, Hitbox::Shape hitboxShape, Hitbox::Size hitboxSize);
	void Update(float const time, D3DXVECTOR2 const & position) override;

	void AddBullet(D3DXVECTOR2 const & position);

	void Scale();
};

