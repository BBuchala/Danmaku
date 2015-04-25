#include "Trajectory.h"


Trajectory::Trajectory() : theta(0.0f)
{
};


Trajectory::~Trajectory()
{
};



void Trajectory::SetStartPoint( float const & x0, float const & y0 )
{
	this->startPoint.x = x0;
	this->startPoint.y = y0;
};



void Trajectory::SetStartPoint( D3DXVECTOR2 const & startPoint )
{
	this->startPoint = startPoint;
};

// obrót
void Trajectory::GetRotation( D3DXVECTOR2 & pos, float const & theta )
{
	D3DXMATRIX mat;
	mat._11 = cos(theta);	mat._12 = sin(theta);	mat._13 = 0.0f;		mat._14 = 0.0f;
    mat._21 = -sin(theta);	mat._22 = cos(theta);	mat._23 = 0.0f;		mat._24 = 0.0f;
    mat._31 = 0.0f;			mat._32 = 0.0f;			mat._33 = 1.0f;		mat._34 = 0.0f;
    mat._41 = 0.0f;			mat._42 = 0.0f;			mat._43 = 0.0f;		mat._44 = 1.0f;
	D3DXVec2TransformCoord(&pos, &pos, &mat);
};