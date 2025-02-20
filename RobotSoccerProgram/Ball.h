#pragma once

#include "screenobject.h"
#include "PointDouble.h"	// Added by ClassView
#include "Ground.h"

#if !defined(OBJECT_STATE_NOT_EXIST)
#define OBJECT_STATE_NOT_EXIST	0
#define OBJECT_STATE_REAL		1
#define OBJECT_STATE_VIRTUAL	2
#endif

class CBall :
	public CScreenObject
{
public:
	void SimulationMove( double sec );
	// Variable Interface
	bool IsExist();


	void SetRadius( double radius );
	double Radius();
	
	void SetState( int state );
	int State();

	void SetPosition( CPointDouble p );
	CPointDouble Position();
	void SetPositionCurrent( CPointDouble p );
	CPointDouble PositionCurrent();

	void SetPositionPast( CPointDouble p );
	CPointDouble PositionPast();

	void SetPositionError( CPointDouble p );
	CPointDouble PositionError();

	void SetVelocity( CPointDouble velocity );
	void SetVelocityCurrent( CPointDouble velocity );
	void SetVelocityPast( CPointDouble velocity );
	CPointDouble VelocityCurrent();
	CPointDouble Velocity();
	CPointDouble VelocityPast();

	void SetAcceleration( CPointDouble velocity );
	void SetAccelerationCurrent( CPointDouble velocity );
	void SetAccelerationPast( CPointDouble velocity );
	CPointDouble AccelerationCurrent();
	CPointDouble Acceleration();
	CPointDouble AccelerationPast();

	void SetGround( CGround ground );

	CBall(void);
	~CBall(void);

protected:
	double m_radius;

	CPointDouble m_posPast;
	CPointDouble m_velocity;
	CPointDouble m_velocityCurrent;
	CPointDouble m_velocityPast;
	CPointDouble m_posError;

	CPointDouble m_acceleration;
	CPointDouble m_accelerationCurrent;
	CPointDouble m_accelerationPast;

	int m_state;
	CGround m_ground;
};

