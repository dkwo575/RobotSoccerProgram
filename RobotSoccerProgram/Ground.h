#pragma once

#include"PointDouble.h"

class CGround
{
public:
	enum Enum
	{
		NOTHING,
		_5vs5,
		_11vs11,
		_3vs3,
		_AndroSot,
	};

	CPointDouble Origin();

	int Type();
	void ScreenToGround( CPointDouble &p );
	void ScreenToGround( double &p );
	void GroundToScreen( CPointDouble &p );
	void GroundToScreen( double &p );
	void ScreenToGround( double &x, double &y );
	void GroundToScreen( double &x, double &y );
	double ScreenRatio();
	void SetScreenRatio( double ratio );
	void SetCenter( CPoint center );
	CPoint Center();
	double Width();
	double Height();
	double Goalsize();
	void Draw( CDC *pDC, COLORREF color, bool bNULL_BRUSH, bool bGuideLine );
	void SetGround( int type, CRect rect, double zoom, CPoint center );
	void SetGround( int type, CRect rect, double zoom );
	void SetGround( int type );

	CGround(void);
	~CGround(void);

protected:
	void DrawMark( CDC *pDC, CPoint point );
	void ResizeToScreen( CRect &rect );
	void ResizeToScreen();


	int m_Type;

	CPoint m_origin;
	CPoint m_center;
	double m_screenRatio;

	CRect m_rect;
	CRect m_Ground;

	CRect m_GoalArea[2];
	CRect m_PenaltyArea[2];
	CRect m_GoalinArea[2];
	CRect m_PKCircle[2];

	CRect m_CenterCircle;
//	CRect m_Corner[4];

	CRect m_FKCircle[2];

	CRect m_FreeBall[4];
};

