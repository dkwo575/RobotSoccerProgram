#pragma once


#include"FrameDC.h"

// CPropertyPageRobotSoccer dialog

namespace MouseCapture 
{
	enum Enum
	{
		NOTHING,
		SET,
		RELEASE
	};
}

class CPropertyPageRobotSoccer : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyPageRobotSoccer)

public:
	CPropertyPageRobotSoccer();
	CPropertyPageRobotSoccer( UINT enumIDD );
	virtual ~CPropertyPageRobotSoccer();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_ROBOTSOCCER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnInitDialog();
protected:
	void MoveDlgItem( int nID, CPoint posMove );
	void ChangeSizeDlgItem( int nID, CPoint size );

	CRITICAL_SECTION m_critProp;

	bool m_bLButton;
	bool m_bRButton;
	CPoint m_mouseDownPoint;
	CPoint m_mouseMovePoint;
	CPoint m_mouseUpPoint;

	CFont* m_pDialogFont;

	CFrameDC* m_pDC;

	bool m_bActive;
public:
	bool IsActive(void);
	void SetDisplayDC(CFrameDC* pDC);
	
	virtual void DrawDisplay(void);

	virtual MouseCapture::Enum DisplayRButtonDown( UINT nFlags, CPoint point );
	virtual MouseCapture::Enum DisplayRButtonUp( UINT nFlags, CPoint point );
	virtual MouseCapture::Enum DisplayLButtonDown( UINT nFlags, CPoint point );
	virtual MouseCapture::Enum DisplayLButtonUp( UINT nFlags, CPoint point );
	virtual MouseCapture::Enum DisplayMouseMove( UINT nFlags, CPoint point );
	virtual MouseCapture::Enum DisplayMouseWheel( UINT nFlags, short zDelta, CPoint point );
};
