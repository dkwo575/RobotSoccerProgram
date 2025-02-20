#pragma once

#include"PropertyPageRobotSoccer.h"

#include "dualslider.h"
#include"ColorPicker.h"
#include"FrameDC.h"
#include"VisionCoreDiagonalPatch.h"

// CPropertyPageVisionCoreDiagonalPatch dialog

class CPropertyPageVisionCoreDiagonalPatch : public CPropertyPageRobotSoccer, public CVisionCoreDiagonalPatch
{
	DECLARE_DYNAMIC(CPropertyPageVisionCoreDiagonalPatch)

public:
	void OpenFile(CArchive &ar);
	void SaveFile(CArchive &ar);

	CPropertyPageVisionCoreDiagonalPatch();
	virtual ~CPropertyPageVisionCoreDiagonalPatch();

	void Display_RobotSegment(BOOL bShowCameraImage, BOOL bMasking, COLORREF colorMask);
	void DrawIDSelect();
	void DrawDisplay(BOOL bMasking, COLORREF colorMask);

// Dialog Data
	enum { IDD = IDD_PROPPAGE_VISION_DIAGONAL_PATCH };

protected:
	int m_sizePatchDC;
	CFrameDC m_dcIDSelect[5];
	CFrameDC m_dcRobotSegment;
	

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int prevSeg;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CColorPicker m_colorpickScanInterval;
	CColorPicker m_colorpickBall;
	CColorPicker m_colorpickOpponent;
	CColorPicker m_colorpickTeam;
	CColorPicker m_bTeamSegment;
	CColorPicker m_colorpickID1;
	CColorPicker m_colorpickID2;
	CColorPicker m_colorpickID3;
	CColorPicker m_colorpickTeamIDDistance;
	CColorPicker m_colorpickTeamSegment;
	BOOL m_bScanningInterval;
	BOOL m_bBall;
	BOOL m_bOpponent;
	BOOL m_bTeam;
	BOOL m_bID1;
	BOOL m_bID2;
	BOOL m_bID3;
	BOOL m_bTeamIDDistance;
	CDualSlider m_sliderScanInterval;
	CDualSlider m_sliderSizeBall;
	CDualSlider m_sliderSizeOpponent;
	CDualSlider m_sliderSizeTeam;
	CDualSlider m_sliderSizeTeamIDDistance;
	CDualSlider m_sliderSizeID;
	afx_msg void OnBnClickedCheckEditSegmentInformation();
	afx_msg void OnBnClickedCheckEditSegmentPosition();
	afx_msg void OnSelchangeComboRobotId();
	afx_msg void OnBnClickedCheckScanningInterval();
	afx_msg void OnBnClickedCheckBall();
	afx_msg void OnBnClickedCheckOpponents();
	afx_msg void OnBnClickedCheckTeam();
	afx_msg void OnBnClickedCheckId1();
	afx_msg void OnBnClickedCheckId2();
	afx_msg void OnBnClickedCheckId3();
	afx_msg void OnBnClickedCheckTeamIdDistance();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CComboBox m_comboRobotID;
	BOOL m_bEditSegmentPosition;
	BOOL m_bEditSegmentInformation;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
