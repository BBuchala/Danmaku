/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, który porusza siê po elipsie
 *  @Utworzona: 22.03.2015 13:48
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#pragma once

#include "GameObject.h"


class Bullet : public GameObject
{
public:
	Bullet( float const & x, float const & y );
	virtual ~Bullet();

	bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height) override;
	bool Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, int const & width, int const & height) override;
};



