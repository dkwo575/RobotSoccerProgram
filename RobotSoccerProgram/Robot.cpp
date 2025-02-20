#include "StdAfx.h"
#include "Robot.h"

#define _USE_MATH_DEFINES
#include <math.h>
double kickdistance = 0.15;
CRobot::CRobot(void)
{
	m_bRoleSetplay = false;
	m_strName = _T("");

	m_id = 0;
	m_state = OBJECT_STATE_NOT_EXIST;

	m_pos.x = 0;
	m_pos.y = 0;
	m_orientation = 0;

	m_enemypos.x = m_ground.Width();
	m_enemypos.x = m_ground.Height();
	m_enemyori = 180;
	
	m_posCurrent.x = 0;
	m_posCurrent.y = 0;
	m_orientationCurrent = 0;
	
	m_posPast.x = 0;
	m_posPast.y = 0;
	m_orientationPast = 0;

	m_posError.x = 0;
	m_posError.y = 0;
	m_orientationError = 0;

	m_AngularVelocity = 0;
	m_LinearVelocity = 0;


	m_posTarget = CPointDouble(-1,-1);

	
	m_state = OBJECT_STATE_NOT_EXIST;

	m_timeNow = 0;
	m_timeGame = 0;

	Stop();
}


CRobot::~CRobot(void)
{
}

void CRobot::AngleCorrectionDegree( double& angle, double min_angle, double max_angle )
{
	while( angle > max_angle ) angle -= 360;
	while( angle < min_angle ) angle += 360;
}

void CRobot::AngleCorrectionRadian( double& angle, double min_angle, double max_angle )
{
	while( angle > max_angle ) angle -= (M_PI*2);
	while( angle < min_angle ) angle += (M_PI*2);
}

void CRobot::SetTimeNow( double time ){ m_timeNow = time; }
void CRobot::SetTimeGame( double time ){ m_timeGame = time; }

int CRobot::ID(){ return m_id; }
void CRobot::SetID(int id){ m_id = id; }

void CRobot::SetState(int state){ m_state = state; }
int CRobot::State(){ return m_state; }

void CRobot::SetPosition(CPointDouble p){ 
	m_pos = p; 
	m_enemypos.x = m_ground.Width() - p.x;
	m_enemypos.y = m_ground.Height() - p.y;
}
CPointDouble CRobot::Position(){	return m_pos; }
void CRobot::SetPositionCurrent(CPointDouble p){ 
	m_posCurrent = p; 
	m_enemyposCurrent.x = m_ground.Width() - p.x;
	m_enemyposCurrent.y = m_ground.Height() - p.y;
}
CPointDouble CRobot::PositionCurrent(){ return m_posCurrent; }
void CRobot::SetPositionPast(CPointDouble p){ 
	m_posPast = p; 
	m_enemyposPast.x = m_ground.Width() - p.x;
	m_enemyposPast.y = m_ground.Height() - p.y;
}
CPointDouble CRobot::PositionPast(){ return m_posPast; }

void CRobot::SetStrategyParameter( CStrategyParameter param ){ m_StrategyParameter = param; }
void CRobot::SetVelocityParameter( CVelocityParameter param ){ m_VelocityParameter = param; }
void CRobot::SetVelocityParameter2( int mission, CVelocityParameter2 param ){ m_VelocityParameter2[mission] = param; }


void CRobot::SetOrientationDegree(double ori)
{
	AngleCorrectionDegree( ori );
	m_orientation = ori;
	if (ori + 180 > 180) {
		m_enemyori = ori - 180;
	} 
	else {
		m_enemyori = ori + 180;
	}
	
}

void CRobot::SetOrientationRadian(double orientation)
{
	orientation = orientation*180/M_PI;

	AngleCorrectionDegree( orientation );

	m_orientation = orientation;
	if (orientation + 180 > 180) {
		m_enemyori = orientation - 180;
	}
	else {
		m_enemyori = orientation + 180;
	}
}

double CRobot::OrientationDegree(){ return m_orientation; }
double CRobot::OrientationRadian(){ return m_orientation*M_PI/180.0; }

void CRobot::SetOrientationCurrent(double orientation)
{
	AngleCorrectionDegree( orientation );
	
	m_orientationCurrent = orientation;
}
double CRobot::OrientationCurrent(){ return m_orientationCurrent; }

void CRobot::SetOrientationPast(double orientation)
{
	AngleCorrectionDegree( orientation );
	
	m_orientationPast = orientation;
}
double CRobot::OrientationPast(){ return m_orientationPast; }

void CRobot::SetPositionError(CPointDouble p){ m_posError = p; }
void CRobot::SetOrientationError(double error)
{
	m_orientationError = error;
}
CPointDouble CRobot::PositionError(){ return m_posError; }
double CRobot::OrientationError(){ return m_orientationError; }

double CRobot::VelocityRight()
{
	return m_LinearVelocity + m_AngularVelocity * 0.0675 / 2.;
}

double CRobot::VelocityLeft()
{
	return m_LinearVelocity - m_AngularVelocity * 0.0675 / 2.;
}
double CRobot::VelocityLinear()
{
	return m_LinearVelocity;
}

double CRobot::VelocityAngularDegree()
{
	return m_AngularVelocity * 180.0 / M_PI;
}

double CRobot::VelocityAngularRadian()
{
	return m_AngularVelocity;
}

double CRobot::PastVelocityAngularDegree()
{
	return m_pastAngularVelocity * 180.0 / M_PI;
}

double CRobot::PastVelocityAngularRadian()
{
	return m_pastAngularVelocity;
}

double CRobot::PastVelocityLinear()
{
	return m_pastLinearVelocity;
}

void CRobot::SetGround(CGround ground){ m_ground = ground; }



bool CRobot::IsExist(){ return (m_state != OBJECT_STATE_NOT_EXIST ); }


void CRobot::SetVelocity(int type, double v1, double v2)
{
	if( type == VelocityCommandType::LINEAR_ANGULAR_RADIAN )
	{
		m_LinearVelocity = v1;
		m_AngularVelocity = v2;
	}
	else
	if( type == VelocityCommandType::LINEAR_ANGULAR_DEGREE )
	{
		m_LinearVelocity = v1;
		m_AngularVelocity = v2/180.0*M_PI;
	}
	else
	if( type == VelocityCommandType::LEFT_RIGHT )
	{
		m_LinearVelocity = (v1+v2)/2;
		m_AngularVelocity = (v2-v1)/0.0675;
	}
}

void CRobot::Stop()
{
	m_MissionSet.Reset();
	m_staticPath.Reset();

	SetVelocity( VelocityCommandType::LINEAR_ANGULAR_DEGREE, 0, 0 );

	previous_linear_velocity = 0;
	previous_angular_velocity = 0;

	angular_position_error0 = 0.;
	angular_position_error1 = 0.;
	angular_position_error2 = 0.;

	m_bRoleSetplay = false;
	m_role.name = "";

	SetBehavior( ROBOT_BEHAVIOR_STOP );
}

void CRobot::VelocityStop()
{
	SetVelocity( VelocityCommandType::LINEAR_ANGULAR_DEGREE, 0, 0 );
}

void CRobot::VelocityBackup()
{
	m_pastLinearVelocity = m_LinearVelocity;
	m_pastAngularVelocity = m_AngularVelocity;
}

CString CRobot::Role()
{
	return m_role.name;
}

void CRobot::SetRole( CStrategyGUI::Role role, bool bSetplay )
{
	//if( !m_MissionSet.HasMission() )
	//	m_bRoleSetplay = false;

	if( !m_bRoleSetplay )
	{
		m_bRoleSetplay = bSetplay;

		if( m_role.name != role.name )
		{
			m_MissionSet.Reset();
			//m_MissionSet.Reset_without_Setplay();
			m_role = role;
			m_bRoleSetplay = bSetplay;
		}
	}
}

void CRobot::SetBall(CBall ball){ m_ball = ball; }

void CRobot::ResetRobotObject()
{
	m_vecRobotHomePos.clear();
	m_vecRobotOpponentPos.clear();
}

void CRobot::AddRobotObject_Home( CPointDouble pos )
{
	if( pos.x < 0 ) return;
	if( pos.x > m_ground.Width() ) return;

	if( pos.y < 0 ) return;
	if( pos.y > m_ground.Height() ) return;

	m_vecRobotHomePos.push_back(pos);
}

void CRobot::AddRobotObject_Opponent( CPointDouble pos )
{
	if( pos.x < 0 ) return;
	if( pos.x > m_ground.Width() ) return;

	if( pos.y < 0 ) return;
	if( pos.y > m_ground.Height() ) return;

	m_vecRobotOpponentPos.push_back(pos);
}

void CRobot::MissionComplete()
{
	m_MissionSet.Complete();
}

void CRobot::MissionAdd(CMission mission, bool bOverwrite)
{
	m_MissionSet.Add( mission, bOverwrite );
}

void CRobot::MissionReset()
{
	m_MissionSet.Reset();
	m_staticPath.Reset();
}

double CRobot::DistanceToLine( CPointDouble line_P1, CPointDouble line_P2, CPointDouble P )
{
	double angle1 = ( line_P1 - line_P2 ).AngleRadian();
	double angle2 = (       P - line_P2 ).AngleRadian();

	double distance = ( P - line_P2 ).Distance() * sin( angle2 - angle1 );

	return distance;
}

bool CRobot::Intersection(CPointDouble P1, CPointDouble P2, CPointDouble Q1, CPointDouble Q2, CPointDouble &Intersection)
{
	P2 = P2 - P1;
	Q2 = Q2 - Q1;
	
	double k = -P2.x*Q2.y + P2.y*Q2.x;
	
	if( k == 0 )
		return false;
	
	
	double t = ( -Q2.y*(-P1.x+Q1.x) + Q2.x*(-P1.y+Q1.y) )/k;
	double s = ( -P2.y*(-P1.x+Q1.x) + P2.x*(-P1.y+Q1.y) )/k;
	
	CPointDouble Test1 = P1 + P2*t;
	CPointDouble Test2 = Q1 + Q2*s;

	Intersection = P1 + P2 * t;

	if( t < 0 || t > 1 || s < 0 || s > 1 )
		return false;

	return true;
}


bool CRobot::Intersection( CPointDouble _A, CPointDouble _B, CPointDouble _C, CPointDouble _D, CPointDouble& _P, double&t )
{
	double t1_c = (_A.y-_C.y)*(_D.x-_C.x) - (_A.x-_C.x)*(_D.y-_C.y);
	double t1_p = (_B.x-_A.x)*(_D.y-_C.y) - (_B.y-_A.y)*(_D.x-_C.x);

	if( t1_p == 0 )
		return false; // 평행

	double t1 = t1_c / t1_p;

	_P = _A + (_B-_A)*t1;
	t = t1;

	return true;
}


CPointDouble CRobot::InsideGround(CPointDouble A, CPointDouble B, CPointDouble W1, CPointDouble W2 )
{
	CPointDouble Result = B;
	CPointDouble Pwall;
	
	if(    B.x >= W1.x && B.y >= W1.y
		&& B.x <= W2.x && B.y <= W2.y )
		return Result;
	
	
	if( Intersection(
		A,
		B,
		CPointDouble( W1.x, W1.y ),
		CPointDouble( W1.x, W2.y ),
		Pwall ) )
	{
		Result = Pwall;
	}
	
	if( Intersection(
		A,
		B,
		CPointDouble( W2.x, W1.y ),
		CPointDouble( W2.x, W2.y ),
		Pwall ) )
	{
		Result = Pwall;
	}
	
	if( Intersection(
		A,
		B,
		CPointDouble( W1.x, W1.y ),
		CPointDouble( W2.x, W1.y ),
		Pwall ) )
	{
		Result = Pwall;
	}
	
	if( Intersection(
		A,
		B,
		CPointDouble( W1.x, W2.y ),
		CPointDouble( W2.x, W2.y ),
		Pwall ) )
	{
		Result = Pwall;
	}
	
	return Result;
}

void CRobot::UpdateMission_GUI( bool bSetplay_init )
{
	CMission missionCurrent = m_MissionSet.GetCurrentMission();

	//if( missionCurrent.type == CMission::GOALKEEPER )
	//	m_MissionSet.Reset();

	//if( missionCurrent.type == CMission::WALL )
	//	m_MissionSet.Reset();


	if( !m_MissionSet.HasMission() )
	if( !m_bRoleSetplay || bSetplay_init )
	{
		for( auto behavior = m_role.vecBehavior.begin() ; behavior < m_role.vecBehavior.end() ; behavior++ )
		{
			CMission mission = m_MissionSet.GetCurrentMission();
			mission.behavior = *behavior;

			if( behavior->type == StrategyGUI_BehaviorType::Goalkeep )
			{
				mission.text = _T("escape goalpost.start");
				mission.type = MissionType::Goalkeeper_Escape;
				mission.behavior.controlType = StrategyGUI_BehaviorControlType::Keep;
				MissionAdd( mission );

				mission.text = _T("kickout");
				mission.type = MissionType::Goalkeeper_Clear;
				mission.behavior.controlType = StrategyGUI_BehaviorControlType::Keep;
				MissionAdd( mission );

				mission.text = _T("basic goalKeeper");
				mission.type = MissionType::Goalkeeper_Basic;
				mission.behavior.controlType = StrategyGUI_BehaviorControlType::Keep;
				MissionAdd( mission );
				
				mission.text = _T("chase ball");
				mission.type = MissionType::Goalkeeper_Trace;
				mission.behavior.controlType = StrategyGUI_BehaviorControlType::Keep;
				MissionAdd( mission );
			}

			if( behavior->type == StrategyGUI_BehaviorType::Defense_Wall )
			{
				mission.text = _T("kickout");
				mission.type = MissionType::Defense_Wall_Clear;
				mission.behavior.controlType = StrategyGUI_BehaviorControlType::Keep;
				MissionAdd( mission );

				mission.text = _T("basic defense");
				mission.type = MissionType::Defense_Wall;
				mission.behavior.controlType = StrategyGUI_BehaviorControlType::Keep;
				MissionAdd( mission );

				mission.text = _T("chase ball");
				mission.type = MissionType::Defense_Wall_Trace;
				mission.behavior.controlType = StrategyGUI_BehaviorControlType::Keep;
				MissionAdd( mission );
			}

			if( behavior->type == StrategyGUI_BehaviorType::MoveTo )
			{
				mission.text = _T("move");
				mission.type = MissionType::MoveTo;
				MissionAdd( mission );
			}

			if( behavior->type == StrategyGUI_BehaviorType::Kick_A )
			{
				mission.text = _T("kick");
				mission.type = MissionType::MoveToKick;
				MissionAdd( mission );
			}

			if( behavior->type == StrategyGUI_BehaviorType::OrientationTo )
			{
				mission.text = _T("change direction");
				mission.type = MissionType::OrientationTo;
				MissionAdd( mission );
			}

			if( behavior->type == StrategyGUI_BehaviorType::Wait )
			{
				mission.text = _T("wait");
				mission.type = MissionType::Wait;
				m_timeRoleBegin = m_timeGame;
				MissionAdd( mission );
			}

			if( behavior->type == StrategyGUI_BehaviorType::Velocity )
			{
				mission.text = _T("command velocity.start");
				mission.type = MissionType::ManualVelocity;
				MissionAdd( mission );
			}

			if( behavior->type == StrategyGUI_BehaviorType::Kick_B )
			{
				mission.text = _T("wait&kick");
				mission.type = MissionType::WaitAndKick;
				MissionAdd( mission );
			}

			// New Action
			if (behavior->type == StrategyGUI_BehaviorType::Corner_Kick)
			{
				mission.text = _T("corner kick");
				mission.type = MissionType::CornerKick;
				MissionAdd(mission);
			}
		}
	}
}

void CRobot::ExecuteMission()
{
	bool bAllMissionComplete = true;

	for( int i=0 ; i<m_MissionSet.MissionN() ; i++ )
	{
		CMission mission = m_MissionSet.GetMission( i );

		bool bActiveMission = false;

		if( mission.bComplete )
			continue;

		switch( mission.type )
		{
		case MissionType::Goalkeeper_Escape:
			// ACTION/BEHAVIORTYPE: GOALKEEPER, Escape
			{
				// VelocityGenerationType::DefenseWall

				if(	mission.text == _T("escape goalpost.start") )
				{
					double x_distance_in_goal = 0.02;
					double robot_size = 0.075;

					if( Position().x < mission.behavior.options.goalkeep.x_pos - 0.02 
					 && Position().y < m_ground.Height()/2 + (m_ground.Goalsize()/2) 
					 && Position().y > m_ground.Height()/2 - (m_ground.Goalsize()/2) )
					{ 
						mission.text = _T("escape goalpost");
					}
					else
					{
						mission.text = _T("escape goalpost.end");
					}
				}


				if(	mission.text == _T("escape goalpost") )
				{
					CPointDouble target_pos( mission.behavior.options.goalkeep.x_pos, m_ball.Position().y );
						double robot_size = 0.075;
						target_pos.y = min( target_pos.y, m_ground.Height()/2 + (m_ground.Goalsize()/2 - robot_size/2) );
						target_pos.y = max( target_pos.y, m_ground.Height()/2 - (m_ground.Goalsize()/2 - robot_size/2) );

					double errorOrientation_forward  =  90 - OrientationDegree();
					double errorOrientation_backward = -90 - OrientationDegree();
					AngleCorrectionDegree( errorOrientation_forward );
					AngleCorrectionDegree( errorOrientation_backward );

					double errorOrientation = min( errorOrientation_forward, errorOrientation_backward );
							
					double errorPositionStop = 0.005;
					if( ExecuteMission_MoveTo( VelocityGenerationType::DefenseWall, target_pos ).Distance() < errorPositionStop )
					{
						//double errorOrientationStop = 3;
						//if(	ExecuteMission_OrientationTo( VelocityGenerationType::DefenseWall, 90 ) < errorOrientationStop )
						//{
							mission.text = _T("escape goalpost.end");
							SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );
						//}
					}

					mission.posDestination = target_pos;
					//mission.posDestination.x = m_ground.Width() - target_pos.x;
					//mission.posDestination.y = m_ground.Height() - target_pos.y;
				}

				if(	mission.text == _T("escape goalpost.end") )
				{
					mission.text = _T("escape goalpost.start");

					SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );

					if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
						mission.bComplete = true;
				}
				else
				{
					bActiveMission = true;
				}

				m_MissionSet.Change( i, mission );
			}
			break;

		case MissionType::Goalkeeper_Clear :
			// ACTION/BEHAVIORTYPE: GOALKEEPER, Kick Out
			{
				// VelocityGenerationType::DefenseWall

				mission.text = _T("kickout");

				double ball_speed_move = mission.behavior.options.goalkeep.clear_ball_speed;
		
				double tmp = m_ball.Velocity().Distance();

				if( m_ball.Position().x < mission.behavior.options.goalkeep.clear_x_size
				 && m_ball.Position().y < m_ground.Height()/2 + mission.behavior.options.goalkeep.clear_y_size
				 && m_ball.Position().y > m_ground.Height()/2 - mission.behavior.options.goalkeep.clear_y_size
				 && m_ball.Velocity().Distance() < ball_speed_move )
				{
					// 걷어내기 영역

					//double robot_size = 0.075;
					//if( m_ball.Velocity().Distance() < ball_speed_move && Position().x + robot_size/2 < m_ball.Position().x )
					//{
					//	// 정면
						CPointDouble target_pos = m_ball.Position();
					
						ExecuteMission_MoveTo( VelocityGenerationType::DefenseWall, target_pos ).Distance();
						bActiveMission = true;
					//}
					//else
					//if( m_ball.Position().x <= Position().x + robot_size/2 )
					//{
					//}


					mission.posDestination = target_pos;
					//mission.posDestination.x = m_ground.Width() - target_pos.x;
					//mission.posDestination.y = m_ground.Height() - target_pos.y;
				}
				else
				{
					SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );

					if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
						mission.bComplete = true;					
				}

				m_MissionSet.Change( i, mission );
			}
			break;

		case MissionType::Goalkeeper_Basic:
			// ACTION/BEHAVIORTYPE: GOALKEEPER, Basic
			{
				// VelocityGenerationType::DefenseWall

				mission.text = _T("basic goalkeeper");

				CPointDouble target_pos( mission.behavior.options.goalkeep.x_pos, m_ball.Position().y );
					double robot_size = 0.075;
					target_pos.y = min( target_pos.y, m_ground.Height()/2 + mission.behavior.options.goalkeep.y_size );
					target_pos.y = max( target_pos.y, m_ground.Height()/2 - mission.behavior.options.goalkeep.y_size );
					//target_pos.y = m_ball.Position().y /2;

					//TODU
					/*
					if (m_ball.Position().x >m_ground.Width()/2){
					
						target_pos.y = m_ground.Height()/2;
					}else


					if (m_ball.Position().x <= mission.behavior.options.goalkeep.x_pos*2){

						if (m_ball.Position().y >= m_ground.Height()/2){
							target_pos.y = m_ground.Height()/2 + mission.behavior.options.goalkeep.y_size;
						}
						if(m_ball.Position().y <= m_ground.Height()/2){
								target_pos.y = m_ground.Height()/2 - mission.behavior.options.goalkeep.y_size;
						}


					}else			if (m_ball.Position().y >= m_ground.Height()/2){
						target_pos.y = (m_ball.Position().y - m_ground.Height()/2)/(m_ground.Height()/2) * mission.behavior.options.goalkeep.y_size  + m_ground.Height()/2;
					}else {
						target_pos.y = m_ground.Height()/2 - (m_ground.Height()/2-m_ball.Position().y)/(m_ground.Height()/2) * mission.behavior.options.goalkeep.y_size ;
					
					}
					*/
					
				double errorOrientation_forward  =  90 - OrientationDegree();
				double errorOrientation_backward = -90 - OrientationDegree();
				AngleCorrectionDegree( errorOrientation_forward );
				AngleCorrectionDegree( errorOrientation_backward );

				double errorOrientation = min( errorOrientation_forward, errorOrientation_backward );
							

				double errorPositionStop = 0.02;
				if( ExecuteMission_MoveTo( VelocityGenerationType::DefenseWall, target_pos ).Distance() < errorPositionStop )
				{
					double errorOrientationStop = 5;
					if(	ExecuteMission_OrientationTo( VelocityGenerationType::DefenseWall, 90 ) < errorOrientationStop )
					{
						SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );

						if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
							mission.bComplete = true;
					}
					else
					{
						bActiveMission = true;
					}
				}
				else
				{
					bActiveMission = true;
				}

				mission.posDestination = target_pos;
				//mission.posDestination.x = m_ground.Width() - target_pos.x;
				//mission.posDestination.y = m_ground.Height() - target_pos.y;
				m_MissionSet.Change( i, mission );
			}
			break;

		case MissionType::Goalkeeper_Trace:
			// ACTION/BEHAVIORTYPE: GOALKEEPER, Chase Ball
			{
				mission.text = _T("chase ball");

				double ball_speed_move = 0.02;
				double robot_size = 0.075;
				if( //m_ball.Velocity().Distance() < ball_speed_move
				  m_ball.Position().x < Position().x + robot_size/2 )
				{
						SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );

						if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
							mission.bComplete = true;
				}
				else
				{
					if( m_ball.Velocity().y < 0.002 )
					{
						SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );

						if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
							mission.bComplete = true;
					}
					else
					if( m_ball.Position().y > m_ground.Height()/2 + mission.behavior.options.goalkeep.y_size
					 || m_ball.Position().y < m_ground.Height()/2 - mission.behavior.options.goalkeep.y_size )
					{
						SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );

						if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
							mission.bComplete = true;
					}
					else
					{
						CPointDouble target_pos( mission.behavior.options.goalkeep.x_pos, m_ball.Position().y );
							double robot_size = 0.075;
							target_pos.y = min( target_pos.y, m_ground.Height()/2 + mission.behavior.options.goalkeep.y_size );
							target_pos.y = max( target_pos.y, m_ground.Height()/2 - mission.behavior.options.goalkeep.y_size );

						double errorOrientation_forward  =  90 - OrientationDegree();
						double errorOrientation_backward = -90 - OrientationDegree();
						AngleCorrectionDegree( errorOrientation_forward );
						AngleCorrectionDegree( errorOrientation_backward );

						double errorOrientation = min( errorOrientation_forward, errorOrientation_backward );
							


						ExecuteMission_OrientationTo( VelocityGenerationType::DefenseWall, 90 );

						double error_y = target_pos.y - Position().y;

						if( OrientationDegree() > 0 )
						{
							m_LinearVelocity =  m_ball.Velocity().y + error_y;
						}
						else
						{
							m_LinearVelocity = -(m_ball.Velocity().y + error_y);
						}
				
						SmoothVelocity( VelocityGenerationType::DefenseWall );

						bActiveMission = true;
					}
				}


				m_MissionSet.Change( i, mission );
			}
			break;


		case MissionType::Defense_Wall_Clear :
			// ACTION/BEHAVIORTYPE: DEFENSE, Kick Out
			{
				// VelocityGenerationType::DefenseWall

				mission.text = _T("kickout");

				CPointDouble A         = mission.behavior.options.defense_wall.posA;
				CPointDouble B         = mission.behavior.options.defense_wall.posB;
				double x_clear_size    = mission.behavior.options.defense_wall.clear_x_size;
				double ball_speed_move = mission.behavior.options.defense_wall.clear_ball_speed;


				CPointDouble P = A;
				CPointDouble d = (B-A).Normalize();

				CPointDouble Ball_minus_P = (m_ball.Position() - P );
				double t = Ball_minus_P.x * d.x + Ball_minus_P.y * d.y;
				CPointDouble H = P + d*t;

				CPointDouble A2;
				CPointDouble B2; 
				A2.x = A.x + cos( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
				A2.y = A.y + sin( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
				B2.x = B.x + cos( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
				B2.y = B.y + sin( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;

				if( ccw(  A, A2, m_ball.Position() ) <= 0
				 && ccw( A2, B2, m_ball.Position() ) <= 0
				 && ccw( B2,  B, m_ball.Position() ) <= 0
				 && ccw(  B,  A, m_ball.Position() ) <= 0
				 && m_ball.Velocity().Distance() < ball_speed_move )
				{
					// Stripping area
					CPointDouble target_pos = m_ball.Position();
					
					ExecuteMission_MoveTo( VelocityGenerationType::DefenseWall, target_pos ).Distance();
					bActiveMission = true;

					mission.posDestination = target_pos;
					//mission.posDestination.x = m_ground.Width() - target_pos.x;
					//mission.posDestination.y = m_ground.Height() - target_pos.y;
				}
				else
				{
					SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );

					if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
						mission.bComplete = true;
				}

				m_MissionSet.Change( i, mission );
			}
			break;

		case MissionType::Defense_Wall:
			// ACTION/BEHAVIORTYPE: DEFENSE, Basic
			{
				// VelocityGenerationType::DefenseWall

				mission.text = _T("basic defense");

				CPointDouble A         = mission.behavior.options.defense_wall.posA;
				CPointDouble B         = mission.behavior.options.defense_wall.posB;
				double x_clear_size    = mission.behavior.options.defense_wall.clear_x_size;

				CPointDouble P = A;
				CPointDouble d = (B-A).Normalize();

				CPointDouble Ball_minus_P = (m_ball.Position() - P );
				double t = Ball_minus_P.x * d.x + Ball_minus_P.y * d.y;
				CPointDouble H = P + d*t;

				CPointDouble A2;
				CPointDouble B2; 
				A2.x = A.x + cos( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
				A2.y = A.y + sin( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
				B2.x = B.x + cos( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
				B2.y = B.y + sin( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;

				if( ccw( A, A2, m_ball.Position() ) > 0 )
				{
					H = A;
				}

				if( ccw( B2, B, m_ball.Position() ) > 0 )
				{
					H = B;
				}
					
				CPointDouble target_pos = H;
					
				double errorOrientation_forward  = (A-B).AngleDegree()      - OrientationDegree();
				double errorOrientation_backward = (A-B).AngleDegree() +180 - OrientationDegree();
				AngleCorrectionDegree( errorOrientation_forward );
				AngleCorrectionDegree( errorOrientation_backward );

				double errorOrientation = min( errorOrientation_forward, errorOrientation_backward );
							

				double errorPositionStop = 0.02;
				if( ExecuteMission_MoveTo( VelocityGenerationType::DefenseWall, target_pos ).Distance() < errorPositionStop )
				{
					double errorOrientationStop = 5;
					if(	ExecuteMission_OrientationTo( VelocityGenerationType::DefenseWall, (A-B).AngleDegree() ) < errorOrientationStop )
					{
						mission.text = _T("basic defense.A");
						SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );

						if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
							mission.bComplete = true;
					}
					else
					{
						mission.text = _T("basic defense.B");
						bActiveMission = true;
					}
				}
				else
				{
						mission.text = _T("basic defense.C");
					bActiveMission = true;
				}

				mission.posDestination = target_pos;
				//mission.posDestination.x = m_ground.Width() - target_pos.x;
				//mission.posDestination.y = m_ground.Height() - target_pos.y;
				m_MissionSet.Change( i, mission );
			}
			break;

		case MissionType::Defense_Wall_Trace:
			// ACTION/BEHAVIORTYPE: DEFENSE, Chase Ball
			{
				// VelocityGenerationType::DefenseWall

				mission.text = _T("chase ball");

				CPointDouble A         = mission.behavior.options.defense_wall.posA;
				CPointDouble B         = mission.behavior.options.defense_wall.posB;
				double x_clear_size    = mission.behavior.options.defense_wall.clear_x_size;

				CPointDouble P = A;
				CPointDouble d = (B-A).Normalize();

				CPointDouble Ball_minus_P = (m_ball.Position() - P );
				double t = Ball_minus_P.x * d.x + Ball_minus_P.y * d.y;
				CPointDouble H = P + d*t;

				CPointDouble A2;
				CPointDouble B2; 
				A2.x = A.x + cos( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
				A2.y = A.y + sin( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
				B2.x = B.x + cos( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
				B2.y = B.y + sin( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;

				if( ccw( A, A2, m_ball.Position() ) > 0 )
				{
					H = A;
				}

				if( ccw( B2, B, m_ball.Position() ) > 0 )
				{
					H = B;
				}

				double ball_speed_move = 0.02;
				double robot_size = 0.075;

				if( //m_ball.Velocity().Distance() < ball_speed_move
				  ccw( A, A2, m_ball.Position() ) > 0
				 || ccw( B2, B, m_ball.Position() ) > 0
				 || ccw( B,  A, m_ball.Position() ) > 0 )
				{
						SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );

						if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
							mission.bComplete = true;
				}
				else
				{
					double radian_AB = (A-B).AngleRadian();
					double radian_Ball_AB = m_ball.Velocity().AngleRadian() - radian_AB;

					double ball_velocity_AB = cos( radian_Ball_AB ) * m_ball.Velocity().Distance();
					
					if( ball_velocity_AB < 0.002 )
						ball_velocity_AB = 0.0;

					//if( ball_velocity_AB < 0.002 )
					//{
					//	SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );
					//
					//	if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
					//		mission.bComplete = true;
					//}
					//else
					{
						CPointDouble target_pos = H;

						double errorOrientation_forward  =  90 - OrientationDegree();
						double errorOrientation_backward = -90 - OrientationDegree();
						AngleCorrectionDegree( errorOrientation_forward );
						AngleCorrectionDegree( errorOrientation_backward );

						double errorOrientation = min( errorOrientation_forward, errorOrientation_backward );
							


						ExecuteMission_OrientationTo( VelocityGenerationType::DefenseWall, (A-B).AngleDegree() );

						double error_y = target_pos.y - Position().y;

						if( OrientationDegree() > 0 )
						{
							m_LinearVelocity =  m_ball.Velocity().y + error_y;
						}
						else
						{
							m_LinearVelocity = -(m_ball.Velocity().y + error_y);
						}
				
						SmoothVelocity( VelocityGenerationType::DefenseWall );

						bActiveMission = true;
					}
				}


				m_MissionSet.Change( i, mission );
			}
			break;

		case MissionType::MoveTo :
			// ACTION/BEHAVIORTYPE: MOVE TO
			{
				// VelocityGenerationType::MoveToStop

				mission.text = _T("move");

				CPointDouble target_pos;
				if( mission.behavior.options.move_to.destination.bBall )
				{
					target_pos = m_ball.Position();
				}
				else
				{
					target_pos = mission.behavior.options.move_to.destination.pos;
				}

				double errorPositionStop = mission.behavior.options.move_to.destination.error;
				if( ExecuteMission_MoveTo( VelocityGenerationType::MoveToStop, target_pos ).Distance() < errorPositionStop )
				{
					SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );

					if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
						mission.bComplete = true;
				}
				else
				{
					bActiveMission = true;
				}

				mission.posDestination = target_pos;
				//mission.posDestination.x = m_ground.Width() - target_pos.x;
				//mission.posDestination.y = m_ground.Height() - target_pos.y;


				m_MissionSet.Change( i, mission );
			}
			break;

		case MissionType::MoveToKick :
			// ACTION/BEHAVIORTYPE: KICK A
			{
				// VelocityGenerationType::MoveTo
				CBall ballHit = m_ball;
				ballHit.SimulationMove( 0.2 );

				// 회전하다가 공이 멀어지면 다시 이동으로 전환
				// 슛이 가능한 각도에서 접근할때 회전 접근 위치가 안좋음. 원의 접선 방정식 만들어서 써야함
				// 이에 따라 회전 시간 조절

				// If the ball moves away while rotating, it switches back to movement
				// Rotation approach position is bad when approaching from an angle that can shoot. You have to create and write the tangent equation of the circle
				// Adjust the rotation time accordingly

				CPointDouble A = Position();
				CPointDouble B;

				if( mission.behavior.options.kick_A.direction.bPosDirection )
				{
					B = mission.behavior.options.kick_A.direction.posDirection;
				}
				else
				{
					B.x = Position().x + cos( mission.behavior.options.kick_A.direction.direction * M_PI / 180 ) * 0.20;
					B.y = Position().y + sin( mission.behavior.options.kick_A.direction.direction * M_PI / 180 ) * 0.20;
				}

				CPointDouble target_pos = A;
				double robot_size = 0.075;
				
				if( mission.text != _T("kick.approach.rotate") )
				{
					double dis_ball_to_wait_line = DistanceToLine( A, B, ballHit.Position() );
					
					double angle_robot_to_ball = ( ballHit.Position() - Position() ).AngleDegree();
					double angle_robot_to_B    = (                 B - Position() ).AngleDegree();
					double angle_check = angle_robot_to_ball - angle_robot_to_B;
					AngleCorrectionDegree( angle_check );

					double orientationError = angle_robot_to_B - OrientationDegree();
					AngleCorrectionDegree( orientationError );

					if( fabs(dis_ball_to_wait_line) < robot_size/2
					 && fabs(angle_check) < 90
					 && fabs(orientationError) < 10 )
					{
						mission.text = _T("kick");
							
						target_pos = B;

						double errorPositionStop = 0.01;
						if( ExecuteMission_MoveTo( VelocityGenerationType::MoveTo, target_pos ).Distance() < errorPositionStop )
						{
							if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
								mission.bComplete = true;
						}
						else
						{
							bActiveMission = true;
						}
					}
					else
					{
						// target 위치 후보군 2개 만들어서 가까운 곳으로 선택 (했음)
						// 단, 경기장 밖 후보군은 제외하도록...

						// Make two candidates for target location and select it as a nearby one (I chose)
						// However, exclude candidates outside the stadium...

						CPointDouble tmp = ballHit.Position() + ( m_ball.Position() - B ).Normalize() * robot_size/2;
						double rad_ball_to_B = ( B - ballHit.Position() ).AngleRadian();

						int TurnDirection = -1; // Bottom: Turn right
						if( ccw( Position(), ballHit.Position(), B ) >= 0 )
							TurnDirection = 1;


						CPointDouble posCenter;
						posCenter.x = tmp.x + cos( rad_ball_to_B + TurnDirection * M_PI/2 ) * robot_size;
						posCenter.y = tmp.y + sin( rad_ball_to_B + TurnDirection * M_PI/2 ) * robot_size;	

						CPointDouble posCenter_planB;
						posCenter_planB.x = tmp.x + cos( rad_ball_to_B - TurnDirection * M_PI/2 ) * robot_size;
						posCenter_planB.y = tmp.y + sin( rad_ball_to_B - TurnDirection * M_PI/2 ) * robot_size;	

						if( posCenter.x < robot_size/2
						 || posCenter.y < robot_size/2
						 || posCenter.x > m_ground.Width() - robot_size/2
						 || posCenter.y > m_ground.Height() - robot_size/2 )
						{
							posCenter = posCenter_planB;
							TurnDirection = - TurnDirection;
						}


						mission.tmp = posCenter;

						double disRobotToCenter = (Position() - posCenter).Distance();
						double radius = robot_size/2;

						if( disRobotToCenter > radius )
						{
							double disRobotToTarget = sqrt( disRobotToCenter*disRobotToCenter - radius*radius );

							double rad_Target = atan2( disRobotToTarget, radius );

							double rad_CenterToRobot = ( Position() - posCenter ).AngleRadian();


							target_pos.x = posCenter.x + cos( rad_CenterToRobot + TurnDirection * rad_Target ) * radius;
							target_pos.y = posCenter.y + sin( rad_CenterToRobot + TurnDirection * rad_Target ) * radius;
						}
						


						double errorPositionStop = 0.03;
						if( ExecuteMission_MoveTo( VelocityGenerationType::MoveTo, target_pos ).Distance() < errorPositionStop )
						{
							mission.text = _T("kick.approach.rotate");
							m_timeMissionBegin = m_timeGame;


							// 로봇 위치 방향에 따라 ==> 회전 방향 주의, 속도 변경?

							// Depending on the robot position direction ==> Pay attention to the direction of rotation, change the speed?
							mission.behavior.options.manual_velocity.time = 0.5;
							mission.behavior.options.manual_velocity.vLinear  = 0.30;
							mission.behavior.options.manual_velocity.vAngular = 480 * TurnDirection;

							if( m_bMoveBackward )
							{
								mission.behavior.options.manual_velocity.vLinear  = -mission.behavior.options.manual_velocity.vLinear;
							}

						}
						else
						{
							bActiveMission = true;

							mission.text = _T("kick.approach");
						}
					}
				}

				if( mission.text == _T("kick.approach.rotate") )
				{
					if( m_timeMissionBegin + mission.behavior.options.manual_velocity.time < m_timeGame )
					{
						//if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
							mission.bComplete = true;

						mission.text = _T("kick");
						SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );
					}
					else
					{
						SetVelocity( VelocityCommandType::LINEAR_ANGULAR_DEGREE, mission.behavior.options.manual_velocity.vLinear, mission.behavior.options.manual_velocity.vAngular );
						bActiveMission = true;
					}
				}

				mission.posDestination = target_pos;
				//mission.posDestination.x = m_ground.Width() - target_pos.x;
				//mission.posDestination.y = m_ground.Height() - target_pos.y;
				m_MissionSet.Change( i, mission );
			}
			break;

		case MissionType::OrientationTo :
			// ACTION/BEHAVIORTYPE: ORIENTATION
			{
				// VelocityGenerationType::MoveToStop

				mission.text = _T("change direction");

				double target_orientation;
				if( mission.behavior.options.orientation.orientation.bPosDirection )
				{
					target_orientation = ( mission.behavior.options.orientation.orientation.posDirection - Position() ).AngleDegree();
				}
				else
				{
					target_orientation = mission.behavior.options.orientation.orientation.direction;
				}

				double errorOrientationStop = 3.0;
				if( ExecuteMission_OrientationTo( VelocityGenerationType::MoveToStop, target_orientation, true ) < errorOrientationStop )
				{
					SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );

					if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
						mission.bComplete = true;
				}
				else
				{
					bActiveMission = true;
				}

				mission.orientationDestination = target_orientation;
				m_MissionSet.Change( i, mission );
			}
			break;

		case MissionType::Wait :
			// ACTION/BEHAVIORTYPE: WAIT
			{
				mission.text = _T("wait");

				if( m_timeRoleBegin + mission.behavior.options.wait.time < m_timeGame )
				{
					if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
						mission.bComplete = true;
				}
				else
				{
					SetVelocity( VelocityCommandType::LINEAR_ANGULAR_DEGREE, 0, 0 );
					bActiveMission = true;
				}


				m_MissionSet.Change( i, mission );
			}
			break;

		case MissionType::ManualVelocity :
			// ACTION/BEHAVIORTYPE: VELOCITY
			{
				if( mission.text == _T("command velocity.start") )
				{
					m_timeMissionBegin = m_timeGame;
					mission.text = _T("command velocity");
				}
				
				if( mission.text == _T("command velocity") )
				{
					if( m_timeMissionBegin + mission.behavior.options.manual_velocity.time < m_timeGame )
					{
						//if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
							mission.bComplete = true;

						
						mission.text = _T("command velocity.start");
						SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );
					}
					else
					{
						SetVelocity( VelocityCommandType::LINEAR_ANGULAR_DEGREE, mission.behavior.options.manual_velocity.vLinear, mission.behavior.options.manual_velocity.vAngular );
						bActiveMission = true;
					}
				}

				m_MissionSet.Change( i, mission );
			}
			break;

		case MissionType::WaitAndKick :
			// ACTION/BEHAVIORTYPE: KICK B
			{
				// VelocityGenerationType::MoveToStop

				CPointDouble A         = mission.behavior.options.kick_B.posA;
				CPointDouble B         = mission.behavior.options.kick_B.posB;
				CPointDouble target_pos = A;


				double robot_size = 0.075;
				CBall ballHit= m_ball;
				ballHit.SimulationMove( 0.2 );

				mission.tmp = ballHit.Position();

				double dis_ball_to_wait_line = DistanceToLine( A, B, ballHit.Position() );
					
				double angle_robot_to_ball = ( ballHit.Position() - Position() ).AngleDegree();
				double angle_robot_to_B    = (                 B - Position() ).AngleDegree();
				double angle_check = angle_robot_to_ball - angle_robot_to_B;
				AngleCorrectionDegree( angle_check );

				if( fabs(dis_ball_to_wait_line) < robot_size/2 && fabs(angle_check) < 90 )
				{
					mission.text = _T("wait&kick.kick");
							
					target_pos = (B - Position()).Normalize() * 1 + Position();
/*
					if( mission.text == _T("킥.접근.회전") )
					{
						if( m_timeMissionBegin + mission.behavior.options.manual_velocity.time < m_timeGame )
						{
							//if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
								mission.bComplete = true;

							mission.text = _T("킥");
							SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );
						}
						else
						{
							SetVelocity( VelocityCommandType::LINEAR_ANGULAR_DEGREE, mission.behavior.options.manual_velocity.vLinear, mission.behavior.options.manual_velocity.vAngular );
							bActiveMission = true;
						}
					}
*/
				}
				else
				{
					mission.text = _T("wait&kick.wait");

					CPointDouble posKick;
					double t;
					bool bKick = Intersection( A, B, m_ball.Position(), m_ball.Position() + m_ball.Velocity(), posKick, t );

					double robot_size = 0.075;
					CPointDouble posWait = posKick + ( A-B ).Normalize() * 0.1;//robot_size;


					if( m_ball.Velocity().Distance() > 0.05 && bKick && 0 <= t && t <= 1 )
					{
						double directionError = (posKick - m_ball.Position()).AngleDegree() - m_ball.Velocity().AngleDegree();

						AngleCorrectionDegree( directionError );


						if( fabs(directionError) < 90 )
						{
							target_pos = posWait;
						}
					}
				}

				double errorOrientation_forward  = (A-B).AngleDegree()      - OrientationDegree();
				double errorOrientation_backward = (A-B).AngleDegree() +180 - OrientationDegree();
				AngleCorrectionDegree( errorOrientation_forward );
				AngleCorrectionDegree( errorOrientation_backward );

				double errorOrientation = min( errorOrientation_forward, errorOrientation_backward );
							

				double errorPositionStop = 0.01;


				int VG_id = VelocityGenerationType::MoveToStop;

				if( mission.text == _T("wait&kick.kick") )
					VG_id = VelocityGenerationType::MoveTo;

				if( ExecuteMission_MoveTo( VG_id, target_pos ).Distance() < errorPositionStop )
				{
					double errorOrientationStop = 3;
					if(	ExecuteMission_OrientationTo( VelocityGenerationType::DefenseWall, (A-B).AngleDegree() ) < errorOrientationStop )
					{
						SetVelocity( VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0 );
					}
					else
					{
						bActiveMission = true;
					}
				}
				else
				{
					bActiveMission = true;
				}

				mission.posDestination = target_pos;
				//mission.posDestination.x = m_ground.Width() - target_pos.x;
				//mission.posDestination.y = m_ground.Height() - target_pos.y;
				m_MissionSet.Change( i, mission );
			}
			break;

		//// NEW ACTION
		//case MissionType::CornerKick: 
		//	{

		//	}
		//	break;
		
		// New Action
		case MissionType::CornerKick:
			// ACTION/BEHAVIORTYPE: KICK A
		{
			// VelocityGenerationType::MoveTo
			CBall ballHit = m_ball;
			ballHit.SimulationMove(0.2);

			// 회전하다가 공이 멀어지면 다시 이동으로 전환
			// 슛이 가능한 각도에서 접근할때 회전 접근 위치가 안좋음. 원의 접선 방정식 만들어서 써야함
			// 이에 따라 회전 시간 조절

			// If the ball moves away while rotating, it switches back to movement
			// Rotation approach position is bad when approaching from an angle that can shoot. You have to create and write the tangent equation of the circle
			// Adjust the rotation time accordingly

			CPointDouble A = Position();
			CPointDouble B;

			if (mission.behavior.options.kick_A.direction.bPosDirection)
			{
				B = mission.behavior.options.kick_A.direction.posDirection;
			}
			else
			{
				B.x = Position().x + cos(mission.behavior.options.kick_A.direction.direction * M_PI / 180) * 0.20;
				B.y = Position().y + sin(mission.behavior.options.kick_A.direction.direction * M_PI / 180) * 0.20;
			}

			CPointDouble target_pos = A;
			double robot_size = 0.075;

			if (mission.text != _T("kick.approach.rotate"))
			{
				double dis_ball_to_wait_line = DistanceToLine(A, B, ballHit.Position());

				double angle_robot_to_ball = (ballHit.Position() - Position()).AngleDegree();
				double angle_robot_to_B = (B - Position()).AngleDegree();
				double angle_check = angle_robot_to_ball - angle_robot_to_B;
				AngleCorrectionDegree(angle_check);

				double orientationError = angle_robot_to_B - OrientationDegree();
				AngleCorrectionDegree(orientationError);

				if (fabs(dis_ball_to_wait_line) < robot_size / 2
					&& fabs(angle_check) < 90
					&& fabs(orientationError) < 10)
				{
					mission.text = _T("kick");

					target_pos = B;

					double errorPositionStop = 0.01;
					if (ExecuteMission_MoveTo(VelocityGenerationType::MoveTo, target_pos).Distance() < errorPositionStop)
					{
						if (mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once)
							mission.bComplete = true;
					}
					else
					{
						bActiveMission = true;
					}
				}
				else
				{
					// target 위치 후보군 2개 만들어서 가까운 곳으로 선택 (했음)
					// 단, 경기장 밖 후보군은 제외하도록...

					// Make two candidates for target location and select it as a nearby one (I chose)
					// However, exclude candidates outside the stadium...

					CPointDouble tmp = ballHit.Position() + (m_ball.Position() - B).Normalize() * robot_size / 2;
					double rad_ball_to_B = (B - ballHit.Position()).AngleRadian();

					int TurnDirection = -1; // Bottom: Turn right
					if (ccw(Position(), ballHit.Position(), B) >= 0)
						TurnDirection = 1;


					CPointDouble posCenter;
					posCenter.x = tmp.x + cos(rad_ball_to_B + TurnDirection * M_PI / 2) * robot_size;
					posCenter.y = tmp.y + sin(rad_ball_to_B + TurnDirection * M_PI / 2) * robot_size;

					CPointDouble posCenter_planB;
					posCenter_planB.x = tmp.x + cos(rad_ball_to_B - TurnDirection * M_PI / 2) * robot_size;
					posCenter_planB.y = tmp.y + sin(rad_ball_to_B - TurnDirection * M_PI / 2) * robot_size;

					if (posCenter.x < robot_size / 2
						|| posCenter.y < robot_size / 2
						|| posCenter.x > m_ground.Width() - robot_size / 2
						|| posCenter.y > m_ground.Height() - robot_size / 2)
					{
						posCenter = posCenter_planB;
						TurnDirection = -TurnDirection;
					}


					mission.tmp = posCenter;

					double disRobotToCenter = (Position() - posCenter).Distance();
					double radius = robot_size / 2;

					if (disRobotToCenter > radius)
					{
						double disRobotToTarget = sqrt(disRobotToCenter * disRobotToCenter - radius * radius);

						double rad_Target = atan2(disRobotToTarget, radius);

						double rad_CenterToRobot = (Position() - posCenter).AngleRadian();


						target_pos.x = posCenter.x + cos(rad_CenterToRobot + TurnDirection * rad_Target) * radius;
						target_pos.y = posCenter.y + sin(rad_CenterToRobot + TurnDirection * rad_Target) * radius;
					}



					double errorPositionStop = 0.03;
					if (ExecuteMission_MoveTo(VelocityGenerationType::MoveTo, target_pos).Distance() < errorPositionStop)
					{
						mission.text = _T("kick.approach.rotate");
						m_timeMissionBegin = m_timeGame;


						// 로봇 위치 방향에 따라 ==> 회전 방향 주의, 속도 변경?

						// Depending on the robot position direction ==> Pay attention to the direction of rotation, change the speed?
						mission.behavior.options.manual_velocity.time = 0.5;
						mission.behavior.options.manual_velocity.vLinear = 0.30;
						mission.behavior.options.manual_velocity.vAngular = 480 * TurnDirection;

						if (m_bMoveBackward)
						{
							mission.behavior.options.manual_velocity.vLinear = -mission.behavior.options.manual_velocity.vLinear;
						}

					}
					else
					{
						bActiveMission = true;

						mission.text = _T("kick.approach");
					}
				}
			}

			if (mission.text == _T("kick.approach.rotate"))
			{
				if (m_timeMissionBegin + mission.behavior.options.manual_velocity.time < m_timeGame)
				{
					//if( mission.behavior.controlType == StrategyGUI_BehaviorControlType::Once )
					mission.bComplete = true;

					mission.text = _T("kick");
					SetVelocity(VelocityCommandType::LINEAR_ANGULAR_RADIAN, 0, 0);
				}
				else
				{
					SetVelocity(VelocityCommandType::LINEAR_ANGULAR_DEGREE, mission.behavior.options.manual_velocity.vLinear, mission.behavior.options.manual_velocity.vAngular);
					bActiveMission = true;
				}
			}

			mission.posDestination = target_pos;
			//mission.posDestination.x = m_ground.Width() - target_pos.x;
			//mission.posDestination.y = m_ground.Height() - target_pos.y;
			m_MissionSet.Change(i, mission);
		}
		break;

		case MissionType::None :
			{
				mission.text = _T("stop");
				m_MissionSet.Change( i, mission );

				Stop();
			}
			break;

		}

		if( bActiveMission )
		{
			m_MissionSet.UpdateRecentMission( mission, i );
			bAllMissionComplete = false;
			break;
		}
	}

	if( bAllMissionComplete )
	{
		if( m_bRoleSetplay )
		{
			Stop();
		}
		else
		{
			for( int i=0 ; i<m_MissionSet.MissionN() ; i++ )
			{
				CMission mission = m_MissionSet.GetMission( i );

				if( mission.bTemporary )
				{
					m_MissionSet.DeleteMission( i );
					i--;
				}
				else
				{
					mission.bComplete = false;
					m_MissionSet.Change( i, mission );
				}
			}
		}
	}
}

double CRobot::ExecuteMission_OrientationTo( int VP2M_id, double orientation, bool bMoveForwardOnly )
{
	double errorDistance    = 0;
	double errorOrientation = orientation - OrientationDegree();
	AngleCorrectionDegree( errorOrientation );

	bool bMoveBackward = false;

	if( !bMoveForwardOnly && fabs(errorOrientation) > 90 )
	{
		bMoveBackward = true;

		errorOrientation += 180;
		AngleCorrectionDegree( errorOrientation );
	}

	GenerateVelocity_VP2( VP2M_id, errorOrientation, errorDistance, m_AngularVelocity, m_LinearVelocity );

	SmoothVelocity( VP2M_id );

	return fabs(errorOrientation);
}

CPointDouble CRobot::ExecuteMission_MoveTo( int VP2M_id, CPointDouble pos, bool bMoveForwardOnly )
{
	CPointDouble errorPosition = (pos - Position() );
	double errorDistance       = errorPosition.Distance();
	double errorOrientation    = errorPosition.AngleDegree() - OrientationDegree();
	AngleCorrectionDegree( errorOrientation );

	bool bMoveBackward = false;

	if( !bMoveForwardOnly && fabs(errorOrientation) > 90 )
	{
		bMoveBackward = true;

		errorOrientation += 180;
		AngleCorrectionDegree( errorOrientation );
	}

	GenerateVelocity_VP2( VP2M_id, errorOrientation, errorDistance, m_AngularVelocity, m_LinearVelocity );

	if( bMoveBackward )
	{
		m_LinearVelocity = -m_LinearVelocity;
	}

	SmoothVelocity( VP2M_id );

	m_bMoveBackward = bMoveBackward;

	return errorPosition;
}


double CRobot::ccw(CPointDouble p1, CPointDouble p2, CPointDouble p3)
{
	return p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - p1.x*p3.y - p2.x*p1.y  - p3.x*p2.y;
}


void CRobot::GenerateVelocity_VP2( int VP2M_id, double errorOrientation, double errorDistance, double& AngularVelocityRadian, double& LinearVelocity )
{
	double AngularVelocityDegree = ( m_VelocityParameter2[VP2M_id].m_dVMin
					+ (double)(m_VelocityParameter2[VP2M_id].m_dVMax-m_VelocityParameter2[VP2M_id].m_dVMin)*( 1.0 - exp( -((double)(errorOrientation)/m_VelocityParameter2[VP2M_id].m_K_dV)*((double)(errorOrientation)/m_VelocityParameter2[VP2M_id].m_K_dV)  ) ) );

	if( errorOrientation < 0 ) AngularVelocityDegree = -AngularVelocityDegree;

	double Vmax = ( m_VelocityParameter2[VP2M_id].m_VmaxMin
						+ (m_VelocityParameter2[VP2M_id].m_VmaxMax-m_VelocityParameter2[VP2M_id].m_VmaxMin)
							*( exp( -((double)(errorOrientation)/m_VelocityParameter2[VP2M_id].m_K_Vmax)*((double)(errorOrientation)/m_VelocityParameter2[VP2M_id].m_K_Vmax)  ) ) );
	
	double V = ( Vmax*( 1.0 - exp( -((double)(errorDistance)/m_VelocityParameter2[VP2M_id].m_K_Vc)*((double)(errorDistance)/m_VelocityParameter2[VP2M_id].m_K_Vc)  ) ) );

	AngularVelocityRadian = AngularVelocityDegree * M_PI / 180.0;	
	LinearVelocity = V;
}


void CRobot::ExecuteMission_FollowVector( int VP2M_id, CPointDouble vector, double dis )
{
//	CMission mission = m_MissionSet.GetCurrentMission();
	double pre_lv = m_LinearVelocity;
	double pre_av = m_AngularVelocity;
	bool bMoveBackward=false;

	
//	double dis = (m_pos-mission.pos).Distance();
//	double angle = ( mission.pos - m_pos ).AngleDegree();

	double e_theta = vector.AngleDegree() - m_orientation;

	AngleCorrectionDegree( e_theta );

	if( fabs(e_theta) > 90 )
	{
		bMoveBackward = true;

		e_theta+=180;
		AngleCorrectionDegree( e_theta );
	}


	double AngularVelocityDegree = ( m_VelocityParameter2[VP2M_id].m_dVMin
					+ (double)(m_VelocityParameter2[VP2M_id].m_dVMax-m_VelocityParameter2[VP2M_id].m_dVMin)*( 1.0 - exp( -((double)(e_theta)/m_VelocityParameter2[VP2M_id].m_K_dV)*((double)(e_theta)/m_VelocityParameter2[VP2M_id].m_K_dV)  ) ) );

	if( e_theta < 0 ) AngularVelocityDegree = -AngularVelocityDegree;

	double Vmax = ( m_VelocityParameter2[VP2M_id].m_VmaxMin
					   + (m_VelocityParameter2[VP2M_id].m_VmaxMax-m_VelocityParameter2[VP2M_id].m_VmaxMin)
						 *( exp( -((double)(e_theta)/m_VelocityParameter2[VP2M_id].m_K_Vmax)*((double)(e_theta)/m_VelocityParameter2[VP2M_id].m_K_Vmax)  ) ) );
	
	//double V = Vmax;
	double V = ( Vmax*( 1.0 - exp( -((double)(dis)/m_VelocityParameter2[VP2M_id].m_K_Vc)*((double)(dis)/m_VelocityParameter2[VP2M_id].m_K_Vc)  ) ) );
	
	m_AngularVelocity = AngularVelocityDegree * M_PI / 180.0;	
	m_LinearVelocity = V;

	if( bMoveBackward )
		m_LinearVelocity = -m_LinearVelocity;

	SmoothVelocity( VP2M_id );
}


void CRobot::RobotSimulationMove( double sec )
{
	double save_x= m_pos.x, save_y= m_pos.y, save_angle = m_orientation;

	if( ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_MiroSot )
	{
		double vl = VelocityLeft();
		double vr = VelocityRight();

		if (fabs(vl - vr) < 0.000000001)
		{
			m_pos.x = m_pos.x + vl * cos((m_orientation)*M_PI / 180.0) * sec;
			m_pos.y = m_pos.y + vl * sin((m_orientation)*M_PI / 180.0) * sec;
		}
		else
		if (vl + vr == 0)
		{
			double theta = (vr * sec / ((ROBOT_LENGTH - 0.009) * M_PI)) * 360;

			m_orientation += theta;

			AngleCorrectionDegree(m_orientation);
		}
		else
		if (vl > vr)
		{
			double r = (double)((ROBOT_LENGTH - 0.009) / 2 * (vr + vl)) / (double)(vl - vr);


			double cx = m_pos.x + r * cos((m_orientation - 90.0) * M_PI / 180.0);
			double cy = m_pos.y + r * sin((m_orientation - 90.0) * M_PI / 180.0);

			double theta = ((vl + vr) / 2 * sec / (2 * M_PI * r)) * 360;

			m_orientation -= theta;

			AngleCorrectionDegree(m_orientation);

			m_pos.x = cx + r * cos((m_orientation + 90.0) * M_PI / 180.0);
			m_pos.y = cy + r * sin((m_orientation + 90.0) * M_PI / 180.0);
		}
		else
			//if( vl < vr )
		{
			double r = (double)((ROBOT_LENGTH - 0.009) / 2 * (vr + vl)) / (double)(vr - vl);


			double cx = m_pos.x + r * cos((m_orientation + 90.0) * M_PI / 180.0);
			double cy = m_pos.y + r * sin((m_orientation + 90.0) * M_PI / 180.0);

			double theta = ((vl + vr) / 2 * sec / (2 * M_PI * r)) * 360;

			m_orientation += theta;

			AngleCorrectionDegree(m_orientation);

			m_pos.x = cx + r * cos((m_orientation - 90.0) * M_PI / 180.0);
			m_pos.y = cy + r * sin((m_orientation - 90.0) * M_PI / 180.0);
		}
	
	}

	if( ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_AndroSot )
	{
		// 안드로솟 시뮬레이션

		switch( Behavior() )
		{
		case ROBOT_BEHAVIOR_STOP :
			{
				m_pos; 
				m_orientation;

				Position();
				OrientationDegree();
				OrientationRadian();
			}
			break;
		case ROBOT_BEHAVIOR_MOVE_FORWARD50 :
			{
				double v = 0.07;

				CPointDouble new_pos;

				new_pos.x = Position().x + cos( OrientationRadian() ) * v * sec;
				new_pos.y = Position().y + sin( OrientationRadian() ) * v * sec;

				m_pos = new_pos;
			}
		break;
		case ROBOT_BEHAVIOR_MOVE_BACKWARD :
			{
				double v = 0.07;

				CPointDouble new_pos;

				new_pos.x = Position().x - cos( OrientationRadian() ) * v * sec;
				new_pos.y = Position().y - sin( OrientationRadian() ) * v * sec;

				m_pos = new_pos;
			}
		break;

			
		case ROBOT_BEHAVIOR_TURN_LEFT20 :
			{
				double w = 20;

				m_orientation = m_orientation + w * sec;
			}
			break;
		case ROBOT_BEHAVIOR_TURN_RIGHT20 :
			{
				double w = 20;

				m_orientation = m_orientation - w * sec;
			}
			break;
		case ROBOT_BEHAVIOR_TURN_LEFT10 :
			{
				double w = 5;

				m_orientation = m_orientation + w * sec;
			}
			break;
		case ROBOT_BEHAVIOR_TURN_RIGHT10 :
			{
				double w = 5;

				m_orientation = m_orientation - w * sec;
			}
			break;
		case ROBOT_BEHAVIOR_TURN_LEFT60 :
			{
				double w = 45;

				m_orientation = m_orientation + w * sec;
			}
			break;
		case ROBOT_BEHAVIOR_TURN_RIGHT60 :
			{
				double w = 45;

				m_orientation = m_orientation - w * sec;
			}
			break;
		case ROBOT_BEHAVIOR_MOVE_LEFT20 :
			{
				double v = 0.025;

				CPointDouble new_pos;

				new_pos.x = Position().x + cos( OrientationRadian() + M_PI/2 ) * v * sec;
				new_pos.y = Position().y + sin( OrientationRadian() + M_PI/2 ) * v * sec;

				m_pos = new_pos;
			}
		break;
		case ROBOT_BEHAVIOR_MOVE_LEFT70 :
			{
				double v = 0.06;

				CPointDouble new_pos;

				new_pos.x = Position().x + cos( OrientationRadian() + M_PI/2 ) * v * sec;
				new_pos.y = Position().y + sin( OrientationRadian() + M_PI/2 ) * v * sec;

				m_pos = new_pos;
			}
		break;

		case ROBOT_BEHAVIOR_GOALKEEP_RIGHT :
			{

				double v = 0.1;
				double v2 = 0.03;

				CPointDouble new_pos;

				new_pos.x = Position().x + cos( OrientationRadian() ) * v * sec;
				new_pos.y = Position().y - sin( OrientationRadian() ) * v2 * sec;
				m_pos = new_pos;

				double w = 90;
				m_orientation = m_orientation - w * sec;
			}
		break;
		case ROBOT_BEHAVIOR_GOALKEEP_LEFT :
			{
				double v = 0.1;
				double v2 = 0.03;

				CPointDouble new_pos;

				new_pos.x = Position().x + cos( OrientationRadian() ) * v * sec;
				new_pos.y = Position().y + sin( OrientationRadian() ) * v2 * sec;
				m_pos = new_pos;

				double w = 90;
				m_orientation = m_orientation + w * sec;
			
			}
		break;
		case ROBOT_BEHAVIOR_MOVE_RIGHT20 :
			{
				double v = 0.025;

				CPointDouble new_pos;

				new_pos.x = Position().x + cos( OrientationRadian() - M_PI/2 ) * v * sec;
				new_pos.y = Position().y + sin( OrientationRadian() - M_PI/2 ) * v * sec;

				m_pos = new_pos;
			}			
		break;
		case ROBOT_BEHAVIOR_MOVE_RIGHT70 :
		{
			double v = 0.06;

			CPointDouble new_pos;

			new_pos.x = Position().x + cos( OrientationRadian() - M_PI/2 ) * v * sec;
			new_pos.y = Position().y + sin( OrientationRadian() - M_PI/2 ) * v * sec;

			m_pos = new_pos;
		}			
		break;
		
		case ROBOT_BEHAVIOR_KICK_LEFTSIDE :
			{
			
			}
			break;
		case ROBOT_BEHAVIOR_KICK_RIGHTSIDE :
			{
			
			}			
			break;
		case ROBOT_BEHAVIOR_KICK_LEFTBACK :
			{

			}
			break;
		case ROBOT_BEHAVIOR_KICK_RIGHTBACK :
			{
				
				
			}			
			break;
	




		case ROBOT_BEHAVIOR_TEST :
			break;
		}
	}


	// 시뮬레이션 이동 후 화면 영역에서 벗어나는 것 방지, Prevents deviation from screen area after moving simulation
	if(		m_pos.x < -0.3 || m_pos.x > m_ground.Width() + 0.3
		||	m_pos.y <   0 || m_pos.y > m_ground.Height() )
	{
		m_pos.x = save_x;
		m_pos.y = save_y;
		m_orientation = save_angle; // Rotation is allowed
	}

	AngleCorrectionDegree( m_orientation );
}

// NEW: To Simulation Enemy Team Actions
void CRobot::RobotEnemySimulationMove(double sec)
{
	double save_x = m_enemypos.x, save_y = m_enemypos.y, save_angle = m_enemyori;

	if (ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_MiroSot)
	{
		// Rotating the orientation and invering the x and y position
		if (!enemy_set) {
			m_enemypos.x = (m_ground.Width() - m_enemypos.x);
			m_enemypos.y = (m_ground.Width() - m_enemypos.y);
			enemy_set = true;
		}

		// Swap velocities
		double vr = VelocityLeft();
		double vl = VelocityRight();

		if (fabs(vl - vr) < 0.000000001)
		{
			m_enemypos.x = (m_enemypos.x) - vl * cos((m_enemyori)*M_PI / 180.0) * sec;
			m_enemypos.y = (m_enemypos.y) - vl * sin((m_enemyori)*M_PI / 180.0) * sec;
		}
		else
		if (vl + vr == 0)
		{
			double theta = (vr * sec / ((ROBOT_LENGTH - 0.009) * M_PI)) * 360;

			m_enemyori += theta;

			AngleCorrectionDegree(m_enemyori);
		}
		else
		if (vl > vr)
		{
			double r = (double)((ROBOT_LENGTH - 0.009) / 2 * (vr + vl)) / (double)(vl - vr);


			double cx = (m_enemypos.x) - r * cos((m_enemyori + 90.0) * M_PI / 180.0);
			double cy = (m_enemypos.y) - r * sin((m_enemyori + 90.0) * M_PI / 180.0);

			double theta = ((vl + vr) / 2 * sec / (2 * M_PI * r)) * 360;

			m_enemyori += theta;

			AngleCorrectionDegree(m_enemyori);

			m_enemypos.x = cx - r * cos((m_enemyori - 90.0) * M_PI / 180.0);
			m_enemypos.y = cy - r * sin((m_enemyori - 90.0) * M_PI / 180.0);
		}
		else
		//if( vl < vr )
		{
			double r = (double)((ROBOT_LENGTH - 0.009) / 2 * (vr + vl)) / (double)(vr - vl);


			double cx = (m_enemypos.x) - r * cos((m_enemyori - 90.0) * M_PI / 180.0);
			double cy = (m_enemypos.y) - r * sin((m_enemyori - 90.0) * M_PI / 180.0);

			double theta = ((vl + vr) / 2 * sec / (2 * M_PI * r)) * 360;

			m_enemyori -= theta;

			AngleCorrectionDegree(m_enemyori);

			m_enemypos.x = cx - r * cos((m_enemyori + 90.0) * M_PI / 180.0);
			m_enemypos.y = cy - r * sin((m_enemyori + 90.0) * M_PI / 180.0);
		}

	}

	// 시뮬레이션 이동 후 화면 영역에서 벗어나는 것 방지, Prevents deviation from screen area after moving simulation
	if (m_enemypos.x < -0.3 || m_enemypos.x > m_ground.Width() + 0.3
		|| m_enemypos.y <   0 || m_enemypos.y > m_ground.Height())
	{
		m_enemypos.x = save_x;
		m_enemypos.y = save_y;
		m_enemyori = save_angle; // Rotation is allowed
	}

	AngleCorrectionDegree(m_orientation);
}

CMission CRobot::GetRecentMission()
{
	return m_MissionSet.GetRecentMission();
}

int CRobot::GetMissionN()
{
	return m_MissionSet.MissionN();
}

CString CRobot::Name()
{
	return m_strName;
}

void CRobot::SetName( CString name )
{
	m_strName = name;
}

void CRobot::SmoothVelocity( int VP2M_id )
{
	double LinearVelocityMaxAcc  = m_VelocityParameter2[VP2M_id].m_Ak1 * 1.0 / 30.0;
	double LinearVelocityMaxDec  = m_VelocityParameter2[VP2M_id].m_Ak2 * 1.0 / 30.0;
	double AngularVelocityMaxAcc = m_VelocityParameter2[VP2M_id].m_Ak3 * M_PI / 180.0 * 1.0 / 30.0;
	
	double pre_lv = m_pastLinearVelocity;
	double pre_av = m_pastAngularVelocity;

	if( pre_lv * m_LinearVelocity < 0 )
	{
		m_LinearVelocity = 0;
	}
	else
	{
		double d_lv = m_LinearVelocity - pre_lv;
		if( d_lv > 0  ) // 가속
		{
			d_lv = min( d_lv, LinearVelocityMaxAcc );

			//if( m_LinearVelocity > 0 )
				m_LinearVelocity = pre_lv + d_lv;
			//else
			//	m_LinearVelocity = pre_lv - d_lv;
		}
		else // 감속
		{
			d_lv = -min( -d_lv, LinearVelocityMaxDec );

			m_LinearVelocity = pre_lv + d_lv;
		}
	}

	if( pre_av * m_AngularVelocity < 0 )
	{
		m_AngularVelocity = 0;
	}
	else
	{
		double d_av = m_AngularVelocity - pre_av;
		if( d_av > 0  ) // 가속
		{
			d_av = min( d_av, AngularVelocityMaxAcc );

			//if( m_AngularVelocity > 0 )
				m_AngularVelocity = pre_av + d_av;
			//else
			//	m_AngularVelocity = pre_av - d_av;
		}
		else // 감속
		{
			d_av = -min( -d_av, AngularVelocityMaxAcc );

			//if( m_AngularVelocity > 0 )
				m_AngularVelocity = pre_av + d_av;
			//else
			//	m_AngularVelocity = pre_av - d_av;
		}
	}

}

double CRobot::CalcKickFitness( CPointDouble ball_pos, CPointDouble target_pos )
{
	double dis = (ball_pos-m_pos).Distance();

	double d_angle = (target_pos - ball_pos).AngleDegree() - (m_pos - ball_pos).AngleDegree();
	AngleCorrectionDegree( d_angle );

	double k1 = 0.8;
	double fitness = fabs(d_angle)/180.0 * k1 + max( 0, (1.0-dis)/1.0 ) * (1.0 - k1);

	return fitness;
}


void CRobot::SetBehavior(int behavior)
{
	m_behavior = behavior;
}

int CRobot::Behavior()
{
	return m_behavior;
}


BOOL CRobot::GenerateVelocity( CPathCubicSpline& path, double velocity_begin, double velocity_end, bool bMissionComplete )
{	
	/*
	가속 시 가속도     0 ~   6  0.1 //3.8 (3.7913741223671011)
	감속 시 가속도     6 ~   6  0.1 //2.9 (2.8435305917753255)
	구심가속도         0 ~  10  0.1 //7

	최대가속도 제한    0 ~   6  0.1 //6
	최대속도 제한      0 ~   4  0.1 //4

	경로 오차 gain     0 ~ 100  1   //20
	각속도 오차 P gain 0 ~ 100  1   //13
	각속도 오차 D gain 0 ~ 100  1   //0
	*/

	double max_accel       = m_VelocityParameter.m_Acceleration;
	double max_decel       = m_VelocityParameter.m_Deceleration;
	double max_centripetal = m_VelocityParameter.m_CentripetalAcceleration;
	double accel_limit     = m_VelocityParameter.m_MaxAccelerationLimit;
	double velocity_limit  = m_VelocityParameter.m_MaxVelocityLimit;
	double path_gain       = m_VelocityParameter.m_PathErrorGain;
	double omega_p         = m_VelocityParameter.m_AngularVelocityErrorPGain;
	double omega_d         = m_VelocityParameter.m_AngularVelocityErrorDGain;

	m_posCurrent;//현재 변위
	m_orientationCurrent;//현재 각변위
	m_posPast;//이전 변위
	m_orientationPast;//이전 각변위
	m_LinearVelocity;//이전 선속도
	m_AngularVelocity;//이전 각속도

	path.UpdateTracePoint( m_pos );//로봇의 위치를 입력하여 trace point를 갱신합니다.
	if( path.pointN == 0 
		|| ( !path.bLoop && path.tracePoint > path.pointN-5
		&& ( path.point[path.pointN-1] - m_pos ).Distance() < 0.0675/2. )) // Modify
	{
		if( bMissionComplete )
			m_MissionSet.Complete();

		m_staticPath.tracePoint = 0;
		m_LinearVelocity = 0;
		m_AngularVelocity = 0;

		return TRUE;
	}

	// Robot specifications
	#define H 0.023 // (m) center of mass height
	#define B (0.0675 / 2.) // (m) Distance between drive wheel and caster
	#define T (0.0675) // (m) wheel (distance between left and right wheels)
	#define G (10.0) // (m / s ^ 2) Gravity acceleration is about 9.8 or 10, so it is easy to manage. Fine tuning is impossible anyway
	#define U (0.7) // () Friction coefficient
	#define M (0.48) // (kg) Robot mass
	#define I ((0.25 * T) * (0.25 * T) * M) // (kgm ^ 2) Estimation of the robot rotational inertia (assuming that the quality points are located 50% left and right from the center of the robot)

	//AX(1.0) 4.7392176529588763
	#define AX_MAX max_accel // ((B * U * G) / (B + H * U)) * 0.8 // Maximum acceleration that can hold in the direction of the robot during acceleration
	#define AX_MIN max_decel // ((B * U * G) / (B + H * U)) * 0.6 // Maximum acceleration that can hold in the direction of the robot during deceleration
	#define AY_MAX max_centripetal // (U * G) // Maximum acceleration that the robot can hold in the lateral direction (ignore the toppling because the center of mass of the robot is low enough)
	#define V_MAX 4. // Value larger than the speed the robot can achieve (used to limit outliers in simulation)

	#define MAX_ACCELERATION accel_limit // (m_userParameter [5] / 10)
	#define MAX_VELOCITY velocity_limit // (m_userParameter [1])

	// PATH
	double c[PATH_POINT_MAX]; //curvature
	double dc[PATH_POINT_MAX]; // Curvature (curvature difference over distance)
	double d[PATH_POINT_MAX]; // Distance between points

	// VELOCITY PROFILE
	double v[PATH_POINT_MAX]; // Line speed
	//0, 1, 2, ..., N-2, N-1
//#define next_trace_point ( (path.tracePoint+1 >= path.pointN)?(  (path.bLoop)?(                              0):(path.pointN-1)   ):(path.tracePoint+1) )

#define next_trace_point(x) ( (path.tracePoint+x >= path.pointN)?(  (path.bLoop)?((path.tracePoint+x)%path.pointN):(path.pointN-1)   ):(path.tracePoint+x) )

	//path.pointN path의 point개수
	//0, 1, 2, ..., N-2, N-1
	if( path.pointN > 1 )//point개수가 2개 이상이어야 속도 계산 가능함
	{
////////////////////////////////////////////////////////////////////////////////
// STATIC PATH의 곡률, 변곡률, POINT간의 거리 구하기 ///////////////////////////
////////////////////////////////////////////////////////////////////////////////
		{
			int i;
			//PATH의 곡률과 point간의 거리를 구한다.
			// exception : pointN == 1
			for(i=0; i<path.pointN-1; i++){
				d[i] = (path.point[i+1] - path.point[i]).Distance();//(m)

				double angle = (path.direction[i+1].AngleDegree()-path.direction[i].AngleDegree())*M_PI/180.;//(rad)
				AngleCorrectionRadian( angle );

				// exception : distance == 0
				c[i] = angle/d[i];//(rad/meter)
			}
			if(path.bLoop){
				d[path.pointN-1] = (path.point[0] - path.point[path.pointN-1]).Distance();//(m)

				double angle = (path.direction[0].AngleDegree()-path.direction[path.pointN-1].AngleDegree())*M_PI/180.;//(rad)
				AngleCorrectionRadian( angle );

				// exception : distance == 0
				c[path.pointN-1] = angle/d[path.pointN-1];//(rad/meter)
			}
			else{
				d[path.pointN-1] = d[path.pointN-2];
				c[path.pointN-1] = c[path.pointN-2];
			}
			//PATH의 변곡률을 구한다.
			for(i=0; i<path.pointN-1; i++){
				dc[i] = c[i+1]-c[i];
			}
			dc[path.pointN-1] = dc[path.pointN-2];
		}
////////////////////////////////////////////////////////////////////////////////
// STATIC PATH의 속도 구하기 ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
		{
	////////////////////////////////////////////////////////////////////////////////
			//가속도를 고려하지 않고, 원심력을 한계치로 만드는 속도를 구한다.
	////////////////////////////////////////////////////////////////////////////////
			int i;
			//Velocity profile 계산
			//path.pointN path의 point개수
			//0, 1, 2, ..., N-2, N-1
			for(i=0; i<path.pointN-1; i++){
				v[i] = min(
					V_MAX,
					sqrt(
						(M * AX_MAX) /
						max(
							fabs(2*I/T * fabs(dc[i])) + fabs(AX_MAX/AY_MAX * M * fabs(c[i])),
							M*AX_MAX/(V_MAX*V_MAX)
						)
					)
				);//곡률과 변곡률을 고려한 최대 속도
			}
			v[0] = velocity_begin;//0.15;//처음 속도
			v[path.pointN-1] = velocity_end;//0.15;//마지막 속도

	////////////////////////////////////////////////////////////////////////////////
			//가속 시의 가속도를 고려하여 속도를 다시 만든다.
	////////////////////////////////////////////////////////////////////////////////
			//forward iteration
			//0, 1, 2, ..., N-2, N-1
			for(i=0; i<path.pointN-2; i++){
				double a1 =
					(
						AX_MAX *
							(
								max(0,
									M- fabs(M*fabs(c[i])*v[i]*v[i]/AY_MAX)
								)
							)
						- 2*I/T*dc[i]*v[i]*v[i]
					)
					/(  2*I/T*c[i] + M )
				;
				if ( (a1*c[i] < -dc[i] * v[i]* v[i]) || (a1<0) ) a1 = 0.;

				double a3 =
					(
						AX_MAX *
							(
								max(0,
									M- fabs(M*fabs(c[i])*v[i]*v[i]/AY_MAX)
								)
							)
						+ 2*I/T*dc[i]*v[i]*v[i]
					)
					/( -2*I/T*c[i] + M )
				;
				if ( (a3*c[i] > -dc[i] * v[i]* v[i]) || (a3<0) ) a3 = 0.;

				double accel = max(a1, a3);
				accel = min(accel, MAX_ACCELERATION);
				v[i+1] = min( v[i+1], sqrt( v[i]*v[i]+2*accel*d[i] ));
			}

	////////////////////////////////////////////////////////////////////////////////
			//감속 시의 가속도를 고려하여 속도를 다시 만든다.
	////////////////////////////////////////////////////////////////////////////////
			//reverse iteration
			//0, 1, 2, ..., N-2, N-1
			for(i=path.pointN-1; i>0; i--){
				double a2 =
					(
						AX_MIN *
							(
								max(0,
									M- fabs(M*fabs(c[i])*v[i]*v[i]/AY_MAX)
								)
							)
						- 2*I/T*dc[i]*v[i]*v[i]
					)
					/(  2*I/T*c[i] - M )
				;
				if ( (a2*c[i] < -dc[i] * v[i]* v[i]) || (a2>0) ) a2 = 0.;

				double a4 =
					(
						AX_MIN *
							(
								max(0,
									M- fabs(M*fabs(c[i])*v[i]*v[i]/AY_MAX)
								)
							)
						+ 2*I/T*dc[i]*v[i]*v[i]
					)
					/( -2*I/T*c[i] - M )
				;
				if ( (a4*c[i] > -dc[i] * v[i]* v[i]) || (a4>0) ) a4 = 0.;

				double accel = max(-a2, -a4);
				accel = min(accel, MAX_ACCELERATION);
				v[i-1] = min( v[i-1], sqrt( v[i]*v[i]+2*accel*d[i-1] ));
			}
		}
////////////////////////////////////////////////////////////////////////////////
// STATIC PATH 속도 계산 완료
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// DYNAMIC PATH를 만든다. (선변위 오차도 구함)
////////////////////////////////////////////////////////////////////////////////
		// 1. 가장 가까운 인터폴레이션 점 찾기 (search area에서)
		path.UpdateTracePoint( m_pos );//로봇의 위치를 입력하여 trace point를 갱신합니다.

		// 2. Path의 Direction Vector와 위치 오차 Vector를 더한다.
		CPointDouble direction = path.GetTracePointDirection();
		CPointDouble error = path.GetTracePointPosition() - m_pos;

		//path에서 떨어진 거리에 대한 보정값의 weight

		//1cm정도의 vision 떨림을 무시한다.
		double dead_zone = 0.001;
		if( error.Distance() < dead_zone ) error = CPointDouble(0,0);
		else
		{
			double d = error.Distance();
			error = error.Normalize()*(d-dead_zone);
		}

		double distance = 0.;
		int here = 0;
		CPointDouble dynamic_path = CPointDouble(0,0);
		do{
			dynamic_path += path.direction[next_trace_point(here)].Normalize() * (error.Distance()-distance);
			distance+=d[next_trace_point(here)];
			here++;		
		} while(distance < error.Distance());
		dynamic_path = dynamic_path.Normalize();
		dynamic_path += error*path_gain/max(2., (m_LinearVelocity*m_LinearVelocity));
		//고속에서 path가 smooth해지게 한다.
//		CPointDouble dynamic_path = direction.Normalize() + error*path_gain/max(2., (m_LinearVelocity*m_LinearVelocity));
		dynamic_path = dynamic_path.Normalize();
////////////////////////////////////////////////////////////////////////////////
// DYNAMIC PATH 생성 완료
////////////////////////////////////////////////////////////////////////////////
		double current_c;
		double current_v;

		current_v = 
			(
				( path.point[next_trace_point(1)] - m_pos).Distance() * v[path.tracePoint    ]
				+(path.point[path.tracePoint    ] - m_pos).Distance() * v[next_trace_point(1)]
			)
			/
			(
				( path.point[path.tracePoint    ] - m_pos).Distance()
				+(path.point[next_trace_point(1)] - m_pos).Distance()
			)
		;

		current_c = 
			(
				( path.point[next_trace_point(1)] - m_pos).Distance() * c[path.tracePoint    ]
				+(path.point[path.tracePoint    ] - m_pos).Distance() * c[next_trace_point(1)]
			)
			/
			(
				( path.point[path.tracePoint    ] - m_pos).Distance()
				+(path.point[next_trace_point(1)] - m_pos).Distance()
			)
		;

//		current_c = c[path.tracePoint  ];
//		current_v = v[path.tracePoint  ];


////////////////////////////////////////////////////////////////////////////////
// 로봇의 오차 계산(각변위 오차를 구함)
////////////////////////////////////////////////////////////////////////////////
		//각변위 오차 2개 저장
		angular_position_error9 = angular_position_error8;
		angular_position_error8 = angular_position_error7;
		angular_position_error7 = angular_position_error6;
		angular_position_error6 = angular_position_error5;
		angular_position_error5 = angular_position_error4;
		angular_position_error4 = angular_position_error3;
		angular_position_error3 = angular_position_error2;
		angular_position_error2 = angular_position_error1;
		angular_position_error1 = angular_position_error0;
		angular_position_error0 = (dynamic_path.AngleDegree() - m_orientation) / 180. * M_PI;
		AngleCorrectionRadian( angular_position_error0 );

		//각변위 오차의 차분값 구하기(오차의 변화 속도)(noise가 심해서 차분값을 사용하려면 더 많은 sample이 필요함)
//		double angular_error_velocity = angular_position_error0 - angular_position_error1;
		double angular_error_velocity = (angular_position_error0 - angular_position_error2)/2;  // 세형이형이 임시로 고치라고 해준거

////////////////////////////////////////////////////////////////////////////////
// 오차를 보상하기 위한 선속도와 각속도 구함
////////////////////////////////////////////////////////////////////////////////
		//각속도 계산
		double p_value = angular_position_error0 * omega_p;// * m_LinearVelocity;
		double d_value = angular_error_velocity  * omega_d;// * m_LinearVelocity;
		double target_w = p_value + d_value + current_c * m_LinearVelocity;

		//선속도 계산
//		double target_v = min( sqrt(v[path.tracePoint]*v[path.tracePoint]+2*AX_MAX*error.Distance()), MAX_VELOCITY);
		double target_v = current_v;
//		double target_v = min( sqrt(max(current_v*current_v-2*AX_MAX*error.Distance(), 0.15*0.15)), MAX_VELOCITY);
//		double target_v = min( sqrt(max(v[path.tracePoint]*v[path.tracePoint]-2*AX_MAX*error.Distance(), 0.15*0.15)), MAX_VELOCITY);
		target_v = min( target_v, MAX_VELOCITY);
//		if( fabs(target_w * target_v) > AY_MAX) target_v = fabs(AY_MAX / target_w);

		double available_force_accel = max( AX_MAX/10. , AX_MAX * (M - fabs(M*m_AngularVelocity*m_LinearVelocity)/AY_MAX ) * 1.5 );
		double a_accel     = 1./M * available_force_accel;
		double available_force_decel = max( AX_MIN/10. , AX_MIN * (M - fabs(M*m_AngularVelocity*m_LinearVelocity)/AY_MAX ) * 1.5 );
		double a_decel     = 1./M * available_force_decel;
//		double a = fabs((v[path.tracePoint+1 ]*v[path.tracePoint+1 ]-v[path.tracePoint  ]*v[path.tracePoint  ]) / (2*d[path.tracePoint  ]));
		if     (m_LinearVelocity  < target_v){
			m_LinearVelocity = min( m_LinearVelocity  + a_accel /30. , target_v);//30 frame/second
		}
		else if(m_LinearVelocity  > target_v){
			m_LinearVelocity = max( m_LinearVelocity  - a_decel /30. , target_v);
		}

		//각속도 다시 계산
		m_AngularVelocity = p_value + d_value + current_c * m_LinearVelocity;

		//원심력 제한을 위해서 각속도 출력을 제한합니다.
		if     ( m_AngularVelocity * m_LinearVelocity >  AY_MAX * 1.5 ) m_AngularVelocity =  AY_MAX * 1.5 /m_LinearVelocity;
		else if( m_AngularVelocity * m_LinearVelocity < -AY_MAX * 1.5 ) m_AngularVelocity = -AY_MAX * 1.5 /m_LinearVelocity;
////////////////////////////////////////////////////////////////////////////////
// DYNAMIC PATH의 속도 생성 완료
////////////////////////////////////////////////////////////////////////////////

	/*
		if( m_id == 1 )
		{
			FILE *fp;

			fp = fopen("Profile.txt", "wt");

			for(int i=0; i<path.pointN-1; i++)
			{
				fprintf( fp, "%lf\t%lf\n", curvature[i], distance[i] );
			}

			fclose(fp);
		}
	*/

	}
	else
	{
		m_MissionSet.Complete();
		m_staticPath.tracePoint = 0;
		m_LinearVelocity = 0;
		m_AngularVelocity = 0;

		return TRUE;
	}

	return FALSE;
}

void CRobot::UpdatePath()
{
	/*
	if( !m_MissionSet.HasMission() )
	{
		Stop();
		return;
	}

	CMission mission = m_MissionSet.GetCurrentMission();

	switch( mission.type )
	{
	case CMission::SPLINE_PATH :
		{
			mission.posPath[0] = m_pos;
			m_staticPath.PathFollow( mission.posPath );
			m_staticPath.SafeGroundPath( m_ground.Width(), m_ground.Height(), m_StrategyParameter.m_AvoidBoundSize );
		}
		break;

	case CMission::TEST_PATH8 :
		{
			m_staticPath.InfiniteLoop( mission.parameter[0],
										 mission.parameter[1],
										 mission.parameter[2],
										 mission.parameter[3]);

			m_staticPath.SafeGroundPath( m_ground.Width(), m_ground.Height(), m_StrategyParameter.m_AvoidBoundSize );
		}
		break;

	}
	*/
}