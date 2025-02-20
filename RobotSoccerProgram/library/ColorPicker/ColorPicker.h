#pragma once

#include<afxwin.h>

// Written by Chris Maunder (Chris.Maunder@cbr.clw.csiro.au)
// Extended by Alexander Bischofberger (bischofb@informatik.tu-muenchen.de)
// Copyright (c) 1998.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage whatsoever.
// It's free - so you get what you pay for.


#include "ColorPopup.h"

/////////////////////////////////////////////////////////////////////////////
// CColorPicker window

void AFXAPI DDX_ColorPicker(CDataExchange *pDX, int nIDC, COLORREF& crColor);

/////////////////////////////////////////////////////////////////////////////
// CColorPicker window

#define CP_MODE_TEXT 1  // edit text Color
#define CP_MODE_BK   2  // edit background Color (default)

class CColorPicker :
	public CButton
{
// Construction
public:
    CColorPicker();
    DECLARE_DYNCREATE(CColorPicker);

// Attributes
public:
	CColorPicker& operator =(CColorPicker& c);

    COLORREF GetColor();
    void     SetColor(COLORREF crColor); 

    void     SetDefaultText(LPCTSTR szDefaultText);
    void     SetCustomText(LPCTSTR szCustomText);

    void     SetTrackSelection(BOOL bTracking = TRUE)  { m_bTrackSelection = bTracking; }
    BOOL     GetTrackSelection()                       { return m_bTrackSelection; }

    void     SetSelectionMode(UINT nMode)              { m_nSelectionMode = nMode; }
    UINT     GetSelectionMode()                        { return m_nSelectionMode; };

    void     SetBkColor(COLORREF crColorBk);
    COLORREF GetBkColor()                             { return m_crColorBk; }
    
    void     SetTextColor(COLORREF crColorText);
    COLORREF GetTextColor()                           { return m_crColorText;}

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CColorPicker)
    public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
	void SetEditable( BOOL state );
    virtual ~CColorPicker();

protected:
    void SetWindowSize();

// protected attributes
protected:
	CColorPopup *m_ColorPopup;
	BOOL     m_bEditable;              // shchoi : for show only option.
    BOOL     m_bActive,                // Is the dropdown active?
             m_bTrackSelection;        // track Color changes?
    COLORREF m_crColorBk;
    COLORREF m_crColorText;
    UINT     m_nSelectionMode;
    CRect    m_ArrowRect;
    CString  m_strDefaultText;
    CString  m_strCustomText;

    // Generated message map functions
protected:
    //{{AFX_MSG(CColorPicker)
    afx_msg BOOL OnClicked();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
    afx_msg LONG OnSelEndCancel(UINT lParam, LONG wParam);
    afx_msg LONG OnSelChange(UINT lParam, LONG wParam);

    DECLARE_MESSAGE_MAP()
};

