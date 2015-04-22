#include "TrajectorySpiral.h"


TrajectorySpiral::TrajectorySpiral( D3DXVECTOR2 const & center, float const & a, float const & b )
{
	this->SetParameters( a, b );
	// punktem pocz¹tkowym jest Ÿród³o spirali
	this->SetStartPoint( center );
};


TrajectorySpiral::~TrajectorySpiral()
{
};



void TrajectorySpiral::SetParameters( float const & a, float const & b )
{
	this->a = a;
	this->b = b;
};


D3DXVECTOR2 TrajectorySpiral::GetPosition( float const & t )
{
	float radius = this->a + this->b * t;
	D3DXVECTOR2 position = Vector::Polar(radius, t);
	GetRotation(position, theta);
	position += startPoint;
	return position;
};


void TrajectorySpiral::Translate( D3DXVECTOR2 const & translate )
{
	startPoint += translate;
};


void TrajectorySpiral::Scale( float const & scale )
{
	this->b *= scale;
};


void TrajectorySpiral::Rotate( float const & theta )
{
	this->theta += theta;
};
