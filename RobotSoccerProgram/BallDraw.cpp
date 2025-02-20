#include "StdAfx.h"
#include "BallDraw.h"

#define _USE_MATH_DEFINES
#include <math.h>

CBallDraw::CBallDraw(void)
{
	for( int i=0 ; i<2 ; i++ )
	{
		m_colorPen[i][1] = RGB(128,128,128);
		m_colorBrush[i][1] = RGB(0,0,0);
		m_colorPen[i][2] = RGB(255,0,0);
		m_colorBrush[i][2] = RGB(0,0,0);
		m_colorPen[i][3] = RGB(128,0,0);
		m_colorBrush[i][3] = RGB(0,0,0);

		m_colorPenSelect[i] = RGB(255,0,0);
		m_colorBrushSelect[i] = RGB(0,255,0);
	}
}


CBallDraw::~CBallDraw(void)
{
}


//////////////////////////////////////////////////////////////////////////
// Draw
//////////////////////////////////////////////////////////////////////////

void CBallDraw::SetColor( int type, int state, COLORREF pen, COLORREF brush )
{
	if( state == 3 )
	{
		m_colorPenSelect[type] = pen;
		m_colorBrushSelect[type] = brush;
	}

	m_colorPen[type][state] = pen;
	m_colorBrush[type][state] = brush;
}

void CBallDraw::Draw(CFrameDC *pDC, CGround* pGround, CBall *pBall)
{
	int state = pBall->State();
	CPointDouble pos = pBall->Position();
	CPointDouble velocity = pBall->Velocity();
	double radiusDC = pBall->Radius();

	CPointDouble posDC = pos + pBall->DragPoint();
	CPointDouble velocityDC = posDC + velocity;

	pGround->GroundToScreen( posDC );
	pGround->GroundToScreen( velocityDC );
	pGround->GroundToScreen( radiusDC );


	COLORREF colorPen, colorBrush;

//	if( IsSelect() )
//	{
//		colorPen = m_colorPenSelect[1];
//		colorBrush = m_colorBrushSelect[1];
//	}
//	else
	{
		colorPen = m_colorPen[1][state];
		colorBrush = m_colorBrush[1][state];
	}

	{
		pDC->SelectBrush( colorBrush );
		pDC->SelectPen( colorPen, PS_SOLID, 1 );

		pDC->Circle( (int)posDC.x, (int)posDC.y, (int)radiusDC );

		pDC->MoveTo( posDC.Integer() );
		pDC->LineTo( velocityDC.Integer() );
		
		CString tmp;
		tmp.Format(_T("(%.1lf, %.1lf)"), pos.x*1000, pos.y*1000 );
		CRect rect( (int)posDC.x, (int)posDC.y, (int)posDC.x + 100, (int)posDC.y+20 );
		//pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
}

void CBallDraw::DrawCurrent(CFrameDC *pDC, CGround* pGround, CBall *pBall)
{
	int state = pBall->State();
	CPointDouble pos = pBall->PositionCurrent();
	CPointDouble velocity = pBall->Velocity();
	double radiusDC = pBall->Radius();


	CPointDouble posDC = pos + pBall->DragPoint();
	CPointDouble velocityDC = posDC + velocity;

	pGround->GroundToScreen( posDC );
	pGround->GroundToScreen( velocityDC );
	pGround->GroundToScreen( radiusDC );



	COLORREF colorPen, colorBrush;

	if( pBall->IsSelect() )
	{
		colorPen = m_colorPenSelect[1];
		colorBrush = m_colorBrushSelect[1];
	}
	else
	{
		colorPen = m_colorPen[1][state];
		colorBrush = m_colorBrush[1][state];
	}

	{
		pDC->SelectBrush( colorBrush );
		pDC->SelectPen( colorPen, PS_SOLID, 1 );

		pDC->Circle( (int)posDC.x, (int)posDC.y, (int)radiusDC/2 );

		pDC->MoveTo( posDC.Integer() );
		pDC->LineTo( velocityDC.Integer() );
		
		//CRect rect( (int)posDC.x, (int)posDC.y, (int)posDC.x + 45, (int)posDC.y+12 );
		//CString tmp;
		//tmp.Format(_T("%.3lf"), velocity.x );
		//pDC->DrawText( tmp, rect, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		//tmp.Format(_T("%.3lf"), velocity.y );
		//pDC->DrawText( tmp, rect+CPoint(0,12), DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		//tmp.Format(_T("%.3lf"), velocity.Distance() );
		//pDC->DrawText( tmp, rect+CPoint(0,24), DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	}
}
void CBallDraw::DrawInfo(CFrameDC *pDC, CBall *pBall)
{
	CPointDouble pos = pBall->Position();
	CPointDouble velocity = pBall->Velocity();
	CPointDouble posError = pBall->PositionError();


	COLORREF title_bgcolor=RGB(160,160,160);
	COLORREF data_bgcolor=RGB(255,255,255);

	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( RGB( 0,0,0 ) );
	
	// print text 
//	CString tmp[6];
//	tmp[0].Format("-- Ball Information --");
//	tmp[1].Format("(X,Y) = ( %+06.1lf, %+06.1lf)", posDisplay.x, posDisplay.y );
//	tmp[2].Format("         Real     Simulation");
//	tmp[3].Format(" Vc      %+06.1lf  %+06.1lf", m_velocity.Distance(), m_SimulationVelocity.Distance()  );
//	tmp[4].Format(" Angle   %+06.1lf  %+06.1lf", m_velocity.Angle(), m_SimulationVelocity.Angle()  );
//	tmp[5].Format("ErrorX:%+7.2lf ErrorY:%+7.2lf\n", m_error.x, m_error.y );
//	tmp[5].Format("");
//	
//	for( int i=0 ; i<6 ; i++ )
//		pDC->TextOut( 0, i*15, tmp[i]);

	CRect infoRectOrgin(0, 0, 233, 200);
	CRect infoRect = infoRectOrgin;
	int nextY = 0;
	int height = 15;
	{
		CString tmp;
		tmp.Format(_T("Ball"));
		CRect rect( 0, nextY, infoRect.Width(), nextY+height );
		rect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect( rect, title_bgcolor);
		pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
	nextY+=height;

	{
		CRect rect( 0, nextY, infoRect.Width()/3, nextY+height );
		rect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect( rect, title_bgcolor);
		pDC->DrawText(_T("X"), rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
	{
		CRect rect( infoRect.Width()/3, nextY, infoRect.Width()*2/3, nextY+height );
		rect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect( rect, title_bgcolor);
		pDC->DrawText(_T("Y"), rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
	{
		CRect rect( infoRect.Width()*2/3, nextY, infoRect.Width(), nextY+height );
		rect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect( rect, title_bgcolor);
		pDC->DrawText(_T("Angle"), rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
	nextY+=height;


	{
		CString tmp;
		tmp.Format(_T("%+06.1lf"), pos.x*100);
		CRect rect( 0, nextY, infoRect.Width()/3, nextY+height );
		rect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect( rect, data_bgcolor);
		rect.DeflateRect(5,0,5,0);
		pDC->DrawText( tmp, rect, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	}
	{
		CString tmp;
		tmp.Format(_T("%+06.1lf"), pos.y*100);
		CRect rect( infoRect.Width()/3, nextY, infoRect.Width()*2/3, nextY+height );
		rect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect( rect, data_bgcolor);
		rect.DeflateRect(5,0,5,0);
		pDC->DrawText( tmp, rect, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	}
	{
		CString tmp;
		tmp.Format(_T("%+06.1lf"), velocity.AngleDegree());
		CRect rect( infoRect.Width()*2/3, nextY, infoRect.Width(), nextY+height );
		rect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect( rect, data_bgcolor);
		rect.DeflateRect(5,0,5,0);
		pDC->DrawText( tmp, rect, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	}
	nextY+=height;

	{
		CString tmp;
		tmp.Format(_T("%+06.1lf"), posError.x*100);
		CRect rect( 0, nextY, infoRect.Width()/3, nextY+height );
		rect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect( rect, data_bgcolor);
		rect.DeflateRect(5,0,5,0);
		pDC->DrawText( tmp, rect, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	}
	{
		CString tmp;
		tmp.Format(_T("%+06.1lf"), posError.y*100);
		CRect rect( infoRect.Width()/3, nextY, infoRect.Width()*2/3, nextY+height );
		rect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect( rect, data_bgcolor);
		rect.DeflateRect(5,0,5,0);
		pDC->DrawText( tmp, rect, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	}
	nextY+=height;

	{
		CRect rect( infoRect.Width()/3, nextY, infoRect.Width()*2/3, nextY+height );
		rect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect( rect, title_bgcolor);
		pDC->DrawText(_T("Velocity"), rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
	nextY+=height;

	{
		CString tmp;
		tmp.Format(_T("%+06.1lf"), velocity.Distance()*100);
		CRect rect( infoRect.Width()/3, nextY, infoRect.Width()*2/3, nextY+height );
		rect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect( rect, data_bgcolor);
		rect.DeflateRect(5,0,5,0);
		pDC->DrawText( tmp, rect, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	}
	nextY+=height;


}