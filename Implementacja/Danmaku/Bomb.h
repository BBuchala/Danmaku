#pragma once

#include "GameObject.h"

class Bomb: public GameObject
	{	
	private:

		const float maxTime;
		float elapsedTime;

		bool inUse;
		// przesuni�cie wzgl�dem �rodka gracza
		D3DXVECTOR2 shift;

	public:
		Bomb (D3DXVECTOR2 const & position, float const speed);
		Bomb ( Bomb const & bomb );
		~Bomb();


		void Initialize(LPDIRECT3DDEVICE9 device);

		void Update(float const time) override;
		// Sytuacja co z PlayerPatternem, p�ki co nie mam pomys�u jak to za�ata�.
		void Update(float const time, D3DXVECTOR2 const & position); 

		void Launch();

		inline bool InUse()
		{
			return inUse;
		}

	};
