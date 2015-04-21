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


D3DXVECTOR2 TrajectorySpiral::GetPosition( float const & theta ) const
{
	float radius = this->a + this->b * theta;
	D3DXVECTOR2 position = startPoint + Vector::Polar(radius, theta);
	return position;
};


void TrajectorySpiral::Translate( D3DXVECTOR2 const & translate )
{
	// TODO
};


void TrajectorySpiral::Scale( float const & scale )
{
	this->a *= scale;
	this->b *= scale;
};


void TrajectorySpiral::Rotate( float const & theta )
{
	// TODO
};
