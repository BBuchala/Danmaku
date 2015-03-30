#include "Sprite.h"

Sprite::Sprite()
{
	// When color is set to white, what you see is exactly what the image looks like.
	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	// We are not initialized yet
	initialized = false;
};

bool Sprite::Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height)
{
	//Same functionality as D3DXCreateTextureFromFile EXCEPT width and height are manually entered
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(device, file.c_str(), 
		width, height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, 0, NULL, NULL, &tex)))
	{
		std::string s = "There was an issue creating the Texture.  Make sure the requested image is available.  Requested image: " + file;
		MessageBox(NULL, s.c_str(), NULL, NULL); 
		return false;
	}

	//Attempt to create the sprite
	if(!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "There was an issue creating the Sprite.", NULL, NULL);
		return false;
	}

	this->width = width;
	this->height = height;

	initialized = true;

	return true;
};

bool Sprite::IsInitialized()
{
	return initialized;
};


void Sprite::Draw(D3DXVECTOR3 const & position)
{
	if(this->sprite && this->tex)
	{
		this->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		this->sprite->Draw(this->tex, NULL, NULL, &position, this->color);

		this->sprite->End();
	}
};

Sprite::~Sprite()
{
	if (sprite)
	{
		sprite->Release();
		sprite = 0;
	}

	if (tex)
	{
		tex->Release();
		tex = 0;
	}
};
