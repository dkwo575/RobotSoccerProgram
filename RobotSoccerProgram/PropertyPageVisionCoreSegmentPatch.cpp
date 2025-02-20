// PropertyPageVisionCoreSegmentPatch.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "PropertyPageVisionCoreSegmentPatch.h"
#include "afxdialogex.h"


// CPropertyPageVisionCoreSegmentPatch dialog

IMPLEMENT_DYNAMIC(CPropertyPageVisionCoreSegmentPatch, CPropertyPageRobotSoccer)

CPropertyPageVisionCoreSegmentPatch::CPropertyPageVisionCoreSegmentPatch()
	: CPropertyPageRobotSoccer(CPropertyPageVisionCoreSegmentPatch::IDD)
	, m_bScanningInterval(FALSE)
	, m_bBall(FALSE)
	, m_bOpponent(FALSE)
	, m_bTeamSegment(FALSE)
	, m_bAssistant1(FALSE)
	, m_bAssistant2(FALSE)
	, m_bTeamAssistantDistance(FALSE)
	, m_bDrawTeamWithoutSegment(FALSE)
	, m_bEditSegmentInformation(FALSE)
	, m_bEditSegmentPosition(FALSE)
{
	m_selectSegmentID = -1;
}

CPropertyPageVisionCoreSegmentPatch::~CPropertyPageVisionCoreSegmentPatch()
{
}

void CPropertyPageVisionCoreSegmentPatch::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageRobotSoccer::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR_PICK_SCAN_INTERVAL, m_colorpickScanInterval);
	DDX_Control(pDX, IDC_COLOR_PICK_BALL, m_colorpickBall);
	DDX_Control(pDX, IDC_COLOR_PICK_OPPONENT, m_colorpickOpponent);
	DDX_Control(pDX, IDC_COLOR_PICK_TEAM_SEGMENT, m_colorpickTeamSegment);
	DDX_Control(pDX, IDC_COLOR_PICK_ASSISTANT1, m_colorpickAssistant1);
	DDX_Control(pDX, IDC_COLOR_PICK_ASSISTANT2, m_colorpickAssistant2);
	DDX_Control(pDX, IDC_COLOR_PICK_TEAM_ASSISTANT_DISTANCE, m_colorpickTeamAssistantDistance);
	DDX_Check(pDX, IDC_CHECK_SCANNING_INTERVAL, m_bScanningInterval);
	DDX_Check(pDX, IDC_CHECK_BALL, m_bBall);
	DDX_Check(pDX, IDC_CHECK_OPPONENT, m_bOpponent);
	DDX_Check(pDX, IDC_CHECK_TEAM_SEGMENT, m_bTeamSegment);
	DDX_Check(pDX, IDC_CHECK_ASSISTANT1, m_bAssistant1);
	DDX_Check(pDX, IDC_CHECK_ASSISTANT2, m_bAssistant2);
	DDX_Check(pDX, IDC_CHECK_TEAM_ASSISTANT_DISTANCE, m_bTeamAssistantDistance);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SCAN_INTERVAL, m_sliderScanInterval);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_BALL, m_sliderSizeBall);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_OPPONENT, m_sliderSizeOpponent);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_TEAM_SEGMENT, m_sliderSizeTeamSegment);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_ASSISTANT, m_sliderSizeAssistant);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_TEAM_ASSISTANT_DISTANCE, m_sliderTeamAssistantDistance);
	DDX_Check(pDX, IDC_CHECK_DRAW_TEAM_WITHOUT_SEGMENT, m_bDrawTeamWithoutSegment);
	DDX_Check(pDX, IDC_CHECK_EDIT_SEGMENT_INFORMATION, m_bEditSegmentInformation);
	DDX_Check(pDX, IDC_CHECK_EDIT_SEGMENT_POSITION, m_bEditSegmentPosition);
	DDX_Control(pDX, IDC_COMBO_ROBOT_ID, m_comboRobotID);
	DDX_Control(pDX, IDC_COLOR_PICK_SEGMENT_MARKER, m_colorpickSegmentMarker);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SEGMENT_THRESHOLD, m_sliderSegmentThreshold);
}


BEGIN_MESSAGE_MAP(CPropertyPageVisionCoreSegmentPatch, CPropertyPageRobotSoccer)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_SCANNING_INTERVAL, &CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckScanningInterval)
	ON_BN_CLICKED(IDC_CHECK_BALL, &CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckBall)
	ON_BN_CLICKED(IDC_CHECK_OPPONENT, &CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckOpponent)
	ON_BN_CLICKED(IDC_CHECK_TEAM_SEGMENT, &CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckTeamSegment)
	ON_BN_CLICKED(IDC_CHECK_ASSISTANT1, &CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckAssistant1)
	ON_BN_CLICKED(IDC_CHECK_ASSISTANT2, &CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckAssistant2)
	ON_BN_CLICKED(IDC_CHECK_TEAM_ASSISTANT_DISTANCE, &CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckTeamAssistantDistance)
	ON_BN_CLICKED(IDC_CHECK_DRAW_TEAM_WITHOUT_SEGMENT, &CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckDrawTeamWithoutSegment)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECK_EDIT_SEGMENT_INFORMATION, &CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckEditSegmentInformation)
	ON_BN_CLICKED(IDC_CHECK_EDIT_SEGMENT_POSITION, &CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckEditSegmentPosition)
	ON_CBN_SELCHANGE(IDC_COMBO_ROBOT_ID, &CPropertyPageVisionCoreSegmentPatch::OnSelchangeComboRobotId)
END_MESSAGE_MAP()


// CPropertyPageVisionCoreSegmentPatch message handlers

BOOL CPropertyPageVisionCoreSegmentPatch::OnInitDialog()
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
	
	m_sliderSizeAssistant.SetOption( _T("Support Colour"), true, 1, 1000, 1, 0 );
	m_sliderSizeAssistant.SetValue( 5, 480 );
	
	m_sliderTeamAssistantDistance.SetOption( _T("Support Colour Distance(cm)"), false, 1, 10, 0.1, 1 );
	m_sliderTeamAssistantDistance.SetValue( 3.3 );
	
	m_colorpickTeamSegment.SetEditable( FALSE );
	m_colorpickAssistant1.SetEditable( FALSE );
	m_colorpickAssistant2.SetEditable( FALSE );
	
	m_colorpickTeamAssistantDistance.SetColor( RGB(0,255,0) );

	m_colorpickSegmentMarker.SetColor( RGB(255,255,255) );


	m_sliderSegmentThreshold.SetOption( _T("Minimum Confirmed Id"), false, 1, 5, 1, 0 );
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
		tmp.Format(_T("Robot%02d"), i+1 );
		m_comboRobotID.AddString( tmp );
	}

	m_comboRobotID.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPropertyPageVisionCoreSegmentPatch::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	m_colorpickBall.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_0 ) );
	m_colorpickOpponent.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_7 ) );
	m_colorpickTeamSegment.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_6 ) );
	m_colorpickAssistant1.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_1 ) );
	m_colorpickAssistant2.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_2 ) );
}

void CPropertyPageVisionCoreSegmentPatch::DrawDisplay( BOOL bMasking, COLORREF colorMask )
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

	if( m_bAssistant1 )
	{
		COLORREF color;

		if( bMasking )
			color = colorMask;
		else
			color =  m_colorpickAssistant1.GetColor();

		Display_AssistantPart( 0, m_pDC, color );
	}


	if( m_bAssistant2 )
	{
		COLORREF color;

		if( bMasking )
			color = colorMask;
		else
			color = m_colorpickAssistant2.GetColor();

		Display_AssistantPart( 1, m_pDC, color );
	}

	if( m_bTeamAssistantDistance )
	{
		SetTeamAssistantDistance( m_sliderTeamAssistantDistance.GetValueLeft()/100.0 );

		COLORREF color;

		if( bMasking )
			color = colorMask;
		else
			color = m_colorpickTeamAssistantDistance.GetColor();

	
		Display_TeamAssistantDistance( m_pDC, color );
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
}

void CPropertyPageVisionCoreSegmentPatch::Display_RobotSegment( BOOL bShowCameraImage, BOOL bMasking, COLORREF colorMask )
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

	if( m_bEditSegmentInformation )
	{
		int robot_id = m_comboRobotID.GetCurSel();

		for( int s=0 ; s<6 ; s++ )
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
			Display_RobotImage( &m_dcRobotSegment, m_dcRobotSegment.Width(), m_dcRobotSegment.Height(), -1 );
		}

		// Draw Segment
		{
			Display_SegmentImage( &m_dcRobotSegment, m_dcRobotSegment.Width(), m_dcRobotSegment.Height(),
				!m_bDrawTeamWithoutSegment, m_colorpickSegmentMarker.GetColor(), RGB(0,0,0),
				bMasking, colorMask,
				FALSE, RGB(0,0,0), -1 );
		}
	}

	if( m_bEditSegmentPosition )
	{
		for( int s=0 ; s<6 ; s++ )
		{
			int dc_x = (int)(m_SegmentPosition[s].x*10 + m_dcRobotSegment.Width()/2);
			int dc_y = (int)(-m_SegmentPosition[s].y*10 + m_dcRobotSegment.Height()/2);

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



void CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckDrawTeamWithoutSegment()
{
	UpdateData(TRUE);
}

void CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckScanningInterval()
{
	UpdateData(TRUE);
}
void CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckBall(){ UpdateData(TRUE); }
void CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckOpponent(){ UpdateData(TRUE); }
void CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckTeamSegment(){ UpdateData(TRUE); }
void CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckAssistant1(){ UpdateData(TRUE); }
void CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckAssistant2(){ UpdateData(TRUE); }
void CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckTeamAssistantDistance(){ UpdateData(TRUE); }



void CPropertyPageVisionCoreSegmentPatch::VisionRun()
{
	SetScanInterval( (int)m_sliderScanInterval.GetValue() );
	SetBallMinMax( (int)m_sliderSizeBall.GetValueLeft(), (int)m_sliderSizeBall.GetValueRight() );
	SetOppMinMax( (int)m_sliderSizeOpponent.GetValueLeft(), (int)m_sliderSizeOpponent.GetValueRight() );

	SetTeamMinMax( (int)m_sliderSizeTeamSegment.GetValueLeft(), (int)m_sliderSizeTeamSegment.GetValueRight() );
	SetAssistantMinMax( (int)m_sliderSizeAssistant.GetValueLeft(), (int)m_sliderSizeAssistant.GetValueRight() );


	SetSegmentThreshold( (int)m_sliderSegmentThreshold.GetValueLeft() );
	//SetSegmentCheckDistance( 1 );

	SetTeamAssistantDistance( m_sliderTeamAssistantDistance.GetValueLeft() / 100.0 );



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



void CPropertyPageVisionCoreSegmentPatch::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( m_dcRobotSegment.IsPointInRect( point ) )
	{
		if( m_bEditSegmentPosition )
		{
			CPointDouble posMouse = point - m_dcRobotSegment.TopLeft();

			m_selectSegmentID = -1;

			for( int s=0 ; s<6 ; s++ )
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

			for( int s=0 ; s<6 ; s++ )
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


BOOL CPropertyPageVisionCoreSegmentPatch::PreTranslateMessage(MSG* pMsg)
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



void CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckEditSegmentInformation()
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


void CPropertyPageVisionCoreSegmentPatch::OnBnClickedCheckEditSegmentPosition()
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


void CPropertyPageVisionCoreSegmentPatch::OnSelchangeComboRobotId()
{
	UpdateData(TRUE);
}

void CPropertyPageVisionCoreSegmentPatch::OpenFile(CArchive &ar)
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

		if( tmp == _T("Assistant") )
		{
			double value1,value2;
			ar >> value1;
			ar >> value2;
			m_sliderSizeAssistant.SetValue( value1, value2 );

			ar >> value1;
			m_sliderTeamAssistantDistance.SetValue( value1 );
		}

		if( tmp == _T("Segment Threshold") )
		{
			double value;
			ar >> value;
			m_sliderSegmentThreshold.SetValue( value );
		}

		if( tmp == _T("Segment Position") )
		{
			for( int j=0 ; j<6 ; j++ )
			{
				ar >> m_SegmentPosition[j].x;
				ar >> m_SegmentPosition[j].y;
			}
		}

		if( tmp == _T("Robot-Segment Information") )
		{
			int robot_i;
			ar >> robot_i;

			for( int j=0 ; j<6 ; j++ )
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

void CPropertyPageVisionCoreSegmentPatch::SaveFile(CArchive &ar)
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
	
	ar << CString("Assistant");
	ar << m_sliderSizeAssistant.GetValueLeft();
	ar << m_sliderSizeAssistant.GetValueRight();
	
	ar << m_sliderTeamAssistantDistance.GetValueLeft();

	ar << CString("Segment Threshold");
	ar << m_sliderSegmentThreshold.GetValue();


		ar << CString("Segment Position");
		for( int j=0 ; j<6 ; j++ )
		{
			ar << m_SegmentPosition[j].x;
			ar << m_SegmentPosition[j].y;
		}

	for( int i=0 ; i<MAX_OF_ROBOT_ID ; i++ )
	{
		ar << CString("Robot-Segment Information");
		ar << i;

		for( int j=0 ; j<6 ; j++ )
		{
			ar << m_SegCombination[i][j];
		}
	}

	ar << CString("ProcessingArea");
	for( int p=0 ; p<CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX ; p++ )
			ar << m_pProcessingArea[p];

	ar << CString("- END : VisionCoreSegmentPatch -");
}
