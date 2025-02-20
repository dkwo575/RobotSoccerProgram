#pragma once



// CFontPropertySheet

class CFontPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CFontPropertySheet)

protected:
	CFont* m_pDialogFont;

public:
	CFontPropertySheet(UINT nIDCaption=IDS_PROPERTY_SHEET_DEFAULT_NAME, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CFontPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CFontPropertySheet();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};


