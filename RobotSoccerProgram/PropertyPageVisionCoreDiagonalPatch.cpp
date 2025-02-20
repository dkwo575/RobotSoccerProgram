// PropertyPageVisionCoreDiagonalPatch.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "PropertyPageVisionCoreDiagonalPatch.h"
#include "afxdialogex.h"


// CPropertyPageVisionCoreDiagonalPatch dialog

IMPLEMENT_DYNAMIC(CPropertyPageVisionCoreDiagonalPatch, CPropertyPageRobotSoccer)

CPropertyPageVisionCoreDiagonalPatch::CPropertyPageVisionCoreDiagonalPatch()
	: CPropertyPageRobotSoccer(CPropertyPageVisionCoreDiagonalPatch::IDD)
	, m_bScanningInterval(FALSE)
	, m_bBall(FALSE)
	, m_bOpponent(FALSE)
	, m_bTeam(FALSE)
	, m_bEditSegmentInformation(FALSE)
	, m_bEditSegmentPosition(FALSE)
	, m_bID1(FALSE)
	, m_bID2(FALSE)
	, m_bID3(FALSE)
	, m_bTeamIDDistance(FALSE)

{
	m_selectSegmentID = -1;
	if( ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_3 )
	{
		m_IDSelect[0][0] = 1;
		m_IDSelect[0][1] = 0;

		m_IDSelect[1][0] = 2;
		m_IDSelect[1][1] = 0;
	
		m_IDSelect[2][0] = 1;
		m_IDSelect[2][1] = 2;

		m_IDSelect[3][0] = -1;
		m_IDSelect[3][1] = -1;

		m_IDSelect[4][0] = -1;
		m_IDSelect[4][1] = -1;
	}

	if( ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_5 )
	{
		m_IDSelect[0][0] = 1;
		m_IDSelect[0][1] = 0;

		m_IDSelect[1][0] = 2;
		m_IDSelect[1][1] = 0;
	
		m_IDSelect[2][0] = 3;
		m_IDSelect[2][1] = 0;

		m_IDSelect[3][0] = 1;
		m_IDSelect[3][1] = 2;

		m_IDSelect[4][0] = 1;
		m_IDSelect[4][1] = 3;
	}

	m_sizePatchDC = 40;
}

CPropertyPageVisionCoreDiagonalPatch::~CPropertyPageVisionCoreDiagonalPatch()
{
}

void CPropertyPageVisionCoreDiagonalPatch::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageRobotSoccer::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR_PICK_SCAN_INTERVAL, m_colorpickScanInterval);
	DDX_Control(pDX, IDC_COLOR_PICK_BALL, m_colorpickBall);
	DDX_Control(pDX, IDC_COLOR_PICK_OPPONENT, m_colorpickOpponent);
	DDX_Control(pDX, IDC_COLOR_PICK_TEAM, m_colorpickTeam);
	DDX_Control(pDX, IDC_COLOR_PICK_ID1, m_colorpickID1);
	DDX_Control(pDX, IDC_COLOR_PICK_ID2, m_colorpickID2);
	DDX_Control(pDX, IDC_COLOR_PICK_ID3, m_colorpickID3);
	DDX_Control(pDX, IDC_COLOR_PICK_TEAM_ID_DISTANCE, m_colorpickTeamIDDistance);
	DDX_Check(pDX, IDC_CHECK_SCANNING_INTERVAL, m_bScanningInterval);
	DDX_Check(pDX, IDC_CHECK_BALL, m_bBall);
	DDX_Check(pDX, IDC_CHECK_OPPONENTS, m_bOpponent);
	DDX_Check(pDX, IDC_CHECK_TEAM, m_bTeam);
	DDX_Check(pDX, IDC_CHECK_ID1, m_bID1);
	DDX_Check(pDX, IDC_CHECK_ID2, m_bID2);
	DDX_Check(pDX, IDC_CHECK_ID3, m_bID3);
	DDX_Check(pDX, IDC_CHECK_TEAM_ID_DISTANCE, m_bTeamIDDistance);
	DDX_Check(pDX, IDC_CHECK_EDIT_SEGMENT_INFORMATION, m_bEditSegmentInformation);
	DDX_Check(pDX, IDC_CHECK_EDIT_SEGMENT_POSITION, m_bEditSegmentPosition);
	DDX_Control(pDX, IDC_COMBO_ROBOT_ID, m_comboRobotID);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SCAN_INTERVAL, m_sliderScanInterval);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_BALL, m_sliderSizeBall);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_OPPONENT, m_sliderSizeOpponent);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_TEAM, m_sliderSizeTeam);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_TEAM_ID_DISTANCE, m_sliderSizeTeamIDDistance);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SIZE_THRESHOLD_ID, m_sliderSizeID);
}


BEGIN_MESSAGE_MAP(CPropertyPageVisionCoreDiagonalPatch, CPropertyPageRobotSoccer)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECK_SCANNING_INTERVAL, &CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckScanningInterval)
	ON_BN_CLICKED(IDC_CHECK_BALL, &CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckBall)
	ON_BN_CLICKED(IDC_CHECK_OPPONENTS, &CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckOpponents)
	ON_BN_CLICKED(IDC_CHECK_TEAM, &CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckTeam)
	ON_BN_CLICKED(IDC_CHECK_ID1, &CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckId1)
	ON_BN_CLICKED(IDC_CHECK_ID2, &CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckId2)
	ON_BN_CLICKED(IDC_CHECK_ID3, &CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckId3)
	ON_BN_CLICKED(IDC_CHECK_TEAM_ID_DISTANCE, &CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckTeamIdDistance)
	ON_BN_CLICKED(IDC_CHECK_EDIT_SEGMENT_INFORMATION, &CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckEditSegmentInformation)
	ON_BN_CLICKED(IDC_CHECK_EDIT_SEGMENT_POSITION, &CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckEditSegmentPosition)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CPropertyPageVisionCoreDiagonalPatch message handlers

BOOL CPropertyPageVisionCoreDiagonalPatch::OnInitDialog()
{
	CPropertyPageRobotSoccer::OnInitDialog();

	//if( ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_5 )
	//{
	//	MoveDlgItem( IDC_FRAME_ID_SELECT1, CPoint(-21,0) );
	//	MoveDlgItem( IDC_FRAME_ID_SELECT2, CPoint(-53,0) );
	//	MoveDlgItem( IDC_FRAME_ID_SELECT3, CPoint(-85,0) );
	//	MoveDlgItem( IDC_FRAME_ID_SELECT4, CPoint(-125,0) );
	//	MoveDlgItem( IDC_FRAME_ID_SELECT5, CPoint(-127,0) );
	//}
	

	m_colorpickScanInterval.SetColor( RGB(0,255,0) );

	m_colorpickScanInterval.SetEditable(TRUE);
	m_colorpickBall.SetEditable(FALSE);
	m_colorpickOpponent.SetEditable(FALSE);


	m_sliderScanInterval.SetOption( _T("Dist for Colour Detection"), false, 1, 100, 1, 0 );
	m_sliderScanInterval.SetValue( 7 );

	m_sliderSizeBall.SetOption( _T("Ball Colour"), true, 1, 2000, 1, 0 );
	m_sliderSizeBall.SetValue( 50, 300 );

	m_sliderSizeOpponent.SetOption( _T("Opponent Colour"), true, 1, 2000, 1, 0 );
	m_sliderSizeOpponent.SetValue( 50, 500 );


	m_sliderSizeTeam.SetOption( _T("Team Colour"), true, 1, 2000, 1, 0 );
	m_sliderSizeTeam.SetValue( 50, 500 );
	
	m_sliderSizeID.SetOption( _T("ID Colour"), true, 1, 1000, 1, 0 );
	m_sliderSizeID.SetValue( 15, 100 );
	
	m_sliderSizeTeamIDDistance.SetOption( _T("Team-ID Distance(cm)"), false, 1, 10, 0.1, 1 );
	m_sliderSizeTeamIDDistance.SetValue( 3.3 );

	m_colorpickTeam.SetEditable( FALSE );
	m_colorpickID1.SetEditable( FALSE );
	m_colorpickID2.SetEditable( FALSE );
	m_colorpickID3.SetEditable( FALSE );
	
	m_colorpickTeamIDDistance.SetColor( RGB(0,255,0) );

/*
	CClientDC dc(this);
	CRect rect;
	
	GetDlgItem(IDC_FRAME_ID_SELECT1)->GetWindowRect(rect);
	ScreenToClient(rect);
	GetDlgItem(IDC_FRAME_ID_SELECT1)->SetWindowPos( NULL, rect.left, rect.top, m_sizePatchDC+2, m_sizePatchDC+2, SWP_NOZORDER | SWP_NOACTIVATE);
	GetDlgItem(IDC_FRAME_ID_SELECT1)->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1,1,1,1);
	m_dcIDSelect[0].UpdateRect( rect );
	m_dcIDSelect[0].Init( &dc );

	GetDlgItem(IDC_FRAME_ID_SELECT2)->GetWindowRect(rect);
	ScreenToClient(rect);
	GetDlgItem(IDC_FRAME_ID_SELECT2)->SetWindowPos( NULL, rect.left, rect.top, m_sizePatchDC+2, m_sizePatchDC+2, SWP_NOZORDER | SWP_NOACTIVATE);
	GetDlgItem(IDC_FRAME_ID_SELECT2)->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1,1,1,1);
	m_dcIDSelect[1].UpdateRect( rect );
	m_dcIDSelect[1].Init( &dc );

	GetDlgItem(IDC_FRAME_ID_SELECT3)->GetWindowRect(rect);
	ScreenToClient(rect);
	GetDlgItem(IDC_FRAME_ID_SELECT3)->SetWindowPos( NULL, rect.left, rect.top, m_sizePatchDC+2, m_sizePatchDC+2, SWP_NOZORDER | SWP_NOACTIVATE);
	GetDlgItem(IDC_FRAME_ID_SELECT3)->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1,1,1,1);
	m_dcIDSelect[2].UpdateRect( rect );
	m_dcIDSelect[2].Init( &dc );

	GetDlgItem(IDC_FRAME_ID_SELECT4)->GetWindowRect(rect);
	ScreenToClient(rect);
	GetDlgItem(IDC_FRAME_ID_SELECT4)->SetWindowPos( NULL, rect.left, rect.top, m_sizePatchDC+2, m_sizePatchDC+2, SWP_NOZORDER | SWP_NOACTIVATE);
	GetDlgItem(IDC_FRAME_ID_SELECT4)->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1,1,1,1);
	m_dcIDSelect[3].UpdateRect( rect );
	m_dcIDSelect[3].Init( &dc );


	GetDlgItem(IDC_FRAME_ID_SELECT5)->GetWindowRect(rect);
	ScreenToClient(rect);
	GetDlgItem(IDC_FRAME_ID_SELECT5)->SetWindowPos( NULL, rect.left, rect.top, m_sizePatchDC+2, m_sizePatchDC+2, SWP_NOZORDER | SWP_NOACTIVATE);
	GetDlgItem(IDC_FRAME_ID_SELECT5)->GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1,1,1,1);
	m_dcIDSelect[4].UpdateRect( rect );
	m_dcIDSelect[4].Init( &dc );
	*/

	{
		CClientDC dc(this);
		CRect rect;
		GetDlgItem(IDC_FRAME_ROBOT_SEGMENT)->GetWindowRect(rect);
		ScreenToClient(rect);
		m_dcRobotSegment.Init(&dc, rect);
	}

	for (int i = 0; i < MAX_OF_ROBOT_ID; i++)
	{
		CString tmp;
		tmp.Format(_T("Robot-%02d"), i + 1);
		m_comboRobotID.AddString(tmp);
	}

	m_comboRobotID.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPropertyPageVisionCoreDiagonalPatch::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	m_colorpickBall.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_0 ) );
	m_colorpickOpponent.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_7 ) );
	m_colorpickTeam.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_4 ) );
	m_colorpickID1.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_1 ) );
	m_colorpickID2.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_2 ) );
	m_colorpickID3.SetColor( m_pLookUpTable->GetColor( VISION_ARRAY_ID_3 ) );

	DrawIDSelect();
}

void CPropertyPageVisionCoreDiagonalPatch::DrawDisplay(BOOL bMasking, COLORREF colorMask)
{
	if (m_bScanningInterval)
	{
		for (int p = 0; p < m_pDC->Width() * m_pDC->Height(); p += (int)m_sliderScanInterval.GetValue())
		{
			int i = p % m_pDC->Width();
			int j = p / m_pDC->Width();

			m_pDC->SetPixel(i, j, m_colorpickScanInterval.GetColor());
		}
	}

	// Drawing the selected colour onto the camera

	if (m_bBall)
	{
		COLORREF color = m_colorpickBall.GetColor();
		if (bMasking)
			color = colorMask;
		Draw_BallPatch(m_pDC, color);
	}


	if (m_bOpponent)
	{
		COLORREF color = m_colorpickOpponent.GetColor();
		if (bMasking)
			color = colorMask;
		Draw_OpponentsPatch(m_pDC, color);
	}

	if (m_bTeamSegment)
	{
		COLORREF color = m_colorpickTeamSegment.GetColor();
		if (bMasking)
			color = colorMask;
		Draw_TeamPatch(m_pDC, color);
	}

	if (m_bID1)
	{
		COLORREF color = m_colorpickID1.GetColor();
		if (bMasking)
			color = colorMask;
		Draw_IDPatch(m_pDC, 0, color);
	}

	if (m_bID2)
	{
		COLORREF color = m_colorpickID2.GetColor();
		if (bMasking)
			color = colorMask;
		Draw_IDPatch(m_pDC, 1, color);
	}

	if (m_bID3)
	{
		COLORREF color = m_colorpickID3.GetColor();
		if (bMasking)
			color = colorMask;
		Draw_IDPatch(m_pDC, 2, color);
	}

	CString tmp;
	//tmp.Format(_T("%d"), m_countTest );
	m_pDC->TextOut(10, 10, tmp);

	//if( m_bSelectRobotPosition )
	{
		CPen pen, * pOldPen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		pOldPen = (CPen*)m_pDC->SelectObject(&pen);

		m_pDC->SelectStockObject(NULL_BRUSH);

		m_pDC->Circle((int)m_SelectRobotPosition.x, (int)m_SelectRobotPosition.y, 20);

		m_pDC->SelectObject(pOldPen);
	}

	// Drawing of the segment info
	if (m_bEditSegmentInformation)
	{
		CRect rectRobot(-40, -40, 40, 40);
		CRect rectTeam(-14, -35, 14, 35);
		CRect rectSeg[4];
		// screen y = -y

		for (int i = 0; i < ROBOT_SOCCER_RROGRAM_ROBOT_N; i++)
		{
			CPoint posRobot(0, 0);
			if (ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_3)
				posRobot = CPoint(580, i * 90 + 60 + 90 * 2);
			if (ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_5)
				posRobot = CPoint(580, i * 90 + 60);
			//posRobot = CPoint( i*100 + 120, 430 );

			// Segment Info Box
			m_pDC->SelectPen(RGB(255, 255, 255)); // Outline
			m_pDC->SelectBrush(RGB(0, 0, 0)); // Inside
			m_pDC->Rectangle(rectRobot + posRobot);

			// Team Patch
			m_pDC->SelectPen(RGB(255, 255, 255));
			m_pDC->SelectBrush(m_colorpickTeam.GetColor());
			CPoint T_Pt[7];
			T_Pt[0] = CPoint(14, 35) + posRobot;
			T_Pt[1] = CPoint(-35, -14) + posRobot;
			T_Pt[2] = CPoint(-35, -35) + posRobot;
			T_Pt[3] = CPoint(-14, -35) + posRobot;
			T_Pt[4] = CPoint(35, 14) + posRobot;
			T_Pt[5] = CPoint(35, 35) + posRobot;
			T_Pt[6] = CPoint(14, 35) + posRobot;
			m_pDC->Polygon(T_Pt , 7);


			m_pDC->SetBkMode(OPAQUE);
			m_pDC->SetBkColor(RGB(0, 0, 0));
			m_pDC->SetTextColor(RGB(255, 255, 255));

			CString tmp;
			tmp.Format(_T("[%d]"), i + 1); // Printing the ID number
			m_pDC->DrawText(tmp, rectTeam + posRobot, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			// Setting the colour of the pen and brush dependong on the Segment value
			for (int s = 0; s < 2; s++)
			{
				if (m_SegCombination[i][s] == 0)
				{
					m_pDC->SelectPen(RGB(0, 0, 0));
					m_pDC->SelectBrush(RGB(0, 0, 0));
				}
				if (m_SegCombination[i][s] == 1 || m_SegCombination[i][s] == 2 || m_SegCombination[i][s] == 3)
				{
					// Getting the colour of the IDs to display as the segment patch
					m_pDC->SelectPen(RGB(255, 255, 255));
					if (m_SegCombination[i][s] == 1) {
						m_pDC->SelectBrush(m_colorpickID1.GetColor());
					}
					else if (m_SegCombination[i][s] == 2) {
						m_pDC->SelectBrush(m_colorpickID2.GetColor());
					}
					else {
						m_pDC->SelectBrush(m_colorpickID3.GetColor());
					}
				}
				if (m_SegCombination[i][s] == -1)
				{
					m_pDC->SelectPen(RGB(255, 255, 255));
					m_pDC->SelectBrush(false);
				}

				CPoint S_Pt[4];
				if (s == 0) {
					// Top Right Segment Patch
					S_Pt[0] = CPoint(35, 0) + posRobot;
					S_Pt[1] = CPoint(0, -35) + posRobot;
					S_Pt[2] = CPoint(35, -35) + posRobot;
					S_Pt[3] = CPoint(35, 0) + posRobot;
				}
				else {
					// Bottom Left Segment Patch
					S_Pt[0] = CPoint(0, 35) + posRobot;
					S_Pt[1] = CPoint(-35, 35) + posRobot;
					S_Pt[2] = CPoint(-35, 0) + posRobot;
					S_Pt[3] = CPoint(0, 35) + posRobot;
				}
				//m_pDC->Rectangle(rectSeg[s] + posRobot);
				m_pDC->Polygon(S_Pt, 4);
			}
		}
	}
}
void CPropertyPageVisionCoreDiagonalPatch::Display_RobotSegment(BOOL bShowCameraImage, BOOL bMasking, COLORREF colorMask)
{
	CClientDC dc(this);

	{
		CBrush brush, * pOldBrush;
		brush.CreateSolidBrush(RGB(0, 0, 0));

		pOldBrush = (CBrush*)m_dcRobotSegment.SelectObject(&brush);

		CRect rect = m_dcRobotSegment.GetRect();
		m_dcRobotSegment.Rectangle(rect - rect.TopLeft());

		m_dcRobotSegment.SelectObject(pOldBrush);
	}

	// Selecting the colour of the segement depending on the combination value 
	if (m_bEditSegmentInformation)
	{
		int robot_id = m_comboRobotID.GetCurSel();

		for (int s = 0; s < 2; s++)
		{
			int dc_x = (int)(m_SegmentPosition[s].x * 10 + m_dcRobotSegment.Width() / 2);
			int dc_y = (int)(-m_SegmentPosition[s].y * 10 + m_dcRobotSegment.Height() / 2);

			COLORREF colorPen = RGB(255, 0, 0);
			COLORREF colorBrush = RGB(0, 0, 0);

			if (m_SegCombination[robot_id][s] == 1)
			{
				colorBrush = m_colorpickID1.GetColor();
			}
			if (m_SegCombination[robot_id][s] == 2)
			{
				colorBrush = m_colorpickID2.GetColor();
			}
			if (m_SegCombination[robot_id][s] == 3)
			{
				colorBrush = m_colorpickID3.GetColor();
			}
			if (m_SegCombination[robot_id][s] == -1)
			{
				colorBrush = RGB(192, 192, 192);
			}

			CPen pen, * pOldPen;
			pen.CreatePen(PS_SOLID, 1, colorPen);
			pOldPen = (CPen*)m_dcRobotSegment.SelectObject(&pen);

			CBrush brush, * pOldBrush;
			brush.CreateSolidBrush(colorBrush);
			pOldBrush = (CBrush*)m_dcRobotSegment.SelectObject(&brush);

			m_dcRobotSegment.Circle(dc_x, dc_y, 5);

			m_dcRobotSegment.SelectObject(pOldBrush);
			m_dcRobotSegment.SelectObject(pOldPen);
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
			m_dcRobotSegment.SelectBrush(false);
			m_dcRobotSegment.SelectPen(RGB(255, 255, 255));

			Display_SegmentImage(&m_dcRobotSegment, m_dcRobotSegment.Width(), m_dcRobotSegment.Height(),
				FALSE, FALSE, FALSE, RGB(255,255,255), RGB(128, 128, 128),
				bMasking, colorMask,
				FALSE, RGB(0,0,0), -1);
		}
	}

	if (m_bEditSegmentPosition)
	{
		for (int s = 0; s < 2; s++)
		{
			int dc_x = (int)(m_SegmentPosition[s].x * 10 + m_dcRobotSegment.Width() / 2);
			int dc_y = (int)(-m_SegmentPosition[s].y * 10 + m_dcRobotSegment.Height() / 2);

			// This is the edit segment position
			COLORREF color = RGB(255, 0, 0);

			if (s == m_selectSegmentID)
			{
				color = RGB(0, 255, 0);
			}

			CPen pen, * pOldPen;
			pen.CreatePen(PS_SOLID, 1, color);
			pOldPen = (CPen*)m_dcRobotSegment.SelectObject(&pen);
			m_dcRobotSegment.SelectStockObject(NULL_BRUSH);

			int size = m_valueSegmentCheckDistance;
			m_dcRobotSegment.Square(dc_x, dc_y, size);
			//m_dcRobotSegment.Polygon();

			if (s == m_selectSegmentID)
			{
				//size += 5;
				m_dcRobotSegment.Square(dc_x, dc_y, size);

				int k = 10;
				m_dcRobotSegment.MoveTo(dc_x - m_valueSegmentCheckDistance * k, dc_y);
				m_dcRobotSegment.LineTo(dc_x + m_valueSegmentCheckDistance * k + 1, dc_y);

				m_dcRobotSegment.MoveTo(dc_x, dc_y - m_valueSegmentCheckDistance * k);
				m_dcRobotSegment.LineTo(dc_x, dc_y + m_valueSegmentCheckDistance * k + 1);
			}

			m_dcRobotSegment.SelectObject(pOldPen);
		}

		//CString tmp;
		//tmp.Format(_T("%d"), m_valueSegmentCheckDistance );
		//m_dcRobotSegment.TextOut( 5, 5, tmp );
	}


	m_dcRobotSegment.BitBlt(&dc);
}

void CPropertyPageVisionCoreDiagonalPatch::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_dcRobotSegment.IsPointInRect(point))
	{
		if (m_bEditSegmentPosition)
		{
			CPointDouble posMouse = point - m_dcRobotSegment.TopLeft();

			m_selectSegmentID = -1;

			for (int s = 0; s < 2; s++)
			{
				CPointDouble posSeg;
				posSeg.x = (int)(m_SegmentPosition[s].x * 10 + m_dcRobotSegment.Width() / 2);
				posSeg.y = (int)(-m_SegmentPosition[s].y * 10 + m_dcRobotSegment.Height() / 2);

				if ((posSeg - posMouse).Distance() < 5)
				{
					m_selectSegmentID = s;
				}
			}
		}

		if (m_bEditSegmentInformation)
		{
			CPointDouble posMouse = point - m_dcRobotSegment.TopLeft();

			m_selectSegmentID = -1;

			for (int s = 0; s < 2; s++)
			{
				CPointDouble posSeg;
				posSeg.x = (int)(m_SegmentPosition[s].x * 10 + m_dcRobotSegment.Width() / 2);
				posSeg.y = (int)(-m_SegmentPosition[s].y * 10 + m_dcRobotSegment.Height() / 2);

				if ((posSeg - posMouse).Distance() < 5)
				{
					m_selectSegmentID = s;
				}
			}

			int robot_id = m_comboRobotID.GetCurSel();

			// Updating the segment combination upon each click
			if (m_selectSegmentID >= 0)
			{
				if (m_SegCombination[robot_id][m_selectSegmentID] == 1)
					m_SegCombination[robot_id][m_selectSegmentID] = 2;
				else if (m_SegCombination[robot_id][m_selectSegmentID] == 2)
					m_SegCombination[robot_id][m_selectSegmentID] = 3;
				else if (m_SegCombination[robot_id][m_selectSegmentID] == 3)
					m_SegCombination[robot_id][m_selectSegmentID] = 0;
				else if (m_SegCombination[robot_id][m_selectSegmentID] == 0)
					m_SegCombination[robot_id][m_selectSegmentID] = -1;
				else if (m_SegCombination[robot_id][m_selectSegmentID] == -1)
					m_SegCombination[robot_id][m_selectSegmentID] = 1;
			}
		}
	}
	__super::OnLButtonDown(nFlags, point);
}


void CPropertyPageVisionCoreDiagonalPatch::OnLButtonUp(UINT nFlags, CPoint point)
{
	for( int i=0 ; i<5 ; i++ )
	{
		if( m_dcIDSelect[i].IsPointInRect( point ) )
		{
			CPoint p = point - m_dcIDSelect[i].TopLeft();

			if( p.x > p.y + m_dcIDSelect[i].Width()*0.4 )
				m_IDSelect[i][0] = (m_IDSelect[i][0]+1)%4;
			else
			if( p.x < p.y - m_dcIDSelect[i].Width()*0.4 )
				m_IDSelect[i][1] = (m_IDSelect[i][1]+1)%4;
		}
	}

	DrawIDSelect();

	__super::OnLButtonUp(nFlags, point);
}
BOOL CPropertyPageVisionCoreDiagonalPatch::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && m_bEditSegmentPosition && m_selectSegmentID >= 0)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
		case VK_NUMPAD8:
		{
			m_SegmentPosition[m_selectSegmentID].y += 0.1;
			return TRUE;
		}
		break;
		case VK_DOWN:
		case VK_NUMPAD2:
		{
			m_SegmentPosition[m_selectSegmentID].y -= 0.1;
			return TRUE;
		}
		break;
		case VK_LEFT:
		case VK_NUMPAD4:
		{
			m_SegmentPosition[m_selectSegmentID].x -= 0.1;
			return TRUE;
		}
		break;
		case VK_RIGHT:
		case VK_NUMPAD6:
		{
			m_SegmentPosition[m_selectSegmentID].x += 0.1;
			return TRUE;
		}
		break;
		case VK_PRIOR:
		{
			m_valueSegmentCheckDistance++;
			return TRUE;
		}
		break;
		case VK_NEXT:
		{
			m_valueSegmentCheckDistance--;

			if (m_valueSegmentCheckDistance < 1)
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


void CPropertyPageVisionCoreDiagonalPatch::DrawIDSelect()
{
	CClientDC dc(this);

	COLORREF m_colorDrawID[4];
	COLORREF m_colorDrawTeam;

	m_colorDrawID[1] = m_colorpickID1.GetColor();
	m_colorDrawID[2] = m_colorpickID2.GetColor();
	m_colorDrawID[3] = m_colorpickID3.GetColor();
	m_colorDrawID[0] = RGB(0,0,0);
	m_colorDrawTeam = m_colorpickTeam.GetColor();


	int margin_size = 1;

	for( int i=0 ; i<5 ; i++ )
	{
		m_dcIDSelect[i].SetBkMode( TRANSPARENT );
		m_dcIDSelect[i].SetTextColor( RGB( 255,255,255 ) );
		
		for( int x=0 ; x<m_dcIDSelect[i].Width() ; x++ )
		{
			for( int y=0 ; y<m_dcIDSelect[i].Height() ; y++ )
			{
				if( x < margin_size || y < margin_size || x >= m_dcIDSelect[i].Width()-margin_size || y >= m_dcIDSelect[i].Height()-margin_size )
					m_dcIDSelect[i].SetPixel( x, y, RGB(0,0,0) );
				else
				if( x > y + m_dcIDSelect[i].Width()*0.4 )
					m_dcIDSelect[i].SetPixel( x, y, m_colorDrawID[ m_IDSelect[i][0] ] );
				else
				if( x > y + m_dcIDSelect[i].Width()*0.4 - 3 )
					m_dcIDSelect[i].SetPixel( x, y, RGB(0,0,0) );
				else
				if( x < y - m_dcIDSelect[i].Width()*0.4 )
					m_dcIDSelect[i].SetPixel( x, y, m_colorDrawID[ m_IDSelect[i][1] ] );
				else
				if( x < y - m_dcIDSelect[i].Width()*0.4 + 3 )
					m_dcIDSelect[i].SetPixel( x, y, RGB(0,0,0) );
				else
					m_dcIDSelect[i].SetPixel( x, y, m_colorDrawTeam );
			}
		}
		
		if( m_IDSelect[i][0] == 0 )
		{
			m_dcIDSelect[i].SetTextColor( RGB(255,255,255) );
			m_dcIDSelect[i].TextOut( (int)(m_dcIDSelect[i].Width()*0.7), 0, _T("¡¿"));
		}

		if( m_IDSelect[i][1] == 0 )
		{
			m_dcIDSelect[i].SetTextColor( RGB(255,255,255) );
			m_dcIDSelect[i].TextOut( 3, (int)(m_dcIDSelect[i].Height()*0.6), _T("¡¿"));
		}

		m_dcIDSelect[i].BitBlt(&dc);
	}
}
void CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckEditSegmentInformation()
{
	UpdateData(TRUE);

	if (m_bEditSegmentInformation)
	{
		if (m_bEditSegmentPosition)
		{
			m_bEditSegmentPosition = FALSE;
			UpdateData(FALSE);
		}
	}
}


void CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckEditSegmentPosition()
{
	UpdateData(TRUE);

	if (m_bEditSegmentPosition)
	{
		if (m_bEditSegmentInformation)
		{
			m_bEditSegmentInformation = FALSE;
			UpdateData(FALSE);
		}
	}
}


void CPropertyPageVisionCoreDiagonalPatch::OnSelchangeComboRobotId()
{
	UpdateData(TRUE);
}

void CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckScanningInterval()
{
	UpdateData(TRUE);
}


void CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckBall()
{
	UpdateData(TRUE);
}


void CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckOpponents()
{
	UpdateData(TRUE);
}


void CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckTeam()
{
	UpdateData(TRUE);
}


void CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckId1()
{
	UpdateData(TRUE);
}


void CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckId2()
{
	UpdateData(TRUE);
}


void CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckId3()
{
	UpdateData(TRUE);
}


void CPropertyPageVisionCoreDiagonalPatch::OnBnClickedCheckTeamIdDistance()
{
	UpdateData(TRUE);
}

void CPropertyPageVisionCoreDiagonalPatch::OpenFile(CArchive &ar)
{
	CString tmp;

	while(1)
	{
		ar >> tmp;

		if( tmp == _T("- END : VisionCoreDiagonalPatch -") )
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

		if( tmp == _T("Team") )
		{
			double value1,value2;
			ar >> value1;
			ar >> value2;
			m_sliderSizeTeam.SetValue( value1, value2 );
		}

		if( tmp == _T("ID") )
		{
			double value1,value2;
			ar >> value1;
			ar >> value2;
			m_sliderSizeID.SetValue( value1, value2 );

			ar >> value1;
			m_sliderSizeTeamIDDistance.SetValue( value1 );

			for( int i=0 ; i<5 ; i++ )
				for( int j=0 ; j<2 ; j++ )
				{
					ar >> m_IDSelect[i][j];
				}
		}

		if( tmp == _T("ProcessingArea") )
		{
			for( int p=0 ; p<CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX ; p++ )
				ar >> m_pProcessingArea[p];
		}
	}

	DrawIDSelect();

	Invalidate(TRUE);
}

void CPropertyPageVisionCoreDiagonalPatch::SaveFile(CArchive &ar)
{
	ar << CString("Scan Interval");
	ar << m_sliderScanInterval.GetValue();

	ar << CString("Ball");
	ar << m_sliderSizeBall.GetValueLeft();
	ar << m_sliderSizeBall.GetValueRight();

	ar << CString("Opponent");
	ar << m_sliderSizeOpponent.GetValueLeft();
	ar << m_sliderSizeOpponent.GetValueRight();

	ar << CString("Team");
	ar << m_sliderSizeTeam.GetValueLeft();
	ar << m_sliderSizeTeam.GetValueRight();
	
	ar << CString("ID");
	ar << m_sliderSizeID.GetValueLeft();
	ar << m_sliderSizeID.GetValueRight();
	
	ar << m_sliderSizeTeamIDDistance.GetValueLeft();

	for( int i=0 ; i<5 ; i++ )
		for( int j=0 ; j<2 ; j++ )
		{
			ar << m_IDSelect[i][j];
		}

	ar << CString("ProcessingArea");
	for( int p=0 ; p<CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX ; p++ )
			ar << m_pProcessingArea[p];

	ar << CString("- END : VisionCoreDiagonalPatch -");
}
