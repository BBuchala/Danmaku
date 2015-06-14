#pragma once

#include "GameObject.h"
#include "BombInitializationFailedException.h"

#undef DEBUG

/// <summary>
/// Bomba, kt�rej mo�e u�ywac gracz
/// </summary>
class Bomb: public GameObject
	{	
	private:
		const float maxTime;
		float elapsedTime;

		const unsigned short damage;

		bool inUse;
		// przesuni�cie wzgl�dem �rodka gracza
		D3DXVECTOR2 shift;
		D3DXVECTOR2 * _playerPosition;	// wska�nik na pozycj� gracza
#ifdef DEBUG
		Sprite * tmp;
#endif
	public:
		Bomb (D3DXVECTOR2 * const playerPosition, float const speed);
		Bomb ( Bomb const & bomb );
		~Bomb();

		bool Initialize(LPDIRECT3DDEVICE9 device);
		void Update(float const time) override;
		void Draw( RECT const & rect ) override;

		void Launch();

		/// <summary>
		/// Czy bomba jest wykorzystywana.
		/// </summary>
		/// <returns></returns>
		inline bool InUse()
		{
			return inUse;
		}

		/// <summary>
		/// Zwr�cenie obra�e� jakie zadaje.
		/// </summary>
		/// <returns></returns>
		inline unsigned short GetDamage() const
		{
			return this->damage;
		}

	};
