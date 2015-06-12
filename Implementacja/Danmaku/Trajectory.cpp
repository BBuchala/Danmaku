#include "Trajectory.h"


/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="Trajectory"/>.
/// </summary>
Trajectory::Trajectory() : theta(0.0f)
{
};


/// <summary>
/// Niszczy instancjê klasy <see cref="Trajectory"/>.
/// </summary>
Trajectory::~Trajectory()
{
};


/// <summary>
/// Wybranie punktu startowego.
/// </summary>
/// <param name="startPoint">Punkt startowy.</param>
void Trajectory::SetStartPoint( D3DXVECTOR2 const & startPoint )
{
	this->startPoint = startPoint;
};

/// <summary>
/// Obrócenie trajektorii o wybrany k¹t wzglêdem wskazanej pozycji.
/// </summary>
/// <param name="pos">Pozycja.</param>
/// <param name="theta">K¹t.</param>
void Trajectory::GetRotation( D3DXVECTOR2 & pos, float const theta )
{
	D3DXMATRIX mat; 
	mat._11 = cos(theta);	mat._12 = sin(theta);	mat._13 = 0.0f;		mat._14 = 0.0f;
    mat._21 = -sin(theta);	mat._22 = cos(theta);	mat._23 = 0.0f;		mat._24 = 0.0f;
    mat._31 = 0.0f;			mat._32 = 0.0f;			mat._33 = 1.0f;		mat._34 = 0.0f;
    mat._41 = 0.0f;			mat._42 = 0.0f;			mat._43 = 0.0f;		mat._44 = 1.0f;
	D3DXVec2TransformCoord(&pos, &pos, &mat);
};


/// <summary>
/// Ustawienie d³ugoœci drogi.
/// </summary>
/// <param name="length">D³ugoœæ.</param>
void Trajectory::SetLength(float length)
{
	_length = length;
};
