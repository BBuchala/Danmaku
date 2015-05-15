#include "TrajectoryElipse.h"

TrajectoryElipse::TrajectoryElipse( D3DXVECTOR2 const & center, float const a, float const b )
{
	this->SetCenterPoint( center );
	this->SetElipseRadius( a, b );
	// punktem pocz¹tkowym jest punkt przy 0.0 stopni
	this->SetStartPoint( this->GetPosition( 0.0f ) );
};

TrajectoryElipse::~TrajectoryElipse()
{
};



void TrajectoryElipse::SetElipseRadius( float const a, float const b )
{
	this->a = a;
	this->b = b;
};


void TrajectoryElipse::SetCenterPoint( D3DXVECTOR2 const & center )
{
	this->center = center;
};


D3DXVECTOR2 TrajectoryElipse::GetPosition( float const t )
{
	D3DXVECTOR2 position;
	position.x = a * cos(t);
	position.y = b * sin(t);
	GetRotation(position, theta);
	position += center;
	return position;
};


void TrajectoryElipse::Translate( D3DXVECTOR2 const & move )
{
	this->center += move;
};


void TrajectoryElipse::Scale( float const scale )
{
	this->a *= scale;
	this->b *= scale;
};


void TrajectoryElipse::Rotate( float const theta )
{
	this->theta += theta;
};