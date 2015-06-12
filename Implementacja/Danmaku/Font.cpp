#include "Font.h"


/// <summary>
/// Tworzy now� instacj� klasy <see cref="Font"/>.
/// </summary>
/// <param name="fieldPosition">Pozycja pola, w kt�rym b�dzie znajdowa� si� napis.</param>
/// <param name="fieldWidth">Szeroko�� tego pola.</param>
/// <param name="fieldHeight">Wysoko�� tego pola.</param>
Font::Font( D3DXVECTOR2 const & fieldPosition, unsigned short const fieldWidth, unsigned short const fieldHeight )
	: fieldWidth(fieldWidth), fieldHeight(fieldHeight), fieldPosition(fieldPosition)
{
	SetRect(&rect, static_cast<int>(fieldPosition.x), static_cast<int>(fieldPosition.y), fieldWidth, fieldHeight);
};

/// <summary>
/// Niszczy instancj� klasy <see cref="Font"/>.
/// </summary>
Font::~Font()
{
	if ( text )
	{
		text->Release();
		text = NULL;
	}
};


/// <summary>
/// Inicjalizacja i utowrzenie w�a�ciwej instacji czcionki.
/// </summary>
/// <param name="gDevice">Urz�dzenie graficzne.</param>
/// <param name="fontHeight">Wysoko�c czcionki.</param>
/// <param name="fontWidth">Szeroko�� czcionki.</param>
/// <param name="font">Format czcionki.</param>
/// <param name="bold">Czy pogrubiona.</param>
/// <param name="italic">Czy pochy�a.</param>
/// <param name="color">Kolor czcionki.</param>
/// <returns></returns>
bool Font::Initialize( GraphicsDevice * const gDevice, short unsigned const fontHeight, 
		short unsigned const fontWidth, std::string const & font, bool bold, bool italic, D3DXCOLOR const & color )
{
	this->SetColor(color);
	if (D3DXCreateFont( gDevice->device, fontHeight, fontWidth, bold ? FW_BOLD : FW_NORMAL, 1, italic,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		font.c_str(), &text ))
	{
		return true;
	}
	return false;
};


/// <summary>
/// Narysowanie napisu ze wskazanym paddingiem
/// </summary>
/// <param name="str">Napis.</param>
/// <param name="padding">The padding.</param>
void Font::Draw( std::string const & str, short unsigned const padding )
{
	std::stringstream ss;
	ss << std::setw(padding) << std::setfill(' ') << str;
	text->DrawText( NULL, ss.str().c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color );
};


/// <summary>
/// Narysowanie liczby ze wskazanym wype�nieniem zerami
/// </summary>
/// <param name="number">Liczba.</param>
/// <param name="padding">The padding.</param>
void Font::Draw( int const number, short unsigned const padding )
{
	std::stringstream ss;
	ss << std::setw(padding) << std::setfill('0') << number;
	text->DrawText( NULL, ss.str().c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color );
};

/// <summary>
/// Narysowanie liczby zmiennoprzecinkowej z okre�lon� precyzj�
/// </summary>
/// <param name="number">Liczba.</param>
/// <param name="padding">The padding.</param>
/// <param name="precision">Precyzja.</param>
void Font::Draw( float const number, short unsigned const padding, short unsigned const precision )
{
	std::stringstream ss;
	ss << std::setw(padding) << std::setfill('0') << std::fixed << std::setprecision(precision) << number;
	text->DrawText( NULL, ss.str().c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color );
};

/// <summary>
/// Wyb�r koloru.
/// </summary>
/// <param name="color">Kolor.</param>
void Font::SetColor(D3DXCOLOR const & color)
{
	this->color = color;
};
