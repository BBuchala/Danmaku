#include "Font.h"


Font::Font( D3DXVECTOR2 const & fieldPosition, unsigned short const fieldWidth, unsigned short const fieldHeight )
	: fieldWidth(fieldWidth), fieldHeight(fieldHeight), fieldPosition(fieldPosition)
{
	SetRect(&rect, static_cast<int>(fieldPosition.x), static_cast<int>(fieldPosition.y), fieldWidth, fieldHeight);
};


Font::~Font()
{
	if ( text )
	{
		text->Release();
		text = NULL;
	}
};


bool Font::Initialize( GraphicsDevice * const gDevice, short unsigned const fontHeight, 
		short unsigned const fontWidth, std::string const & font, bool bold, bool italic, D3DXCOLOR const & color )
{
	this->color = color;
	if (D3DXCreateFont( gDevice->device, fontHeight, fontWidth, bold ? FW_BOLD : FW_NORMAL, 1, italic,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		font.c_str(), &text ))
	{
		return true;
	}
	return false;
};


void Font::Draw( std::string const & str, short unsigned const padding )
{
	std::stringstream ss;
	ss << std::setw(padding) << std::setfill(' ') << str;
	text->DrawText( NULL, ss.str().c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color );
};


void Font::Draw( int const number, short unsigned const padding )
{
	std::stringstream ss;
	ss << std::setw(padding) << std::setfill('0') << number;
	text->DrawText( NULL, ss.str().c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color );
};

void Font::Draw( float const number, short unsigned const padding, short unsigned const precision )
{
	std::stringstream ss;
	ss << std::setw(padding) << std::setfill('0') << std::fixed << std::setprecision(precision) << number;
	text->DrawText( NULL, ss.str().c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, color );
};