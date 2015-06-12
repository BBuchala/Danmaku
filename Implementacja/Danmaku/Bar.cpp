#include "Bar.h"


/// <summary>
/// Tworzy now� instacj� klasy <see cref="Bar"/>.
/// </summary>
/// <param name="pos">Pozycja.</param>
/// <param name="initialCount">Pocz�tkowa liczba element�w.</param>
Bar::Bar(D3DXVECTOR2 pos, BYTE initialCount)
{
	this->startPos = pos;
	this->count = initialCount;
}

/// <summary>
/// Niszczy instancj� klasy <see cref="Bar"/>.
/// </summary>
Bar::~Bar()
{
	delete sprite;
}

/// <summary>
/// Inicjalizacja paska.
/// </summary>
/// <param name="device">Urz�dznie graficzne.</param>
/// <param name="file">�cie�ka do pliku elementu.</param>
/// <param name="width">Szeroko�� elementu.</param>
/// <param name="height">Wysoko�� elementu.</param>
/// <returns></returns>
bool Bar::Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const width, int const height)
{
	this->sprite = new Sprite( device, file, width, height);
	return true;
}

/// <summary>
/// Inicjalizacja paska.
/// </summary>
/// <param name="device">Urz�dznie graficzne.</param>
/// <param name="file">�cie�ka do pliku elementu.</param>
/// <returns></returns>
bool Bar::Initialize(LPDIRECT3DDEVICE9 device, std::string const & file)
{
	this->sprite = new Sprite( device, file );
	return true;
}

/// <summary>
/// Narysowanie paska z elementami.
/// </summary>
void Bar::Draw()
{
	for (int i = 0; i < count; i++)
	{
		this->sprite->Draw( D3DXVECTOR2( startPos.x + i * 25, startPos.y ) );
	}
}

/// <summary>
/// Inkrementacja liczby element�w.
/// </summary>
void Bar::IncrementCount()
{
	if (count < 8)
		count++;
}

/// <summary>
/// Dekrementacja liczby element�w.
/// </summary>
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

/// <summary>
/// Ustawienie liczby element�w.
/// </summary>
/// <param name="newCount">Nowa liczba.</param>
void Bar::SetCount(short newCount)
{
	this->count = newCount;
}