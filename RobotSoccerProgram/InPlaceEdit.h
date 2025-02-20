#pragma once

#include<afxwin.h>

class CInPlaceEdit :
	public CEdit
{
public:
    CInPlaceEdit(int iItem, int iSubItem, CString sInitText);
	CInPlaceEdit(void);
	~CInPlaceEdit(void);

	void CalculateSize();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	int m_iItem;
	int m_iSubItem;
	CString m_sInitText;
	BOOL    m_bESC;         // To indicate whether ESC key was pressed
};

