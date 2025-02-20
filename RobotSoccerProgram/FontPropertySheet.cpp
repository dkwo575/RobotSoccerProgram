// FontPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "FontPropertySheet.h"


// CFontPropertySheet

IMPLEMENT_DYNAMIC(CFontPropertySheet, CPropertySheet)

CFontPropertySheet::CFontPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pDialogFont = new CFont (); 
	ASSERT (m_pDialogFont); 
	m_pDialogFont->CreateFont(13, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
		FF_DONTCARE, _T("tahoma")); 

}

CFontPropertySheet::CFontPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CFontPropertySheet::~CFontPropertySheet()
{
	if (m_pDialogFont != NULL) 
      delete m_pDialogFont; 
}


BEGIN_MESSAGE_MAP(CFontPropertySheet, CPropertySheet)
END_MESSAGE_MAP()


// CFontPropertySheet message handlers


BOOL CFontPropertySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	SendMessageToDescendants (WM_SETFONT, (WPARAM) 
								 m_pDialogFont->GetSafeHandle (), 1, TRUE, FALSE); 
	return bResult;
}
