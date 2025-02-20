#include "StdAfx.h"
#include "GameRun.h"

#define _USE_MATH_DEFINES
#include <math.h>

CGameRun::CGameRun(void)
{
	InitializeCriticalSection(&m_critGame);

	int p=0;
	m_strSituationName[p++] = _T("Default - Kickoff (Off)");
	m_strSituationName[p++] = _T("Default - Kickoff (Def)");
	m_strSituationName[p++] = _T("Default - Goal kick (Off)");
	m_strSituationName[p++] = _T("Default - Goal kick (Def)");
	m_strSituationName[p++] = _T("Default - Penalty kick (Off)");
	m_strSituationName[p++] = _T("Default - Penalty kick (Def)");
	m_strSituationName[p++] = _T("Default - Free ball (Home-Left)");
	m_strSituationName[p++] = _T("Default - Free ball (Opp-Left)");
	m_strSituationName[p++] = _T("Default - Free ball (Home-Right)");
	m_strSituationName[p++] = _T("Default - Free ball (Opp-Right)");
	m_strSituationName[p++] = _T("Default - Combo box");
}


CGameRun::~CGameRun(void)
{
	DeleteCriticalSection(&m_critGame);
}

bool CGameRun::Intersection(CPointDouble P1, CPointDouble P2, CPointDouble Q1, CPointDouble Q2, CPointDouble &Intersection)
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
	
	if( t < 0 || t > 1 || s < 0 || s > 1 )
		return false;
	
	Intersection = P1 + P2 * t;
	
	return true;
}

CPointDouble CGameRun::InsideGround(CPointDouble A, CPointDouble B, CPointDouble W1, CPointDouble W2 )
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

void CGameRun::RunGUI()
{
	static int situationID = -1;
	CStrategyGUI::Situation situation;

	bool bBallOwnerHome = false;
	double min_dis_home = 100.0;
	double min_dis_opp = 100.0;

	{

		for( int i=0 ; i<m_robotN ; i++ )
		{
			if( ( m_Robot[i].Position() - m_Ball.Position() ).Distance() < min_dis_home )
			{
				min_dis_home = ( m_Robot[i].Position() - m_Ball.Position() ).Distance();
			}
		}
		for( int i=0 ; i<m_opponentN ; i++ )
		{
			if( ( m_Opponent[i].Position() - m_Ball.Position() ).Distance() < min_dis_opp )
			{
				min_dis_opp = ( m_Opponent[i].Position() - m_Ball.Position() ).Distance();
			}
		}

		if( min_dis_home < min_dis_opp )
		{
			bBallOwnerHome = true;
		}
	}
	
	bool bFirstSituation = false;

	int situationN = m_strategyGUI.GetSituationN();

	for( int i=0 ; i < situationN ; i++ )
	{
		situation = m_strategyGUI.GetSituation(i);

		if( situation.priority == StrategyGUI_SituationPriority::First )
		if( situation.time.begin_sec <= m_timeGame
		 && situation.time.end_sec > m_timeGame )
		{
			if( situation.condition.area.type == CStrategyGUI::CONDITION_AREA_RECTANGLE )
			{
				if( situation.condition.area.rect.left   <= m_Ball.m_pos.x
				 && situation.condition.area.rect.right  >= m_Ball.m_pos.x
				 && situation.condition.area.rect.top    <= m_Ball.m_pos.y
				 && situation.condition.area.rect.bottom >= m_Ball.m_pos.y )
				{
					if( situation.condition.ball.bHome
					 && min_dis_home < min_dis_opp
					 && min_dis_home <= situation.condition.ball.owner_distance )
					{
						situationID = i;
						bFirstSituation = true;
						break;
					}
					else
					if( situation.condition.ball.bOpp
					 && min_dis_opp < min_dis_home
					 && min_dis_opp <= situation.condition.ball.owner_distance )
					{
						situationID = i;
						bFirstSituation = true;
						break;
					}
					else
					if( situation.condition.ball.bFree
					 && min_dis_home > situation.condition.ball.owner_distance
					 && min_dis_opp  > situation.condition.ball.owner_distance )
					{
						situationID = i;
						bFirstSituation = true;
						break;
					}
				}
			}
			else
			if( situation.condition.area.type == CStrategyGUI::CONDITION_AREA_ELLIPSE )
			{
			}
		}
	}
	


	bool bHoldSituation = false;

	if( !bFirstSituation )
	if( situationID >= 0 && situationID < situationN )
	{
		situation = m_strategyGUI.GetSituation( situationID );

		if( situation.time.begin_sec <= m_timeGame
		 && situation.time.end_sec > m_timeGame
		 && situation.condition.area.type == CStrategyGUI::CONDITION_AREA_RECTANGLE )
		{
			if( situation.condition.area.rect.left   <= m_Ball.m_pos.x
			 && situation.condition.area.rect.right  >= m_Ball.m_pos.x
			 && situation.condition.area.rect.top    <= m_Ball.m_pos.y
			 && situation.condition.area.rect.bottom >= m_Ball.m_pos.y )
			{
				if( situation.condition.ball.bHome
				 && min_dis_home < min_dis_opp
				 && min_dis_home <= situation.condition.ball.owner_distance )
				{
					situationID = situationID;
					bHoldSituation = true;
				}
				else
				if( situation.condition.ball.bOpp
				 && min_dis_opp < min_dis_home
				 && min_dis_opp <= situation.condition.ball.owner_distance )
				{
					situationID = situationID;
					bHoldSituation = true;
				}
				else
				if( situation.condition.ball.bFree
				 && min_dis_home > situation.condition.ball.owner_distance
				 && min_dis_opp  > situation.condition.ball.owner_distance )
				{
					situationID = situationID;
					bHoldSituation = true;
				}
			}
		}
	}

	if(	!bHoldSituation && !bFirstSituation )
	for( int i=0 ; i < situationN ; i++ )
	{
		situation = m_strategyGUI.GetSituation(i);

		if( situation.time.begin_sec <= m_timeGame
		 && situation.time.end_sec > m_timeGame )
		{
			if( situation.condition.area.type == CStrategyGUI::CONDITION_AREA_RECTANGLE )
			{
				if( situation.condition.area.rect.left   <= m_Ball.m_pos.x
				 && situation.condition.area.rect.right  >= m_Ball.m_pos.x
				 && situation.condition.area.rect.top    <= m_Ball.m_pos.y
				 && situation.condition.area.rect.bottom >= m_Ball.m_pos.y )
				{
					if( situation.condition.ball.bHome
					 && min_dis_home < min_dis_opp
					 && min_dis_home <= situation.condition.ball.owner_distance )
					{
						situationID = i;
						break;
					}
					else
					if( situation.condition.ball.bOpp
					 && min_dis_opp < min_dis_home
					 && min_dis_opp <= situation.condition.ball.owner_distance )
					{
						situationID = i;
						break;
					}
					else
					if( situation.condition.ball.bFree
					 && min_dis_home > situation.condition.ball.owner_distance
					 && min_dis_opp  > situation.condition.ball.owner_distance )
					{
						situationID = i;
						break;
					}
				}
			}
			else
			if( situation.condition.area.type == CStrategyGUI::CONDITION_AREA_ELLIPSE )
			{
			}
		}
	}

	EnterCriticalSection(&m_critGame);
	m_situationCurrent = situation;
	LeaveCriticalSection(&m_critGame);

	if( situationID != -1 )
	{
		int RobotRoleAssign[CStrategyGUI::MAX_SITUATION_ROBOT_N];
		int tmpRoleAssign[CStrategyGUI::MAX_SITUATION_ROBOT_N];

		for( int i=0 ; i<CStrategyGUI::MAX_SITUATION_ROBOT_N ; i++ )
		{
			RobotRoleAssign[i] = -1;
			tmpRoleAssign[i] = -1;
		}

		for( int role_assign_i=0 ; role_assign_i<CStrategyGUI::MAX_SITUATION_ROBOT_N ; role_assign_i++ )
		{
			if( situation.role_assign.role[role_assign_i].assign.option_hold == StrategyGUI_RoleAssignOptionHold::Hold )
			{
				for( int robot_i=0 ; robot_i<m_robotN ; robot_i++ )
				{
					if( m_Robot[robot_i].Role() == situation.role_assign.role[role_assign_i].name )
					{
						tmpRoleAssign[role_assign_i] = robot_i;
						RobotRoleAssign[robot_i] = role_assign_i;
						
						break;
					}
				}
			}
		}


		for( int role_assign_i=0 ; role_assign_i<CStrategyGUI::MAX_SITUATION_ROBOT_N ; role_assign_i++ )
		{
			if( tmpRoleAssign[role_assign_i] != -1 )
				continue;

			if( situation.role_assign.role[role_assign_i].assign.method == StrategyGUI_RoleAssignMethod::CloseToBall     )
			{
				int select_id = -1;

				double min_dis = 100.0;
				for( int robot_i=0 ; robot_i<m_robotN ; robot_i++ )
				{
					if( m_Robot[robot_i].IsExist() )
					if( RobotRoleAssign[ robot_i ] == -1 )
					{
						double dis = ( m_Robot[robot_i].m_pos - m_Ball.m_pos ).Distance();
						if( dis < min_dis )
						{
							select_id = robot_i;
							min_dis = dis;
						}
					}
				}

				if( select_id >= 0 )
				{
					tmpRoleAssign[role_assign_i] = select_id;
					RobotRoleAssign[select_id] = role_assign_i;
				}
			}
			if( situation.role_assign.role[role_assign_i].assign.method == StrategyGUI_RoleAssignMethod::GoodToKick     )
			{
				int select_id = -1;

				double max_fitness = 0.0;
				for( int robot_i=0 ; robot_i<m_robotN ; robot_i++ )
				{
					if( m_Robot[robot_i].IsExist() )
					if( RobotRoleAssign[ robot_i ] == -1 )
					{
						double fitness = m_Robot[robot_i].CalcKickFitness( m_Ball.Position(), situation.role_assign.role[role_assign_i].assign.pos );
						if( fitness > max_fitness )
						{
							select_id = robot_i;
							max_fitness = fitness;
						}
					}
				}

				if( select_id >= 0 )
				{
					tmpRoleAssign[role_assign_i] = select_id;
					RobotRoleAssign[select_id] = role_assign_i;
				}				
			}
			if( situation.role_assign.role[role_assign_i].assign.method == StrategyGUI_RoleAssignMethod::CloseToLocation )
			{
				CPointDouble pos = situation.role_assign.role[role_assign_i].assign.pos;

				int select_id = -1;

				double min_dis = 100.0;
				for( int robot_i=0 ; robot_i<m_robotN ; robot_i++ )
				{
					if( m_Robot[robot_i].IsExist() )
					if( RobotRoleAssign[ robot_i ] == -1 )
					{
						double dis = ( m_Robot[robot_i].m_pos - pos ).Distance();
						if( dis < min_dis )
						{
							select_id = robot_i;
							min_dis = dis;
						}
					}
				}

				if( select_id >= 0 )
				{
					tmpRoleAssign[role_assign_i] = select_id;
					RobotRoleAssign[select_id] = role_assign_i;
				}
			}
			if( situation.role_assign.role[role_assign_i].assign.method == StrategyGUI_RoleAssignMethod::Rest              )
			{
				int select_id = -1;

				double min_dis = 100.0;
				for( int robot_i=0 ; robot_i<m_robotN ; robot_i++ )
				{
					if( m_Robot[robot_i].IsExist() )
					if( RobotRoleAssign[ robot_i ] == -1 )
					{
						select_id = robot_i;
						break;
					}
				}

				if( select_id >= 0 )
				{
					tmpRoleAssign[role_assign_i] = select_id;
					RobotRoleAssign[select_id] = role_assign_i;
				}
			}
		}

		for( int role_assign_i=0 ; role_assign_i<CStrategyGUI::MAX_SITUATION_ROBOT_N ; role_assign_i++ )
		{
			if(  tmpRoleAssign[role_assign_i] == -1 )
			{
				int select_id = -1;

				double min_dis = 100.0;
				for( int robot_i=0 ; robot_i<m_robotN ; robot_i++ )
				{
					if( m_Robot[robot_i].IsExist() )
					if( RobotRoleAssign[ robot_i ] == -1 )
					{
						select_id = robot_i;
						break;
					}
				}

				if( select_id >= 0 )
				{
					tmpRoleAssign[role_assign_i] = select_id;
					RobotRoleAssign[select_id] = role_assign_i;
				}
			}
		}

		for( int robot_i=0 ; robot_i<CStrategyGUI::MAX_SITUATION_ROBOT_N ; robot_i++ )
		{
			if( m_Robot[robot_i].IsExist() )
			{
				int role_assign_i = RobotRoleAssign[robot_i];

				int role_i = m_strategyGUI.FindRole( situation.role_assign.role[role_assign_i].name );
				if( role_i >= 0 )
				{
					CStrategyGUI::Role role = m_strategyGUI.GetRole( role_i );

					m_Robot[robot_i].SetRole( role );
				}
			}
		}
	}

	UpdateMission_GUI();
	ExecuteMission();
}

// 안드로솟 전략
void CGameRun::Run( bool bRoleChange )
{
	if( ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_AndroSot )
	{
		m_Robot[0].SetBehavior( ROBOT_BEHAVIOR_STOP );
		m_Robot[1].SetBehavior( ROBOT_BEHAVIOR_STOP );
		m_Robot[2].SetBehavior( ROBOT_BEHAVIOR_STOP );
	}

	/*
		//InitUpdate()
	
		UnderstandSituation();

		if( bRoleChange )
			UpdateRole();

		UpdateMission();
	
		ExecuteMission();
	*/	


	/* // example ////////////////////////////////////////////////////////////////////////////////////////////////////////

	CPointDouble pos_robot_A = m_Robot[0].Position();
	double orientation = m_Robot[0].OrientationDegree();
	pos_robot_A.x;
	pos_robot_A.y;

	double v_left = 0.05;
	double v_right = 0.00;
	m_Robot[0].SetVelocity( VelocityType::LEFT_RIGHT,            v_left, v_right );

	m_Robot[1].SetVelocity( VelocityType::LEFT_RIGHT,            0, 0 );
	m_Robot[2].SetVelocity( VelocityType::LEFT_RIGHT,            0, 0 );


	CPointDouble pos_robot_A = m_Robot[0].Position();
	pos_robot_A.x;
	pos_robot_A.y;

	CPointDouble pos_opp_A = m_Opponent[0].Position();
	pos_opp_A.x;
	pos_opp_A.y;

	CTest algorithm; //실험용 알고리즘 구동 클래스

	for( int i=0 ; i<3 ; i++ )
	{
		algorithm.SetRobotHome( 0, m_Robot[i].Position().x, m_Robot[i].Position().y, m_Robot[i].OrientationRadian() )
		algorithm.SetRobotOpp(  0, m_Opponent[i].Position().x, m_Opponent[i].Position().y )
	}

	algorithm.Execute();

	for( int i=0 ; i<3 ; i++ )
	{
		double v_linear;
		double v_angular_radian;
		algorithm.GetVelocityHome( i, &v_liear, &v_angular_radian );
		m_Robot[i].SetVelocity( VelocityType::LINEAR_ANGULAR_RADIAN, v_linear, v_angular_radian );
	}

	// 속도 출력 방법1
	{
		double v_linear;
		double v_angular_radian;
		m_Robot[0].SetVelocity( VelocityType::LINEAR_ANGULAR_RADIAN, v_linear, v_angular_radian );
	}

	// 속도 출력 방법2
	{
		double v_linear;
		double v_angular_degree;
		m_Robot[0].SetVelocity( VelocityType::LINEAR_ANGULAR_DEGREE, v_linear, v_angular_degree );
	}

	// 속도 출력 방법3
	{
		double v_left;
		double v_right;
		m_Robot[0].SetVelocity( VelocityType::LEFT_RIGHT,            v_left, v_right );
	}
	*/
}

void CGameRun::UnderstandSituation()
{
	m_situation.Update( m_Ball.Position() );
}

void CGameRun::UpdateRole()
{	
	if( m_ground.Type() == CGround::_3vs3 )
		UpdateRole_3vs3();

	if( m_ground.Type() == CGround::_5vs5 )
		UpdateRole_5vs5();
}

void CGameRun::UpdateRole_3vs3()
{
}

void CGameRun::UpdateRole_5vs5()
{
}

double CGameRun::ccw(CPointDouble p1, CPointDouble p2, CPointDouble p3)
{
	//	p1.x p2.x p3.x
	//	p1.y p2.y p3.y

	return p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - p1.x*p3.y - p2.x*p1.y  - p3.x*p2.y;
}


void CGameRun::UpdateMission()
{
	for( int id=0 ; id<m_robotN ; id++ )
	{
//		m_Robot[id].UpdateMission();
	}
}

void CGameRun::UpdateMission_GUI( bool bSetplay_init )
{
	for( int id=0 ; id<m_robotN ; id++ )
	{
		if( m_Robot[id].IsExist() )
			m_Robot[id].UpdateMission_GUI( bSetplay_init );
	}
}


void CGameRun::ExecuteMission()
{
	for( int id=0 ; id<m_robotN ; id++ )
	{
		if( m_Robot[id].IsExist() )
			m_Robot[id].ExecuteMission();
	}
}

void CGameRun::SetRobotName( CString name[] )
{
	for( int i=0 ; i<m_robotN ; i++ )
	{
		m_Robot[i].SetName( name[i] );
	}
}

void CGameRun::SetRobotRole( CString nameRole[] )
{
	for( int i=0 ; i<m_robotN ; i++ )
	{
		int role_id = m_strategyGUI.FindRole( nameRole[i] );
		if( role_id >= 0 )
		{
			CStrategyGUI::Role role = m_strategyGUI.GetRole( role_id );
			m_Robot[i].SetRole( role, true );
		}
	}
}

void CGameRun::SetGroundType(int type, CRect rect, double zoom )
{
	m_ground.SetGround( type, rect, zoom );
	m_ground.SetCenter( CPoint(320,240) );

	m_Ball.SetGround( m_ground );
	for( int id=0 ; id<m_robotN ; id++ )
	{
		m_Robot[id].SetGround( m_ground );
//		m_Robot[id].SetRole( Role::NOTHING );
	}

	for( int id=0 ; id<m_opponentN ; id++ )
	{
		m_Opponent[id].SetGround( m_ground );
	}
}


//////////////////////////////////////////////////////////////////////////
// File
//////////////////////////////////////////////////////////////////////////

bool CGameRun::LoadAutoPosition(CString situation)
{
	for( int robot_i=0 ; robot_i<m_robotN ; robot_i++ )
	{
		m_Robot[robot_i].MissionReset();
	}

	CAutopositionData::Team auto_pos;
	auto_pos= m_AutoPositionData.GetAutoPositionData( situation );

	if( auto_pos.bValid == false )
		return false;

	for( int i=0 ; i<(int)auto_pos.robot.size() ; i++ )
	{
		for( int robot_i=0 ; robot_i<m_robotN ; robot_i++ )
		{
			if( auto_pos.robot[i].name == m_Robot[robot_i].Name() )
			{
				m_Robot[robot_i].MissionReset();

				CMission mission;

				mission.bTemporary = true;

				mission.text = _T("Move autoposition");
				mission.type = MissionType::MoveTo;
				mission.behavior.controlType = StrategyGUI_BehaviorControlType::Once;
				mission.behavior.options.move_to.destination.bBall = false;
				mission.behavior.options.move_to.destination.pos = CPointDouble( auto_pos.robot[i].x, auto_pos.robot[i].y );
				mission.behavior.options.move_to.destination.error = 0.01;


				mission.posDestination = CPointDouble( auto_pos.robot[i].x, auto_pos.robot[i].y );
				m_Robot[robot_i].MissionAdd( mission );
				m_Robot[robot_i].m_MissionSet.UpdateRecentMission( mission, 0 );



				mission.bTemporary = true;

				mission.text = _T("rotate autoposition");
				mission.type = MissionType::OrientationTo;
				mission.behavior.controlType = StrategyGUI_BehaviorControlType::Once;
				mission.behavior.options.orientation.orientation.bPosDirection = false;
				mission.behavior.options.orientation.orientation.direction = auto_pos.robot[i].orientation;

				m_Robot[robot_i].MissionAdd( mission );
			}
		}
	}
	
	return true;
}

bool CGameRun::UpdateAutoPosition(CString situation)
{
	CAutopositionData::Team auto_pos_data;

	auto_pos_data.bValid = true;
	auto_pos_data.situation = situation;

	for( int robot_i=0 ; robot_i<m_robotN ; robot_i++ )
	{
		if( m_Robot[robot_i].Name() != _T("") )
		{
			CAutopositionData::Robot robot;
			robot.name  = m_Robot[robot_i].Name();
			robot.x     = m_Robot[robot_i].m_pos.x;
			robot.y     = m_Robot[robot_i].m_pos.y;
			robot.orientation = m_Robot[robot_i].OrientationDegree();

			auto_pos_data.robot.push_back( robot );
		}
	}

	return m_AutoPositionData.UpdateAutoPositionData( auto_pos_data );
}