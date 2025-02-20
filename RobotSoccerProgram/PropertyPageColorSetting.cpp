// PropertyPageColorSetting.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "PropertyPageColorSetting.h"
#include "afxdialogex.h"


#define _USE_MATH_DEFINES
#include <math.h>

#include<queue>


// CPropertyPageColorSetting dialog

IMPLEMENT_DYNAMIC(CPropertyPageColorSetting, CPropertyPageRobotSoccer)

CPropertyPageColorSetting::CPropertyPageColorSetting()
	: CPropertyPageRobotSoccer(CPropertyPageColorSetting::IDD)
	, m_bShowCameraImage(TRUE)
	, m_bColorMaskSample(TRUE)
	, m_matColor(3, 3, CV_64F)
	, m_matColori(3, 3, CV_64F)
	, m_matXY(3, 1, CV_64F)
	, m_matRGB(3, 1, CV_64F)
	, m_checkSample0(FALSE)
	, m_checkSample1(FALSE)
	, m_checkSample2(FALSE)
	, m_checkSample3(FALSE)
	, m_checkSample4(FALSE)
	, m_checkSample5(FALSE)
	, m_checkSample6(FALSE)
	, m_checkSample7(FALSE)
	, m_checkPatch0(FALSE)
	, m_checkPatch1(FALSE)
	, m_checkPatch2(FALSE)
	, m_checkPatch3(FALSE)
	, m_checkPatch4(FALSE)
	, m_checkPatch5(FALSE)
	, m_checkPatch6(FALSE)
	, m_checkPatch7(FALSE)
	, m_strPatch0(_T(""))
	, m_bColorMaskPatch(TRUE)
	, m_bShowMasking(TRUE)
	, m_strFileName(_T(""))
{
	m_bMouseLButtonDown = false;
	m_bMouseRButtonDown = false;
	m_bMouseNormalizedRGB = false;

	m_bZoomClick = false;

	m_radioSample = 0;
	m_strSample0 = _T("Sample0");
	m_strSample1 = _T("Sample1");
	m_strSample2 = _T("Sample2");
	m_strSample3 = _T("Sample3");
	m_strSample4 = _T("Sample4");
	m_strSample5 = _T("Sample5");
	m_strSample6 = _T("Sample6");
	m_strSample7 = _T("Sample7");

	m_radioPatch = 0;
	//m_strPatch0 = _T("ball");
	//m_strPatch1 = _T("id-1");
	//m_strPatch2 = _T("id-2");
	//m_strPatch3 = _T("id-3");
	//m_strPatch4 = _T("team");
	//m_strPatch5 = _T("-");
	//m_strPatch6 = _T("-");
	//m_strPatch7 = _T("opponent");

	m_patchMask = 0;

	m_bGeneratePatchColor = false;

	m_sampleMask[0] = FALSE;
	m_sampleMask[1] = FALSE;
	m_sampleMask[2] = FALSE;
	m_sampleMask[3] = FALSE;
	m_sampleMask[4] = FALSE;
	m_sampleMask[5] = FALSE;
	m_sampleMask[6] = FALSE;
	m_sampleMask[7] = FALSE;

	m_patchMask = 0x00;

	InitializeCriticalSection(&m_critColorSetting);
}

CPropertyPageColorSetting::~CPropertyPageColorSetting()
{
	DeleteCriticalSection(&m_critColorSetting);
}

void CPropertyPageColorSetting::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageRobotSoccer::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_CAMERA_IMAGE, m_bShowCameraImage);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_ZOOM_DBCLICK_K, m_sliderZoomDBClickK);
	DDX_Control(pDX, IDC_COLOR_PICK_SAMPLE0, m_colorpickSample0);
	DDX_Control(pDX, IDC_COLOR_PICK_SAMPLE1, m_colorpickSample1);
	DDX_Control(pDX, IDC_COLOR_PICK_SAMPLE2, m_colorpickSample2);
	DDX_Control(pDX, IDC_COLOR_PICK_SAMPLE3, m_colorpickSample3);
	DDX_Control(pDX, IDC_COLOR_PICK_SAMPLE4, m_colorpickSample4);
	DDX_Control(pDX, IDC_COLOR_PICK_SAMPLE5, m_colorpickSample5);
	DDX_Control(pDX, IDC_COLOR_PICK_SAMPLE6, m_colorpickSample6);
	DDX_Control(pDX, IDC_COLOR_PICK_SAMPLE7, m_colorpickSample7);
	DDX_Check(pDX, IDC_CHECK_SAMPLE0, m_checkSample0);
	DDX_Check(pDX, IDC_CHECK_SAMPLE1, m_checkSample1);
	DDX_Check(pDX, IDC_CHECK_SAMPLE2, m_checkSample2);
	DDX_Check(pDX, IDC_CHECK_SAMPLE3, m_checkSample3);
	DDX_Check(pDX, IDC_CHECK_SAMPLE4, m_checkSample4);
	DDX_Check(pDX, IDC_CHECK_SAMPLE5, m_checkSample5);
	DDX_Check(pDX, IDC_CHECK_SAMPLE6, m_checkSample6);
	DDX_Check(pDX, IDC_CHECK_SAMPLE7, m_checkSample7);
	DDX_Control(pDX, IDC_EDIT_SAMPLE0, m_ctrlSample0);
	DDX_Control(pDX, IDC_EDIT_SAMPLE1, m_ctrlSample1);
	DDX_Control(pDX, IDC_EDIT_SAMPLE2, m_ctrlSample2);
	DDX_Control(pDX, IDC_EDIT_SAMPLE3, m_ctrlSample3);
	DDX_Control(pDX, IDC_EDIT_SAMPLE4, m_ctrlSample4);
	DDX_Control(pDX, IDC_EDIT_SAMPLE5, m_ctrlSample5);
	DDX_Control(pDX, IDC_EDIT_SAMPLE6, m_ctrlSample6);
	DDX_Control(pDX, IDC_EDIT_SAMPLE7, m_ctrlSample7);
	DDX_Text(pDX, IDC_EDIT_SAMPLE0, m_strSample0);
	DDX_Text(pDX, IDC_EDIT_SAMPLE1, m_strSample1);
	DDX_Text(pDX, IDC_EDIT_SAMPLE2, m_strSample2);
	DDX_Text(pDX, IDC_EDIT_SAMPLE3, m_strSample3);
	DDX_Text(pDX, IDC_EDIT_SAMPLE4, m_strSample4);
	DDX_Text(pDX, IDC_EDIT_SAMPLE5, m_strSample5);
	DDX_Text(pDX, IDC_EDIT_SAMPLE6, m_strSample6);
	DDX_Text(pDX, IDC_EDIT_SAMPLE7, m_strSample7);
	DDX_Check(pDX, IDC_CHECK_COLOR_SAMPLE, m_bColorMaskSample);
	DDX_Control(pDX, IDC_COLOR_PICK_MASK_SAMPLE_CHECK, m_colorpickMaskSampleCheck);
	DDX_Control(pDX, IDC_COLOR_PICK_MASK_SAMPLE_SELECT, m_colorpickMaskSampleSelect);
	DDX_Control(pDX, IDC_COLOR_PICK_PATCH0, m_colorpickPatch0);
	DDX_Control(pDX, IDC_COLOR_PICK_PATCH1, m_colorpickPatch1);
	DDX_Control(pDX, IDC_COLOR_PICK_PATCH2, m_colorpickPatch2);
	DDX_Control(pDX, IDC_COLOR_PICK_PATCH3, m_colorpickPatch3);
	DDX_Control(pDX, IDC_COLOR_PICK_PATCH4, m_colorpickPatch4);
	DDX_Control(pDX, IDC_COLOR_PICK_PATCH5, m_colorpickPatch5);
	DDX_Control(pDX, IDC_COLOR_PICK_PATCH6, m_colorpickPatch6);
	DDX_Control(pDX, IDC_COLOR_PICK_PATCH7, m_colorpickPatch7);
	DDX_Check(pDX, IDC_CHECK_PATCH0, m_checkPatch0);
	DDX_Check(pDX, IDC_CHECK_PATCH1, m_checkPatch1);
	DDX_Check(pDX, IDC_CHECK_PATCH2, m_checkPatch2);
	DDX_Check(pDX, IDC_CHECK_PATCH3, m_checkPatch3);
	DDX_Check(pDX, IDC_CHECK_PATCH4, m_checkPatch4);
	DDX_Check(pDX, IDC_CHECK_PATCH5, m_checkPatch5);
	DDX_Check(pDX, IDC_CHECK_PATCH6, m_checkPatch6);
	DDX_Check(pDX, IDC_CHECK_PATCH7, m_checkPatch7);
	DDX_Control(pDX, IDC_EDIT_PATCH0, m_ctrlPatch0);
	DDX_Control(pDX, IDC_EDIT_PATCH1, m_ctrlPatch1);
	DDX_Control(pDX, IDC_EDIT_PATCH2, m_ctrlPatch2);
	DDX_Control(pDX, IDC_EDIT_PATCH3, m_ctrlPatch3);
	DDX_Control(pDX, IDC_EDIT_PATCH4, m_ctrlPatch4);
	DDX_Control(pDX, IDC_EDIT_PATCH5, m_ctrlPatch5);
	DDX_Control(pDX, IDC_EDIT_PATCH6, m_ctrlPatch6);
	DDX_Control(pDX, IDC_EDIT_PATCH7, m_ctrlPatch7);
	//DDX_Text(pDX, IDC_EDIT_PATCH0, m_strPatch0);
	//DDX_Text(pDX, IDC_EDIT_PATCH1, m_strPatch1);
	//DDX_Text(pDX, IDC_EDIT_PATCH2, m_strPatch2);
	//DDX_Text(pDX, IDC_EDIT_PATCH3, m_strPatch3);
	//DDX_Text(pDX, IDC_EDIT_PATCH4, m_strPatch4);
	//DDX_Text(pDX, IDC_EDIT_PATCH5, m_strPatch5);
	//DDX_Text(pDX, IDC_EDIT_PATCH6, m_strPatch6);
	//DDX_Text(pDX, IDC_EDIT_PATCH7, m_strPatch7);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_KEY_SAMPLE_N, m_sliderKeySampleN);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_KEY_SAMPLE_SIZE, m_sliderKeySampleSize);
	DDX_Check(pDX, IDC_CHECK_COLOR_PATCH, m_bColorMaskPatch);
	DDX_Control(pDX, IDC_COLOR_PICK_MASK_PATCH_CHECK, m_colorpickMaskPatchCheck);
	DDX_Control(pDX, IDC_COLOR_PICK_MASK_PATCH_SELECT, m_colorpickMaskPatchSelect);
	DDX_Check(pDX, IDC_CHECK_SHOW_MASKING, m_bShowMasking);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
}

BEGIN_MESSAGE_MAP(CPropertyPageColorSetting, CPropertyPageRobotSoccer)
	// 메시지 맵 항목을 여기에 추가합니다.
	ON_BN_CLICKED(IDC_CHECK_CAMERA_IMAGE, &CPropertyPageColorSetting::OnBnClickedCheckCameraImage)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_CLEAR_SAMPLE_SELECTION, &CPropertyPageColorSetting::OnBnClickedClearSampleSelection)
	ON_BN_CLICKED(IDC_ZOOM_CAPTURE_AGAIN, &CPropertyPageColorSetting::OnBnClickedZoomCaptureAgain)
	ON_WM_PAINT()
	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE0, &CPropertyPageColorSetting::OnSetfocusEditSample0)
	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE1, &CPropertyPageColorSetting::OnSetfocusEditSample1)
	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE2, &CPropertyPageColorSetting::OnSetfocusEditSample2)
	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE3, &CPropertyPageColorSetting::OnSetfocusEditSample3)
	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE4, &CPropertyPageColorSetting::OnSetfocusEditSample4)
	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE5, &CPropertyPageColorSetting::OnSetfocusEditSample5)
	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE6, &CPropertyPageColorSetting::OnSetfocusEditSample6)
	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE7, &CPropertyPageColorSetting::OnSetfocusEditSample7)
	ON_BN_CLICKED(IDC_CHECK_SAMPLE0, &CPropertyPageColorSetting::OnBnClickedCheckSample0)
	ON_BN_CLICKED(IDC_CHECK_SAMPLE1, &CPropertyPageColorSetting::OnBnClickedCheckSample1)
	ON_BN_CLICKED(IDC_CHECK_SAMPLE2, &CPropertyPageColorSetting::OnBnClickedCheckSample2)
	ON_BN_CLICKED(IDC_CHECK_SAMPLE3, &CPropertyPageColorSetting::OnBnClickedCheckSample3)
	ON_BN_CLICKED(IDC_CHECK_SAMPLE4, &CPropertyPageColorSetting::OnBnClickedCheckSample4)
	ON_BN_CLICKED(IDC_CHECK_SAMPLE5, &CPropertyPageColorSetting::OnBnClickedCheckSample5)
	ON_BN_CLICKED(IDC_CHECK_SAMPLE6, &CPropertyPageColorSetting::OnBnClickedCheckSample6)
	ON_BN_CLICKED(IDC_CHECK_SAMPLE7, &CPropertyPageColorSetting::OnBnClickedCheckSample7)
	ON_BN_CLICKED(IDC_ZOOM_SAMPLING, &CPropertyPageColorSetting::OnBnClickedZoomSampling)
	ON_EN_CHANGE(IDC_EDIT_SAMPLE0, &CPropertyPageColorSetting::OnChangeEditSample0)
	ON_EN_CHANGE(IDC_EDIT_SAMPLE1, &CPropertyPageColorSetting::OnChangeEditSample1)
	ON_EN_CHANGE(IDC_EDIT_SAMPLE2, &CPropertyPageColorSetting::OnChangeEditSample2)
	ON_EN_CHANGE(IDC_EDIT_SAMPLE3, &CPropertyPageColorSetting::OnChangeEditSample3)
	ON_EN_CHANGE(IDC_EDIT_SAMPLE4, &CPropertyPageColorSetting::OnChangeEditSample4)
	ON_EN_CHANGE(IDC_EDIT_SAMPLE5, &CPropertyPageColorSetting::OnChangeEditSample5)
	ON_EN_CHANGE(IDC_EDIT_SAMPLE6, &CPropertyPageColorSetting::OnChangeEditSample6)
	ON_EN_CHANGE(IDC_EDIT_SAMPLE7, &CPropertyPageColorSetting::OnChangeEditSample7)
	ON_BN_CLICKED(IDC_SAMPLE_CLEAR, &CPropertyPageColorSetting::OnBnClickedSampleClear)
	ON_BN_CLICKED(IDC_CHECK_COLOR_SAMPLE, &CPropertyPageColorSetting::OnBnClickedCheckColorSample)
	ON_MESSAGE(CPN_SELENDOK, OnColorPickerChanged)
	ON_BN_CLICKED(IDC_CHECK_PATCH0, &CPropertyPageColorSetting::OnBnClickedCheckPatch0)
	ON_BN_CLICKED(IDC_CHECK_PATCH1, &CPropertyPageColorSetting::OnBnClickedCheckPatch1)
	ON_BN_CLICKED(IDC_CHECK_PATCH2, &CPropertyPageColorSetting::OnBnClickedCheckPatch2)
	ON_BN_CLICKED(IDC_CHECK_PATCH3, &CPropertyPageColorSetting::OnBnClickedCheckPatch3)
	ON_BN_CLICKED(IDC_CHECK_PATCH4, &CPropertyPageColorSetting::OnBnClickedCheckPatch4)
	ON_BN_CLICKED(IDC_CHECK_PATCH5, &CPropertyPageColorSetting::OnBnClickedCheckPatch5)
	ON_BN_CLICKED(IDC_CHECK_PATCH6, &CPropertyPageColorSetting::OnBnClickedCheckPatch6)
	ON_BN_CLICKED(IDC_CHECK_PATCH7, &CPropertyPageColorSetting::OnBnClickedCheckPatch7)
	ON_BN_CLICKED(IDC_GENERATE_PATCH_COLOR, &CPropertyPageColorSetting::OnBnClickedGeneratePatchColor)
	ON_EN_SETFOCUS(IDC_EDIT_PATCH0, &CPropertyPageColorSetting::OnSetfocusEditPatch0)
	ON_EN_SETFOCUS(IDC_EDIT_PATCH1, &CPropertyPageColorSetting::OnSetfocusEditPatch1)
	ON_EN_SETFOCUS(IDC_EDIT_PATCH2, &CPropertyPageColorSetting::OnSetfocusEditPatch2)
	ON_EN_SETFOCUS(IDC_EDIT_PATCH3, &CPropertyPageColorSetting::OnSetfocusEditPatch3)
	ON_EN_SETFOCUS(IDC_EDIT_PATCH4, &CPropertyPageColorSetting::OnSetfocusEditPatch4)
	ON_EN_SETFOCUS(IDC_EDIT_PATCH5, &CPropertyPageColorSetting::OnSetfocusEditPatch5)
	ON_EN_SETFOCUS(IDC_EDIT_PATCH6, &CPropertyPageColorSetting::OnSetfocusEditPatch6)
	ON_EN_SETFOCUS(IDC_EDIT_PATCH7, &CPropertyPageColorSetting::OnSetfocusEditPatch7)
	ON_BN_CLICKED(IDC_PATCH_CLEAR, &CPropertyPageColorSetting::OnBnClickedPatchClear)
	ON_BN_CLICKED(IDC_CHECK_COLOR_PATCH, &CPropertyPageColorSetting::OnBnClickedCheckColorPatch)
	ON_BN_CLICKED(IDC_CHECK_SHOW_MASKING, &CPropertyPageColorSetting::OnBnClickedCheckShowMasking)
	ON_BN_CLICKED(IDC_OPEN_PATCH, &CPropertyPageColorSetting::OnBnClickedOpenPatch)
	ON_BN_CLICKED(IDC_SAVE_PATCH, &CPropertyPageColorSetting::OnBnClickedSavePatch)
	ON_NOTIFY(CPN_DRAW_DUALSLIDER, IDC_PROGRESS_SLIDER_KEY_SAMPLE_N, &CPropertyPageColorSetting::OnDrawDualSliderKeySampleN)
	ON_NOTIFY(CPN_DRAW_DUALSLIDER, IDC_PROGRESS_SLIDER_KEY_SAMPLE_SIZE, &CPropertyPageColorSetting::OnDrawDualSliderKeySampleSize)
	ON_BN_CLICKED(IDC_GENERATE_KEY_SAMPLE, &CPropertyPageColorSetting::OnBnClickedGenerateKeySample)
END_MESSAGE_MAP()


//BEGIN_MESSAGE_MAP(CPropertyPageColorSetting, CPropertyPageRobotSoccer)
//	ON_BN_CLICKED(IDC_CHECK_CAMERA_IMAGE, &CPropertyPageColorSetting::OnBnClickedCheckCameraImage)
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
//	ON_WM_RBUTTONDOWN()
//	ON_WM_RBUTTONUP()
//	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONDBLCLK()
//	ON_BN_CLICKED(IDC_CLEAR_SAMPLE_SELECTION, &CPropertyPageColorSetting::OnBnClickedClearSampleSelection)
//	ON_BN_CLICKED(IDC_ZOOM_CAPTURE_AGAIN, &CPropertyPageColorSetting::OnBnClickedZoomCaptureAgain)
//	ON_WM_PAINT()
//	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE0, &CPropertyPageColorSetting::OnSetfocusEditSample0)
//	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE1, &CPropertyPageColorSetting::OnSetfocusEditSample1)
//	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE2, &CPropertyPageColorSetting::OnSetfocusEditSample2)
//	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE3, &CPropertyPageColorSetting::OnSetfocusEditSample3)
//	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE4, &CPropertyPageColorSetting::OnSetfocusEditSample4)
//	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE5, &CPropertyPageColorSetting::OnSetfocusEditSample5)
//	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE6, &CPropertyPageColorSetting::OnSetfocusEditSample6)
//	ON_EN_SETFOCUS(IDC_EDIT_SAMPLE7, &CPropertyPageColorSetting::OnSetfocusEditSample7)
//	ON_BN_CLICKED(IDC_CHECK_SAMPLE0, &CPropertyPageColorSetting::OnBnClickedCheckSample0)
//	ON_BN_CLICKED(IDC_CHECK_SAMPLE1, &CPropertyPageColorSetting::OnBnClickedCheckSample1)
//	ON_BN_CLICKED(IDC_CHECK_SAMPLE2, &CPropertyPageColorSetting::OnBnClickedCheckSample2)
//	ON_BN_CLICKED(IDC_CHECK_SAMPLE3, &CPropertyPageColorSetting::OnBnClickedCheckSample3)
//	ON_BN_CLICKED(IDC_CHECK_SAMPLE4, &CPropertyPageColorSetting::OnBnClickedCheckSample4)
//	ON_BN_CLICKED(IDC_CHECK_SAMPLE5, &CPropertyPageColorSetting::OnBnClickedCheckSample5)
//	ON_BN_CLICKED(IDC_CHECK_SAMPLE6, &CPropertyPageColorSetting::OnBnClickedCheckSample6)
//	ON_BN_CLICKED(IDC_CHECK_SAMPLE7, &CPropertyPageColorSetting::OnBnClickedCheckSample7)
//	ON_BN_CLICKED(IDC_ZOOM_SAMPLING, &CPropertyPageColorSetting::OnBnClickedZoomSampling)
//	ON_EN_CHANGE(IDC_EDIT_SAMPLE0, &CPropertyPageColorSetting::OnChangeEditSample0)
//	ON_EN_CHANGE(IDC_EDIT_SAMPLE1, &CPropertyPageColorSetting::OnChangeEditSample1)
//	ON_EN_CHANGE(IDC_EDIT_SAMPLE2, &CPropertyPageColorSetting::OnChangeEditSample2)
//	ON_EN_CHANGE(IDC_EDIT_SAMPLE3, &CPropertyPageColorSetting::OnChangeEditSample3)
//	ON_EN_CHANGE(IDC_EDIT_SAMPLE4, &CPropertyPageColorSetting::OnChangeEditSample4)
//	ON_EN_CHANGE(IDC_EDIT_SAMPLE5, &CPropertyPageColorSetting::OnChangeEditSample5)
//	ON_EN_CHANGE(IDC_EDIT_SAMPLE6, &CPropertyPageColorSetting::OnChangeEditSample6)
//	ON_EN_CHANGE(IDC_EDIT_SAMPLE7, &CPropertyPageColorSetting::OnChangeEditSample7)
//	ON_BN_CLICKED(IDC_SAMPLE_CLEAR, &CPropertyPageColorSetting::OnBnClickedSampleClear)
//	ON_BN_CLICKED(IDC_CHECK_COLOR_SAMPLE, &CPropertyPageColorSetting::OnBnClickedCheckColorSample)
//    ON_MESSAGE(CPN_SELENDOK,    OnColorPickerChanged)
//	ON_BN_CLICKED(IDC_CHECK_PATCH0, &CPropertyPageColorSetting::OnBnClickedCheckPatch0)
//	ON_BN_CLICKED(IDC_CHECK_PATCH1, &CPropertyPageColorSetting::OnBnClickedCheckPatch1)
//	ON_BN_CLICKED(IDC_CHECK_PATCH2, &CPropertyPageColorSetting::OnBnClickedCheckPatch2)
//	ON_BN_CLICKED(IDC_CHECK_PATCH3, &CPropertyPageColorSetting::OnBnClickedCheckPatch3)
//	ON_BN_CLICKED(IDC_CHECK_PATCH4, &CPropertyPageColorSetting::OnBnClickedCheckPatch4)
//	ON_BN_CLICKED(IDC_CHECK_PATCH5, &CPropertyPageColorSetting::OnBnClickedCheckPatch5)
//	ON_BN_CLICKED(IDC_CHECK_PATCH6, &CPropertyPageColorSetting::OnBnClickedCheckPatch6)
//	ON_BN_CLICKED(IDC_CHECK_PATCH7, &CPropertyPageColorSetting::OnBnClickedCheckPatch7)
//	ON_BN_CLICKED(IDC_GENERATE_PATCH_COLOR, &CPropertyPageColorSetting::OnBnClickedGeneratePatchColor)
//	ON_EN_SETFOCUS(IDC_EDIT_PATCH0, &CPropertyPageColorSetting::OnSetfocusEditPatch0)
//	ON_EN_SETFOCUS(IDC_EDIT_PATCH1, &CPropertyPageColorSetting::OnSetfocusEditPatch1)
//	ON_EN_SETFOCUS(IDC_EDIT_PATCH2, &CPropertyPageColorSetting::OnSetfocusEditPatch2)
//	ON_EN_SETFOCUS(IDC_EDIT_PATCH3, &CPropertyPageColorSetting::OnSetfocusEditPatch3)
//	ON_EN_SETFOCUS(IDC_EDIT_PATCH4, &CPropertyPageColorSetting::OnSetfocusEditPatch4)
//	ON_EN_SETFOCUS(IDC_EDIT_PATCH5, &CPropertyPageColorSetting::OnSetfocusEditPatch5)
//	ON_EN_SETFOCUS(IDC_EDIT_PATCH6, &CPropertyPageColorSetting::OnSetfocusEditPatch6)
//	ON_EN_SETFOCUS(IDC_EDIT_PATCH7, &CPropertyPageColorSetting::OnSetfocusEditPatch7)
//	ON_BN_CLICKED(IDC_PATCH_CLEAR, &CPropertyPageColorSetting::OnBnClickedPatchClear)
//	ON_BN_CLICKED(IDC_CHECK_COLOR_PATCH, &CPropertyPageColorSetting::OnBnClickedCheckColorPatch)
//	ON_BN_CLICKED(IDC_CHECK_SHOW_MASKING, &CPropertyPageColorSetting::OnBnClickedCheckShowMasking)
//	ON_BN_CLICKED(IDC_OPEN_PATCH, &CPropertyPageColorSetting::OnBnClickedOpenPatch)
//	ON_BN_CLICKED(IDC_SAVE_PATCH, &CPropertyPageColorSetting::OnBnClickedSavePatch)
//	ON_NOTIFY(CPN_DRAW_DUALSLIDER, IDC_PROGRESS_SLIDER_KEY_SAMPLE_N, &CPropertyPageColorSetting::OnDrawDualSliderKeySampleN)
//	ON_NOTIFY(CPN_DRAW_DUALSLIDER, IDC_PROGRESS_SLIDER_KEY_SAMPLE_SIZE, &CPropertyPageColorSetting::OnDrawDualSliderKeySampleSize)
//	ON_BN_CLICKED(IDC_GENERATE_KEY_SAMPLE, &CPropertyPageColorSetting::OnBnClickedGenerateKeySample)
//END_MESSAGE_MAP()


// CPropertyPageColorSetting message handlers


LONG CPropertyPageColorSetting::OnColorPickerChanged(UINT lParam, LONG wParam)
{
	SampleInfoDraw();
	NormalizedRGBDraw();

    return TRUE;
}

// CPropertyPageColorSetting message handlers

//LRESULT CPropertyPageColorSetting::OnColorPickerChanged(WPARAM wParam, LPARAM lParam)
//{
//	SampleInfoDraw();
//	NormalizedRGBDraw();
//
//	return TRUE;
//}


void CPropertyPageColorSetting::GenerateMaskInformation(void)
{
	std::vector<CPoint> vecMaskInformation[8];

	if( m_bGeneratePatchColor == false && m_bShowMasking )
	for( int i=0 ; i<m_pDC->Width() ; i++)
	{
		for( int j=0 ; j<m_pDC->Height() ; j++)
		{
			unsigned char r, g, b;
			
			m_pImageGrabber->GetColor( r, g, b, i, j, 0 );
				
			for( int p=0 ; p<8 ; p++ )
			{
				unsigned char l_mask = (0x01 << p);
				unsigned char color_data = m_pLookUpTable->GetLUTData( r, g, b );

				if( m_patchMask & l_mask & color_data )
				{
					vecMaskInformation[p].push_back( CPoint(i,j) );
				}

				if( p==m_radioPatch && (l_mask & color_data) )
				{
					vecMaskInformation[p].push_back( CPoint(i,j) );
				}
			}
		}
	}

	EnterCriticalSection(&m_critColorSetting);

	for( int p=0 ; p<8 ; p++ )
	{
		m_vecMaskInformation_share[p] = vecMaskInformation[p];
	}

	LeaveCriticalSection(&m_critColorSetting);
}

void CPropertyPageColorSetting::SetActiveVisionCore( CString strActiveVisionCore )
{
	static CString s_activeVisionCore = _T("");

	if( s_activeVisionCore == strActiveVisionCore )
		return;

	s_activeVisionCore = strActiveVisionCore;

	if( strActiveVisionCore == _T("DiagonalPatch") )
	{
		SetDlgItemTextW(IDC_EDIT_PATCH0, _T("Ball"   ) );
		SetDlgItemTextW(IDC_EDIT_PATCH1, _T("id-1"   ) );
		SetDlgItemTextW(IDC_EDIT_PATCH2, _T("id-2"   ) );
		SetDlgItemTextW(IDC_EDIT_PATCH3, _T("id-3"   ) );
		SetDlgItemTextW(IDC_EDIT_PATCH4, _T("team"   ) );
		SetDlgItemTextW(IDC_EDIT_PATCH5, _T("-") );
		SetDlgItemTextW(IDC_EDIT_PATCH6, _T("-") );
		SetDlgItemTextW(IDC_EDIT_PATCH7, _T("opponent"   ) );
	}

	if( strActiveVisionCore == _T("SegmentPatch") )
	{
		SetDlgItemTextW(IDC_EDIT_PATCH0, _T("ball"    ) );
		SetDlgItemTextW(IDC_EDIT_PATCH1, _T("support-1"  ) );
		SetDlgItemTextW(IDC_EDIT_PATCH2, _T("support-2"  ) );
		SetDlgItemTextW(IDC_EDIT_PATCH3, _T("-"       ) );
		SetDlgItemTextW(IDC_EDIT_PATCH4, _T("team"    ) );
		SetDlgItemTextW(IDC_EDIT_PATCH5, _T("-"       ) );
		SetDlgItemTextW(IDC_EDIT_PATCH6, _T("team+segment") );
		SetDlgItemTextW(IDC_EDIT_PATCH7, _T("opponent"    ) );
	}

	if( strActiveVisionCore == _T("BarPatch") )
	{
		SetDlgItemTextW(IDC_EDIT_PATCH0, _T("ball"   ) );
		SetDlgItemTextW(IDC_EDIT_PATCH1, _T("black"  ) );
		SetDlgItemTextW(IDC_EDIT_PATCH2, _T("-"      ) );
		SetDlgItemTextW(IDC_EDIT_PATCH3, _T("-"      ) );
		SetDlgItemTextW(IDC_EDIT_PATCH4, _T("team"   ) );
		SetDlgItemTextW(IDC_EDIT_PATCH5, _T("-"      ) );
		SetDlgItemTextW(IDC_EDIT_PATCH6, _T("-"      ) );
		SetDlgItemTextW(IDC_EDIT_PATCH7, _T("opponent"   ) );
	}
}

void CPropertyPageColorSetting::DrawDisplay(void)
{
	COLORREF patchColor[8];
	

	std::vector<CPoint> vecMaskInformation_draw[8];

	EnterCriticalSection(&m_critColorSetting);

	for( int p=0 ; p<8 ; p++ )
	{
		vecMaskInformation_draw[p] = m_vecMaskInformation_share[p];
	}

	LeaveCriticalSection(&m_critColorSetting);


	for( int p=0 ; p<8 ; p++ )
	{
		patchColor[p] = m_pLookUpTable->GetColor(p);

		if( m_bColorMaskPatch )
		{
			unsigned char l_mask = (0x01 << p);

			if( m_patchMask&l_mask )
			{
				patchColor[p] = m_colorpickMaskPatchCheck.GetColor();
			}
			else
			{
				patchColor[p] = m_colorpickMaskPatchSelect.GetColor();
			}
		}
	}

	

	if( m_pDC == NULL )
		return;

	if( m_pImageGrabber == NULL )
		return;

	if( !m_pImageGrabber->IsReady() )
	{
		m_pDC->FillSolidRect(0, 0, m_pDC->Width(), m_pDC->Height(), RGB(0,0,0) );
		m_pDC->SetBkMode( OPAQUE );
		m_pDC->SetTextColor( RGB(255,0,0) );
		m_pDC->TextOut( m_pDC->Width()/2-100, m_pDC->Height()/2-20,
						_T(" The image was not initialized "));
	}
	else
	{
		m_pDC->SetBkMode( OPAQUE );
		m_pDC->SetTextColor( RGB(255,0,0) );
		/*
		if( !m_pImageGrabber->IsCameraReady() )
		{
			m_pDC->TextOut( m_pDC->Width()/2-100, m_pDC->Height()/2-20,
			_T("        Camera is not ready        "));
			
			return;
		}
		*/
		
		if( !m_bShowCameraImage )
			m_pDC->FillSolidRect(0, 0, m_pDC->Width(), m_pDC->Height(), RGB(0,0,0) );
		else
			m_pImageGrabber->DrawToDC( m_pDC, 0, 0 );

		for( int p=0 ; p<8 ; p++ )
		{
			for( unsigned int i=0 ; i<vecMaskInformation_draw[p].size() ; i++ )
			{
				CPoint point = vecMaskInformation_draw[p][i];

				m_pDC->SetPixel( point.x, point.y, patchColor[p] );
			}
		}

		/*
		if( m_bGeneratePatchColor == false && m_bShowMasking )
		for( int i=0 ; i<m_pDC->Width() ; i++)
		{
			for( int j=0 ; j<m_pDC->Height() ; j++)
			{
				unsigned char r, g, b;
				m_pImageGrabber->GetColor( r, g, b, i, j, 0 );
				
				for( int p=0 ; p<8 ; p++ )
				{
					unsigned char l_mask = (0x01 << p);

					if( (m_patchMask&l_mask) & m_pLookUpTable->GetLUTData( r, g, b ) )
					{
						if( m_bColorMaskPatch )
							;//m_pDC->SetPixel( i, j, m_colorpickMaskPatchCheck.GetColor() );
						else
							;//m_pDC->SetPixel( i, j, m_pLookUpTable->GetColor(p) );
					}
				}

				for( int p=0 ; p<8 ; p++ )
				{
					unsigned char l_mask = (0x01 << p);
					
					if( p==m_radioPatch && (l_mask & m_pLookUpTable->GetLUTData( r, g, b )) )
					{
						if( m_bColorMaskPatch )
							;//m_pDC->SetPixel( i, j, m_colorpickMaskPatchSelect.GetColor() );
						else
							;//m_pDC->SetPixel( i, j, m_pLookUpTable->GetColor(p) );
					}
				}
			}
		}
		*/
	}


	//CString tmp;
	//tmp.Format(_T("%d : %d"), m_radioSample, m_radioPatch );
	//m_pDC->TextOut( 0,0, tmp );
	/*
	if( !m_bShowCameraImage )
	for( int i=0 ; i<m_pDC->Width() ; i++)
	{
		for( int j=0 ; j<m_pDC->Height() ; j++)
		{
			unsigned char r, g, b;
			m_pImageGrabber->GetColor( r, g, b, i, j, 0 );

			//double b_test = (double)b / (double)(r+g+b);

			double b_test = (double)b - (double)(r+g)/2;

			if( b_test < 0 ) b_test = 0;

			b_test = b_test * 5;

			bool bOver = false;
			if( b_test > 255 )
			{
				b_test = 255;
				bOver = true;
			}

			unsigned char b_color = (int)b_test;
			unsigned char r_color = b_color;
			unsigned char g_color = b_color;

			if( bOver )
			{
				b_color = r_color = 0;
				g_color = 255;
			}
			else
			{
			}



			m_pDC->SetPixel( i, j, RGB(r_color, g_color, b_color) );
		}
	}
	*/

}


void CPropertyPageColorSetting::OnBnClickedCheckCameraImage()
{
	EnterCriticalSection(&m_critColorSetting);
	UpdateData(TRUE);
	LeaveCriticalSection(&m_critColorSetting);


	NormalizedRGBDraw();
	SampleInfoDraw();;
}

MouseCapture::Enum CPropertyPageColorSetting::DisplayLButtonDown( UINT nFlags, CPoint point )
{
	m_pointZoomClick = point;
	ZoomInit();
	ZoomCaptureAgain();
	ZoomInfoDraw();

	return MouseCapture::NOTHING;
}

MouseCapture::Enum CPropertyPageColorSetting::DisplayMouseWheel( UINT nFlags, short zDelta, CPoint point )
{
	if( zDelta > 0 )
	{
		m_sampleData[m_radioSample].m_paramKeySampleSize += 0.01;
	}
	else
	if( zDelta < 0 )
	{
		m_sampleData[m_radioSample].m_paramKeySampleSize -= 0.01;
	}

	m_sampleData[m_radioSample].m_paramKeySampleSize = std::min( m_sampleData[m_radioSample].m_paramKeySampleSize, 0.50 );
	m_sampleData[m_radioSample].m_paramKeySampleSize = std::max( m_sampleData[m_radioSample].m_paramKeySampleSize, 0.01 );

	m_sliderKeySampleSize.SetValue( m_sampleData[m_radioSample].m_paramKeySampleSize );

	NormalizedRGBDraw();

	return MouseCapture::NOTHING;
}

void CPropertyPageColorSetting::ZoomInit()
{
	// special mark
	int m_mark[20][20] = 
	{	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 },
		{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
	int m_mark2[20][20] = 
	{	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
		{ 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
		
		{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0 },
		{ 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0 },
		{ 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },

		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};


	for( int i=0 ; i<ZOOM_X/ZOOM_K ; i++ )
	{
		for( int j=0 ; j<ZOOM_Y/ZOOM_K ; j++ )
		{
/*			if( m_mark[j][i] == 0 )
				m_zoomImage[i][j] = RGB( 255,255,255 );
			else
			if( m_mark[j][i] == 1 )
				m_zoomImage[i][j] = RGB( 255,32,32 );
			
			if( m_mark[19-j][19-i] == 1 )
				m_zoomImage[i][j] = RGB( 32, 32, 255 );

			if( m_mark2[j][i] == 1 )
*/				m_zoomImage[i][j] = RGB( 0, 0, 0);

			m_zoomMark[i][j] = false;
		}
	}

	m_zoomMarkedPixels = 0;

	m_textZoomInfo = _T("");
}

void CPropertyPageColorSetting::ZoomCaptureAgain()
{
	for( int i=0 ; i<ZOOM_X/ZOOM_K ; i++ )
	{
		for( int j=0 ; j<ZOOM_Y/ZOOM_K ; j++ )
		{
			m_zoomImage[i][j] = m_pImageGrabber->GetColor( m_pointZoomClick.x+i, m_pointZoomClick.y+j, 0 );
		}
	}
	
	ZoomDraw();
}


void CPropertyPageColorSetting::ZoomDraw()
{
	for( int i=0 ; i<ZOOM_X/ZOOM_K ; i++ )
	{
		for( int j=0 ; j<ZOOM_Y/ZOOM_K ; j++ )
		{
			ZoomPixelDraw( i, j );
		}
	}

	ZoomMouseDraw();


	CClientDC dc(this);
	m_dcZoom.BitBlt( &dc );
}

void CPropertyPageColorSetting::ZoomPixelDraw(int i, int j)
{
	for( int k1=0 ; k1< ZOOM_K ; k1++ )
		for( int k2=0 ; k2< ZOOM_K ; k2++ )
		{
			if( k1 == ZOOM_K-1 || k2 == ZOOM_K-1 )
				m_dcZoom.SetPixel( i*ZOOM_K + k1, j*ZOOM_K + k2,
									RGB( (int)(128*(ZOOM_K-1 - (k1+k2-ZOOM_K-1))/ZOOM_K),
										 (int)(128*(ZOOM_K-1 - (k1+k2-ZOOM_K-1))/ZOOM_K),
										 (int)(128*(ZOOM_K-1 - (k1+k2-ZOOM_K-1))/ZOOM_K) ) );
			else
				m_dcZoom.SetPixel( i*ZOOM_K + k1, j*ZOOM_K + k2, m_zoomImage[i][j] );
		}

	if( m_zoomMark[i][j] )
	{
		COLORREF color[8];
		// 0 = black  ..... 3,4 = ComplementaryColor(r,g,b) ..... 7 = white
		unsigned char r = 255-GetRValue( m_zoomImage[i][j] );
		unsigned char g = 255-GetGValue( m_zoomImage[i][j] );
		unsigned char b = 255-GetBValue( m_zoomImage[i][j] );

		for( int k=0 ; k<4 ; k++ )
		{
			color[k] = RGB( r*k/3, g*k/3, b*k/3);
		}
		for( int k=0 ; k<4 ; k++ )
		{
			color[k+4] = RGB( (255-r)*k/3+r, (255-g)*k/3+g, (255-b)*k/3+b);
		}

		int check_type = 0;

		if( check_type == 0 )
		{
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-2, j*ZOOM_K + ZOOM_K/2  , color[0] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-1, j*ZOOM_K + ZOOM_K/2  , color[1] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2  , color[2] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2-1, color[3] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2-2, color[4] );

			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-2, j*ZOOM_K + ZOOM_K/2-2 , color[5] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-1, j*ZOOM_K + ZOOM_K/2-2 , color[6] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-2, j*ZOOM_K + ZOOM_K/2-1 , color[7] );
		}
		
		//3x3
		if( check_type == 1 )
		{
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-2, j*ZOOM_K + ZOOM_K/2  , color[0] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-1, j*ZOOM_K + ZOOM_K/2  , color[2] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2  , color[3] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2-1, color[5] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2-2, color[7] );
// 			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-2, j*ZOOM_K + ZOOM_K/2  , RGB(  0,255,255) );
// 			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-1, j*ZOOM_K + ZOOM_K/2  , RGB( 50,255,255) );
// 			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2  , RGB(100,255,255) );
// 			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2-1, RGB(150,255,255) );
// 			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2-2, RGB(200,255,255) );
		}
		
		//2x2
		if( check_type == 2 )
		{
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-1, j*ZOOM_K + ZOOM_K/2  , color[0] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-1, j*ZOOM_K + ZOOM_K/2-1, color[5] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2  , color[6] );
			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2-1, color[7] );
// 			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-1, j*ZOOM_K + ZOOM_K/2  , RGB(  0,255,255) );
// 			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2-1, j*ZOOM_K + ZOOM_K/2-1, RGB(  0,255,255) );
// 			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2  , RGB(  0,255,255) );
// 			m_dcZoom.SetPixel( i*ZOOM_K + ZOOM_K/2  , j*ZOOM_K + ZOOM_K/2-1, RGB(  0,255,255) );
		}
	}
}

void CPropertyPageColorSetting::ZoomMouseDraw()
{
	static CPoint m_oldPos = CPoint(0,0);
	
	// Red Mouse Point
	if( 0 <= m_mouseZoomPos.x && m_mouseZoomPos.x < ZOOM_X/ZOOM_K
	 &&	0 <= m_mouseZoomPos.y && m_mouseZoomPos.y < ZOOM_X/ZOOM_K )
	{
		ZoomPixelDraw( m_oldPos.x, m_oldPos.y );
		ZoomPixelDraw( m_oldPos.x-1, m_oldPos.y );
		ZoomPixelDraw( m_oldPos.x, m_oldPos.y-1 );

		int i = m_mouseZoomPos.x;
		int j = m_mouseZoomPos.y;

		int k1,k2;
		for( int k=0 ; k< ZOOM_K ; k++ )
		{
			k1 = k;
			k2 = ZOOM_K-1;
			m_dcZoom.SetPixel( i*ZOOM_K + k1, j*ZOOM_K + k2,
									RGB( 255,0,0 ));

			k1 = ZOOM_K-1;
			k2 = k;
			m_dcZoom.SetPixel( i*ZOOM_K + k1, j*ZOOM_K + k2,
									RGB( 255,0,0 ));

			k1 = k;
			k2 = -1;
			m_dcZoom.SetPixel( i*ZOOM_K + k1, j*ZOOM_K + k2,
									RGB( 255,0,0 ));

			k1 = -1;
			k2 = k;
			m_dcZoom.SetPixel( i*ZOOM_K + k1, j*ZOOM_K + k2,
									RGB( 255,0,0 ));
		}

		m_oldPos = m_mouseZoomPos;
	}
}


void CPropertyPageColorSetting::ZoomPixelClickRecursive(CPoint point, COLORREF color)
{
	struct st_pixel
	{
		CPoint point;
		COLORREF color;
	};

	std::queue< struct st_pixel> q;

	struct st_pixel data;
	data.point = point;
	data.color = color;
	q.push( data );

	while( !q.empty() )
	{
		data = q.front();
		q.pop();

		if( 0 <= data.point.x && data.point.x < ZOOM_X/ZOOM_K && 0 <= data.point.y && data.point.y < ZOOM_Y/ZOOM_K )
		{
			int dR = GetRValue( data.color ) - GetRValue( m_zoomImage[data.point.x][data.point.y] );
			int dG = GetGValue( data.color ) - GetGValue( m_zoomImage[data.point.x][data.point.y] );
			int dB = GetBValue( data.color ) - GetBValue( m_zoomImage[data.point.x][data.point.y] );
		
			if( !m_zoomMark[data.point.x][data.point.y] )
				if( sqrt((double)(dR*dR+dG*dG+dB*dB)) < m_sliderZoomDBClickK.GetValue() )
				{
					m_zoomMarkedPixels++;
				
					m_zoomMark[data.point.x][data.point.y] = true;
				
					CPoint dp[4]={ CPoint(-1,0),CPoint(+1,0),CPoint(0,-1),CPoint(0,+1)};
				
					for( int i=0 ; i<4 ; i++ )
					{
						struct st_pixel new_data;
						new_data.point = data.point + dp[i];
						new_data.color = data.color;

						q.push( new_data );
					}
					//ZoomPixelClickRecursive( point+dp[0], color );
					//ZoomPixelClickRecursive( point+dp[1], color );
					//ZoomPixelClickRecursive( point+dp[2], color );
					//ZoomPixelClickRecursive( point+dp[3], color );
				
					{
						ZoomPixelDraw( point.x, point.y );
						CClientDC dc(this);
						m_dcZoom.BitBlt( &dc );
					}
				
					CString tmp;
					tmp.Format(_T("%3ld pixels are marked"), m_zoomMarkedPixels );
					//AfxMessageBox(tmp);
					ZoomInfoDraw(tmp);
				}
		}

	}
}

void CPropertyPageColorSetting::ZoomPixelClick(CPoint point, bool mask)
{
	if( 0 <= point.x && point.x < ZOOM_X/ZOOM_K && 0 <= point.y && point.y < ZOOM_Y/ZOOM_K )
	{
		if( mask && !m_zoomMark[point.x][point.y] )
			m_zoomMarkedPixels++;
		
		if( !mask && m_zoomMark[point.x][point.y] )
			m_zoomMarkedPixels--;
		
		m_zoomMark[point.x][point.y] = mask;
		
		//		ZoomDraw();
		{
			ZoomPixelDraw( point.x, point.y );
			CClientDC dc(this);
			m_dcZoom.BitBlt( &dc );
		}
		
		CString tmp;
		tmp.Format(_T("%3ld pixels are marked"), m_zoomMarkedPixels );
		//AfxMessageBox(tmp);
		ZoomInfoDraw(tmp);
	}
}

CPoint CPropertyPageColorSetting::PointToZoomArray(CPoint point)
{
	CPoint p = point - m_dcZoom.TopLeft();
	
	p.x = p.x / ZOOM_K;
	p.y = p.y / ZOOM_K;
	
	return p;
}


void CPropertyPageColorSetting::ZoomInfoDraw(CString text)
{
	m_textZoomInfo = text;
	
	ZoomInfoDraw();
}

void CPropertyPageColorSetting::ZoomInfoDraw()
{
	{
		m_dcZoomInfo.SetBkMode( TRANSPARENT );
		//m_dcZoomInfo.SetBkMode( OPAQUE );
		//m_dcZoomInfo.SetBkColor( RGB( 0, 0, 0 ) );
		m_dcZoomInfo.SetTextColor( RGB( 255,255,255 ) );
		//m_infom_pDC->TextOut( 0, 0, "TEST");
		
		CString tmp;

		tmp.Format(_T("Sample-%d : "), m_radioSample );

		if( m_radioSample == 0 ) tmp += m_strSample0;
		if( m_radioSample == 1 ) tmp += m_strSample1;
		if( m_radioSample == 2 ) tmp += m_strSample2;
		if( m_radioSample == 3 ) tmp += m_strSample3;
		if( m_radioSample == 4 ) tmp += m_strSample4;
		if( m_radioSample == 5 ) tmp += m_strSample5;
		if( m_radioSample == 6 ) tmp += m_strSample6;
		if( m_radioSample == 7 ) tmp += m_strSample7;

		tmp += _T("\n");
		tmp += m_textZoomInfo;

		// 텍스트 출력
		CRect rect( 0, 0, ZOOM_INFO_X, ZOOM_INFO_Y );
		m_dcZoomInfo.FillSolidRect( 0, 0, ZOOM_INFO_X, ZOOM_INFO_Y, RGB(0,0,0));
		m_dcZoomInfo.DrawText( tmp, rect, DT_CENTER);
		/*
		DT_LEFT, DT_RIGHT, DT_CENTER
		DT_TOP, DT_VCENTER, DT_BOTTOM
		DT_SINGLELINE
		* DT_VCENTER need DT_SINGLELINE
		*/
		
		//		CBrush brush, *pOldBrush;
		//		brush.CreateSolidBrush( RGB(0,0,0) );
		//		pOldBrush = (CBrush*)m_infom_pDC->SelectObject( &brush );
		//
		//		CPen pen, *pOldPen;
		//		pen.CreatePen( PS_SOLID, 1, RGB(0,0,0) );
		//		pOldPen = (CPen*)m_infom_pDC->SelectObject( &pen );
		//
		//		m_infom_pDC->SelectObject( pOldPen );
		//		m_infom_pDC->SelectObject( pOldBrush );
	}
	
	CClientDC dc(this);
	m_dcZoomInfo.BitBlt( &dc );
}

int CPropertyPageColorSetting::PointToPatchParameter( CPoint point )
{
	CPoint p = point - m_dcSampleInfo.TopLeft() - CPoint(SAMPLE_INFO_MARGIN_LEFT,SAMPLE_INFO_MARGIN_TOP);
	
	double scaleK = (m_dcSampleInfo.Width()-(SAMPLE_INFO_MARGIN_LEFT+SAMPLE_INFO_MARGIN_RIGHT)) / (255.0*3.0);

	int result = (int)(p.x / scaleK);

	result = std::max( 0, result );
	result = std::min( 255*3, result );

	return result;
}

CPoint CPropertyPageColorSetting::PointToNormalizedRGB(CPoint point)
{
	CPoint p = point - m_dcNormalizedRGB.TopLeft();
	
	return p;
}

void CPropertyPageColorSetting::NormalizedRGBClick(CPoint point, bool mask)
{
	if( mask == true )
	{
		int i = point.x;
		int j = point.y;
	
		m_NormalizedRGBMark[m_radioSample][i][j] = true;
	}
	else
	{
		double size = m_sampleData[m_radioSample].m_paramKeySampleSize*NORMALIZED_RGB_DATA_SIZE;

		for( int i=0 ; i<NORMALIZED_RGB_DATA_SIZE ; i++ )
		{
			for( int j=0 ; j<NORMALIZED_RGB_DATA_SIZE ; j++ )
			{
				if( m_NormalizedRGBMark[m_radioSample][i][j] )
				{
					if( size*size > (i-point.x)*(i-point.x) + (j-point.y)*(j-point.y) )
					{
						m_NormalizedRGBMark[m_radioSample][i][j] = false;
					}
				}


			}
		}
	}

	m_sampleData[m_radioSample].m_paramKeySampleN = 0;
	for( int i=0 ; i<NORMALIZED_RGB_DATA_SIZE ; i++ )
	{
		for( int j=0 ; j<NORMALIZED_RGB_DATA_SIZE ; j++ )
		{
			if( m_NormalizedRGBMark[m_radioSample][i][j] == true )
			{
				m_sampleData[m_radioSample].m_paramKeySampleN++;
			}
		}
	}

	m_sliderKeySampleN.SetValue( m_sampleData[m_radioSample].m_paramKeySampleN );
}


void CPropertyPageColorSetting::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( m_bMouseRButtonDown )
	{
		// cancel
		m_bMouseRButtonDown = false;
		m_bMouseLButtonDown = false;
		ReleaseCapture();
	}
	else
	{
		if( m_dcZoom.IsPointInRect( point ) )
		{
			// Zoom Frame에 있을 때
			CPoint zoomPos = PointToZoomArray( point );
			m_mouseZoomPos = zoomPos;
			ZoomPixelClick( zoomPos, true );
			ZoomMouseDraw();			

			CClientDC dc(this);
			m_dcZoom.BitBlt( &dc );

			m_bZoomClick = true;
		}
		else
		if( m_dcSampleInfo.IsPointInRect( point ) )
		{
			int rgb_min = PointToPatchParameter( point );
			if( rgb_min < m_sampleData[m_radioSample].m_paramRGBmax )
				m_sampleData[m_radioSample].m_paramRGBmin = rgb_min;
			SampleInfoDraw();
		}
		else
		if( m_dcNormalizedRGB.IsPointInRect( point ) )
		{
			CPoint nrgbPos = PointToNormalizedRGB( point );
			m_mouseNRGBPos = nrgbPos;
			NormalizedRGBClick( nrgbPos, true );
			
			NormalizedRGBDraw();

			m_bZoomClick = false;
		}
	
			
		//마우스 위치 기록 생략
		m_bMouseLButtonDown = true;
		SetCapture();
	}

	CPropertyPageRobotSoccer::OnLButtonDown(nFlags, point);
}


void CPropertyPageColorSetting::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bMouseLButtonDown = false;
	ReleaseCapture();
		
	m_bZoomClick = false;

	CPropertyPageRobotSoccer::OnLButtonUp(nFlags, point);
}


void CPropertyPageColorSetting::OnRButtonDown(UINT nFlags, CPoint point)
{
	if( m_bMouseLButtonDown )
	{
		// cancel
		m_bMouseRButtonDown = false;
		m_bMouseLButtonDown = false;
		ReleaseCapture();
	}
	else
	{
		if( m_dcZoom.IsPointInRect( point ) )
		{
			// Zoom Frame에 있을 때
			CPoint zoomPos = PointToZoomArray( point );
			m_mouseZoomPos = zoomPos;
			ZoomPixelClick( zoomPos, false );
			ZoomMouseDraw();			
			
			CClientDC dc(this);
			m_dcZoom.BitBlt( &dc );

			m_bZoomClick = true;
		}
		else
		if( m_dcSampleInfo.IsPointInRect( point ) )
		{
			int rgb_max = PointToPatchParameter( point );
			if( rgb_max > m_sampleData[m_radioSample].m_paramRGBmin )
				m_sampleData[m_radioSample].m_paramRGBmax = rgb_max;
			SampleInfoDraw();
		}
		else
		if( m_dcNormalizedRGB.IsPointInRect( point ) )
		{
			CPoint nrgbPos = PointToNormalizedRGB( point );
			m_mouseNRGBPos = nrgbPos;
			NormalizedRGBClick( nrgbPos, false );
						
			NormalizedRGBDraw();

			m_bZoomClick = false;
		}
		
		
		//마우스 위치 기록 생략
		m_bMouseRButtonDown = true;
		SetCapture();
	}

	CPropertyPageRobotSoccer::OnRButtonDown(nFlags, point);
}


void CPropertyPageColorSetting::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_bMouseRButtonDown = false;
	ReleaseCapture();
	
	m_bZoomClick = false;
	

	CPropertyPageRobotSoccer::OnRButtonUp(nFlags, point);
}


void CPropertyPageColorSetting::OnMouseMove(UINT nFlags, CPoint point)
{
	/*
	if( m_dcNormalizedRGB.IsPointInRect( point ) )
	{
		if( !m_bMouseNormalizedRGB )
		{
			GetDlgItem(IDC_FRAME_NORMALIZED_RGB_MASK_GRAPH)->SetFocus();
			m_bMouseNormalizedRGB = true;
		}
	}
	else
	{
		if( m_bMouseNormalizedRGB )
		{
			m_bMouseNormalizedRGB = false;
		}
	}
	*/

	if( m_bZoomClick )
	{
		CPoint zoomPos = PointToZoomArray( point );

		if( m_bMouseLButtonDown && !m_bMouseRButtonDown )
		{
			CPoint oldPoint = m_mouseZoomPos;
			CPoint dp = oldPoint - zoomPos;
			int dis = std::max( abs(dp.x), abs(dp.y) );

			if( dis>0 )
			for( int i=0 ; i<=dis ; i++ )
			{
				int x = (oldPoint.x * (dis-i) + zoomPos.x * i )/dis;
				int y = (oldPoint.y * (dis-i) + zoomPos.y * i )/dis;

				m_mouseZoomPos = CPoint(x,y);

				ZoomPixelClick( CPoint(x,y), true );
				ZoomMouseDraw();
			}
			CClientDC dc(this);
			m_dcZoom.BitBlt( &dc );
		}
		else
		if( !m_bMouseLButtonDown && m_bMouseRButtonDown )
		{
			CPoint oldPoint = m_mouseZoomPos;
			CPoint dp = oldPoint - zoomPos;
			int dis = std::max( abs(dp.x), abs(dp.y) );

			m_mouseZoomPos = zoomPos;

			if( dis>0 )
			for( int i=0 ; i<=dis ; i++ )
			{
				int x = (oldPoint.x * (dis-i) + zoomPos.x * i )/dis;
				int y = (oldPoint.y * (dis-i) + zoomPos.y * i )/dis;

				ZoomPixelClick( CPoint(x,y), false );
				ZoomMouseDraw();
			}
			CClientDC dc(this);
			m_dcZoom.BitBlt( &dc );
		}
		else
		if( m_mouseZoomPos != zoomPos )
		{
			m_mouseZoomPos = zoomPos;
			ZoomDraw();
			CClientDC dc(this);
			m_dcZoom.BitBlt( &dc );
		}
	}
	else
	{
		if( m_dcZoom.IsPointInRect( point ) )
		{
			CPoint zoomPos = PointToZoomArray( point );
			m_mouseZoomPos = zoomPos;
			ZoomDraw();
			CClientDC dc(this);
			m_dcZoom.BitBlt( &dc );
		}
	}
	
	CPropertyPageRobotSoccer::OnMouseMove(nFlags, point);
}

void CPropertyPageColorSetting::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	{
		if( m_dcZoom.IsPointInRect( point ) )
		{
			CPoint zoomPos = PointToZoomArray( point );
			
			if( 0 <= zoomPos.x && zoomPos.x < ZOOM_X/ZOOM_K && 0 <= zoomPos.y && zoomPos.y < ZOOM_Y/ZOOM_K )
			{
				m_zoomMark[zoomPos.x][zoomPos.y] = false;
				m_zoomMarkedPixels--;
				ZoomPixelClickRecursive( zoomPos, m_zoomImage[zoomPos.x][zoomPos.y]  );
			}
		}
		
		m_bMouseLButtonDown = false;
		m_bMouseRButtonDown = false;
		//SetCapture();
	}

	ZoomDraw();

	CPropertyPageRobotSoccer::OnLButtonDblClk(nFlags, point);
}

BOOL CPropertyPageColorSetting::OnInitDialog()
{
	CPropertyPageRobotSoccer::OnInitDialog();

	CClientDC dc(this);

	SetActiveVisionCore(_T("DiagonalPatch")); // Updated from "BarPatch"

	// 유사 색상 판단
	m_sliderZoomDBClickK.SetOption( _T("Check Similar Colour"), false, 0, 50, 5, 1 );
	m_sliderZoomDBClickK.SetValue( 30 );

	// Init Zoom
	CRect rect;
	GetDlgItem(IDC_FRAME_ZOOM)->GetWindowRect(rect);
	ScreenToClient(rect);
	GetDlgItem(IDC_FRAME_ZOOM)->SetWindowPos( NULL, rect.left, rect.top, ZOOM_X+1, ZOOM_Y+1, SWP_NOZORDER | SWP_NOACTIVATE);
	GetDlgItem(IDC_FRAME_ZOOM)->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1,1,1,1);
	m_dcZoom.Init( &dc, rect );
	ZoomInit();
	
	// Init ZoomInfo
	GetDlgItem(IDC_FRAME_ZOOM_INFO)->GetWindowRect(rect);
	ScreenToClient(rect);
	GetDlgItem(IDC_FRAME_ZOOM_INFO)->SetWindowPos( NULL, rect.left, rect.top, ZOOM_INFO_X+2, ZOOM_INFO_Y+2, SWP_NOZORDER | SWP_NOACTIVATE);
	GetDlgItem(IDC_FRAME_ZOOM_INFO)->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1,1,1,1);
	m_dcZoomInfo.UpdateRect( rect );
	m_dcZoomInfo.Init( &dc );


	m_pcolorpickSample[0] = &m_colorpickSample0;
	m_pcolorpickSample[1] = &m_colorpickSample1;
	m_pcolorpickSample[2] = &m_colorpickSample2;
	m_pcolorpickSample[3] = &m_colorpickSample3;
	m_pcolorpickSample[4] = &m_colorpickSample4;
	m_pcolorpickSample[5] = &m_colorpickSample5;
	m_pcolorpickSample[6] = &m_colorpickSample6;
	m_pcolorpickSample[7] = &m_colorpickSample7;

	m_pcolorpickPatch[0] = &m_colorpickPatch0;
	m_pcolorpickPatch[1] = &m_colorpickPatch1;
	m_pcolorpickPatch[2] = &m_colorpickPatch2;
	m_pcolorpickPatch[3] = &m_colorpickPatch3;
	m_pcolorpickPatch[4] = &m_colorpickPatch4;
	m_pcolorpickPatch[5] = &m_colorpickPatch5;
	m_pcolorpickPatch[6] = &m_colorpickPatch6;
	m_pcolorpickPatch[7] = &m_colorpickPatch7;

	for( int i=0 ; i<8 ; i++ )
	{
		m_pcolorpickSample[i]->SetEditable( FALSE );
		m_pcolorpickPatch[i]->SetEditable( FALSE );

		m_pcolorpickSample[i]->SetColor( RGB(0,0,0) );
		m_pcolorpickPatch[i]->SetColor( RGB(0,0,0) );
	}



	// Init SampleInfo
	GetDlgItem(IDC_FRAME_SAMPLE_INFO)->GetWindowRect(rect);
	ScreenToClient(rect);
//	GetDlgItem(IDC_FRAME_SAMPLE_INFO)->SetWindowPos( NULL, rect.left, rect.top, SAMPLE_INFO_X+2, SAMPLE_INFO_Y+2, SWP_NOZORDER | SWP_NOACTIVATE);
//	GetDlgItem(IDC_FRAME_SAMPLE_INFO)->GetWindowRect(rect);
//	ScreenToClient(rect);
	rect.DeflateRect(1,1,1,1);
	m_dcSampleInfo.UpdateRect( rect );
	m_dcSampleInfo.Init( &dc );

	SetfocusEditSample();
	SetfocusEditPatch();

	m_colorpickMaskSampleCheck.SetColor(  RGB(  0,255,255) );
	m_colorpickMaskSampleSelect.SetColor( RGB(  0,255,  0) );


	// Init Normalized RGB Graph
	GetDlgItem(IDC_FRAME_NORMALIZED_RGB_MASK_GRAPH)->GetWindowRect(rect);
	ScreenToClient(rect);
	GetDlgItem(IDC_FRAME_NORMALIZED_RGB_MASK_GRAPH)->SetWindowPos( NULL, rect.left, rect.top, NORMALIZED_RGB_DRAW_SIZE+2, NORMALIZED_RGB_DRAW_SIZE+2, SWP_NOZORDER | SWP_NOACTIVATE);
	GetDlgItem(IDC_FRAME_NORMALIZED_RGB_MASK_GRAPH)->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1,1,1,1);
	m_dcNormalizedRGB.UpdateRect( rect );
	m_dcNormalizedRGB.Init( &dc );

	InitializeNormalizedRGB();


	m_sliderKeySampleSize.SetOption( _T("Sample Size"), false, 0.01, 0.5, 0.01, 2 );
	m_sliderKeySampleSize.SetValue( 0.1 );

	m_sliderKeySampleN.SetOption( _T("Samples"), false, 0, MAX_KEY_SAMPLE_N, 1, 0 );
	m_sliderKeySampleN.SetValue( 1 );

	m_colorpickMaskPatchCheck.SetColor(   RGB(255,255,255) );
	m_colorpickMaskPatchSelect.SetColor(  RGB(255,  0,  0) );







	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageColorSetting::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	ZoomDraw();
	ZoomInfoDraw();


	SampleInfoDraw();

////	MaskFrameDraw();
////	MaskGraphDraw();

	NormalizedRGBDraw();
}

void CPropertyPageColorSetting::OnBnClickedClearSampleSelection()
{
	m_zoomMarkedPixels = 0;

	for( int i=0 ; i<ZOOM_X/ZOOM_K ; i++ )
	{
		for( int j=0 ; j<ZOOM_Y/ZOOM_K ; j++ )
		{
			m_zoomMark[i][j] = false;
		}
	}
	
	ZoomDraw();
	ZoomInfoDraw(_T("initialise selected sample "));
}


void CPropertyPageColorSetting::OnBnClickedZoomCaptureAgain()
{
	for( int i=0 ; i<ZOOM_X/ZOOM_K ; i++ )
	{
		for( int j=0 ; j<ZOOM_Y/ZOOM_K ; j++ )
		{
			m_zoomImage[i][j] = m_pImageGrabber->GetColor( m_pointZoomClick.x+i, m_pointZoomClick.y+j, 0 );
		}
	}
	
	ZoomDraw();
}

void CPropertyPageColorSetting::OnSetfocusEditSample0(){ SelectSample(0); }
void CPropertyPageColorSetting::OnSetfocusEditSample1(){ SelectSample(1); }
void CPropertyPageColorSetting::OnSetfocusEditSample2(){ SelectSample(2); }
void CPropertyPageColorSetting::OnSetfocusEditSample3(){ SelectSample(3); }
void CPropertyPageColorSetting::OnSetfocusEditSample4(){ SelectSample(4); }
void CPropertyPageColorSetting::OnSetfocusEditSample5(){ SelectSample(5); }
void CPropertyPageColorSetting::OnSetfocusEditSample6(){ SelectSample(6); }
void CPropertyPageColorSetting::OnSetfocusEditSample7(){ SelectSample(7); }


void CPropertyPageColorSetting::SelectSample(int p)
{
	m_radioSample = p;
	SetfocusEditSample();
	
	ZoomInfoDraw();
	SampleInfoDraw();
	
//	m_sliderKeySampleSize.SetValue( m_sampleData[p].m_paramKeySampleSize );
	
	NormalizedRGBDraw();
//	NormalizedRGBInfoDraw();
}

void CPropertyPageColorSetting::SetfocusEditSample()
{
	COLORREF colorTextDeselect = RGB(0,0,0);
	COLORREF colorBKDeselect = GetSysColor( COLOR_BTNFACE ) ;

	COLORREF colorTextSelect = RGB(0,0,0);
	COLORREF colorBKSelect = RGB(128,255,128);
	
	m_ctrlSample0.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlSample1.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlSample2.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlSample3.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlSample4.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlSample5.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlSample6.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlSample7.SetColor( colorTextDeselect, colorBKDeselect );	
	
	if( m_radioSample == 0 ) m_ctrlSample0.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioSample == 1 ) m_ctrlSample1.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioSample == 2 ) m_ctrlSample2.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioSample == 3 ) m_ctrlSample3.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioSample == 4 ) m_ctrlSample4.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioSample == 5 ) m_ctrlSample5.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioSample == 6 ) m_ctrlSample6.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioSample == 7 ) m_ctrlSample7.SetColor( colorTextSelect, colorBKSelect );

	m_ctrlSample0.Invalidate(FALSE);	
	m_ctrlSample1.Invalidate(FALSE);	
	m_ctrlSample2.Invalidate(FALSE);	
	m_ctrlSample3.Invalidate(FALSE);	
	m_ctrlSample4.Invalidate(FALSE);	
	m_ctrlSample5.Invalidate(FALSE);	
	m_ctrlSample6.Invalidate(FALSE);	
	m_ctrlSample7.Invalidate(FALSE);
}

void CPropertyPageColorSetting::OnBnClickedCheckSample0(){ UpdateData(TRUE); OnBnClickedCheckSample( 0, m_checkSample0 ); }
void CPropertyPageColorSetting::OnBnClickedCheckSample1(){ UpdateData(TRUE); OnBnClickedCheckSample( 1, m_checkSample1 ); }
void CPropertyPageColorSetting::OnBnClickedCheckSample2(){ UpdateData(TRUE); OnBnClickedCheckSample( 2, m_checkSample2 ); }
void CPropertyPageColorSetting::OnBnClickedCheckSample3(){ UpdateData(TRUE); OnBnClickedCheckSample( 3, m_checkSample3 ); }
void CPropertyPageColorSetting::OnBnClickedCheckSample4(){ UpdateData(TRUE); OnBnClickedCheckSample( 4, m_checkSample4 ); }
void CPropertyPageColorSetting::OnBnClickedCheckSample5(){ UpdateData(TRUE); OnBnClickedCheckSample( 5, m_checkSample5 ); }
void CPropertyPageColorSetting::OnBnClickedCheckSample6(){ UpdateData(TRUE); OnBnClickedCheckSample( 6, m_checkSample6 ); }
void CPropertyPageColorSetting::OnBnClickedCheckSample7(){ UpdateData(TRUE); OnBnClickedCheckSample( 7, m_checkSample7 ); }
void CPropertyPageColorSetting::OnBnClickedCheckSample( int sampleID, BOOL checkSample )
{
	m_sampleMask[sampleID] = checkSample;
	
	NormalizedRGBDraw();
}

void CPropertyPageColorSetting::OnBnClickedZoomSampling()
{
	for( int i=0 ; i<ZOOM_X/ZOOM_K ; i++ )
		for( int j=0 ; j<ZOOM_Y/ZOOM_K ; j++ )
		{
			if( m_zoomMark[i][j] )
			{
				m_sampleData[m_radioSample].AddData( m_zoomImage[i][j] );
			}
		}

	m_sampleData[m_radioSample].m_paramRGBmin = std::max( 0, m_sampleData[m_radioSample].RGBMin()-20 );
	m_sampleData[m_radioSample].m_paramRGBmax = std::min( 255*3, m_sampleData[m_radioSample].RGBMax()+20 );

	m_pcolorpickSample[m_radioSample]->SetColor( m_sampleData[m_radioSample].GetColorREF() );
	
	NormalizedRGBDraw();
	SampleInfoDraw();
}


void CPropertyPageColorSetting::OnChangeEditSample0(){ OnChangeEditSample(0); }
void CPropertyPageColorSetting::OnChangeEditSample1(){ OnChangeEditSample(1); }
void CPropertyPageColorSetting::OnChangeEditSample2(){ OnChangeEditSample(2); }
void CPropertyPageColorSetting::OnChangeEditSample3(){ OnChangeEditSample(3); }
void CPropertyPageColorSetting::OnChangeEditSample4(){ OnChangeEditSample(4); }
void CPropertyPageColorSetting::OnChangeEditSample5(){ OnChangeEditSample(5); }
void CPropertyPageColorSetting::OnChangeEditSample6(){ OnChangeEditSample(6); }
void CPropertyPageColorSetting::OnChangeEditSample7(){ OnChangeEditSample(7); }
void CPropertyPageColorSetting::OnChangeEditSample( int sampleID )
{
	UpdateData(TRUE);
	ZoomInfoDraw();
	SampleInfoDraw();
}


void CPropertyPageColorSetting::OnBnClickedSampleClear()
{
	UpdateData(TRUE);
	
	m_sampleData[m_radioSample].Clear();
	m_pcolorpickSample[m_radioSample]->SetColor( m_sampleData[m_radioSample].GetColorREF() );
	//UpdateData(FALSE);
	
	SampleInfoDraw();
}


void CPropertyPageColorSetting::SampleInfoDraw()
{
	m_dcSampleInfo.SetBkMode( TRANSPARENT );
	m_dcSampleInfo.SetTextColor( RGB( 255,255,255 ) );
	m_dcSampleInfo.FillSolidRect( 0, 0, m_dcSampleInfo.Width(), m_dcSampleInfo.Height(), RGB(128,128,128));

	#define TEXT_HEIGHT 16
	
	CString info0, info1;
	info0.Format(_T("Sample-%d : "),m_radioSample );

	if( m_radioSample == 0 ) info0 += m_strSample0;
	if( m_radioSample == 1 ) info0 += m_strSample1;
	if( m_radioSample == 2 ) info0 += m_strSample2;
	if( m_radioSample == 3 ) info0 += m_strSample3;
	if( m_radioSample == 4 ) info0 += m_strSample4;
	if( m_radioSample == 5 ) info0 += m_strSample5;
	if( m_radioSample == 6 ) info0 += m_strSample6;
	if( m_radioSample == 7 ) info0 += m_strSample7;

	info1.Format(_T("%3ld samples [%03ld,%03ld] <%03ld, %03ld>)"),
		m_sampleData[m_radioSample].DataN(),
		m_sampleData[m_radioSample].RGBMin(),
		m_sampleData[m_radioSample].RGBMax(),
		m_sampleData[m_radioSample].m_paramRGBmin,
		m_sampleData[m_radioSample].m_paramRGBmax );

	CRect rectText = m_dcSampleInfo.GetRect() - m_dcSampleInfo.TopLeft();
	rectText.top = rectText.bottom-TEXT_HEIGHT;
	rectText.DeflateRect( 5, 0, 5, 0 );

	m_dcSampleInfo.DrawText( info0, rectText, DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	m_dcSampleInfo.DrawText( info1, rectText, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	/*
	DT_LEFT, DT_RIGHT, DT_CENTER
	DT_TOP, DT_VCENTER, DT_BOTTOM
	DT_SINGLELINE
	* DT_VCENTER need DT_SINGLELINE
	*/



	CRect rectGraph;
	rectGraph = m_dcSampleInfo.GetRect() - m_dcSampleInfo.TopLeft();
	rectGraph.DeflateRect(  SAMPLE_INFO_MARGIN_LEFT,
							SAMPLE_INFO_MARGIN_TOP,
							SAMPLE_INFO_MARGIN_RIGHT,
							SAMPLE_INFO_MARGIN_BOTTOM+TEXT_HEIGHT );

	
	COLORREF color = m_sampleData[m_radioSample].GetColorREF();
	double color_r = GetRValue(color);
	double color_g = GetGValue(color);
	double color_b = GetBValue(color);

	double sum = color_r+color_g+color_b;

	if( color_r+color_g+color_b == 0 )
		color_r = color_g = color_b = 1.0/3.0;
	else
	{
		color_r = color_r / sum;
		color_g = color_g / sum;
		color_b = color_b / sum;
	}


	int count[255*3+1];
	for( int c=0 ; c<255*3+1 ; c++ )
		count[c] = 0;
	
	for( int p=0 ; p<m_sampleData[m_radioSample].DataN() ; p++ )
	{
		COLORREF color = m_sampleData[m_radioSample].GetRGBData(p);

		int sampleR = GetRValue(color);
		int sampleG = GetGValue(color);
		int sampleB = GetBValue(color);

		int sampleP = sampleR+sampleG+sampleB;

		count[sampleP]++;
	}

	{
		CBrush brush, *pOldBrush;
		brush.CreateSolidBrush( RGB(192,192,192) );
		pOldBrush = (CBrush*)m_dcSampleInfo.SelectObject( &brush );
		
		CPen pen, *pOldPen;
		pen.CreatePen( PS_SOLID, 1, RGB(0,0,0) );
		pOldPen = (CPen*)m_dcSampleInfo.SelectObject( &pen );
		
		CRect rect = rectGraph;
		rect.InflateRect(1,1,1,2);

		m_dcSampleInfo.Rectangle( rect );
		
		m_dcSampleInfo.SelectObject( pOldPen );
		m_dcSampleInfo.SelectObject( pOldBrush );

	}

	double scaleK = rectGraph.Width() / (255.0*3.0);

	for( int i=0 ; i<255*3 ; i++ )
	{
		int r = (int)( color_r * i );
		int g = (int)( color_g * i );
		int b = (int)( color_b * i );

		r = std::min(r,255); r = std::max(r,0);
		g = std::min(g,255); g = std::max(g,0);
		b = std::min(b,255); b = std::max(b,0);

		int x = (int)( i*scaleK ) + rectGraph.left;

		if( i < m_sampleData[m_radioSample].m_paramRGBmin || i > m_sampleData[m_radioSample].m_paramRGBmax )
		{
			int thickness=1;
			for( int j=rectGraph.Height()/2-thickness ; j<=rectGraph.Height()/2+thickness ; j++ )
			{
				int y = rectGraph.bottom-j;
				m_dcSampleInfo.SetPixel( x, y, RGB(r,g,b) );
			}
		}
		else
		{
			if( m_bShowCameraImage || i == m_sampleData[m_radioSample].m_paramRGBmin || i == m_sampleData[m_radioSample].m_paramRGBmax )
			for( int j=0 ; j<=rectGraph.Height() ; j++ )
			{
				int y = rectGraph.bottom-j;
				m_dcSampleInfo.SetPixel( x, y, RGB(r,g,b) );
			}
		}

		for( int j=0 ; j<count[i]*3 && j<=rectGraph.Height() ; j++ )
		{
			int y = rectGraph.bottom-j;

			if( m_bColorMaskSample )
				m_dcSampleInfo.SetPixel( x, y, m_colorpickMaskSampleSelect.GetColor() );
			else
				m_dcSampleInfo.SetPixel( x, y, m_sampleData[m_radioSample].GetColorREF() );

		}

	}
/*
	{
		int x = rectGraph.left + (int)( m_patchParameterRGBmin*scaleK );
		
		for( int j=0 ; j<=rectGraph.Height() ; j++ )
		{
			int y = rectGraph.bottom-j;
			
			m_dcSampleInfo.SetPixel( x, y, RGB(255,0,0) );
		}

		int y=rectGraph.top;
		m_dcSampleInfo.SetPixel( x+0, y-2, RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x+0, y-1, RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x+0, y  , RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x+0, y+1, RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x+0, y+2, RGB(255,0,0) );

		m_dcSampleInfo.SetPixel( x+1, y-1, RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x+1, y  , RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x+1, y+1, RGB(255,0,0) );

		m_dcSampleInfo.SetPixel( x+2, y  , RGB(255,0,0) );
	}
	{
		int x = rectGraph.left + (int)( m_patchParameterRGBmax*scaleK );
		
		for( int j=0 ; j<=rectGraph.Height() ; j++ )
		{
			int y = rectGraph.bottom-j;
			
			m_dcSampleInfo.SetPixel( x, y, RGB(255,0,0) );
		}

		int y = rectGraph.bottom;
		m_dcSampleInfo.SetPixel( x-0, y-2, RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x-0, y-1, RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x-0, y  , RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x-0, y+1, RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x-0, y+2, RGB(255,0,0) );
		
		m_dcSampleInfo.SetPixel( x-1, y-1, RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x-1, y  , RGB(255,0,0) );
		m_dcSampleInfo.SetPixel( x-1, y+1, RGB(255,0,0) );
		
		m_dcSampleInfo.SetPixel( x-2, y  , RGB(255,0,0) );
	}
*/
	CBrush brush, *pOldBrush;
	brush.CreateSolidBrush( RGB(0,0,0) );
	pOldBrush = (CBrush*)m_dcSampleInfo.SelectObject( &brush );

	CPen pen, *pOldPen;
	pen.CreatePen( PS_SOLID, 1, RGB(255,0,0) );
	pOldPen = (CPen*)m_dcSampleInfo.SelectObject( &pen );


	m_dcSampleInfo.SelectObject( pOldPen );
	m_dcSampleInfo.SelectObject( pOldBrush );

	
	CClientDC dc(this);
	m_dcSampleInfo.BitBlt( &dc );
}


void CPropertyPageColorSetting::InitializeNormalizedRGB()
{
	// r,g,b -> x,y
	m_matColor.at<double>(0,0) = cos( M_PI*1/2 );
	m_matColor.at<double>(1,0) = sin( M_PI*1/2 );
	m_matColor.at<double>(2,0) = 1;
	
	m_matColor.at<double>(0,1) = cos( M_PI*7/6 );
	m_matColor.at<double>(1,1) = sin( M_PI*7/6 );
	m_matColor.at<double>(2,1) = 1;
	
	m_matColor.at<double>(0,2) = cos( -M_PI*1/6 );
	m_matColor.at<double>(1,2) = sin( -M_PI*1/6 );
	m_matColor.at<double>(2,2) = 1;
	
	m_matColori = m_matColor.inv();


/*
	double test =
	 m_matColor[0][0]*m_matColor[1][1]*m_matColor[2][2]
	+m_matColor[0][1]*m_matColor[1][2]*m_matColor[2][0]
	+m_matColor[0][2]*m_matColor[1][0]*m_matColor[2][1]
	-m_matColor[0][2]*m_matColor[1][1]*m_matColor[2][0]
	-m_matColor[0][1]*m_matColor[1][0]*m_matColor[2][2]
	-m_matColor[0][0]*m_matColor[1][2]*m_matColor[2][1];
*/

	for( int i=0 ; i<NORMALIZED_RGB_DATA_SIZE ; i++ )
	{
		for( int j=0 ; j<NORMALIZED_RGB_DATA_SIZE ; j++ )
		{
			m_bNormalizedRGBColor[i][j] = true;

			for( int k=0 ; k<8 ; k++ )
				m_NormalizedRGBMark[k][i][j] = false;

			// (x,y) ([-1.0, 1.0], [-1.0, 1.0])
			double x =  ((double)i - NORMALIZED_RGB_DATA_SIZE/2.0)/(NORMALIZED_RGB_DATA_SIZE/2.0);
			double y = -((double)j - NORMALIZED_RGB_DATA_SIZE/2.0)/(NORMALIZED_RGB_DATA_SIZE/2.0);
			
			double gradation_d = 0.05;
			if( x*x + y*y < 1.0 + gradation_d )
			{
				m_matXY.at<double>(0,0) = x;
				m_matXY.at<double>(1,0) = y;
				m_matXY.at<double>(2,0) = 1;
				
				m_matRGB = m_matColori * m_matXY;
				
				double r = m_matRGB.at<double>(0,0) * 255;
				double g = m_matRGB.at<double>(1,0) * 255;
				double b = m_matRGB.at<double>(2,0) * 255;
				
 				if( r<0 || g<0 || b<0 || r>255 || g>255 || b>255 )
 				{
					r = r*0.75;
					g = g*0.75;
					b = b*0.75;
					
					r = (std::min)(r,255.0); r = (std::max)(r,0.0);
					g = (std::min)(g,255.0); g = (std::max)(g,0.0);
					b = (std::min)(b,255.0); b = (std::max)(b,0.0);
					m_bNormalizedRGBColor[i][j] = false;
 				}

				if( x*x + y*y > 1.0 - gradation_d )
				{
					r = r * (1.0 + gradation_d - (x*x + y*y)) / (gradation_d*2);
					g = g * (1.0 + gradation_d - (x*x + y*y)) / (gradation_d*2);
					b = b * (1.0 + gradation_d - (x*x + y*y)) / (gradation_d*2);
				}
				
				m_NormalizedRGBColor[i][j] = RGB((int)r,(int)g,(int)b);
			}
			else
			{
				m_NormalizedRGBColor[i][j] = RGB(0,0,0);
			}
		}
	}
}


void CPropertyPageColorSetting::NormalizedRGBDrawPoint( CPoint point )
{
	int i = point.x * NORMALIZED_RGB_DATA_SIZE / NORMALIZED_RGB_DRAW_SIZE;
	int j = point.y * NORMALIZED_RGB_DATA_SIZE / NORMALIZED_RGB_DRAW_SIZE;
	
	{
		COLORREF color = m_NormalizedRGBColor[i][j];
		
		int r = GetRValue( color );
		int g = GetGValue( color );
		int b = GetBValue( color );


		if( m_bNormalizedRGBColor[i][j] == false )
		{
			m_dcNormalizedRGB.SetPixel( point.x, point.y, color );
			return;
		}

		if( !m_bShowCameraImage )
		{
			color=RGB(0,0,0);
		}
		
		
		for( int p=0 ; p<8 ; p++ )
		{
			if( m_patchMask || m_radioPatch==p )
			{
				unsigned char l_mask = (0x01 << p);
				
				COLORREF patch_color = m_pLookUpTable->GetColor(p);
				int patch_r = GetRValue( patch_color );
				int patch_g = GetGValue( patch_color );
				int patch_b = GetBValue( patch_color );
				
				double k = 0;

				if( r+g+b > 0 )
					k = (double)(patch_r+patch_g+patch_b)/(r+g+b);
				
				int matched_r = (int)(k*r);
				int matched_g = (int)(k*g);
				int matched_b = (int)(k*b);
				
				matched_r = std::min(matched_r, 255);
				matched_g = std::min(matched_g, 255);
				matched_b = std::min(matched_b, 255);
				
				if( m_radioPatch == p )
				{
					if( l_mask & m_pLookUpTable->GetLUTData( matched_r, matched_g, matched_b ) )
					{
						if( m_bColorMaskPatch )
							color = m_colorpickMaskPatchSelect.GetColor();
						else
							color = m_pLookUpTable->GetLUTColor( l_mask );
					}
				}
				else
				{
					if( (m_patchMask&l_mask) & m_pLookUpTable->GetLUTData( matched_r, matched_g, matched_b ) )
					{
						if( m_bColorMaskPatch )
							color = m_colorpickMaskPatchCheck.GetColor();
						else
							color = m_pLookUpTable->GetLUTColor( l_mask );
					}
				}
			}
		}

		m_dcNormalizedRGB.SetPixel( point.x, point.y, color );

	}
}

void CPropertyPageColorSetting::NormalizedRGBDraw( bool bBitblt )
{
	for( int pi=0 ; pi<NORMALIZED_RGB_DRAW_SIZE ; pi++ )
		for( int pj=0 ; pj<NORMALIZED_RGB_DRAW_SIZE ; pj++ )
		{
			NormalizedRGBDrawPoint( CPoint(pi,pj) );
		}

	
	for( int pi=0 ; pi<NORMALIZED_RGB_DRAW_SIZE ; pi++ )
		for( int pj=0 ; pj<NORMALIZED_RGB_DRAW_SIZE ; pj++ )
		{
			int i = pi * NORMALIZED_RGB_DATA_SIZE / NORMALIZED_RGB_DRAW_SIZE;
			int j = pj * NORMALIZED_RGB_DATA_SIZE / NORMALIZED_RGB_DRAW_SIZE;

			if( m_NormalizedRGBMark[m_radioSample][i][j] )
			{
				m_dcNormalizedRGB.SelectStockObject( NULL_BRUSH );				
				CPen pen, *pOldPen;
				//pen.CreatePen( PS_SOLID, 1, m_colorpickKeySample.GetColor() );
				pen.CreatePen( PS_SOLID, 1, RGB(255,0,0) );
				pOldPen = (CPen*)m_dcNormalizedRGB.SelectObject( &pen );
				
				double x = (double)i*NORMALIZED_RGB_DRAW_SIZE/NORMALIZED_RGB_DATA_SIZE;
				double y = (double)j*NORMALIZED_RGB_DRAW_SIZE/NORMALIZED_RGB_DATA_SIZE;
				
				double size = m_sampleData[m_radioSample].m_paramKeySampleSize * NORMALIZED_RGB_DRAW_SIZE;
				m_dcNormalizedRGB.Ellipse(
					(int)(pi-size),
					(int)(pj-size),
					(int)(pi+size),
					(int)(pj+size) );
				
				m_dcNormalizedRGB.SelectObject( pOldPen );
			}
		}

	for( int radioSample=0 ; radioSample<8 ; radioSample++ )
	{
		if( m_sampleMask[radioSample] || m_radioSample == radioSample )
		{
			for( int i=0 ; i<m_sampleData[radioSample].DataN() ; i++ )
			{
				COLORREF color = m_sampleData[radioSample].GetRGBData(i);
				
				int r = GetRValue( color );
				int g = GetGValue( color );
				int b = GetBValue( color );
				
				int sum = r+g+b;
				
				double nr=0,ng=0,nb=0;
				if( sum != 0 )
				{
					nr = (double)r/sum;
					ng = (double)g/sum;
					nb = (double)b/sum;
				}
				
				m_matRGB.at<double>(0,0) = nr;
				m_matRGB.at<double>(1,0) = ng;
				m_matRGB.at<double>(2,0) = nb;
				m_matXY = m_matColor * m_matRGB;
				
				int pi =  (int)(m_matXY.at<double>(0,0) * (NORMALIZED_RGB_DRAW_SIZE/2.0) + (NORMALIZED_RGB_DRAW_SIZE/2.0));
				int pj = -(int)(m_matXY.at<double>(1,0) * (NORMALIZED_RGB_DRAW_SIZE/2.0) - (NORMALIZED_RGB_DRAW_SIZE/2.0));

				
				if( m_bColorMaskSample )
				{
					if( m_radioSample == radioSample )
					{
						color = m_colorpickMaskSampleSelect.GetColor();
					}
					else
					{
						color = m_colorpickMaskSampleCheck.GetColor();
					}
				}
				

				m_dcNormalizedRGB.SetPixel( pi, pj, color );
			}
		}
	}

	CPointDouble posR = CPointDouble( 1+cos( M_PI*1/2), 1-sin( M_PI*1/2) ) * (NORMALIZED_RGB_DRAW_SIZE/2.0);
	CPointDouble posG = CPointDouble( 1+cos( M_PI*7/6), 1-sin( M_PI*7/6) ) * (NORMALIZED_RGB_DRAW_SIZE/2.0);
	CPointDouble posB = CPointDouble( 1+cos(-M_PI*1/6), 1-sin(-M_PI*1/6) ) * (NORMALIZED_RGB_DRAW_SIZE/2.0);


	m_dcNormalizedRGB.SelectPen( RGB(255,0,0) );
	m_dcNormalizedRGB.MoveTo( NORMALIZED_RGB_DRAW_SIZE/2, NORMALIZED_RGB_DRAW_SIZE/2 );
	m_dcNormalizedRGB.LineTo( (int)posR.x, (int)posR.y );

	m_dcNormalizedRGB.SelectPen( RGB(0,255,0) );
	m_dcNormalizedRGB.MoveTo( NORMALIZED_RGB_DRAW_SIZE/2, NORMALIZED_RGB_DRAW_SIZE/2 );
	m_dcNormalizedRGB.LineTo( (int)posG.x, (int)posG.y );

	m_dcNormalizedRGB.SelectPen( RGB(0,0,255) );
	m_dcNormalizedRGB.MoveTo( NORMALIZED_RGB_DRAW_SIZE/2, NORMALIZED_RGB_DRAW_SIZE/2 );
	m_dcNormalizedRGB.LineTo( (int)posB.x, (int)posB.y );

	m_dcNormalizedRGB.SetPixel( NORMALIZED_RGB_DRAW_SIZE/2, NORMALIZED_RGB_DRAW_SIZE/2, RGB(255,255,255) );
	
	
	if( bBitblt )
	{
		CClientDC dc(this);
		m_dcNormalizedRGB.BitBlt( &dc );
	}
}

void CPropertyPageColorSetting::OnBnClickedCheckColorSample()
{
	UpdateData(TRUE);

	NormalizedRGBDraw();
	SampleInfoDraw();;
}

void CPropertyPageColorSetting::OnBnClickedCheckPatch0(){ UpdateData(TRUE); OnBnClickedCheckPatch( 0, m_checkPatch0 ); }
void CPropertyPageColorSetting::OnBnClickedCheckPatch1(){ UpdateData(TRUE); OnBnClickedCheckPatch( 1, m_checkPatch1 ); }
void CPropertyPageColorSetting::OnBnClickedCheckPatch2(){ UpdateData(TRUE); OnBnClickedCheckPatch( 2, m_checkPatch2 ); }
void CPropertyPageColorSetting::OnBnClickedCheckPatch3(){ UpdateData(TRUE); OnBnClickedCheckPatch( 3, m_checkPatch3 ); }
void CPropertyPageColorSetting::OnBnClickedCheckPatch4(){ UpdateData(TRUE); OnBnClickedCheckPatch( 4, m_checkPatch4 ); }
void CPropertyPageColorSetting::OnBnClickedCheckPatch5(){ UpdateData(TRUE); OnBnClickedCheckPatch( 5, m_checkPatch5 ); }
void CPropertyPageColorSetting::OnBnClickedCheckPatch6(){ UpdateData(TRUE); OnBnClickedCheckPatch( 6, m_checkPatch6 ); }
void CPropertyPageColorSetting::OnBnClickedCheckPatch7(){ UpdateData(TRUE); OnBnClickedCheckPatch( 7, m_checkPatch7 ); }

void CPropertyPageColorSetting::OnBnClickedCheckPatch( int patchID, BOOL checkPatch )
{
	unsigned char mask = (unsigned char)(checkPatch<<patchID);
	unsigned char unmask = (0xFF - (unsigned char)(1<<patchID));

	EnterCriticalSection(&m_critColorSetting);
	m_patchMask &= unmask;
	m_patchMask |= mask;
	LeaveCriticalSection(&m_critColorSetting);

	NormalizedRGBDraw();
}

void CPropertyPageColorSetting::OnBnClickedGeneratePatchColor()
{
	OnBnClickedPatchClear();

	if( m_sampleData[m_radioSample].m_paramKeySampleN <= 0 )
	{
		return;
	}

	EnterCriticalSection(&m_critColorSetting);

	m_bGeneratePatchColor = true;

	//OnBnClickedPatchClear();

	BeginWaitCursor();

	long cR=0;
	long cG=0;
	long cB=0;
	long count=0;

	for( int i=0 ; i<NORMALIZED_RGB_DATA_SIZE ; i++ )
	{
		for( int j=0 ; j<NORMALIZED_RGB_DATA_SIZE ; j++ )
		{
			if( m_NormalizedRGBMark[m_radioSample][i][j] )
			{
				int sR = GetRValue( m_NormalizedRGBColor[i][j] );
				int sG = GetGValue( m_NormalizedRGBColor[i][j] );
				int sB = GetBValue( m_NormalizedRGBColor[i][j] );
				
				double RGBsum = sR+sG+sB;
				
				double nR = sR/RGBsum;
				double nG = sG/RGBsum;
				double nB = sB/RGBsum;
				
				
				int sum;
				for( int r=0 ; r<256 ; r++ )
				{
					for( int g=0 ; g<256 ; g++ )
					{
						for( int b=0 ; b<256 ; b++ )
						{
							if( m_pLookUpTable->GetData( m_radioPatch, r,g,b ) )
								continue;
							
							sum = r+g+b;
							
							if( m_sampleData[m_radioSample].m_paramRGBmin <= sum && sum <= m_sampleData[m_radioSample].m_paramRGBmax )
							{
								double dR = 0;
								double dG = 0;
								double dB = 0;

								if( sum > 0 )
								{
									dR = (nR - (double)r/sum);
									dG = (nG - (double)g/sum);
									dB = (nB - (double)b/sum);
								}
								
								// 2.5 : Normalized RGB Plane <-> RGB 3D Space scale parameter
								
								if( dR*dR+dG*dG+dB*dB <= m_sampleData[m_radioSample].m_paramKeySampleSize*m_sampleData[m_radioSample].m_paramKeySampleSize*2.5 )
								{
									m_pLookUpTable->SetData( m_radioPatch, r, g, b, true );

									cR+=r;
									cG+=g;
									cB+=b;
									count++;
								}
							}
						}
					}
				}
			}
		}


		if( i%4 == 0 )
		{
			NormalizedRGBDraw(false);

			int draw_p = i;

				CBrush brush, *pOldBrush;
				brush.CreateSolidBrush( RGB(0,0,0) );
				pOldBrush = (CBrush*)m_dcNormalizedRGB.SelectObject( &brush );
		
				CPen pen, *pOldPen;
				pen.CreatePen( PS_SOLID, 1, RGB(0,0,0) );
				pOldPen = (CPen*)m_dcNormalizedRGB.SelectObject( &pen );
		
			m_dcNormalizedRGB.Rectangle( draw_p, NORMALIZED_RGB_DRAW_SIZE, NORMALIZED_RGB_DRAW_SIZE, 0 );


				m_dcNormalizedRGB.SelectObject( pOldPen );
				m_dcNormalizedRGB.SelectObject( pOldBrush );


			CClientDC dc(this);
			m_dcNormalizedRGB.BitBlt(&dc);
		}

	}

	if( count > 0 )
	{
		cR /= count;
		cG /= count;
		cB /= count;
	}

	m_pLookUpTable->SetColor( m_radioPatch, cR, cG, cB );

	m_pcolorpickPatch[m_radioPatch]->SetColor( RGB(cR,cG,cB) );
	

	EndWaitCursor();

	NormalizedRGBDraw();

	m_bGeneratePatchColor = false;

	LeaveCriticalSection(&m_critColorSetting);
}

void CPropertyPageColorSetting::OnSetfocusEditPatch0(){ SelectPatch( 0 ); } 
void CPropertyPageColorSetting::OnSetfocusEditPatch1(){ SelectPatch( 1 ); } 
void CPropertyPageColorSetting::OnSetfocusEditPatch2(){ SelectPatch( 2 ); } 
void CPropertyPageColorSetting::OnSetfocusEditPatch3(){ SelectPatch( 3 ); } 
void CPropertyPageColorSetting::OnSetfocusEditPatch4(){ SelectPatch( 4 ); } 
void CPropertyPageColorSetting::OnSetfocusEditPatch5(){ SelectPatch( 5 ); } 
void CPropertyPageColorSetting::OnSetfocusEditPatch6(){ SelectPatch( 6 ); } 
void CPropertyPageColorSetting::OnSetfocusEditPatch7(){ SelectPatch( 7 ); } 


void CPropertyPageColorSetting::SelectPatch(int p)
{
	EnterCriticalSection(&m_critColorSetting);
	m_radioPatch = p;
	LeaveCriticalSection(&m_critColorSetting);

	SetfocusEditPatch();
	
	UpdateData(TRUE);
	NormalizedRGBDraw();
}

void CPropertyPageColorSetting::SetfocusEditPatch()
{
	UpdateData(TRUE);
	
	COLORREF colorTextDeselect = RGB(0,0,0);
	COLORREF colorBKDeselect = GetSysColor( COLOR_BTNFACE ) ;

	COLORREF colorTextSelect = RGB(0,0,0);
	COLORREF colorBKSelect = RGB(128,128,255);

	m_ctrlPatch0.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlPatch1.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlPatch2.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlPatch3.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlPatch4.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlPatch5.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlPatch6.SetColor( colorTextDeselect, colorBKDeselect );	
	m_ctrlPatch7.SetColor( colorTextDeselect, colorBKDeselect );	
	
	if( m_radioPatch == 0 ) m_ctrlPatch0.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioPatch == 1 ) m_ctrlPatch1.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioPatch == 2 ) m_ctrlPatch2.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioPatch == 3 ) m_ctrlPatch3.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioPatch == 4 ) m_ctrlPatch4.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioPatch == 5 ) m_ctrlPatch5.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioPatch == 6 ) m_ctrlPatch6.SetColor( colorTextSelect, colorBKSelect );	
	if( m_radioPatch == 7 ) m_ctrlPatch7.SetColor( colorTextSelect, colorBKSelect );	
	
	
	m_ctrlPatch0.Invalidate(FALSE);	
	m_ctrlPatch1.Invalidate(FALSE);	
	m_ctrlPatch2.Invalidate(FALSE);	
	m_ctrlPatch3.Invalidate(FALSE);	
	m_ctrlPatch4.Invalidate(FALSE);	
	m_ctrlPatch5.Invalidate(FALSE);	
	m_ctrlPatch6.Invalidate(FALSE);	
	m_ctrlPatch7.Invalidate(FALSE);
}

void CPropertyPageColorSetting::OnBnClickedPatchClear()
{
	EnterCriticalSection(&m_critColorSetting);
	m_pLookUpTable->ClearLUT(m_radioPatch);
	LeaveCriticalSection(&m_critColorSetting);

	m_pcolorpickPatch[m_radioPatch]->SetColor( RGB(0,0,0) );
//	UpdateData(FALSE);	

	NormalizedRGBDraw();
}


void CPropertyPageColorSetting::OnBnClickedCheckColorPatch()
{
	EnterCriticalSection(&m_critColorSetting);
	UpdateData(TRUE);
	LeaveCriticalSection(&m_critColorSetting);

	NormalizedRGBDraw();
	SampleInfoDraw();;
}


void CPropertyPageColorSetting::OnBnClickedCheckShowMasking()
{
	EnterCriticalSection(&m_critColorSetting);

	UpdateData(TRUE);

	LeaveCriticalSection(&m_critColorSetting);
}


void CPropertyPageColorSetting::OnBnClickedOpenPatch()
{
	UpdateData(TRUE);

	BeginWaitCursor();
	
	TCHAR szFilter[] = _T("Patch Look Up Table File(*.PCH)|*.PCH|All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("default"), _T("default"), NULL, szFilter);
	
	if( dlg.DoModal() == IDOK )
	{
		RestoreWaitCursor();
		OpenFile( dlg.GetPathName() );
	}

	EndWaitCursor();
}


void CPropertyPageColorSetting::OnBnClickedSavePatch()
{
	UpdateData(TRUE);

	BeginWaitCursor();

	TCHAR szFilter[] = _T("Patch Look Up Table File(*.PCH)|*.PCH|All Files(*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("default"), _T("default"), NULL, szFilter);
	
	if( dlg.DoModal() == IDOK )
	{
		RestoreWaitCursor();
		SaveFile( dlg.GetPathName() );
	}

	EndWaitCursor();	
}

void CPropertyPageColorSetting::OpenFile(CString filename)
{
	CFile file;

	m_strFileName = filename;
	
	if( file.Open(m_strFileName, CFile::modeRead ) == FALSE )
	{
		AfxMessageBox(_T("Failed to open the file. (CPropertyPageColorSetting::OpenFile)"));
		return;
	}
	
	CArchive ar( &file, CArchive::load );
	
	m_pLookUpTable->OpenFile( ar );
	
	ar.Close();
	file.Close();
	
	UpdateData(FALSE);

	Invalidate(FALSE);

	for( int i=0 ; i<8 ; i++ )
	{
		m_pcolorpickPatch[i]->SetColor( m_pLookUpTable->GetColor(i) );
	}

}

void CPropertyPageColorSetting::SaveFile(CString filename)
{
	CFile file;
	
	m_strFileName = filename;

	file.Open( m_strFileName, CFile::modeCreate | CFile::modeWrite );
	CArchive ar( &file, CArchive::store );
	
	m_pLookUpTable->SaveFile( ar );
	
	ar.Close();
	file.Close();

	UpdateData(FALSE);
}

void CPropertyPageColorSetting::OnDrawDualSliderKeySampleN(NMHDR *pNMHDR, LRESULT *pResult)
{
	//NormalizedRGBDraw();
}

void CPropertyPageColorSetting::OnDrawDualSliderKeySampleSize(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_sampleData[m_radioSample].m_paramKeySampleSize = m_sliderKeySampleSize.GetValue();

	NormalizedRGBDraw();
}

void CPropertyPageColorSetting::OnBnClickedGenerateKeySample()
{
	UpdateData(TRUE);

	struct normalized_rgb_xy
	{
		double x;
		double y;
	} new_data;

	std::vector< struct normalized_rgb_xy > m_data;

	int m_dataN = m_sampleData[m_radioSample].DataN();

	if( m_dataN <= 0 )
		return;
	
	double mu[MAX_KEY_SAMPLE_N][2];
	double sigma[MAX_KEY_SAMPLE_N][2][2];
	int m_calcN = m_sampleData[m_radioSample].m_paramKeySampleN;

	ZeroMemory( mu, sizeof(mu) );
	ZeroMemory( sigma, sizeof(sigma) );

	for( int i=0 ; i<m_dataN; i++ )
	{
		COLORREF color = m_sampleData[m_radioSample].GetRGBData(i);

		int r = GetRValue( color );
		int g = GetGValue( color );
		int b = GetBValue( color );
		
		int sum = r+g+b;
		
		double nr=0,ng=0,nb=0;
		if( sum != 0 )
		{
			nr = (double)r/sum;
			ng = (double)g/sum;
			nb = (double)b/sum;
		}
		
		m_matRGB.at<double>(0,0) = nr;
		m_matRGB.at<double>(1,0) = ng;
		m_matRGB.at<double>(2,0) = nb;
		m_matXY = m_matColor * m_matRGB;
		
		
		new_data.x =  (m_matXY.at<double>(0,0) + 1.0) * (NORMALIZED_RGB_DATA_SIZE/2);
		new_data.y =  (1.0 - m_matXY.at<double>(1,0)) * (NORMALIZED_RGB_DATA_SIZE/2);

		mu[0][0] += new_data.x;
		mu[0][1] += new_data.y;

		m_data.push_back( new_data );
	}

	mu[0][0] /= m_dataN;
	mu[0][1] /= m_dataN;

	for( int i=0 ; i<m_dataN; i++ )
	{
		sigma[0][0][0] += (m_data[i].x - mu[0][0])*(m_data[i].x - mu[0][0]);
		sigma[0][1][1] += (m_data[i].y - mu[0][1])*(m_data[i].y - mu[0][1]);
	}

	sigma[0][0][0] /= m_dataN;
	sigma[0][0][0] = sqrt( sigma[0][0][0] );
	sigma[0][1][1] /= m_dataN;
	sigma[0][1][1] = sqrt( sigma[0][1][1] );


	double p[MAX_KEY_SAMPLE_N];


	int key_i=0;
	for( int i=0 ; i<NORMALIZED_RGB_DATA_SIZE ; i++ )
	{
		for( int j=0 ; j<NORMALIZED_RGB_DATA_SIZE ; j++ )
		{
			if( m_NormalizedRGBMark[m_radioSample][i][j] == true )
			{
				mu[key_i][0] = (double)i;
				mu[key_i][1] = (double)j;

				key_i++;
			}
		}
	}

	for( int i = key_i ; i<(int)m_sampleData[m_radioSample].m_paramKeySampleN ; i++ )
	{
		mu[i][0] = mu[0][0] + i;
		mu[i][1] = mu[0][1] + i;
	}
	
	if( m_calcN == 0 )
	{
		m_calcN = 1;
	}

	for( int j=0 ; j<m_calcN ; j++ )
	{
		sigma[j][0][0] = sigma[0][0][0];
		sigma[j][1][1] = sigma[0][1][1];
		p[j] = 1.0/(double)m_calcN;
	}
	

	std::vector<double> px;
	std::vector<double> cond_prob_xj[MAX_KEY_SAMPLE_N];
	std::vector<double> cond_prob_jx[MAX_KEY_SAMPLE_N];

	for( unsigned int i=0 ; i<m_data.size() ; i++ )
	{
		px.push_back( 0 );

		for( int j=0 ; j<m_calcN ; j++ )
		{
			cond_prob_xj[j].push_back( 0 );
			cond_prob_jx[j].push_back( 0 );
		}
	}

	//double cond_prob_xj[MAX_KEY_SAMPLE_N][SAMPLE_PIXEL_MAX_N];
	//double cond_prob_jx[MAX_KEY_SAMPLE_N][SAMPLE_PIXEL_MAX_N];

	for( int k=0 ; k<100 ; k++ )
	{
		double sum_cond_prob_jx[MAX_KEY_SAMPLE_N];
		double temp_cond_prob_jx[MAX_KEY_SAMPLE_N][2];
		ZeroMemory( sum_cond_prob_jx, sizeof(sum_cond_prob_jx) );
		ZeroMemory( temp_cond_prob_jx, sizeof(temp_cond_prob_jx) );
		
		for( int i=0 ; i<m_dataN ; i++ )
		{
			double x[2];
			x[0] = m_data[i].x;
			x[1] = m_data[i].y;
			
			px[i] = 0;
			for( int j=0 ; j<m_calcN ; j++ )
			{  //[2.77]

				double c0 = (x[0] - mu[j][0])*(x[0] - mu[j][0])+(x[1] - mu[j][1])*(x[1] - mu[j][1]);
				double c1 = (2.0 * sigma[j][0][0]*sigma[j][0][0] );

				//double check = - ((x[0] - mu[j][0])*(x[0] - mu[j][0])+(x[1] - mu[j][1])*(x[1] - mu[j][1]))
				//	/ (2.0 * sigma[j][0][0]*sigma[j][0][0] );
				
				//double check2 = (2.0 * M_PI * sigma[j][0][0]*sigma[j][0][0]);

				cond_prob_xj[j][i] = 
					exp(- ((x[0] - mu[j][0])*(x[0] - mu[j][0])+(x[1] - mu[j][1])*(x[1] - mu[j][1]))
					/ (2.0 * sigma[j][0][0]*sigma[j][0][0])
					)
					/ (2.0 * M_PI * sigma[j][0][0]*sigma[j][0][0]);

				if( cond_prob_xj[j][i] == 0 )
					cond_prob_xj[j][i] = 0.0001;

				px[i] += cond_prob_xj[j][i] * p[j]; //[2.71]
			}
			
			for( int j=0 ; j<m_calcN ; j++ ) //[2.75]
				cond_prob_jx[j][i] = cond_prob_xj[j][i] * p[j] / px[i];
			
			for( int j=0 ; j<m_calcN ; j++ )
			{
				sum_cond_prob_jx[j] += cond_prob_jx[j][i];
				temp_cond_prob_jx[j][0] += cond_prob_jx[j][i] * x[0];
				temp_cond_prob_jx[j][1] += cond_prob_jx[j][i] * x[1];
			}
		}
		
		double newmu[MAX_KEY_SAMPLE_N][2];
		for( int j=0 ; j<m_calcN ; j++ )
		{ //[2.96]
			mu[j][0] = newmu[j][0] = temp_cond_prob_jx[j][0] / sum_cond_prob_jx[j];
			mu[j][1] = newmu[j][1] = temp_cond_prob_jx[j][1] / sum_cond_prob_jx[j];
		}
		
		double num_cond_prob_jx[MAX_KEY_SAMPLE_N];
		ZeroMemory( num_cond_prob_jx, sizeof(num_cond_prob_jx) );
		
		for( int i=0 ; i<m_dataN ; i++ )
		{
			double x[2];
			x[0] = m_data[i].x;
			x[1] = m_data[i].y;
			
			for( int j=0 ; j<m_calcN ; j++ )
				num_cond_prob_jx[j] += cond_prob_jx[j][i] * ( (x[0]-mu[j][0])*(x[0]-mu[j][0]) + (x[1]-mu[j][1])*(x[1]-mu[j][1]) );
		}
		
		double newsigma[MAX_KEY_SAMPLE_N][2][2];
		ZeroMemory( newsigma, sizeof(newsigma) );
		
		for( int j=0 ; j<m_calcN ; j++ )
		{ //[2.97]
			sigma[j][0][0] = newsigma[j][0][0] = sqrt( num_cond_prob_jx[j] / (2 * sum_cond_prob_jx[j]));
			sigma[j][0][1] = newsigma[j][0][1] = sqrt( num_cond_prob_jx[j] / (2 * sum_cond_prob_jx[j]));
			sigma[j][1][0] = newsigma[j][1][0] = sqrt( num_cond_prob_jx[j] / (2 * sum_cond_prob_jx[j]));
			sigma[j][1][1] = newsigma[j][1][1] = sqrt( num_cond_prob_jx[j] / (2 * sum_cond_prob_jx[j]));
		}
		
		for( int j=0 ; j<m_calcN ; j++ )
			p[j] = sum_cond_prob_jx[j] / m_dataN; //[2.98]
	}	




	//ClearNormalizedRGB();
	for( int i=0 ; i<NORMALIZED_RGB_DATA_SIZE ; i++ )
		for( int j=0 ; j<NORMALIZED_RGB_DATA_SIZE ; j++ )
		{
			m_NormalizedRGBMark[m_radioSample][i][j] = false;
		}


	NormalizedRGBDraw();

	m_sampleData[m_radioSample].m_paramKeySampleN = 0;
	m_sliderKeySampleN.SetValue( 0 );





	double sqrt_sigma_avg=0;
	for( int i=0 ; i<m_calcN ; i++ )
	{
		int x = (int)mu[i][0];
		int y = (int)mu[i][1];

		if( m_NormalizedRGBMark[m_radioSample][x][y] == false )
		{
			m_NormalizedRGBMark[m_radioSample][x][y] = true;
			m_sampleData[m_radioSample].m_paramKeySampleN++;
		}
		
		sqrt_sigma_avg += sqrt(sigma[0][0][0]);
	}


	sqrt_sigma_avg /= m_calcN;

	m_sampleData[m_radioSample].m_paramKeySampleSize = sqrt_sigma_avg/20.0;

	m_sampleData[m_radioSample].m_paramKeySampleSize = ((int)(m_sampleData[m_radioSample].m_paramKeySampleSize*100))/100.0;

	m_sampleData[m_radioSample].m_paramKeySampleSize = std::min( m_sampleData[m_radioSample].m_paramKeySampleSize, 0.2 );
	m_sampleData[m_radioSample].m_paramKeySampleSize = std::max( m_sampleData[m_radioSample].m_paramKeySampleSize, 0.01 );

	m_sliderKeySampleSize.SetValue( m_sampleData[m_radioSample].m_paramKeySampleSize );
	m_sliderKeySampleN.SetValue( m_sampleData[m_radioSample].m_paramKeySampleN );

	NormalizedRGBDraw();
}