#pragma once

#include "GameRun.h"
#include "BallDraw.h"
#include "RobotDraw.h"

class CGameGUI :
	public CGameRun
{
public:
	void Stop();
	// Mouse
	int SelectRobotID();
	void Screen_DragObject( CPoint p1, CPoint p2 );
	void Screen_SelectObject( CPoint p1, CPoint p2 );
	void Screen_DropObject( CPoint p1, CPoint p2, bool bCtrl = false );
	bool Screen_IsObject( CPoint p );

	bool Screen_Grasp( CPoint p );
	
	void Screen_ControlOrientationTo( CPoint point1, CPoint point2, bool bDrop = false );
	void Screen_ControlMoveTo( CPoint point, int MoveType );

	void DrawDisplay(CFrameDC *pDC, bool bRobotMessage, bool bRobotMessageOnly );

	CGameGUI(void);
	~CGameGUI(void);

protected:
	std::vector<double> m_vecTest1;
	std::vector<double> m_vecTest2;
	CRITICAL_SECTION m_critGameGUI;

	CRobot* m_Robot_share;
	CRobot* m_Robot_draw;


	void DrawStrategyParameter( CDC *pDC );
	void DrawAutoPosition( CFrameDC *pDC, CString situation );

	bool IsPointInRect( CRect rect, CPointDouble point );
	bool IsPointInRect( CPointDouble p1, CPointDouble p2, CPointDouble point );

};

