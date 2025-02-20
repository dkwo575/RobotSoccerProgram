#include "StdAfx.h"
#include "RectMouse.h"
#define _USE_MATH_DEFINES
#include <math.h>

CRectMouse::CRectMouse()
{
	m_title = _T("CMyRect");
	m_color = RGB(128, 128, 128);

	m_bCapture = false;

	m_bCaptureLeft = false;
	m_bCaptureTop = false;
	m_bCaptureRight = false;
	m_bCaptureBottom = false;
}

CRectMouse::~CRectMouse()
{

}

void CRectMouse::Init( CRect rect )
{
	m_left = rect.left;
	m_top = rect.top;
	m_right = rect.right;
	m_bottom = rect.bottom;
}

void CRectMouse::Init(double l, double t, double r, double b)
{
	m_left = l;
	m_top = t;
	m_right = r;
	m_bottom = b;
}

CRect CRectMouse::GetRect()
{
	return CRect((int)m_left, (int)m_top, (int)m_right, (int)m_bottom );
}

void CRectMouse::MouseLDown(CPoint point)
{
//	IDC_ARROW	화살표
//	IDC_WAIT	모래시계
//	IDC_IBEAM	I
//	IDC_CROSS	+
//	IDC_UPARROW
//	IDC_SIZENWSE	\
//	IDC_SIZENESW	/
//	IDC_SIZEWE		-
//	IDC_SIZENS		|
//	IDC_SIZEALL
//	IDC_NO		금지
//	IDC_APPSTARTING	화살표+모래시계
//	IDC_HELP	화살표+?

	m_bCapture = true;
	m_capturePoint = point;

	if( fabs(point.x-m_left) < SAME_POINT )
	{
		if( fabs(point.y-m_top) < SAME_POINT )
		{
			// 왼쪽 & 위쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENWSE ) );
			CaptureLeft();
			CaptureTop();
		}
		else
		if( fabs(point.y-m_bottom) < SAME_POINT )
		{
			// 왼쪽 & 아래쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENESW ) );
			CaptureLeft();
			CaptureBottom();
		}
		else
		if( m_top < point.y && point.y < m_bottom )
		{
			// 왼쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZEWE ) );
			CaptureLeft();
		}
	}
	else
	if( fabs(point.x-m_right) < SAME_POINT )
	{
		if( fabs(point.y-m_top) < SAME_POINT )
		{
			// 오른쪽 & 위쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENESW ) );
			CaptureRight();
			CaptureTop();
		}
		else
		if( fabs(point.y-m_bottom) < SAME_POINT )
		{
			// 오른쪽 & 아래쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENWSE ) );
			CaptureRight();
			CaptureBottom();

		}
		else
		if( m_top < point.y && point.y < m_bottom )
		{
			// 오른쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZEWE ) );
			CaptureRight();
		}
	}
	else
	if( m_left < point.x && point.x < m_right )
	{
		if( fabs(point.y-m_top) < SAME_POINT )
		{
			// 위쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENS ) );
			CaptureTop();
		}
		else
		if( fabs(point.y-m_bottom) < SAME_POINT )
		{
			// 아래쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENS ) );
			CaptureBottom();
		}
		else
		if( m_top < point.y && point.y < m_bottom )
		{
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZEALL ) );
			CaptureLeft();
			CaptureRight();
			CaptureTop();
			CaptureBottom();
		}
		else
		{
			// Nothing
			m_bCapture = false;
		}
	}
}

void CRectMouse::MouseLUp(CPoint point)
{
	ReleaseAll();
	SetCursor( AfxGetApp()->LoadStandardCursor( IDC_ARROW ) );
}

void CRectMouse::MouseMove(CPoint point)
{
	if( m_bCaptureLeft )	m_left   = m_left_bak   + (point.x - m_capturePoint.x);
	if( m_bCaptureTop )		m_top    = m_top_bak    + (point.y - m_capturePoint.y);
	if( m_bCaptureRight )	m_right  = m_right_bak  + (point.x - m_capturePoint.x);
	if( m_bCaptureBottom )	m_bottom = m_bottom_bak + (point.y - m_capturePoint.y);

	SetCursor( AfxGetApp()->LoadStandardCursor( IDC_ARROW ) );

	if( fabs(point.x-m_left) < SAME_POINT )
	{
		if( fabs(point.y-m_top) < SAME_POINT )
		{
			// 왼쪽 & 위쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENWSE ) );
		}
		else
		if( fabs(point.y-m_bottom) < SAME_POINT )
		{
			// 왼쪽 & 아래쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENESW ) );
		}
		else
		if( m_top < point.y && point.y < m_bottom )
		{
			// 왼쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZEWE ) );

		}
	}
	else
	if( fabs(point.x-m_right) < SAME_POINT )
	{
		if( fabs(point.y-m_top) < SAME_POINT )
		{
			// 오른쪽 & 위쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENESW ) );

		}
		else
		if( fabs(point.y-m_bottom) < SAME_POINT )
		{
			// 오른쪽 & 아래쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENWSE ) );

		}
		else
		if( m_top < point.y && point.y < m_bottom )
		{
			// 오른쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZEWE ) );

		}
	}
	else
	if( m_left < point.x && point.x < m_right )
	{
		if( fabs(point.y-m_top) < SAME_POINT )
		{
			// 위쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENS ) );

		}
		else
		if( fabs(point.y-m_bottom) < SAME_POINT )
		{
			// 아래쪽
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZENS ) );

		}
		if( m_top < point.y && point.y < m_bottom )
		{
			SetCursor( AfxGetApp()->LoadStandardCursor( IDC_SIZEALL ) );
		}

	}
}

void CRectMouse::CaptureLeft()
{
	m_bCaptureLeft = true;
	m_left_bak = m_left;
}

void CRectMouse::CaptureTop()
{
	m_bCaptureTop = true;
	m_top_bak = m_top;
}

void CRectMouse::CaptureRight()
{
	m_bCaptureRight = true;
	m_right_bak = m_right;
}

void CRectMouse::CaptureBottom()
{
	m_bCaptureBottom = true;
	m_bottom_bak = m_bottom;
}

void CRectMouse::ReleaseAll()
{
	if( m_left > m_right )
	{
		double tmp = m_left;
		m_left = m_right;
		m_right = tmp;
	}

	if( m_top > m_bottom )
	{
		double tmp = m_top;
		m_top = m_bottom;
		m_bottom = tmp;
	}

	m_bCapture = false;
	m_bCaptureLeft = false;
	m_bCaptureTop = false;
	m_bCaptureRight = false;
	m_bCaptureBottom = false;
}

void CRectMouse::MouseRUp( CPoint point )
{
	ReleaseAll();
	SetCursor( AfxGetApp()->LoadStandardCursor( IDC_ARROW ) );
}

void CRectMouse::MouseRDown( CPoint point )
{
	if( m_bCaptureLeft )	m_left   = m_left_bak  ;
	if( m_bCaptureTop )		m_top    = m_top_bak   ;
	if( m_bCaptureRight )	m_right  = m_right_bak ;
	if( m_bCaptureBottom )	m_bottom = m_bottom_bak;

	ReleaseAll();
	SetCursor( AfxGetApp()->LoadStandardCursor( IDC_ARROW ) );
}

void CRectMouse::SetColor(COLORREF color)
{
	m_color = color;
}

COLORREF CRectMouse::GetColor()
{
	return m_color;
}

CRect CRectMouse::GetZeroOffsetRect()
{
	return CRect( 0, 0, (int)(m_right-m_left), (int)(m_bottom-m_top) );
}

CString CRectMouse::GetTextInfo()
{
	CString tmp;
	tmp.Format(_T("%s\n\r(%d,%d)-(%d,%d)\n\r(%d,%d)"), m_title, (int)m_left, (int)m_top, (int)m_right, (int)m_bottom, (int)m_right-(int)m_left, (int)m_bottom-(int)m_top);

	return tmp;
}

void CRectMouse::SetTitle(CString title)
{
	m_title = title;
}

CString CRectMouse::Title()
{
	return m_title;
}

void CRectMouse::SaveFile(CArchive &ar)
{
	ar << m_left;
	ar << m_top;
	ar << m_right;
	ar << m_bottom;
	
	ar << m_color;
	ar << m_title;

	ar << m_left_bak;
	ar << m_top_bak;
	ar << m_right_bak;
	ar << m_bottom_bak;

}

void CRectMouse::OpenFile(CArchive &ar)
{
	ar >> m_left;
	ar >> m_top;
	ar >> m_right;
	ar >> m_bottom;
	
	ar >> m_color;
	ar >> m_title;

	ar >> m_left_bak;
	ar >> m_top_bak;
	ar >> m_right_bak;
	ar >> m_bottom_bak;
}