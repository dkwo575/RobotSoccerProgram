// VelocityParameterDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "VelocityParameterDlg2.h"
#include "afxdialogex.h"

#define _USE_MATH_DEFINES
#include <math.h>


// CVelocityParameterDlg2 dialog

IMPLEMENT_DYNAMIC(CVelocityParameterDlg2, CDialog)

CVelocityParameterDlg2::CVelocityParameterDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CVelocityParameterDlg2::IDD, pParent)
	, m_radioParam(FALSE)
{
	m_bActive = false;

	m_bDialogShow = false;

	OnBnClickedOpenV2File();

	/*
2.0
0.10
0.00
0.50
35.0
0
300
50
0.60
3.00
900
2.00
0.25
0.00
1.50
35.0
0
300
50
3.00
3.00
900
2.00
0.25
0.00
1.00
50.0
0
300
50
0.50
1.00
900
1.50
0.05
0.00
0.80
35.0
0
300
50
2.0
4.0
900
1.50
0.05
0.00
1.10
35.0
0
300
50
5.0
5.0
900
	*/

	InitializeCriticalSection(&m_critVisionPrarameter2);
}

CVelocityParameterDlg2::~CVelocityParameterDlg2()
{
	DeleteCriticalSection(&m_critVisionPrarameter2);
}

void CVelocityParameterDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_1, m_sliderParam1);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_2, m_sliderParam2);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_3, m_sliderParam3);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_4, m_sliderParam4);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_5, m_sliderParam5);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_6, m_sliderParam6);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_7, m_sliderParam7);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_8, m_sliderParam8);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_9, m_sliderParam9);
	DDX_Radio(pDX, IDC_RADIO_PARAMETER1, m_radioParam);
}


BEGIN_MESSAGE_MAP(CVelocityParameterDlg2, CDialog)
	ON_BN_CLICKED(IDC_RADIO_PARAMETER1, &CVelocityParameterDlg2::OnBnClickedRadioParameter1)
	ON_BN_CLICKED(IDC_RADIO_PARAMETER2, &CVelocityParameterDlg2::OnBnClickedRadioParameter2)
	ON_BN_CLICKED(IDC_RADIO_PARAMETER3, &CVelocityParameterDlg2::OnBnClickedRadioParameter3)
	ON_BN_CLICKED(IDC_RADIO_PARAMETER4, &CVelocityParameterDlg2::OnBnClickedRadioParameter4)
	ON_BN_CLICKED(IDC_RADIO_PARAMETER5, &CVelocityParameterDlg2::OnBnClickedRadioParameter5)
	ON_BN_CLICKED(IDOK, &CVelocityParameterDlg2::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CVelocityParameterDlg2::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SAVE_V2_FILE, &CVelocityParameterDlg2::OnBnClickedSaveV2File)
	ON_BN_CLICKED(IDC_OPEN_V2_FILE, &CVelocityParameterDlg2::OnBnClickedOpenV2File)
END_MESSAGE_MAP()


// CVelocityParameterDlg2 message handlers


BOOL CVelocityParameterDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_sliderParam1.SetOption( _T("linear velocity (m/s)"), false, 0, 5, 0.01, 2 );
	m_sliderParam2.SetOption( _T("generate cont. velocity-1"), false, 0, 1, 0.01, 2 );

	m_sliderParam3.SetOption( _T("min/max linear v (m/s)"), true, 0, 5, 0.01, 2 );
	m_sliderParam4.SetOption( _T("generate cont. velocity-2"), false, 0, 100, 0.01, 2 );


	m_sliderParam5.SetOption( _T("min/max angular v (°/s)"), true, 0, 720, 10.0, 0 );
	m_sliderParam6.SetOption( _T("generate cont. angular v"), false, 0, 100, 0.01, 2 );

	m_sliderParam7.SetOption( _T("max linear acceleration (m/s^2)"), false, 0, 50, 0.01, 2 );
	m_sliderParam8.SetOption( _T("max linear acceleration (m/s^2)"), false, 0, 50, 0.01, 2 );
	m_sliderParam9.SetOption( _T("Maximum Angular (decrease) acce. (°/s^2)"), false, 0, 3600, 10.0, 0 );
	

	for( int i=0 ; i<5 ; i++ )
		m_VelocityParameter2_backup[i] = m_VelocityParameter2[i];

	UpdateSlider( FALSE );


	CClientDC dc(this);

	{
		CRect rect;
		GetDlgItem(IDC_FRAME0)->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.DeflateRect(1,1,1,1);
		m_displayVc.Init( &dc, rect );
	}
	{
		CRect rect;
		GetDlgItem(IDC_FRAME1)->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.DeflateRect(1,1,1,1);
		m_displayVmax.Init( &dc, rect );
	}
	{
		CRect rect;
		GetDlgItem(IDC_FRAME2)->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.DeflateRect(1,1,1,1);
		m_displaydV.Init( &dc, rect );
	}

	m_bActive = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVelocityParameterDlg2::SetParameters( int p, CVelocityParameter2 param )
{
	EnterCriticalSection(&m_critVisionPrarameter2);

	m_VelocityParameter2[p] = param;

	m_VelocityParameter2_backup[p] = m_VelocityParameter2[p];

	if( p == m_radioParam )
		UpdateSlider( FALSE );

	LeaveCriticalSection(&m_critVisionPrarameter2);
}

CVelocityParameter2 CVelocityParameterDlg2::GetParameters( int p )
{
	CVelocityParameter2 result;

	EnterCriticalSection(&m_critVisionPrarameter2);

	if( m_bDialogShow == false )
	{
		result = m_VelocityParameter2[p];
	}
	else
	{
		UpdateSlider( TRUE );
		//DisplayVelocityK();

		result = m_VelocityParameter2[p];
	}

	LeaveCriticalSection(&m_critVisionPrarameter2);

	return result;
}


void CVelocityParameterDlg2::OnBnClickedRadioParameter1()
{
	UpdateSlider(TRUE);
	UpdateData(TRUE);
	UpdateSlider(FALSE);
	DisplayVelocityK();
}


void CVelocityParameterDlg2::OnBnClickedRadioParameter2()
{
	UpdateSlider(TRUE);
	UpdateData(TRUE);
	UpdateSlider(FALSE);
	DisplayVelocityK();
}


void CVelocityParameterDlg2::OnBnClickedRadioParameter3()
{
	UpdateSlider(TRUE);
	UpdateData(TRUE);
	UpdateSlider(FALSE);
	DisplayVelocityK();
}


void CVelocityParameterDlg2::OnBnClickedRadioParameter4()
{
	UpdateSlider(TRUE);
	UpdateData(TRUE);
	UpdateSlider(FALSE);
	DisplayVelocityK();
}


void CVelocityParameterDlg2::OnBnClickedRadioParameter5()
{
	UpdateSlider(TRUE);
	UpdateData(TRUE);
	UpdateSlider(FALSE);
	DisplayVelocityK();
}


void CVelocityParameterDlg2::UpdateSlider( BOOL bUpdate )
{
	if( bUpdate == FALSE )
	{
		m_sliderParam1.SetValue( m_VelocityParameter2[ m_radioParam ].m_VcValue );
		m_sliderParam2.SetValue( m_VelocityParameter2[ m_radioParam ].m_K_Vc );


		m_sliderParam3.SetValue( m_VelocityParameter2[ m_radioParam ].m_VmaxMin, m_VelocityParameter2[ m_radioParam ].m_VmaxMax );
		m_sliderParam4.SetValue( m_VelocityParameter2[ m_radioParam ].m_K_Vmax );


		m_sliderParam5.SetValue( m_VelocityParameter2[ m_radioParam ].m_dVMin, m_VelocityParameter2[ m_radioParam ].m_dVMax );
		m_sliderParam6.SetValue( m_VelocityParameter2[ m_radioParam ].m_K_dV );

		m_sliderParam7.SetValue( m_VelocityParameter2[ m_radioParam ].m_Ak1 );
		m_sliderParam8.SetValue( m_VelocityParameter2[ m_radioParam ].m_Ak2 );
		m_sliderParam9.SetValue( m_VelocityParameter2[ m_radioParam ].m_Ak3 );
	}
	else
	{
		m_VelocityParameter2[ m_radioParam ].m_VcValue = m_sliderParam1.GetValue();
		m_VelocityParameter2[ m_radioParam ].m_K_Vc    = m_sliderParam2.GetValue();

		m_VelocityParameter2[ m_radioParam ].m_VmaxMin = m_sliderParam3.GetValueLeft();
		m_VelocityParameter2[ m_radioParam ].m_VmaxMax = m_sliderParam3.GetValueRight();
		m_VelocityParameter2[ m_radioParam ].m_K_Vmax  = m_sliderParam4.GetValue();

		m_VelocityParameter2[ m_radioParam ].m_dVMin   = m_sliderParam5.GetValueLeft();
		m_VelocityParameter2[ m_radioParam ].m_dVMax   = m_sliderParam5.GetValueRight();
		m_VelocityParameter2[ m_radioParam ].m_K_dV    = m_sliderParam6.GetValue();

		m_VelocityParameter2[ m_radioParam ].m_Ak1     = m_sliderParam7.GetValue();
		m_VelocityParameter2[ m_radioParam ].m_Ak2     = m_sliderParam8.GetValue();
		m_VelocityParameter2[ m_radioParam ].m_Ak3     = m_sliderParam9.GetValue();
	}
}


void CVelocityParameterDlg2::OnBnClickedOk()
{
	UpdateSlider(TRUE);

	Hide();
	CDialog::OnOK();
}


void CVelocityParameterDlg2::OnBnClickedCancel()
{
	for( int i=0 ; i<5 ; i++ )
		m_VelocityParameter2[i] = m_VelocityParameter2_backup[i];

	UpdateSlider( FALSE );

	Hide();

	CDialog::OnCancel();
}

bool CVelocityParameterDlg2::IsShow()
{
	return m_bDialogShow;
}

void CVelocityParameterDlg2::Show()
{
	UpdateSlider(FALSE);
	m_bDialogShow = true;
	//SetTimer(0, 500, NULL );
}

void CVelocityParameterDlg2::Hide()
{
	//KillTimer(0);
	m_bDialogShow = false;
}

void CVelocityParameterDlg2::DisplayVelocityK()
{
	EnterCriticalSection(&m_critVisionPrarameter2);

	UpdateSlider(TRUE);

	CClientDC dc(this);

	{
		m_displayVc.SetTextColor( RGB(255,255,255) );

		m_displayVc.FillSolidRect( 0, 0, m_displayVc.GetRect().Width(), m_displayVc.GetRect().Height(), RGB(0,0,0));

		int width = m_displayVc.GetRect().Width();
		int height = m_displayVc.GetRect().Height();
		{
			CPen pen, *pOldPen;
			pen.CreatePen( PS_SOLID, 1, RGB(64,64,64) );
			pOldPen = (CPen*)m_displayVc.SelectObject( &pen );

			m_displayVc.SelectStockObject( NULL_BRUSH );

//			pDC->Rectangle( graph2_x-180, graph2_y-100, graph2_x+180, graph2_y-100 );

			for( double x=0 ; x<1 ; x+=0.2 )
			{
				int dx = (int)( x * width/1.0 );
				m_displayVc.MoveTo( dx, 0 );
				m_displayVc.LineTo( dx, height );

				if( x > 0 )
				{
					CString tmp;
					tmp.Format(_T("%.1lf"), x);
					CRect rect = CRect( 0, 0, 100, 20 ) + CPoint(dx, height-15);
					rect.DeflateRect(1,1,1,1);
					//pDC->FillSolidRect( rect, title_bgcolor);
					m_displayVc.DrawText( tmp, rect, DT_LEFT);
				}
			}
			
			for( double y=0 ; y<5 ; y+=1.0 )
			{
				int dy = (int)( y * height / (m_sliderParam1.GetRangeMax()-m_sliderParam1.GetRangeMin()) );
				m_displayVc.MoveTo( 0, height-dy );
				m_displayVc.LineTo( width, height-dy );

				{
					CString tmp;
					tmp.Format(_T("%.1lf"), y);
					CRect rect = CRect( 0, 0, 100, 20 ) + CPoint(0, height-dy);
					rect.DeflateRect(1,1,1,1);
					//pDC->FillSolidRect( rect, title_bgcolor);
					m_displayVc.DrawText( tmp, rect, DT_LEFT);
				}
			}

			m_displayVc.SelectObject( pOldPen );

		}
		{
			CPen pen, *pOldPen;
			pen.CreatePen( PS_SOLID, 1, RGB(0,255,0) );
			pOldPen = (CPen*)m_displayVc.SelectObject( &pen );

			//m_displayVc.MoveTo( graph2_x-width, graph2_y );
			//m_displayVc.LineTo( graph2_x+width, graph2_y );
			//m_displayVc.MoveTo( graph2_x, graph2_y-height );
			//m_displayVc.LineTo( graph2_x, graph2_y+height );

			for( int x=0 ; x<width ; x++ )
			{
				double dis = x * 1.0 / width;
				double y = ( 0
					+ (double)(m_VelocityParameter2[ m_radioParam ].m_VcValue-0)
							*( 1.0 - exp( -(dis/m_VelocityParameter2[ m_radioParam ].m_K_Vc)
							              *(dis/m_VelocityParameter2[ m_radioParam ].m_K_Vc)  ) ) );

				if( x < 0 ) y = -y;

//				int y = (int)(atan2( (double)x, (double)m_VK_dvK )* m_VK_dvMax / (M_PI/2) );

				if( x == 0 )
					m_displayVc.MoveTo( x, height-(int)(y*height/(m_sliderParam1.GetRangeMax()-m_sliderParam1.GetRangeMin())) );
				else
					m_displayVc.LineTo( x, height-(int)(y*height/(m_sliderParam1.GetRangeMax()-m_sliderParam1.GetRangeMin())) );
			}

			m_displayVc.SelectObject( pOldPen );
		}

//			m_displayVc.SelectStockObject( WHITE_PEN );
//			m_displayVc.MoveTo( graph2_x-width, graph2_y-(int)(m_strategy.m_robot[0].m_dv*4) );
//			m_displayVc.LineTo( graph2_x+width, graph2_y-(int)(m_strategy.m_robot[0].m_dv*4) );

	}
	{
		m_displayVmax.SetTextColor( RGB(255,255,255) );
		m_displayVmax.FillSolidRect( 0, 0, m_displayVmax.GetRect().Width(), m_displayVmax.GetRect().Height(), RGB(0,0,0));

		int graph1_x = m_displayVmax.GetRect().Width()/2;
		int graph1_y = m_displayVmax.GetRect().Height();
		int width = m_displayVmax.GetRect().Width()/2;
		int height = m_displayVmax.GetRect().Height();
		{
			CPen pen, *pOldPen;
			pen.CreatePen( PS_SOLID, 1, RGB(64,64,64) );
			pOldPen = (CPen*)m_displayVmax.SelectObject( &pen );

			m_displayVmax.SelectStockObject( NULL_BRUSH );

//			m_displayVmax.Rectangle( graph1_x-width, graph1_y, graph1_x+width, graph1_y-height );

			for( double x=0 ; x<180 ; x+=45 )
			{
				int dx = (int)( x*width/180.0 );

				m_displayVmax.MoveTo( graph1_x+dx, graph1_y );
				m_displayVmax.LineTo( graph1_x+dx, graph1_y-height );
				m_displayVmax.MoveTo( graph1_x-dx, graph1_y );
				m_displayVmax.LineTo( graph1_x-dx, graph1_y-height );

				if( x > 0 )
				{
					{
						CString tmp;
						tmp.Format(_T("%.0lf"), x);
						CRect rect = CRect( 0, 0, 100, 20 ) + CPoint(graph1_x+dx, height-15);
						rect.DeflateRect(1,1,1,1);
						//pDC->FillSolidRect( rect, title_bgcolor);
						m_displayVmax.DrawText( tmp, rect, DT_LEFT);
					}
					{
						CString tmp;
						tmp.Format(_T("%.0lf"), -x);
						CRect rect = CRect( 0, 0, 100, 20 ) + CPoint(graph1_x-dx, height-15);
						rect.DeflateRect(1,1,1,1);
						//pDC->FillSolidRect( rect, title_bgcolor);
						m_displayVmax.DrawText( tmp, rect, DT_LEFT);
					}
				}
			}

			for( double y=0 ; y<5 ; y+=1.0 )
			{
				int dy = (int)( y * height / (m_sliderParam3.GetRangeMax()-m_sliderParam3.GetRangeMin()) );

				m_displayVmax.MoveTo( graph1_x-width, graph1_y-dy );
				m_displayVmax.LineTo( graph1_x+width, graph1_y-dy );
				m_displayVmax.MoveTo( graph1_x-width, graph1_y-dy );
				m_displayVmax.LineTo( graph1_x+width, graph1_y-dy );

				{
					CString tmp;
					tmp.Format(_T("%.1lf"), y);
					CRect rect = CRect( 0, 0, 100, 20 ) + CPoint(0, height-dy);
					rect.DeflateRect(1,1,1,1);
					//pDC->FillSolidRect( rect, title_bgcolor);
					m_displayVmax.DrawText( tmp, rect, DT_LEFT);
				}
			}

			m_displayVmax.SelectObject( pOldPen );
		}
		{
			CPen pen, *pOldPen;
			pen.CreatePen( PS_SOLID, 1, RGB(255,0,0) );
			pOldPen = (CPen*)m_displayVmax.SelectObject( &pen );

			m_displayVmax.MoveTo( graph1_x-width, graph1_y );
			m_displayVmax.LineTo( graph1_x+width, graph1_y );
			m_displayVmax.MoveTo( graph1_x, graph1_y-height );
			m_displayVmax.LineTo( graph1_x, graph1_y+height );

			for( int x=-width ; x<width ; x++ )
			{
				double e_theta = x*180.0/width;

				double y = (   m_VelocityParameter2[ m_radioParam ].m_VmaxMin
						+ (m_VelocityParameter2[ m_radioParam ].m_VmaxMax-m_VelocityParameter2[ m_radioParam ].m_VmaxMin)
						*( exp( -(e_theta/m_VelocityParameter2[ m_radioParam ].m_K_Vmax)
								*(e_theta/m_VelocityParameter2[ m_radioParam ].m_K_Vmax)  ) ) );

				int py = (int)( y * height / (m_sliderParam3.GetRangeMax()-m_sliderParam3.GetRangeMin()) );
				py = graph1_y - py;

				if( x == -width )
					m_displayVmax.MoveTo( x+graph1_x, py );
				else
					m_displayVmax.LineTo( x+graph1_x, py );
			}

			m_displayVmax.SelectObject( pOldPen );
		}
//			m_displaydV.SelectStockObject( WHITE_PEN );
//			m_displayVmax.MoveTo( graph1_x-width, graph1_y-(int)(m_strategy.m_robot[0].m_vc) );
//			m_displayVmax.LineTo( graph1_x+width, graph1_y-(int)(m_strategy.m_robot[0].m_vc) );

	}
	{
		m_displaydV.SetTextColor( RGB(255,255,255) );
		m_displaydV.FillSolidRect( 0, 0, m_displaydV.GetRect().Width(), m_displaydV.GetRect().Height(), RGB(0,0,0));

		int graph2_x = m_displaydV.GetRect().Width()/2;
		int graph2_y = m_displaydV.GetRect().Height()/2;
		int width = m_displaydV.GetRect().Width()/2;
		int height = m_displaydV.GetRect().Height()/2;
		{
			CPen pen, *pOldPen;
			pen.CreatePen( PS_SOLID, 1, RGB(64,64,64) );
			pOldPen = (CPen*)m_displaydV.SelectObject( &pen );

			m_displaydV.SelectStockObject( NULL_BRUSH );

//			pDC->Rectangle( graph2_x-180, graph2_y-100, graph2_x+180, graph2_y-100 );

			for( double x=0 ; x<180 ; x+=45 )
			{
				int dx = (int)( x*width/180.0 );

				m_displaydV.MoveTo( graph2_x+dx, graph2_y-height );
				m_displaydV.LineTo( graph2_x+dx, graph2_y+height );
				m_displaydV.MoveTo( graph2_x-dx, graph2_y-height );
				m_displaydV.LineTo( graph2_x-dx, graph2_y+height );

				if( x > 0 )
				{
					{
						CString tmp;
						tmp.Format(_T("%.0lf"), x);
						CRect rect = CRect( 0, 0, 100, 20 ) + CPoint(graph2_x+dx, height-15);
						rect.DeflateRect(1,1,1,1);
						//pDC->FillSolidRect( rect, title_bgcolor);
						m_displaydV.DrawText( tmp, rect, DT_LEFT);
					}
					{
						CString tmp;
						tmp.Format(_T("%.0lf"), -x);
						CRect rect = CRect( 0, 0, 100, 20 ) + CPoint(graph2_x-dx, height-15);
						rect.DeflateRect(1,1,1,1);
						//pDC->FillSolidRect( rect, title_bgcolor);
						m_displaydV.DrawText( tmp, rect, DT_LEFT);
					}
				}
			}


			for( double y=0 ; y<=360 ; y+=180.0 )
			{
				int dy = (int)( y * height / (m_sliderParam5.GetRangeMax()-m_sliderParam5.GetRangeMin()) );

				m_displaydV.MoveTo( graph2_x-width, graph2_y-dy );
				m_displaydV.LineTo( graph2_x+width, graph2_y-dy );
				m_displaydV.MoveTo( graph2_x-width, graph2_y+dy );
				m_displaydV.LineTo( graph2_x+width, graph2_y+dy );

				{
					CString tmp;
					tmp.Format(_T("%.1lf"), y);
					CRect rect = CRect( 0, 0, 100, 20 ) + CPoint(graph2_x-width, graph2_y-dy);
					rect.DeflateRect(1,1,1,1);
					//pDC->FillSolidRect( rect, title_bgcolor);
					m_displaydV.DrawText( tmp, rect, DT_LEFT);
				}
				{
					CString tmp;
					tmp.Format(_T("%.1lf"), -y);
					CRect rect = CRect( 0, 0, 100, 20 ) + CPoint(graph2_x-width, graph2_y+dy);
					rect.DeflateRect(1,1,1,1);
					//pDC->FillSolidRect( rect, title_bgcolor);
					m_displaydV.DrawText( tmp, rect, DT_LEFT);
				}
			}

			m_displaydV.SelectObject( pOldPen );
		}
		{
			CPen pen, *pOldPen;
			pen.CreatePen( PS_SOLID, 1, RGB(0,0,255) );
			pOldPen = (CPen*)m_displaydV.SelectObject( &pen );

			m_displaydV.MoveTo( graph2_x-width, graph2_y );
			m_displaydV.LineTo( graph2_x+width, graph2_y );
			m_displaydV.MoveTo( graph2_x, graph2_y-height );
			m_displaydV.LineTo( graph2_x, graph2_y+height );

			for( int x=-width ; x<width ; x++ )
			{
				double e_theta = x*180.0/width;

				double y = ( m_VelocityParameter2[ m_radioParam ].m_dVMin
							+ (double)(m_VelocityParameter2[ m_radioParam ].m_dVMax-m_VelocityParameter2[ m_radioParam ].m_dVMin)
							*( 1.0 - exp( -(e_theta/m_VelocityParameter2[ m_radioParam ].m_K_dV)
							              *(e_theta/m_VelocityParameter2[ m_radioParam ].m_K_dV)  ) ) );

				if( x < 0 ) y = -y;

//				int y = (int)(atan2( (double)x, (double)m_VK_dvK )* m_VK_dvMax / (M_PI/2) );

				int py = (int)( y * height / (m_sliderParam5.GetRangeMax()-m_sliderParam5.GetRangeMin()) );
				py = graph2_y - py;

				if( x == -width )
					m_displaydV.MoveTo( x+graph2_x, py );
				else
					m_displaydV.LineTo( x+graph2_x, py );
			}

			m_displaydV.SelectObject( pOldPen );
		}

//			m_displaydV.SelectStockObject( WHITE_PEN );
//			m_displaydV.MoveTo( graph2_x-width, graph2_y-(int)(m_strategy.m_robot[0].m_dv*4) );
//			m_displaydV.LineTo( graph2_x+width, graph2_y-(int)(m_strategy.m_robot[0].m_dv*4) );
	}

	m_displayVc.BitBlt(&dc);
	m_displayVmax.BitBlt( &dc );
	m_displaydV.BitBlt( &dc );

	LeaveCriticalSection(&m_critVisionPrarameter2);
}

void CVelocityParameterDlg2::OnPaint()
{
	CPaintDC dc(this); // device context for painting


	//DisplayVelocityK();
}

void CVelocityParameterDlg2::OnTimer(UINT_PTR nIDEvent)
{
	//DisplayVelocityK();	

	CDialog::OnTimer(nIDEvent);
}


void CVelocityParameterDlg2::OnBnClickedSaveV2File()
{
	/*
	TCHAR szFilter[] = _T("Robot Soccer Velocity Generation Parameters File(*.VGP)|*.VGP||");
	CFileDialog dlg(FALSE, _T("default"), _T("default"), NULL, szFilter);
		
	if( dlg.DoModal() == IDOK )
	{
		BeginWaitCursor();

		CFile file;
		
		file.Open( dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite );
		CArchive ar( &file, CArchive::store );
			
	
		EndWaitCursor();	
	}
	*/

	FILE *fp = fopen("vparam.txt", "wt");

	if( fp != NULL )
	{
		for( int p = 0 ; p<5 ; p++ )
		{
			fprintf( fp, "%lf\n", m_VelocityParameter2[p].m_VcValue );
			fprintf( fp, "%lf\n", m_VelocityParameter2[p].m_K_Vc    );
			fprintf( fp, "%lf\n", m_VelocityParameter2[p].m_VmaxMin );
			fprintf( fp, "%lf\n", m_VelocityParameter2[p].m_VmaxMax );
			fprintf( fp, "%lf\n", m_VelocityParameter2[p].m_K_Vmax  );
			fprintf( fp, "%lf\n", m_VelocityParameter2[p].m_dVMin   );
			fprintf( fp, "%lf\n", m_VelocityParameter2[p].m_dVMax   );
			fprintf( fp, "%lf\n", m_VelocityParameter2[p].m_K_dV    );
			fprintf( fp, "%lf\n", m_VelocityParameter2[p].m_Ak1     );
			fprintf( fp, "%lf\n", m_VelocityParameter2[p].m_Ak2     );
			fprintf( fp, "%lf\n", m_VelocityParameter2[p].m_Ak3     );
		}

		fclose(fp);
	}	
	else
	{
		AfxMessageBox(_T("save the speed control of robot into vparam.txt file failed."), MB_ICONERROR);
	}
}


void CVelocityParameterDlg2::OnBnClickedOpenV2File()
{
	/*
	TCHAR szFilter[] = _T("Robot Soccer Velocity Generation Parameters File(*.VGP)|*.VGP||");
	CFileDialog dlg(TRUE, _T("default"), _T("default"), NULL, szFilter);

	if( dlg.DoModal() == IDOK )
	{
		BeginWaitCursor();

		CFile file;
		
		if( file.Open( dlg.GetPathName(), CFile::modeRead ) == FALSE )
		{
			AfxMessageBox(_T("파일 열기가 실패하였습니다. (CRobotSoccerDlg::SaveSystem)"));
			return;
		}
		
		CArchive ar( &file, CArchive::load );
		
		CString fullname = dlg.GetPathName();
		CString filename = dlg.GetFileName();
		CString path = fullname.Left( fullname.GetLength() - filename.GetLength() );
		CString filename_only = filename.Left( filename.GetLength()-4 );

		CString tmp;
		ar >> tmp;

		ar.Close();
		file.Close();
		
		EndWaitCursor();
	}
	*/


	FILE *fp = fopen("vparam.txt", "rt");

	if( fp != NULL )
	{
		for( int p = 0 ; p<5 ; p++ )
		{
			fscanf( fp, "%lf", &m_VelocityParameter2[p].m_VcValue );
			fscanf( fp, "%lf", &m_VelocityParameter2[p].m_K_Vc    );
			fscanf( fp, "%lf", &m_VelocityParameter2[p].m_VmaxMin );
			fscanf( fp, "%lf", &m_VelocityParameter2[p].m_VmaxMax );
			fscanf( fp, "%lf", &m_VelocityParameter2[p].m_K_Vmax  );
			fscanf( fp, "%lf", &m_VelocityParameter2[p].m_dVMin   );
			fscanf( fp, "%lf", &m_VelocityParameter2[p].m_dVMax   );
			fscanf( fp, "%lf", &m_VelocityParameter2[p].m_K_dV    );
			fscanf( fp, "%lf", &m_VelocityParameter2[p].m_Ak1     );
			fscanf( fp, "%lf", &m_VelocityParameter2[p].m_Ak2     );
			fscanf( fp, "%lf", &m_VelocityParameter2[p].m_Ak3     );
		}

		fclose(fp);
	}
	else
	{
		AfxMessageBox(_T("Robot speed control file vparam.txt does not exist. Use the default values."), MB_ICONERROR);

		int p = 0;
		m_VelocityParameter2[p].m_VcValue = 2.00;
		m_VelocityParameter2[p].m_K_Vc    = 0.10;
		m_VelocityParameter2[p].m_VmaxMin = 0.00;
		m_VelocityParameter2[p].m_VmaxMax = 0.50;
		m_VelocityParameter2[p].m_K_Vmax  = 35.0;
		m_VelocityParameter2[p].m_dVMin   = 0;
		m_VelocityParameter2[p].m_dVMax   = 300;
		m_VelocityParameter2[p].m_K_dV    = 50;
		m_VelocityParameter2[p].m_Ak1     = 0.60;
		m_VelocityParameter2[p].m_Ak2     = 3.00;
		m_VelocityParameter2[p].m_Ak3     = 900;

		p = 1;
		m_VelocityParameter2[p].m_VcValue = 2.00;
		m_VelocityParameter2[p].m_K_Vc    = 0.25;
		m_VelocityParameter2[p].m_VmaxMin = 0.00;
		m_VelocityParameter2[p].m_VmaxMax = 1.50;
		m_VelocityParameter2[p].m_K_Vmax  = 35.0;
		m_VelocityParameter2[p].m_dVMin   = 0;
		m_VelocityParameter2[p].m_dVMax   = 300;
		m_VelocityParameter2[p].m_K_dV    = 50;
		m_VelocityParameter2[p].m_Ak1     = 3.00;
		m_VelocityParameter2[p].m_Ak2     = 3.00;
		m_VelocityParameter2[p].m_Ak3     = 900;
	

		p = 2;
		m_VelocityParameter2[p].m_VcValue = 2.00;
		m_VelocityParameter2[p].m_K_Vc    = 0.25;
		m_VelocityParameter2[p].m_VmaxMin = 0.00;
		m_VelocityParameter2[p].m_VmaxMax = 1.00;
		m_VelocityParameter2[p].m_K_Vmax  = 50.0;
		m_VelocityParameter2[p].m_dVMin   = 0;
		m_VelocityParameter2[p].m_dVMax   = 300;
		m_VelocityParameter2[p].m_K_dV    = 50;
		m_VelocityParameter2[p].m_Ak1     = 0.50;
		m_VelocityParameter2[p].m_Ak2     = 1.00;
		m_VelocityParameter2[p].m_Ak3     = 900;

		p = 3;
		m_VelocityParameter2[p].m_VcValue = 1.50;
		m_VelocityParameter2[p].m_K_Vc    = 0.05;
		m_VelocityParameter2[p].m_VmaxMin = 0.00;
		m_VelocityParameter2[p].m_VmaxMax = 0.80;
		m_VelocityParameter2[p].m_K_Vmax  = 35.0;
		m_VelocityParameter2[p].m_dVMin   = 0;
		m_VelocityParameter2[p].m_dVMax   = 300;
		m_VelocityParameter2[p].m_K_dV    = 50;
		m_VelocityParameter2[p].m_Ak1     = 2.0;
		m_VelocityParameter2[p].m_Ak2     = 4.0;
		m_VelocityParameter2[p].m_Ak3     = 900;

		p = 4;
		m_VelocityParameter2[p].m_VcValue = 1.50;
		m_VelocityParameter2[p].m_K_Vc    = 0.05;
		m_VelocityParameter2[p].m_VmaxMin = 0.00;
		m_VelocityParameter2[p].m_VmaxMax = 1.10;
		m_VelocityParameter2[p].m_K_Vmax  = 35.0;
		m_VelocityParameter2[p].m_dVMin   = 0;
		m_VelocityParameter2[p].m_dVMax   = 300;
		m_VelocityParameter2[p].m_K_dV    = 50;
		m_VelocityParameter2[p].m_Ak1     = 5.0;
		m_VelocityParameter2[p].m_Ak2     = 5.0;
		m_VelocityParameter2[p].m_Ak3     = 900;
	}	
}
