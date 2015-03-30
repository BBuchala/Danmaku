/* ======================================================== *\
 *  @GraphicsDevice.cpp
 *  @Opis: obs³uga i kontrola urz¹dzenia graficznego
 *  @Utworzona: 21.03.2015 21:52
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#pragma once

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

public:
	GraphicsDevice();

	// utworzenie w³aœciwego obiektu Device
	bool Initialize(HWND & hWnd, bool windowed);

	void ReleaseObjects();

	bool InitScene();

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
