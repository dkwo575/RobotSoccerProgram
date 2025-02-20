#pragma once

#include "ObjectPositionInfo.h"	// Added by ClassView
#include "ObjectVelocityInfo.h"	// Added by ClassView

#include "Ball.h"
#include "Robot.h"

#define SYNCH_TIME_N 10
#define SYNCH_TIME_CURRENT 7

#define LOST_ROBOT_COUNT_MAX 30

class CSynchronousModule
{
public:
	void SetGround( CGround* pGround );
	void SetSimulationTime( double t );
	void Simulation( BOOL flag, int simulation_step );
	void TimePass();
	void SetDelayTime( int dt );
	CObjectVelocityInfo VelocityData();
	void UpdateVelocityData( CObjectVelocityInfo& info );
	CObjectPositionInfo PositionData();
	CObjectPositionInfo PositionDataCurrent();
	CObjectPositionInfo PositionDataPast();
	CObjectPositionInfo PositionDataError();
	void UpdatePositionData(CObjectPositionInfo &VisionInfo, CObjectPositionInfo &StrategyInfo);

	CSynchronousModule(void);
	~CSynchronousModule(void);

protected:
	void CollisionCheck();
	void Collision( CPointDouble col_dir, double m1, double m2, CPointDouble v1, CPointDouble v2, CPointDouble& v1_new, CPointDouble& v2_new );
	void CollisionCheck_Sphere( int p );
	void CollisionCheck_Box( int p );
	void CollisionCheck_SphereBox( int i, int p );
	void CalcCurrentBallVelocity();
	// 0:past -> 100:future
	CObjectPositionInfo m_objects[SYNCH_TIME_N];
	CObjectVelocityInfo m_velocity[SYNCH_TIME_N];
	CObjectPositionInfo m_error;
	int m_DelayTime;


	double m_SimulationTime;

	CRobot* m_simulBox;
	CPointDouble m_simulBox_p[POSITION_INFO_ROBOT_N][5];

	CBall* m_simulSphere;
	CGround* m_pGround;
};

