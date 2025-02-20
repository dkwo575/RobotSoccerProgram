#pragma once

#include "Robot.h"
#include "FrameDC.h"

class CRobotDraw
{
public:
	void SetColor( int type, int state, COLORREF body, COLORREF wheel );

	void DrawArrow(CFrameDC *pDC, CGround *pGround, CPointDouble posBegin, CPointDouble posEnd, double orientation, double size_length, double size_angle, COLORREF color );
	double ccw(CPointDouble p1, CPointDouble p2, CPointDouble p3);

	//void DrawPath(CDC *pDC);
	void DrawInfoToGround(CFrameDC *pDC, CGround *pGround, CRobot *pRobot, CString strInfo = _T(""));
	void DrawMission(CFrameDC *pDC, CGround *pGround, CRobot *pRobot);
	CPointDouble MakeVector(CGround *pGround, CRobot *pRobot, CPointDouble vector_pos);
	void DrawPath(CFrameDC *pDC, CGround *pGround, CPathCubicSpline& path);


	void DrawBody(CFrameDC *pDC, CGround *pGround, CRobot *pRobot, double robot_size=1.0);
	void DrawBody_MiroSot(CFrameDC *pDC, CGround *pGround, CRobot *pRobot, double robot_size);
	void DrawBody_AndroSot(CFrameDC *pDC, CGround *pGround, CRobot *pRobot, double robot_size);

	void DrawBodyCurrent(CFrameDC *pDC, CGround *pGround, CRobot *pRobot);

	CRobotDraw(void);
	~CRobotDraw(void);

protected:
	COLORREF m_colorPenBody[2][3];
	COLORREF m_colorPenWheel[2][3];
	COLORREF m_colorPenBodySelect[2];
	COLORREF m_colorPenWheelSelect[2];
};

