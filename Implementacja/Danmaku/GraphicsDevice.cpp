#include "GraphicsDevice.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="GraphicsDevice"/>.
/// </summary>
GraphicsDevice::GraphicsDevice()
{
};

/// <summary>
/// Utworzenie w³aœciwego obiektu Device
/// </summary>
/// <param name="hWnd">Uchwyt do okna.</param>
/// <param name="windowed">Jeœli <c>true</c> [uruchomiony w oknie].</param>
/// <returns></returns>
bool GraphicsDevice::Initialize(HWND & hWnd, bool windowed)
{
	// utworznie wskaŸnika do Direct 3D
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS presentationParams;
	ZeroMemory(&presentationParams, sizeof(presentationParams));
	presentationParams.Windowed = windowed;
	presentationParams.SwapEffect = D3DSWAPEFFECT_DISCARD; // fastest
	presentationParams.hDeviceWindow = hWnd; // nasze okno
	
	// utworzenie diwajsa
	if ( !SUCCEEDED ( direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING, &presentationParams, &device ) ) )
	{
		return false;
	}

	return true;
};

/// <summary>
/// Zwolenienie pamiêci
/// </summary>
void GraphicsDevice::ReleaseObjects()
{
	if (this->device)
	{
		this->device->Release();
	}

	if (this->direct3d)
	{
		this->direct3d->Release();
	}
};


/// <summary>
/// Wyczyszczenie diwajsa
/// </summary>
/// <param name="color">Kolor.</param>
void GraphicsDevice::Clear(D3DCOLOR const & color)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

/// <summary>
/// Rozpoczêcie rysowania
/// </summary>
void GraphicsDevice::Begin()
{
	device->BeginScene();
}

/// <summary>
/// Zakoñczenie rysowania
/// </summary>
void GraphicsDevice::End()
{
	device->EndScene();
}

/// <summary>
/// Zaprezentowanie naszej narysowanej sceny w oknie
/// </summary>
void GraphicsDevice::Present()
{
	device->Present(NULL, NULL, NULL, NULL);
}

