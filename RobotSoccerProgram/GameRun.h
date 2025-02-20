#pragma once

#include "Ground.h"	// Added by ClassView
#include "Robot.h"	// Added by ClassView
#include "Ball.h"	// Added by ClassView
#include "AutopositionData.h"	// Added by ClassView

#define ZERO_DISTANCE 0.01 // meter
#define ZERO_ANGLE    2.0  // degree

#include "StrategyParameter.h"
#include "Situation.h"

#include "StrategyGUI.h"

class CGameRun
{
public:
	void SetRobotName( CString name[] );
	void SetRobotRole( CString nameRole[] );

	void UnderstandSituation();
	CStrategyParameter m_StrategyParam;
	CSituation m_situation;
	void UpdateRole();
	void UpdateRole_3vs3();
	void UpdateRole_5vs5();
	double ccw(CPointDouble p1, CPointDouble p2, CPointDouble p3);
	void UpdateMission();
	void UpdateMission_GUI( bool bSetplay_init = false );

	void ExecuteMission();

	void Run( bool bRoleChange );
	void RunGUI();

	CGameRun(void);
	~CGameRun(void);



	int m_opponentN;
	int m_robotN;

	CBall m_Ball;
	CRobot* m_Robot;
	CBall* m_Opponent;

	void SetGroundType(int type, CRect rect, double zoom );

	CStrategyGUI m_strategyGUI;

protected:
	CRITICAL_SECTION m_critGame;
	
	CString m_strParametersFileName;

	double m_timeStart;
	double m_timeGame;
	double m_timeNow;

	
	bool LoadAutoPosition( CString situation );
	bool UpdateAutoPosition( CString situation );
	CAutopositionData m_AutoPositionData;


	CGround m_ground;


	CStrategyGUI::Situation m_situationCurrent;
	
	CString m_strSituationName[11];

	bool Intersection( CPointDouble P1, CPointDouble P2, CPointDouble Q1, CPointDouble Q2, CPointDouble& Intersection );
	CPointDouble InsideGround( CPointDouble A, CPointDouble B, CPointDouble W1, CPointDouble W2 );
};

