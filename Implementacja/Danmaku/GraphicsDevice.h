/* ======================================================== *\
 *  @GraphicsDevice.cpp
 *  @Opis: obs³uga i kontrola urz¹dzenia graficznego
 *  @Utworzona: 21.03.2015 21:52
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#ifndef GAMEDEVICE_H
#define GAMEDEVICE_H

#include <d3d9.h>
#include <d3dx9.h>
#include "Bullet.h"

#include "Direct3DInitializationFailedException.h"
#include "SceneInitializationFailedException.h"

class GraphicsDevice
{
public:
	// uchywty do urz¹dzeñ DirectXa
	LPDIRECT3DDEVICE9 device;
	LPDIRECT3D9 direct3d;

private:
	// zmiana koloru t³a
	unsigned short red;
	unsigned short green;
	unsigned short blue;
	short incRed;
	short incGreen;
	short incBlue;

	// pociski
	Bullet ** bullet;

	// tymczasowy timer
	unsigned long timer;
	unsigned int interval;
	unsigned bulletNumber;

public:
	GraphicsDevice();

	// utworzenie w³aœciwego obiektu Device
	bool Initialize(HWND & hWnd, bool windowed);

	void ReleaseObjects();

	bool InitScene();

	int messageloop();

	void addBullet( Bullet ** bullet );

	// funkcje do prezentacji ekranu
	void Clear(D3DCOLOR const & color);
	void Begin();
	void End();
	void Present();


private:
	// aktualizacja ekranu gry
	void UpdateScene();

	// narysowanie ekranu gry
	void DrawScene();

};

#endif