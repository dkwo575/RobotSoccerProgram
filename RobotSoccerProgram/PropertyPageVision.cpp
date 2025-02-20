// PropertyPageVision.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "PropertyPageVision.h"
#include "afxdialogex.h"


// CPropertyPageVision dialog

IMPLEMENT_DYNAMIC(CPropertyPageVision, CPropertyPageRobotSoccer)

CPropertyPageVision::CPropertyPageVision()
	: CPropertyPageRobotSoccer(CPropertyPageVision::IDD)
	, m_bShowCameraImage(TRUE)
	, m_bMasking(FALSE)
	, m_bFlatImage(FALSE)
	, m_bFlatImage_ball(FALSE)
	, m_bRevisionImage(FALSE)
	, m_bRevisionImage_ball(FALSE)
	, m_bCameraPause(FALSE)
	, m_strFileName(_T(""))
	, m_bRobotAll(FALSE)
	, m_bRobot01(FALSE)
	, m_bRobot02(FALSE)
	, m_bRobot03(FALSE)
	, m_bRobot04(FALSE)
	, m_bRobot05(FALSE)
	, m_bRobot06(FALSE)
	, m_bRobot07(FALSE)
	, m_bRobot08(FALSE)
	, m_bRobot09(FALSE)
	, m_bRobot10(FALSE)
	, m_bRobot11(FALSE)
	, m_bProcessingArea(FALSE)
{
	m_VisionTest.count = 0;

	InitializeCriticalSection(&m_critVision);
}

CPropertyPageVision::~CPropertyPageVision()
{
	DeleteCriticalSection(&m_critVision);
}

void CPropertyPageVision::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageRobotSoccer::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_BACKGROUND, m_bShowCameraImage);
	//DDX_Control(pDX, IDC_PROGRESS_SLIDER_REVISION_K, m_sliderRevisionK);
	//DDX_Control(pDX, IDC_PROGRESS_SLIDER_REVISION_ZOOM, m_sliderRevisionZoom);
	DDX_Check(pDX, IDC_CHECK_FLAT_IMAGE, m_bFlatImage);
	DDX_Check(pDX, IDC_CHECK_REVISION_IMAGE, m_bRevisionImage);
	DDX_Check(pDX, IDC_CHECK_CAMERA_PAUSE, m_bCameraPause);
	DDX_Check(pDX, IDC_CHECK_COLOR_MASKING, m_bMasking);
	DDX_Control(pDX, IDC_COLOR_PICK_MASK, m_colorpickMask);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_PATCH_DIRECTION, m_sliderPatchDirection);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
	DDX_Check(pDX, IDC_CHECK_ROBOT_ALL, m_bRobotAll);
	DDX_Check(pDX, IDC_CHECK_ROBOT01, m_bRobot01);
	DDX_Check(pDX, IDC_CHECK_ROBOT02, m_bRobot02);
	DDX_Check(pDX, IDC_CHECK_ROBOT03, m_bRobot03);
	DDX_Check(pDX, IDC_CHECK_ROBOT04, m_bRobot04);
	DDX_Check(pDX, IDC_CHECK_ROBOT05, m_bRobot05);
	DDX_Check(pDX, IDC_CHECK_ROBOT06, m_bRobot06);
	DDX_Check(pDX, IDC_CHECK_ROBOT07, m_bRobot07);
	DDX_Check(pDX, IDC_CHECK_ROBOT08, m_bRobot08);
	DDX_Check(pDX, IDC_CHECK_ROBOT09, m_bRobot09);
	DDX_Check(pDX, IDC_CHECK_ROBOT10, m_bRobot10);
	DDX_Check(pDX, IDC_CHECK_ROBOT11, m_bRobot11);
	DDX_Check(pDX, IDC_CHECK_PROCESSING_AREA, m_bProcessingArea);
	DDX_Check(pDX, IDC_CHECK_FLAT_IMAGE2, m_bFlatImage_ball);
	DDX_Check(pDX, IDC_CHECK_REVISION_IMAGE2, m_bRevisionImage_ball);
}


BEGIN_MESSAGE_MAP(CPropertyPageVision, CPropertyPageRobotSoccer)
	ON_BN_CLICKED(IDC_CHECK_BACKGROUND, &CPropertyPageVision::OnBnClickedCheckBackground)
	ON_BN_CLICKED(IDC_CHECK_FLAT_IMAGE, &CPropertyPageVision::OnBnClickedCheckFlatImage)
	ON_BN_CLICKED(IDC_CHECK_REVISION_IMAGE, &CPropertyPageVision::OnBnClickedCheckRevisionImage)
	ON_BN_CLICKED(IDC_CHECK_CAMERA_PAUSE, &CPropertyPageVision::OnBnClickedCheckCameraPause)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_COLOR_MASKING, &CPropertyPageVision::OnBnClickedCheckColorMasking)
	ON_BN_CLICKED(IDC_OPEN_VISION, &CPropertyPageVision::OnBnClickedOpenVision)
	ON_BN_CLICKED(IDC_SAVE_VISION, &CPropertyPageVision::OnBnClickedSaveVision)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_ALL, &CPropertyPageVision::OnBnClickedCheckRobotAll)
	ON_BN_CLICKED(IDC_CHECK_ROBOT01, &CPropertyPageVision::OnBnClickedCheckRobot01)
	ON_BN_CLICKED(IDC_CHECK_ROBOT02, &CPropertyPageVision::OnBnClickedCheckRobot02)
	ON_BN_CLICKED(IDC_CHECK_ROBOT03, &CPropertyPageVision::OnBnClickedCheckRobot03)
	ON_BN_CLICKED(IDC_CHECK_ROBOT04, &CPropertyPageVision::OnBnClickedCheckRobot04)
	ON_BN_CLICKED(IDC_CHECK_ROBOT05, &CPropertyPageVision::OnBnClickedCheckRobot05)
	ON_BN_CLICKED(IDC_CHECK_ROBOT06, &CPropertyPageVision::OnBnClickedCheckRobot06)
	ON_BN_CLICKED(IDC_CHECK_ROBOT07, &CPropertyPageVision::OnBnClickedCheckRobot07)
	ON_BN_CLICKED(IDC_CHECK_ROBOT08, &CPropertyPageVision::OnBnClickedCheckRobot08)
	ON_BN_CLICKED(IDC_CHECK_ROBOT09, &CPropertyPageVision::OnBnClickedCheckRobot09)
	ON_BN_CLICKED(IDC_CHECK_ROBOT10, &CPropertyPageVision::OnBnClickedCheckRobot10)
	ON_BN_CLICKED(IDC_CHECK_ROBOT11, &CPropertyPageVision::OnBnClickedCheckRobot11)
	ON_BN_CLICKED(IDC_CHECK_PROCESSING_AREA, &CPropertyPageVision::OnBnClickedCheckProcessingArea)
	ON_BN_CLICKED(IDC_CHECK_FLAT_IMAGE2, &CPropertyPageVision::OnBnClickedCheckFlatImage2)
	ON_BN_CLICKED(IDC_CHECK_REVISION_IMAGE2, &CPropertyPageVision::OnBnClickedCheckRevisionImage2)
END_MESSAGE_MAP()


// CPropertyPageVision message handlers

BOOL CPropertyPageVision::OnInitDialog()
{
	CPropertyPageRobotSoccer::OnInitDialog();

	if( ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_5 )
	{
		/*SetDlgItemTextW(IDC_CHECK_ROBOT_ALL, _T("All") );
		MoveDlgItem( IDC_CHECK_ROBOT_ALL, CPoint(21,0) ); ChangeSizeDlgItem( IDC_CHECK_ROBOT_ALL, CPoint(-40,0) );

		SetDlgItemTextW(IDC_CHECK_ROBOT01  , _T("1") );
		SetDlgItemTextW(IDC_CHECK_ROBOT02  , _T("2") );
		SetDlgItemTextW(IDC_CHECK_ROBOT03  , _T("3") );
		
		MoveDlgItem( IDC_CHECK_ROBOT01, CPoint(-29,0) ); ChangeSizeDlgItem( IDC_CHECK_ROBOT01, CPoint(-26,0) );
		MoveDlgItem( IDC_CHECK_ROBOT02, CPoint(-53,0) ); ChangeSizeDlgItem( IDC_CHECK_ROBOT02, CPoint(-26,0) );
		MoveDlgItem( IDC_CHECK_ROBOT03, CPoint(-78,0) ); ChangeSizeDlgItem( IDC_CHECK_ROBOT03, CPoint(-26,0) );

		MoveDlgItem( IDC_CHECK_ROBOT04, CPoint(-300,0) );
		MoveDlgItem( IDC_CHECK_ROBOT05, CPoint(-300,0) );*/
	}

	if( ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_11 )
	{
		SetDlgItemTextW(IDC_CHECK_ROBOT_ALL, _T("All") );
		MoveDlgItem( IDC_CHECK_ROBOT_ALL, CPoint(21,-10) ); ChangeSizeDlgItem( IDC_CHECK_ROBOT_ALL, CPoint(-40,0) );

		SetDlgItemTextW(IDC_CHECK_ROBOT01  , _T("1") );
		SetDlgItemTextW(IDC_CHECK_ROBOT02  , _T("2") );
		SetDlgItemTextW(IDC_CHECK_ROBOT03  , _T("3") );
		
		MoveDlgItem( IDC_CHECK_ROBOT01, CPoint(-29,-10) ); ChangeSizeDlgItem( IDC_CHECK_ROBOT01, CPoint(-26,0) );
		MoveDlgItem( IDC_CHECK_ROBOT02, CPoint(-53,-10) ); ChangeSizeDlgItem( IDC_CHECK_ROBOT02, CPoint(-26,0) );
		MoveDlgItem( IDC_CHECK_ROBOT03, CPoint(-78,-10) ); ChangeSizeDlgItem( IDC_CHECK_ROBOT03, CPoint(-26,0) );

		MoveDlgItem( IDC_CHECK_ROBOT04, CPoint(-300,-10) );
		MoveDlgItem( IDC_CHECK_ROBOT05, CPoint(-300,-10) );
		MoveDlgItem( IDC_CHECK_ROBOT06, CPoint(-300,-10) );
		MoveDlgItem( IDC_CHECK_ROBOT07, CPoint(-300,-10) );
		MoveDlgItem( IDC_CHECK_ROBOT08, CPoint(-300,-10) );
		MoveDlgItem( IDC_CHECK_ROBOT09, CPoint(-300,-10) );
		MoveDlgItem( IDC_CHECK_ROBOT10, CPoint(-300,-10) );
		MoveDlgItem( IDC_CHECK_ROBOT11, CPoint(-300,-10) );

		MoveDlgItem( IDC_FRAME_VISION_TEST_RESULT, CPoint(0,0) ); ChangeSizeDlgItem( IDC_FRAME_VISION_TEST_RESULT, CPoint(0,20) );
	}


	m_propVisionCoreDiagonalPatch_draw.SetDisplayDC( m_pDC );
	m_propVisionCoreDiagonalPatch_draw.SetLookUpTable( m_pLookUpTable );
	m_propVisionCoreDiagonalPatch_draw.SetImageGrabber( m_pImageGrabber );
	m_propVisionCoreDiagonalPatch_draw.SetRevision( &m_revision, &m_revision_ball );
	m_propVisionCoreDiagonalPatch_draw.SetGround( m_pGround );

	m_VisionCoreDiagonalPatch_share.SetLookUpTable( m_pLookUpTable );
	m_VisionCoreDiagonalPatch_share.SetImageGrabber( m_pImageGrabber );
	m_VisionCoreDiagonalPatch_share.SetRevision( &m_revision, &m_revision_ball );
	m_VisionCoreDiagonalPatch_share.SetGround( m_pGround );

	m_VisionCoreDiagonalPatch_process.SetLookUpTable( m_pLookUpTable );
	m_VisionCoreDiagonalPatch_process.SetImageGrabber( m_pImageGrabber );
	m_VisionCoreDiagonalPatch_process.SetRevision( &m_revision, &m_revision_ball );
	m_VisionCoreDiagonalPatch_process.SetGround( m_pGround );



	m_propVisionCoreSegmentPatch_draw.SetDisplayDC( m_pDC );
	m_propVisionCoreSegmentPatch_draw.SetLookUpTable( m_pLookUpTable );
	m_propVisionCoreSegmentPatch_draw.SetImageGrabber( m_pImageGrabber );
	m_propVisionCoreSegmentPatch_draw.SetRevision( &m_revision, &m_revision_ball );
	m_propVisionCoreSegmentPatch_draw.SetGround( m_pGround );

	m_VisionCoreSegmentPatch_share.SetLookUpTable( m_pLookUpTable );
	m_VisionCoreSegmentPatch_share.SetImageGrabber( m_pImageGrabber );
	m_VisionCoreSegmentPatch_share.SetRevision( &m_revision, &m_revision_ball );
	m_VisionCoreSegmentPatch_share.SetGround( m_pGround );

	m_VisionCoreSegmentPatch_process.SetLookUpTable( m_pLookUpTable );
	m_VisionCoreSegmentPatch_process.SetImageGrabber( m_pImageGrabber );
	m_VisionCoreSegmentPatch_process.SetRevision( &m_revision, &m_revision_ball );
	m_VisionCoreSegmentPatch_process.SetGround( m_pGround );



	m_propVisionCoreBarPatch_draw.SetDisplayDC( m_pDC );
	m_propVisionCoreBarPatch_draw.SetLookUpTable( m_pLookUpTable );
	m_propVisionCoreBarPatch_draw.SetImageGrabber( m_pImageGrabber );
	m_propVisionCoreBarPatch_draw.SetRevision( &m_revision, &m_revision_ball );
	m_propVisionCoreBarPatch_draw.SetGround( m_pGround );

	m_VisionCoreBarPatch_share.SetLookUpTable( m_pLookUpTable );
	m_VisionCoreBarPatch_share.SetImageGrabber( m_pImageGrabber );
	m_VisionCoreBarPatch_share.SetRevision( &m_revision, &m_revision_ball );
	m_VisionCoreBarPatch_share.SetGround( m_pGround );

	m_VisionCoreBarPatch_process.SetLookUpTable( m_pLookUpTable );
	m_VisionCoreBarPatch_process.SetImageGrabber( m_pImageGrabber );
	m_VisionCoreBarPatch_process.SetRevision( &m_revision, &m_revision_ball );
	m_VisionCoreBarPatch_process.SetGround( m_pGround );


	CClientDC dc(this);
	{
		m_dcFlat.UpdateRect( CRect(0,0,m_pImageGrabber->Width(),m_pImageGrabber->Height()));
		m_dcFlat.Init( &dc );	
		m_dcFlat_share.UpdateRect( CRect(0,0,m_pImageGrabber->Width(),m_pImageGrabber->Height()));
		m_dcFlat_share.Init( &dc );	

		m_dcRevision.UpdateRect( CRect(0,0,m_pImageGrabber->Width(),m_pImageGrabber->Height()));
		m_dcRevision.Init( &dc );	
		m_dcRevision_share.UpdateRect( CRect(0,0,m_pImageGrabber->Width(),m_pImageGrabber->Height()));
		m_dcRevision_share.Init( &dc );	

		m_dcImage.UpdateRect( CRect(0,0,m_pImageGrabber->Width(),m_pImageGrabber->Height()));
		m_dcImage.Init( &dc );
	}


	m_sliderRevisionK.SetOption( _T("Revision Constant"), false, 100, 3000, 1, 0 );
	m_sliderRevisionK.SetValue( 2000 );
	m_sliderRevisionZoom.SetOption( _T("Zoom"), false, .10, 2.00, 0.01, 2 );
	m_sliderRevisionZoom.SetValue( 0.9 );


	m_FlatPoints.Init( 55, 10, m_pImageGrabber->Width()-60, m_pImageGrabber->Height()-15);
	m_FlatPoints.SetTitle( _T("Revision Area - Robot") );

	m_FlatPoints_ball.Init( 155, 110, m_pImageGrabber->Width()-160, m_pImageGrabber->Height()-115);
	m_FlatPoints_ball.SetTitle( _T("Revision Area - Ball") );

	m_revision.SetImageSize( m_pImageGrabber->Height(), m_pImageGrabber->Width() );
	m_revision_ball.SetImageSize( m_pImageGrabber->Height(), m_pImageGrabber->Width() );



	double left		= 0;;
	double right	= m_pGround->Width();
	double bottom	= 0;
	double top		= m_pGround->Height();
	
	m_pGround->GroundToScreen( left, top );
	m_pGround->GroundToScreen( right, bottom );
	m_rectGroundMappingArea.Init( left, top, right, bottom );

	m_rectGroundMappingArea.SetColor( RGB(0,255,0) );
	m_rectGroundMappingArea.SetTitle( _T("Ground Mapping Area") );


	{
		m_patchEnable.bDiagonal = false;
		m_patchEnable.bSegment  = false;
		m_patchEnable.bBar      = false;

		FILE *fp;
		fp = fopen("patch.cfg", "rt");

		if( fp != NULL )
		{
			while( !feof(fp) )
			{
				char buf[256];
				fgets( buf, 256, fp);

				CString patch_type(buf);

				while( patch_type.GetLength() >= 1 )
				{
					if( patch_type.GetAt(0) == ' '
						|| patch_type.GetAt(0) == '\t'
						|| patch_type.GetAt(0) == '\n'
						|| patch_type.GetAt(0) == '\r' )
						patch_type.Delete( 0, 1 );
					else
						break;
				}

				while(1)
				{
					int n = patch_type.GetLength();

					if( n <= 0 )
						break;

					if( patch_type.GetAt(n-1) == ' '
						|| patch_type.GetAt(n-1) == '\t'
						|| patch_type.GetAt(n-1) == '\n'
						|| patch_type.GetAt(n-1) == '\r' )
						patch_type.Delete( n-1, 1 );
					else
						break;
				}

				if( patch_type.GetLength() <= 0 )
					continue;

				if( patch_type.GetAt(0) == '/' && patch_type.GetAt(1) == '/' )
				{
					// commnet
				}
				else
				{
					if( patch_type == "diagonal" )
					{
						m_patchEnable.bDiagonal = true;
					}
					if( patch_type == "segment" )
					{
						m_patchEnable.bSegment = true;
					}
					if( patch_type == "bar" )
					{
						m_patchEnable.bBar = true;
					}
				}
			}

			fclose( fp );
		}
		else
		{
			m_patchEnable.bBar= true;	// 기본 설정
		}
	}

	// Patch Sheet/Page nabling
	if( m_patchEnable.bDiagonal )
	{
		m_PropertySheetVisionCore.AddPage(&m_propVisionCoreDiagonalPatch_draw);	
	}
	else
	{
		m_PropertySheetVisionCore_invisible.AddPage(&m_propVisionCoreDiagonalPatch_draw);	
	}
	if( m_patchEnable.bSegment )
	{
		m_PropertySheetVisionCore.AddPage(&m_propVisionCoreSegmentPatch_draw);	
	}
	else

	{
		m_PropertySheetVisionCore_invisible.AddPage(&m_propVisionCoreSegmentPatch_draw);	
	}

	if( m_patchEnable.bBar )
	{
		m_PropertySheetVisionCore.AddPage(&m_propVisionCoreBarPatch_draw);	
	}
	else
	{
		m_PropertySheetVisionCore_invisible.AddPage(&m_propVisionCoreBarPatch_draw);	
	}

	if( !m_patchEnable.bBar || !m_patchEnable.bSegment || !m_patchEnable.bDiagonal )
	{
		m_PropertySheetVisionCore_invisible.Create(this, WS_CHILD|WS_VISIBLE,0);
		m_PropertySheetVisionCore_invisible.ModifyStyleEx(0, WS_EX_CONTROLPARENT);
		m_PropertySheetVisionCore_invisible.ModifyStyle(WS_TABSTOP, 0);
		m_PropertySheetVisionCore_invisible.SetTitle(_T("VisionCore_invisible"), PSH_PROPTITLE);

		CRect rcSheet;
		GetDlgItem(IDC_FRAME_PROPERTY_SHEET_VISION_CORE_INVISIBLE)->GetWindowRect(&rcSheet);
		ScreenToClient(&rcSheet);
		CTabCtrl *TabCtrl = m_PropertySheetVisionCore_invisible.GetTabControl();
		TabCtrl->MoveWindow(0, 0, rcSheet.Width(), rcSheet.Height());
	
		m_PropertySheetVisionCore_invisible.SetWindowPos(NULL, rcSheet.left, rcSheet.top, rcSheet.Width(), rcSheet.Height(),
			SWP_NOZORDER | SWP_NOACTIVATE);
		m_PropertySheetVisionCore_invisible.SetActivePage(2);	// for InitDialog execution
		m_PropertySheetVisionCore_invisible.SetActivePage(1);	// for InitDialog execution
		m_PropertySheetVisionCore_invisible.SetActivePage(0);	// for InitDialog execution

		m_PropertySheetVisionCore.SetActivePage(0);	// for InitDialog execution
	}	
	

	// Adding the patch tabs in one place
	// m_PropertySheetVisionCore.AddPage(&m_propVisionCoreDiagonalPatch_draw);
	// m_PropertySheetVisionCore.AddPage(&m_propVisionCoreSegmentPatch_draw);
	// m_PropertySheetVisionCore.AddPage(&m_propVisionCoreBarPatch_draw);

	{
	

		m_PropertySheetVisionCore.Create(this, WS_CHILD|WS_VISIBLE,0);
		m_PropertySheetVisionCore.ModifyStyleEx(0, WS_EX_CONTROLPARENT);
		m_PropertySheetVisionCore.ModifyStyle(WS_TABSTOP, 0);
		m_PropertySheetVisionCore.SetTitle(_T("VisionCore"), PSH_PROPTITLE);

		CRect rcSheet;
		GetDlgItem(IDC_FRAME_PROPERTY_SHEET_VISION_CORE)->GetWindowRect(&rcSheet);
		ScreenToClient(&rcSheet);
		CTabCtrl *TabCtrl = m_PropertySheetVisionCore.GetTabControl();
		TabCtrl->MoveWindow(0, 0, rcSheet.Width(), rcSheet.Height());
	
		m_PropertySheetVisionCore.SetWindowPos(NULL, rcSheet.left, rcSheet.top, rcSheet.Width(), rcSheet.Height(),
			SWP_NOZORDER | SWP_NOACTIVATE);
		m_PropertySheetVisionCore.SetActivePage(2);	// for InitDialog execution
		m_PropertySheetVisionCore.SetActivePage(1);	// for InitDialog execution
		m_PropertySheetVisionCore.SetActivePage(0);	// for InitDialog execution

		m_PropertySheetVisionCore.SetActivePage(0);	// for InitDialog execution
	}	

	m_colorpickMask.SetColor( RGB(0,255,0) );


	m_sliderPatchDirection.SetOption( _T("patch direction"), false, -180, 180, 45, 0 );
	m_sliderPatchDirection.SetValue( 0 );


	m_revision.SetVisionCenter(m_pDC->Width()/2, m_pDC->Height()/2);
	m_revision.SetVisionParam( m_sliderRevisionK.GetValue(), m_sliderRevisionZoom.GetValue() );

	m_revision_ball.SetVisionCenter(m_pDC->Width()/2, m_pDC->Height()/2);
	m_revision_ball.SetVisionParam( m_sliderRevisionK.GetValue(), m_sliderRevisionZoom.GetValue() );

	RevisionUpdate();

	{
		CRect rect;
		GetDlgItem(IDC_FRAME_VISION_TEST_RESULT)->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.DeflateRect(1,1,1,1);
		m_dcTestResult.UpdateRect( rect );
		m_dcTestResult.Init( &dc );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageVision::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call __super::OnPaint() for painting messages

}

CString CPropertyPageVision::GetActiveVisionCore()
{
	if( m_patchEnable.bDiagonal && m_propVisionCoreDiagonalPatch_draw.IsActive() )
	{
		return _T("DiagonalPatch");
	}

	if( m_patchEnable.bSegment && m_propVisionCoreSegmentPatch_draw.IsActive() )
	{
		return _T("SegmentPatch");
	}

	if( m_patchEnable.bBar && m_propVisionCoreBarPatch_draw.IsActive() )
	{
		return _T("BarPatch");
	}

	return 0;
}

void CPropertyPageVision::GenerateDrawInformation()
{
	if( !m_bCameraPause )
	{
		if( m_bRevisionImage || m_bRevisionImage_ball )
		{
			DrawRevisionImage( &m_dcRevision );

			EnterCriticalSection(&m_critVision);
			m_dcRevision.Copy( &m_dcRevision_share );
			LeaveCriticalSection(&m_critVision);
		}
		else
			/*
		if( m_bFlatImage || m_bFlatImage_ball )
		{
			DrawFlatImage( &m_dcFlat );

			EnterCriticalSection(&m_critVision);
			m_dcFlat.Copy( &m_dcFlat_share );
			LeaveCriticalSection(&m_critVision);
		}
		else
		*/
		{
			EnterCriticalSection(&m_critVision);
			m_pImageGrabber->DrawToDC( &m_dcImage, 0, 0 );
			LeaveCriticalSection(&m_critVision);
		}
	}
}

void CPropertyPageVision::DrawDisplay(void)
{
	//UpdatePropertyPageVisionCore();

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

	
		if( m_bRevisionImage || m_bRevisionImage_ball )
		{
			// Ground <- Flat <- Vision

			if( m_bShowCameraImage )
			{
				/*
				if( m_bCameraPause )
					m_dcRevision.Copy(m_pDC);
				else
					DrawRevisionImage( m_pDC );
				*/

				EnterCriticalSection(&m_critVision);
				m_dcRevision_share.Copy(m_pDC);
				LeaveCriticalSection(&m_critVision);
			}
			else
			{
				m_pDC->FillSolidRect(0, 0, m_pDC->Width(), m_pDC->Height(), RGB(0,0,0) );
			}


			if( !m_bRevisionImage && !m_bRevisionImage_ball )
				m_pDC->FillSolidRect(0, 0, m_pDC->Width(), m_pDC->Height(), RGB(0,0,0) );

			m_pGround->Draw( m_pDC, RGB(255,0,0), true, true );
				
			CPen pen, *pOldPen;
			pen.CreatePen( PS_SOLID, 1, m_rectGroundMappingArea.GetColor() );
			pOldPen = (CPen*)m_pDC->SelectObject( &pen );
				
			m_pDC->SelectStockObject( NULL_BRUSH );
				
			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( m_rectGroundMappingArea.GetColor() );
				
				
			double top,left,right,bottom;
			left = m_rectGroundMappingArea.m_left;
			top = m_rectGroundMappingArea.m_top;
			right = m_rectGroundMappingArea.m_right;
			bottom = m_rectGroundMappingArea.m_bottom;
				
			m_pGround->ScreenToGround( left, top );
			m_pGround->ScreenToGround( right, bottom );
				
			CString tmp;
			tmp.Format(_T("%s"), m_rectGroundMappingArea.Title() );
			m_pDC->DrawText(	tmp,
				m_rectGroundMappingArea.GetRect()-CPoint(0,20),
				DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				
			tmp.Format(_T("(%.2lf,%.2lf)-(%.2lf,%.2lf)"), left, top, right, bottom );
			m_pDC->DrawText(	tmp,
				m_rectGroundMappingArea.GetRect(),
				DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				
			tmp.Format(_T("(%.2lf,%.2lf)"), right-left, bottom-top );
			m_pDC->DrawText(	tmp,
				m_rectGroundMappingArea.GetRect()+CPoint(0,20),
				DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				
			m_pDC->Rectangle( m_rectGroundMappingArea.GetRect() );
				
			m_pDC->SelectObject( pOldPen );
		}
		else if( m_bFlatImage || m_bFlatImage_ball )
		{
			// GroundPoints, RevisionImage가 우선 순위임

			if( m_bShowCameraImage )
			{
				EnterCriticalSection(&m_critVision);
				m_dcImage.Copy(m_pDC);
				//m_dcFlat_share.Copy(m_pDC);
				LeaveCriticalSection(&m_critVision);


				/*
				if( m_bCameraPause )
					m_dcFlat.Copy(m_pDC);
				else
					DrawFlatImage( m_pDC );
				*/
			}
			else
			{
				m_pDC->FillSolidRect(0, 0, m_pDC->Width(), m_pDC->Height(), RGB(0,0,0) );
			}

			if( m_bFlatImage )
			{
				CPen pen, *pOldPen;
				pen.CreatePen( PS_DOT, 1, m_FlatPoints.ColorLine() );
				pOldPen = (CPen*)m_pDC->SelectObject( &pen );
					
				m_pDC->SelectStockObject( NULL_BRUSH );
					
				m_pDC->MoveTo( m_FlatPoints.GetPoint(0) );
				m_pDC->LineTo( m_FlatPoints.GetPoint(1) );
				m_pDC->LineTo( m_FlatPoints.GetPoint(2) );
				m_pDC->LineTo( m_FlatPoints.GetPoint(3) );
				m_pDC->LineTo( m_FlatPoints.GetPoint(0) );
					
				m_pDC->SetBkMode( TRANSPARENT );
				m_pDC->SetTextColor( m_FlatPoints.ColorText() );
					
				for( int i=0 ; i<4 ; i++ )
				{
					CPoint textPos = m_FlatPoints.GetTextPos(i);
					m_pDC->TextOut( textPos.x, textPos.y, m_FlatPoints.GetTextInfo(i) );
			
					CPoint p = m_FlatPoints.GetPoint(i);
					m_pDC->FillSolidRect( p.x-1, p.y-1, 3, 3, m_FlatPoints.ColorPoint() );
				}

				{
					CPoint p0 = m_FlatPoints.GetTextPos(0);
					CPoint p1 = m_FlatPoints.GetTextPos(1);
					CPoint p2 = m_FlatPoints.GetTextPos(2);
					CPoint p3 = m_FlatPoints.GetTextPos(3);

					m_pDC->TextOut( (p0+p3).x/2, (p0+p3).y/2, _T("Team ground") );
					m_pDC->TextOut( (p1+p2).x/2, (p1+p2).y/2, _T("opponent ground") );
				}
					
				CPoint titlePos = m_FlatPoints.TitlePos();
				m_pDC->TextOut( titlePos.x, titlePos.y, m_FlatPoints.Title() );
					
				m_pDC->SelectObject( pOldPen );
			}

			if( m_bFlatImage_ball )
			{
				CPen pen, *pOldPen;
				pen.CreatePen( PS_DOT, 1, m_FlatPoints_ball.ColorLine() );
				pOldPen = (CPen*)m_pDC->SelectObject( &pen );
					
				m_pDC->SelectStockObject( NULL_BRUSH );
					
				m_pDC->MoveTo( m_FlatPoints_ball.GetPoint(0) );
				m_pDC->LineTo( m_FlatPoints_ball.GetPoint(1) );
				m_pDC->LineTo( m_FlatPoints_ball.GetPoint(2) );
				m_pDC->LineTo( m_FlatPoints_ball.GetPoint(3) );
				m_pDC->LineTo( m_FlatPoints_ball.GetPoint(0) );
					
				m_pDC->SetBkMode( TRANSPARENT );
				m_pDC->SetTextColor( m_FlatPoints_ball.ColorText() );
					
				for( int i=0 ; i<4 ; i++ )
				{
					CPoint textPos = m_FlatPoints_ball.GetTextPos(i);
					m_pDC->TextOut( textPos.x, textPos.y, m_FlatPoints_ball.GetTextInfo(i) );
			
					CPoint p = m_FlatPoints_ball.GetPoint(i);
					m_pDC->FillSolidRect( p.x-1, p.y-1, 3, 3, m_FlatPoints_ball.ColorPoint() );
				}

				{
					CPoint p0 = m_FlatPoints_ball.GetTextPos(0);
					CPoint p1 = m_FlatPoints_ball.GetTextPos(1);
					CPoint p2 = m_FlatPoints_ball.GetTextPos(2);
					CPoint p3 = m_FlatPoints_ball.GetTextPos(3);

					m_pDC->TextOut( (p0+p3).x/2, (p0+p3).y/2, _T("Team ground") );
					m_pDC->TextOut( (p1+p2).x/2, (p1+p2).y/2, _T("Opponent ground") );
				}
					
				CPoint titlePos = m_FlatPoints_ball.TitlePos();
				m_pDC->TextOut( titlePos.x, titlePos.y, m_FlatPoints_ball.Title() );
					
				m_pDC->SelectObject( pOldPen );
			}

		}
		else
		{
			// 일반 영상

			if( m_bShowCameraImage )
			{
				/*
				if( m_bCameraPause )
					m_dcImage.Copy(m_pDC);
				else
				{
					m_pImageGrabber->DrawToDC( m_pDC, 0, 0 );
				}
				*/

				EnterCriticalSection(&m_critVision);
				m_dcImage.Copy(m_pDC);
				LeaveCriticalSection(&m_critVision);				
			}
			else
			{
				m_pDC->FillSolidRect(0, 0, m_pDC->Width(), m_pDC->Height(), RGB(0,0,0) );
			}
			
			if( m_propVisionCoreDiagonalPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreDiagonalPatch_draw.CopyData( m_VisionCoreDiagonalPatch_share );
				LeaveCriticalSection( &m_critVision );

				COLORREF color;
				if( m_bMasking )
					color = m_colorpickMask.GetColor();
				
				m_propVisionCoreDiagonalPatch_draw.DrawDisplay(m_bMasking, color);
				m_propVisionCoreDiagonalPatch_draw.Display_RobotSegment(m_bShowCameraImage, m_bMasking, m_colorpickMask.GetColor());


				if( m_propVisionCoreDiagonalPatch_draw.m_bScanningInterval )
				{
					if( !m_bMasking )
						color = m_propVisionCoreDiagonalPatch_draw.m_colorpickScanInterval.GetColor();
					
					for( int p=0 ; p<m_pDC->Width()*m_pDC->Height() ; p+=(int)m_propVisionCoreDiagonalPatch_draw.m_sliderScanInterval.GetValue() )
					{
						int i = p%m_pDC->Width();
						int j = p/m_pDC->Width();

						m_pDC->SetPixel( i, j, color );
					}
				}

				if( m_propVisionCoreDiagonalPatch_draw.m_bBall )
				{
					if( !m_bMasking )
						color = m_propVisionCoreDiagonalPatch_draw.m_colorpickBall.GetColor();
					m_propVisionCoreDiagonalPatch_draw.Draw_BallPatch( m_pDC, color );
				}


				if( m_propVisionCoreDiagonalPatch_draw.m_bOpponent )
				{
					if( !m_bMasking )
						color = m_propVisionCoreDiagonalPatch_draw.m_colorpickOpponent.GetColor();
					m_propVisionCoreDiagonalPatch_draw.Draw_OpponentsPatch( m_pDC, color );
				}

				if( m_propVisionCoreDiagonalPatch_draw.m_bTeam )
				{
					if( !m_bMasking )
						color = m_propVisionCoreDiagonalPatch_draw.m_colorpickTeam.GetColor();
					m_propVisionCoreDiagonalPatch_draw.Draw_TeamPatch( m_pDC, color );
				}

				
				if( m_propVisionCoreDiagonalPatch_draw.m_bID1 )
				{
					if( !m_bMasking )
						color = m_propVisionCoreDiagonalPatch_draw.m_colorpickID1.GetColor();
					m_propVisionCoreDiagonalPatch_draw.Draw_IDPatch( m_pDC, 0, color );
				}
				
				if( m_propVisionCoreDiagonalPatch_draw.m_bID2 )
				{
					if( !m_bMasking )
						color = m_propVisionCoreDiagonalPatch_draw.m_colorpickID2.GetColor();
					m_propVisionCoreDiagonalPatch_draw.Draw_IDPatch( m_pDC, 1, color );
				}
				
				if( m_propVisionCoreDiagonalPatch_draw.m_bID3 )
				{
					if( !m_bMasking )
						color = m_propVisionCoreDiagonalPatch_draw.m_colorpickID3.GetColor();
					m_propVisionCoreDiagonalPatch_draw.Draw_IDPatch( m_pDC, 2, color );
				}
				
				
				if( m_propVisionCoreDiagonalPatch_draw.m_bTeamIDDistance )
				{
					m_propVisionCoreDiagonalPatch_draw.SetTeamIDDistance( m_propVisionCoreDiagonalPatch_draw.m_sliderSizeTeamIDDistance.GetValueLeft()/100.0 );

					if( !m_bMasking )
						color = m_propVisionCoreDiagonalPatch_draw.m_colorpickTeamIDDistance.GetColor();
					m_propVisionCoreDiagonalPatch_draw.Draw_TeamIDDistance( m_pDC, color );
				}


				BOOL bRobot[11];
				bRobot[0]  = m_bRobot01;
				bRobot[1]  = m_bRobot02;
				bRobot[2]  = m_bRobot03;
				bRobot[3]  = m_bRobot04;
				bRobot[4]  = m_bRobot05;
				bRobot[5]  = m_bRobot06;
				bRobot[6]  = m_bRobot07;
				bRobot[7]  = m_bRobot08;
				bRobot[8]  = m_bRobot09;
				bRobot[9]  = m_bRobot10;
				bRobot[10] = m_bRobot11;
				m_propVisionCoreDiagonalPatch_draw.Draw_Robot( m_pDC, m_bRobotAll, bRobot );
			}
			
			if( m_propVisionCoreSegmentPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreSegmentPatch_draw.CopyData( m_VisionCoreSegmentPatch_share );
				LeaveCriticalSection( &m_critVision );

				COLORREF color;
				if( m_bMasking )
					color = m_colorpickMask.GetColor();

				m_propVisionCoreSegmentPatch_draw.DrawDisplay( m_bMasking, color );
				m_propVisionCoreSegmentPatch_draw.Display_RobotSegment( m_bShowCameraImage, m_bMasking, m_colorpickMask.GetColor() );

				BOOL bRobot[11];
				bRobot[0]  = m_bRobot01;
				bRobot[1]  = m_bRobot02;
				bRobot[2]  = m_bRobot03;
				bRobot[3]  = m_bRobot04;
				bRobot[4]  = m_bRobot05;
				bRobot[5]  = m_bRobot06;
				bRobot[6]  = m_bRobot07;
				bRobot[7]  = m_bRobot08;
				bRobot[8]  = m_bRobot09;
				bRobot[9]  = m_bRobot10;
				bRobot[10] = m_bRobot11;
				m_propVisionCoreSegmentPatch_draw.Draw_Robot( m_pDC, m_bRobotAll, bRobot );
			}
			
			if( m_propVisionCoreBarPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreBarPatch_draw.CopyData( m_VisionCoreBarPatch_share );
				LeaveCriticalSection( &m_critVision );

				COLORREF color;
				if( m_bMasking )
					color = m_colorpickMask.GetColor();

				m_propVisionCoreBarPatch_draw.DrawDisplay( m_bMasking, color );
				m_propVisionCoreBarPatch_draw.Display_RobotSegment( m_bShowCameraImage, m_bMasking, m_colorpickMask.GetColor() );

				BOOL bRobot[11];
				bRobot[0]  = m_bRobot01;
				bRobot[1]  = m_bRobot02;
				bRobot[2]  = m_bRobot03;
				bRobot[3]  = m_bRobot04;
				bRobot[4]  = m_bRobot05;
				bRobot[5]  = m_bRobot06;
				bRobot[6]  = m_bRobot07;
				bRobot[7]  = m_bRobot08;
				bRobot[8]  = m_bRobot09;
				bRobot[9]  = m_bRobot10;
				bRobot[10] = m_bRobot11;
				m_propVisionCoreBarPatch_draw.Draw_Robot( m_pDC, m_bRobotAll, bRobot );
			}
			

			if( m_bProcessingArea )
			{
				if( m_propVisionCoreDiagonalPatch_draw.IsActive() )
					m_propVisionCoreDiagonalPatch_draw.DrawProcessingArea( m_pDC, m_colorpickMask.GetColor() );
				if( m_propVisionCoreSegmentPatch_draw.IsActive() )
					m_propVisionCoreSegmentPatch_draw.DrawProcessingArea( m_pDC, m_colorpickMask.GetColor() );
				if( m_propVisionCoreBarPatch_draw.IsActive() )
					m_propVisionCoreBarPatch_draw.DrawProcessingArea( m_pDC, m_colorpickMask.GetColor() );
			}	
			
		}		
	}


	{
		CClientDC dc(this);

		{
			CBrush brush, *pOldBrush;
			brush.CreateSolidBrush( RGB(0,0,0) );


			pOldBrush = (CBrush*)m_dcTestResult.SelectObject( &brush );
								
			CRect rect = m_dcTestResult.GetRect();
			m_dcTestResult.Rectangle( rect - rect.TopLeft() );
				
			m_dcTestResult.SelectObject( pOldBrush );
		}


		m_dcTestResult.SetBkMode( TRANSPARENT );

		CBrush brush, *pOldBrush;
		brush.CreateSolidBrush( RGB(30,30,64) );
		pOldBrush = (CBrush*)m_dcTestResult.SelectObject( &brush );

		if( ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_3 )
		{
			for( int i=0 ; i<3 ; i++ )
			{
				CRect rect = m_dcTestResult.GetRect();

				rect.left  = 15 + 90 * i;
				rect.right = rect.left + 80;
				rect.top = 5;
				rect.bottom = rect.top+25;

				m_dcTestResult.Rectangle( rect );


				COLORREF colorText = RGB( 255,255,255 );
				int c = m_VisionTest.robot[i].countLoss*255/100;
				colorText = RGB(255, 255-c, 0);

				if( m_VisionTest.robot[i].countLoss == 0 )
					colorText = RGB(0,255,0);
				m_dcTestResult.SetTextColor( colorText );

				CString tmp;
				tmp.Format(_T(" [Robot-%d]"), i+1); 
				m_dcTestResult.DrawText( tmp, rect, DT_LEFT|DT_SINGLELINE|DT_VCENTER );

				tmp.Format(_T("%d "), 100-m_VisionTest.robot[i].countLoss ); 
				m_dcTestResult.DrawText( tmp, rect, DT_RIGHT|DT_SINGLELINE|DT_VCENTER );
			}
		}

		if( ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_5 )
		{
			for( int i=0 ; i<5 ; i++ )
			{
				CRect rect = m_dcTestResult.GetRect();

				rect.left = 10 + 55 * i;
				rect.right = 10 + 55 * i + 43;
				rect.top = 5;
				rect.bottom = rect.top+25;

				m_dcTestResult.Rectangle( rect );


				COLORREF colorText = RGB( 255,255,255 );
				int c = m_VisionTest.robot[i].countLoss*255/100;
				colorText = RGB(255, 255-c, 0);

				if( m_VisionTest.robot[i].countLoss == 0 )
					colorText = RGB(0,255,0);
				m_dcTestResult.SetTextColor( colorText );

				CString tmp;
				tmp.Format(_T("[%d]"), i+1); 
				m_dcTestResult.DrawText( tmp, rect, DT_LEFT|DT_SINGLELINE|DT_VCENTER );


				tmp.Format(_T("%d "), 100-m_VisionTest.robot[i].countLoss ); 
				m_dcTestResult.DrawText( tmp, rect, DT_RIGHT|DT_SINGLELINE|DT_VCENTER );
			}
		}

		if( ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_11 )
		{
			for( int i=0 ; i<11 ; i++ )
			{
				CRect rect = m_dcTestResult.GetRect();

				if( i < 5 )
				{
					rect.left = 10 + 45 * (i+1);
					rect.right = 10 + 45 * (i+1) + 43;
					rect.top = 5;
					rect.bottom = rect.top+25;
				}
				else
				{
					rect.left = 10 + 45 * (i-5);
					rect.right = 10 + 45 * (i-5) + 43;
					rect.top = 35;
					rect.bottom = rect.top+25;
				}


				m_dcTestResult.Rectangle( rect );


				COLORREF colorText = RGB( 255,255,255 );
				int c = m_VisionTest.robot[i].countLoss*255/100;
				colorText = RGB(255, 255-c, 0);

				if( m_VisionTest.robot[i].countLoss == 0 )
					colorText = RGB(0,255,0);
				m_dcTestResult.SetTextColor( colorText );

				CString tmp;
				tmp.Format(_T("[%d]"), i+1); 
				m_dcTestResult.DrawText( tmp, rect, DT_LEFT|DT_SINGLELINE|DT_VCENTER );


				tmp.Format(_T("%d "), 100-m_VisionTest.robot[i].countLoss ); 
				m_dcTestResult.DrawText( tmp, rect, DT_RIGHT|DT_SINGLELINE|DT_VCENTER );
			}
		}

		m_dcTestResult.SelectObject( pOldBrush );

		{
			CPen pen, *pOldPen;
			pen.CreatePen( PS_SOLID, 1, RGB(255,0,255) );
			pOldPen = (CPen*)m_dcTestResult.SelectObject( &pen );
				
			int y = 35;//m_dcTestResult.Height()/2;

			//static bool bIn = false;
			//bIn = !bIn;
			//double t = m_VisionTest.count%100 / 100.0;

			double t = m_VisionTest.count%100 / 100.0;

			//for( int t=0 ; t<m_dcTestResult.Width()/2/4 ; t++ )
			
			bool bIn = true;

			if( t < 0.5 )
			{
				t = t*2;
			}
			else
			{
				bIn = false;
				t = 1.0 - (t-0.5)*2;
			}
			
			{
				int x = (int)(t*(m_dcTestResult.Width()/2+50));

				for( int i=50 ; i>=0 ; i-- )
				{
					int r = i*5;
					if( bIn )
						r = (50-i)*5;

					int g = 0;
					int b = 0;
					
					{
						int x_left = x-i;
						if( x_left > m_dcTestResult.Width()/2 )
							x_left = m_dcTestResult.Width()/2;
						if( x_left < 0 )
							x_left = 0;
						m_dcTestResult.SetPixel( x_left, y, RGB(r,g,b) );
					}

					{
						int x_right = m_dcTestResult.Width() - (x-i);
						if( x_right < m_dcTestResult.Width()/2 )
							x_right = m_dcTestResult.Width()/2;
						if( x_right > m_dcTestResult.Width()   )
							x_right = m_dcTestResult.Width();
						
						m_dcTestResult.SetPixel( x_right, y, RGB(r,g,b) ); 
					}
				}
			}

				
			m_dcTestResult.SelectObject( pOldPen );
		}

		m_dcTestResult.BitBlt(&dc);
	}
}

void CPropertyPageVision::OnBnClickedCheckBackground()
{
	UpdateData(TRUE);
}

void CPropertyPageVision::OnBnClickedCheckColorMasking()
{
	UpdateData(TRUE);
}

void CPropertyPageVision::OnBnClickedCheckProcessingArea()
{
	UpdateData(TRUE);
}

void CPropertyPageVision::OnBnClickedCheckFlatImage()
{
	UpdateData(TRUE);

	if( m_bFlatImage )
	{
		m_bFlatImage_ball= FALSE;

		m_bRevisionImage = FALSE;
		m_bRevisionImage_ball = FALSE;

		UpdateData(FALSE);
	}
}

void CPropertyPageVision::OnBnClickedCheckFlatImage2()
{
	UpdateData(TRUE);

	if( m_bFlatImage_ball )
	{
		m_bFlatImage     = FALSE;

		m_bRevisionImage = FALSE;
		m_bRevisionImage_ball = FALSE;

		UpdateData(FALSE);
	}
}


void CPropertyPageVision::DrawFlatImage( CFrameDC *pDC )
{
	m_revision.SetVisionCenter(m_pDC->Width()/2, m_pDC->Height()/2);
	m_revision.SetVisionParam( m_sliderRevisionK.GetValue(), m_sliderRevisionZoom.GetValue() );

	return;
	/*
	for( int i=0 ; i<pDC->Width() ; i++ )
	{
		for( int j=0 ; j<pDC->Height() ; j++ )
		{
			double x = i;
			double y = j;
			m_revision.FlatToVision( x, y );
			
			{
				// m_bFlatImageInterporation
				if( 0 < x && x < pDC->Width() && 0 < y && y < pDC->Height())
					pDC->SetPixel( i, j, m_pImageGrabber->GetColorFloat( x, y, 0 ) );
				else
					pDC->SetPixel( i, j, RGB(0,0,0) );
				// m_pDC->SetPixel( i, j, m_pImageGrabber->GetColor( (int)x, (int)y, m_cameraID ) );
			}
		}
	}
	*/
}

void CPropertyPageVision::DrawRevisionImage( CFrameDC *pDC )
{
	RevisionUpdate();

	if( m_bRevisionImage )
	{
		for( int i=0 ; i<pDC->Width() ; i++ )
		{
			for( int j=0 ; j<pDC->Height() ; j++ )
			{
				if( m_revision.IsInDCGround( i, j ) )
				{
					double x = i;
					double y = j;
				
					m_revision.ScreenToFlat( x, y );
					m_revision.FlatToVision( x, y );
				
					{
						// m_bFlatImageInterporation
						if( 0 < x && x < m_pDC->Width() && 0 < y && y < m_pDC->Height())
							pDC->SetPixel( i, j, m_pImageGrabber->GetColorFloat( x, y, 0 ) );
						else
							pDC->SetPixel( i, j, RGB(0,0,0));
					
						//m_pDC->SetPixel( i, j, m_pImageGrabber->GetColor( (int)x, (int)y, m_cameraID ) );
					}
				}
				else
				{
					//							if( !m_bGroundPoints )
					{
						pDC->SetPixel( i, j, RGB(0,0,0));
					}
				}
			}
		}
	}
	else
	if( m_bRevisionImage_ball )
	{
		for( int i=0 ; i<pDC->Width() ; i++ )
		{
			for( int j=0 ; j<pDC->Height() ; j++ )
			{
				if( m_revision_ball.IsInDCGround( i, j ) )
				{
					double x = i;
					double y = j;
				
					m_revision_ball.ScreenToFlat( x, y );
					m_revision_ball.FlatToVision( x, y );
				
					{
						// m_bFlatImageInterporation
						if( 0 < x && x < m_pDC->Width() && 0 < y && y < m_pDC->Height())
							pDC->SetPixel( i, j, m_pImageGrabber->GetColorFloat( x, y, 0 ) );
						else
							pDC->SetPixel( i, j, RGB(0,0,0));
					
						//m_pDC->SetPixel( i, j, m_pImageGrabber->GetColor( (int)x, (int)y, m_cameraID ) );
					}
				}
				else
				{
					//							if( !m_bGroundPoints )
					{
						pDC->SetPixel( i, j, RGB(0,0,0));
					}
				}
			}
		}
	}
}

void CPropertyPageVision::RevisionUpdate()
{
	double top,left,right,bottom;
	left = m_rectGroundMappingArea.m_left;
	top = m_rectGroundMappingArea.m_top;
	right = m_rectGroundMappingArea.m_right;
	bottom = m_rectGroundMappingArea.m_bottom;
	
	m_revision.SetGroundRect( left, top, right, bottom );
	m_revision.SetFlatPoints( m_FlatPoints );
	m_revision.GenerateRevisionMatrix();

	m_revision_ball.SetGroundRect( left, top, right, bottom );
	m_revision_ball.SetFlatPoints( m_FlatPoints_ball );
	m_revision_ball.GenerateRevisionMatrix();
}

MouseCapture::Enum CPropertyPageVision::DisplayLButtonDown( UINT nFlags, CPoint point )
{
	if( m_bRevisionImage )
		m_rectGroundMappingArea.MouseLDown( point );
	else
	if( m_bFlatImage )
	{
		m_FlatPoints.MouseLDown( point );
	}
	else
	if( m_bFlatImage_ball )
	{
		m_FlatPoints_ball.MouseLDown( point );
	}
	else
	if( m_bProcessingArea )
	{
		int size = 10;

		if( nFlags&MK_CONTROL )
			size = 1;

		if( m_propVisionCoreDiagonalPatch_draw.IsActive() )
		{
			EnterCriticalSection( &m_critVision );
			m_propVisionCoreDiagonalPatch_draw.ProcessingAreaUpdate( point.x, point.y, true, size );
			LeaveCriticalSection( &m_critVision );
		}
		
		if( m_propVisionCoreSegmentPatch_draw.IsActive() )
		{
			EnterCriticalSection( &m_critVision );
			m_propVisionCoreSegmentPatch_draw.ProcessingAreaUpdate( point.x, point.y, true, size );
			LeaveCriticalSection( &m_critVision );
		}

		if( m_propVisionCoreBarPatch_draw.IsActive() )
		{
			EnterCriticalSection( &m_critVision );
			m_propVisionCoreBarPatch_draw.ProcessingAreaUpdate( point.x, point.y, true, size );
			LeaveCriticalSection( &m_critVision );
		}
	}

	if( m_bRButton )
	{
		// cancel
		m_bRButton = false;
		m_bLButton = false;
		return MouseCapture::RELEASE;
	}
	else
	{
		m_mouseDownPoint = point;
		m_bLButton = true;

		return MouseCapture::SET;
	}

	return MouseCapture::NOTHING;
}

MouseCapture::Enum CPropertyPageVision::DisplayLButtonUp( UINT nFlags, CPoint point )
{
	if( m_bRevisionImage )
		m_rectGroundMappingArea.MouseLUp( point );
	else
	if( m_bFlatImage )
	{
		m_FlatPoints.MouseLUp( point );
	}
	else
	if( m_bFlatImage_ball )
	{
		m_FlatPoints_ball.MouseLUp( point );
	}

	m_mouseUpPoint = point;
	m_bLButton = false;

	
	if( m_propVisionCoreSegmentPatch_draw.IsActive() )
	{
		EnterCriticalSection( &m_critVision );
		m_propVisionCoreSegmentPatch_draw.SetSelectRobotPosition( point + CPoint(1,1) );
		LeaveCriticalSection( &m_critVision );
	}
	
	if( m_propVisionCoreBarPatch_draw.IsActive() )
	{
		EnterCriticalSection( &m_critVision );
		m_propVisionCoreBarPatch_draw.SetSelectRobotPosition( point + CPoint(1,1) );
		LeaveCriticalSection( &m_critVision );
	}

	if (m_propVisionCoreDiagonalPatch_draw.IsActive())
	{
		EnterCriticalSection(&m_critVision);
		m_propVisionCoreDiagonalPatch_draw.SetSelectRobotPosition(point + CPoint(1, 1));
		LeaveCriticalSection(&m_critVision);
	}

	return MouseCapture::RELEASE;
}


MouseCapture::Enum CPropertyPageVision::DisplayRButtonDown( UINT nFlags, CPoint point )
{
	if( m_bLButton )
	{
		m_bRButton = false;
		m_bLButton = false;

		return MouseCapture::RELEASE;
	}
	else
	{
		m_mouseDownPoint = point;
		m_bRButton = true;


		if( m_bProcessingArea )
		{
			int size = 10;

			if( nFlags&MK_CONTROL )
				size = 1;

			if( m_propVisionCoreDiagonalPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreDiagonalPatch_draw.ProcessingAreaUpdate( point.x, point.y, false, size );
				LeaveCriticalSection( &m_critVision );
			}
			
			if( m_propVisionCoreSegmentPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreSegmentPatch_draw.ProcessingAreaUpdate( point.x, point.y, false, size );
				LeaveCriticalSection( &m_critVision );
			}

			if( m_propVisionCoreBarPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreBarPatch_draw.ProcessingAreaUpdate( point.x, point.y, false, size );
				LeaveCriticalSection( &m_critVision );
			}
		}

		return MouseCapture::SET;
	}
	
	return MouseCapture::NOTHING;
}

MouseCapture::Enum CPropertyPageVision::DisplayRButtonUp( UINT nFlags, CPoint point )
{
	if( m_bRevisionImage )
		m_rectGroundMappingArea.MouseRUp( point );
	else
	if( m_bFlatImage )
	{
		m_FlatPoints.MouseRUp( point );
	}
	else
	if( m_bFlatImage_ball )
	{
		m_FlatPoints_ball.MouseRUp( point );
	}

	m_mouseUpPoint = point;
	m_bRButton = false;

	return MouseCapture::RELEASE;
}


MouseCapture::Enum CPropertyPageVision::DisplayMouseMove( UINT nFlags, CPoint point )
{
	m_mouseDownPoint = point;

	if( m_bRevisionImage )
		m_rectGroundMappingArea.MouseMove( point );
	else
	if( m_bFlatImage )
	{
		m_FlatPoints.MouseMove( point );
	}
	else
	if( m_bFlatImage_ball )
	{
		m_FlatPoints_ball.MouseMove( point );
	}
	else
	if( m_bProcessingArea )
	{
		int size = 10;

		if( nFlags&MK_CONTROL )
			size = 1;

		if( m_bLButton )
		{
			if( m_propVisionCoreDiagonalPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreDiagonalPatch_draw.ProcessingAreaUpdate( point.x, point.y, true, size );
				LeaveCriticalSection( &m_critVision );
			}
			
			if( m_propVisionCoreSegmentPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreSegmentPatch_draw.ProcessingAreaUpdate( point.x, point.y, true, size );
				LeaveCriticalSection( &m_critVision );
			}

			if( m_propVisionCoreBarPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreBarPatch_draw.ProcessingAreaUpdate( point.x, point.y, true, size );
				LeaveCriticalSection( &m_critVision );
			}
		}
		if( m_bRButton )
		{
			if( m_propVisionCoreDiagonalPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreDiagonalPatch_draw.ProcessingAreaUpdate( point.x, point.y, false, size );
				LeaveCriticalSection( &m_critVision );
			}
			
			if( m_propVisionCoreSegmentPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreSegmentPatch_draw.ProcessingAreaUpdate( point.x, point.y, false, size );
				LeaveCriticalSection( &m_critVision );
			}
			
			if( m_propVisionCoreBarPatch_draw.IsActive() )
			{
				EnterCriticalSection( &m_critVision );
				m_propVisionCoreBarPatch_draw.ProcessingAreaUpdate( point.x, point.y, false, size );
				LeaveCriticalSection( &m_critVision );
			}
		}
	}

	return MouseCapture::NOTHING;
}

void CPropertyPageVision::OnBnClickedCheckRevisionImage()
{
	UpdateData(TRUE);

	m_revision.SetVisionCenter(m_pDC->Width()/2, m_pDC->Height()/2);
	m_revision.SetVisionParam( m_sliderRevisionK.GetValue(), m_sliderRevisionZoom.GetValue() );

	if( m_bRevisionImage )
	{
		m_bFlatImage = FALSE;
		m_bFlatImage_ball = FALSE;

		m_bRevisionImage_ball = FALSE;

		UpdateData(FALSE);
	}
}

void CPropertyPageVision::OnBnClickedCheckRevisionImage2()
{
	UpdateData(TRUE);

	m_revision_ball.SetVisionCenter(m_pDC->Width()/2, m_pDC->Height()/2);
	m_revision_ball.SetVisionParam( m_sliderRevisionK.GetValue(), m_sliderRevisionZoom.GetValue() );

	if( m_bRevisionImage_ball )
	{
		m_bFlatImage = FALSE;
		m_bFlatImage_ball = FALSE;

		m_bRevisionImage = FALSE;

		UpdateData(FALSE);
	}
}

void CPropertyPageVision::OnBnClickedCheckCameraPause()
{
	UpdateData(TRUE);
	/*
	if( m_bCameraPause )
	{
		BeginWaitCursor();

		m_pImageGrabber->DrawToDC( &m_dcImage, 0, 0 );

		DrawFlatImage( &m_dcFlat );

		DrawRevisionImage( &m_dcRevision );
	
		EndWaitCursor();
	}
	*/


	if( m_bCameraPause )
	{
		EnterCriticalSection(&m_critVision);
		{
			DrawRevisionImage( &m_dcRevision );

			m_dcRevision.Copy( &m_dcRevision_share );
		}

		{
			DrawFlatImage( &m_dcFlat );
			m_dcFlat.Copy( &m_dcFlat_share );
		}

		{
			m_pImageGrabber->DrawToDC( &m_dcImage, 0, 0 );
		}
		LeaveCriticalSection(&m_critVision);
	}
}


void CPropertyPageVision::VisionRun()
{
	EnterCriticalSection(&m_critVision);
	//m_dcRevision.Copy( &m_dcRevision_share );
	LeaveCriticalSection(&m_critVision);
	if (m_propVisionCoreBarPatch_draw.IsActive())
	{
		EnterCriticalSection(&m_critVision);
		CopyMemory(m_VisionCoreBarPatch_process.m_pProcessingArea, m_propVisionCoreBarPatch_draw.m_pProcessingArea, sizeof(unsigned char) * CAMERA_WIDTH_MAX * CAMERA_HEIGHT_MAX);


		for (int i = 0; i < MAX_OF_ROBOT_ID; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_VisionCoreBarPatch_process.m_SegCombination[i][j] = m_propVisionCoreBarPatch_draw.m_SegCombination[i][j];
			}
		}

		for (int j = 0; j < 4; j++)
		{
			m_VisionCoreBarPatch_process.m_SegmentPosition[j] = m_propVisionCoreBarPatch_draw.m_SegmentPosition[j];
		}

		LeaveCriticalSection(&m_critVision);

		m_VisionCoreBarPatch_process.SetScanInterval((int)m_propVisionCoreBarPatch_draw.m_sliderScanInterval.GetValue());
		m_VisionCoreBarPatch_process.SetBallMinMax((int)m_propVisionCoreBarPatch_draw.m_sliderSizeBall.GetValueLeft(), (int)m_propVisionCoreBarPatch_draw.m_sliderSizeBall.GetValueRight());
		m_VisionCoreBarPatch_process.SetOppMinMax((int)m_propVisionCoreBarPatch_draw.m_sliderSizeOpponent.GetValueLeft(), (int)m_propVisionCoreBarPatch_draw.m_sliderSizeOpponent.GetValueRight());

		m_VisionCoreBarPatch_process.SetTeamMinMax((int)m_propVisionCoreBarPatch_draw.m_sliderSizeTeamSegment.GetValueLeft(), (int)m_propVisionCoreBarPatch_draw.m_sliderSizeTeamSegment.GetValueRight());

		m_VisionCoreBarPatch_process.SetSegmentThreshold((int)m_propVisionCoreBarPatch_draw.m_sliderSegmentThreshold.GetValue());
		m_VisionCoreBarPatch_process.SetSegmentCheckDistance((int)m_propVisionCoreBarPatch_draw.m_sliderSegmentCheckSize.GetValue());

		m_VisionCoreBarPatch_process.SetPatchDirectionOffset(m_sliderPatchDirection.GetValue());

		m_VisionCoreBarPatch_process.Run();


		m_ObjectPositionInfo.Reset();
		m_VisionCoreBarPatch_process.UpdateObjectPositionInfo(m_ObjectPositionInfo);

		EnterCriticalSection(&m_critVision);
		m_VisionCoreBarPatch_share.CopyData(m_VisionCoreBarPatch_process);
		LeaveCriticalSection(&m_critVision);
	}


	if( m_propVisionCoreDiagonalPatch_draw.IsActive() )
	{
		EnterCriticalSection( &m_critVision );
		CopyMemory( m_VisionCoreDiagonalPatch_process.m_pProcessingArea, m_propVisionCoreDiagonalPatch_draw.m_pProcessingArea, sizeof(unsigned char)*CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX );
		LeaveCriticalSection( &m_critVision );

		m_VisionCoreDiagonalPatch_process.SetScanInterval( (int)m_propVisionCoreDiagonalPatch_draw.m_sliderScanInterval.GetValue() );
		m_VisionCoreDiagonalPatch_process.SetBallMinMax( (int)m_propVisionCoreDiagonalPatch_draw.m_sliderSizeBall.GetValueLeft(), (int)m_propVisionCoreDiagonalPatch_draw.m_sliderSizeBall.GetValueRight() );
		m_VisionCoreDiagonalPatch_process.SetOppMinMax( (int)m_propVisionCoreDiagonalPatch_draw.m_sliderSizeOpponent.GetValueLeft(), (int)m_propVisionCoreDiagonalPatch_draw.m_sliderSizeOpponent.GetValueRight() );

		m_VisionCoreDiagonalPatch_process.SetTeamMinMax( (int)m_propVisionCoreDiagonalPatch_draw.m_sliderSizeTeam.GetValueLeft(), (int)m_propVisionCoreDiagonalPatch_draw.m_sliderSizeTeam.GetValueRight() );
		m_VisionCoreDiagonalPatch_process.SetIDMinMax( (int)m_propVisionCoreDiagonalPatch_draw.m_sliderSizeID.GetValueLeft(), (int)m_propVisionCoreDiagonalPatch_draw.m_sliderSizeID.GetValueRight() );
		m_VisionCoreDiagonalPatch_process.SetTeamIDDistance( m_propVisionCoreDiagonalPatch_draw.m_sliderSizeTeamIDDistance.GetValueLeft()/100.0 );

		m_VisionCoreDiagonalPatch_process.SetIDSelectData( m_propVisionCoreDiagonalPatch_draw.m_IDSelect );
		
		m_VisionCoreDiagonalPatch_process.SetPatchDirectionOffset( m_sliderPatchDirection.GetValue() );
		m_VisionCoreDiagonalPatch_process.Run();
		m_ObjectPositionInfo.Reset();
		m_VisionCoreDiagonalPatch_process.UpdateObjectPositionInfo( m_ObjectPositionInfo );

		EnterCriticalSection( &m_critVision );
		m_VisionCoreDiagonalPatch_share.CopyData( m_VisionCoreDiagonalPatch_process );
		LeaveCriticalSection( &m_critVision );
	}

	
	if( m_propVisionCoreSegmentPatch_draw.IsActive() )
	{
		EnterCriticalSection( &m_critVision );
		CopyMemory( m_VisionCoreSegmentPatch_process.m_pProcessingArea, m_propVisionCoreSegmentPatch_draw.m_pProcessingArea, sizeof(unsigned char)*CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX );


		for( int i=0 ; i<MAX_OF_ROBOT_ID ; i++ )
		{
			for( int j=0 ; j<6 ; j++ )
			{
				m_VisionCoreSegmentPatch_process.m_SegCombination[i][j] = m_propVisionCoreSegmentPatch_draw.m_SegCombination[i][j];
			}
		}
	
			for( int j=0 ; j<6 ; j++ )
			{
				m_VisionCoreSegmentPatch_process.m_SegmentPosition[j] = m_propVisionCoreSegmentPatch_draw.m_SegmentPosition[j];
			}

		LeaveCriticalSection( &m_critVision );

		m_VisionCoreSegmentPatch_process.SetScanInterval( (int)m_propVisionCoreSegmentPatch_draw.m_sliderScanInterval.GetValue() );
		m_VisionCoreSegmentPatch_process.SetBallMinMax( (int)m_propVisionCoreSegmentPatch_draw.m_sliderSizeBall.GetValueLeft(), (int)m_propVisionCoreSegmentPatch_draw.m_sliderSizeBall.GetValueRight() );
		m_VisionCoreSegmentPatch_process.SetOppMinMax( (int)m_propVisionCoreSegmentPatch_draw.m_sliderSizeOpponent.GetValueLeft(), (int)m_propVisionCoreSegmentPatch_draw.m_sliderSizeOpponent.GetValueRight() );

		m_VisionCoreSegmentPatch_process.SetTeamMinMax( (int)m_propVisionCoreSegmentPatch_draw.m_sliderSizeTeamSegment.GetValueLeft(), (int)m_propVisionCoreSegmentPatch_draw.m_sliderSizeTeamSegment.GetValueRight() );
		m_VisionCoreSegmentPatch_process.SetAssistantMinMax( (int)m_propVisionCoreSegmentPatch_draw.m_sliderSizeAssistant.GetValueLeft(), (int)m_propVisionCoreSegmentPatch_draw.m_sliderSizeAssistant.GetValueRight() );

		m_VisionCoreSegmentPatch_process.SetSegmentThreshold( (int)m_propVisionCoreSegmentPatch_draw.m_sliderSegmentThreshold.GetValue() );
		m_VisionCoreSegmentPatch_process.SetSegmentCheckDistance( 1 );
		m_VisionCoreSegmentPatch_process.SetTeamAssistantDistance( (int)m_propVisionCoreSegmentPatch_draw.m_sliderTeamAssistantDistance.GetValue()/100.0 );
		
		m_VisionCoreSegmentPatch_process.SetPatchDirectionOffset( m_sliderPatchDirection.GetValue() );

		m_VisionCoreSegmentPatch_process.Run();


		m_ObjectPositionInfo.Reset();
		m_VisionCoreSegmentPatch_process.UpdateObjectPositionInfo( m_ObjectPositionInfo );

		EnterCriticalSection( &m_critVision );
		m_VisionCoreSegmentPatch_share.CopyData( m_VisionCoreSegmentPatch_process );
		LeaveCriticalSection( &m_critVision );
	}
	
	
	for( int i=0 ; i<POSITION_INFO_ROBOT_N ; i++ )
	{
		if( m_ObjectPositionInfo.m_Robot[i].state == OBJECT_STATE_REAL )
			m_VisionTest.robot[i].bFound[ m_VisionTest.count ] = true;
		else
			m_VisionTest.robot[i].bFound[ m_VisionTest.count ] = false;

		int countLoss = 0;
		for( int t=0 ; t<100 ; t++ )
		{
			if( m_VisionTest.robot[i].bFound[t] == false )
				countLoss++; 
		}
		m_VisionTest.robot[i].countLoss = countLoss;
	}

	m_VisionTest.count = (m_VisionTest.count+1)%100;
}


void CPropertyPageVision::OnBnClickedOpenVision()
{
	UpdateData(TRUE);
	
	TCHAR szFilter[] = _T("Vision Setting File(*.VS)|*.VS|All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("default"), _T("default"), NULL, szFilter);
	
	if( dlg.DoModal() == IDOK )
	{
		BeginWaitCursor();
		OpenFile( dlg.GetPathName() );
		EndWaitCursor();
	}	
	
	UpdateData(FALSE);
}


void CPropertyPageVision::OnBnClickedSaveVision()
{
	UpdateData(TRUE);
	
	TCHAR szFilter[] = _T("Vision Setting File(*.VS)|*.VS|All Files(*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("default"), _T("default"), NULL, szFilter);
	
	if( dlg.DoModal() == IDOK )
	{
		BeginWaitCursor();
		SaveFile( dlg.GetPathName() );
		EndWaitCursor();	
	}
	
	UpdateData(FALSE);	
}


void CPropertyPageVision::OpenFile(CString filename)
{
	m_strFileName = filename;

	CFile file;

	if( file.Open(filename, CFile::modeRead ) == FALSE )
	{
		AfxMessageBox(_T("Failed to open file. (CPropertyPageVision::OpenFile)"));
		return;
	}

	CArchive ar( &file, CArchive::load );


	CString version;
	ar >> version;

	CString tmp;

	while(1)
	{
		ar >> tmp;

		if( tmp == _T("- END : Vision -") )
			break;

		if( tmp == _T("Flat Points") )
		{
			m_FlatPoints.OpenFile( ar );
		}

		if( tmp == _T("Flat Points - ball") )
		{
			m_FlatPoints_ball.OpenFile( ar );
		}

		if( tmp == _T("Revision") )
		{
			double value;
			ar >> value;
			m_sliderRevisionK.SetValue( value );
			ar >> value;
			m_sliderRevisionZoom.SetValue( value );

			m_revision.OpenFile( ar );
		}

		if( tmp == _T("Revision - ball") )
		{
			double value;
			ar >> value;
			m_sliderRevisionK.SetValue( value );
			ar >> value;
			m_sliderRevisionZoom.SetValue( value );

			m_revision_ball.OpenFile( ar );
		}


		if( tmp == _T("Ground Mapping Area") )
		{
			m_rectGroundMappingArea.OpenFile( ar );
		}

		if( tmp == _T("Vision Algorithm : Diagonal Patch") )
		{
			EnterCriticalSection(&m_critVision);
			m_propVisionCoreDiagonalPatch_draw.OpenFile( ar );
			LeaveCriticalSection(&m_critVision);
		}

		if( tmp == _T("Vision Algorithm : Segment Patch") )
		{
		}

		if( tmp == _T("Vision Algorithm : Segment Patch*") )
		{
			EnterCriticalSection(&m_critVision);
			m_propVisionCoreSegmentPatch_draw.OpenFile( ar );
			LeaveCriticalSection(&m_critVision);
		}

		if( tmp == _T("Vision Algorithm : Bar Patch") )
		{
			EnterCriticalSection(&m_critVision);
			m_propVisionCoreBarPatch_draw.OpenFile( ar );
			LeaveCriticalSection(&m_critVision);
		}

		if( tmp == _T("Patch Direction") )
		{
			double value;
			ar >> value;
			m_sliderPatchDirection.SetValue( value );
		}

		if( tmp ==_T("Vision Algorithm Type") )
		{
			int activeVisionCore;
			ar >> activeVisionCore;
			
			//m_PropertySheetVisionCore.SetActivePage(activeVisionCore);
		}
	}

	RevisionUpdate();

	ar.Close();
	file.Close();
}


void CPropertyPageVision::SaveFile(CString filename)
{
	m_strFileName = filename;

	CFile file;

	file.Open( filename, CFile::modeCreate | CFile::modeWrite );
	CArchive ar( &file, CArchive::store );

	
	ar << CString(ROBOT_SOCCER_VERSION);

	ar << CString("Flat Points");
	m_FlatPoints.SaveFile( ar );

	ar << CString("Flat Points - ball");
	m_FlatPoints_ball.SaveFile( ar );

	ar << CString("Revision");
	ar << m_sliderRevisionK.GetValue();
	ar << m_sliderRevisionZoom.GetValue();
	m_revision.SaveFile( ar );

	ar << CString("Revision - ball");
	ar << m_sliderRevisionK.GetValue();
	ar << m_sliderRevisionZoom.GetValue();
	m_revision_ball.SaveFile( ar );

	ar << CString("Ground Mapping Area");
	m_rectGroundMappingArea.SaveFile( ar );


	EnterCriticalSection(&m_critVision);

	ar << CString("Vision Algorithm : Diagonal Patch");
	m_propVisionCoreDiagonalPatch_draw.SaveFile( ar );

	ar << CString("Vision Algorithm : Segment Patch*");
	m_propVisionCoreSegmentPatch_draw.SaveFile( ar );

	ar << CString("Vision Algorithm : Bar Patch");
	m_propVisionCoreBarPatch_draw.SaveFile( ar );

	ar << CString("Vision Algorithm Type");
	int activeVisionCore = 0;
	if( m_propVisionCoreDiagonalPatch_draw.IsActive() )
	{
		activeVisionCore = 0;
	}
	else
	if( m_propVisionCoreSegmentPatch_draw.IsActive() )
	{
		activeVisionCore = 1;
	}
	else
	if( m_propVisionCoreBarPatch_draw.IsActive() )
	{
		activeVisionCore = 2;
	}
	ar << activeVisionCore;

	LeaveCriticalSection(&m_critVision);

	// Patch Direction
	ar << CString("Patch Direction");
	ar << m_sliderPatchDirection.GetValue();

	ar << CString("- END : Vision -");

	ar.Close();
	file.Close();

	UpdateData(FALSE);
}

CObjectPositionInfo CPropertyPageVision::GetObjectInfo()
{
	return m_ObjectPositionInfo;
}


void CPropertyPageVision::OnBnClickedCheckRobotAll(){ UpdateData(TRUE); }
void CPropertyPageVision::OnBnClickedCheckRobot01(){ UpdateData(TRUE); }
void CPropertyPageVision::OnBnClickedCheckRobot02(){ UpdateData(TRUE); }
void CPropertyPageVision::OnBnClickedCheckRobot03(){ UpdateData(TRUE); }
void CPropertyPageVision::OnBnClickedCheckRobot04(){ UpdateData(TRUE); }
void CPropertyPageVision::OnBnClickedCheckRobot05(){ UpdateData(TRUE); }
void CPropertyPageVision::OnBnClickedCheckRobot06(){ UpdateData(TRUE); }
void CPropertyPageVision::OnBnClickedCheckRobot07(){ UpdateData(TRUE); }
void CPropertyPageVision::OnBnClickedCheckRobot08(){ UpdateData(TRUE); }
void CPropertyPageVision::OnBnClickedCheckRobot09(){ UpdateData(TRUE); }
void CPropertyPageVision::OnBnClickedCheckRobot10(){ UpdateData(TRUE); }
void CPropertyPageVision::OnBnClickedCheckRobot11(){ UpdateData(TRUE); }


