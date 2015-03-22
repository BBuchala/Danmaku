#include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice()
{
	red = 0;
	green = 0;
	blue = 0;
	incRed = 1;
	incBlue = 2;
	incGreen = 3;

	timer = 0;
	interval = 15;
	bulletNumber = 1;
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
	direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &presentationParams, 
		&device);

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


bool GraphicsDevice::InitScene()
{
	// miejsce na definicjê stejd¿y, afaik
	return true;
};

// W Update znajduje siê sama zmiana stanu gry
void GraphicsDevice::UpdateScene()
{
	// Inkrementacja licznika
	// Potem trzeba zrobiæ taki globalnie
	timer++;
	if (timer % interval == 0 && bulletNumber < 20) bulletNumber++;

	// Zmiana kolorów
	red += incRed;
	green += incGreen;
	blue += incBlue;

	if (red >= 255 || red <= 0)
		incRed *= -1;
	if(green >= 255 || green <= 0)
		incGreen *= -1;
	if(blue >= 255 || blue <= 0)
		incBlue *= -1;

	// Zmiana po³o¿enia pocisków
	for (int i = 0; i < bulletNumber; i++)
	{
		bullet[i]->move();
	}

};

// Narysowanie zmian
void GraphicsDevice::DrawScene()
{
	// wyczyszczenie ca³ej planszy i przekazanie nowego koloru t³a
	this->Clear(D3DCOLOR_XRGB(red, green, blue));
	this->Begin();

	for (int i = 0; i < bulletNumber; i++)
	{
		bullet[i]->sprite->Draw();
	}

	this->End();
	this->Present();
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

// pêtla g³ówna Diwajsa, rysuje i aktualizuje
int GraphicsDevice::messageloop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);	
			DispatchMessage(&msg);
		}
		else
		{
			// TODO: kod naszej gry
			UpdateScene();
			DrawScene();
            
		}
	}
	return msg.wParam;
};

// dodanie pocisku, tymczasowe
void GraphicsDevice::addBullet( Bullet ** bullet )
{
	this->bullet = bullet;
};