#pragma once
#include "EPattern.h"
#include "PlayerBullet.h"

class PlayerPattern : public EPattern
{
private:
	TrajectoryPtr line1;

public:
	PlayerPattern(void);
	~PlayerPattern(void);

	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void Update(float const time) override;
	void Update(float const time, bool pressedKey, D3DXVECTOR2 const & position);

	void Add(D3DXVECTOR2 const & position);
};

