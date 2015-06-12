#pragma once

#include "GameObject.h"

#undef DEBUG

class Bomb: public GameObject
	{	
	private:

		const float maxTime;
		float elapsedTime;

		const unsigned short damage;

		bool inUse;
		// przesuniêcie wzglêdem œrodka gracza
		D3DXVECTOR2 shift;
		D3DXVECTOR2 * _playerPosition;	// wskaŸnik na pozycjê gracza
#ifdef DEBUG
		Sprite * tmp;
#endif
	public:
		Bomb (D3DXVECTOR2 * const playerPosition, float const speed);
		Bomb ( Bomb const & bomb );
		~Bomb();

		void Initialize(LPDIRECT3DDEVICE9 device);
		void Update(float const time) override;
		void Draw( RECT const & rect ) override;

		void Launch();

		inline bool InUse()
		{
			return inUse;
		}

		inline unsigned short GetDamage() const
		{
			return this->damage;
		}

	};
