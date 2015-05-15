#include "TrajectoryNone.h"

TrajectoryNone::TrajectoryNone( D3DXVECTOR2 const & position, float const angle, float const length )
{
	_length = length;
	_position = position;
};

TrajectoryNone::~TrajectoryNone()
{
};

void TrajectoryNone::SetPosition( D3DXVECTOR2 const & position )
{
	_position = position;
};

D3DXVECTOR2 TrajectoryNone::GetPosition( float const distance )
{
	return _position;
};


void TrajectoryNone::Translate( D3DXVECTOR2 const & translate )
{
	_position += translate;
};


void TrajectoryNone::Scale( float const scale )
{
	// NULL
};


void TrajectoryNone::Rotate( float const theta )
{
	// NULL
};

