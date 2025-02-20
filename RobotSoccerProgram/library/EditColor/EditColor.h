#pragma once

#include<afxwin.h>

class CEditColor : public CEdit
{
// Construction
public:
	CEditColor();
	void SetColor( COLORREF colorText, COLORREF colorBK );
	void SetColorText( COLORREF color );
	void SetColorBK( COLORREF color );

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditColor)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditColor();

	// Generated message map functions
protected:
	COLORREF m_colorBK;
	COLORREF m_colorText;
	CBrush m_brush;

	//{{AFX_MSG(CEditColor)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

