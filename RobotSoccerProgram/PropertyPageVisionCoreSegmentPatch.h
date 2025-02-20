#pragma once

#include"PropertyPageRobotSoccer.h"
#include"VisionCore_Segment.h"
#include "colorpicker.h"
#include "dualslider.h"
#include "FrameDC.h"
#include "afxwin.h"

// CPropertyPageVisionCoreSegmentPatch dialog

class CPropertyPageVisionCoreSegmentPatch : public CPropertyPageRobotSoccer, public CVisionCore_Segment
{
	DECLARE_DYNAMIC(CPropertyPageVisionCoreSegmentPatch)

public:
	void OpenFile(CArchive &ar);
	void SaveFile(CArchive &ar);

	void Display_RobotSegment( BOOL bShowCameraImage, BOOL bMasking, COLORREF colorMask );

	void VisionRun();
	void DrawDisplay( BOOL bMasking, COLORREF colorMask );

	CPropertyPageVisionCoreSegmentPatch();
	virtual ~CPropertyPageVisionCoreSegmentPatch();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_VISION_SEGMENT_PATCH };

protected:
	CFrameDC m_dcRobotSegment;
	int m_selectSegmentID;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CColorPicker m_colorpickScanInterval;
	CColorPicker m_colorpickBall;
	CColorPicker m_colorpickOpponent;
	CColorPicker m_colorpickTeamSegment;
	CColorPicker m_colorpickAssistant1;
	CColorPicker m_colorpickAssistant2;
	CColorPicker m_colorpickTeamAssistantDistance;
	BOOL m_bScanningInterval;
	BOOL m_bBall;
	BOOL m_bOpponent;
	BOOL m_bTeamSegment;
	BOOL m_bAssistant1;
	BOOL m_bAssistant2;
	BOOL m_bTeamAssistantDistance;
	CDualSlider m_sliderScanInterval;
	CDualSlider m_sliderSizeBall;
	CDualSlider m_sliderSizeOpponent;
	CDualSlider m_sliderSizeTeamSegment;
	CDualSlider m_sliderSizeAssistant;
	CDualSlider m_sliderTeamAssistantDistance;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCheckScanningInterval();
	afx_msg void OnBnClickedCheckBall();
	afx_msg void OnBnClickedCheckOpponent();
	afx_msg void OnBnClickedCheckTeamSegment();
	afx_msg void OnBnClickedCheckAssistant1();
	afx_msg void OnBnClickedCheckAssistant2();
	afx_msg void OnBnClickedCheckTeamAssistantDistance();
	BOOL m_bDrawTeamWithoutSegment;
	afx_msg void OnBnClickedCheckDrawTeamWithoutSegment();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCheckEditSegmentInformation();
	BOOL m_bEditSegmentInformation;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCheckEditSegmentPosition();
	BOOL m_bEditSegmentPosition;
	CComboBox m_comboRobotID;
	afx_msg void OnSelchangeComboRobotId();
	CColorPicker m_colorpickSegmentMarker;
	CDualSlider m_sliderSegmentThreshold;
};
