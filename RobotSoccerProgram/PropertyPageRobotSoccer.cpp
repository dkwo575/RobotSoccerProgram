// PropertyPageRobotSoccer.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "PropertyPageRobotSoccer.h"
#include "afxdialogex.h"


// CPropertyPageRobotSoccer dialog

IMPLEMENT_DYNAMIC(CPropertyPageRobotSoccer, CPropertyPage)

CPropertyPageRobotSoccer::CPropertyPageRobotSoccer()
	: CPropertyPage(CPropertyPageRobotSoccer::IDD)
{
	m_bActive = false;
	m_pDC = NULL;
}

CPropertyPageRobotSoccer::CPropertyPageRobotSoccer( UINT enumIDD )
		: CPropertyPage(enumIDD)
{
	InitializeCriticalSection(&m_critProp);

	m_bActive = false;
	m_pDC = NULL;

	m_bLButton = false;
	m_bRButton = false;

	m_pDialogFont = new CFont (); 
	ASSERT (m_pDialogFont); 
	m_pDialogFont->CreateFont(13, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
		FF_DONTCARE, _T("Tahoma")); 
}


CPropertyPageRobotSoccer::~CPropertyPageRobotSoccer()
{
	if (m_pDialogFont != NULL) 
      delete m_pDialogFont; 

	DeleteCriticalSection(&m_critProp);
}

void CPropertyPageRobotSoccer::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropertyPageRobotSoccer, CPropertyPage)
END_MESSAGE_MAP()


// CPropertyPageRobotSoccer message handlers


BOOL CPropertyPageRobotSoccer::OnSetActive()
{
	SendMessageToDescendants (WM_SETFONT, (WPARAM) 
								m_pDialogFont->GetSafeHandle (), 1, TRUE, FALSE); 
	m_bActive = true;

	return CPropertyPage::OnSetActive();
}


BOOL CPropertyPageRobotSoccer::OnKillActive()
{
	m_bActive = false;

	return CPropertyPage::OnKillActive();
}


BOOL CPropertyPageRobotSoccer::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


bool CPropertyPageRobotSoccer::IsActive(void)
{
	bool bActive;

	EnterCriticalSection(&m_critProp);

	bActive = m_bActive;

	LeaveCriticalSection(&m_critProp);

	return m_bActive;;
}


void CPropertyPageRobotSoccer::SetDisplayDC(CFrameDC* pDC)
{
	m_pDC = pDC;
}

void CPropertyPageRobotSoccer::DrawDisplay(void)
{
	if( m_pDC == NULL )
		return;

	m_pDC->FillSolidRect(0, 0, m_pDC->Width(), m_pDC->Height(), RGB(0,0,0) );
	m_pDC->SetBkMode( OPAQUE );
	m_pDC->SetTextColor( RGB(255,0,0) );
	m_pDC->TextOut( m_pDC->Width()/2-100, m_pDC->Height()/2-20,
					_T(" CPropertyPageRobotSoccer "));
}

MouseCapture::Enum CPropertyPageRobotSoccer::DisplayRButtonDown( UINT nFlags, CPoint point )
{
	return MouseCapture::NOTHING;
}

MouseCapture::Enum CPropertyPageRobotSoccer::DisplayRButtonUp( UINT nFlags, CPoint point )
{
	return MouseCapture::NOTHING;
}

MouseCapture::Enum CPropertyPageRobotSoccer::DisplayLButtonDown( UINT nFlags, CPoint point )
{
	return MouseCapture::NOTHING;
}

MouseCapture::Enum CPropertyPageRobotSoccer::DisplayLButtonUp( UINT nFlags, CPoint point )
{
	return MouseCapture::NOTHING;
}

MouseCapture::Enum CPropertyPageRobotSoccer::DisplayMouseMove( UINT nFlags, CPoint point )
{
	return MouseCapture::NOTHING;
}

MouseCapture::Enum CPropertyPageRobotSoccer::DisplayMouseWheel( UINT nFlags, short zDelta, CPoint point )
{
	return MouseCapture::NOTHING;
}

void CPropertyPageRobotSoccer::MoveDlgItem( int nID, CPoint posMove )
{
	CRect rect;
	GetDlgItem(nID)->GetWindowRect( rect );
	ScreenToClient(rect);
	rect += posMove;
	GetDlgItem(nID)->SetWindowPos( NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER | SWP_NOACTIVATE);
}

void CPropertyPageRobotSoccer::ChangeSizeDlgItem( int nID, CPoint size )
{
	CRect rect;
	GetDlgItem(nID)->GetWindowRect( rect );
	ScreenToClient(rect);
	rect.right  += size.x;
	rect.bottom += size.y;
	GetDlgItem(nID)->SetWindowPos( NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER | SWP_NOACTIVATE);
}
