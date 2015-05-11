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
	return this->sprite.Initialize( device, file );
}

void Bar::Draw()
{
	for (int i = 0; i < count; i++)
	{
		this->sprite.Draw( D3DXVECTOR2( startPos.x + i * 25, startPos.y ) );
	}
}

void Bar::IncrementCount()
{
	if (count < 8)
		count++;
}

void Bar::DecrementCount()
{
	if (count > 0)
		count--;
}
// ++Bar
Bar & Bar::operator++()
{
	IncrementCount();
	return *this;
}
// --Bar
Bar & Bar::operator--()
{
	DecrementCount();
	return *this;
}
// Bar++
int Bar::operator++(int)
{
	int oldCount = count;
	IncrementCount();
	return oldCount;
}
// Bar++
int Bar::operator--(int)
{
	int oldCount = count;
	DecrementCount();
	return oldCount;
}
