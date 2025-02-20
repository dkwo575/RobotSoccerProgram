#include "StdAfx.h"
#include "Ball.h"


CBall::CBall(void)
{
	m_velocityCurrent = CPointDouble(0,0);

	//#define BALL_RADIUS (0.047/2.0)
	m_radius = 0.047/2.0;

	m_state = OBJECT_STATE_NOT_EXIST;
}


CBall::~CBall(void)
{
}


//////////////////////////////////////////////////////////////////////////
// Variable Interface
//////////////////////////////////////////////////////////////////////////

bool CBall::IsExist(){ return (m_state != OBJECT_STATE_NOT_EXIST); }

void CBall::SetRadius( double radius ){	m_radius = radius; }
double CBall::Radius(){ return m_radius; }

void CBall::SetState(int state){ m_state = state; }
int CBall::State(){ return m_state; }

void CBall::SetPosition(CPointDouble p){ m_pos = p; }
CPointDouble CBall::Position(){ return m_pos; }
void CBall::SetPositionCurrent(CPointDouble p){ m_posCurrent = p; }
CPointDouble CBall::PositionCurrent(){ return m_posCurrent; }
void CBall::SetPositionPast(CPointDouble p){ m_posPast = p; }
CPointDouble CBall::PositionPast(){ return m_posPast; }
void CBall::SetPositionError(CPointDouble p){ m_posError = p; }
CPointDouble CBall::PositionError(){ return m_posError; }

void CBall::SetVelocity(CPointDouble velocity){ m_velocity = velocity; }
void CBall::SetVelocityCurrent(CPointDouble velocity){ m_velocityCurrent = velocity; }
CPointDouble CBall::VelocityCurrent(){ return m_velocityCurrent; }
CPointDouble CBall::Velocity(){ return m_velocity; }
void CBall::SetVelocityPast(CPointDouble velocity){ m_velocityPast = velocity; }
CPointDouble CBall::VelocityPast(){ return m_velocityPast; }

void CBall::SetAcceleration(CPointDouble acc){ m_acceleration = acc; }
void CBall::SetAccelerationCurrent(CPointDouble acc){ m_accelerationCurrent = acc; }
CPointDouble CBall::AccelerationCurrent(){ return m_accelerationCurrent; }
CPointDouble CBall::Acceleration(){ return m_acceleration; }
void CBall::SetAccelerationPast(CPointDouble acc){ m_accelerationPast = acc; }
CPointDouble CBall::AccelerationPast(){ return m_accelerationPast; }



void CBall::SetGround(CGround ground){ m_ground = ground; }

void CBall::SimulationMove(double sec)
{
	m_pos += m_velocity * sec;

	double BALL_WALL_K = 0.5;
	if( m_pos.x < m_radius && m_velocity.x < 0 )
	{
		m_pos.x = m_radius - BALL_WALL_K*(m_pos.x-m_radius);
		m_velocity.x *= -BALL_WALL_K;
	}
	if( m_pos.x > m_ground.Width()-m_radius && m_velocity.x > 0 )
	{
		m_pos.x = (m_ground.Width()-m_radius) - BALL_WALL_K*(m_pos.x-(m_ground.Width()-m_radius));
		m_velocity.x *= -BALL_WALL_K;
	}


	if( m_pos.y < m_radius && m_velocity.y < 0)
	{
		m_pos.y = m_radius - BALL_WALL_K*(m_pos.y-m_radius);
		m_velocity.y *= -BALL_WALL_K;
	}
	if( m_pos.y > m_ground.Height()-m_radius && m_velocity.y > 0 )
	{
		m_pos.y = (m_ground.Height()-m_radius) - BALL_WALL_K*(m_pos.y-(m_ground.Height()-m_radius));
		m_velocity.y *= -BALL_WALL_K;
	}


	double k = m_frictionK;
	double g = 9.8;
	double mass = m_mass;

	CPointDouble friction = m_velocity;
	friction.Normalize();
	m_velocity = m_velocity - friction * k * mass * g * sec;
}
