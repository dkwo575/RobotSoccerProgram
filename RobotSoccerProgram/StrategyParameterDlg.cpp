// StrategyParameterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "StrategyParameterDlg.h"
#include "afxdialogex.h"


// CStrategyParameterDlg dialog

IMPLEMENT_DYNAMIC(CStrategyParameterDlg, CDialog)

CStrategyParameterDlg::CStrategyParameterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStrategyParameterDlg::IDD, pParent)
{
	m_bActive = false;

	m_bDialogShow = false;

	m_StrategyParameter.m_AvoidBoundSize       = 0.05;
	m_StrategyParameter.m_LinearVelocityLimitA = 0.05;
	m_StrategyParameter.m_GoalYSize            = 0.191;
	m_StrategyParameter.m_DefenseLineX         = 0.44;
	m_StrategyParameter.m_OffenseLineX         = 0.44;
	m_StrategyParameter.m_GoalkeeperX          = 0.044;
	m_StrategyParameter.m_GoalkeeperYSize      = 0.14;
	m_StrategyParameter.m_GoalkeeperClearX     = 0.151;
	m_StrategyParameter.m_GoalkeeperClearYSize = 0.40;
	m_StrategyParameter.m_SweeperX             = 0.190;
	m_StrategyParameter.m_SweeperYSize         = 0.17;
	m_StrategyParameter.m_WingBack_Def_X       = 0.25;
	m_StrategyParameter.m_WingBack_Def_Y       = 0.5;
	m_StrategyParameter.m_WingBack_Nor_X       = 0.5;
	m_StrategyParameter.m_WingBack_Nor_Y       = 0.5;
	m_StrategyParameter.m_WingForward_Nor_X    = 0.5;
	m_StrategyParameter.m_WingForward_Nor_Y    = 0.5;
	m_StrategyParameter.m_WingForward_Off_X    = 1.15;
	m_StrategyParameter.m_WingForward_Off_Y    = 0.6;
	m_StrategyParameter.m_MF_X1                = 2.37;
	m_StrategyParameter.m_MF_X2                = 2.51;
	m_StrategyParameter.m_CenterBack_Def_X     = 0.40;
	m_StrategyParameter.m_CenterBack_Def_Y     = 0.21;
	m_StrategyParameter.m_CenterBack_Nor_X     = 1.0;
	m_StrategyParameter.m_CenterForward_Nor_X  = 1.95;
	m_StrategyParameter.m_CenterForward_Off_X  = 2.05;
	m_StrategyParameter.m_AverageVelocity      = 1.46;
	m_StrategyParameter.m_HitTime              = 0.62;

}

CStrategyParameterDlg::~CStrategyParameterDlg()
{
}

void CStrategyParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_1 , m_sliderParam01);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_2 , m_sliderParam02);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_3 , m_sliderParam03);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_4 , m_sliderParam04);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_5 , m_sliderParam05);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_6 , m_sliderParam06);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_7 , m_sliderParam07);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_8 , m_sliderParam08);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_9 , m_sliderParam09);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_10, m_sliderParam10);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_11, m_sliderParam11);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_12, m_sliderParam12);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_13, m_sliderParam13);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_14, m_sliderParam14);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_15, m_sliderParam15);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_16, m_sliderParam16);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_17, m_sliderParam17);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_18, m_sliderParam18);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_19, m_sliderParam19);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_20, m_sliderParam20);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_21, m_sliderParam21);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_22, m_sliderParam22);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_23, m_sliderParam23);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_24, m_sliderParam24);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_25, m_sliderParam25);
	DDX_Control(pDX, IDC_SLIDER_STRATEGY_PARAMETER_26, m_sliderParam26);
}


BEGIN_MESSAGE_MAP(CStrategyParameterDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CStrategyParameterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStrategyParameterDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CStrategyParameterDlg message handlers


BOOL CStrategyParameterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_sliderParam01.SetOption( _T("Bound Distance"), false, 0, 0.1, 0.001, 3 );
	m_sliderParam02.SetOption( _T("LinearVelocity Limit Acc."), false, 0, 0.1, 0.001, 3 );
	m_sliderParam03.SetOption( _T("Goal Y"), false, 0, 1, 0.001, 3 );

	m_sliderParam04.SetOption( _T("Def/Off X"), true, 0, 3, 0.01, 2 );
	m_sliderParam05.SetOption( _T("Goalkeeper X"), false, 0, 0.3, 0.001, 3 );
	m_sliderParam06.SetOption( _T("Goalkeeper Y"), false, 0, 1, 0.01, 2 );

	m_sliderParam07.SetOption( _T("GK Clear X"), false, 0, 0.4, 0.001, 3 );
	m_sliderParam08.SetOption( _T("GK Clear Y"), false, 0, 2, 0.01, 2 );

	m_sliderParam09.SetOption( _T("Sweeper X"), false, 0, 2, 0.001, 3 );
	m_sliderParam10.SetOption( _T("Sweeper Y Size"), false, 0, 3, 0.01, 2 );

	m_sliderParam11.SetOption( _T("WingBack Def.X"), false, 0, 4, 0.01, 2 );
	m_sliderParam12.SetOption( _T("WingBack Def.Y"), false, 0, 2, 0.01, 2 );

	m_sliderParam13.SetOption( _T("WingBack Nor.X"), false, 0, 4, 0.01, 2 );
	m_sliderParam14.SetOption( _T("WingBack Nor.Y"), false, 0, 2, 0.01, 2 );

	m_sliderParam15.SetOption( _T("WingForward Nor.X"), false, 0, 4, 0.01, 2 );
	m_sliderParam16.SetOption( _T("WingForward Nor.Y"), false, 0, 2, 0.01, 2 );

	m_sliderParam17.SetOption( _T("WingForward Off.X"), false, 0, 4, 0.01, 2 );
	m_sliderParam18.SetOption( _T("WingForward Off.Y"), false, 0, 2, 0.01, 2 );

	m_sliderParam19.SetOption( _T("WingForward Off.X"), true, 0, 4, 0.01, 2 );
	m_sliderParam20.SetOption( _T("CenterBack Def.X"), false, 0, 4, 0.01, 2 );
	m_sliderParam21.SetOption( _T("CenterBack Def.Y"), false, 0, 2, 0.01, 2 );
	m_sliderParam22.SetOption( _T("CenterBack Nor.X"), false, 0, 4, 0.01, 2 );
	m_sliderParam23.SetOption( _T("CenterForward Nor.X"), false, 0, 4, 0.01, 2 );
	m_sliderParam24.SetOption( _T("CenterForward Off.X"), false, 0, 4, 0.01, 2 );
	m_sliderParam25.SetOption( _T("Average Velocity"), false, 0, 4, 0.01, 2 );
	m_sliderParam26.SetOption( _T("Prediction Time"), false, 0, 1, 0.01, 2 );


	m_bActive = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



CStrategyParameter CStrategyParameterDlg::GetParameters()
{
	if( m_bDialogShow == false )
	{
		return m_StrategyParameter;
	}

	CStrategyParameter param;

	param.m_AvoidBoundSize       = m_sliderParam01.GetValue();
	param.m_LinearVelocityLimitA = m_sliderParam02.GetValue();
	param.m_GoalYSize            = m_sliderParam03.GetValue();
	param.m_DefenseLineX         = m_sliderParam04.GetValueLeft();
	param.m_OffenseLineX         = m_sliderParam04.GetValueRight();
	param.m_GoalkeeperX          = m_sliderParam05.GetValue();
	param.m_GoalkeeperYSize      = m_sliderParam06.GetValue();
	param.m_GoalkeeperClearX     = m_sliderParam07.GetValue();
	param.m_GoalkeeperClearYSize = m_sliderParam08.GetValue();
	param.m_SweeperX             = m_sliderParam09.GetValue();
	param.m_SweeperYSize         = m_sliderParam10.GetValue();
	param.m_WingBack_Def_X       = m_sliderParam11.GetValue();
	param.m_WingBack_Def_Y       = m_sliderParam12.GetValue();
	param.m_WingBack_Nor_X       = m_sliderParam13.GetValue();
	param.m_WingBack_Nor_Y       = m_sliderParam14.GetValue();
	param.m_WingForward_Nor_X    = m_sliderParam15.GetValue();
	param.m_WingForward_Nor_Y    = m_sliderParam16.GetValue();
	param.m_WingForward_Off_X    = m_sliderParam17.GetValue();
	param.m_WingForward_Off_Y    = m_sliderParam18.GetValue();
	param.m_MF_X1                = m_sliderParam19.GetValueLeft();
	param.m_MF_X2                = m_sliderParam19.GetValueRight();
	param.m_CenterBack_Def_X     = m_sliderParam20.GetValue();
	param.m_CenterBack_Def_Y     = m_sliderParam21.GetValue();
	param.m_CenterBack_Nor_X     = m_sliderParam22.GetValue();
	param.m_CenterForward_Nor_X  = m_sliderParam23.GetValue();
	param.m_CenterForward_Off_X  = m_sliderParam24.GetValue();
	param.m_AverageVelocity      = m_sliderParam25.GetValue();
	param.m_HitTime              = m_sliderParam26.GetValue();


	return param;
}

void CStrategyParameterDlg::SetParameters( CStrategyParameter param )
{
	m_StrategyParameter = param;

	UpdateSlider();
}

void CStrategyParameterDlg::UpdateSlider()
{
	m_sliderParam01.SetValue( m_StrategyParameter.m_AvoidBoundSize );
	m_sliderParam02.SetValue( m_StrategyParameter.m_LinearVelocityLimitA );
	m_sliderParam03.SetValue( m_StrategyParameter.m_GoalYSize );
	m_sliderParam04.SetValue( m_StrategyParameter.m_DefenseLineX, m_StrategyParameter.m_OffenseLineX );
	m_sliderParam05.SetValue( m_StrategyParameter.m_GoalkeeperX );
	m_sliderParam06.SetValue( m_StrategyParameter.m_GoalkeeperYSize );
	m_sliderParam07.SetValue( m_StrategyParameter.m_GoalkeeperClearX );
	m_sliderParam08.SetValue( m_StrategyParameter.m_GoalkeeperClearYSize );
	m_sliderParam09.SetValue( m_StrategyParameter.m_SweeperX );
	m_sliderParam10.SetValue( m_StrategyParameter.m_SweeperYSize );
	m_sliderParam11.SetValue( m_StrategyParameter.m_WingBack_Def_X );
	m_sliderParam12.SetValue( m_StrategyParameter.m_WingBack_Def_Y );
	m_sliderParam13.SetValue( m_StrategyParameter.m_WingBack_Nor_X );
	m_sliderParam14.SetValue( m_StrategyParameter.m_WingBack_Nor_Y );
	m_sliderParam15.SetValue( m_StrategyParameter.m_WingForward_Nor_X );
	m_sliderParam16.SetValue( m_StrategyParameter.m_WingForward_Nor_Y );
	m_sliderParam17.SetValue( m_StrategyParameter.m_WingForward_Off_X );
	m_sliderParam18.SetValue( m_StrategyParameter.m_WingForward_Off_Y );
	m_sliderParam19.SetValue( m_StrategyParameter.m_MF_X1, m_StrategyParameter.m_MF_X2 );
	m_sliderParam20.SetValue( m_StrategyParameter.m_CenterBack_Def_X );
	m_sliderParam21.SetValue( m_StrategyParameter.m_CenterBack_Def_Y );
	m_sliderParam22.SetValue( m_StrategyParameter.m_CenterBack_Nor_X );
	m_sliderParam23.SetValue( m_StrategyParameter.m_CenterForward_Nor_X );
	m_sliderParam24.SetValue( m_StrategyParameter.m_CenterForward_Off_X );
	m_sliderParam25.SetValue( m_StrategyParameter.m_AverageVelocity );
	m_sliderParam26.SetValue( m_StrategyParameter.m_HitTime );
}


void CStrategyParameterDlg::OnBnClickedOk()
{
	CStrategyParameter param;

	param.m_AvoidBoundSize       = m_sliderParam01.GetValue();
	param.m_LinearVelocityLimitA = m_sliderParam02.GetValue();
	param.m_GoalYSize            = m_sliderParam03.GetValue();
	param.m_DefenseLineX         = m_sliderParam04.GetValueLeft();
	param.m_OffenseLineX         = m_sliderParam04.GetValueRight();
	param.m_GoalkeeperX          = m_sliderParam05.GetValue();
	param.m_GoalkeeperYSize      = m_sliderParam06.GetValue();
	param.m_GoalkeeperClearX     = m_sliderParam07.GetValue();
	param.m_GoalkeeperClearYSize = m_sliderParam08.GetValue();
	param.m_SweeperX             = m_sliderParam09.GetValue();
	param.m_SweeperYSize         = m_sliderParam10.GetValue();
	param.m_WingBack_Def_X       = m_sliderParam11.GetValue();
	param.m_WingBack_Def_Y       = m_sliderParam12.GetValue();
	param.m_WingBack_Nor_X       = m_sliderParam13.GetValue();
	param.m_WingBack_Nor_Y       = m_sliderParam14.GetValue();
	param.m_WingForward_Nor_X    = m_sliderParam15.GetValue();
	param.m_WingForward_Nor_Y    = m_sliderParam16.GetValue();
	param.m_WingForward_Off_X    = m_sliderParam17.GetValue();
	param.m_WingForward_Off_Y    = m_sliderParam18.GetValue();
	param.m_MF_X1                = m_sliderParam19.GetValueLeft();
	param.m_MF_X2                = m_sliderParam19.GetValueRight();
	param.m_CenterBack_Def_X     = m_sliderParam20.GetValue();
	param.m_CenterBack_Def_Y     = m_sliderParam21.GetValue();
	param.m_CenterBack_Nor_X     = m_sliderParam22.GetValue();
	param.m_CenterForward_Nor_X  = m_sliderParam23.GetValue();
	param.m_CenterForward_Off_X  = m_sliderParam24.GetValue();
	param.m_AverageVelocity      = m_sliderParam25.GetValue();
	param.m_HitTime              = m_sliderParam26.GetValue();

	m_StrategyParameter = param;

	Hide();
	CDialog::OnOK();
}


void CStrategyParameterDlg::OnBnClickedCancel()
{
	Hide();
	CDialog::OnCancel();
}

bool CStrategyParameterDlg::IsShow()
{
	return m_bDialogShow;
}

void CStrategyParameterDlg::Show()
{
	UpdateSlider();

	m_bDialogShow = true;
}

void CStrategyParameterDlg::Hide()
{
	m_bDialogShow = false;
}
