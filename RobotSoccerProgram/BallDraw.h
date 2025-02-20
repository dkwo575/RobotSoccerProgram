#pragma once

#include "ball.h"
#include "FrameDC.h"

class CBallDraw
{
public:
	void SetColor( int type, int state, COLORREF pen, COLORREF brush );

	void Draw( CFrameDC *pDC, CGround* pGround, CBall *pBall );
	void DrawCurrent( CFrameDC *pDC, CGround* pGround, CBall *pBall );
	void DrawInfo( CFrameDC *pDC, CBall *pBall );

	CBallDraw(void);
	~CBallDraw(void);

protected:
	COLORREF m_colorPen[2][3];
	COLORREF m_colorBrush[2][3];
	COLORREF m_colorPenSelect[2];
	COLORREF m_colorBrushSelect[2];
};

