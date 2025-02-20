#pragma once

#include"PropertyPageRobotSoccer.h"
#include"RobotSoccerCommon.h"

// CPropertyPageColorSetting dialog

#include"ColorPicker.h"
#include"EditColor.h"
#include"FrameDC.h"
#include"DualSlider.h"
#include "afxwin.h"

#include"ColorSampleData.h"

#include"cv.h"

#include<vector>

#define ZOOM_K 6
#define ZOOM_X 180
#define ZOOM_Y 180

#define ZOOM_INFO_X (ZOOM_X-1)
#define ZOOM_INFO_Y 30

#define SAMPLE_INFO_MARGIN_LEFT   4
#define SAMPLE_INFO_MARGIN_RIGHT  4
#define SAMPLE_INFO_MARGIN_TOP    4
#define SAMPLE_INFO_MARGIN_BOTTOM 4

#define NORMALIZED_RGB_DRAW_SIZE 180
#define NORMALIZED_RGB_DATA_SIZE 180

#define MAX_KEY_SAMPLE_N 10

class CPropertyPageColorSetting : public CPropertyPageRobotSoccer, public CRobotSoccerCommon
{
	DECLARE_DYNAMIC(CPropertyPageColorSetting)

public:
	CPropertyPageColorSetting();
	virtual ~CPropertyPageColorSetting();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void SetActiveVisionCore( CString strActiveVisionCore );

	void OpenFile(CString filename);
	void SaveFile(CString filename);

	void GenerateMaskInformation();
	void DrawDisplay(void);
	MouseCapture::Enum DisplayLButtonDown( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayMouseWheel( UINT nFlags, short zDelta, CPoint point );

protected:
	// shared information
	CRITICAL_SECTION m_critColorSetting;
	std::vector<CPoint> m_vecMaskInformation_share[8];

	// Zoom
	CFrameDC m_dcZoom;
	void ZoomInit();
	void ZoomCaptureAgain();

	CPoint m_mouseZoomPos;
	COLORREF m_zoomImage[ZOOM_X/ZOOM_K][ZOOM_Y/ZOOM_K];
	bool m_zoomMark[ZOOM_X/ZOOM_K][ZOOM_Y/ZOOM_K];

	bool m_bZoomClick;
	CPoint m_pointZoomClick;
	int m_zoomMarkedPixels;
	double m_ZoomPixelClickRecursiveK;

	void ZoomDraw();
	void ZoomPixelDraw( int i, int j );
	void ZoomMouseDraw();
	void ZoomPixelClickRecursive(CPoint point, COLORREF color);
	void ZoomPixelClick( CPoint point, bool mask );
	CPoint PointToZoomArray(CPoint point);

	CFrameDC m_dcZoomInfo;
	CString m_textZoomInfo;
	void ZoomInfoDraw();
	void ZoomInfoDraw( CString text );


	// Sampling Data
	CColorPicker*	m_pcolorpickSample[8];
	BOOL m_sampleMask[8];
	CColorSampleData m_sampleData[8];

	int m_radioSample;
	void SelectSample(int p);
	void SetfocusEditSample();
	void OnBnClickedCheckSample( int sampleID, BOOL checkSample );
	void OnChangeEditSample( int sampleID );

	CFrameDC m_dcSampleInfo;
	void SampleInfoDraw();
	int PointToPatchParameter( CPoint point );

	CFrameDC m_dcNormalizedRGB;
	void InitializeNormalizedRGB();
	void NormalizedRGBDraw( bool bBitBlt = true );
	void NormalizedRGBDrawPoint( CPoint point );

	bool m_NormalizedRGBMark[8][NORMALIZED_RGB_DATA_SIZE][NORMALIZED_RGB_DATA_SIZE];
	COLORREF m_NormalizedRGBColor[NORMALIZED_RGB_DATA_SIZE][NORMALIZED_RGB_DATA_SIZE];
	bool m_bNormalizedRGBColor[NORMALIZED_RGB_DATA_SIZE][NORMALIZED_RGB_DATA_SIZE];

	cv::Mat m_matColor;		// Nomalized RGB <-> RGB º¯È¯¿ë Matrix
	cv::Mat m_matColori;
	cv::Mat m_matXY;
	cv::Mat m_matRGB;


	// Mouse
	bool m_bMouseLButtonDown;
	bool m_bMouseRButtonDown;


	// Patch
	CColorPicker*	m_pcolorpickPatch[8];
	unsigned char m_patchMask;
	int m_radioPatch;
	bool m_bGeneratePatchColor;

	void SelectPatch(int p);
	void SetfocusEditPatch();
	void OnBnClickedCheckPatch( int patchID, BOOL checkPatch );

	CPoint m_mouseNRGBPos;
	bool m_bNormalizedRGBClick;
	bool m_bMouseNormalizedRGB;
	CPoint PointToNormalizedRGB(CPoint point);
	void NormalizedRGBClick(CPoint point, bool mask);



public:
	virtual BOOL OnInitDialog();
	CDualSlider m_sliderZoomDBClickK;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedClearSampleSelection();
	afx_msg void OnBnClickedZoomCaptureAgain();
	afx_msg void OnPaint();
	BOOL m_bShowCameraImage;
    afx_msg LONG OnColorPickerChanged(UINT lParam, LONG wParam);
	/*afx_msg LRESULT OnColorPickerChanged(WPARAM wParam, LPARAM lParam);*/

	

	CColorPicker m_colorpickSample0;
	CColorPicker m_colorpickSample1;
	CColorPicker m_colorpickSample2;
	CColorPicker m_colorpickSample3;
	CColorPicker m_colorpickSample4;
	CColorPicker m_colorpickSample5;
	CColorPicker m_colorpickSample6;
	CColorPicker m_colorpickSample7;
	BOOL m_checkSample0;
	BOOL m_checkSample1;
	BOOL m_checkSample2;
	BOOL m_checkSample3;
	BOOL m_checkSample4;
	BOOL m_checkSample5;
	BOOL m_checkSample6;
	BOOL m_checkSample7;
	CEditColor m_ctrlSample0;
	CEditColor m_ctrlSample1;
	CEditColor m_ctrlSample2;
	CEditColor m_ctrlSample3;
	CEditColor m_ctrlSample4;
	CEditColor m_ctrlSample5;
	CEditColor m_ctrlSample6;
	CEditColor m_ctrlSample7;
	CString m_strSample0;
	CString m_strSample1;
	CString m_strSample2;
	CString m_strSample3;
	CString m_strSample4;
	CString m_strSample5;
	CString m_strSample6;
	CString m_strSample7;
	afx_msg void OnSetfocusEditSample0();
	afx_msg void OnSetfocusEditSample1();
	afx_msg void OnSetfocusEditSample2();
	afx_msg void OnSetfocusEditSample3();
	afx_msg void OnSetfocusEditSample4();
	afx_msg void OnSetfocusEditSample5();
	afx_msg void OnSetfocusEditSample6();
	afx_msg void OnSetfocusEditSample7();
	afx_msg void OnBnClickedCheckSample0();
	afx_msg void OnBnClickedCheckSample1();
	afx_msg void OnBnClickedCheckSample2();
	afx_msg void OnBnClickedCheckSample3();
	afx_msg void OnBnClickedCheckSample4();
	afx_msg void OnBnClickedCheckSample5();
	afx_msg void OnBnClickedCheckSample6();
	afx_msg void OnBnClickedCheckSample7();
	afx_msg void OnBnClickedZoomSampling();
	afx_msg void OnChangeEditSample0();
	afx_msg void OnChangeEditSample1();
	afx_msg void OnChangeEditSample2();
	afx_msg void OnChangeEditSample3();
	afx_msg void OnChangeEditSample4();
	afx_msg void OnChangeEditSample5();
	afx_msg void OnChangeEditSample6();
	afx_msg void OnChangeEditSample7();
	afx_msg void OnBnClickedSampleClear();
	BOOL m_bColorMaskSample;
	BOOL m_bShowMasking;
	afx_msg void OnBnClickedCheckColorSample();
	afx_msg void OnBnClickedCheckCameraImage();
	afx_msg void OnBnClickedCheckShowMasking();
	CColorPicker m_colorpickMaskSampleCheck;
	CColorPicker m_colorpickMaskSampleSelect;

	CColorPicker m_colorpickPatch0;
	CColorPicker m_colorpickPatch1;
	CColorPicker m_colorpickPatch2;
	CColorPicker m_colorpickPatch3;
	CColorPicker m_colorpickPatch4;
	CColorPicker m_colorpickPatch5;
	CColorPicker m_colorpickPatch6;
	CColorPicker m_colorpickPatch7;
	BOOL m_checkPatch0;
	BOOL m_checkPatch1;
	BOOL m_checkPatch2;
	BOOL m_checkPatch3;
	BOOL m_checkPatch4;
	BOOL m_checkPatch5;
	BOOL m_checkPatch6;
	BOOL m_checkPatch7;
	CEditColor m_ctrlPatch0;
	CEditColor m_ctrlPatch1;
	CEditColor m_ctrlPatch2;
	CEditColor m_ctrlPatch3;
	CEditColor m_ctrlPatch4;
	CEditColor m_ctrlPatch5;
	CEditColor m_ctrlPatch6;
	CEditColor m_ctrlPatch7;
	afx_msg void OnBnClickedCheckPatch0();
	afx_msg void OnBnClickedCheckPatch1();
	afx_msg void OnBnClickedCheckPatch2();
	afx_msg void OnBnClickedCheckPatch3();
	afx_msg void OnBnClickedCheckPatch4();
	afx_msg void OnBnClickedCheckPatch5();
	afx_msg void OnBnClickedCheckPatch6();
	afx_msg void OnBnClickedCheckPatch7();
	CString m_strPatch0;
	CString m_strPatch1;
	CString m_strPatch2;
	CString m_strPatch3;
	CString m_strPatch4;
	CString m_strPatch5;
	CString m_strPatch6;
	CString m_strPatch7;
	CDualSlider m_sliderKeySampleN;
	CDualSlider m_sliderKeySampleSize;
	afx_msg void OnBnClickedGeneratePatchColor();
	afx_msg void OnSetfocusEditPatch0();
	afx_msg void OnSetfocusEditPatch1();
	afx_msg void OnSetfocusEditPatch2();
	afx_msg void OnSetfocusEditPatch3();
	afx_msg void OnSetfocusEditPatch4();
	afx_msg void OnSetfocusEditPatch5();
	afx_msg void OnSetfocusEditPatch6();
	afx_msg void OnSetfocusEditPatch7();
	afx_msg void OnBnClickedPatchClear();
	afx_msg void OnBnClickedCheckColorPatch();
	BOOL m_bColorMaskPatch;
	CColorPicker m_colorpickMaskPatchCheck;
	CColorPicker m_colorpickMaskPatchSelect;

	CString m_strFileName;
	afx_msg void OnBnClickedOpenPatch();
	afx_msg void OnBnClickedSavePatch();
	afx_msg void OnDrawDualSliderKeySampleN(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDrawDualSliderKeySampleSize(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedGenerateKeySample();
};
