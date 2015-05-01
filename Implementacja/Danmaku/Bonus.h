#pragma once

#include "GameObject.h"
#include "TrajectoryFactory.h"

class Bonus: public GameObject
{
protected:
	// definicja wsp�lnego wska�nika na tor
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;
	TrajectoryPtr trajectory;

	float distance;
	std::string fileName;				// Nazwa pliku, z kt�rego pobierany b�dzie sprite. Definiowana w klasach pochodnych

public:
	// KONSTRUKTORY I DESTRUKTOR
	Bonus (D3DXVECTOR2 const & position, float const speed, std::string fileName);
	Bonus ( Bonus const & bonus );
	virtual ~Bonus();

	// METODA INICJALIZUJ�CA SPRITE
	bool Initialize(LPDIRECT3DDEVICE9 device);												

	virtual byte getBonusCode() = 0;			// Mo�na by zrobi� jako zwyk�� zmienn� typu bajtowego
												// ale wtedy klasa nie b�dzie abstrakcyjna, a Forczu chcia�, by by�a :<
	// METODA DO AKTUALIZACJI POZYCJI OBIEKTU
	void Update(float const time) override;

	// METODA SPRAWDZAJ�CA, CZY BONUS ZNAJDUJE SI� W OBSZARZE GRY
	bool isBonusWithinBounds(const short x, const short y, const short width, const short height);

	inline Trajectory * const GetTrajectory() const
	{
		return trajectory.get();
	}
};