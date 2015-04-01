#include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice()
{
};

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
	// D3DADAPTER_DEFAULT = Primary display adapter (default graphics card)
	// D3DDEVTYPE_HAL = Hardware rasterization
	// D3DCREATE_MIXED_VERTEXPROCESSING = Uses both hardware and software for 3D calculations
	if ( !SUCCEEDED ( direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING, &presentationParams, &device ) ) )
	{
		return false;
	}

	return true;
};

// zwolenienie pamiêci
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


void GraphicsDevice::Clear(D3DCOLOR const & color)
{
	// 2nd param 'NULL' clears the entire back buffer.
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

// rozpoczêcie rysowania
void GraphicsDevice::Begin()
{
	device->BeginScene();
}

// zakoñczenie rysowania
void GraphicsDevice::End()
{
	device->EndScene();
}

// Zaprezentowanie naszej narysowanej sceny w oknie
void GraphicsDevice::Present()
{
	device->Present(NULL, NULL, NULL, NULL);
}

