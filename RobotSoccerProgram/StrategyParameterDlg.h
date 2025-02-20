#pragma once

#include"StrategyParameter.h"
#include "dualslider.h"
// CStrategyParameterDlg dialog

class CStrategyParameterDlg : public CDialog
{
	DECLARE_DYNAMIC(CStrategyParameterDlg)

public:
	void Hide();
	void Show();
	bool IsShow();
	bool m_bDialogShow;


	bool m_bActive;
	CStrategyParameter m_StrategyParameter;
	void SetParameters( CStrategyParameter param );
	void UpdateSlider();
	CStrategyParameter GetParameters();

	CStrategyParameterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStrategyParameterDlg();

// Dialog Data
	enum { IDD = IDD_STRATEGY_PARAMETER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDualSlider m_sliderParam01;
	CDualSlider m_sliderParam02;
	CDualSlider m_sliderParam03;
	CDualSlider m_sliderParam04;
	CDualSlider m_sliderParam05;
	CDualSlider m_sliderParam06;
	CDualSlider m_sliderParam07;
	CDualSlider m_sliderParam08;
	CDualSlider m_sliderParam09;
	CDualSlider m_sliderParam10;
	CDualSlider m_sliderParam11;
	CDualSlider m_sliderParam12;
	CDualSlider m_sliderParam13;
	CDualSlider m_sliderParam14;
	CDualSlider m_sliderParam15;
	CDualSlider m_sliderParam16;
	CDualSlider m_sliderParam17;
	CDualSlider m_sliderParam18;
	CDualSlider m_sliderParam19;
	CDualSlider m_sliderParam20;
	CDualSlider m_sliderParam21;
	CDualSlider m_sliderParam22;
	CDualSlider m_sliderParam23;
	CDualSlider m_sliderParam24;
	CDualSlider m_sliderParam25;
	CDualSlider m_sliderParam26;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
