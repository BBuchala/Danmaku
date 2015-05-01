#pragma once

#include "GameObject.h"
#include "TrajectoryFactory.h"

class Bonus: public GameObject
{
protected:
	// definicja wspólnego wskaŸnika na tor
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;
	TrajectoryPtr trajectory;

	float distance;
	std::string fileName;				// Nazwa pliku, z którego pobierany bêdzie sprite. Definiowana w klasach pochodnych

public:
	// KONSTRUKTORY I DESTRUKTOR
	Bonus (D3DXVECTOR2 const & position, float const speed, std::string fileName);
	Bonus ( Bonus const & bonus );
	virtual ~Bonus();

	// METODA INICJALIZUJ¥CA SPRITE
	bool Initialize(LPDIRECT3DDEVICE9 device);												

	virtual byte getBonusCode() = 0;			// Mo¿na by zrobiæ jako zwyk³¹ zmienn¹ typu bajtowego
												// ale wtedy klasa nie bêdzie abstrakcyjna, a Forczu chcia³, by by³a :<
	// METODA DO AKTUALIZACJI POZYCJI OBIEKTU
	void Update(float const time) override;

	// METODA SPRAWDZAJ¥CA, CZY BONUS ZNAJDUJE SIÊ W OBSZARZE GRY
	bool isBonusWithinBounds(const short x, const short y, const short width, const short height);

	inline Trajectory * const GetTrajectory() const
	{
		return trajectory.get();
	}
};