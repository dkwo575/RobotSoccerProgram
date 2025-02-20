#include "StdAfx.h"
#include "PolygonMouse.h"

#include"RobotSoccerProgram.h"

CPolygonMouse::CPolygonMouse(void)
{
	m_title = _T("CPolygonMouse");
	m_colorLine = RGB(255, 0, 0);
	m_colorText = RGB(0, 255, 128);
	m_colorPoint = RGB(0, 255, 0);

	m_point[0] = CPoint(0,0);
	m_point[1] = CPoint(0,0);
	m_point[2] = CPoint(0,0);
	m_point[3] = CPoint(0,0);

	m_bCapture[0] = false;
	m_bCapture[1] = false;
	m_bCapture[2] = false;
	m_bCapture[3] = false;

	m_width = 640;
	m_height = 480;
}


CPolygonMouse::~CPolygonMouse(void)
{
}


void CPolygonMouse::Init(int l, int t, int r, int b)
{
	m_point[0] = CPoint( l, t );
	m_point[1] = CPoint( r, t );
	m_point[2] = CPoint( r, b );
	m_point[3] = CPoint( l, b );
}


bool CPolygonMouse::MouseLDown(CPoint point)
{
//	IDC_ARROW	arrow
//	IDC_WAIT	wait
//	IDC_IBEAM	I
//	IDC_CROSS	+
//	IDC_UPARROW
//	IDC_SIZENWSE	\
//	IDC_SIZENESW	/
//	IDC_SIZEWE		-
//	IDC_SIZENS		|
//	IDC_SIZEALL
//	IDC_NO		±ÝÁö
//	IDC_APPSTARTING	arrow+wait
//	IDC_HELP	arrow+?

	m_capturePoint = point;

	for( int i=0 ; i<4 ; i++ )
		if( AboutZero( point - m_point[i]) )
		{
			m_bCapture[i] = true;
			m_backup[i] = m_point[i];

			HCURSOR hCursor;
			hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION2 );
			SetCursor(hCursor);

			return true;
		}

		CPoint center = m_point[0]+m_point[1]+m_point[2]+m_point[3];
		center.x /= 4;
		center.y /= 4;
		if( AboutZero( point - center) )
		{
			CPoint imsi= m_point[3];
			m_point[3] = m_point[2];
			m_point[2] = m_point[1];
			m_point[1] = m_point[0];
			m_point[0] = imsi;

			HCURSOR hCursor;
			hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION4 );
			SetCursor(hCursor);

			return true;
		}

	return false;
}

void CPolygonMouse::MouseLUp(CPoint point)
{
	m_bCapture[0] = false;
	m_bCapture[1] = false;
	m_bCapture[2] = false;
	m_bCapture[3] = false;
	
	m_capturePoint = point;
	
	for( int i=0 ; i<4 ; i++ )
		if( AboutZero( point - m_point[i]) )
		{
			HCURSOR hCursor;
			hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION1 );
			SetCursor(hCursor);
			
			break;
		}
		
		CPoint center = m_point[0]+m_point[1]+m_point[2]+m_point[3];
		center.x /= 4;
		center.y /= 4;
		if( AboutZero( point - center) )
		{

			HCURSOR hCursor;
			hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION3 );
			SetCursor(hCursor);
			
		}
}

void CPolygonMouse::MouseMove(CPoint point)
{
	bool bCheck = true;
	for( int i=0 ; i<4 ; i++)
	{
		if( m_bCapture[i] )
		{
			m_point[i] = m_backup[i]   + (point - m_capturePoint);

			m_point[i].x = max( m_point[i].x, 0L );
			m_point[i].y = max( m_point[i].y, 0L );
			m_point[i].x = min( m_point[i].x, m_width );
			m_point[i].y = min( m_point[i].y, m_height );

			HCURSOR hCursor;
			hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION2 );
			SetCursor(hCursor);

			return;
		}
	}
	
	{
		for( int i=0 ; i<4 ; i++)
			if( AboutZero( point - m_point[i] ) )
			{
				HCURSOR hCursor;
				hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION1 );
				SetCursor(hCursor);
				bCheck = false;
			}

		CPoint center = m_point[0]+m_point[1]+m_point[2]+m_point[3];
		center.x /= 4;
		center.y /= 4;
		if( AboutZero( point - center) )
		{
			HCURSOR hCursor;
			hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION3 );
			SetCursor(hCursor);

			return;
		}
	}

	if( bCheck )
	{
		HCURSOR hCursor;
		hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION0 );
		SetCursor(hCursor);
	}
}

void CPolygonMouse::MouseRUp( CPoint point )
{
	m_capturePoint = point;
	
	for( int i=0 ; i<4 ; i++ )
		if( AboutZero( point - m_point[i]) )
		{
			HCURSOR hCursor;
			hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION1 );
			SetCursor(hCursor);
			
			break;
		}
		
		CPoint center = m_point[0]+m_point[1]+m_point[2]+m_point[3];
		center.x /= 4;
		center.y /= 4;
		if( AboutZero( point - center) )
		{
			
			HCURSOR hCursor;
			hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION3 );
			SetCursor(hCursor);
			
		}
}

void CPolygonMouse::MouseRDown( CPoint point )
{
	for( int i=0 ; i<4 ; i++)
		if( m_bCapture[i] )
		{
			m_bCapture[i] = false;
			m_point[i] = m_backup[i];
		}

		m_capturePoint = point;
		
	for( int i=0 ; i<4 ; i++ )
		if( AboutZero( point - m_point[i]) )
		{
			HCURSOR hCursor;
			hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION1 );
			SetCursor(hCursor);
			
			break;
		}
		
		CPoint center = m_point[0]+m_point[1]+m_point[2]+m_point[3];
		center.x /= 4;
		center.y /= 4;
		if( AboutZero( point - center) )
		{
			
			HCURSOR hCursor;
			hCursor = AfxGetApp()->LoadCursor( IDC_CURSOR_REVISION3 );
			SetCursor(hCursor);
			
	}
}

COLORREF CPolygonMouse::ColorText(){	return m_colorText; }
COLORREF CPolygonMouse::ColorLine(){	return m_colorLine; }
COLORREF CPolygonMouse::ColorPoint(){return m_colorPoint;}
//COLORREF CPolygonMouse::SetColorText(COLORREF color){	m_colorText = color; }
//COLORREF CPolygonMouse::SetColorLine(COLORREF color){	m_colorLine = color; }
//COLORREF CPolygonMouse::SetColorPoint(COLORREF color{	m_colorPoint = color;}

void CPolygonMouse::SetTitle(CString title)
{
	m_title = title;
}

bool CPolygonMouse::AboutZero(CPoint point)
{
//	if( point.x <= 0 && point.y <= 0 
//	 && abs(point.x) < REVISION_SAME_POINT && abs(point.y) < REVISION_SAME_POINT )
//		return true;

	double dx = point.x;
	double dy = point.y;

	if( ( dx * dx + dy * dy ) < REVISION_SAME_POINT*REVISION_SAME_POINT )
		return true;

	return false;
}

CPoint CPolygonMouse::GetPoint(int id)
{
	return m_point[id];
}

CPoint CPolygonMouse::GetTextPos(int id)
{
	CPoint center = m_point[0]+m_point[1]+m_point[2]+m_point[3];
	center.x /= 4;
	center.y /= 4;

	double a = 0.8;

	CPoint result;
	result.x = (long)(a * m_point[id].x + (1-a) * center.x)-30;
	result.y = (long)(a * m_point[id].y + (1-a) * center.y)-10;

	return result;
}

CString CPolygonMouse::GetTextInfo(int id)
{
	CString tmp = _T("");

	if( id == 0 )
		tmp.Format(_T("Left-Top"));

	if( id == 2 )
		tmp.Format(_T("Right-Bottom"));
	

	return tmp;
}

CPoint CPolygonMouse::TitlePos()
{
	CPoint center = m_point[0]+m_point[1]+m_point[2]+m_point[3];
	center.x /= 4;
	center.y /= 4;

	center.x -= 30;
	center.y -= 10;

	return center;
}

CString CPolygonMouse::Title()
{
	return m_title;
}

void CPolygonMouse::OpenFile(CArchive &ar)
{
	ar >> m_colorLine;
	ar >> m_colorPoint;
	ar >> m_colorText;
	ar >> m_title;

	ar >> m_point[0];
	ar >> m_point[1];
	ar >> m_point[2];
	ar >> m_point[3];
	ar >> m_point[4];
}

void CPolygonMouse::SaveFile(CArchive &ar)
{
	ar << m_colorLine;
	ar << m_colorPoint;
	ar << m_colorText;
	ar << m_title;

	ar << m_point[0];
	ar << m_point[1];
	ar << m_point[2];
	ar << m_point[3];
	ar << m_point[4];
}

