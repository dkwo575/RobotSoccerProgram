#pragma once

#include"VelocityParameter2.h"
#include "dualslider.h"
#include"FrameDC.h"

// CVelocityParameterDlg2 dialog

class CVelocityParameterDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CVelocityParameterDlg2)

public:
	void DisplayVelocityK();

	void Hide();
	void Show();
	bool IsShow();
	bool m_bDialogShow;

	bool m_bActive;
	void UpdateSlider( BOOL bUpdate );

	CVelocityParameter2 m_VelocityParameter2[5];
	CVelocityParameter2 m_VelocityParameter2_backup[5];
	void SetParameters( int p, CVelocityParameter2 param );
	CVelocityParameter2 GetParameters( int p );


	CVelocityParameterDlg2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVelocityParameterDlg2();

// Dialog Data
	enum { IDD = IDD_VELOCITY_PARAMETER2_DIALOG };

protected:
	CRITICAL_SECTION m_critVisionPrarameter2;

	CFrameDC m_displayVc;
	CFrameDC m_displayVmax;
	CFrameDC m_displaydV;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CDualSlider m_sliderParam1;
	CDualSlider m_sliderParam2;
	CDualSlider m_sliderParam3;
	CDualSlider m_sliderParam4;
	CDualSlider m_sliderParam5;
	CDualSlider m_sliderParam6;
	CDualSlider m_sliderParam7;
	CDualSlider m_sliderParam8;
	CDualSlider m_sliderParam9;
	BOOL m_radioParam;
	afx_msg void OnBnClickedRadioParameter1();
	afx_msg void OnBnClickedRadioParameter2();
	afx_msg void OnBnClickedRadioParameter3();
	afx_msg void OnBnClickedRadioParameter4();
	afx_msg void OnBnClickedRadioParameter5();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedSaveV2File();
	afx_msg void OnBnClickedOpenV2File();
};
