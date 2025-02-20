#pragma once
#include "dualslider.h"
#include "VelocityParameter.h"


// CVelocityParameterDlg dialog

class CVelocityParameterDlg : public CDialog
{
	DECLARE_DYNAMIC(CVelocityParameterDlg)

public:
	void Hide();
	void Show();
	bool IsShow();
	bool m_bDialogShow;

	bool m_bActive;
	CVelocityParameter m_VelocityParameter;
	CVelocityParameter GetParameters();
	void SetParameters( CVelocityParameter param );
	void UpdateSlider();


	CVelocityParameterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVelocityParameterDlg();

// Dialog Data
	enum { IDD = IDD_VELOCITY_PARAMETER1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDualSlider m_sliderAcceleration;
	virtual BOOL OnInitDialog();
	CDualSlider m_sliderDeceleration;
	CDualSlider m_sliderCentripetalAcceleration;
	CDualSlider m_sliderMaxAccelerationLimit;
	CDualSlider m_sliderMaxVelocityLimit;
	CDualSlider m_sliderPathErrorGain;
	CDualSlider m_sliderAngularVelocityErrorPGain;
	CDualSlider m_sliderAngularVelocityErrorDGain;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
