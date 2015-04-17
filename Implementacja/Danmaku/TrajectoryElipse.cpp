#include "TrajectoryElipse.h"

TrajectoryElipse::TrajectoryElipse( D3DXVECTOR2 const & center, float const & a, float const & b )
{
	this->SetCenterPoint( center );
	this->SetElipseRadius( a, b );
	// punktem pocz�tkowym jest punkt przy 0.0 stopni
	this->SetStartPoint( this->GetPosition( 0.0f ) );
	this->theta = 0.0f;
};

TrajectoryElipse::~TrajectoryElipse()
{
};



void TrajectoryElipse::SetElipseRadius( float const & a, float const & b )
{
	this->a = a;
	this->b = b;
};


void TrajectoryElipse::SetCenterPoint( float const & x0, float const & y0 )
{
	this->center.x = x0;
	this->center.y = y0;
};


void TrajectoryElipse::SetCenterPoint( D3DXVECTOR2 const & center )
{
	this->center = center;
};


D3DXVECTOR2 TrajectoryElipse::GetPosition( float const & t ) const
{
	D3DXVECTOR2 position;
	position.x = this->center.x + ( a * cos(t) * cos(theta) - b * sin(t) * sin(theta) );
	position.y = this->center.y + ( b * sin(t) * cos(theta) + a * cos(t) * sin(theta) );
	return position;
};


void TrajectoryElipse::Translate( D3DXVECTOR2 const & move )
{
	this->center += move;
};


void TrajectoryElipse::Scale( float const & scale )
{
	this->a *= scale;
	this->b *= scale;
};


void TrajectoryElipse::Rotate( float const & theta )
{
	this->theta += theta;
};