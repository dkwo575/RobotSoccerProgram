#include "stdafx.h"
#include "StrategyGUI.h"


CStrategyGUI::CStrategyGUI(void)
{
	InitializeCriticalSection(&m_critStrategyGUI);

	m_vecRoleAssignMethod.push_back( StrategyGUI_RoleAssignMethod::CloseToLocation );
	m_vecRoleAssignMethod.push_back( StrategyGUI_RoleAssignMethod::CloseToBall     );
	m_vecRoleAssignMethod.push_back( StrategyGUI_RoleAssignMethod::GoodToKick      );
	m_vecRoleAssignMethod.push_back( StrategyGUI_RoleAssignMethod::Rest            );

	m_vecRoleAssignOption_Hold.push_back( StrategyGUI_RoleAssignOptionHold::Refresh );
	m_vecRoleAssignOption_Hold.push_back( StrategyGUI_RoleAssignOptionHold::Hold    );

	m_vecSituationPriority.push_back( StrategyGUI_SituationPriority::Default );
	m_vecSituationPriority.push_back( StrategyGUI_SituationPriority::First   );

	m_vecBehaviorControlType.push_back( StrategyGUI_BehaviorControlType::Once );
	m_vecBehaviorControlType.push_back( StrategyGUI_BehaviorControlType::Keep );

	if( ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_MiroSot )
	{
		if( ROBOT_SOCCER_PROGRAM_COMMUNICATION_PROTOCOL == ROBOT_SOCCER_PROGRAM_COMMUNICATION_PROTOCOL_KMC )
		{
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Goalkeep       );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Defense_Wall   );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::MoveTo         );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Kick_A         );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Kick_B         );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Velocity       );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::OrientationTo  );
			// Adding new action to list
			// m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Corner_Kick    );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Wait           );
		}

		if( ROBOT_SOCCER_PROGRAM_COMMUNICATION_PROTOCOL == ROBOT_SOCCER_PROGRAM_COMMUNICATION_PROTOCOL_RIT )
		{
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Goalkeep       );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Defense_Wall   );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::MoveTo         );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Kick_A         );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Kick_B         );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Velocity       );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::OrientationTo  );
			m_vecBehaviorType.push_back( StrategyGUI_BehaviorType::Wait           );
		}
	}

	if( ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_AndroSot )
	{
	}
}


CStrategyGUI::~CStrategyGUI(void)
{
	DeleteCriticalSection(&m_critStrategyGUI);
}

CString CStrategyGUI::TypeToName( CString type )
{
	if( type == StrategyGUI_BehaviorType::Velocity      ) return _T("Velocity");
	if( type == StrategyGUI_BehaviorType::Wait          ) return _T("--- Wait ---");
	if( type == StrategyGUI_BehaviorType::MoveTo        ) return _T("Move");
	if( type == StrategyGUI_BehaviorType::OrientationTo ) return _T("Orientation To");
	if( type == StrategyGUI_BehaviorType::Goalkeep      ) return _T("GoalKeeper");
	if( type == StrategyGUI_BehaviorType::Defense_Wall  ) return _T("Defence Pos");
	if( type == StrategyGUI_BehaviorType::Kick_A        ) return _T("Kick-A");
	if( type == StrategyGUI_BehaviorType::Kick_B        ) return _T("Kick-B");
	if( type == StrategyGUI_BehaviorType::Kick_C        ) return _T("Kick-C");
	// Text in drop down for new action
	if( type == StrategyGUI_BehaviorType::Corner_Kick	) return _T("Corner Kick");

	if( type == StrategyGUI_BehaviorControlType::Once      ) return _T("↓");
	if( type == StrategyGUI_BehaviorControlType::Keep      ) return _T("∞");
	if( type == StrategyGUI_BehaviorControlType::Temporary ) return _T("");

	if( type == StrategyGUI_SituationPriority::Default ) return _T("Default");
	if( type == StrategyGUI_SituationPriority::First   ) return _T("First");

	if( type == StrategyGUI_RoleAssignOptionHold::Refresh ) return _T("Refresh");
	if( type == StrategyGUI_RoleAssignOptionHold::Hold    ) return _T("hold");

	if( type == StrategyGUI_RoleAssignMethod::CloseToLocation ) return _T("closest robot to location");
	if( type == StrategyGUI_RoleAssignMethod::CloseToBall     ) return _T("closest robot to ball"  );
	if( type == StrategyGUI_RoleAssignMethod::GoodToKick      ) return _T("chance to kick");
	if( type == StrategyGUI_RoleAssignMethod::Rest            ) return _T("Rest"   );

	return _T("error");
}

void CStrategyGUI::SetFileName( CString filename )
{
	m_filename = filename;
}


bool CStrategyGUI::VerifyStrategy()
{
	EnterCriticalSection(&m_critStrategyGUI);

	for( int i=0 ; i<3 ; i++ )
	{
		m_vecVerifySituationRect[i].clear();

		CRectDouble rect( 0, 0, 1.5, 1.3 ); // _3vs3

		if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_5vs5 )
			rect = CRectDouble( 0, 0, 2.2, 1.8 );

		if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_AndroSot )
			rect = CRectDouble( 0, 0, 2.2, 1.8 );

		if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_3vs3 )
			rect = CRectDouble( 0, 0, 1.5, 1.3 );

		m_vecVerifySituationRect[i].push_back( rect );

		for( int j=0 ; j<GetSituationN() ; j++ )
		{
			if( i==0 && m_vecSituation[j].condition.ball.bHome == false )
				continue;
			if( i==1 && m_vecSituation[j].condition.ball.bOpp  == false )
				continue;
			if( i==2 && m_vecSituation[j].condition.ball.bFree == false )
				continue;

			bool bUpdate = false;
			
			do
			{
				bUpdate = false;

				for( auto it = m_vecVerifySituationRect[i].begin() ; it != m_vecVerifySituationRect[i].end() ; it++ )
				{
					// 03
					// 12
					CRectDouble rect_p = m_vecSituation[j].condition.area.rect;
					CRectDouble rect_q = *it;

					rect_p.left   = max( rect_p.left  , rect_q.left   );
					rect_p.right  = min( rect_p.right , rect_q.right  );
					rect_p.top    = max( rect_p.top   , rect_q.top    );
					rect_p.bottom = min( rect_p.bottom, rect_q.bottom );

					CPointDouble p[4];
					p[0].x = rect_p.left;
					p[0].y = rect_p.top;
					p[1].x = rect_p.left;
					p[1].y = rect_p.bottom;
					p[2].x = rect_p.right;
					p[2].y = rect_p.bottom;
					p[3].x = rect_p.right;
					p[3].y = rect_p.top;

					CPointDouble q[4];
					q[0].x = rect_q.left;
					q[0].y = rect_q.top;
					q[1].x = rect_q.left;
					q[1].y = rect_q.bottom;
					q[2].x = rect_q.right;
					q[2].y = rect_q.bottom;
					q[3].x = rect_q.right;
					q[3].y = rect_q.top;

					if( rect_p.right <= rect_q.left )
						continue;

					if( rect_q.right <= rect_p.left )
						continue;

					if( rect_p.bottom <= rect_q.top )
						continue;

					if( rect_q.bottom <= rect_p.top )
						continue;

	/*
					int countInside_p = 0;
					for( int pi=0 ; pi<4 ; pi++ )
					{
						if( rect_q.Inside( p[pi] ) )
						{
							countInside_p++;
						}
					}
	*/
					int countInside_q = 0;
					for( int qi=0 ; qi<4 ; qi++ )
					{
						if( rect_p.Inside( q[qi] ) )
						{
							countInside_q++;
						}
					}

					if( countInside_q == 4 )
					{
						m_vecVerifySituationRect[i].erase( it );
						bUpdate = true;
						break;
					}
					else
					{
						bool bFound = false;
						CRectDouble rect[2];

						for( int pi=0 ; pi<4 ; pi++ )
						{
							rect[0] = rect[1] = rect_q;

							// Hori.
							if( p[pi].y > rect_q.top
								&& p[pi].y < rect_q.bottom
								&& rect_q.left  <= p[pi].x
								&& rect_q.right >= p[pi].x )
							{
								rect[0].bottom = p[pi].y;
								rect[1].top    = p[pi].y;

								bFound = true;
								break;
							}

							// Vert.
							if( p[pi].x > rect_q.left
								&& p[pi].x < rect_q.right
								&& rect_q.top    <= p[pi].y
								&& rect_q.bottom >= p[pi].y )
							{
								rect[0].left  = p[pi].x;
								rect[1].right = p[pi].x;

								bFound = true;
								break;
							}
						}

						if( bFound )
						{
							m_vecVerifySituationRect[i].erase( it );
							m_vecVerifySituationRect[i].push_back( rect[0] );
							m_vecVerifySituationRect[i].push_back( rect[1] );

							bUpdate = true;
							break;
						}


					}
				}
			}while( bUpdate );
		}
	}

	m_vecError.clear();

	if( m_vecVerifySituationRect[0].size() > 0
	 || m_vecVerifySituationRect[1].size() > 0
	 || m_vecVerifySituationRect[2].size() > 0 )
	{
		CString tmp = _T("- situation (");
		if( m_vecVerifySituationRect[0].size() > 0 )
			tmp += _T("team");

		if( m_vecVerifySituationRect[1].size() > 0 )
		{
			if( m_vecVerifySituationRect[0].size() > 0 )
				tmp += _T(", ");
			tmp += _T("opponent");
		}
		if( m_vecVerifySituationRect[2].size() > 0 )
		{
			if( m_vecVerifySituationRect[0].size() > 0 || m_vecVerifySituationRect[1].size() > 0 )
				tmp += _T(", ");
			tmp += _T("free");
		}

		tmp += _T(")lack of stratgy of. (red area)");

		m_vecError.push_back( tmp );
	}


	
	bool bError = false;
	for( auto it = m_vecSituation.begin() ; it != m_vecSituation.end() ; it++ )
	{
		bool bErrorSituation = false;
		CString tmp;

		for( int j=0 ; j<MAX_SITUATION_ROBOT_N ; j++ )
		{
			if( FindRole( it->role_assign.role[j].name ) == -1 )
			{
				if( bErrorSituation == false )
				{
					CString tmp1;
					tmp1.Format(_T("  > %s : %s"), it->name, it->role_assign.role[j].name );

					tmp = tmp + tmp1;
				}
				else
				{
					CString tmp1;
					tmp1.Format(_T(", %s"), it->role_assign.role[j].name );

					tmp = tmp + tmp1;
				}

				bErrorSituation = true;
			}
		}

		if( bErrorSituation )
		{
			if( bError == false )
			{
				CString tmp0 = _T("- role does not exist according to the situation.");
				m_vecError.push_back( tmp0 );

				bError = true;
			}

			m_vecError.push_back( tmp );
		}
	}

	LeaveCriticalSection(&m_critStrategyGUI);

	return true;
}

void CStrategyGUI::UpdateSituation( int n, Situation situation )
{
	EnterCriticalSection(&m_critStrategyGUI);

	m_vecSituation[n] = situation;

	LeaveCriticalSection(&m_critStrategyGUI);

	VerifyStrategy();
}

void CStrategyGUI::AddSituation( Situation situation )
{
	EnterCriticalSection(&m_critStrategyGUI);

	InsertSituation( m_vecSituation.size(), situation );

	LeaveCriticalSection(&m_critStrategyGUI);
}

void CStrategyGUI::InsertSituation( int n, Situation situation )
{
	EnterCriticalSection(&m_critStrategyGUI);

	auto it = m_vecSituation.begin();

	for( int i=0 ; i<n ; i++ )
	{
		it++;
	}

	m_vecSituation.insert( it, situation );

	LeaveCriticalSection(&m_critStrategyGUI);

	VerifyStrategy();
}

void CStrategyGUI::DeleteSituation( int n )
{
	EnterCriticalSection(&m_critStrategyGUI);

	auto it = m_vecSituation.begin();

	for( int i=0 ; i<n ; i++ )
	{
		it++;
	}

	m_vecSituation.erase( it );

	LeaveCriticalSection(&m_critStrategyGUI);

	VerifyStrategy();
}

int CStrategyGUI::FindSituation( CString name )
{
	int situation_i = -1;

	EnterCriticalSection(&m_critStrategyGUI);

	for( auto it = m_vecSituation.begin() ; it!=m_vecSituation.end() ; it++ )
	{
		if( it->name == name )
		{
			situation_i = (it - m_vecSituation.begin());
			break;
		}
	}

	LeaveCriticalSection(&m_critStrategyGUI);

	return situation_i;
}


CStrategyGUI::Situation CStrategyGUI::GetSituation( int i )
{
	EnterCriticalSection(&m_critStrategyGUI);

	CStrategyGUI::Situation situation = m_vecSituation[i];

	LeaveCriticalSection(&m_critStrategyGUI);

	return situation;
}

CString CStrategyGUI::GetFileName()
{
	return m_filename;
}

int CStrategyGUI::GetSituationN()
{
	EnterCriticalSection(&m_critStrategyGUI);

	int situation_n = m_vecSituation.size();

	LeaveCriticalSection(&m_critStrategyGUI);

	return situation_n;
}

int CStrategyGUI::GetRoleN()
{
	EnterCriticalSection(&m_critStrategyGUI);

	int role_n = m_vecRole.size();

	LeaveCriticalSection(&m_critStrategyGUI);

	return role_n;
}

void CStrategyGUI::AddRole( CStrategyGUI::Role role )
{
	EnterCriticalSection(&m_critStrategyGUI);

	InsertRole( m_vecRole.size(), role );

	LeaveCriticalSection(&m_critStrategyGUI);
}

void CStrategyGUI::InsertRole( int n, Role role )
{
	EnterCriticalSection(&m_critStrategyGUI);

	m_vecRole.insert( m_vecRole.begin() + n, role );

	LeaveCriticalSection(&m_critStrategyGUI);

	VerifyStrategy();
}

CStrategyGUI::Role CStrategyGUI::GetRole( int n )
{
	CStrategyGUI::Role role;

	EnterCriticalSection(&m_critStrategyGUI);

	role = m_vecRole[n];

	LeaveCriticalSection(&m_critStrategyGUI);

	return role;
}

int CStrategyGUI::FindRole( CString name )
{
	int role_i = -1;

	EnterCriticalSection(&m_critStrategyGUI);

	for( unsigned int i=0 ; i<m_vecRole.size() ; i++ )
	{
		if( m_vecRole[i].name == name )
		{
			role_i = i;
			break;
		}
	}

	LeaveCriticalSection(&m_critStrategyGUI);

	return role_i;
}


int CStrategyGUI::CountRoleInSituation( CString name )
{
	int count = 0;

	EnterCriticalSection(&m_critStrategyGUI);

	for( auto it = m_vecSituation.begin() ; it != m_vecSituation.end() ; it++ )
	{
		for( int j=0 ; j<MAX_SITUATION_ROBOT_N ; j++ )
		{
			if( it->role_assign.role[j].name == name )
			{
				count++;
			}
		}
	}

	LeaveCriticalSection(&m_critStrategyGUI);

	return count;
}


void CStrategyGUI::ChangeRoleInSituation( CString old_name, CString new_name )
{
	EnterCriticalSection(&m_critStrategyGUI);

	for( auto it = m_vecSituation.begin() ; it != m_vecSituation.end() ; it++ )
	{
		for( int j=0 ; j<MAX_SITUATION_ROBOT_N ; j++ )
		{
			if( it->role_assign.role[j].name == old_name )
			{
				it->role_assign.role[j].name = new_name;
			}
		}
	}

	LeaveCriticalSection(&m_critStrategyGUI);
}


void CStrategyGUI::UpdateRole( int n, Role role )
{
	EnterCriticalSection(&m_critStrategyGUI);

	m_vecRole[n] = role;

	LeaveCriticalSection(&m_critStrategyGUI);

	VerifyStrategy();
}

void CStrategyGUI::DeleteRole( int n )
{
	EnterCriticalSection(&m_critStrategyGUI);

	m_vecRole.erase( m_vecRole.begin() + n );

	LeaveCriticalSection(&m_critStrategyGUI);

	VerifyStrategy();
}

void CStrategyGUI::OpenFile_version_1_0(CArchive &ar)
{
	bool bErrorRobotN = false;
	CString tmpString;
	UINT tmpEnum;

	ar >> tmpString;
	if( tmpString == _T("Strategy - begin") )
	while(1)
	{
		ar >> tmpString;

		if( tmpString == _T("Strategy - end") )
		{
			break;
		}

		if( tmpString == _T("Situation - begin") )
		{
			Situation situation;

			situation.time.begin_sec = 0;
			situation.time.end_sec   = MAX_SITUATION_TIME;

			situation.priority = TypeToName(StrategyGUI_SituationPriority::Default);

			while(1)
			{
				ar >> tmpString;

				if( tmpString == _T("name") )
					ar >> situation.name;

				if( tmpString == _T("priority") )
					ar >> situation.priority;

				if( tmpString == _T("time") )
				{
					ar >> situation.time.begin_sec;
					ar >> situation.time.end_sec  ;
				}


				if( tmpString == _T("type") )
				{
					ar >> tmpEnum;
					situation.condition.area.type = (enumConditionArea)tmpEnum;
				}

				if( tmpString == _T("condition.area") )
				{
					ar >> situation.condition.area.rect.left;
					ar >> situation.condition.area.rect.right;
					ar >> situation.condition.area.rect.top;
					ar >> situation.condition.area.rect.bottom;
				}

				if( tmpString == _T("condition.ball") )
				{
					ar >> situation.condition.ball.bFree;
					ar >> situation.condition.ball.bHome;
					ar >> situation.condition.ball.bOpp;
					ar >> situation.condition.ball.owner_distance;
				}

				if( tmpString == _T("role_assign - begin") )
				{
					int robot_n;
					ar >> robot_n;
					if( robot_n != MAX_SITUATION_ROBOT_N )
					{
						if( !bErrorRobotN )
						{
							CString msg;
							msg.Format(_T("stratgy file does not match the number of robots.\n strategy file : %d´ë \n ÇÁ·Î±×·¥ Çü½Ä : %d´ë"), robot_n, MAX_SITUATION_ROBOT_N );
							AfxMessageBox(msg, MB_ICONERROR);
						}
						
						bErrorRobotN = true;

						for( int j=0 ; j<robot_n ; j++ )
						{
							while(1)
							{
								ar >> tmpString;

								CString tmpSkipString;
								double tmpSkipDouble;

								if( tmpString == _T("role.name") )
								{
									ar >> tmpSkipString;
								}
								if( tmpString == _T("role.assign.method") )
								{
									ar >> tmpSkipString;
								}
								if( tmpString == _T("role.assign.pos") )
								{
									ar >> tmpSkipDouble;
									ar >> tmpSkipDouble;			
								}
						
								if( tmpString == _T("role_assign - next") )
								{
									break;
								}
							}
						}
					}
					else
					{
						for( int j=0 ; j<robot_n ; j++ )
						{
							situation.role_assign.role[j].assign.option_hold = StrategyGUI_RoleAssignOptionHold::Refresh;

							while(1)
							{
								ar >> tmpString;

								if( tmpString == _T("role.name") )
								{
									ar >> situation.role_assign.role[j].name;
								}
								if( tmpString == _T("role.assign.option_hold") )
								{
									ar >> situation.role_assign.role[j].assign.option_hold;
								}
								if( tmpString == _T("role.assign.method") )
								{
									ar >> situation.role_assign.role[j].assign.method;
								}
								if( tmpString == _T("role.assign.pos") )
								{
									ar >> situation.role_assign.role[j].assign.pos.x;
									ar >> situation.role_assign.role[j].assign.pos.y;			
								}
						
								if( tmpString == _T("role_assign - next") )
								{
									break;
								}
							}
						}
					}
				}

				if( tmpString == _T("Situation - end") )
				{
					m_vecSituation.push_back( situation );
					break;
				}
			}
		}




		if( tmpString == _T("Role - begin") )
		{
			Role role;

			while(1)
			{
				ar >> tmpString;

				if( tmpString == _T("name") )
					ar >> role.name;

				if( tmpString == _T("Behavior - begin") )
				{
					Behavior behavior;
					behavior.options.goalkeep.clear_x_size = 0.3;
					behavior.options.goalkeep.clear_ball_speed = 0.02;
					behavior.controlType = StrategyGUI_BehaviorControlType::Once;

					while(1)
					{
						ar >> tmpString;

						if( tmpString == _T("behavior.type") )
							ar >> behavior.type;
						else
						if( tmpString == _T("behavior.controlType") )
							ar >> behavior.controlType;
						else

						// Goalkeep

						if( tmpString == _T("behavior.options.goalkeep.x_pos") )
						{
							ar >> behavior.options.goalkeep.x_pos;
						}
						else
						if( tmpString == _T("behavior.options.goalkeep.y_size") )
						{
							ar >> behavior.options.goalkeep.y_size;
						}
						else
						if( tmpString == _T("behavior.options.goalkeep.clear_y_size") )
						{
							ar >> behavior.options.goalkeep.clear_y_size;
						}
						else
						if( tmpString == _T("behavior.options.goalkeep.clear_x_size") )
						{
							ar >> behavior.options.goalkeep.clear_x_size;
						}
						else
						if( tmpString == _T("behavior.options.goalkeep.clear_ball_speed") )
						{
							ar >> behavior.options.goalkeep.clear_ball_speed;
						}
						else

						// Defense wall
						if( tmpString == _T("behavior.options.defense_wall.posA") )
						{
							ar >> behavior.options.defense_wall.posA.x;
							ar >> behavior.options.defense_wall.posA.y;
						}
						else
						if( tmpString == _T("behavior.options.defense_wall.posB") )
						{
							ar >> behavior.options.defense_wall.posB.x;
							ar >> behavior.options.defense_wall.posB.y;
						}
						else
						if( tmpString == _T("behavior.options.defense_wall.clear_x_size") )
						{
							ar >> behavior.options.defense_wall.clear_x_size;
						}
						else
						if( tmpString == _T("behavior.options.defense_wall.clear_ball_speed") )
						{
							ar >> behavior.options.defense_wall.clear_ball_speed;
						}
						else



						// Move
						if( tmpString == _T("behavior.options.move_to.destination.bBall") )
						{
							ar >> behavior.options.move_to.destination.bBall;
						}
						else
						if( tmpString == _T("behavior.options.move_to.destination.pos") )
						{
							ar >> behavior.options.move_to.destination.pos.x;
							ar >> behavior.options.move_to.destination.pos.y;
						}
						else
						if( tmpString == _T("behavior.options.move_to.destination.error") )
						{
							ar >> behavior.options.move_to.destination.error;
						}
						else

						// Move Direction
						if( tmpString == _T("behavior.options.kick_A.destination.bBall") )
						{
							ar >> behavior.options.kick_A.destination.bBall;
						}
						else
						if( tmpString == _T("behavior.options.kick_A.destination.pos") )
						{
							ar >> behavior.options.kick_A.destination.pos.x;
							ar >> behavior.options.kick_A.destination.pos.y;						
						}
						else
						if( tmpString == _T("behavior.options.kick_A.destination.error") )
						{
							ar >> behavior.options.kick_A.destination.error;
						}
						else
						if( tmpString == _T("behavior.options.kick_A.direction.bPosDirection") )
						{
							ar >> behavior.options.kick_A.direction.bPosDirection;						
						}
						else
						if( tmpString == _T("behavior.options.kick_A.direction.posDirection") )
						{
							ar >> behavior.options.kick_A.direction.posDirection.x;
							ar >> behavior.options.kick_A.direction.posDirection.y;						
						}
						else
						if( tmpString == _T("behavior.options.kick_A.direction.direction") )
						{
							ar >> behavior.options.kick_A.direction.direction;						
						}
						else


						// OrientationTo
						if( tmpString == _T("behavior.options.orientation.orientation.bPosDirection") )
						{
							ar >> behavior.options.orientation.orientation.bPosDirection;						
						}
						else
						if( tmpString == _T("behavior.options.orientation.orientation.posDirection") )
						{
							ar >> behavior.options.orientation.orientation.posDirection.x;
							ar >> behavior.options.orientation.orientation.posDirection.y;						
						}
						else
						if( tmpString == _T("behavior.options.orientation.orientation.direction") )
						{
							ar >> behavior.options.orientation.orientation.direction;						
						}
						else

						// Wait
						if( tmpString == _T("behavior.options.wait.time") )
						{
							ar >> behavior.options.wait.time;
						}
						else

						// kick_C
						if( tmpString == _T("behavior.options.kick_C.target.bPosDirection") )
						{
							ar >> behavior.options.kick_C.target.bPosDirection;						
						}
						else
						if( tmpString == _T("behavior.options.kick_C.target.posDirection") )
						{
							ar >> behavior.options.kick_C.target.posDirection.x;
							ar >> behavior.options.kick_C.target.posDirection.y;						
						}
						else
						if( tmpString == _T("behavior.options.kick_C.target.direction") )
						{
							ar >> behavior.options.kick_C.target.direction;						
						}
						else
						if( tmpString == _T("behavior.options.kick_C.approach.bPosDirection") )
						{
							ar >> behavior.options.kick_C.approach.bPosDirection;						
						}
						else
						if( tmpString == _T("behavior.options.kick_C.approach.posDirection") )
						{
							ar >> behavior.options.kick_C.approach.posDirection.x;
							ar >> behavior.options.kick_C.approach.posDirection.y;						
						}
						else
						if( tmpString == _T("behavior.options.kick_C.approach.direction") )
						{
							ar >> behavior.options.kick_C.approach.direction;						
						}
						else

						// Manual Velocity
						if( tmpString == _T("behavior.options.manual_velocity") )
						{
							ar >> behavior.options.manual_velocity.vLinear;
							ar >> behavior.options.manual_velocity.vAngular;
							ar >> behavior.options.manual_velocity.time;
						}
						else

						// Wait and kick
						if( tmpString == _T("behavior.options.kick_B.posA") )
						{
							ar >> behavior.options.kick_B.posA.x;
							ar >> behavior.options.kick_B.posA.y;
						}
						else
						if( tmpString == _T("behavior.options.kick_B.posB") )
						{
							ar >> behavior.options.kick_B.posB.x;
							ar >> behavior.options.kick_B.posB.y;
						}
						else

						if( tmpString == _T("Behavior - end") )
						{
							role.vecBehavior.push_back( behavior );
							break;
						}
						else
						{
							CString tmp;
							tmp.Format(_T("File Version : 3.0\n\n Value was found unrecognizable .\n\n\"%s\""), tmpString );
							AfxMessageBox( tmp );

							return;
						}
					}
				}

				if( tmpString == _T("Role - end") )
				{
					m_vecRole.push_back( role );
					break;
				}
			}
		}
	}
}

void CStrategyGUI::OpenFile(CArchive &ar)
{
	EnterCriticalSection(&m_critStrategyGUI);

	CString tmpString;
		
	m_vecSituation.clear();
	m_vecRole.clear();

	ar >> tmpString;

	if( tmpString == _T("Version 1.0") )
	{
		OpenFile_version_1_0( ar );
	}

	LeaveCriticalSection(&m_critStrategyGUI);

	VerifyStrategy();
}

void CStrategyGUI::SaveFile(CArchive &ar)
{
	EnterCriticalSection(&m_critStrategyGUI);

	ar << CString("Version 1.0");

	ar << CString("Strategy - begin");


	for( unsigned int i=0 ; i<m_vecSituation.size() ; i++ )
	{
		ar << CString("Situation - begin");

		ar << CString("name");
		ar << m_vecSituation[i].name;

		ar << CString("priority");
		ar << m_vecSituation[i].priority;

		ar << CString("time");
		ar << m_vecSituation[i].time.begin_sec;
		ar << m_vecSituation[i].time.end_sec;

		ar << CString("type");
		ar << m_vecSituation[i].condition.area.type;

		ar << CString("condition.area");
		ar << m_vecSituation[i].condition.area.rect.left;
		ar << m_vecSituation[i].condition.area.rect.right;
		ar << m_vecSituation[i].condition.area.rect.top;
		ar << m_vecSituation[i].condition.area.rect.bottom;

		ar << CString("condition.ball");
		ar << m_vecSituation[i].condition.ball.bFree;
		ar << m_vecSituation[i].condition.ball.bHome;
		ar << m_vecSituation[i].condition.ball.bOpp;
		ar << m_vecSituation[i].condition.ball.owner_distance;

		ar << CString("role_assign - begin");
		int robot_n = MAX_SITUATION_ROBOT_N ;
		ar << robot_n;
		for( int j=0 ; j<MAX_SITUATION_ROBOT_N ; j++ )
		{
			ar << CString("role.name");
			ar << m_vecSituation[i].role_assign.role[j].name;

			ar << CString("role.assign.option_hold");
			ar << m_vecSituation[i].role_assign.role[j].assign.option_hold;

			ar << CString("role.assign.method");
			ar << m_vecSituation[i].role_assign.role[j].assign.method;

			if( m_vecSituation[i].role_assign.role[j].assign.method == StrategyGUI_RoleAssignMethod::CloseToLocation
			 || m_vecSituation[i].role_assign.role[j].assign.method == StrategyGUI_RoleAssignMethod::GoodToKick )
			{
				ar << CString("role.assign.pos");
				ar << m_vecSituation[i].role_assign.role[j].assign.pos.x;
				ar << m_vecSituation[i].role_assign.role[j].assign.pos.y;
			}

			ar << CString("role_assign - next");
		}

		ar << CString("Situation - end");
	}

	//ar << m_vecRole.size();

	for( unsigned int i=0 ; i<m_vecRole.size() ; i++ )
	{
		ar << CString("Role - begin");

		ar << CString("name");
		ar << m_vecRole[i].name;

		//ar << m_vecRole[i].vecBehavior.size();
		for( unsigned int j=0 ; j<m_vecRole[i].vecBehavior.size() ; j++ )
		{
			ar << CString("Behavior - begin");

			ar << CString("behavior.type");
			ar << m_vecRole[i].vecBehavior[j].type;

			ar << CString("behavior.controlType");
			ar << m_vecRole[i].vecBehavior[j].controlType;

			if( m_vecRole[i].vecBehavior[j].type == StrategyGUI_BehaviorType::Goalkeep )
			{
				ar << CString("behavior.options.goalkeep.x_pos");
				ar << m_vecRole[i].vecBehavior[j].options.goalkeep.x_pos;
				ar << CString("behavior.options.goalkeep.y_size");
				ar << m_vecRole[i].vecBehavior[j].options.goalkeep.y_size;
				ar << CString("behavior.options.goalkeep.clear_x_size");
				ar << m_vecRole[i].vecBehavior[j].options.goalkeep.clear_x_size;
				ar << CString("behavior.options.goalkeep.clear_y_size");
				ar << m_vecRole[i].vecBehavior[j].options.goalkeep.clear_y_size;
				ar << CString("behavior.options.goalkeep.clear_ball_speed");
				ar << m_vecRole[i].vecBehavior[j].options.goalkeep.clear_ball_speed;
			}

			if( m_vecRole[i].vecBehavior[j].type == StrategyGUI_BehaviorType::Defense_Wall )
			{
				ar << CString("behavior.options.defense_wall.posA");
				ar << m_vecRole[i].vecBehavior[j].options.defense_wall.posA.x;
				ar << m_vecRole[i].vecBehavior[j].options.defense_wall.posA.y;
				ar << CString("behavior.options.defense_wall.posB");
				ar << m_vecRole[i].vecBehavior[j].options.defense_wall.posB.x;
				ar << m_vecRole[i].vecBehavior[j].options.defense_wall.posB.y;
				ar << CString("behavior.options.defense_wall.clear_x_size");
				ar << m_vecRole[i].vecBehavior[j].options.defense_wall.clear_x_size;
				ar << CString("behavior.options.defense_wall.clear_ball_speed");
				ar << m_vecRole[i].vecBehavior[j].options.defense_wall.clear_ball_speed;
			}

			if( m_vecRole[i].vecBehavior[j].type == StrategyGUI_BehaviorType::MoveTo )
			{
				ar << CString("behavior.options.move_to.destination.bBall");
				ar << m_vecRole[i].vecBehavior[j].options.move_to.destination.bBall;

				ar << CString("behavior.options.move_to.destination.pos");
				ar << m_vecRole[i].vecBehavior[j].options.move_to.destination.pos.x;
				ar << m_vecRole[i].vecBehavior[j].options.move_to.destination.pos.y;

				ar << CString("behavior.options.move_to.destination.error");
				ar << m_vecRole[i].vecBehavior[j].options.move_to.destination.error;
			}

			if( m_vecRole[i].vecBehavior[j].type == StrategyGUI_BehaviorType::Kick_A )
			{
				ar << CString("behavior.options.kick_A.destination.bBall");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.destination.bBall;

				ar << CString("behavior.options.kick_A.destination.pos");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.destination.pos.x;
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.destination.pos.y;

				ar << CString("behavior.options.kick_A.destination.error");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.destination.error;


				ar << CString("behavior.options.kick_A.direction.bPosDirection");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.direction.bPosDirection;

				ar << CString("behavior.options.kick_A.direction.posDirection");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.direction.posDirection.x;
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.direction.posDirection.y;

				ar << CString("behavior.options.kick_A.direction.direction");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.direction.direction;
			}

			if( m_vecRole[i].vecBehavior[j].type == StrategyGUI_BehaviorType::Kick_B )
			{
				ar << CString("behavior.options.kick_B.posA");
				ar << m_vecRole[i].vecBehavior[j].options.kick_B.posA.x;
				ar << m_vecRole[i].vecBehavior[j].options.kick_B.posA.y;
				ar << CString("behavior.options.kick_B.posB");
				ar << m_vecRole[i].vecBehavior[j].options.kick_B.posB.x;
				ar << m_vecRole[i].vecBehavior[j].options.kick_B.posB.y;
			}

			if( m_vecRole[i].vecBehavior[j].type == StrategyGUI_BehaviorType::Velocity   )
			{
				ar << CString("behavior.options.manual_velocity");
				ar << m_vecRole[i].vecBehavior[j].options.manual_velocity.vLinear;
				ar << m_vecRole[i].vecBehavior[j].options.manual_velocity.vAngular;
				ar << m_vecRole[i].vecBehavior[j].options.manual_velocity.time;
			}

			if( m_vecRole[i].vecBehavior[j].type == StrategyGUI_BehaviorType::OrientationTo   )
			{
				ar << CString("behavior.options.orientation.orientation.bPosDirection");
				ar << m_vecRole[i].vecBehavior[j].options.orientation.orientation.bPosDirection;

				ar << CString("behavior.options.orientation.orientation.posDirection");
				ar << m_vecRole[i].vecBehavior[j].options.orientation.orientation.posDirection.x;
				ar << m_vecRole[i].vecBehavior[j].options.orientation.orientation.posDirection.y;

				ar << CString("behavior.options.orientation.orientation.direction");
				ar << m_vecRole[i].vecBehavior[j].options.orientation.orientation.direction;
			}

			if( m_vecRole[i].vecBehavior[j].type == StrategyGUI_BehaviorType::Kick_C )
			{
				ar << CString("behavior.options.kick_C.target.bPosDirection");
				ar << m_vecRole[i].vecBehavior[j].options.kick_C.target.bPosDirection;

				ar << CString("behavior.options.kick_C.target.posDirection");
				ar << m_vecRole[i].vecBehavior[j].options.kick_C.target.posDirection.x;
				ar << m_vecRole[i].vecBehavior[j].options.kick_C.target.posDirection.y;

				ar << CString("behavior.options.kick_C.target.direction");
				ar << m_vecRole[i].vecBehavior[j].options.kick_C.target.direction;



				ar << CString("behavior.options.kick_C.approach.bPosDirection");
				ar << m_vecRole[i].vecBehavior[j].options.kick_C.approach.bPosDirection;

				ar << CString("behavior.options.kick_C.approach.posDirection");
				ar << m_vecRole[i].vecBehavior[j].options.kick_C.approach.posDirection.x;
				ar << m_vecRole[i].vecBehavior[j].options.kick_C.approach.posDirection.y;

				ar << CString("behavior.options.kick_C.approach.direction");
				ar << m_vecRole[i].vecBehavior[j].options.kick_C.approach.direction;
			}

			if( m_vecRole[i].vecBehavior[j].type == StrategyGUI_BehaviorType::Wait )
			{
				ar << CString("behavior.options.wait.time");
				ar << m_vecRole[i].vecBehavior[j].options.wait.time;
			}

			// Adding functions for new action, currently same as Kick_A
			if (m_vecRole[i].vecBehavior[j].type == StrategyGUI_BehaviorType::Corner_Kick)
			{
				ar << CString("behavior.options.kick_A.destination.bBall");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.destination.bBall;

				ar << CString("behavior.options.kick_A.destination.pos");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.destination.pos.x;
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.destination.pos.y;

				ar << CString("behavior.options.kick_A.destination.error");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.destination.error;


				ar << CString("behavior.options.kick_A.direction.bPosDirection");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.direction.bPosDirection;

				ar << CString("behavior.options.kick_A.direction.posDirection");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.direction.posDirection.x;
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.direction.posDirection.y;

				ar << CString("behavior.options.kick_A.direction.direction");
				ar << m_vecRole[i].vecBehavior[j].options.kick_A.direction.direction;
			}


			ar << CString("Behavior - end");
		}

		ar << CString("Role - end");
	}


	ar << CString("Strategy - end");

	LeaveCriticalSection(&m_critStrategyGUI);
}

CString CStrategyGUI::RoleOptionString( int roleID, int behaviorID )
{
	CString strResult;

	EnterCriticalSection(&m_critStrategyGUI);

	if( m_vecRole[roleID].vecBehavior[behaviorID].type == StrategyGUI_BehaviorType::Goalkeep     )
	{
		strResult.Format(_T("defence area(X position:%.3lfm, Y width:¡¾%.3lfm, kick out area(width:%.3lfm, width:%.3lfm, kick out condition(attack speed is>%.3lfm/s)"),
			m_vecRole[roleID].vecBehavior[behaviorID].options.goalkeep.x_pos,
			m_vecRole[roleID].vecBehavior[behaviorID].options.goalkeep.y_size,
			m_vecRole[roleID].vecBehavior[behaviorID].options.goalkeep.clear_x_size,
			m_vecRole[roleID].vecBehavior[behaviorID].options.goalkeep.clear_y_size,
			m_vecRole[roleID].vecBehavior[behaviorID].options.goalkeep.clear_ball_speed
			);
	}

	if( m_vecRole[roleID].vecBehavior[behaviorID].type == StrategyGUI_BehaviorType::Defense_Wall )
	{
		strResult = _T("(no)");
	}

	if( m_vecRole[roleID].vecBehavior[behaviorID].type == StrategyGUI_BehaviorType::MoveTo )
	{
		if( m_vecRole[roleID].vecBehavior[behaviorID].options.move_to.destination.bBall )
		{
			strResult.Format(_T("location(ball)"));
		}
		else
		{
			strResult.Format(_T("location(%.3lfm,%.3lfm)"),
				m_vecRole[roleID].vecBehavior[behaviorID].options.move_to.destination.pos.x,
				m_vecRole[roleID].vecBehavior[behaviorID].options.move_to.destination.pos.y );
		}
	}

	if( m_vecRole[roleID].vecBehavior[behaviorID].type == StrategyGUI_BehaviorType::Kick_A )
	{
		if( m_vecRole[roleID].vecBehavior[behaviorID].options.kick_A.destination.bBall )
		{
			strResult.Format(_T("location(ball) direction(%.0lfdeg)"),
				m_vecRole[roleID].vecBehavior[behaviorID].options.orientation );
		}
		else
		{
			strResult.Format(_T("location(%.3lfm,%.3lfm) direction(%.0lfdeg)"), 
				m_vecRole[roleID].vecBehavior[behaviorID].options.kick_A.destination.pos.x, 
				m_vecRole[roleID].vecBehavior[behaviorID].options.kick_A.destination.pos.y,
				m_vecRole[roleID].vecBehavior[behaviorID].options.orientation );
		}
	}

	if( m_vecRole[roleID].vecBehavior[behaviorID].type == StrategyGUI_BehaviorType::Velocity )
	{
			strResult.Format(_T("linear v(%.3lfm/s) angular(%.3lfdegree/s) time(%.1lfs)"),
				m_vecRole[roleID].vecBehavior[behaviorID].options.manual_velocity.vLinear,
				m_vecRole[roleID].vecBehavior[behaviorID].options.manual_velocity.vAngular,
				m_vecRole[roleID].vecBehavior[behaviorID].options.manual_velocity.time );
	}

	if( m_vecRole[roleID].vecBehavior[behaviorID].type == StrategyGUI_BehaviorType::OrientationTo )
	{
			strResult.Format(_T("direction(%.0lfdeg)"),
				m_vecRole[roleID].vecBehavior[behaviorID].options.orientation.orientation.direction );
	}

	// Adding functions for new action, currently same as Kick_A
	if (m_vecRole[roleID].vecBehavior[behaviorID].type == StrategyGUI_BehaviorType::Corner_Kick)
	{
		if (m_vecRole[roleID].vecBehavior[behaviorID].options.kick_A.destination.bBall)
		{
			strResult.Format(_T("location(ball) direction(%.0lfdeg)"),
				m_vecRole[roleID].vecBehavior[behaviorID].options.orientation);
		}
		else
		{
			strResult.Format(_T("location(%.3lfm,%.3lfm) direction(%.0lfdeg)"),
				m_vecRole[roleID].vecBehavior[behaviorID].options.kick_A.destination.pos.x,
				m_vecRole[roleID].vecBehavior[behaviorID].options.kick_A.destination.pos.y,
				m_vecRole[roleID].vecBehavior[behaviorID].options.orientation);
		}
	}

	LeaveCriticalSection(&m_critStrategyGUI);

	return strResult;
}

int CStrategyGUI::GetVerifyVerifySituationRectN( int category )
{
	int rect_n;

	EnterCriticalSection(&m_critStrategyGUI);

	rect_n = m_vecVerifySituationRect[ category ].size();

	LeaveCriticalSection(&m_critStrategyGUI);

	return rect_n;
}

CRectDouble CStrategyGUI::GetVerifyVerifySituationRect( int category, int rect_i )
{
	CRectDouble rect;
	
	EnterCriticalSection(&m_critStrategyGUI);

	rect = m_vecVerifySituationRect[ category ][rect_i];

	LeaveCriticalSection(&m_critStrategyGUI);

	return rect;
}

CString CStrategyGUI::GetErrorMsg()
{
	CString tmp;

	EnterCriticalSection(&m_critStrategyGUI);

	for( auto it=m_vecError.begin() ; it != m_vecError.end() ; it++ )
	{
		tmp += *it;
		tmp += _T("\n");
	}

	LeaveCriticalSection(&m_critStrategyGUI);

	return tmp;
}
