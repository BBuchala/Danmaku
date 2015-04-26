#include "Bar.h"


Bar::Bar(D3DXVECTOR2 pos, BYTE initialCount)
{
	this->startPos = pos;
	this->count = initialCount;
}

bool Bar::Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const width, int const height)
{
	return this->sprite.Initialize( device, file, width, height);
}

bool Bar::Initialize(LPDIRECT3DDEVICE9 device, std::string const & file)
{
	return this->sprite.Initialize( device, file, 20, 20);
}

void Bar::Draw()
{
	for (int i = 0; i < count; i++)
	{
		this->sprite.Draw( D3DXVECTOR2( startPos.x + i * 25, startPos.y ) );
	}
}

Bar & Bar::operator++()
{
	count++;
	return *this;
}

Bar & Bar::operator++(int)
{
	Bar tmp = (*this);
	++count;
	return tmp;
}

Bar & Bar::operator--()
{
	count--;
	return *this;
}

Bar & Bar::operator--(int)
{
	Bar tmp = (*this);
	--count;
	return tmp;
}