// PropertyPageVisionCoreBarPatch.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "PropertyPageVisionCoreBarPatch.h"


// CPropertyPageVisionCoreBarPatch

IMPLEMENT_DYNAMIC(CPropertyPageVisionCoreBarPatch, CPropertyPageRobotSoccer)

CPropertyPageVisionCoreBarPatch::CPropertyPageVisionCoreBarPatch()
	: CPropertyPageRobotSoccer(CPropertyPageVisionCoreBarPatch::IDD)
	, m_bScanningInterval(FALSE)
	, m_bBall(FALSE)
	, m_bOpponent(FALSE)
	, m_bTeamSegment(FALSE)
	, m_bEditSegmentInformation(FALSE)
	, m_bEditSegmentPosition(FALSE)
	, m_bInverseSegmentImage(FALSE)
	, m_bTeamColorOnly(FALSE)
	, m_bAntiBlack(FALSE)
{
	m_selectSegmentID = -1;
}

CPropertyPageVisionCoreBarPatch::~CPropertyPageVisionCoreBarPatch()
{
}


void CPropertyPageVisionCoreBarPatch::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageRobotSoccer::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR_PICK_SCAN_INTERVAL, m_colorpickScanInterval);
	DDX_Control(pDX, IDC_COLOR_PICK_BALL, m_colorpickBall);
	DDX_Control(pDX, IDC_COLOR_PICK_OPPONENT, m_colorpickOpponent);
	DDX_Control(pDX, IDC_COLOR_PICK_TEAM_SEGMENT, m_colorpickTeamSegment);
	//  DDX_Control(pDX, IDC_COLOR_PICK_ASSISTANT1, m_colorpickAssistant1);
	//  DDX_Control(pDX, IDC_COLOR_PICK_ASSISTANT2, m_colorpickAssistant2);
	//  DDX_Control(pDX, IDC_COLOR_PICK_TEAM_ASSISTANT_DISTANCE, m_colorpickTeamAssistantDistance);
	DDX_Check(pDX, IDC_CHECK_SCANNING_INTERVAL, m_bScanningInterval);
	DDX_Check(pDX, IDC_CHECK_BALL, m_bBall);
	DDX_Check(pDX, IDC_CHECK_OPPONENT, m_bOpponent);
	DDX_Check(pDX, IDC_CHECK_TEAM_SEGMENT, m_bTeamSegment);
	//  DDX_Check(pDX, IDC_CHECK_ASSISTANT1, m_bAssistant1);
	//  DDX_Check(pDX, IDC_CHECK_ASSISTANT2, m_bAssistant2);
	//  DDX_Check(pDX, IDC_CHECK_TEAM_ASSISTANT_DISTANCE, m_bTeamAssistantDistance);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SCAN_INTERVAL, m_sliderScanInterval);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_BALL, m_sliderSizeBall);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_OPPONENT, m_sliderSizeOpponent);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_TEAM_SEGMENT, m_sliderSizeTeamSegment);
	//  DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_ASSISTANT, m_sliderSizeAssistant);
	//  DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_TEAM_ASSISTANT_DISTANCE, m_sliderTeamAssistantDistance);
	DDX_Check(pDX, IDC_CHECK_EDIT_SEGMENT_INFORMATION, m_bEditSegmentInformation);
	DDX_Check(pDX, IDC_CHECK_EDIT_SEGMENT_POSITION, m_bEditSegmentPosition);
	DDX_Control(pDX, IDC_COMBO_ROBOT_ID, m_comboRobotID);
	DDX_Control(pDX, IDC_COLOR_PICK_SEGMENT_MARKER, m_colorpickSegmentMarker);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SEGMENT_THRESHOLD, m_sliderSegmentThreshold);
	DDX_Check(pDX, IDC_CHECK_INVERSE_SEGMENT_IMAGE, m_bInverseSegmentImage);
	DDX_Check(pDX, IDC_CHECK_TEAM_COLOR_ONLY, m_bTeamColorOnly);
	DDX_Check(pDX, IDC_CHECK_ANTI_BLACK, m_bAntiBlack);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SEGMENT_CHECK_SIZE, m_sliderSegmentCheckSize);
}

BEGIN_MESSAGE_MAP(CPropertyPageVisionCoreBarPatch, CPropertyPageRobotSoccer)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_SCANNING_INTERVAL, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckScanningInterval)
	ON_BN_CLICKED(IDC_CHECK_BALL, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckBall)
	ON_BN_CLICKED(IDC_CHECK_OPPONENT, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckOpponent)
	ON_BN_CLICKED(IDC_CHECK_TEAM_SEGMENT, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckTeamSegment)
//	ON_BN_CLICKED(IDC_CHECK_ASSISTANT1, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckAssistant1)
//	ON_BN_CLICKED(IDC_CHECK_ASSISTANT2, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckAssistant2)
//	ON_BN_CLICKED(IDC_CHECK_TEAM_ASSISTANT_DISTANCE, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckTeamAssistantDistance)
//	ON_BN_CLICKED(IDC_CHECK_DRAW_TEAM_WITHOUT_SEGMENT, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckDrawTeamWithoutSegment)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECK_EDIT_SEGMENT_INFORMATION, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckEditSegmentInformation)
	ON_BN_CLICKED(IDC_CHECK_EDIT_SEGMENT_POSITION, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckEditSegmentPosition)
	ON_CBN_SELCHANGE(IDC_COMBO_ROBOT_ID, &CPropertyPageVisionCoreBarPatch::OnSelchangeComboRobotId)
	ON_BN_CLICKED(IDC_CHECK_INVERSE_SEGMENT_IMAGE, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckInverseSegmentImage)
	ON_BN_CLICKED(IDC_CHECK_TEAM_COLOR_ONLY, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckTeamColorOnly)
	ON_BN_CLICKED(IDC_CHECK_ANTI_BLACK, &CPropertyPageVisionCoreBarPatch::OnBnClickedCheckAntiBlack)
END_MESSAGE_MAP()



// CPropertyPageVisionCoreBarPatch message handlers


BOOL CPropertyPageVisionCoreBarPatch::OnInitDialog()
{
	__super::OnInitDialog();

	m_colorpickScanInterval.SetColor( RGB(0,255,0) );

	m_colorpickScanInterval.SetEditable(TRUE);
	m_colorpickBall.SetEditable(FALSE);
	m_colorpickOpponent.SetEditable(FALSE);


	m_sliderScanInterval.SetOption( _T("Dist for Colour Detection"), false, 1, 200, 1, 0 );
	m_sliderScanInterval.SetValue( 26 );

	m_sliderSizeBall.SetOption( _T("Ball Colour"), true, 1, 1000, 1, 0 );
	m_sliderSizeBall.SetValue( 50, 200 );

	m_sliderSizeOpponent.SetOption( _T("Opponent Colour"), true, 1, 1000, 1, 0 );
	m_sliderSizeOpponent.SetValue( 50, 200 );


	m_sliderSizeTeamSegment.SetOption( _T("Team Colour"), true, 1, 1000, 1, 0 );
	m_sliderSizeTeamSegment.SetValue( 50, 480 );
	
	
	
	m_colorpickTeamSegment.SetEditable( FALSE );
	

	m_colorpickSegmentMarker.SetColor( RGB(255,255,255) );


	
	m_sliderSegmentCheckSize.SetOption( _T("Check Pos."), false, 1, 10, 1, 0 );
	m_sliderSegmentCheckSize.SetValue( 1 );

	m_sliderSegmentThreshold.SetOption( _T("Threshold"), false, 1, 5, 1, 0 );
	m_sliderSegmentThreshold.SetValue( 2 );


	{
		CClientDC dc(this);
		CRect rect;
		GetDlgItem(IDC_FRAME_ROBOT_SEGMENT)->GetWindowRect( rect );
		ScreenToClient(rect);
		m_dcRobotSegment.Init( &dc, rect );
	}

	for( int i=0 ; i<MAX_OF_ROBOT_ID ; i++ )
	{
		CString tmp;
		tmp.Format(_T("Robot-%02d"), i+1 );
		m_comboRobotID.AddString( tmp );
	}

	m_comboRobotID.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPropertyPageVisionCoreBarPatch::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	m_colorpickBall.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_0 ) );
	m_colorpickOpponent.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_7 ) );
	m_colorpickTeamSegment.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_4 ) );
}

void CPropertyPageVisionCoreBarPatch::DrawDisplay( BOOL bMasking, COLORREF colorMask )
{
	if( m_bScanningInterval )
	{
		for( int p=0 ; p<m_pDC->Width()*m_pDC->Height() ; p+=(int)m_sliderScanInterval.GetValue() )
		{
			int i = p%m_pDC->Width();
			int j = p/m_pDC->Width();

			m_pDC->SetPixel( i, j, m_colorpickScanInterval.GetColor() );
		}
	}

	// Drawing the selected colour onto the camera

	if( m_bBall )
	{
		COLORREF color = m_colorpickBall.GetColor();
		if( bMasking )
			color = colorMask;
		Draw_BallPatch( m_pDC, color );
	}


	if( m_bOpponent )
	{
		COLORREF color = m_colorpickOpponent.GetColor();
		if( bMasking )
			color = colorMask;
		Draw_OpponentsPatch( m_pDC, color );
	}

	if( m_bTeamSegment )
	{
		COLORREF color = m_colorpickTeamSegment.GetColor();
		if( bMasking )
			color = colorMask;
		Draw_TeamPatch( m_pDC, color );
	}



	CString tmp;
	//tmp.Format(_T("%d"), m_countTest );
	m_pDC->TextOut( 10, 10, tmp );

	//if( m_bSelectRobotPosition )
	{
		CPen pen, *pOldPen;
		pen.CreatePen( PS_SOLID, 1, RGB(0,255,0) );
		pOldPen = (CPen*)m_pDC->SelectObject( &pen );

		m_pDC->SelectStockObject( NULL_BRUSH );

		m_pDC->Circle( (int)m_SelectRobotPosition.x, (int)m_SelectRobotPosition.y, 20 );

		m_pDC->SelectObject( pOldPen );			
	}

	// Drawing of the segment info
	if( m_bEditSegmentInformation )
	{
		CRect rectRobot( -40, -40, 40, 40 );
		CRect rectTeam( -14, -35, 14, 35 );
		CRect rectSeg[4];
		// screen y = -y
		rectSeg[0] = CRect( -8, -16, 8, 16 ) + CPoint(-28, -19);
		rectSeg[1] = CRect( -8, -16, 8, 16 ) + CPoint( 28, -19);
		rectSeg[2] = CRect( -8, -16, 8, 16 ) + CPoint(-28,  19);
		rectSeg[3] = CRect( -8, -16, 8, 16 ) + CPoint( 28,  19);


		for( int i=0 ; i<ROBOT_SOCCER_RROGRAM_ROBOT_N ; i++ )
		{
			CPoint posRobot(0,0);
			if( ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_3 )
				posRobot = CPoint( 580, i*90 + 60 + 90*2 );
			if( ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_5 )
				posRobot = CPoint( 580,  i*90 + 60 );
			//posRobot = CPoint( i*100 + 120, 430 );

			m_pDC->SelectPen( RGB(255,255,255) );
			m_pDC->SelectBrush( RGB(0,0,0) );
			m_pDC->Rectangle( rectRobot + posRobot );

			m_pDC->SelectPen( m_colorpickTeamSegment.GetColor() );
			m_pDC->SelectBrush( m_colorpickTeamSegment.GetColor() );
			m_pDC->Rectangle( rectTeam  + posRobot );

			m_pDC->SetBkMode( OPAQUE );
			m_pDC->SetBkColor( RGB( 0,0,0 ) );
			m_pDC->SetTextColor( RGB( 255,255,255 ) );

			CString tmp;
			tmp.Format(_T("[%d]"), i+1 ); // Printing the ID number
			m_pDC->DrawText( tmp, rectTeam  + posRobot, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

			// Setting the colour of the pen and brush dependong on the Segment value
			for( int s=0 ; s<4 ; s++ )
			{
				if( m_SegCombination[i][s] == 0 )
				{
					m_pDC->SelectPen( RGB(0,0,0) );
					m_pDC->SelectBrush( RGB(0,0,0) );
				}
				if( m_SegCombination[i][s] == 1 )
				{
					m_pDC->SelectPen( RGB(255,255,255) );
					m_pDC->SelectBrush( RGB(255,255,255) );
				}
				if( m_SegCombination[i][s] == -1 )
				{
					m_pDC->SelectPen( RGB(255,255,255) );
					m_pDC->SelectBrush( false );
				}

				m_pDC->Rectangle( rectSeg[s]  + posRobot );
			}
		}
	}
}

void CPropertyPageVisionCoreBarPatch::Display_RobotSegment( BOOL bShowCameraImage, BOOL bMasking, COLORREF colorMask )
{
	CClientDC dc(this);

	{
		CBrush brush, *pOldBrush;
		brush.CreateSolidBrush( RGB(0,0,0) );

		pOldBrush = (CBrush*)m_dcRobotSegment.SelectObject( &brush );
								
		CRect rect = m_dcRobotSegment.GetRect();
		m_dcRobotSegment.Rectangle( rect - rect.TopLeft() );
				
		m_dcRobotSegment.SelectObject( pOldBrush );
	}

	// Selecting the colour of the segement depending on the combination value 
	if( m_bEditSegmentInformation )
	{
		int robot_id = m_comboRobotID.GetCurSel();

		for( int s=0 ; s<4 ; s++ )
		{
			int dc_x = (int)(m_SegmentPosition[s].x*10 + m_dcRobotSegment.Width()/2);
			int dc_y = (int)(-m_SegmentPosition[s].y*10 + m_dcRobotSegment.Height()/2);

			COLORREF colorPen = RGB(255,0,0);
			COLORREF colorBrush = RGB(0,0,0);

			if( m_SegCombination[robot_id][s] == 1 )
			{
				colorBrush = RGB(255,0,0);
			}
			if( m_SegCombination[robot_id][s] == -1 )
			{
				colorBrush = RGB(192,192,192);
			}

			CPen pen, *pOldPen;
			pen.CreatePen( PS_SOLID, 1, colorPen );
			pOldPen = (CPen*)m_dcRobotSegment.SelectObject( &pen );

			CBrush brush, *pOldBrush;
			brush.CreateSolidBrush( colorBrush );
			pOldBrush = (CBrush*)m_dcRobotSegment.SelectObject( &brush );

			m_dcRobotSegment.Circle( dc_x, dc_y, 5 );
				
			m_dcRobotSegment.SelectObject( pOldBrush );
			m_dcRobotSegment.SelectObject( pOldPen );
		}
	}
	else
	{
		// Draw Select Robot
		{
			//Display_RobotImage( &m_dcRobotSegment, m_dcRobotSegment.Width(), m_dcRobotSegment.Height(), -1 );
		}

		// Draw Segment
		{
			m_dcRobotSegment.SelectBrush( false );
			m_dcRobotSegment.SelectPen( RGB(255,255,255) );

			Display_SegmentImage( &m_dcRobotSegment, m_dcRobotSegment.Width(), m_dcRobotSegment.Height(),
				m_bInverseSegmentImage, m_bAntiBlack, m_bTeamColorOnly, m_colorpickSegmentMarker.GetColor(), RGB(128,128,128),
				bMasking, colorMask,
				FALSE, RGB(0,0,0), -1 );
		}
	}

	if( m_bEditSegmentPosition )
	{
		for( int s=0 ; s<4 ; s++ )
		{
			int dc_x = (int)(m_SegmentPosition[s].x*10 + m_dcRobotSegment.Width()/2);
			int dc_y = (int)(-m_SegmentPosition[s].y*10 + m_dcRobotSegment.Height()/2);

			// This is the edit segment position
			COLORREF color = RGB(255,0,0);

			if( s == m_selectSegmentID )
			{
				color = RGB(0,255,0);
			}

			CPen pen, *pOldPen;
			pen.CreatePen( PS_SOLID, 1, color );
			pOldPen = (CPen*)m_dcRobotSegment.SelectObject( &pen );
			m_dcRobotSegment.SelectStockObject( NULL_BRUSH );

			int size = m_valueSegmentCheckDistance;
			m_dcRobotSegment.Square( dc_x, dc_y, size );

			if( s == m_selectSegmentID )
			{
				//size += 5;
				m_dcRobotSegment.Square( dc_x, dc_y, size );

				int k=10;
				m_dcRobotSegment.MoveTo( dc_x-m_valueSegmentCheckDistance*k  , dc_y );
				m_dcRobotSegment.LineTo( dc_x+m_valueSegmentCheckDistance*k+1, dc_y );
				
				m_dcRobotSegment.MoveTo( dc_x, dc_y-m_valueSegmentCheckDistance*k   );
				m_dcRobotSegment.LineTo( dc_x, dc_y+m_valueSegmentCheckDistance*k+1 );
			}

			m_dcRobotSegment.SelectObject( pOldPen );
		}

		//CString tmp;
		//tmp.Format(_T("%d"), m_valueSegmentCheckDistance );
		//m_dcRobotSegment.TextOut( 5, 5, tmp );
	}

	
	m_dcRobotSegment.BitBlt( &dc );
}

void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckScanningInterval()
{
	UpdateData(TRUE);
}
void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckBall(){ UpdateData(TRUE); }
void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckOpponent(){ UpdateData(TRUE); }
void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckTeamSegment(){ UpdateData(TRUE); }
//void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckAssistant1(){ UpdateData(TRUE); }
//void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckAssistant2(){ UpdateData(TRUE); }
//void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckTeamAssistantDistance(){ UpdateData(TRUE); }



void CPropertyPageVisionCoreBarPatch::VisionRun()
{
	SetScanInterval( (int)m_sliderScanInterval.GetValue() );
	SetBallMinMax( (int)m_sliderSizeBall.GetValueLeft(), (int)m_sliderSizeBall.GetValueRight() );
	SetOppMinMax( (int)m_sliderSizeOpponent.GetValueLeft(), (int)m_sliderSizeOpponent.GetValueRight() );

	SetTeamMinMax( (int)m_sliderSizeTeamSegment.GetValueLeft(), (int)m_sliderSizeTeamSegment.GetValueRight() );


	SetSegmentCheckDistance( (int)m_sliderSegmentCheckSize.GetValueLeft() );

	SetSegmentThreshold( (int)m_sliderSegmentThreshold.GetValueLeft() );
	//SetSegmentCheckDistance( 1 );




	/*
	{
		CPointDouble seg_pos[6];
		for( int i=0 ; i<6 ; i++ )
		{
			seg_pos[i].x = m_listSegment.GetItemDouble( i, 0 ) * m_sliderSizeSegment.GetValueMin();
			seg_pos[i].y = m_listSegment.GetItemDouble( i, 1 ) * m_sliderSizeSegment.GetValueMin();
		}
		SetSegmentPosition( seg_pos );
	}
	{
		int matching_data[11][6];
		for( int row=0 ; row<11 ; row++ )
			for( int col=1 ; col<=6 ; col++ )
			{
				CString text = m_listSegCombination.GetItemText( row, col );
				if( text == _T("o") ) matching_data[row][col-1] =  1;
				if( text == _T(".") ) matching_data[row][col-1] =  0;
				if( text == _T("-") ) matching_data[row][col-1] = -1;
			}

		m_VisionCore_Segment.SetSegmentCombination( matching_data );
	}
	*/

	Run();
/*
	SetScanInterval( (int)m_sliderScanInterval.GetValue() );
	SetBallMinMax( (int)m_sliderSizeBall.GetValueLeft(), (int)m_sliderSizeBall.GetValueRight() );
	SetOppMinMax( (int)m_sliderSizeOpponent.GetValueLeft(), (int)m_sliderSizeOpponent.GetValueRight() );

	SetTeamMinMax( (int)m_sliderSizeTeam.GetValueLeft(), (int)m_sliderSizeTeam.GetValueRight() );
	SetIDMinMax( (int)m_sliderSizeID.GetValueLeft(), (int)m_sliderSizeID.GetValueRight() );
	SetTeamIDDistance( m_sliderSizeTeamIDDistance.GetValueLeft()/100.0, m_sliderSizeTeamIDDistance.GetValueRight()/100.0 );

	SetIDSelectData( m_IDSelect );

	Run();
*/
}



void CPropertyPageVisionCoreBarPatch::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( m_dcRobotSegment.IsPointInRect( point ) )
	{
		if( m_bEditSegmentPosition )
		{
			CPointDouble posMouse = point - m_dcRobotSegment.TopLeft();

			m_selectSegmentID = -1;

			for( int s=0 ; s<4 ; s++ )
			{
				CPointDouble posSeg;
				posSeg.x = (int)(m_SegmentPosition[s].x*10 + m_dcRobotSegment.Width()/2);
				posSeg.y = (int)(-m_SegmentPosition[s].y*10 + m_dcRobotSegment.Height()/2);

				if( (posSeg-posMouse).Distance() < 5 )
				{
					m_selectSegmentID = s;
				}
			}
		}

		if( m_bEditSegmentInformation )
		{
			CPointDouble posMouse = point - m_dcRobotSegment.TopLeft();

			m_selectSegmentID = -1;

			for( int s=0 ; s<4 ; s++ )
			{
				CPointDouble posSeg;
				posSeg.x = (int)(m_SegmentPosition[s].x*10 + m_dcRobotSegment.Width()/2);
				posSeg.y = (int)(-m_SegmentPosition[s].y*10 + m_dcRobotSegment.Height()/2);

				if( (posSeg-posMouse).Distance() < 5 )
				{
					m_selectSegmentID = s;
				}
			}

			int robot_id = m_comboRobotID.GetCurSel();

			// Updating the segment combination upon each click
			if( m_selectSegmentID >= 0 )
			{
				if( m_SegCombination[robot_id][m_selectSegmentID] == 1 )
					m_SegCombination[robot_id][m_selectSegmentID] = 0;
				else
				if( m_SegCombination[robot_id][m_selectSegmentID] == 0 )
					m_SegCombination[robot_id][m_selectSegmentID] = -1;
				else
				if( m_SegCombination[robot_id][m_selectSegmentID] == -1 )
					m_SegCombination[robot_id][m_selectSegmentID] = 1;
			}
		}
	}

	__super::OnLButtonDown(nFlags, point);
}


BOOL CPropertyPageVisionCoreBarPatch::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_KEYDOWN && m_bEditSegmentPosition && m_selectSegmentID >= 0 )
    {
        switch( pMsg->wParam )
		{
            case VK_UP:
			case VK_NUMPAD8 :
				{
					m_SegmentPosition[ m_selectSegmentID ].y += 0.1;
					return TRUE;
				}
				break;
            case VK_DOWN:
			case VK_NUMPAD2 :
				{
					m_SegmentPosition[ m_selectSegmentID ].y -= 0.1;
					return TRUE;
				}
				break;
            case VK_LEFT:
			case VK_NUMPAD4 :
				{
					m_SegmentPosition[ m_selectSegmentID ].x -= 0.1;
					return TRUE;
				}
				break;
            case VK_RIGHT:
			case VK_NUMPAD6 :
				{
					m_SegmentPosition[ m_selectSegmentID ].x += 0.1;
					return TRUE;
				}
				break;
			case VK_PRIOR :
				{
					m_valueSegmentCheckDistance++;
					return TRUE;
				}
				break;
			case VK_NEXT :
				{
					m_valueSegmentCheckDistance--;

					if( m_valueSegmentCheckDistance < 1 )
						m_valueSegmentCheckDistance = 1;

					return TRUE;
				}
				break;
            default:
                break;
		}
    }

	return __super::PreTranslateMessage(pMsg);
}



void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckEditSegmentInformation()
{
	UpdateData(TRUE);

	if( m_bEditSegmentInformation )
	{
		if( m_bEditSegmentPosition )
		{
			m_bEditSegmentPosition = FALSE;
			UpdateData(FALSE);
		}
	}
}


void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckEditSegmentPosition()
{
	UpdateData(TRUE);

	if( m_bEditSegmentPosition )
	{
		if( m_bEditSegmentInformation )
		{
			m_bEditSegmentInformation = FALSE;
			UpdateData(FALSE);
		}
	}
}


void CPropertyPageVisionCoreBarPatch::OnSelchangeComboRobotId()
{
	UpdateData(TRUE);
}

void CPropertyPageVisionCoreBarPatch::OpenFile(CArchive &ar)
{
	CString tmp;

	while(1)
	{
		ar >> tmp;

		if( tmp == _T("- END : VisionCoreSegmentPatch -") )
			break;

		if( tmp == _T("Scan Interval") )
		{
			double value;
			ar >> value;
			m_sliderScanInterval.SetValue( value );
		}

		if( tmp == _T("Ball") )
		{
			double value1, value2;
			ar >> value1;
			ar >> value2;
			m_sliderSizeBall.SetValue( value1, value2 );
		}

		if( tmp == _T("Opponent") )
		{
			double value1, value2;
			ar >> value1;
			ar >> value2;
			m_sliderSizeOpponent.SetValue( value1, value2 );
		}

		if( tmp == _T("TeamSegment") )
		{
			double value1,value2;
			ar >> value1;
			ar >> value2;
			m_sliderSizeTeamSegment.SetValue( value1, value2 );
		}


		if( tmp == _T("Segment Threshold") )
		{
			double value;
			ar >> value;
			m_sliderSegmentThreshold.SetValue( value );
		}

		if( tmp == _T("Segment Position") )
		{
			for( int j=0 ; j<4 ; j++ )
			{
				ar >> m_SegmentPosition[j].x;
				ar >> m_SegmentPosition[j].y;
			}
		}

		if( tmp == _T("Robot-Segment Information") )
		{
			int robot_i;
			ar >> robot_i;

			for( int j=0 ; j<4 ; j++ )
			{
				int segcombination;
				ar >> segcombination;

				if( robot_i < MAX_OF_ROBOT_ID )
					m_SegCombination[robot_i][j] = segcombination;
			}
		}

		if( tmp == _T("ProcessingArea") )
		{
			for( int p=0 ; p<CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX ; p++ )
				ar >> m_pProcessingArea[p];
		}
	}

	Invalidate(TRUE);
}

void CPropertyPageVisionCoreBarPatch::SaveFile(CArchive &ar)
{
	ar << CString("Scan Interval");
	ar << m_sliderScanInterval.GetValue();

	ar << CString("Ball");
	ar << m_sliderSizeBall.GetValueLeft();
	ar << m_sliderSizeBall.GetValueRight();

	ar << CString("Opponent");
	ar << m_sliderSizeOpponent.GetValueLeft();
	ar << m_sliderSizeOpponent.GetValueRight();

	ar << CString("TeamSegment");
	ar << m_sliderSizeTeamSegment.GetValueLeft();
	ar << m_sliderSizeTeamSegment.GetValueRight();
	
	ar << CString("Segment Threshold");
	ar << m_sliderSegmentThreshold.GetValue();


		ar << CString("Segment Position");
		for( int j=0 ; j<4 ; j++ )
		{
			ar << m_SegmentPosition[j].x;
			ar << m_SegmentPosition[j].y;
		}

	for( int i=0 ; i<MAX_OF_ROBOT_ID ; i++ )
	{
		ar << CString("Robot-Segment Information");
		ar << i;

		for( int j=0 ; j<4 ; j++ )
		{
			ar << m_SegCombination[i][j];
		}
	}

	ar << CString("ProcessingArea");
	for( int p=0 ; p<CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX ; p++ )
			ar << m_pProcessingArea[p];

	ar << CString("- END : VisionCoreSegmentPatch -");
}


void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckInverseSegmentImage()
{
	UpdateData(TRUE);
}


void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckTeamColorOnly()
{
	UpdateData(TRUE);
}


void CPropertyPageVisionCoreBarPatch::OnBnClickedCheckAntiBlack()
{
	UpdateData(TRUE);
}
