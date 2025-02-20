// VelocityParameterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "VelocityParameterDlg.h"
#include "afxdialogex.h"


// CVelocityParameterDlg dialog

IMPLEMENT_DYNAMIC(CVelocityParameterDlg, CDialog)

CVelocityParameterDlg::CVelocityParameterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVelocityParameterDlg::IDD, pParent)
{
	m_bActive = false;

	m_bDialogShow = false;

	m_VelocityParameter.m_Acceleration = 1.5;
	m_VelocityParameter.m_Deceleration = 1.4;
	m_VelocityParameter.m_CentripetalAcceleration = 4.2;
	m_VelocityParameter.m_MaxAccelerationLimit = 2.8;
	m_VelocityParameter.m_MaxVelocityLimit = 2.2;
	m_VelocityParameter.m_PathErrorGain = 4;
	m_VelocityParameter.m_AngularVelocityErrorPGain = 9;
	m_VelocityParameter.m_AngularVelocityErrorDGain = 10;
}

CVelocityParameterDlg::~CVelocityParameterDlg()
{
}

void CVelocityParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_1, m_sliderAcceleration);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_2, m_sliderDeceleration);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_3, m_sliderCentripetalAcceleration);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_4, m_sliderMaxAccelerationLimit);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_5, m_sliderMaxVelocityLimit);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_6, m_sliderPathErrorGain);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_7, m_sliderAngularVelocityErrorPGain);
	DDX_Control(pDX, IDC_SLIDER_VELOCITY_PARAMETER1_8, m_sliderAngularVelocityErrorDGain);
}


BEGIN_MESSAGE_MAP(CVelocityParameterDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CVelocityParameterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CVelocityParameterDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CVelocityParameterDlg message handlers


BOOL CVelocityParameterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	m_sliderAcceleration.SetOption( _T("Acceleration"), false, 0, 6, 0.1, 1 );
	
	m_sliderDeceleration.SetOption( _T("Deceleration"), false, 0, 6, 0.1, 1 );

	m_sliderCentripetalAcceleration.SetOption( _T("Centripedal Acceleration"), false, 0, 10, 0.1, 1 );

	m_sliderMaxAccelerationLimit.SetOption( _T("Max. Acceleration"), false, 0, 6, 0.1, 1 );

	m_sliderMaxVelocityLimit.SetOption( _T("Max Velocity"), false, 0, 4, 0.1, 1 );

	m_sliderPathErrorGain.SetOption( _T("Path Error gain"), false, 0, 100, 1, 0 );

	m_sliderAngularVelocityErrorPGain.SetOption( _T("Angular Velocity Error P gain"), false, 0, 100, 1, 0 );

	m_sliderAngularVelocityErrorDGain.SetOption( _T("Angular Velocity Error D gain"), false, 0, 100, 1, 0 );


	m_bActive = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVelocityParameter CVelocityParameterDlg::GetParameters()
{
	if( m_bDialogShow == false )
		return m_VelocityParameter;

	CVelocityParameter param;

	param.m_Acceleration                    = m_sliderAcceleration.GetValue();
	param.m_Deceleration                    = m_sliderDeceleration.GetValue();
	param.m_CentripetalAcceleration         = m_sliderCentripetalAcceleration.GetValue();
	param.m_MaxAccelerationLimit            = m_sliderMaxAccelerationLimit.GetValue();
	param.m_MaxVelocityLimit                = m_sliderMaxVelocityLimit.GetValue();
	param.m_PathErrorGain                   = m_sliderPathErrorGain.GetValue();
	param.m_AngularVelocityErrorPGain       = m_sliderAngularVelocityErrorPGain.GetValue();
	param.m_AngularVelocityErrorDGain       = m_sliderAngularVelocityErrorDGain.GetValue();

	return param;
}

void CVelocityParameterDlg::SetParameters( CVelocityParameter param )
{
	m_VelocityParameter = param;

	UpdateSlider();
}

void CVelocityParameterDlg::UpdateSlider()
{
	m_sliderAcceleration.SetValue( m_VelocityParameter.m_Acceleration );
	m_sliderDeceleration.SetValue( m_VelocityParameter.m_Deceleration );
	m_sliderCentripetalAcceleration.SetValue( m_VelocityParameter.m_CentripetalAcceleration );
	m_sliderMaxAccelerationLimit.SetValue( m_VelocityParameter.m_MaxAccelerationLimit );
	m_sliderMaxVelocityLimit.SetValue( m_VelocityParameter.m_MaxVelocityLimit );
	m_sliderPathErrorGain.SetValue( m_VelocityParameter.m_PathErrorGain );
	m_sliderAngularVelocityErrorPGain.SetValue( m_VelocityParameter.m_AngularVelocityErrorPGain );
	m_sliderAngularVelocityErrorDGain.SetValue( m_VelocityParameter.m_AngularVelocityErrorDGain );
}


void CVelocityParameterDlg::OnBnClickedOk()
{
	CVelocityParameter param;

	param.m_Acceleration                    = m_sliderAcceleration.GetValue();
	param.m_Deceleration                    = m_sliderDeceleration.GetValue();
	param.m_CentripetalAcceleration         = m_sliderCentripetalAcceleration.GetValue();
	param.m_MaxAccelerationLimit            = m_sliderMaxAccelerationLimit.GetValue();
	param.m_MaxVelocityLimit                = m_sliderMaxVelocityLimit.GetValue();
	param.m_PathErrorGain                   = m_sliderPathErrorGain.GetValue();
	param.m_AngularVelocityErrorPGain       = m_sliderAngularVelocityErrorPGain.GetValue();
	param.m_AngularVelocityErrorDGain       = m_sliderAngularVelocityErrorDGain.GetValue();

	m_VelocityParameter = param;
	
	Hide();
	CDialog::OnOK();
}


void CVelocityParameterDlg::OnBnClickedCancel()
{
	Hide();
	CDialog::OnCancel();
}


bool CVelocityParameterDlg::IsShow()
{
	return m_bDialogShow;
}

void CVelocityParameterDlg::Show()
{
	UpdateSlider();

	m_bDialogShow = true;
}

void CVelocityParameterDlg::Hide()
{
	m_bDialogShow = false;
}
