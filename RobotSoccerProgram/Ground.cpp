#include "StdAfx.h"
#include "Ground.h"



CGround::CGround()
{
	if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_3vs3 )
	{
		SetGround( CGround::_3vs3, CRect(0,0,639,479), 240 );
		SetCenter( CPoint(320, 240) );
	}

	if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_5vs5 )
	{
		SetGround( CGround::_5vs5, CRect(0,0,639,479), 180 );
		SetCenter( CPoint(320, 210) );
	}

	if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_AndroSot )
	{
		SetGround( CGround::_AndroSot, CRect(0,0,639,479), 180 );
		SetCenter( CPoint(320, 210) );
	}
}

CGround::~CGround()
{

}

void CGround::SetScreenRatio( double ratio )
{
	SetGround( m_Type, m_rect, ratio );
}

void CGround::SetCenter( CPoint center )
{
	SetGround( m_Type, m_rect, m_screenRatio, center );
}

CPoint CGround::Center()
{
	return m_center;
}

void CGround::SetGround( int type )
{
	SetGround( type, CRect(0, 0, 100, 100), 1 );
}

void CGround::SetGround( int type, CRect rect, double zoom )
{
	CPoint center = CPoint( rect.Width()/2, rect.Height()/2 );

	SetGround( type, rect, zoom, center );
}

void CGround::SetGround( int type, CRect rect, double zoom, CPoint center )
{
	m_Type = type;
	m_screenRatio = zoom;

	m_rect.left = 0;
	m_rect.top = 0;
	m_rect.right = rect.Width();
	m_rect.bottom = rect.Height();

	m_center = center;

	if( m_Type == CGround::_AndroSot )
	{
		m_origin.x = (long)(m_center.x - 2.20/2.0*m_screenRatio);
		m_origin.y = (long)(m_center.y - 1.80/2.0*m_screenRatio);

		m_Ground = CRect( 0, 0, 220, 180 );

		m_GoalArea[0] = CRect( 0, 0, 15, 90 ) + CPoint(0, 45);
		m_GoalArea[1] = CRect( 0, 0, 15, 90 ) + CPoint(220-15, 45) ;

		m_PenaltyArea[0] = CRect( 0, 0, 40, 110 ) + CPoint(0, 35);
		m_PenaltyArea[1] = CRect( 0, 0, 40, 110 ) + CPoint(220-40, 35) ;

		m_GoalinArea[0] = CRect( 0, 0, 15, 80 ) + CPoint(-15, 50);
		m_GoalinArea[1] = CRect( 0, 0, 15, 80 ) + CPoint(220, 50) ;

		m_PKCircle[0] = CRect( 0, 0, 28, 28 ) + CPoint(    29-14, 90-14);
		m_PKCircle[1] = CRect( 0, 0, 28, 28 ) + CPoint(220-29-14, 90-14) ;

		m_CenterCircle = CRect( 0, 0, 50, 50 ) + CPoint( 110-25, 90-25 );

	//	m_FKCircle[0] = CRect( 0, 0, 60, 60 ) + CPoint( 70, 110 );
	//	m_FKCircle[1] = CRect( 0, 0, 60, 60 ) + CPoint(270, 110 );

		m_FreeBall[0] = CRect(      30,     30,     80,     30 );
		m_FreeBall[1] = CRect( 220- 80,     30, 220-30,     30 );
		m_FreeBall[2] = CRect(      30, 180-30,     80, 180-30 );
		m_FreeBall[3] = CRect( 220- 80, 180-30, 220-30, 180-30 );
	}
	else
	if( m_Type == CGround::_5vs5 )
	{
		m_origin.x = (long)(m_center.x - 2.20/2.0*m_screenRatio);
		m_origin.y = (long)(m_center.y - 1.80/2.0*m_screenRatio);

		m_Ground = CRect( 0, 0, 220, 180 );

		m_GoalArea[0] = CRect( 0, 0, 15, 50 ) + CPoint(0, 65);
		m_GoalArea[1] = CRect( 0, 0, 15, 50 ) + CPoint(220-15, 65) ;

		m_PenaltyArea[0] = CRect( 0, 0, 35, 80 ) + CPoint(0, 50);
		m_PenaltyArea[1] = CRect( 0, 0, 35, 80 ) + CPoint(220-35, 50) ;

		m_GoalinArea[0] = CRect( 0, 0, 15, 40 ) + CPoint(-15, 70);
		m_GoalinArea[1] = CRect( 0, 0, 15, 40 ) + CPoint(220, 70) ;

		m_PKCircle[0] = CRect( 0, 0, 28, 28 ) + CPoint(    29-14, 90-14);
		m_PKCircle[1] = CRect( 0, 0, 28, 28 ) + CPoint(220-29-14, 90-14) ;

		m_CenterCircle = CRect( 0, 0, 50, 50 ) + CPoint( 110-25, 90-25 );

	//	m_FKCircle[0] = CRect( 0, 0, 60, 60 ) + CPoint( 70, 110 );
	//	m_FKCircle[1] = CRect( 0, 0, 60, 60 ) + CPoint(270, 110 );

		m_FreeBall[0] = CRect(      30,     30,     80,     30 );
		m_FreeBall[1] = CRect( 220- 80,     30, 220-30,     30 );
		m_FreeBall[2] = CRect(      30, 180-30,     80, 180-30 );
		m_FreeBall[3] = CRect( 220- 80, 180-30, 220-30, 180-30 );
	}
	else
	if( m_Type == CGround::_11vs11 )
	{
		m_origin.x = (long)(m_center.x - 4.00/2.0*m_screenRatio);
		m_origin.y = (long)(m_center.y - 2.80/2.0*m_screenRatio);

		m_Ground = CRect( 0, 0, 400, 280 );

		m_GoalArea[0] = CRect( 0, 0, 24, 80 ) + CPoint(0, 100);
		m_GoalArea[1] = CRect( 0, 0, 24, 80 ) + CPoint(400-24, 100) ;

		m_PenaltyArea[0] = CRect( 0, 0, 60, 120 ) + CPoint(0, 80);
		m_PenaltyArea[1] = CRect( 0, 0, 60, 120 ) + CPoint(400-60, 80) ;

		m_GoalinArea[0] = CRect( 0, 0, 20, 60 ) + CPoint(-20, 110);
		m_GoalinArea[1] = CRect( 0, 0, 20, 60 ) + CPoint(400, 110) ;

		m_PKCircle[0] = CRect( 0, 0, 40, 40 ) + CPoint( 30, 120);
		m_PKCircle[1] = CRect( 0, 0, 40, 40 ) + CPoint(330, 120) ;

		m_CenterCircle = CRect( 0, 0, 75, 75 ) + CPoint( 200-37, 140-37 );

		
		m_FKCircle[0] = CRect( 0, 0, 60, 60 ) + CPoint( 70, 110 );
		m_FKCircle[1] = CRect( 0, 0, 60, 60 ) + CPoint(270, 110 );

		m_FreeBall[0] = CRect(      70,     40,    130,     40 );
		m_FreeBall[1] = CRect( 400-130,     40, 400-70,     40 );
		m_FreeBall[2] = CRect(      70, 280-40,    130, 280-40 );
		m_FreeBall[3] = CRect( 400-130, 280-40, 400-70, 280-40 );
	}
	else
	if( m_Type == CGround::_3vs3 )
	{
		m_origin.x = (long)(m_center.x - 1.50/2.0*m_screenRatio);
		m_origin.y = (long)(m_center.y - (1.30/2.0+0.1)*m_screenRatio);

		m_Ground = CRect( 0, 0, 150, 130 );

		m_GoalArea[0] = CRect( 0, -35, 15, 35 ) + CPoint(0, 65);
		m_GoalArea[1] = CRect( 0, -35, 15, 35 ) + CPoint(150-15, 65) ;

		m_PenaltyArea[0] = m_GoalArea[0];
		m_PenaltyArea[1] = m_GoalArea[1];

		m_GoalinArea[0] = CRect(  0, -20, 10, 20 ) + CPoint(-10, 65);
		m_GoalinArea[1] = CRect(  0, -20, 10, 20 ) + CPoint(150, 65) ;

		m_PKCircle[0] = CRect( 0, 0, 24, 24 ) + CPoint(    8-12, 65-12);
		m_PKCircle[1] = CRect( 0, 0, 24, 24 ) + CPoint(150-8-12, 65-12) ;

		m_CenterCircle = CRect( 0, 0, 40, 40 ) + CPoint( 75-20, 65-20 );

	//	m_FKCircle[0] = CRect( 0, 0, 60, 60 ) + CPoint( 70, 110 );
	//	m_FKCircle[1] = CRect( 0, 0, 60, 60 ) + CPoint(270, 110 );

		//CRect(     17.5,    25,    57.5,    25 );
		m_FreeBall[0] = CRect(      17,     25,     58,     25 );
		m_FreeBall[1] = CRect( 150- 58,     25, 150-17,     25 );
		m_FreeBall[2] = CRect(      17, 130-25,     58, 130-25 );
		m_FreeBall[3] = CRect( 150- 58, 130-25, 150-17, 130-25 );
	}

	ResizeToScreen();
}

void CGround::ResizeToScreen()
{
	ResizeToScreen( m_Ground );

	ResizeToScreen( m_GoalArea[0] );
	ResizeToScreen( m_GoalArea[1] );

	ResizeToScreen( m_PenaltyArea[0] );
	ResizeToScreen( m_PenaltyArea[1] );

	ResizeToScreen( m_GoalinArea[0] );
	ResizeToScreen( m_GoalinArea[1] );

	ResizeToScreen( m_PKCircle[0] );
	ResizeToScreen( m_PKCircle[1] );

	ResizeToScreen( m_CenterCircle );

	
	ResizeToScreen( m_FKCircle[0] );
	ResizeToScreen( m_FKCircle[1] );

	ResizeToScreen( m_FreeBall[0] );
	ResizeToScreen( m_FreeBall[1] );
	ResizeToScreen( m_FreeBall[2] );
	ResizeToScreen( m_FreeBall[3] );
}

void CGround::ResizeToScreen(CRect &rect)
{
	rect.left	= (long)( rect.left   * m_screenRatio/100 );
	rect.right	= (long)( rect.right  * m_screenRatio/100 );
	rect.top	= (long)( rect.top    * m_screenRatio/100 );
	rect.bottom	= (long)( rect.bottom * m_screenRatio/100 );
	rect += m_origin;
}

void CGround::Draw(CDC *pDC, COLORREF color, bool bNULL_BRUSH, bool bGuideLine )
{
	if( bNULL_BRUSH )
		pDC->SelectStockObject( NULL_BRUSH );
	else
		pDC->SelectStockObject( BLACK_BRUSH );

	pDC->SelectStockObject( BLACK_PEN );

	pDC->Rectangle( m_rect );

	if( bGuideLine )
	{
		int r = GetRValue(color)/4;
		int g = GetGValue(color)/4;
		int b = GetBValue(color)/4;

		CPen pen, *pOldPen;
		pen.CreatePen( PS_SOLID, 1, RGB(r,g,b) );
		pOldPen = (CPen*)pDC->SelectObject( &pen );

		for( double x=m_Ground.left ; x<m_Ground.right  ; x+=(10* m_screenRatio/100) )
		{
			pDC->MoveTo( (int)x, m_Ground.top );
			pDC->LineTo( (int)x, m_Ground.bottom );
		}

		for( double y=m_Ground.top  ; y<m_Ground.bottom ; y+=(10* m_screenRatio/100) )
		{
			pDC->MoveTo( m_Ground.left , (int)y );
			pDC->LineTo( m_Ground.right, (int)y );
		}

		pDC->SelectObject( pOldPen );
	}

	CPen pen, *pOldPen;
	pen.CreatePen( PS_SOLID, 1, color );
	pOldPen = (CPen*)pDC->SelectObject( &pen );

	pDC->Rectangle( m_Ground );


//	pDC->Ellipse( m_PKCircle[0] );
//	pDC->Ellipse( m_PKCircle[1] );

	pDC->Rectangle( m_PenaltyArea[0] );
	pDC->Rectangle( m_PenaltyArea[1] );

	pDC->Rectangle( m_GoalArea[0] );
	pDC->Rectangle( m_GoalArea[1] );

	pDC->Rectangle( m_GoalinArea[0] );
	pDC->Rectangle( m_GoalinArea[1] );

//	if( m_Type == GROUND_TYPE_11vs11 )
//	{
//	//	pDC->Ellipse( m_FKCircle[0] );
//	//	pDC->Ellipse( m_FKCircle[1] );
//
//	//	CPen pen, *pOldPen;
//	//	pen.CreatePen( PS_SOLID, 1, color );
//	//	pOldPen = (CPen*)pDC->SelectObject( &pen );
//		
//		pDC->MoveTo( m_CenterCircle.left, m_Ground.top+1 );
//		pDC->LineTo( m_CenterCircle.left, m_Ground.bottom-1 );
//		pDC->MoveTo( m_CenterCircle.right, m_Ground.top+1 );
//		pDC->LineTo( m_CenterCircle.right, m_Ground.bottom-1 );
//
//	//	pDC->SelectObject( pOldPen );
//	}

	pDC->Ellipse( m_CenterCircle );

	pDC->MoveTo( (m_Ground.right+m_Ground.left)/2 , m_Ground.top );
	pDC->LineTo( (m_Ground.right+m_Ground.left)/2 , m_Ground.bottom );

	for( int i=0 ; i<4 ; i++ )
	{
		DrawMark( pDC, m_FreeBall[i].CenterPoint() );
		DrawMark( pDC, m_FreeBall[i].TopLeft() );
		DrawMark( pDC, m_FreeBall[i].BottomRight() );
	}

	DrawMark( pDC, m_PKCircle[0].CenterPoint() );
	DrawMark( pDC, m_PKCircle[1].CenterPoint() );
	DrawMark( pDC, m_FKCircle[0].CenterPoint() );
	DrawMark( pDC, m_FKCircle[1].CenterPoint() );


	{
		// Corner
		long length = (long)( 0.075 * m_screenRatio );
		int mirror_x[2][2] = { -1, -1, +1, +1 };
		int mirror_y[2][2] = { -1, +1, -1, +1 };

		CPoint center = m_Ground.CenterPoint();

		for( int i=0 ; i<2 ; i++ )
			for( int j=0 ; j<2 ; j++ )
			{
				pDC->MoveTo( (int)(center.x + mirror_x[i][j]*( m_Ground.Width()/2 - length) ),
							 (int)(center.y + mirror_y[i][j]*( m_Ground.Height()/2-1 - 0) ) );
				pDC->LineTo( (int)(center.x + mirror_x[i][j]*( m_Ground.Width()/2 - 0) ),
							 (int)(center.y + mirror_y[i][j]*( m_Ground.Height()/2-1 - length) ) );
			}

//		for( int i=0 ; i<2 ; i++ )
//			for( int j=0 ; j<2 ; j++ )
//				for( int y=1 ; y< length ; y++ )
//					for( int x=1 ; x< length-y ; x++ )
//					{
//						// Left Top
//						pDC->SetPixel(	(int)(center.x + mirror_x[i][j]*( m_Ground.Width()/2 - x) ),
//										(int)(center.y + mirror_y[i][j]*( m_Ground.Height()/2 - y) ),
//										RGB(255,255,255) );
//
//					}
	}

	pDC->SelectObject( pOldPen );
}


void CGround::DrawMark(CDC *pDC, CPoint point)
{
	pDC->SetPixel( point.x, point.y, RGB(128,128,128) );
}
/*
CRect CGround::GetGroundRect()
{
	if( m_Type == CGround::_3vs3 )
		return CRect( 0, 0, 150, 130 );

	if( m_Type == CGround::_5vs5 )
		return CRect( 0, 0, 220, 180 );

	if( m_Type == CGround::_11vs11 )
		return CRect( 0, 0, 400, 280 );

	return CRect(0,0,0,0);
}
*/
double CGround::Height()
{
	if( m_Type == CGround::_3vs3 )
		return 1.30;

	if( m_Type == CGround::_5vs5 )
		return 1.80;

	if( m_Type == CGround::_11vs11 )
		return 2.80;

	if( m_Type == CGround::_AndroSot )
		return 1.80;

	return 0;
}

double CGround::Width()
{
	if( m_Type == CGround::_3vs3 )
		return 1.50;

	if( m_Type == CGround::_5vs5 )
		return 2.20;

	if( m_Type == CGround::_11vs11 )
		return 4.00;

	if( m_Type == CGround::_AndroSot )
		return 2.20;

	return 0;
}

double CGround::Goalsize()
{
	if( m_Type == CGround::_3vs3 )
		return 0.4;

	if( m_Type == CGround::_5vs5 )
		return 0.4;

	if( m_Type == CGround::_11vs11 )
		return 0.6;

	if( m_Type == CGround::_AndroSot )
		return 0.8;

	return 0;
}

double CGround::ScreenRatio()
{
	return m_screenRatio;
}

void CGround::ScreenToGround( double &x, double &y )
{
	x -= m_origin.x;
	y -= m_origin.y;

	x /= m_screenRatio;
	y /= m_screenRatio;

	y = Height() - y;
}

void CGround::GroundToScreen( double &x, double &y )
{
	y = Height() - y;

	x *= m_screenRatio;
	y *= m_screenRatio;

	x += m_origin.x;
	y += m_origin.y;
}

void CGround::ScreenToGround( CPointDouble &p )
{
	p.x -= m_origin.x;
	p.y -= m_origin.y;

	p.x = (p.x / m_screenRatio);
	p.y = (p.y / m_screenRatio);

	p.y = Height() - p.y;
}

void CGround::ScreenToGround( double &p )
{
	p = p/m_screenRatio;
}

void CGround::GroundToScreen( CPointDouble &p )
{
	p.y = Height() - p.y;

	p.x = (p.x*m_screenRatio);
	p.y = (p.y*m_screenRatio);

	p.x += m_origin.x;
	p.y += m_origin.y;
}

void CGround::GroundToScreen( double &p )
{
	p = p*m_screenRatio;
}

int CGround::Type()
{
	return m_Type;
}

CPointDouble CGround::Origin()
{
	return m_origin;
}