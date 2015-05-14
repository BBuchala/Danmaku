#pragma once

#include "Bonuses.h"
#include "GameObject.h"
#include "TrajectoryFactory.h"

class Bonus: public GameObject
{
protected:
	// definicja wspólnego wskaŸnika na tor
	typedef Trajectory* TrajectoryPtr;
	TrajectoryPtr trajectory;

	float distance;
	std::string fileName;				// Nazwa pliku, z którego pobierany bêdzie sprite. Definiowana w klasach pochodnych

	float value;
	bool _vacuumed;

public:
	// KONSTRUKTORY I DESTRUKTOR
	Bonus (D3DXVECTOR2 const & position, float const value, float const speed, std::string fileName);
	Bonus ( Bonus const & bonus );
	virtual ~Bonus();

	// METODA INICJALIZUJ¥CA SPRITE
	bool Initialize(LPDIRECT3DDEVICE9 device);

	// METODA DO AKTUALIZACJI POZYCJI OBIEKTU
	void Update(float const time) override;

	// METODA SPRAWDZAJ¥CA, CZY BONUS ZNAJDUJE SIÊ W OBSZARZE GRY
	bool isBonusWithinBounds(const short x, const short y, const short width, const short height);

	virtual Bonuses GetBonusId() const = 0;

	void SetDistance(float const distance)
	{
		this->distance = distance;
	}

	virtual inline float Realize() const
	{
		return value;
	}

	inline Trajectory * const GetTrajectory() const
	{
		return trajectory;
	}

	inline bool IsVacuumed() const
	{
		return _vacuumed;
	}

	void SetTrajectoryTowardsPlayer(D3DXVECTOR2 const & position)
	{
		this->GetTrajectory()->SetTrajectoryTowardsPlayer(GetCenterPoint(), position);
		if (!_vacuumed)
		{
			this->SetDistance(0.0f);
			_vacuumed = true;
		}
	};
};
