#pragma once


#include"PropertyPageRobotSoccer.h"
#include"RobotSoccerCommon.h"

#include "dualslider.h"
#include "dualslider.h"
#include "Revision.h"
#include "RectMouse.h"
#include "afxwin.h"

#include"FontPropertySheet.h"
#include"ObjectPositionInfo.h"

#include"PropertyPageVisionCoreDiagonalPatch.h"
#include"PropertyPageVisionCoreSegmentPatch.h"
#include"PropertyPageVisionCoreBarPatch.h"
// CPropertyPageVision dialog

class CPropertyPageVision : public CPropertyPageRobotSoccer, public CRobotSoccerCommon
{
	DECLARE_DYNAMIC(CPropertyPageVision)

public:
	CString GetActiveVisionCore();
	CObjectPositionInfo GetObjectInfo();

	void SaveFile(CString filename);
	void OpenFile(CString filename);

	void VisionRun(void);
	void GenerateDrawInformation();
	void DrawDisplay(void);
	MouseCapture::Enum DisplayLButtonDown( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayLButtonUp( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayMouseMove( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayRButtonDown( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayRButtonUp( UINT nFlags, CPoint point );

	CPropertyPageVision();
	virtual ~CPropertyPageVision();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_VISION };

protected:
	struct PatchEnable
	{
		bool bDiagonal;
		bool bSegment;
		bool bBar;
	} m_patchEnable;

	CRITICAL_SECTION m_critVision;

	struct S_VISION_TEST
	{
		struct S_EACH_ROBOT
		{
			bool bFound[100];
			int countLoss;
		} robot[11];

		int count;
	} m_VisionTest;

	CPolygonMouse m_FlatPoints;
	CPolygonMouse m_FlatPoints_ball;
	CRevision m_revision;
	CRevision m_revision_ball;
	void DrawFlatImage( CFrameDC *pDC );
	void DrawRevisionImage( CFrameDC *pDC );
	void RevisionUpdate();

	CRectMouse m_rectGroundMappingArea;

	CFrameDC m_dcImage;

	CFrameDC m_dcFlat;
	CFrameDC m_dcFlat_share;

	CFrameDC m_dcRevision;
	CFrameDC m_dcRevision_share;

	CFontPropertySheet m_PropertySheetVisionCore;
	CFontPropertySheet m_PropertySheetVisionCore_invisible;

	CPropertyPageVisionCoreDiagonalPatch m_propVisionCoreDiagonalPatch_draw;
	CVisionCoreDiagonalPatch m_VisionCoreDiagonalPatch_share;
	CVisionCoreDiagonalPatch m_VisionCoreDiagonalPatch_process;

	CPropertyPageVisionCoreSegmentPatch m_propVisionCoreSegmentPatch_draw;
	CVisionCore_Segment m_VisionCoreSegmentPatch_share;
	CVisionCore_Segment m_VisionCoreSegmentPatch_process;

	CPropertyPageVisionCoreBarPatch m_propVisionCoreBarPatch_draw;
	CVisionCore_BarPatch m_VisionCoreBarPatch_share;
	CVisionCore_BarPatch m_VisionCoreBarPatch_process;

	CObjectPositionInfo m_ObjectPositionInfo;

	CFrameDC m_dcTestResult;


	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bShowCameraImage;
	afx_msg void OnBnClickedCheckBackground();
	virtual BOOL OnInitDialog();
	CDualSlider m_sliderRevisionK;
	CDualSlider m_sliderRevisionZoom;
	BOOL m_bFlatImage;
	afx_msg void OnBnClickedCheckFlatImage();
	BOOL m_bRevisionImage;
	afx_msg void OnBnClickedCheckRevisionImage();
	BOOL m_bCameraPause;
	afx_msg void OnBnClickedCheckCameraPause();
	afx_msg void OnPaint();
	BOOL m_bMasking;
	afx_msg void OnBnClickedCheckColorMasking();
	CColorPicker m_colorpickMask;
	CDualSlider m_sliderPatchDirection;
	afx_msg void OnBnClickedOpenVision();
	afx_msg void OnBnClickedSaveVision();
	CString m_strFileName;
	BOOL m_bRobotAll;
	BOOL m_bRobot01;
	BOOL m_bRobot02;
	BOOL m_bRobot03;
	BOOL m_bRobot04;
	BOOL m_bRobot05;
	BOOL m_bRobot06;
	BOOL m_bRobot07;
	BOOL m_bRobot08;
	BOOL m_bRobot09;
	BOOL m_bRobot10;
	BOOL m_bRobot11;
	afx_msg void OnBnClickedCheckRobotAll();
	afx_msg void OnBnClickedCheckRobot01();
	afx_msg void OnBnClickedCheckRobot02();
	afx_msg void OnBnClickedCheckRobot03();
	afx_msg void OnBnClickedCheckRobot04();
	afx_msg void OnBnClickedCheckRobot05();
	afx_msg void OnBnClickedCheckRobot06();
	afx_msg void OnBnClickedCheckRobot07();
	afx_msg void OnBnClickedCheckRobot08();
	afx_msg void OnBnClickedCheckRobot09();
	afx_msg void OnBnClickedCheckRobot10();
	afx_msg void OnBnClickedCheckRobot11();
	afx_msg void OnBnClickedCheckProcessingArea();
	BOOL m_bProcessingArea;
	afx_msg void OnBnClickedCheckFlatImage2();
	BOOL m_bFlatImage_ball;
	afx_msg void OnBnClickedCheckRevisionImage2();
	BOOL m_bRevisionImage_ball;
};
