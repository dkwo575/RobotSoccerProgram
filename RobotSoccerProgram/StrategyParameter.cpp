#include "StdAfx.h"
#include "StrategyParameter.h"


CStrategyParameter::CStrategyParameter(void)
{
	m_AvoidBoundSize       = 0.04;
	m_LinearVelocityLimitA = 0.05;
	m_GoalYSize            = 0.191;
	m_DefenseLineX         = 0.44;
	m_OffenseLineX         = 0.44;

	m_GoalkeeperX          = 0.044;
	m_GoalkeeperYSize      = 0.14;
	m_GoalkeeperClearX     = 0.151;
	m_GoalkeeperClearYSize = 0.40;

	m_SweeperX             = 0.190;
	m_SweeperYSize         = 0.17;

	m_WingBack_Def_X       = 0.25;
	m_WingBack_Def_Y       = 0.5;
	m_WingBack_Nor_X       = 0.5;
	m_WingBack_Nor_Y       = 0.5;

	m_WingForward_Nor_X    = 0.5;
	m_WingForward_Nor_Y    = 0.5;
	m_WingForward_Off_X    = 1.15;
	m_WingForward_Off_Y    = 0.6;

	m_MF_X1                = 2.37;
	m_MF_X2                = 2.51;

	m_CenterBack_Def_X     = 0.40;
	m_CenterBack_Def_Y     = 0.21;
	m_CenterBack_Nor_X     = 1.0;

	m_CenterForward_Nor_X  = 1.95;
	m_CenterForward_Off_X  = 2.05;

	m_AverageVelocity      = 1.46;
	m_HitTime              = 0.62;
}


CStrategyParameter::~CStrategyParameter(void)
{
}

void CStrategyParameter::Save(CArchive &ar)
{
	ar << m_AvoidBoundSize       ;
	ar << m_LinearVelocityLimitA ;
	ar << m_GoalYSize            ;
	ar << m_DefenseLineX         ;
	ar << m_OffenseLineX         ;

	ar << m_GoalkeeperX          ;
	ar << m_GoalkeeperYSize      ;
	ar << m_GoalkeeperClearX     ;
	ar << m_GoalkeeperClearYSize ;

	ar << m_SweeperX             ;
	ar << m_SweeperYSize         ;

	ar << m_WingBack_Def_X       ;
	ar << m_WingBack_Def_Y       ;
	ar << m_WingBack_Nor_X       ;
	ar << m_WingBack_Nor_Y       ;

	ar << m_WingForward_Nor_X    ;
	ar << m_WingForward_Nor_Y    ;
	ar << m_WingForward_Off_X    ;
	ar << m_WingForward_Off_Y    ;

	ar << m_MF_X1                ;
	ar << m_MF_X2                ;

	ar << m_CenterBack_Def_X     ;
	ar << m_CenterBack_Def_Y     ;
	ar << m_CenterBack_Nor_X     ;

	ar << m_CenterForward_Nor_X  ;
	ar << m_CenterForward_Off_X  ;

	ar << m_AverageVelocity      ;
	ar << m_HitTime              ;
}

void CStrategyParameter::Open(CArchive &ar)
{
	ar >> m_AvoidBoundSize       ;
	ar >> m_LinearVelocityLimitA ;
	ar >> m_GoalYSize            ;
	ar >> m_DefenseLineX         ;
	ar >> m_OffenseLineX         ;

	ar >> m_GoalkeeperX          ;
	ar >> m_GoalkeeperYSize      ;
	ar >> m_GoalkeeperClearX     ;
	ar >> m_GoalkeeperClearYSize ;

	ar >> m_SweeperX             ;
	ar >> m_SweeperYSize         ;

	ar >> m_WingBack_Def_X       ;
	ar >> m_WingBack_Def_Y       ;
	ar >> m_WingBack_Nor_X       ;
	ar >> m_WingBack_Nor_Y       ;

	ar >> m_WingForward_Nor_X    ;
	ar >> m_WingForward_Nor_Y    ;
	ar >> m_WingForward_Off_X    ;
	ar >> m_WingForward_Off_Y    ;

	ar >> m_MF_X1                ;
	ar >> m_MF_X2                ;

	ar >> m_CenterBack_Def_X     ;
	ar >> m_CenterBack_Def_Y     ;
	ar >> m_CenterBack_Nor_X     ;

	ar >> m_CenterForward_Nor_X  ;
	ar >> m_CenterForward_Off_X  ;

	ar >> m_AverageVelocity      ;
	ar >> m_HitTime              ;
}
