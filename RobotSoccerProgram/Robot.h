#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "screenobject.h"

#include "PointDouble.h"	// Added by ClassView
#include "Ground.h"
#include "MissionSet.h"	// Added by ClassView

#include "Ball.h"
#include "Situation.h"
#include "PathCubicSpline.h"
#include "StrategyParameter.h"
#include "VelocityParameter.h"	// Added by ClassView
#include "VelocityParameter2.h"	// Added by ClassView

#include "StrategyGUI.h"

#define ROBOT_LENGTH 0.075
#define DISTANCE_ZERO 0.005
#define KICK_FAIL_DIS_ALPHA 0.2

#if !defined(OBJECT_STATE_NOT_EXIST)
#define OBJECT_STATE_NOT_EXIST	0
#define OBJECT_STATE_REAL		1
#define OBJECT_STATE_VIRTUAL	2
#endif

namespace VelocityCommandType
{
	enum Enum
	{
		LINEAR_ANGULAR_RADIAN,
		LINEAR_ANGULAR_DEGREE,
		LEFT_RIGHT           
	};
}


#define ROBOT_BEHAVIOR_STOP				32	
#define ROBOT_BEHAVIOR_GOALKEEP			2//8
#define ROBOT_BEHAVIOR_MOVE_FORWARD50	5				// 7~8 cm
#define ROBOT_BEHAVIOR_TURN_LEFT10		7
#define ROBOT_BEHAVIOR_TURN_LEFT20		8				// 20 도
#define ROBOT_BEHAVIOR_TURN_LEFT60		10				// 45 도
#define ROBOT_BEHAVIOR_TURN_RIGHT10		11			
#define ROBOT_BEHAVIOR_TURN_RIGHT20		12				// 20 도
#define ROBOT_BEHAVIOR_TURN_RIGHT60		14				// 45 도
#define ROBOT_BEHAVIOR_MOVE_RIGHT20		15				// 2.5 cm
#define ROBOT_BEHAVIOR_MOVE_RIGHT70		16				// 6~7 cm
#define ROBOT_BEHAVIOR_MOVE_LEFT20		17				// 2.5 cm
#define ROBOT_BEHAVIOR_MOVE_LEFT70		18				// 6 cm
#define ROBOT_BEHAVIOR_MOVE_BACKWARD	21				// -5 cm
#define ROBOT_BEHAVIOR_BACK_CYCLE		21				// 3 cm
#define ROBOT_BEHAVIOR_KICK_RIGHT_FOOT	22
#define ROBOT_BEHAVIOR_KICK_LEFT_FOOT	23
#define ROBOT_BEHAVIOR_KICK_RIGHTSIDE	24
#define ROBOT_BEHAVIOR_KICK_LEFTSIDE	25
#define ROBOT_BEHAVIOR_KICK_RIGHTBACK	26
#define ROBOT_BEHAVIOR_KICK_LEFTBACK	27
#define ROBOT_BEHAVIOR_FORWARD_CYCLE	30
#define ROBOT_BEHAVIOR_GOALKEEP_RIGHT   28
#define ROBOT_BEHAVIOR_GOALKEEP_LEFT    29


#define ROBOT_BEHAVIOR_TEST				4


namespace VelocityGenerationType
{
	const int Autoposition        = 0;
	const int MoveToStop          = 1;
	const int MoveTo              = 2;
	const int Escape              = 3;
	const int DefenseWall         = 4;
	const int N = 5;
}


class CRobot :
	public CScreenObject
{
public:
	CRobot(void);
	~CRobot(void);

	void UpdatePath();

	void SetBehavior(int behavior);
	int Behavior();


	int ID();
	void SetID( int id );
	void SetGround( CGround ground );

	CString Role();
	void SetRole( CStrategyGUI::Role role, bool bSetplay = false );
	
	
	void RobotSimulationMove( double sec );
	void RobotEnemySimulationMove(double sec);

	void SetBall(CBall ball);

	std::vector<CPointDouble> m_vecRobotHomePos;
	std::vector<CPointDouble> m_vecRobotOpponentPos;
	
	void ResetRobotObject();
	void AddRobotObject_Home( CPointDouble pos );
	void AddRobotObject_Opponent( CPointDouble pos );
	

	void ExecuteMission();

	// Mission
	void MissionAdd(CMission mission, bool bOverwrite = false );
	void MissionReset();
	void MissionComplete();
	CMission GetRecentMission();
	int GetMissionN();


	// UpdateMission
	void UpdateMission_GUI( bool bSetplay_init = false );

	// new
	// old
	double ExecuteMission_OrientationTo( int VP2M_id, double orientation, bool bMoveForwardOnly = false );
	CPointDouble ExecuteMission_MoveTo( int VP2M_id, CPointDouble pos, bool bMoveForwardOnly = false );
	void ExecuteMission_WallDefense();
	void ExecuteMission_FollowVector( int VP2M_id, CPointDouble vector, double dis );
	



	void GenerateVelocity_VP2( int VP2M_id, double errorOrientation, double errorDistance, double& AngularVelocityRadian, double& LinearVelocity );
	void SmoothVelocity( int VP2M_id );


	double CalcKickFitness( CPointDouble ball_pos, CPointDouble target_pos );

	void SetStrategyParameter( CStrategyParameter param );
	void SetVelocityParameter( CVelocityParameter param );
	void SetVelocityParameter2( int mission, CVelocityParameter2 param );




	bool IsExist();

	void Stop();
	void SetVelocity( int type, double v1, double v2 );
	void VelocityBackup();
	void VelocityStop();





	
	

	void SetTimeNow( double time );
	void SetTimeGame( double time );

	int State();
	void SetState( int state );
	
	void SetPosition( CPointDouble p );
	CPointDouble Position();
	void SetOrientationDegree( double orientation );
	void SetOrientationRadian( double orientation );
	double OrientationDegree();
	double OrientationRadian();
	
	void SetPositionCurrent( CPointDouble p );
	CPointDouble PositionCurrent();
	void SetOrientationCurrent( double orientation );
	double OrientationCurrent();
	
	void SetPositionPast( CPointDouble p );
	CPointDouble PositionPast();
	void SetOrientationPast( double orientation );
	double OrientationPast();

	void SetPositionError( CPointDouble p );
	void SetOrientationError( double error );
	CPointDouble PositionError();
	double OrientationError();

	double VelocityLeft();
	double VelocityRight();
	double VelocityLinear();
	double VelocityAngularDegree();
	double VelocityAngularRadian();

	double PastVelocityAngularDegree();
	double PastVelocityAngularRadian();
	double PastVelocityLinear();

	CString m_strMsg;
	
	
	CString Name();
	void SetName( CString name );

	CMissionSet m_MissionSet;
	CBall m_ball;

	CStrategyParameter m_StrategyParameter;
	CVelocityParameter m_VelocityParameter;
	CVelocityParameter2 m_VelocityParameter2[VelocityGenerationType::N];

	CPathCubicSpline m_staticPath;

	boolean enemy_set;

protected:

	bool m_bMoveBackward;

	double ccw(CPointDouble p1, CPointDouble p2, CPointDouble p3);
	bool Intersection( CPointDouble P1, CPointDouble P2, CPointDouble Q1, CPointDouble Q2, CPointDouble& Intersection );
	double DistanceToLine( CPointDouble line_P1, CPointDouble line_P2, CPointDouble P );
	CPointDouble InsideGround( CPointDouble A, CPointDouble B, CPointDouble W1, CPointDouble W2 );

	bool Intersection( CPointDouble A, CPointDouble B, CPointDouble C, CPointDouble D, CPointDouble& P, double& t );
	void AngleCorrectionDegree( double& angle, double min_angle = -180, double max_angle = 180 );
	void AngleCorrectionRadian( double& angle, double min_angle = -M_PI, double max_angle = M_PI );

	BOOL GenerateVelocity( CPathCubicSpline& path, double velocity_begin, double velocity_end, bool bMissionComplete );

	int m_behavior;

	bool m_bRoleSetplay;

	CString m_strName;
	CStrategyGUI::Role m_role;


	CPointDouble m_posTarget;


	double m_orientation;
	double m_enemyori;
	double m_timeNow;
	double m_timeGame;
	double m_timeRoleBegin;
	double m_timeMissionBegin;

	int m_id;

	CGround m_ground;


	int m_state;


	double m_orientationCurrent;
	
	CPointDouble m_posPast;
	CPointDouble m_enemyposPast;
	double m_orientationPast;
	

	CPointDouble m_posError;
	double m_orientationError;

	double m_LinearVelocity;
	double m_AngularVelocity;

	double m_pastLinearVelocity;
	double m_pastAngularVelocity;

	double m_prior_direction; // Deok-hwa

	// S.H.CHO
	double previous_linear_velocity;
	double previous_angular_velocity;

	double angular_position_error0;
	double angular_position_error1;
	double angular_position_error2;
	double angular_position_error3;
	double angular_position_error4;
	double angular_position_error5;
	double angular_position_error6;
	double angular_position_error7;
	double angular_position_error8;
	double angular_position_error9;
};

