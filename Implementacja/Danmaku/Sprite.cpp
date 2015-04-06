#include "Sprite.h"

Sprite::Sprite()
{
	// When color is set to white, what you see is exactly what the image looks like.
	this->color = D3DCOLOR_ARGB(255, 255, 255, 255);

	// znullowanie wskaŸnika na tekstury
	this->tex = NULL;

	// We are not initialized yet
	this->initialized = false;
};

bool Sprite::Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int width, int height, D3DXVECTOR3 const & position )
{
	std::vector<std::string> v;
	v.push_back(file);
	return this->Initialize( device, v, width, height, position );
};

bool Sprite::Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & file, int width, int height, D3DXVECTOR3 const & position)
{
	this->texNumber = file.size();
	this->tex = new LPDIRECT3DTEXTURE9[this->texNumber];

	for (int i = 0; i < this->texNumber; i++)
	{
		//Same functionality as D3DXCreateTextureFromFile EXCEPT width and height are manually entered
		if (!SUCCEEDED(D3DXCreateTextureFromFileEx(device, file[i].c_str(), width, height,
			D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0,
			NULL, NULL, &tex[i])))
		{
			std::string s = "There was an issue creating the Texture.  Make sure the requested image is available.  Requested image: " + file[i];
			MessageBox(NULL, s.c_str(), NULL, NULL); 
			return false;
		}
	}

	//Attempt to create the sprite
	if(!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "There was an issue creating the Sprite.", NULL, NULL);
		return false;
	}

	this->SetCurrentTexture( 0 );
	this->texNumber = file.size();

	this->width = width;
	this->height = height;

	this->SetCenterPoint( position );

	this->SetRotation( 0.0f );
	this->SetScale( 1.0f );

	initialized = true;

	return true;
};


void Sprite::SetCenterPoint( D3DXVECTOR3 const & position )
{
	this->SetCenterPoint( position.x + this->GetWidth() / 2, position.y + this->GetHeight() / 2, position.z );
};


void Sprite::SetCenterPoint( float const & x0, float const & y0, float const & z0 )
{
	this->center.x = x0;
	this->center.y = y0;
	this->center.z = z0;
};


// position - górny, lewy róg sprajta
void Sprite::Draw(D3DXVECTOR3 const & position)
{
	if (this->sprite && tex)
	{
		this->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXMATRIX mat;
		D3DXVECTOR2 center2D( center.x, center.y );
		D3DXVECTOR2 position2D( position.x, position.y );

		// skalowanie i obrót
		D3DXMatrixTransformation2D( &mat, &center2D, NULL, new D3DXVECTOR2( scale, scale ), &center2D, rotation, NULL );

		this->sprite->SetTransform( &mat );

		this->sprite->Draw(tex[this->currentTex], NULL, NULL, &position, this->color);

		this->sprite->End();
	}

	/** Dzia³aj¹cy kod na obrót 2D dla kwaternionu. Wyszed³ w praniu
		D3DXVECTOR3 rotor ( rotation, 0.0f, 0.0f );

		float s2 = std::sin( D3DXToRadian ( rotor.x / 2.0f ) );
		float s1 = std::sin( D3DXToRadian ( rotor.y / 2.0f ) );
		float s3 = std::sin( D3DXToRadian ( rotor.z / 2.0f ) );

		float c2 = std::cos( D3DXToRadian ( rotor.x / 2.0f ) );
		float c1 = std::cos( D3DXToRadian ( rotor.y / 2.0f ) );
		float c3 = std::cos( D3DXToRadian ( rotor.z / 2.0f ) );
				
		float rX = s1 * s2 * c3 + c1 * c2 * s3;
		float rY = s1 * c2 * c3 + c1 * s2 * s3;
		float rZ = c1 * s2 * c3 - s1 * c2 * s3;
		float rW = c1 * c2 * c3 - s1 * s2 * s3;

		D3DXQUATERNION quat ( rX, rY, rZ, rW );
		
		D3DXMATRIX mat;
		D3DXMatrixTransformation(&mat, NULL, NULL, NULL, &center, &quat, NULL);
	*/
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
		for (int i = 0; i < this->texNumber; i++)
		{
			tex[i]->Release();
		}
		tex = 0;
	}
};


void Sprite::SetRotation(float const & rotation )
{
	this->rotation = rotation;
};


void Sprite::Rotate( float const & angle )
{
	this->rotation += angle;
};


void Sprite::SetScale( float const & scale )
{
	this->scale = scale;
};


void Sprite::Scale( float const & scale )
{
	this->scale *= scale;
};


void Sprite::SetCurrentTexture( short const & number )
{
	this->currentTex = number;
};