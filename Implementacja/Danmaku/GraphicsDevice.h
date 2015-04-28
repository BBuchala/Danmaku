/* ======================================================== *\
 *  @GraphicsDevice.cpp
 *  @Opis: obs�uga i kontrola urz�dzenia graficznego
 *  @Utworzona: 21.03.2015 21:52
 *  @Autor: Mateusz Forczma�ski
\* ======================================================== */

#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Direct3DInitializationFailedException.h"

class GraphicsDevice
{
public:
	// uchywty do urz�dze� DirectXa
	LPDIRECT3DDEVICE9 device;
	LPDIRECT3D9 direct3d;

private:

public:
	GraphicsDevice();

	// utworzenie w�a�ciwego obiektu Device
	bool Initialize(HWND & hWnd, bool const windowed);

	void ReleaseObjects();

	// funkcje do prezentacji ekranu
	void Clear(D3DCOLOR const & color);
	void Begin();
	void End();
	void Present();

};
