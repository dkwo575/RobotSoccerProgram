// PropertyPageGame.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "PropertyPageGame.h"
#include "afxdialogex.h"

#include <fstream>


// CPropertyPageGame dialog

IMPLEMENT_DYNAMIC(CPropertyPageGame, CPropertyPageRobotSoccer)

CPropertyPageGame::CPropertyPageGame()
	: CPropertyPageRobotSoccer(CPropertyPageGame::IDD)
	, m_strAutoPositionFileName(_T(""))
	, m_radioSituation(FALSE)
	, m_strSituationOption(_T(""))
	, m_bRobotMessage(FALSE)
	, m_bRobotMessageSelectOnly(FALSE)
	, m_radioMoveType(0)
	, m_strStrategyFile(_T(""))
	, m_strRobot01Name(_T(""))
	, m_strRobot02Name(_T(""))
	, m_strRobot03Name(_T(""))
	, m_strRobot04Name(_T(""))
	, m_strRobot05Name(_T(""))
	/*, m_strRobot06Name(_T(""))
	, m_strRobot07Name(_T(""))
	, m_strRobot08Name(_T(""))
	, m_strRobot09Name(_T(""))
	, m_strRobot10Name(_T(""))
	, m_strRobot11Name(_T(""))*/
	, m_checkRoleChange(FALSE)
	, m_strStrategyFileName(_T(""))
	, m_bShowAutoposition(FALSE)
{
	InitializeCriticalSection(&m_critPropGameGUI);

	m_bCopyStrategyGUI = false;

	m_radioSituation = 0;
	m_radioGameStrategyType = 1;

	m_bLButton = false;
	m_bRButton = false;

	m_bDragMove = false;
	m_bDragScreen = false;

	m_bStepFirst = false;

	m_checkRobot01 = TRUE;
	m_checkRobot02 = TRUE;
	m_checkRobot03 = TRUE;
	m_checkRobot04 = TRUE;
	m_checkRobot05 = TRUE;
	/*m_checkRobot06 = TRUE;
	m_checkRobot07 = TRUE;
	m_checkRobot08 = TRUE;
	m_checkRobot09 = TRUE;
	m_checkRobot10 = TRUE;
	m_checkRobot11 = TRUE;*/
	m_strRobot01Role = _T("");
	m_strSituation = _T("");

	m_bDebugWheel = false;
}

CPropertyPageGame::~CPropertyPageGame()
{
	DeleteCriticalSection(&m_critPropGameGUI);
}

void CPropertyPageGame::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageRobotSoccer::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AUTOPOSITION_FILE_NAME, m_strAutoPositionFileName);
	//  DDX_Radio(pDX, IDC_RADIO_SITUATION_ATTACK1, m_radioSituationOffenseDefence);
	DDX_Radio(pDX, IDC_RADIO_SITUATION1, m_radioSituation);
	//DDX_CBString(pDX, IDC_COMBO_SITUATION_OPTION, m_strSituationOption);
	DDX_Check(pDX, IDC_CHECK_SHOW_ROBOT_MESSAGE, m_bRobotMessage);
	DDX_Check(pDX, IDC_CHECK_SHOW_ROBOT_MESSAGE_ONLY, m_bRobotMessageSelectOnly);
	DDX_Radio(pDX, IDC_RADIO_MOVE_TYPE1, m_radioMoveType);
	DDX_Control(pDX, IDC_SLIDER_PATH_TEST1, m_sliderPathTest1);
	DDX_Control(pDX, IDC_SLIDER_PATH_TEST2, m_sliderPathTest2);
	DDX_Control(pDX, IDC_SLIDER_PATH_TEST3, m_sliderPathTest3);
	DDX_Control(pDX, IDC_SLIDER_PATH_TEST4, m_sliderPathTest4);
	DDX_Text(pDX, IDC_EDIT_STRATEGY_FILE_NAME, m_strStrategyFile);
	DDX_Control(pDX, IDC_COMBO_ROBOT_01_NAME, m_comboRobot01Name);
	DDX_Control(pDX, IDC_COMBO_ROBOT_02_NAME, m_comboRobot02Name);
	DDX_Control(pDX, IDC_COMBO_ROBOT_03_NAME, m_comboRobot03Name);
	DDX_Control(pDX, IDC_COMBO_ROBOT_04_NAME, m_comboRobot04Name);
	DDX_Control(pDX, IDC_COMBO_ROBOT_05_NAME, m_comboRobot05Name);
	/*DDX_Control(pDX, IDC_COMBO_ROBOT_06_NAME, m_comboRobot06Name);
	DDX_Control(pDX, IDC_COMBO_ROBOT_07_NAME, m_comboRobot07Name);
	DDX_Control(pDX, IDC_COMBO_ROBOT_08_NAME, m_comboRobot08Name);
	DDX_Control(pDX, IDC_COMBO_ROBOT_09_NAME, m_comboRobot09Name);
	DDX_Control(pDX, IDC_COMBO_ROBOT_10_NAME, m_comboRobot10Name);*/
	//DDX_Control(pDX, IDC_COMBO_ROBOT_11_NAME, m_comboRobot11Name);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_01_NAME, m_strRobot01Name);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_02_NAME, m_strRobot02Name);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_03_NAME, m_strRobot03Name);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_04_NAME, m_strRobot04Name);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_05_NAME, m_strRobot05Name);
	/*DDX_CBString(pDX, IDC_COMBO_ROBOT_06_NAME, m_strRobot06Name);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_07_NAME, m_strRobot07Name);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_08_NAME, m_strRobot08Name);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_09_NAME, m_strRobot09Name);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_10_NAME, m_strRobot10Name);*/
	//DDX_CBString(pDX, IDC_COMBO_ROBOT_11_NAME, m_strRobot11Name);
	//DDX_Check(pDX, IDC_CHECK_ROBOT_01, m_checkRobot01);
	//DDX_Check(pDX, IDC_CHECK_ROBOT_02, m_checkRobot02);
	//DDX_Check(pDX, IDC_CHECK_ROBOT_03, m_checkRobot03);
	//DDX_Check(pDX, IDC_CHECK_ROBOT_04, m_checkRobot04);
	//DDX_Check(pDX, IDC_CHECK_ROBOT_05, m_checkRobot05);
	//DDX_Check(pDX, IDC_CHECK_ROBOT_06, m_checkRobot06);
	//DDX_Check(pDX, IDC_CHECK_ROBOT_07, m_checkRobot07);
	//DDX_Check(pDX, IDC_CHECK_ROBOT_08, m_checkRobot08);
	//DDX_Check(pDX, IDC_CHECK_ROBOT_09, m_checkRobot09);
	//DDX_Check(pDX, IDC_CHECK_ROBOT_10, m_checkRobot10);
	//DDX_Check(pDX, IDC_CHECK_ROBOT_11, m_checkRobot11);
	DDX_Check(pDX, IDC_CHECK_ROLE_CHANGE, m_checkRoleChange);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME_STRATEGY, m_strStrategyFileName);
	DDX_Control(pDX, IDC_COMBO_ROBOT_01_ROLE, m_comobRobot01Role);
	DDX_Control(pDX, IDC_COMBO_ROBOT_02_ROLE, m_comobRobot02Role);
	DDX_Control(pDX, IDC_COMBO_ROBOT_03_ROLE, m_comobRobot03Role);
	DDX_Control(pDX, IDC_COMBO_ROBOT_04_ROLE, m_comobRobot04Role);
	DDX_Control(pDX, IDC_COMBO_ROBOT_05_ROLE, m_comobRobot05Role);
	/*DDX_Control(pDX, IDC_COMBO_ROBOT_06_ROLE, m_comobRobot06Role);
	DDX_Control(pDX, IDC_COMBO_ROBOT_07_ROLE, m_comobRobot07Role);
	DDX_Control(pDX, IDC_COMBO_ROBOT_08_ROLE, m_comobRobot08Role);
	DDX_Control(pDX, IDC_COMBO_ROBOT_09_ROLE, m_comobRobot09Role);
	DDX_Control(pDX, IDC_COMBO_ROBOT_10_ROLE, m_comobRobot10Role);*/
	//DDX_Control(pDX, IDC_COMBO_ROBOT_11_ROLE, m_comobRobot11Role);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_01_ROLE, m_strRobot01Role);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_02_ROLE, m_strRobot02Role);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_03_ROLE, m_strRobot03Role);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_04_ROLE, m_strRobot04Role);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_05_ROLE, m_strRobot05Role);
	/*DDX_CBString(pDX, IDC_COMBO_ROBOT_06_ROLE, m_strRobot06Role);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_07_ROLE, m_strRobot07Role);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_08_ROLE, m_strRobot08Role);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_09_ROLE, m_strRobot09Role);
	DDX_CBString(pDX, IDC_COMBO_ROBOT_10_ROLE, m_strRobot10Role);*/
	//DDX_CBString(pDX, IDC_COMBO_ROBOT_11_ROLE, m_strRobot11Role);
	DDX_Radio(pDX, IDC_RADIO_GAME_STRATEGY_TYPE_01, m_radioGameStrategyType);
	DDX_Check(pDX, IDC_CHECK_SHOW_AUTOPOSITION, m_bShowAutoposition);
	DDX_CBString(pDX, IDC_COMBO_SITUATION, m_strSituation);
	DDX_Control(pDX, IDC_COMBO_SITUATION, m_comboSituation);
}


BEGIN_MESSAGE_MAP(CPropertyPageGame, CPropertyPageRobotSoccer)
	ON_BN_CLICKED(IDC_GAME_READY, &CPropertyPageGame::OnBnClickedGameReady)
	ON_BN_CLICKED(IDC_GAME_START, &CPropertyPageGame::OnBnClickedGameStart)
	ON_BN_CLICKED(IDC_GAME_STOP, &CPropertyPageGame::OnBnClickedGameStop)
	ON_BN_CLICKED(IDC_OPEN_AUTOPOSITION_FILE, &CPropertyPageGame::OnBnClickedOpenAutopositionFile)
	ON_BN_CLICKED(IDC_SAVE_AUTOPOSITION_FILE, &CPropertyPageGame::OnBnClickedSaveAutopositionFile)
	ON_BN_CLICKED(IDC_AUTOPOS_UPDATE, &CPropertyPageGame::OnBnClickedAutoposUpdate)
	ON_BN_CLICKED(IDC_RADIO_SITUATION1, &CPropertyPageGame::OnBnClickedRadioSituation1)
	ON_BN_CLICKED(IDC_RADIO_SITUATION2, &CPropertyPageGame::OnBnClickedRadioSituation2)
	ON_BN_CLICKED(IDC_RADIO_SITUATION3, &CPropertyPageGame::OnBnClickedRadioSituation3)
	ON_BN_CLICKED(IDC_RADIO_SITUATION4, &CPropertyPageGame::OnBnClickedRadioSituation4)
	ON_BN_CLICKED(IDC_RADIO_SITUATION5, &CPropertyPageGame::OnBnClickedRadioSituation5)
	ON_BN_CLICKED(IDC_RADIO_SITUATION6, &CPropertyPageGame::OnBnClickedRadioSituation6)
	ON_BN_CLICKED(IDC_RADIO_SITUATION7, &CPropertyPageGame::OnBnClickedRadioSituation7)
	ON_BN_CLICKED(IDC_RADIO_SITUATION8, &CPropertyPageGame::OnBnClickedRadioSituation8)
	ON_BN_CLICKED(IDC_CHECK_SHOW_ROBOT_MESSAGE, &CPropertyPageGame::OnBnClickedCheckShowRobotMessage)
	ON_BN_CLICKED(IDC_CHECK_SHOW_ROBOT_MESSAGE_ONLY, &CPropertyPageGame::OnBnClickedCheckShowRobotMessageOnly)
	ON_BN_CLICKED(IDC_RADIO_MOVE_TYPE1, &CPropertyPageGame::OnBnClickedRadioMoveType1)
	ON_BN_CLICKED(IDC_RADIO_MOVE_TYPE2, &CPropertyPageGame::OnBnClickedRadioMoveType2)
	ON_BN_CLICKED(IDC_RADIO_MOVE_TYPE3, &CPropertyPageGame::OnBnClickedRadioMoveType3)
	ON_BN_CLICKED(IDC_RADIO_MOVE_TYPE4, &CPropertyPageGame::OnBnClickedRadioMoveType4)
	ON_BN_CLICKED(IDC_RADIO_MOVE_TYPE5, &CPropertyPageGame::OnBnClickedRadioMoveType5)
	ON_BN_CLICKED(IDC_RADIO_MOVE_TYPE6, &CPropertyPageGame::OnBnClickedRadioMoveType6)
	ON_BN_CLICKED(IDC_OPEN_STRATEGY_FILE, &CPropertyPageGame::OnBnClickedOpenStrategyFile)
	ON_BN_CLICKED(IDC_SAVE_STRATEGY_FILE, &CPropertyPageGame::OnBnClickedSaveStrategyFile)
	ON_BN_CLICKED(IDC_VELOCITY_PARAMETER, &CPropertyPageGame::OnBnClickedVelocityParameter)
	ON_BN_CLICKED(IDC_VELOCITY_PARAMETER2, &CPropertyPageGame::OnBnClickedVelocityParameter2)
	ON_BN_CLICKED(IDC_STRATEGY_PARAMETER, &CPropertyPageGame::OnBnClickedStrategyParameter)
	ON_BN_CLICKED(IDC_PATH_TEST, &CPropertyPageGame::OnBnClickedPathTest)
	ON_BN_CLICKED(IDC_GAME_START_STEP, &CPropertyPageGame::OnBnClickedGameStartStep)
	ON_BN_CLICKED(IDC_KICK_TEST, &CPropertyPageGame::OnBnClickedKickTest)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RESET_SCREEN, &CPropertyPageGame::OnBnClickedResetScreen)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_01, &CPropertyPageGame::OnBnClickedCheckRobot01)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_02, &CPropertyPageGame::OnBnClickedCheckRobot02)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_03, &CPropertyPageGame::OnBnClickedCheckRobot03)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_04, &CPropertyPageGame::OnBnClickedCheckRobot04)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_05, &CPropertyPageGame::OnBnClickedCheckRobot05)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_06, &CPropertyPageGame::OnBnClickedCheckRobot06)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_07, &CPropertyPageGame::OnBnClickedCheckRobot07)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_08, &CPropertyPageGame::OnBnClickedCheckRobot08)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_09, &CPropertyPageGame::OnBnClickedCheckRobot09)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_10, &CPropertyPageGame::OnBnClickedCheckRobot10)
	ON_BN_CLICKED(IDC_CHECK_ROBOT_11, &CPropertyPageGame::OnBnClickedCheckRobot11)
	ON_BN_CLICKED(IDC_CHECK_ROLE_CHANGE, &CPropertyPageGame::OnBnClickedCheckRoleChange)
	ON_BN_CLICKED(IDC_LOAD_SET_PLAY, &CPropertyPageGame::OnBnClickedLoadSetPlay)
	ON_BN_CLICKED(IDC_OPEN_STRATEGY, &CPropertyPageGame::OnBnClickedOpenStrategy)
	//	ON_BN_CLICKED(IDC_CHECK_STRATEGY_GUI, &CPropertyPageGame::OnBnClickedCheckStrategyGui)
	//ON_BN_CLICKED(IDC_RADIO_SITUATION_ATTACK3, &CPropertyPageGame::OnBnClickedRadioSituationAttack3)
	ON_BN_CLICKED(IDC_RADIO_GAME_STRATEGY_TYPE_01, &CPropertyPageGame::OnBnClickedRadioGameStrategyType01)
	ON_BN_CLICKED(IDC_RADIO_GAME_STRATEGY_TYPE_02, &CPropertyPageGame::OnBnClickedRadioGameStrategyType02)
	ON_BN_CLICKED(IDC_COPY_STRATEGY_GUI, &CPropertyPageGame::OnBnClickedCopyStrategyGui)
	ON_BN_CLICKED(IDC_ROBOT_ID_ASSIGN, &CPropertyPageGame::OnBnClickedRobotIdAssign)
	ON_BN_CLICKED(IDC_CHECK_SHOW_AUTOPOSITION, &CPropertyPageGame::OnBnClickedCheckShowAutoposition)
	ON_BN_CLICKED(IDC_AUTOPOS_ASSIGN, &CPropertyPageGame::OnBnClickedAutoposAssign)
	ON_BN_CLICKED(IDC_RADIO_SITUATION9, &CPropertyPageGame::OnBnClickedRadioSituation9)
	ON_BN_CLICKED(IDC_RADIO_SITUATION10, &CPropertyPageGame::OnBnClickedRadioSituation10)
	ON_BN_CLICKED(IDC_RADIO_SITUATION11, &CPropertyPageGame::OnBnClickedRadioSituation11)
	ON_CBN_SELCHANGE(IDC_COMBO_SITUATION, &CPropertyPageGame::OnSelchangeComboSituation)
	//ON_CBN_SELENDOK(IDC_COMBO_SITUATION, &CPropertyPageGame::OnSelendokComboSituation)
	//ON_BN_CLICKED(IDC_CHECK_CAMERA_IMAGE, &CPropertyPageGame::OnBnClickedCheckCameraImage)
	ON_CBN_SELCHANGE(IDC_COMBO_ROBOT_04_NAME, &CPropertyPageGame::OnCbnSelchangeComboRobot04Name)
	ON_STN_CLICKED(IDC_STATIC_PROP_GAME_ROBOT_04, &CPropertyPageGame::OnStnClickedStaticPropGameRobot04)
	ON_STN_CLICKED(IDC_STATIC_PROP_GAME_ROBOT_05, &CPropertyPageGame::OnStnClickedStaticPropGameRobot05)
END_MESSAGE_MAP()


// CPropertyPageGame message handlers

BOOL CPropertyPageGame::OnInitDialog()
{
	__super::OnInitDialog();


	{
		m_bDebugWheel = false;

		FILE* fp;
		fp = fopen("debug.cfg", "rt");

		if (fp != NULL)
		{
			while (!feof(fp))
			{
				char buf[256];
				fgets(buf, 256, fp);

				CString patch_type(buf);

				while (patch_type.GetLength() >= 1)
				{
					if (patch_type.GetAt(0) == ' '
						|| patch_type.GetAt(0) == '\t'
						|| patch_type.GetAt(0) == '\n'
						|| patch_type.GetAt(0) == '\r')
						patch_type.Delete(0, 1);
					else
						break;
				}

				while (1)
				{
					int n = patch_type.GetLength();

					if (n <= 0)
						break;

					if (patch_type.GetAt(n - 1) == ' '
						|| patch_type.GetAt(n - 1) == '\t'
						|| patch_type.GetAt(n - 1) == '\n'
						|| patch_type.GetAt(n - 1) == '\r')
						patch_type.Delete(n - 1, 1);
					else
						break;
				}

				if (patch_type.GetLength() <= 0)
					continue;

				if (patch_type.GetAt(0) == '/' && patch_type.GetAt(1) == '/')
				{
					// commnet
				}
				else
				{
					if (patch_type == "game:velocity")
					{
						GetDlgItem(IDC_RADIO_MOVE_TYPE1)->ShowWindow(SW_SHOW);
						GetDlgItem(IDC_RADIO_MOVE_TYPE2)->ShowWindow(SW_SHOW);
						GetDlgItem(IDC_RADIO_MOVE_TYPE3)->ShowWindow(SW_SHOW);
						GetDlgItem(IDC_RADIO_MOVE_TYPE4)->ShowWindow(SW_SHOW);
						GetDlgItem(IDC_RADIO_MOVE_TYPE5)->ShowWindow(SW_SHOW);
						GetDlgItem(IDC_VELOCITY_PARAMETER2)->ShowWindow(SW_SHOW);
					}
					if (patch_type == "game:wheel_zoom")
					{
						m_bDebugWheel = true;
						GetDlgItem(IDC_RESET_SCREEN)->ShowWindow(SW_SHOW);
					}
					if (patch_type == "game:step")
					{
						GetDlgItem(IDC_GAME_START_STEP)->ShowWindow(SW_SHOW);
					}
				}
			}

			fclose(fp);
		}
	}

	if (ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_5)
	{
		//SetDlgItemTextW(IDC_COPY_STRATEGY_GUI, _T("Import"));
		//MoveDlgItem(IDC_COPY_STRATEGY_GUI, CPoint(81, -50));
		//ChangeSizeDlgItem(IDC_COPY_STRATEGY_GUI, CPoint(-80, 0));

		ChangeSizeDlgItem(IDC_STATIC_PROP_GAME_01, CPoint(0, -30));


		ChangeSizeDlgItem(IDC_STATIC_PROP_GAME_02, CPoint(0, 35));

		MoveDlgItem(IDC_STATIC_PROP_GAME_02, CPoint(0, -35));

		MoveDlgItem(IDC_STATIC_PROP_GAME_ROBOT_01, CPoint(0, -40));
		MoveDlgItem(IDC_COMBO_ROBOT_01_NAME, CPoint(0, -40));
		MoveDlgItem(IDC_COMBO_ROBOT_01_ROLE, CPoint(0, -40));

		MoveDlgItem(IDC_STATIC_PROP_GAME_ROBOT_02, CPoint(0, -40));
		MoveDlgItem(IDC_COMBO_ROBOT_02_NAME, CPoint(0, -40));
		MoveDlgItem(IDC_COMBO_ROBOT_02_ROLE, CPoint(0, -40));

		MoveDlgItem(IDC_STATIC_PROP_GAME_ROBOT_03, CPoint(0, -40));
		MoveDlgItem(IDC_COMBO_ROBOT_03_NAME, CPoint(0, -40));
		MoveDlgItem(IDC_COMBO_ROBOT_03_ROLE, CPoint(0, -40));

		// was -350, 2
		MoveDlgItem(IDC_STATIC_PROP_GAME_ROBOT_04, CPoint(0, -40));
		MoveDlgItem(IDC_COMBO_ROBOT_04_NAME, CPoint(0, -40));
		MoveDlgItem(IDC_COMBO_ROBOT_04_ROLE, CPoint(0, -40));
		MoveDlgItem(IDC_STATIC_PROP_GAME_ROBOT_05, CPoint(0, -40));
		MoveDlgItem(IDC_COMBO_ROBOT_05_NAME, CPoint(0, -40));
		MoveDlgItem(IDC_COMBO_ROBOT_05_ROLE, CPoint(0, -40));

		GetDlgItem(IDC_STRATEGY_PARAMETER)->ShowWindow(SW_SHOW);
	}

	if (ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_AndroSot)
	{
		GetDlgItem(IDC_SLIDER_PATH_TEST1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER_PATH_TEST2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER_PATH_TEST3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER_PATH_TEST4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PATH_TEST)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_VELOCITY_PARAMETER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_VELOCITY_PARAMETER2)->ShowWindow(SW_HIDE);
	}


	CRect rect = m_pDC->GetRect();

	OnBnClickedResetScreen();

	const int robot_n = 11;
	CString role[robot_n];
	role[0] = _T("Robot-A");
	role[1] = _T("Robot-B");
	role[2] = _T("Robot-C");
	role[3] = _T("Robot-D");
	role[4] = _T("Robot-E");
	role[5] = _T("Robot-F");
	role[6] = _T("Robot-G");
	role[7] = _T("Robot-H");
	role[8] = _T("Robot-I");
	role[9] = _T("Robot-J");
	role[10] = _T("Robot-K");

	m_comboRobot01Name.ResetContent();
	m_comboRobot02Name.ResetContent();
	m_comboRobot03Name.ResetContent();
	m_comboRobot04Name.ResetContent();
	m_comboRobot05Name.ResetContent();
	m_comboRobot06Name.ResetContent();
	m_comboRobot07Name.ResetContent();
	m_comboRobot08Name.ResetContent();
	m_comboRobot09Name.ResetContent();
	m_comboRobot10Name.ResetContent();
	m_comboRobot11Name.ResetContent();

	//for( int i=0 ; i<robot_n ; i++ )

	int robotN;

	if (ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_3)
	{
		robotN = 3;
	}

	if (ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_5)
	{
		robotN = 5;
	}


	for (int i = 0; i < robotN; i++)
	{
		m_comboRobot01Name.AddString(role[i]);
		m_comboRobot02Name.AddString(role[i]);
		m_comboRobot03Name.AddString(role[i]);
		m_comboRobot04Name.AddString(role[i]);
		m_comboRobot05Name.AddString(role[i]);
		/*m_comboRobot06Name.AddString(role[i]);
		m_comboRobot07Name.AddString(role[i]);
		m_comboRobot08Name.AddString(role[i]);
		m_comboRobot09Name.AddString(role[i]);
		m_comboRobot10Name.AddString(role[i]);
		m_comboRobot11Name.AddString(role[i]);*/

		m_AutoPositionData.m_setRobotName.insert(role[i]);
	}

	if (ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_3)
	{
		m_comboRobot01Name.SetCurSel(0);
		m_comboRobot02Name.SetCurSel(1);
		m_comboRobot03Name.SetCurSel(2);
	}

	if (ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_5)
	{
		m_comboRobot01Name.SetCurSel(0);
		m_comboRobot02Name.SetCurSel(1);
		m_comboRobot03Name.SetCurSel(2);
		m_comboRobot04Name.SetCurSel(3);
		m_comboRobot05Name.SetCurSel(4);

	}

	/*
	{
		m_comboRobot01Name.SetCurSel(0);
		m_comboRobot02Name.SetCurSel(1);
		m_comboRobot03Name.SetCurSel(2);
		m_comboRobot04Name.SetCurSel(3);
		m_comboRobot05Name.SetCurSel(4);
		m_comboRobot06Name.SetCurSel(5);
		m_comboRobot07Name.SetCurSel(6);
		m_comboRobot08Name.SetCurSel(7);
		m_comboRobot09Name.SetCurSel(8);
		m_comboRobot10Name.SetCurSel(9);
		m_comboRobot11Name.SetCurSel(10);
	}
	*/

	/*
	m_sliderParametersExample.SetOption( "Parameters example", false, 0, 1.5, 0.01, 2 );
	m_sliderParametersExample.SetColor( RGB(128,128,255), RGB(0,0,0), RGB(255,0,0) );
	m_sliderParametersExample.SetValue( 0.5 );

	m_sliderParametersExample2.SetOption(
		"Parameters example2",	// 표시될 slider 이름
		false,					// dual slider 사용 여부 (true:듀얼, false:단일)
		0,						// 최소값
		0.05,					// 최대값
		0.001,					// 마우스 클릭으로 변경되는 크기
		3						// 소수점 몇자리까지 표현
		);

	m_sliderParametersExample2.SetColor( RGB(128,128,255), RGB(0,0,0), RGB(255,0,0)	); //슬라이더 색상 설정

	m_sliderParametersExample2.SetValue( 0.001 );	// 초기값
	*/

	m_sliderPathTest1.SetOption(_T("O.x"), false, 0, 3, 0.1, 1);
	m_sliderPathTest1.SetValue(1.1);
	m_sliderPathTest2.SetOption(_T("O.y"), false, 0, 2, 0.1, 1);
	m_sliderPathTest2.SetValue(0.9);
	m_sliderPathTest3.SetOption(_T("r"), false, 0, 3, 0.1, 1);
	m_sliderPathTest3.SetValue(0.3);
	m_sliderPathTest4.SetOption(_T("d"), false, 0, 2, 0.1, 1);
	m_sliderPathTest4.SetValue(0.5);



	m_pVelocityParameterDlg = new CVelocityParameterDlg;
	m_pVelocityParameterDlg->Create(IDD_VELOCITY_PARAMETER1_DIALOG, this);

	m_pVelocityParameterDlg2 = new CVelocityParameterDlg2;
	m_pVelocityParameterDlg2->Create(IDD_VELOCITY_PARAMETER2_DIALOG, this);

	m_pStrategyParameterDlg = new CStrategyParameterDlg;
	m_pStrategyParameterDlg->Create(IDD_STRATEGY_PARAMETER_DIALOG, this);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageGame::DrawDisplay(void)
{
	EnterCriticalSection(&m_critGameGUI);

	for (int i = 0; i < m_robotN; i++)
	{
		m_Robot_draw[i] = m_Robot_share[i];
	}

	LeaveCriticalSection(&m_critGameGUI);



	m_pDC->FillSolidRect(0, 0, m_pDC->Width(), m_pDC->Height(), RGB(0, 0, 0));


	CGameGUI::DrawDisplay(m_pDC, (m_bRobotMessage == TRUE), (m_bRobotMessageSelectOnly == TRUE));

	if (m_pVelocityParameterDlg2->IsShow())
	{
		m_pVelocityParameterDlg2->DisplayVelocityK();
	}

	if (m_pStrategyParameterDlg->IsShow())
	{
		DrawStrategyParameter(m_pDC);
	}

	if (m_bDragScreen)
	{
		CPen pen, * pOldPen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		pOldPen = (CPen*)m_pDC->SelectObject(&pen);

		m_pDC->SelectStockObject(NULL_BRUSH);

		if (!m_bDragMove)
			m_pDC->Rectangle(CRect(m_mouseDownPoint, m_mouseMovePoint));

		m_pDC->SelectObject(pOldPen);
	}

	if (m_bShowAutoposition)
	{
		CString strSituationName = m_strSituationName[m_radioSituation];

		if (m_radioSituation == 10)
		{
			strSituationName = m_strSituation;
		}

		DrawAutoPosition(m_pDC, strSituationName);
	}


	{
		CRect text_rect(20, 5, 220, 20);

		CString tmp;

		if (m_GameState == CPropertyPageGame::GAME_READY)
			tmp.Format(_T("Match Command : Prepare"));
		if (m_GameState == CPropertyPageGame::GAME_PLAY)
			tmp.Format(_T("Match Command : Start"));
		if (m_GameState == CPropertyPageGame::GAME_STOP)
			tmp.Format(_T("Match : Stop"));

		//pDC->SetBkMode( OPAQUE );
		m_pDC->SetBkMode(TRANSPARENT);
		m_pDC->SetTextColor(RGB(255, 255, 255));
		m_pDC->DrawText(tmp, text_rect, DT_LEFT);
	}

	//DrawGraph();
}


CObjectPositionInfo CPropertyPageGame::GetObjectInfomation()
{
	CObjectPositionInfo info;

	info.m_Ball.state = m_Ball.State();
	info.m_Ball.pos = m_Ball.PositionCurrent();
	info.m_Ball.velocity = m_Ball.VelocityCurrent();
	info.m_Ball.acceleration = m_Ball.AccelerationCurrent();

	for (int i = 0; i < m_robotN; i++)
	{
		info.m_Robot[i].state = m_Robot[i].State();
		info.m_Robot[i].pos = m_Robot[i].PositionCurrent();
		info.m_Robot[i].orientation = m_Robot[i].OrientationCurrent();
		//info.m_Robot[i].acceleration;
	}

	for (int i = 0; i < m_opponentN; i++)
	{
		info.m_Opp[i].state = m_Opponent[i].State();
		info.m_Opp[i].pos = m_Opponent[i].PositionCurrent();
		info.m_Opp[i].velocity = m_Opponent[i].VelocityCurrent();
		info.m_Opp[i].acceleration = m_Opponent[i].AccelerationCurrent();
	}

	return info;
}

void CPropertyPageGame::SetObjectInfomation(CObjectPositionInfo futureInfo, CObjectPositionInfo currentInfo, CObjectPositionInfo pastInfo, CObjectPositionInfo errorInfo)
{
	// Future
	m_Ball.SetState(futureInfo.m_Ball.state);
	m_Ball.SetPosition(futureInfo.m_Ball.pos);
	m_Ball.SetVelocity(futureInfo.m_Ball.velocity);
	m_Ball.SetAcceleration(futureInfo.m_Ball.acceleration);

	for (int id = 0; id < m_robotN; id++)
	{
		m_Robot[id].SetState(futureInfo.m_Robot[id].state);
		m_Robot[id].SetPosition(futureInfo.m_Robot[id].pos);
		m_Robot[id].SetOrientationDegree(futureInfo.m_Robot[id].orientation);
		//futureInfo.m_Robot[id].acceleration;
	}

	for (int id = 0; id < m_opponentN; id++)
	{
		m_Opponent[id].SetState(futureInfo.m_Opp[id].state);
		m_Opponent[id].SetPosition(futureInfo.m_Opp[id].pos);
		m_Opponent[id].SetVelocity(futureInfo.m_Opp[id].velocity);
		m_Opponent[id].SetAcceleration(futureInfo.m_Opp[id].acceleration);
	}

	// Current
	m_Ball.SetPositionCurrent(currentInfo.m_Ball.pos);
	m_Ball.SetVelocityCurrent(currentInfo.m_Ball.velocity);
	m_Ball.SetAccelerationCurrent(currentInfo.m_Ball.acceleration);

	for (int id = 0; id < m_robotN; id++)
	{
		m_Robot[id].SetPositionCurrent(currentInfo.m_Robot[id].pos);
		m_Robot[id].SetOrientationCurrent(currentInfo.m_Robot[id].orientation);
	}

	for (int id = 0; id < m_opponentN; id++)
	{
		m_Opponent[id].SetPositionCurrent(currentInfo.m_Opp[id].pos);
		m_Opponent[id].SetVelocityCurrent(currentInfo.m_Opp[id].velocity);
		m_Opponent[id].SetAccelerationCurrent(currentInfo.m_Opp[id].acceleration);
	}

	// Past
	m_Ball.SetPositionPast(pastInfo.m_Ball.pos);
	m_Ball.SetVelocityPast(pastInfo.m_Ball.velocity);
	m_Ball.SetAccelerationPast(pastInfo.m_Ball.acceleration);

	for (int id = 0; id < m_robotN; id++)
	{
		m_Robot[id].SetPositionPast(pastInfo.m_Robot[id].pos);
		m_Robot[id].SetOrientationPast(pastInfo.m_Robot[id].orientation);
	}

	for (int id = 0; id < m_opponentN; id++)
	{
		m_Opponent[id].SetPositionPast(pastInfo.m_Opp[id].pos);
		m_Opponent[id].SetVelocityPast(pastInfo.m_Opp[id].velocity);
		m_Opponent[id].SetAccelerationPast(pastInfo.m_Opp[id].acceleration);
	}


	// Error
	m_Ball.SetPositionError(errorInfo.m_Ball.pos);

	for (int id = 0; id < m_robotN; id++)
	{
		m_Robot[id].SetPositionError(errorInfo.m_Robot[id].pos);
		m_Robot[id].SetOrientationError(errorInfo.m_Robot[id].orientation);
	}

	for (int id = 0; id < m_opponentN; id++)
	{
		m_Opponent[id].SetPositionError(errorInfo.m_Opp[id].pos);
	}

	EnterCriticalSection(&m_critPropGameGUI);
	for (auto it = m_vecMouseInput.begin(); it != m_vecMouseInput.end(); it++)
	{
		CPoint point = it->point;
		UINT nFlags = it->nFlags;

		if (it->state == CPropertyPageGame::MOUSE_Ldown)
		{
			m_mouseDownPoint = point;

			if (m_bRButton)
			{
				// cancel
				m_bRButton = false;
				m_bLButton = false;
			}
			else
			{
				m_mouseDownPoint = point;

				if (Screen_Grasp(m_mouseDownPoint))
				{
					// 물체 클릭
					m_bDragMove = true;
					m_bDragScreen = false;
				}
				else
				{
					// 화면 클릭
					m_bDragMove = false;
					m_bDragScreen = true;
				}

				m_bLButton = true;
			}
		}
		if (it->state == CPropertyPageGame::MOUSE_Lup)
		{
			m_mouseUpPoint = point;

			if (m_bLButton)
			{
				if (m_bDragMove)
				{
					Screen_DropObject(m_mouseDownPoint, m_mouseUpPoint);
				}
				else
				{
					// 영역 선택
					Screen_SelectObject(m_mouseDownPoint, m_mouseUpPoint);
				}

				m_bLButton = false;
			}

			m_bDragScreen = false;
		}
		if (it->state == CPropertyPageGame::MOUSE_Rdown)
		{
			m_mouseDownPoint = point;

			if (m_bLButton)
			{
				// cancel
				Screen_DropObject(m_mouseDownPoint, m_mouseDownPoint);

				m_bRButton = false;
				m_bLButton = false;

				m_bDragMove = false;
				m_bDragScreen = false;
			}
			else
			{
				m_mouseDownPoint = point;

				if (Screen_Grasp(m_mouseDownPoint))
				{
					// 한녀석만 선택되고 각도 이동 준비
					m_bDragMove = true;
				}
				else
				{
					m_bDragMove = false;
				}

				m_bRButton = true;
			}
		}
		if (it->state == CPropertyPageGame::MOUSE_Rup)
		{
			m_mouseUpPoint = point;

			if (m_bRButton)
			{
				// 선택된 object 명령
				if (m_bDragMove && m_mouseUpPoint != m_mouseDownPoint)
				{
					// 선택된 로봇 각도 변경
					if (m_GameState != CPropertyPageGame::GAME_PLAY)
					{
						Screen_ControlOrientationTo(m_mouseDownPoint, m_mouseUpPoint);
					}

					m_bDragMove = false;
				}
				else
				{
					if (Screen_IsObject(m_mouseUpPoint))
					{
						Screen_DropObject(m_mouseDownPoint, m_mouseUpPoint);
					}
					else
					{
						// 선택된 물체(로봇, 공) 이동
						if (m_GameState != CPropertyPageGame::GAME_PLAY)
						{
							Screen_ControlMoveTo(m_mouseUpPoint, m_radioMoveType);
						}
					}
				}

				m_bRButton = false;
			}

			m_bDragScreen = false;
		}
		if (it->state == CPropertyPageGame::MOUSE_move)
		{
			m_mouseMovePoint = point;

			if (m_bLButton)
			{
				// 선택된 object 명령
				if (m_bDragMove)
				{
					// 선택된 물체 이동
					Screen_DragObject(m_mouseDownPoint, m_mouseMovePoint);
				}
				else
				{
					// 화면 선택 : pass
				}
			}

			if (m_bRButton)
			{
				// 선택된 object 명령
				if (m_bDragMove)
				{
					// 선택된 물체 모두 이동
					if (m_GameState != CPropertyPageGame::GAME_PLAY)
					{
						Screen_ControlOrientationTo(m_mouseDownPoint, m_mouseMovePoint, true);
					}
				}
				else
				{
					//단순 선택 -> skip
				}
			}
		}
	}

	m_vecMouseInput.clear();

	LeaveCriticalSection(&m_critPropGameGUI);

	if (m_GameState == CPropertyPageGame::GAME_STOP)
	{
		m_Ball.SetVelocity(CPointDouble(0, 0));
	}
}

CObjectVelocityInfo CPropertyPageGame::Velocity()
{
	CObjectVelocityInfo velocity;

	for (int i = 0; i < m_robotN; i++)
	{
		m_Robot[i].VelocityBackup();

		if (m_GameState == CPropertyPageGame::GAME_PLAY || m_GameState == CPropertyPageGame::GAME_READY || (m_GameState == CPropertyPageGame::GAME_STEP && m_bStepFirst))
		{
			velocity.m_VelocityRight[i] = m_Robot[i].VelocityRight();
			velocity.m_VelocityLeft[i] = m_Robot[i].VelocityLeft();

			velocity.m_LinearVelocity[i] = m_Robot[i].VelocityLinear();
			velocity.m_AngularVelocity[i] = m_Robot[i].VelocityAngularRadian();

			velocity.m_Behavior[i] = m_Robot[i].Behavior();
		}
		else
			if (m_GameState == CPropertyPageGame::GAME_STOP)
			{
				velocity.m_VelocityRight[i] = 0;
				velocity.m_VelocityLeft[i] = 0;

				velocity.m_LinearVelocity[i] = 0;
				velocity.m_AngularVelocity[i] = 0;

				velocity.m_Behavior[i] = ROBOT_BEHAVIOR_STOP;
			}

		// 			if( m_bManualMove && m_StrategyCore.m_Robot[i].IsSelect() )
		// 			{
		// 				if( m_GameState == PS_STOP || m_GameState == PS_READY )
		// 				{
		// 					if( m_LinearVelocity >= 0 )
		// 					{
		// 						velocity.m_VelocityRight[i] = m_LinearVelocity - m_AngularVelocity;
		// 						velocity.m_VelocityLeft[i]  = m_LinearVelocity + m_AngularVelocity;
		// 					}
		// 					else
		// 					{
		// 						velocity.m_VelocityRight[i] = m_LinearVelocity + m_AngularVelocity;
		// 						velocity.m_VelocityLeft[i]  = m_LinearVelocity - m_AngularVelocity;
		// 					}
		// 				}
		// 			}
	}

	m_bStepFirst = false;

	return velocity;
}

void CPropertyPageGame::OnBnClickedRobotIdAssign()
{
	UpdateData(TRUE);

	CString name[5]; // robotN

	name[0] = m_strRobot01Name;
	name[1] = m_strRobot02Name;
	name[2] = m_strRobot03Name;
	name[3] = m_strRobot04Name;
	name[4] = m_strRobot05Name;
	/*name[5] = m_strRobot06Name;
	name[6] = m_strRobot07Name;
	name[7] = m_strRobot08Name;
	name[8] = m_strRobot09Name;
	name[9] = m_strRobot10Name;
	name[10] = m_strRobot11Name;*/

	for (int i = 0; i < m_robotN; i++)
	{
		auto it = m_AutoPositionData.m_setRobotName.find(name[i]);

		if (it == m_AutoPositionData.m_setRobotName.end() && name[i] != _T(""))
		{
			m_AutoPositionData.m_setRobotName.insert(name[i]);

			m_comboRobot01Name.AddString(name[i]);
			m_comboRobot02Name.AddString(name[i]);
			m_comboRobot03Name.AddString(name[i]);
			m_comboRobot04Name.AddString(name[i]);
			m_comboRobot05Name.AddString(name[i]);
			/*m_comboRobot06Name.AddString(name[i]);
			m_comboRobot07Name.AddString(name[i]);
			m_comboRobot08Name.AddString(name[i]);
			m_comboRobot09Name.AddString(name[i]);
			m_comboRobot10Name.AddString(name[i]);
			m_comboRobot11Name.AddString(name[i]);*/
		}
	}

	SetRobotName(name);
}


void CPropertyPageGame::OnBnClickedGameReady()
{
	m_GameState = CPropertyPageGame::GAME_READY;

	//GetDlgItem(IDC_GAME_READY)->EnableWindow(FALSE);
	//GetDlgItem(IDC_GAME_START)->EnableWindow(TRUE);
	//GetDlgItem(IDC_GAME_STOP )->EnableWindow(TRUE);
}

void CPropertyPageGame::OnBnClickedGameStart()
{
	UpdateData(TRUE);

	m_timeStart = m_timeNow;

	m_GameState = CPropertyPageGame::GAME_PLAY;

	//GetDlgItem(IDC_GAME_READY)->EnableWindow(FALSE);
	//GetDlgItem(IDC_GAME_START)->EnableWindow(FALSE);
	//GetDlgItem(IDC_GAME_STOP )->EnableWindow(TRUE);
}


void CPropertyPageGame::OnBnClickedGameStop()
{
	UpdateData(TRUE);

	m_timeStart = m_timeNow;

	m_GameState = CPropertyPageGame::GAME_STOP;

	for (int i = 0; i < m_robotN; i++)
	{
		m_Robot[i].MissionReset();

		CMission mission;
		m_Robot[i].m_MissionSet.UpdateRecentMission(mission, -1);
	}

	Stop();

	//GetDlgItem(IDC_GAME_READY)->EnableWindow(TRUE);
	//GetDlgItem(IDC_GAME_START)->EnableWindow(TRUE);
	//GetDlgItem(IDC_GAME_STOP )->EnableWindow(FALSE);
}

void CPropertyPageGame::OnBnClickedGameStartStep()
{
	UpdateData(TRUE);

	m_GameState = CPropertyPageGame::GAME_STEP;

	m_bStepFirst = true;
}


//////////////////////////////////////////////////////////////////////////
// File
//////////////////////////////////////////////////////////////////////////

void CPropertyPageGame::OnBnClickedOpenAutopositionFile()
{
	UpdateData(TRUE);

	TCHAR szFilter[] = _T("Auto-position File(*.AP)|*.AP||");
	CFileDialog dlg(TRUE, _T("default"), _T("default"), NULL, szFilter);

	if (dlg.DoModal() == IDOK)
	{
		BeginWaitCursor();
		OpenAutopositionFile(dlg.GetPathName());
		EndWaitCursor();
	}

	UpdateData(FALSE);
}


void CPropertyPageGame::OnBnClickedSaveAutopositionFile()
{
	UpdateData(TRUE);

	TCHAR szFilter[] = _T("Auto-position File(*.AP)|*.AP||");
	CFileDialog dlg(FALSE, _T("default"), _T("default"), NULL, szFilter);

	if (dlg.DoModal() == IDOK)
	{
		BeginWaitCursor();
		SaveAutopositionFile(dlg.GetPathName());
		EndWaitCursor();
	}

	UpdateData(FALSE);
}

void CPropertyPageGame::OpenAutopositionFile(CString filename)
{
	m_strAutoPositionFileName = filename;
	m_AutoPositionData.OpenFile(m_strAutoPositionFileName);

	m_comboRobot01Name.ResetContent();
	m_comboRobot02Name.ResetContent();
	m_comboRobot03Name.ResetContent();
	m_comboRobot04Name.ResetContent();
	m_comboRobot05Name.ResetContent();
	m_comboRobot06Name.ResetContent();
	m_comboRobot07Name.ResetContent();
	m_comboRobot08Name.ResetContent();
	m_comboRobot09Name.ResetContent();
	m_comboRobot10Name.ResetContent();
	m_comboRobot11Name.ResetContent();

	for (auto it = m_AutoPositionData.m_setRobotName.begin(); it != m_AutoPositionData.m_setRobotName.end(); it++)
	{
		m_comboRobot01Name.AddString(*it);
		m_comboRobot02Name.AddString(*it);
		m_comboRobot03Name.AddString(*it);
		m_comboRobot04Name.AddString(*it);
		m_comboRobot05Name.AddString(*it);
		m_comboRobot06Name.AddString(*it);
		m_comboRobot07Name.AddString(*it);
		m_comboRobot08Name.AddString(*it);
		m_comboRobot09Name.AddString(*it);
		m_comboRobot10Name.AddString(*it);
		m_comboRobot11Name.AddString(*it);
	}

	{
		m_comboRobot01Name.SetCurSel(0);
		m_comboRobot02Name.SetCurSel(1);
		m_comboRobot03Name.SetCurSel(2);
		//m_comboRobot04Name.SetCurSel(3);
		//m_comboRobot05Name.SetCurSel(4);
		//m_comboRobot06Name.SetCurSel(5);
		//m_comboRobot07Name.SetCurSel(6);
		//m_comboRobot08Name.SetCurSel(7);
		//m_comboRobot09Name.SetCurSel(8);
		//m_comboRobot10Name.SetCurSel(9);
		//m_comboRobot11Name.SetCurSel(10);
	}

	m_comboSituation.ResetContent();

	for (auto it = m_AutoPositionData.m_setSituationName.begin(); it != m_AutoPositionData.m_setSituationName.end(); it++)
	{
		if ((*it).Find(_T("Default - "), 0) != 0)
			m_comboSituation.AddString(*it);
	}




	UpdateData(FALSE);
}

void CPropertyPageGame::SaveAutopositionFile(CString filename)
{
	m_strAutoPositionFileName = filename;
	m_AutoPositionData.SaveFile(m_strAutoPositionFileName);
	UpdateData(FALSE);
}


void CPropertyPageGame::OnBnClickedRadioSituation1() { OnRadioSituation(true); }
void CPropertyPageGame::OnBnClickedRadioSituation2() { OnRadioSituation(true); }
void CPropertyPageGame::OnBnClickedRadioSituation3() { OnRadioSituation(true); }
void CPropertyPageGame::OnBnClickedRadioSituation4() { OnRadioSituation(true); }
void CPropertyPageGame::OnBnClickedRadioSituation5() { OnRadioSituation(true); }
void CPropertyPageGame::OnBnClickedRadioSituation6() { OnRadioSituation(true); }
void CPropertyPageGame::OnBnClickedRadioSituation7() { OnRadioSituation(true); }
void CPropertyPageGame::OnBnClickedRadioSituation8() { OnRadioSituation(true); }
void CPropertyPageGame::OnBnClickedRadioSituation9() { OnRadioSituation(true); }
void CPropertyPageGame::OnBnClickedRadioSituation10() { OnRadioSituation(true); }
void CPropertyPageGame::OnBnClickedRadioSituation11() { OnRadioSituation(false); }

void CPropertyPageGame::OnRadioSituation(bool bBasicSituation)
{
	if (bBasicSituation)
	{
		GetDlgItem(IDC_COMBO_SITUATION)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_SITUATION)->EnableWindow(TRUE);
	}


	UpdateData(TRUE);


	CString strSituationName = m_strSituationName[m_radioSituation];

	if (m_radioSituation == 10)
	{
		strSituationName = m_strSituation;
	}

	CString situation = strSituationName;

	CSetPlayData::Team setplay_role;
	setplay_role = m_SetPlayData.GetSetplayData(situation);

	if (setplay_role.bValid == false)
		return;

	CComboBox* m_pComobRobotRole[11];

	m_pComobRobotRole[0] = &m_comobRobot01Role;
	m_pComobRobotRole[1] = &m_comobRobot02Role;
	m_pComobRobotRole[2] = &m_comobRobot03Role;
	m_pComobRobotRole[3] = &m_comobRobot04Role;
	m_pComobRobotRole[4] = &m_comobRobot05Role;
	m_pComobRobotRole[5] = &m_comobRobot06Role;
	m_pComobRobotRole[6] = &m_comobRobot07Role;
	m_pComobRobotRole[7] = &m_comobRobot08Role;
	m_pComobRobotRole[8] = &m_comobRobot09Role;
	m_pComobRobotRole[9] = &m_comobRobot10Role;
	m_pComobRobotRole[10] = &m_comobRobot11Role;

	for (int i = 0; i < (int)setplay_role.robot.size(); i++)
	{
		for (int robot_i = 0; robot_i < m_robotN; robot_i++)
		{
			if (setplay_role.robot[i].name == m_Robot[robot_i].Name())
			{
				int result = m_pComobRobotRole[robot_i]->SelectString(0, setplay_role.robot[i].strSetPlayRole);

				if (result != CB_ERR)
				{
				}
			}
		}
	}
}


void CPropertyPageGame::OnBnClickedAutoposUpdate()
{
	UpdateData(TRUE);

	CString strSituationName = m_strSituationName[m_radioSituation];

	if (m_radioSituation == 10)
	{
		strSituationName = m_strSituation;
	}

	if (UpdateAutoPosition(strSituationName))
	{
		if (m_radioSituation == 10 && m_comboSituation.FindString(0, strSituationName) == CB_ERR)
			m_comboSituation.AddString(strSituationName);
	}
}



void CPropertyPageGame::OnBnClickedAutoposAssign()
{
	UpdateData(TRUE);

	CString strSituationName = m_strSituationName[m_radioSituation];

	if (m_radioSituation == 10)
	{
		strSituationName = m_strSituation;
	}

	LoadAutoPosition(strSituationName);
}



//////////////////////////////////////////////////////////////////////////
// Mouse
//////////////////////////////////////////////////////////////////////////

MouseCapture::Enum CPropertyPageGame::DisplayLButtonDown(UINT nFlags, CPoint point)
{
	struct MouseInput data;
	data.state = CPropertyPageGame::MOUSE_Ldown;
	data.nFlags = nFlags;
	data.point = point;

	EnterCriticalSection(&m_critPropGameGUI);
	m_vecMouseInput.push_back(data);
	LeaveCriticalSection(&m_critPropGameGUI);

	return MouseCapture::SET;
}

MouseCapture::Enum CPropertyPageGame::DisplayLButtonUp(UINT nFlags, CPoint point)
{
	struct MouseInput data;
	data.state = CPropertyPageGame::MOUSE_Lup;
	data.nFlags = nFlags;
	data.point = point;

	EnterCriticalSection(&m_critPropGameGUI);
	m_vecMouseInput.push_back(data);
	LeaveCriticalSection(&m_critPropGameGUI);

	return MouseCapture::RELEASE;
}

MouseCapture::Enum CPropertyPageGame::DisplayRButtonDown(UINT nFlags, CPoint point)
{
	struct MouseInput data;
	data.state = CPropertyPageGame::MOUSE_Rdown;
	data.nFlags = nFlags;
	data.point = point;

	EnterCriticalSection(&m_critPropGameGUI);
	m_vecMouseInput.push_back(data);
	LeaveCriticalSection(&m_critPropGameGUI);

	return MouseCapture::SET;
}

MouseCapture::Enum CPropertyPageGame::DisplayRButtonUp(UINT nFlags, CPoint point)
{
	struct MouseInput data;
	data.state = CPropertyPageGame::MOUSE_Rup;
	data.nFlags = nFlags;
	data.point = point;

	EnterCriticalSection(&m_critPropGameGUI);
	m_vecMouseInput.push_back(data);
	LeaveCriticalSection(&m_critPropGameGUI);

	return MouseCapture::RELEASE;
}

MouseCapture::Enum CPropertyPageGame::DisplayMouseMove(UINT nFlags, CPoint point)
{
	struct MouseInput data;
	data.state = CPropertyPageGame::MOUSE_move;
	data.nFlags = nFlags;
	data.point = point;

	EnterCriticalSection(&m_critPropGameGUI);
	m_vecMouseInput.push_back(data);
	LeaveCriticalSection(&m_critPropGameGUI);

	if (m_bLButton || m_bRButton)
		return MouseCapture::SET;

	return MouseCapture::RELEASE;
}

MouseCapture::Enum CPropertyPageGame::DisplayMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	if (m_bDebugWheel)
	{
		CPointDouble p0(point);
		m_ground.ScreenToGround(p0);

		double zoom = m_ground.ScreenRatio();
		zoom = zoom + zDelta / 5;
		m_ground.SetScreenRatio(zoom);

		m_ground.GroundToScreen(p0);


		CPoint center = m_ground.Center();
		center = center + (point - p0.Integer());
		m_ground.SetCenter(center);
	}

	return MouseCapture::NOTHING;
}

void CPropertyPageGame::GameRun(double runningTime)
{
	m_timeNow = runningTime;


	// relase / win7 : 4~5 ms
	{
		m_VelocityParameter = m_pVelocityParameterDlg->GetParameters();

		for (int i = 0; i < 5; i++)
			m_VelocityParameter2[i] = m_pVelocityParameterDlg2->GetParameters(i);

		m_StrategyParam = m_pStrategyParameterDlg->GetParameters();
	}

	//	Initialization & Update Parameters
	{
		m_Ball.SetGround(m_ground);

		for (int i = 0; i < m_robotN; i++)
		{
			m_Robot[i].SetStrategyParameter(m_StrategyParam);
			m_Robot[i].SetVelocityParameter(m_VelocityParameter);
			for (int j = 0; j < 5; j++)
				m_Robot[i].SetVelocityParameter2(j, m_VelocityParameter2[j]);

			m_Robot[i].SetBall(m_Ball);
			m_Robot[i].ResetRobotObject();

			for (int j = 0; j < m_opponentN; j++)
			{
				if (m_Opponent[j].State())
					m_Robot[i].AddRobotObject_Opponent(m_Opponent[j].Position());
			}

			for (int j = 0; j < m_robotN; j++)
			{
				if (i != j && m_Robot[j].State())
					m_Robot[i].AddRobotObject_Home(m_Robot[j].Position());
			}
		}

		for (int i = 0; i < m_opponentN; i++)
		{
			m_Opponent[i].SetGround(m_ground);
		}
	}


	if (m_GameState == CPropertyPageGame::GAME_READY)
	{
		for (int i = 0; i < m_robotN; i++)
		{
			m_Robot[i].ExecuteMission();
		}
	}

	if (m_GameState == CPropertyPageGame::GAME_PLAY || (m_GameState == CPropertyPageGame::GAME_STEP && m_bStepFirst))
	{
		m_timeGame = m_timeNow - m_timeStart;

		for (int i = 0; i < m_robotN; i++)
		{
			m_Robot[i].SetTimeNow(m_timeNow);
			m_Robot[i].SetTimeGame(m_timeGame);
			m_Robot[i].SetGround(m_ground);
		}

		if (m_radioGameStrategyType == 0)
		{
			Run(m_checkRoleChange == TRUE);
		}
		else
			if (m_radioGameStrategyType == 1)
			{
				RunGUI();
			}

	}

	EnterCriticalSection(&m_critGameGUI);

	for (int i = 0; i < m_robotN; i++)
	{
		m_Robot_share[i] = m_Robot[i];
	}

	LeaveCriticalSection(&m_critGameGUI);


#ifdef _ROBOT_GRAPH_ENABLE

	for (int i = 0; i < ROBOT_N; i++)
	{
		if (m_Robot[i].State() == OBJECT_STATE_REAL)
			m_graphRobotVelocity[i].AddData(0, m_timeNow, 500);
		else
			m_graphRobotVelocity[i].AddData(0, m_timeNow, -500);
		//m_graphRobotVelocity[i].SetGraphLabel( 0, "Found" );

		// cm/s
		m_graphRobotVelocity[i].AddData(1, m_timeNow, m_Robot[i].VelocityLinear() * 100.0);
		//m_graphRobotVelocity[i].SetGraphLabel( 1, "Linear" );

		// degree/s
		m_graphRobotVelocity[i].AddData(2, m_timeNow, m_Robot[i].VelocityAngularDegree());
		//m_graphRobotVelocity[i].SetGraphLabel( 2, "Angular" );
	}

#endif
}

void CPropertyPageGame::OnBnClickedCheckShowRobotMessage()
{
	UpdateData(TRUE);
}


void CPropertyPageGame::OnBnClickedCheckShowRobotMessageOnly()
{
	UpdateData(TRUE);
}


void CPropertyPageGame::OnBnClickedRadioMoveType1() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedRadioMoveType2() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedRadioMoveType3() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedRadioMoveType4() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedRadioMoveType5() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedRadioMoveType6() { UpdateData(TRUE); }


void CPropertyPageGame::OnBnClickedOpenStrategyFile()
{
	UpdateData(TRUE);

	TCHAR szFilter[] = _T("RIT Lab. Soty Strategy Setting File(*.SST)|*.SST||");
	CFileDialog dlg(TRUE, _T("default"), _T("default"), NULL, szFilter);

	if (dlg.DoModal() == IDOK)
	{
		BeginWaitCursor();
		OpenFile_Parameters(dlg.GetPathName());
		EndWaitCursor();
	}

	UpdateData(FALSE);
}


void CPropertyPageGame::OnBnClickedSaveStrategyFile()
{
	UpdateData(TRUE);

	TCHAR szFilter[] = _T("RIT Lab. Soty Strategy Setting File(*.SST)|*.SST||");
	CFileDialog dlg(FALSE, _T("default"), _T("default"), NULL, szFilter);

	if (dlg.DoModal() == IDOK)
	{
		BeginWaitCursor();
		SaveFile_Parameters(dlg.GetPathName());
		EndWaitCursor();
	}

	UpdateData(FALSE);
}

void CPropertyPageGame::OpenFile_Parameters(CString filename)
{
	CFile file;

	if (file.Open(filename, CFile::modeRead) == FALSE)
	{
		AfxMessageBox(_T("파일 열기가 실패하였습니다. (CPropertyPageGame::OpenFile_Parameters)"));
		return;
	}

	CArchive ar(&file, CArchive::load);

	m_strStrategyFile = filename;

	CString version;
	ar >> version;

	UpdateData(FALSE);

	CString tmp;

	while (1)
	{
		ar >> tmp;

		if (tmp == _T("- END : Strategy -"))
			break;

		if (tmp == _T("Path Test 8"))
		{
			double data;
			ar >> data;
			m_sliderPathTest1.SetValue(data);
			ar >> data;
			m_sliderPathTest2.SetValue(data);
			ar >> data;
			m_sliderPathTest3.SetValue(data);
			ar >> data;
			m_sliderPathTest4.SetValue(data);
		}

		if (tmp == _T("Velocity Parameters (shcho)"))
		{
			CVelocityParameter vparam;
			vparam.Open(ar);
			m_pVelocityParameterDlg->SetParameters(vparam);
		}

		if (tmp == _T("Velocity Parameters (shchoi)"))
		{
			CVelocityParameter2 vparam2;
			int i;
			ar >> i;
			vparam2.Open(ar);
			m_pVelocityParameterDlg2->SetParameters(i, vparam2);
		}

		if (tmp == _T("Strategy Parameters"))
		{
			CStrategyParameter sparam;
			sparam.Open(ar);
			m_pStrategyParameterDlg->SetParameters(sparam);
		}

		if (tmp == _T("Robot Roles"))
		{
			int name[11];
			for (int i = 0; i < 11; i++)
				ar >> name[i];

			m_comboRobot01Name.SetCurSel(name[0]);
			m_comboRobot02Name.SetCurSel(name[1]);
			m_comboRobot03Name.SetCurSel(name[2]);
			m_comboRobot04Name.SetCurSel(name[3]);
			m_comboRobot05Name.SetCurSel(name[4]);
			m_comboRobot06Name.SetCurSel(name[5]);
			m_comboRobot07Name.SetCurSel(name[6]);
			m_comboRobot08Name.SetCurSel(name[7]);
			m_comboRobot09Name.SetCurSel(name[8]);
			m_comboRobot10Name.SetCurSel(name[9]);
			m_comboRobot11Name.SetCurSel(name[10]);
		}
	}

	ar.Close();
	file.Close();

	Invalidate(FALSE);
	UpdateData(TRUE);
}

void CPropertyPageGame::SaveFile_Parameters(CString filename)
{
	m_strStrategyFile = filename;

	CFile file;

	file.Open(filename, CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);

	ar << CString("Version");

	ar << CString("Path Test 8");
	ar << m_sliderPathTest1.GetValue();
	ar << m_sliderPathTest2.GetValue();
	ar << m_sliderPathTest3.GetValue();
	ar << m_sliderPathTest4.GetValue();

	ar << CString("Velocity Parameters (shcho)");
	m_VelocityParameter.Save(ar);

	CVelocityParameter2 vparam2;
	for (int i = 0; i < 5; i++)
	{
		ar << CString("Velocity Parameters (shchoi)");
		ar << i;
		m_VelocityParameter2[i].Save(ar);
	}

	ar << CString("Strategy Parameters");
	m_StrategyParam.Save(ar);

	ar << CString("Robot Roles");
	ar << m_comboRobot01Name.GetCurSel();
	ar << m_comboRobot02Name.GetCurSel();
	ar << m_comboRobot03Name.GetCurSel();
	ar << m_comboRobot04Name.GetCurSel();
	ar << m_comboRobot05Name.GetCurSel();
	ar << m_comboRobot06Name.GetCurSel();
	ar << m_comboRobot07Name.GetCurSel();
	ar << m_comboRobot08Name.GetCurSel();
	ar << m_comboRobot09Name.GetCurSel();
	ar << m_comboRobot10Name.GetCurSel();
	ar << m_comboRobot11Name.GetCurSel();

	ar << CString("- END : Strategy -");

	ar.Close();
	file.Close();

	UpdateData(FALSE);
}

void CPropertyPageGame::OnBnClickedVelocityParameter()
{
	if (!m_pVelocityParameterDlg->IsShow())
	{
		m_pVelocityParameterDlg->ShowWindow(SW_SHOW);
		m_pVelocityParameterDlg->Show();
	}
	else
	{
		m_pVelocityParameterDlg->ShowWindow(SW_HIDE);
		m_pVelocityParameterDlg->Hide();
	}
}


void CPropertyPageGame::OnBnClickedVelocityParameter2()
{
	if (!m_pVelocityParameterDlg2->IsShow())
	{
		m_pVelocityParameterDlg2->ShowWindow(SW_SHOW);
		m_pVelocityParameterDlg2->Show();
	}
	else
	{
		m_pVelocityParameterDlg2->ShowWindow(SW_HIDE);
		m_pVelocityParameterDlg2->Hide();
	}
}


void CPropertyPageGame::OnBnClickedStrategyParameter()
{
	if (!m_pStrategyParameterDlg->IsShow())
	{
		m_pStrategyParameterDlg->ShowWindow(SW_SHOW);
		m_pStrategyParameterDlg->Show();
	}
	else
	{
		m_pStrategyParameterDlg->ShowWindow(SW_HIDE);
		m_pStrategyParameterDlg->Hide();
	}
}


void CPropertyPageGame::OnBnClickedPathTest()
{
	double Ox = m_sliderPathTest1.GetValue();
	double Oy = m_sliderPathTest2.GetValue();
	double r = m_sliderPathTest3.GetValue();
	double d = m_sliderPathTest4.GetValue();

	//SetDataPath( Ox, Oy, r, d );	

	for (int id = 0; id < m_robotN; id++)
		if (m_Robot[id].IsExist())
			if (m_Robot[id].IsSelect())
			{
				/*
				CMission mission;
				mission.pos = m_Robot[id].Position();
				mission.type = CMission::TEST_PATH8;
				mission.text = _T("Data Path");

				mission.parameter[0] = Ox;
				mission.parameter[1] = Oy;
				mission.parameter[2] = r;
				mission.parameter[3] = d;

				m_Robot[id].MissionAdd( mission );
				m_Robot[id].UpdatePath();
				*/
			}

}


void CPropertyPageGame::OnBnClickedKickTest()
{
	/*
	for( int id=0 ; id<m_robotN ; id++ )
			if( m_Robot[id].IsExist() )
			if( m_Robot[id].IsSelect() )
			{
				CPointDouble target(m_ground.Width() - 0.10, m_ground.Height()/2.0);

				m_Robot[id].MissionReset();


				CBall hit_ball = m_ball;

				//double robot_velocity = m_Robot[id].m_StrategyParameter.m_AverageVelocity;//1.5;//1.15;
				//double ball_k = BALL_GROUND_K;
				//for( int j=0 ; j<5 ; j++ )
				//{
				//	double t = ( hit_ball.Position() - m_Robot[id].GetPosition() ).Distance() / robot_velocity;
				//
				//	hit_ball = m_ball;
				//	hit_ball.SimulationMove( t );
				//}

				double angle_factor = (target-hit_ball.Position()).AngleDegree() - (m_Robot[id].GetPosition() - hit_ball.GetPosition()).AngleDegree();


				//while( angle_factor >  180 ) angle_factor -= 360;
				//while( angle_factor < -180 ) angle_factor += 360;
				//
				//{
				//	double t = ( (hit_ball.Position() - m_Robot[id].GetPosition()).Distance() + (180-fabs(angle_factor))/120) / robot_velocity;
				//
				//	hit_ball = m_ball;
				//	hit_ball.SimulationMove( t );
				//}


				CMission mission;
				mission.pos = target; // CHECK200706
				mission.AddPointControl( m_Robot[id].Position() );
				mission.AddPointControl( hit_ball.Position() );
				mission.AddPointControl( target );
				mission.angle = 0;

				mission.type = CMission::TYPE_KICK;
				mission.text = _T("Kick Test!");

				mission.bUpdate = true;

				mission.parameter[0] = 0;

				m_Robot[id].MissionAdd( mission );
				m_Robot[id].UpdatePath();
			}
	*/
}


void CPropertyPageGame::OnDestroy()
{
	delete m_pVelocityParameterDlg;
	delete m_pVelocityParameterDlg2;
	delete m_pStrategyParameterDlg;

	__super::OnDestroy();
}


void CPropertyPageGame::OnBnClickedResetScreen()
{
	CRect rect = m_pDC->GetRect();
	//SetGroundType( CGround::_5vs5, rect, 180 );

	if (ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_3vs3)
		m_ground.SetCenter(CPoint(320, 240));

	if (ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_5vs5)
		m_ground.SetCenter(CPoint(320, 210));

	if (ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_AndroSot)
		m_ground.SetCenter(CPoint(320, 210));
}


void CPropertyPageGame::OnBnClickedCheckRobot01() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedCheckRobot02() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedCheckRobot03() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedCheckRobot04() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedCheckRobot05() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedCheckRobot06() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedCheckRobot07() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedCheckRobot08() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedCheckRobot09() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedCheckRobot10() { UpdateData(TRUE); }
void CPropertyPageGame::OnBnClickedCheckRobot11() { UpdateData(TRUE); }


void CPropertyPageGame::OnBnClickedCheckRoleChange()
{
	UpdateData(TRUE);
}


void CPropertyPageGame::OnBnClickedLoadSetPlay()
{
	OnBnClickedGameStop();

	UpdateData(TRUE);

	CString role[11]; // robotN

	role[0] = m_strRobot01Role;
	role[1] = m_strRobot02Role;
	role[2] = m_strRobot03Role;
	role[3] = m_strRobot04Role;
	role[4] = m_strRobot05Role;
	role[5] = m_strRobot06Role;
	role[6] = m_strRobot07Role;
	role[7] = m_strRobot08Role;
	role[8] = m_strRobot09Role;
	role[9] = m_strRobot10Role;
	role[10] = m_strRobot11Role;


	SetRobotRole(role);





	CString strSituationName = m_strSituationName[m_radioSituation];

	if (m_radioSituation == 10)
	{
		strSituationName = m_strSituation;
	}

	{
		CSetPlayData::Team setplay_data;

		setplay_data.bValid = true;
		setplay_data.situation = strSituationName;

		for (int robot_i = 0; robot_i < m_robotN; robot_i++)
		{
			if (m_Robot[robot_i].Name() != _T(""))
			{
				CSetPlayData::Robot robot;
				robot.name = m_Robot[robot_i].Name();
				robot.strSetPlayRole = m_Robot[robot_i].Role();

				setplay_data.robot.push_back(robot);
			}
		}

		if (m_SetPlayData.UpdateSetplayData(setplay_data))
		{
			if (m_radioSituation == 10 && m_comboSituation.FindString(0, strSituationName) == CB_ERR)
			{
				m_comboSituation.AddString(strSituationName);
			}
		}
	}


	UpdateMission_GUI(true);
}


void CPropertyPageGame::OnBnClickedOpenStrategy()
{
	UpdateData(TRUE);

	BeginWaitCursor();

	TCHAR szFilter[] = _T("Strategy File(*.S)|*.S|All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("default"), _T("default"), NULL, szFilter);

	if (dlg.DoModal() == IDOK)
	{
		RestoreWaitCursor();
		OpenStrategyFile(dlg.GetPathName());
	}

	EndWaitCursor();
}

void CPropertyPageGame::UpdateSetPlayRole()
{
	m_comobRobot01Role.ResetContent();
	m_comobRobot02Role.ResetContent();
	m_comobRobot03Role.ResetContent();
	m_comobRobot04Role.ResetContent();
	m_comobRobot05Role.ResetContent();
	m_comobRobot06Role.ResetContent();
	m_comobRobot07Role.ResetContent();
	m_comobRobot08Role.ResetContent();
	m_comobRobot09Role.ResetContent();
	m_comobRobot10Role.ResetContent();
	m_comobRobot11Role.ResetContent();


	m_comobRobot01Role.AddString(_T("(none)"));
	m_comobRobot02Role.AddString(_T("(none)"));
	m_comobRobot03Role.AddString(_T("(none)"));
	m_comobRobot04Role.AddString(_T("(none)"));
	m_comobRobot05Role.AddString(_T("(none)"));
	m_comobRobot06Role.AddString(_T("(none)"));
	m_comobRobot07Role.AddString(_T("(none)"));
	m_comobRobot08Role.AddString(_T("(none)"));
	m_comobRobot09Role.AddString(_T("(none)"));
	m_comobRobot10Role.AddString(_T("(none)"));
	m_comobRobot11Role.AddString(_T("(none)"));

	int role_n = m_strategyGUI.GetRoleN();
	for (int i = 0; i < role_n; i++)
	{
		CStrategyGUI::Role role = m_strategyGUI.GetRole(i);
		m_comobRobot01Role.AddString(role.name);
		m_comobRobot02Role.AddString(role.name);
		m_comobRobot03Role.AddString(role.name);
		m_comobRobot04Role.AddString(role.name);
		m_comobRobot05Role.AddString(role.name);
		m_comobRobot06Role.AddString(role.name);
		m_comobRobot07Role.AddString(role.name);
		m_comobRobot08Role.AddString(role.name);
		m_comobRobot09Role.AddString(role.name);
		m_comobRobot10Role.AddString(role.name);
		m_comobRobot11Role.AddString(role.name);
	}

	m_comobRobot01Role.SetCurSel(0);
	m_comobRobot02Role.SetCurSel(0);
	m_comobRobot03Role.SetCurSel(0);
	m_comobRobot04Role.SetCurSel(0);
	m_comobRobot05Role.SetCurSel(0);
	m_comobRobot06Role.SetCurSel(0);
	m_comobRobot07Role.SetCurSel(0);
	m_comobRobot08Role.SetCurSel(0);
	m_comobRobot09Role.SetCurSel(0);
	m_comobRobot10Role.SetCurSel(0);
	m_comobRobot11Role.SetCurSel(0);


	for (int i = 0; i < m_robotN; i++)
	{
		CStrategyGUI::Role role;

		m_Robot[i].SetRole(role);
	}


	Invalidate(FALSE);
}

void CPropertyPageGame::OpenStrategyFile(CString filename)
{
	CFile file;

	m_strStrategyFileName = filename;

	if (file.Open(m_strStrategyFileName, CFile::modeRead) == FALSE)
	{
		AfxMessageBox(_T("파일 열기가 실패하였습니다. (CPropertyPageStrategyGUI::OpenFile)"));
	}
	else
	{
		CArchive ar(&file, CArchive::load);

		m_strategyGUI.OpenFile(ar);


		ar.Close();
		file.Close();

		UpdateData(FALSE);

		UpdateSetPlayRole();
	}
}


//void CPropertyPageGame::OnBnClickedCheckStrategyGui()
//{
//	UpdateData(TRUE);
//}


//void CPropertyPageGame::OnBnClickedRadioSituationAttack3()
//{
//	// TODO: Add your control notification handler code here
//}


void CPropertyPageGame::OnBnClickedRadioGameStrategyType01()
{
	UpdateData(TRUE);
}


void CPropertyPageGame::OnBnClickedRadioGameStrategyType02()
{
	UpdateData(TRUE);
}


void CPropertyPageGame::OnBnClickedCopyStrategyGui()
{
	m_bCopyStrategyGUI = true;
}



void CPropertyPageGame::OnBnClickedCheckShowAutoposition()
{
	UpdateData(TRUE);
}



void CPropertyPageGame::OnSelchangeComboSituation()
{
	int select_i = m_comboSituation.GetCurSel();

	m_comboSituation.GetLBText(select_i, m_strSituation);
}



void CPropertyPageGame::OnCbnSelchangeComboRobot04Name()
{
	// TODO: Add your control notification handler code here
}


void CPropertyPageGame::OnStnClickedStaticPropGameRobot04()
{
	// TODO: Add your control notification handler code here
}


void CPropertyPageGame::OnStnClickedStaticPropGameRobot05()
{
	// TODO: Add your control notification handler code here
}
