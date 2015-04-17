#include "TrajectoryLine.h"

TrajectoryLine::TrajectoryLine( D3DXVECTOR2 const & startPoint, float const & angle )
{
	/* Wartosci vectora s¹ w przedziale [0, 1] */
	D3DXVECTOR2 dv;
	dv.x = std::cos( angle );
	dv.y = - std::sin( angle );
	this->SetDirection( dv );
	this->SetStartPoint( startPoint );
};


TrajectoryLine::~TrajectoryLine()
{
};


void TrajectoryLine::SetDirection( D3DXVECTOR2 const & direction )
{
	this->direction = direction;
};


D3DXVECTOR2 TrajectoryLine::GetPosition( float const & distance ) const
{
	D3DXVECTOR2 position;
	position.x = this->startPoint.x + this->direction.x * distance;
	position.y = this->startPoint.y + this->direction.y * distance;
	return position;
};


void TrajectoryLine::Translate( D3DXVECTOR2 const & translate )
{
	this->startPoint += translate;
};


void TrajectoryLine::Scale( float const & scale )
{
	this->direction *= scale;
};


void TrajectoryLine::Rotate( float const & theta )
{
	// TODO
};