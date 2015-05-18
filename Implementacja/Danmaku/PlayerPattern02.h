#pragma once
#include "EPattern.h"
#include "PlayerBullet.h"
#include "PPattern.h"

class PlayerPattern02 : public PPattern
{
public:
	PlayerPattern02(void);
	~PlayerPattern02(void);

	void Initialize(D3DXVECTOR2 const & position) override;
	void Update(float const time, D3DXVECTOR2 const & position) override;

	void Add(D3DXVECTOR2 const & position);

	void LoadSprite(PlayerBulletSpriteResource & pbsResource) override;
};

