#include "StdAfx.h"
#include "SynchronousModule.h"

#define _USE_MATH_DEFINES
#include <math.h>

/*
    |                    | trans.             | trans.             |
    | image              | image              | image              |
    |   processing       |   processing       |   processing       |
    |                    |                    |                    |
*/

CSynchronousModule::CSynchronousModule(void)
{
	for( int t=0 ; t<SYNCH_TIME_N ; t++ )
	{
		m_objects[t].Reset();
		m_velocity[t].Reset();
	}

	m_simulBox    = new CRobot[POSITION_INFO_ROBOT_N];
	m_simulSphere = new CBall[POSITION_INFO_ROBOT_N+1];


	SetSimulationTime( 1.0/30.0 );
	SetDelayTime( 2 );
}


CSynchronousModule::~CSynchronousModule(void)
{
	delete []m_simulBox;
	delete []m_simulSphere;
}


void CSynchronousModule::SetSimulationTime( double t)
{
	m_SimulationTime = t;
}

void CSynchronousModule::SetGround( CGround* pGround )
{
	m_pGround = pGround;
	
	m_simulSphere[POSITION_INFO_ROBOT_N].SetGround( *m_pGround );
	m_simulSphere[POSITION_INFO_ROBOT_N].m_mass = 0.020;

	for( int i=0 ; i<POSITION_INFO_ROBOT_N ; i++ )
	{
		m_simulSphere[i].SetGround( *m_pGround );
		m_simulSphere[i].SetRadius( 0.075/2.0 );
		m_simulSphere[i].m_mass = 0.250;

		m_simulBox[i].SetGround( *m_pGround );
		m_simulBox[i].m_mass = 0.450;
	}
}

void CSynchronousModule::UpdatePositionData(CObjectPositionInfo &VisionInfo, CObjectPositionInfo &StrategyInfo)
{
	// Update PositionData -> Current
		m_error.m_Ball.pos = CPointDouble(0,0);

		if( VisionInfo.m_Ball.state == OBJECT_STATE_REAL )
		{
			m_error.m_Ball.pos = VisionInfo.m_Ball.pos-m_objects[SYNCH_TIME_CURRENT].m_Ball.pos;

			m_objects[SYNCH_TIME_CURRENT].m_Ball.state = OBJECT_STATE_REAL;
			m_objects[SYNCH_TIME_CURRENT].m_Ball.pos = VisionInfo.m_Ball.pos;
		}
		else
		if( VisionInfo.m_Ball.countLost < LOST_ROBOT_COUNT_MAX )
		{
			m_objects[SYNCH_TIME_CURRENT].m_Ball.state = OBJECT_STATE_VIRTUAL;
			if( m_objects[SYNCH_TIME_CURRENT-1].m_Ball.pos != StrategyInfo.m_Ball.pos
				|| m_objects[SYNCH_TIME_CURRENT-1].m_Ball.velocity != StrategyInfo.m_Ball.velocity
				|| m_objects[SYNCH_TIME_CURRENT-1].m_Ball.acceleration != StrategyInfo.m_Ball.acceleration)
			{
				m_error.m_Ball.pos = StrategyInfo.m_Ball.pos-m_objects[SYNCH_TIME_CURRENT].m_Ball.pos;

				m_objects[SYNCH_TIME_CURRENT].m_Ball.pos = StrategyInfo.m_Ball.pos;
				m_objects[SYNCH_TIME_CURRENT].m_Ball.velocity = StrategyInfo.m_Ball.velocity;
				m_objects[SYNCH_TIME_CURRENT].m_Ball.acceleration = StrategyInfo.m_Ball.acceleration;
			}
		}
		else
		{
			m_objects[SYNCH_TIME_CURRENT].m_Ball.state = OBJECT_STATE_NOT_EXIST;
			if( m_objects[SYNCH_TIME_CURRENT-1].m_Ball.pos != StrategyInfo.m_Ball.pos
				|| m_objects[SYNCH_TIME_CURRENT-1].m_Ball.velocity != StrategyInfo.m_Ball.velocity
				|| m_objects[SYNCH_TIME_CURRENT-1].m_Ball.acceleration != StrategyInfo.m_Ball.acceleration)
			{
				m_error.m_Ball.pos = StrategyInfo.m_Ball.pos-m_objects[SYNCH_TIME_CURRENT].m_Ball.pos;

				m_objects[SYNCH_TIME_CURRENT].m_Ball.pos = StrategyInfo.m_Ball.pos;
				m_objects[SYNCH_TIME_CURRENT].m_Ball.velocity = StrategyInfo.m_Ball.velocity;
				m_objects[SYNCH_TIME_CURRENT].m_Ball.acceleration = StrategyInfo.m_Ball.acceleration;
			}
		}


//	FILE *fp;
//	fp = fopen("D:/check.txt", "at");

	for( int i=0 ; i<POSITION_INFO_ROBOT_N ; i++ )
	{
		m_error.m_Robot[i].pos = CPointDouble(0,0);

		if( VisionInfo.m_Robot[i].state == OBJECT_STATE_REAL )
		{
			m_error.m_Robot[i].pos = VisionInfo.m_Robot[i].pos-m_objects[SYNCH_TIME_CURRENT].m_Robot[i].pos;
			m_error.m_Robot[i].orientation = VisionInfo.m_Robot[i].orientation-m_objects[SYNCH_TIME_CURRENT].m_Robot[i].orientation;

			while( m_error.m_Robot[i].orientation < -180 ) m_error.m_Robot[i].orientation += 360;
			while( m_error.m_Robot[i].orientation >  180 ) m_error.m_Robot[i].orientation -= 360;

			m_objects[SYNCH_TIME_CURRENT].m_Robot[i].state = OBJECT_STATE_REAL;
			m_objects[SYNCH_TIME_CURRENT].m_Robot[i].pos = VisionInfo.m_Robot[i].pos;
			m_objects[SYNCH_TIME_CURRENT].m_Robot[i].orientation = VisionInfo.m_Robot[i].orientation;
/*
			if( fpDebug != NULL && i==0 )
			{
				fprintf( fpDebug, "%.5lf\t%.5lf\t",
					m_velocity[SYNCH_TIME_CURRENT].m_VelocityLeft[0], 
					m_velocity[SYNCH_TIME_CURRENT].m_VelocityRight[0]
					);
				for( int t = SYNCH_TIME_CURRENT ; t<SYNCH_TIME_CURRENT+7 ; t++ )
				{
					fprintf( fpDebug, "%d\t%.5lf\t",
						t,
						(VisionInfo.m_posRobot[0] - m_objects[t].m_posRobot[0]).Distance() );
				}
				
				fprintf( fpDebug, "\n" );
			}
*/			
		}
		else if( VisionInfo.m_Robot[i].countLost < LOST_ROBOT_COUNT_MAX )
		{
			m_objects[SYNCH_TIME_CURRENT].m_Robot[i].state = OBJECT_STATE_VIRTUAL;

			if( m_objects[SYNCH_TIME_CURRENT-1].m_Robot[i].pos != StrategyInfo.m_Robot[i].pos
				|| m_objects[SYNCH_TIME_CURRENT-1].m_Robot[i].orientation != StrategyInfo.m_Robot[i].orientation )
			{
				m_error.m_Robot[i].pos = StrategyInfo.m_Robot[i].pos-m_objects[SYNCH_TIME_CURRENT].m_Robot[i].pos;

				m_objects[SYNCH_TIME_CURRENT].m_Robot[i].pos = StrategyInfo.m_Robot[i].pos;
				m_objects[SYNCH_TIME_CURRENT].m_Robot[i].orientation = StrategyInfo.m_Robot[i].orientation;
			}
		}
		else
		{
			m_objects[SYNCH_TIME_CURRENT].m_Robot[i].state = OBJECT_STATE_NOT_EXIST;

			if( m_objects[SYNCH_TIME_CURRENT-1].m_Robot[i].pos != StrategyInfo.m_Robot[i].pos
				|| m_objects[SYNCH_TIME_CURRENT-1].m_Robot[i].orientation != StrategyInfo.m_Robot[i].orientation )
			{
				m_error.m_Robot[i].pos = StrategyInfo.m_Robot[i].pos-m_objects[SYNCH_TIME_CURRENT].m_Robot[i].pos;

				m_objects[SYNCH_TIME_CURRENT].m_Robot[i].pos = StrategyInfo.m_Robot[i].pos;
				m_objects[SYNCH_TIME_CURRENT].m_Robot[i].orientation = StrategyInfo.m_Robot[i].orientation;
			}
		}

//		if( i==1 )
//		{
//			if( VisionInfo.m_Robot[i].state == OBJECT_STATE_REAL )
//				fprintf( fp, "1\t%lf\t%lf\t%lf\n", m_error.m_Robot[i].pos.x, m_error.m_Robot[i].pos.y, m_error.m_Robot[i].angle );
//			else
//				fprintf( fp, "0\t%lf\t%lf\t%lf\n", m_error.m_Robot[i].pos.x, m_error.m_Robot[i].pos.y, m_error.m_Robot[i].angle );
//		}


		m_error.m_Opp[i].pos = CPointDouble(0,0);

		if( VisionInfo.m_Opp[i].state == OBJECT_STATE_REAL )
		{
			m_error.m_Opp[i].pos = VisionInfo.m_Opp[i].pos-m_objects[SYNCH_TIME_CURRENT].m_Robot[i].pos;

			m_objects[SYNCH_TIME_CURRENT].m_Opp[i].state = OBJECT_STATE_REAL;
			m_objects[SYNCH_TIME_CURRENT].m_Opp[i].pos = VisionInfo.m_Opp[i].pos;
			m_objects[SYNCH_TIME_CURRENT].m_Opp[i].acceleration = VisionInfo.m_Opp[i].acceleration;
		}
		else if( VisionInfo.m_Opp[i].countLost < LOST_ROBOT_COUNT_MAX )
		{
			m_objects[SYNCH_TIME_CURRENT].m_Opp[i].state = OBJECT_STATE_VIRTUAL;
			if( m_objects[SYNCH_TIME_CURRENT-1].m_Opp[i].pos != StrategyInfo.m_Opp[i].pos
				|| m_objects[SYNCH_TIME_CURRENT-1].m_Opp[i].velocity != StrategyInfo.m_Opp[i].velocity
				|| m_objects[SYNCH_TIME_CURRENT-1].m_Opp[i].acceleration != StrategyInfo.m_Opp[i].acceleration )
			{
				m_error.m_Opp[i].pos = StrategyInfo.m_Opp[i].pos-m_objects[SYNCH_TIME_CURRENT].m_Robot[i].pos;

				m_objects[SYNCH_TIME_CURRENT].m_Opp[i].state = OBJECT_STATE_VIRTUAL;
				m_objects[SYNCH_TIME_CURRENT].m_Opp[i].pos = StrategyInfo.m_Opp[i].pos;
				m_objects[SYNCH_TIME_CURRENT].m_Opp[i].velocity = StrategyInfo.m_Opp[i].velocity;
				m_objects[SYNCH_TIME_CURRENT].m_Opp[i].acceleration = StrategyInfo.m_Opp[i].acceleration;
			}
		}
		else
		{
			m_objects[SYNCH_TIME_CURRENT].m_Opp[i].state = OBJECT_STATE_NOT_EXIST;
			if( m_objects[SYNCH_TIME_CURRENT-1].m_Opp[i].pos != StrategyInfo.m_Opp[i].pos
				|| m_objects[SYNCH_TIME_CURRENT-1].m_Opp[i].velocity != StrategyInfo.m_Opp[i].velocity
				|| m_objects[SYNCH_TIME_CURRENT-1].m_Opp[i].acceleration != StrategyInfo.m_Opp[i].acceleration )
			{
				m_error.m_Opp[i].pos = StrategyInfo.m_Opp[i].pos-m_objects[SYNCH_TIME_CURRENT].m_Robot[i].pos;

				m_objects[SYNCH_TIME_CURRENT].m_Opp[i].state = OBJECT_STATE_NOT_EXIST;
				m_objects[SYNCH_TIME_CURRENT].m_Opp[i].pos = StrategyInfo.m_Opp[i].pos;
				m_objects[SYNCH_TIME_CURRENT].m_Opp[i].velocity = StrategyInfo.m_Opp[i].velocity;
				m_objects[SYNCH_TIME_CURRENT].m_Opp[i].acceleration = StrategyInfo.m_Opp[i].acceleration;
			}
		}
	}

//	fclose(fp);
}

CObjectPositionInfo CSynchronousModule::PositionData()
{
	// Get PositionData <- Future
	return m_objects[SYNCH_TIME_CURRENT+m_DelayTime];
}

CObjectPositionInfo CSynchronousModule::PositionDataCurrent()
{
	return m_objects[SYNCH_TIME_CURRENT];
}

CObjectPositionInfo CSynchronousModule::PositionDataPast()
{
	return m_objects[SYNCH_TIME_CURRENT-m_DelayTime];
}

CObjectPositionInfo CSynchronousModule::PositionDataError()
{
	return m_error;
}

void CSynchronousModule::UpdateVelocityData(CObjectVelocityInfo &info)
{
	// Update PositionData -> Current
	m_velocity[SYNCH_TIME_CURRENT+m_DelayTime] = info;
}

CObjectVelocityInfo CSynchronousModule::VelocityData()
{
	// Get VelocityData <- Future
	return m_velocity[SYNCH_TIME_CURRENT+m_DelayTime];
}

void CSynchronousModule::SetDelayTime( int dt )
{
	m_DelayTime = dt;
}

void CSynchronousModule::TimePass()
{
	for( int t=1 ; t<SYNCH_TIME_N ; t++ )
	{
		m_objects[t-1] = m_objects[t];
		m_velocity[t-1] = m_velocity[t];
	}
}

void CSynchronousModule::Simulation( BOOL flag, int simulation_step )
{
	if( flag )
		CalcCurrentBallVelocity();

	for( int t=SYNCH_TIME_CURRENT ; t<SYNCH_TIME_N-1 ; t++ )
	{
		for( int i=0 ; i<POSITION_INFO_ROBOT_N ; i++ )
		{
			m_simulBox[i].SetPosition( m_objects[t].m_Robot[i].pos );
			m_simulBox[i].SetOrientationDegree( m_objects[t].m_Robot[i].orientation );
			double vl = m_velocity[t].m_VelocityLeft[i];
			double vr = m_velocity[t].m_VelocityRight[i];
			m_simulBox[i].SetVelocity( VelocityCommandType::LEFT_RIGHT, vl, vr );
			m_simulBox[i].SetBehavior( m_velocity[t].m_Behavior[i] );

			m_simulSphere[i].SetPositionPast( m_objects[t].m_Opp[i].pos );
			m_simulSphere[i].SetPosition( m_objects[t].m_Opp[i].pos );
			m_simulSphere[i].SetVelocity( m_objects[t].m_Opp[i].velocity );
			m_simulSphere[i].SetAcceleration( m_objects[t].m_Opp[i].acceleration );
		}

			m_simulSphere[POSITION_INFO_ROBOT_N].SetPositionPast( m_objects[t].m_Ball.pos );
			m_simulSphere[POSITION_INFO_ROBOT_N].SetPosition( m_objects[t].m_Ball.pos );
			m_simulSphere[POSITION_INFO_ROBOT_N].SetVelocity( m_objects[t].m_Ball.velocity );
			m_simulSphere[POSITION_INFO_ROBOT_N].SetAcceleration( m_objects[t].m_Ball.acceleration );


		double robot_length = 0.075;
		double point_dis = (robot_length*sqrt(2.0)/2.0);
		for( int i=0 ; i<POSITION_INFO_ROBOT_N ; i++ )
		{
			CPointDouble pos = m_simulBox[i].Position();
			double orientation = m_simulBox[i].OrientationRadian();
			
			m_simulBox_p[i][0].x = cos(orientation+M_PI*1/4);
			m_simulBox_p[i][0].y = sin(orientation+M_PI*1/4);
			m_simulBox_p[i][1].x = cos(orientation+M_PI*3/4);
			m_simulBox_p[i][1].y = sin(orientation+M_PI*3/4);
			m_simulBox_p[i][2].x = cos(orientation+M_PI*5/4);
			m_simulBox_p[i][2].y = sin(orientation+M_PI*5/4);
			m_simulBox_p[i][3].x = cos(orientation+M_PI*7/4);
			m_simulBox_p[i][3].y = sin(orientation+M_PI*7/4);

			m_simulBox_p[i][0] = (m_simulBox_p[i][0]* point_dis + pos);
			m_simulBox_p[i][1] = (m_simulBox_p[i][1]* point_dis + pos);
			m_simulBox_p[i][2] = (m_simulBox_p[i][2]* point_dis + pos);
			m_simulBox_p[i][3] = (m_simulBox_p[i][3]* point_dis + pos);
			m_simulBox_p[i][4] =  m_simulBox_p[i][0];
		}


		/*
			10 m/s
			0.01 m/ms
			0.30 m/frame
			0.005 m/simul
		*/

		bool bCollisionCheck = true;
		if( simulation_step == 0 )
		{
			bCollisionCheck =  false;
			simulation_step = 1;
		}

		for( int sec_i=0 ; sec_i<simulation_step ; sec_i++ )
		{
			double sec = m_SimulationTime/simulation_step;

			for( int i=0 ; i<POSITION_INFO_ROBOT_N ; i++ )
			{
				m_simulBox[i].RobotSimulationMove( sec );
				//m_simulBox[i].RobotEnemySimulationMove(sec);

				if( bCollisionCheck )
					CollisionCheck_Box( i );

				m_simulSphere[i].SimulationMove( sec );			

				if( bCollisionCheck )
					CollisionCheck_Sphere( i );
			}
				m_simulSphere[POSITION_INFO_ROBOT_N].SimulationMove( sec );
				//CollisionCheck_Sphere( ROBOT_N_ENOUGH );

			//CollisionCheck();
		}
		

		for( int i=0 ; i<POSITION_INFO_ROBOT_N ; i++ )
		{
			m_objects[t+1].m_Robot[i].state     = m_objects[t].m_Robot[i].state;
			m_objects[t+1].m_Robot[i].pos       = m_simulBox[i].Position();
			m_objects[t+1].m_Robot[i].orientation     = m_simulBox[i].OrientationDegree();

			m_objects[t+1].m_Opp[i].state    = m_objects[t].m_Opp[i].state;
			m_objects[t+1].m_Opp[i].pos      = m_simulSphere[i].Position();
			m_objects[t+1].m_Opp[i].velocity = m_simulSphere[i].Velocity();
			m_objects[t+1].m_Opp[i].acceleration = m_simulSphere[i].Acceleration();
		}
			m_objects[t+1].m_Ball.state    = m_objects[t].m_Ball.state;
			m_objects[t+1].m_Ball.pos      = m_simulSphere[POSITION_INFO_ROBOT_N].Position();
			m_objects[t+1].m_Ball.velocity = m_simulSphere[POSITION_INFO_ROBOT_N].Velocity();
			m_objects[t+1].m_Ball.acceleration = m_simulSphere[POSITION_INFO_ROBOT_N].Acceleration();
	}
}

void CSynchronousModule::CalcCurrentBallVelocity()
{
	if( m_objects[SYNCH_TIME_CURRENT].m_Ball.state != OBJECT_STATE_REAL )
		return;

	CPointDouble mean(0,0);

	int ball_n=SYNCH_TIME_CURRENT;
	for( int i=SYNCH_TIME_CURRENT ; i>SYNCH_TIME_CURRENT-ball_n ; i-- )
	{
		mean += m_objects[i].m_Ball.pos;
	}

	mean /= ball_n;

	double a=0;
	double b=0;
	double c=0;

	for( int i=SYNCH_TIME_CURRENT ; i>SYNCH_TIME_CURRENT-ball_n ; i-- )
	{
		a +=   ( m_objects[i].m_Ball.pos.x - mean.x )*( m_objects[i].m_Ball.pos.x - mean.x );
		b += 2*( m_objects[i].m_Ball.pos.x - mean.x )*( m_objects[i].m_Ball.pos.y - mean.y );
		c +=   ( m_objects[i].m_Ball.pos.y - mean.x )*( m_objects[i].m_Ball.pos.y - mean.y );
	}

	if( a==c || b==0 ) 
	{
		m_objects[SYNCH_TIME_CURRENT].m_Ball.velocity = CPointDouble(0,0);
		return;
	}

	double theta = atan2( b, a-c )/2;
	// -90 ~ theta ~90

	CPointDouble dis = (m_objects[SYNCH_TIME_CURRENT].m_Ball.pos - m_objects[SYNCH_TIME_CURRENT-ball_n].m_Ball.pos);

	// 2 1
	// 3 4

	if( fabs(theta) < M_PI/4 )
	{
		if( dis.x < 0 )
			theta += M_PI;
	}
	else
		if( dis.y > 0 )
		{
			if(theta < 0 )
				theta += M_PI;
		}
		else
		{
			if(theta > 0 )
				theta += M_PI;
		}
	

	double x = cos(theta) * dis.Distance() / ball_n / m_SimulationTime;
	double y = sin(theta) * dis.Distance() / ball_n / m_SimulationTime;

	m_objects[SYNCH_TIME_CURRENT].m_Ball.velocity = CPointDouble(x,y);
}
/*
void CSynchronousModule::CalcCurrentBallVelocity()
{
	if( m_objects[SYNCH_TIME_CURRENT].m_Ball.state != OBJECT_STATE_REAL )
		return;

	CPointDouble mean(0,0);

	int ball_n=SYNCH_TIME_CURRENT;
	for( int i=SYNCH_TIME_CURRENT ; i>SYNCH_TIME_CURRENT-ball_n ; i-- )
	{
		mean += m_objects[i].m_Ball.pos;
	}

	mean /= ball_n;

	double a=0;
	double b=0;
	double c=0;

	for( int i=SYNCH_TIME_CURRENT ; i>SYNCH_TIME_CURRENT-ball_n ; i-- )
	{
		a +=   ( m_objects[i].m_Ball.pos.x - mean.x )*( m_objects[i].m_Ball.pos.x - mean.x );
		b += 2*( m_objects[i].m_Ball.pos.x - mean.x )*( m_objects[i].m_Ball.pos.y - mean.y );
		c +=   ( m_objects[i].m_Ball.pos.y - mean.x )*( m_objects[i].m_Ball.pos.y - mean.y );
	}

	if( a==c || b==0 ) 
	{
		m_objects[SYNCH_TIME_CURRENT].m_Ball.velocity = CPointDouble(0,0);
		return;
	}

	double theta = atan2( b, a-c )/2;
	// -90 ~ theta ~90

	CPointDouble dis = (m_objects[SYNCH_TIME_CURRENT].m_Ball.pos - m_objects[SYNCH_TIME_CURRENT-ball_n].m_Ball.pos);

	// 2 1
	// 3 4

	if( fabs(theta) < M_PI/4 )
	{
		if( dis.x < 0 )
			theta += M_PI;
	}
	else
		if( dis.y > 0 )
		{
			if(theta < 0 )
				theta += M_PI;
		}
		else
		{
			if(theta > 0 )
				theta += M_PI;
		}
	

	double x = cos(theta) * dis.Distance() / ball_n / m_SimulationTime;
	double y = sin(theta) * dis.Distance() / ball_n / m_SimulationTime;

	m_objects[SYNCH_TIME_CURRENT].m_Ball.velocity = CPointDouble(x,y);
}
*/

void CSynchronousModule::Collision( CPointDouble col_dir, double m1, double m2, CPointDouble v1, CPointDouble v2, CPointDouble& v1_new, CPointDouble& v2_new )
{
	col_dir.Normalize();

	CPointDouble v1_col = col_dir * (  col_dir.x * v1.x + col_dir.y * v1.y );
	CPointDouble v2_col = col_dir * (  col_dir.x * v2.x + col_dir.y * v2.y );

	CPointDouble v1_self = v1 - v1_col;
	CPointDouble v2_self = v2 - v2_col;

	double v1_size = v1_col.Distance();
	double v2_size = v2_col.Distance();

	double v2_sign = v1_col.x*v2_col.x + v1_col.y*v2_col.y;

	if( v2_sign < 0 )
		v2_size = -v2_size;

	double C = 0.7;
	double v1_2 = ( (v2_size - v1_size) * C * m2 + v1_size*m1 + v2_size*m2 ) / (m1+m2);
	double v2_2 = ( (v1_size - v2_size) * C * m1 + v1_size*m1 + v2_size*m2 ) / (m1+m2);

	CPointDouble v1_col_new = col_dir;
	CPointDouble v2_col_new = col_dir;

	v1_col_new.Normalize( v1_2 );
	v2_col_new.Normalize( v2_2 );

	v1_new = v1_self + v1_col_new;
	v2_new = v2_self + v2_col_new;
}

void CSynchronousModule::CollisionCheck_Sphere( int p )
{
	int sphereN = POSITION_INFO_ROBOT_N+1;
	for( int i=0 ; i<sphereN ; i++ )
	{
		if( i==p )
			continue;

		double dis = (m_simulSphere[p].m_pos - m_simulSphere[i].m_pos).Distance();
		double min_dis = m_simulSphere[p].Radius() + m_simulSphere[i].Radius();
		if( min_dis > dis )
		{
			double m1 = m_simulSphere[p].m_mass;
			double m2 = m_simulSphere[i].m_mass;
			CPointDouble v1 = m_simulSphere[p].Velocity();
			CPointDouble v2 = m_simulSphere[i].Velocity();

			CPointDouble col_dir = m_simulSphere[i].m_pos - m_simulSphere[p].m_pos;

			CPointDouble v1_new;
			CPointDouble v2_new;

			Collision( col_dir, m1, m2, v1, v2, v1_new, v2_new );

			m_simulSphere[p].SetVelocity( v1_new );
			m_simulSphere[i].SetVelocity( v2_new );

			m_simulSphere[p].m_pos = m_simulSphere[i].m_pos - col_dir.Normalize() * min_dis;
		}
	}

	int boxN = POSITION_INFO_ROBOT_N;

	for( int i=0 ; i<boxN ; i++ )
	{
		CollisionCheck_SphereBox( i, p );
	}
}

void CSynchronousModule::CollisionCheck_SphereBox( int i, int p )
{
	double radius = m_simulSphere[p].Radius();
	CPointDouble pos = m_simulSphere[p].Position();
	double orientation = m_simulBox[i].OrientationDegree();

	for( int pi=0 ; pi<4 ; pi++ )
	{
		double dis_to_point = (m_simulBox_p[i][pi] - m_simulSphere[p].m_pos).Distance();
		double e_theta = (m_simulSphere[p].m_pos - m_simulBox_p[i][pi]).AngleDegree() - (m_simulBox[i].Position() - m_simulBox_p[i][pi]).AngleDegree();

		while( e_theta >  180.0 ) e_theta -= 360.0;
		while( e_theta < -180.0 ) e_theta += 360.0;

		if( dis_to_point < radius && (e_theta > 135 || e_theta < -135) )
		{
			CPointDouble col_point = m_simulBox_p[i][pi];

			double m1 = m_simulSphere[p].m_mass;
			double m2 = m_simulBox[i].m_mass;
			CPointDouble v1 = m_simulSphere[p].Velocity();

			double v2_size;
			if( pi == 0 || pi == 1 ) // left
			{
				v2_size = m_simulBox[i].VelocityLeft();
			}
			if( pi == 2 || pi == 3 ) // right
			{
				v2_size = m_simulBox[i].VelocityRight();
			}

			CPointDouble v2;
			v2.x = cos(m_simulBox[i].OrientationRadian());
			v2.y = sin(m_simulBox[i].OrientationRadian());
			v2 = v2 * v2_size;

			CPointDouble col_dir = col_point - pos;

			CPointDouble v1_new;
			CPointDouble v2_new;

			Collision( col_dir, m1, m2, v1, v2, v1_new, v2_new );

			m_simulSphere[p].SetVelocity( v1_new );

			m_simulSphere[p].m_pos = col_point - col_dir.Normalize() * radius;
			break;
		}


		double x1 = m_simulBox_p[i][pi].x;
		double y1 = m_simulBox_p[i][pi].y;
		double x2 = m_simulBox_p[i][pi+1].x;
		double y2 = m_simulBox_p[i][pi+1].y;

		double a = y2-y1;
		double b = x1-x2;
		double c = (x2-x1)*y1 - (y2-y1)*x1;

		double dis_to_line = fabs( a*pos.x + b*pos.y + c ) / sqrt( a*a + b*b );

		if( dis_to_line < radius )
		{
			int line1 = (pi-1+4)%4;
			int line2 = (pi+1  )%4;

			double ccw1, ccw2;
			{
				CPointDouble p1 = m_simulBox_p[i][line1];
				CPointDouble p2 = m_simulBox_p[i][line1+1];
				CPointDouble p3 = pos;
				ccw1 = p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - p1.x*p3.y - p2.x*p1.y  - p3.x*p2.y;
			}				
			{
				CPointDouble p1 = m_simulBox_p[i][line2];
				CPointDouble p2 = m_simulBox_p[i][line2+1];
				CPointDouble p3 = pos;
				ccw2 = p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - p1.x*p3.y - p2.x*p1.y  - p3.x*p2.y;
			}				

			if( ccw1 >= 0 && ccw2 >= 0 )
			{
				CPointDouble col_point;

				double col_dir_angle = ( m_simulBox_p[i][pi+1] - m_simulBox_p[i][pi] ).AngleRadian() + M_PI/2;

				col_point.x = cos( col_dir_angle );
				col_point.y = sin( col_dir_angle );

				col_point = col_point * dis_to_line + pos;

				double m1 = m_simulSphere[p].m_mass;
				double m2 = m_simulBox[i].m_mass;
				CPointDouble v1 = m_simulSphere[p].Velocity();

				double d_left, d_right;
				if( pi == 0 ) // left
				{
					d_left  = 0;
					d_right = 1;
				}
				if( pi == 1 ) // back
				{
					d_left  = (m_simulBox_p[i][1] - col_point).Distance();
					d_right = (m_simulBox_p[i][2] - col_point).Distance();
				}
				if( pi == 2 ) // right
				{
					d_left  = 1;
					d_right = 0;
				}
				if( pi == 3 ) // front
				{
					d_left  = (m_simulBox_p[i][0] - col_point).Distance();
					d_right = (m_simulBox_p[i][3] - col_point).Distance();
				}

				double v2_size = ( m_simulBox[i].VelocityLeft()*d_right + m_simulBox[i].VelocityRight()*d_left ) / (d_left+d_right);
					

				CPointDouble v2;
				v2.x = cos(m_simulBox[i].OrientationRadian());
				v2.y = sin(m_simulBox[i].OrientationRadian());
				v2 = v2 * v2_size;

				CPointDouble col_dir = col_point - pos;

				CPointDouble v1_new;
				CPointDouble v2_new;

				Collision( col_dir, m1, m2, v1, v2, v1_new, v2_new );

				m_simulSphere[p].SetVelocity( v1_new );

				m_simulSphere[p].m_pos = col_point - col_dir.Normalize() * radius;
				break;
			}
		}
	}
}

void CSynchronousModule::CollisionCheck_Box( int p )
{
	int sphereN = POSITION_INFO_ROBOT_N+1;

	for( int i=0 ; i<sphereN ; i++ )
	{
		CollisionCheck_SphereBox( p, i );
	}

	int boxN = POSITION_INFO_ROBOT_N;

	for( int i=0 ; i<boxN ; i++ )
	{
		if( i==p )
			continue;

		double dis = (m_simulBox[p].m_pos - m_simulBox[i].m_pos).Distance();
		double min_dis = 0.05*2;
		if( min_dis > dis )
		{
			/*
			double m1 = m_simulBox[p].m_mass;
			double m2 = m_simulBox[i].m_mass;
			
			CPointDouble v1;
				v1.x = cos(m_simulBox[p].AngleRadian());
				v1.y = sin(m_simulBox[p].AngleRadian());
				v1 = v1 * m_simulBox[p].GetVelocityLinear();
			CPointDouble v2;
				v2.x = cos(m_simulBox[i].AngleRadian());
				v2.y = sin(m_simulBox[i].AngleRadian());
				v2 = v2 * m_simulBox[i].VelocityLinear();
			*/
			CPointDouble col_dir = m_simulBox[i].m_pos - m_simulBox[p].m_pos;

			//CPointDouble v1_new;
			//CPointDouble v2_new;

			//Collision( col_dir, m1, m2, v1, v2, v1_new, v2_new );

			CPointDouble move_pos = m_simulBox[p].m_pos - m_simulBox[i].m_pos;
			move_pos.Normalize();
			move_pos *= (min_dis-dis)/2;

			m_simulBox[p].m_pos = m_simulBox[p].m_pos + move_pos;
			m_simulBox[i].m_pos = m_simulBox[i].m_pos - move_pos;
		}
	}
}


void CSynchronousModule::CollisionCheck()
{
	int sphereN = POSITION_INFO_ROBOT_N+1;
	for( int i=0 ; i<sphereN ; i++ )
	{
		//CPointDouble pos_S1_begin = m_simulSphere[i].PositionPast();
		//CPointDouble pos_S1_end   = m_simulSphere[i].Position();

		for( int j=i+1 ; j<sphereN ; j++ )
		{
			//CPointDouble pos_S2_begin = m_simulSphere[j].PositionPast();
			//CPointDouble pos_S2_end   = m_simulSphere[j].Position();


	
			double dis = (m_simulSphere[i].m_pos - m_simulSphere[j].m_pos).Distance();
			double min_dis = m_simulSphere[i].Radius() + m_simulSphere[j].Radius();

			if( min_dis > dis )
			{
				double m1 = m_simulSphere[i].m_mass;
				double m2 = m_simulSphere[j].m_mass;
				CPointDouble v1 = m_simulSphere[i].Velocity();
				CPointDouble v2 = m_simulSphere[j].Velocity();

				CPointDouble col_dir = m_simulSphere[j].m_pos - m_simulSphere[i].m_pos;

				CPointDouble v1_new;
				CPointDouble v2_new;

				Collision( col_dir, m1, m2, v1, v2, v1_new, v2_new );

				m_simulSphere[i].SetVelocity( v1_new );
				m_simulSphere[j].SetVelocity( v2_new );

				//m_simulSphere[i].m_pos = m_simulSphere[j].m_pos - col_dir.Normalize() * min_dis;
				//m_simulSphere[j].m_pos = m_simulSphere[i].m_pos + col_dir.Normalize() * min_dis/2;
			}
		}
	}

	int boxN = POSITION_INFO_ROBOT_N;
	for( int i=0 ; i<boxN ; i++ )
	{
		for( int j=i+1 ; j<boxN ; j++ )
		{
		}
	}


	for( int i=0 ; i<sphereN ; i++ )
	{
		for( int j=0 ; j<boxN ; j++ )
		{
		}
	}
}