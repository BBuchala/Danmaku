#pragma once

#include "PlayerBullet.h"
#include "PPattern.h"

class PlayerPattern01 : public PPattern
{
private:

public:
	PlayerPattern01(void);
	~PlayerPattern01(void);

	void Initialize(D3DXVECTOR2 const & position) override;
	void Update(float const time, D3DXVECTOR2 const & position) override;

	void Add(D3DXVECTOR2 const & position);

	void LoadSprite(PlayerBulletSpriteResource & pbsResource) override;
};

