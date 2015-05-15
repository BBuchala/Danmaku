#pragma once

#include "GameObject.h"

namespace
{
	class Bomb: public GameObject
	{	
	private:

		const float maxTime;
		float elapsedTime;

	public:
		Bomb (D3DXVECTOR2 const & position, float const value, float const speed, std::string fileName);
		Bomb ( Bomb const & bomb );
		~Bomb();


		bool Initialize(LPDIRECT3DDEVICE9 device);

		void Update(float const time) override;

	};
}