#pragma once
class CStrategyParameter
{
public:
	void Open(CArchive &ar);
	void Save(CArchive &ar);

	CStrategyParameter(void);
	~CStrategyParameter(void);

	double m_AvoidBoundSize       ;
	double m_LinearVelocityLimitA ;
	double m_GoalYSize            ;
	double m_DefenseLineX         ;
	double m_OffenseLineX         ;

	double m_GoalkeeperX          ;
	double m_GoalkeeperYSize      ;
	double m_GoalkeeperClearX     ;
	double m_GoalkeeperClearYSize ;

	double m_SweeperX             ;
	double m_SweeperYSize         ;

	double m_WingBack_Def_X       ;
	double m_WingBack_Def_Y       ;
	double m_WingBack_Nor_X       ;
	double m_WingBack_Nor_Y       ;

	double m_WingForward_Nor_X    ;
	double m_WingForward_Nor_Y    ;
	double m_WingForward_Off_X    ;
	double m_WingForward_Off_Y    ;

	double m_MF_X1                ;
	double m_MF_X2                ;

	double m_CenterBack_Def_X     ;
	double m_CenterBack_Def_Y     ;
	double m_CenterBack_Nor_X     ;

	double m_CenterForward_Nor_X  ;
	double m_CenterForward_Off_X  ;

	double m_AverageVelocity      ;
	double m_HitTime              ;
};

