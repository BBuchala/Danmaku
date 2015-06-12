#include "Sprite.h"

/* ---- STA�E ---------------------- */
const std::string Sprite::IMG_PATH	= "img/";

/* ---- KONSTRUKTOR --------------- */
/// <summary>
/// Tworzy now� instacj� klasy <see cref="Sprite"/>.
/// </summary>
Sprite::Sprite()
{
	this->ResetValues();
};


/// <summary>
/// Tworzy now� instacj� klasy <see cref="Sprite"/>.
/// </summary>
/// <param name="device">Urz�dzenie graficzne.</param>
/// <param name="file">�cie�ka do pliku.</param>
/// <param name="width">Wybrana szeroko�� sprajta. Domy�lnie przyjmuje jego faktyczn� szeroko��. </param>
/// <param name="height">Wybrana wysoko�� sprajta. Domy�lnie przyjmuje jego faktyczn� wysoko��. </param>
Sprite::Sprite(LPDIRECT3DDEVICE9 device, std::string const & file, UINT const width, UINT const height)
{
	this->ResetValues();
	this->Initialize(device, file, width, height);
};


/// <summary>
/// Tworzy now� instacj� klasy <see cref="Sprite"/>.
/// </summary>
/// <param name="device">Urz�dzenie graficzne.</param>
/// <param name="file">�cie�ka do plik�w.</param>
/// <param name="width">Wybrana szeroko�� sprajta. Domy�lnie przyjmuje jego faktyczn� szeroko��. </param>
/// <param name="height">Wybrana wysoko�� sprajta. Domy�lnie przyjmuje jego faktyczn� wysoko��. </param>
Sprite::Sprite(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, UINT const width, UINT const height)
{
	this->ResetValues();
	this->Initialize(device, fileVect, width, height);
};


/// <summary>
/// Zresetowanie warto�ci sprajta.
/// </summary>
void Sprite::ResetValues()
{
	// przezroczysto�� - brak
	this->color = D3DCOLOR_ARGB(255, 255, 255, 255);

	// znullowanie wska�nika na tekstury
	this->tex = NULL;

	this->initialized = false;
};


/// <summary>
/// Niszczy instancj� klasy <see cref="Sprite"/>.
/// </summary>
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
		delete[] tex;
	}
};


/// <summary>
/// Tworzy sprajt z jednego pliku (jedna tekstura)
/// </summary>
/// <param name="device">Urz�dzenie graficzne.</param>
/// <param name="file">�cie�ka do pliku.</param>
/// <param name="width">Wybrana szeroko�� sprajta. Domy�lnie przyjmuje jego faktyczn� szeroko��. </param>
/// <param name="height">Wybrana wysoko�� sprajta. Domy�lnie przyjmuje jego faktyczn� wysoko��. </param>
/// <returns></returns>
bool Sprite::Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, UINT const width, UINT const height )
{
	std::vector<std::string> v;
	v.push_back(file);
	return this->Initialize( device, v, width, height );
};


/// <summary>
/// Tworzy sprajt z kilka plik�w (wiele tekstur).
/// </summary>
/// <param name="device">Urz�dzenie graficzne.</param>
/// <param name="file">�cie�ka do plik�w.</param>
/// <param name="width">Wybrana szeroko�� sprajta. Domy�lnie przyjmuje jego faktyczn� szeroko��. </param>
/// <param name="height">Wybrana wysoko�� sprajta. Domy�lnie przyjmuje jego faktyczn� wysoko��. </param>
/// <returns></returns>
bool Sprite::Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & file, UINT const width, UINT const height )
{
	if (!initialized)
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
		// przypisanie odpowiedniej wysoko�ci i szeroko�ci
		if ( width == D3DX_DEFAULT_NONPOW2 || height == D3DX_DEFAULT_NONPOW2 )
		{
			D3DXIMAGE_INFO info;
			D3DXGetImageInfoFromFile(file[0].c_str(), &info);
			this->width = info.Width;
			this->height = info.Height;
		}
		else
		{
			this->width = width;
			this->height = height;
		}

		//Attempt to create the sprite
		if (!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
		{
			MessageBox(NULL, "There was an issue creating the Sprite.", NULL, NULL);
			return false;
		}

		this->SetCurrentTexture( 0 );
		this->texNumber = file.size();

		this->SetCenterPoint();

		initialized = true;
	}
	return initialized;
};


/// <summary>
/// Ustawia punkt centralny sprajta.
/// </summary>
void Sprite::SetCenterPoint( )
{
	this->center.x = this->GetWidth() / 2.0f;
	this->center.y = this->GetHeight() / 2.0f;
};



/// <summary>
/// Rysuje sprajt zgodnie ze wskazanymi danymi.
/// </summary>
/// <param name="position">Pozycja sprajta - jego g�rny, lewey r�g.</param>
/// <param name="scale">Skala o jak� sprajt zostanie przeksta�cony.</param>
/// <param name="rotation">K�t o jaki sprajt zostanie obr�cony.</param>
void Sprite::Draw(D3DXVECTOR2 const & position, float scale, float rotation)
{
	if (this->sprite && tex)
	{
		this->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXMATRIX mat;
		D3DXVECTOR2 center2D( position.x + center.x, position.y + center.y );
		D3DXVECTOR3 position3D( position.x, position.y, 0.0f );

		// skalowanie i obr�t
		D3DXMatrixTransformation2D( &mat, &center2D, NULL, new D3DXVECTOR2( scale, scale ), &center2D, rotation, NULL );

		this->sprite->SetTransform( &mat );

		this->sprite->Draw(tex[this->currentTex], NULL, NULL, &position3D, this->color);

		this->sprite->End();
	}
};


/// <summary>
/// Rysuje sprajt zgodnie ze wskazanymi danymi.
/// </summary>
/// <param name="position">Pozycja sprajta - jego g�rny, lewey r�g.</param>
/// <param name="scale">Skala o jak� sprajt zostanie przeksta�cony.</param>
/// <param name="rotation">K�t o jaki sprajt zostanie obr�cony.</param>
void Sprite::Draw(D3DXVECTOR2 const & position, D3DXVECTOR2 const & scale, float rotation)
{
	if (this->sprite && tex)
	{
		this->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXMATRIX mat;
		D3DXVECTOR2 center2D( position.x, position.y );
		D3DXVECTOR3 position3D( position.x, position.y, 0.0f );

		// skalowanie i obr�t
		D3DXMatrixTransformation2D( &mat, &center2D, NULL, &scale, &center2D, rotation, NULL );

		this->sprite->SetTransform( &mat );

		this->sprite->Draw(tex[this->currentTex], NULL, NULL, &position3D, this->color);

		this->sprite->End();
	}
};


/// <summary>
/// Wybiera aktualn� tekstur� sprajta.
/// </summary>
/// <param name="number">Numer tektury.</param>
void Sprite::SetCurrentTexture( short const number )
{
	this->currentTex = number;
};
