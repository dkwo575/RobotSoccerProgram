// PropertyPageStrategyGUI.cpp : implementation file
//

#include "stdafx.h"
#include "RobotSoccerProgram.h"
#include "PropertyPageStrategyGUI.h"
#include "afxdialogex.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

// CPropertyPageStrategyGUI dialog

IMPLEMENT_DYNAMIC(CPropertyPageStrategyGUI, CPropertyPageRobotSoccer)

CPropertyPageStrategyGUI::CPropertyPageStrategyGUI()
	: CPropertyPageRobotSoccer(CPropertyPageStrategyGUI::IDD)
	, m_bBallHome(FALSE)
	, m_bBallOpp(FALSE)
	, m_bBallFree(FALSE)
	, m_bShowAllSituation(FALSE)
	, m_bShowVerifySituation(FALSE)
{
	m_strFileName = _T("");

	m_bLButton = false;
	m_bRButton = false;

	m_bDragMove = false;

	m_bEditLabelMode = false;

	m_focusedSituationID = -1;
	m_focusedSituationRoleID = -1;
	m_focusedRoleID = -1;
	m_focusedBehaviorID = -1;

	m_focusedList = StrategyGUI_List::None;

	InitializeCriticalSection(&m_critPropertyPageStrategyGUI);


	m_posBallClink_screen = CPoint(320,240);
	//  m_strRoleAssign = _T("");

	m_bShowVerifySituation = FALSE;

	m_posRobotGUI = CPointDouble( 1.5/2, 1.3/2 );
	m_orientationRobotGUI = 0;
}

CPropertyPageStrategyGUI::~CPropertyPageStrategyGUI()
{
	DeleteCriticalSection(&m_critPropertyPageStrategyGUI);
}

void CPropertyPageStrategyGUI::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageRobotSoccer::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROLE_ASSIGN, m_comboRoleAssign);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
	DDX_Check(pDX, IDC_CHECK_BALL_SITUATION1, m_bBallHome);
	DDX_Check(pDX, IDC_CHECK_BALL_SITUATION2, m_bBallOpp);
	DDX_Check(pDX, IDC_CHECK_BALL_SITUATION3, m_bBallFree);
	DDX_Check(pDX, IDC_CHECK_SHOW_ALL_SITUATION, m_bShowAllSituation);
	DDX_Control(pDX, IDC_LIST_SITUATION_ROLE_ASSIGN, m_listSituationRoleAssign);
	DDX_Control(pDX, IDC_LIST_SITUATION, m_listSituation);
	DDX_Control(pDX, IDC_LIST_ROLE, m_listRole);
	DDX_Control(pDX, IDC_LIST_ROLE_DEFINITION, m_listRoleDefinition);
	DDX_Control(pDX, IDC_COMBO_BEHAVIOR, m_comboBehavior);
	//  DDX_Check(pDX, IDC_CHECK_BEHAVIOR_BALL, m_bBehaviorDestinationBall);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_BALL_OWNER_DISTANCE, m_sliderBallOwnerDistance);
	//  DDX_CBString(pDX, IDC_COMBO_ROLE_ASSIGN, m_strRoleAssign);
	DDX_Control(pDX, IDC_COMBO_ROLE_ASSIGN2, m_comboRoleAssign_Hold);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER_SITUATION_TIME, m_sliderSituationTime);
	DDX_Check(pDX, IDC_CHECK_SHOW_VERIFY_SITUATION, m_bShowVerifySituation);
	DDX_Control(pDX, IDC_COMBO_SITUATION_PRIORITY, m_comboSituationPriority);
	DDX_Control(pDX, IDC_COMBO_BEHAVIOR_CONTROL_TYPE, m_comboBehaviorControlType);
}


BEGIN_MESSAGE_MAP(CPropertyPageStrategyGUI, CPropertyPageRobotSoccer)
	ON_BN_CLICKED(IDC_ASSIGN_ROLE_TO_SITUATION, &CPropertyPageStrategyGUI::OnBnClickedAssignRoleToSituation)
	//ON_BN_CLICKED(IDC_OPEN_TUTORIAL_GUI, &CPropertyPageStrategyGUI::OnBnClickedTutorialGui)
	ON_BN_CLICKED(IDC_OPEN_STRATEGY_GUI, &CPropertyPageStrategyGUI::OnBnClickedOpenStrategyGui)
	ON_BN_CLICKED(IDC_SAVE_STRATEGY_GUI, &CPropertyPageStrategyGUI::OnBnClickedSaveStrategyGui)
	ON_CBN_SELCHANGE(IDC_COMBO_ROLE_ASSIGN, &CPropertyPageStrategyGUI::OnSelchangeComboRoleAssign)
	ON_BN_CLICKED(IDC_CHECK_BALL_SITUATION1, &CPropertyPageStrategyGUI::OnBnClickedCheckBallSituation1)
	ON_BN_CLICKED(IDC_CHECK_BALL_SITUATION2, &CPropertyPageStrategyGUI::OnBnClickedCheckBallSituation2)
	ON_BN_CLICKED(IDC_CHECK_BALL_SITUATION3, &CPropertyPageStrategyGUI::OnBnClickedCheckBallSituation3)
	ON_BN_CLICKED(IDC_CHECK_SHOW_ALL_SITUATION, &CPropertyPageStrategyGUI::OnBnClickedCheckShowAllSituation)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SITUATION_ROLE_ASSIGN, &CPropertyPageStrategyGUI::OnItemchangedListSituationRole)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SITUATION, &CPropertyPageStrategyGUI::OnItemchangedListSituation)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ROLE, &CPropertyPageStrategyGUI::OnItemchangedListRole)
	ON_BN_CLICKED(IDC_ADD_BEHAVIOR, &CPropertyPageStrategyGUI::OnBnClickedAddBehavior)
	ON_BN_CLICKED(IDC_DELETE_BEHAVIOR, &CPropertyPageStrategyGUI::OnBnClickedDeleteBehavior)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ROLE_DEFINITION, &CPropertyPageStrategyGUI::OnItemchangedListRoleDefinition)
	ON_BN_CLICKED(IDC_ADD_ROLE, &CPropertyPageStrategyGUI::OnBnClickedAddRole)
	ON_BN_CLICKED(IDC_DELETE_ROLE, &CPropertyPageStrategyGUI::OnBnClickedDeleteRole)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_ROLE, &CPropertyPageStrategyGUI::OnEndlabeleditListRole)
	ON_BN_CLICKED(IDC_ADD_SITUATION, &CPropertyPageStrategyGUI::OnBnClickedAddSituation)
	ON_BN_CLICKED(IDC_DELETE_SITUATION, &CPropertyPageStrategyGUI::OnBnClickedDeleteSituation)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_SITUATION, &CPropertyPageStrategyGUI::OnEndlabeleditListSituation)
	ON_BN_CLICKED(IDC_LIST_SITUATION_PRIORITY_UP, &CPropertyPageStrategyGUI::OnBnClickedListSituationPriorityUp)
	ON_BN_CLICKED(IDC_LIST_SITUATION_PRIORITY_DOWN, &CPropertyPageStrategyGUI::OnBnClickedListSituationPriorityDown)
	ON_BN_CLICKED(IDC_LIST_BEHAVIOR_ORDER_UP, &CPropertyPageStrategyGUI::OnBnClickedListBehaviorOrderUp)
	ON_BN_CLICKED(IDC_LIST_BEHAVIOR_ORDER_DOWN, &CPropertyPageStrategyGUI::OnBnClickedListBehaviorOrderDown)
	ON_BN_CLICKED(IDC_COPY_SITUATION, &CPropertyPageStrategyGUI::OnBnClickedCopySituation)
	ON_BN_CLICKED(IDC_COPY_ROLE, &CPropertyPageStrategyGUI::OnBnClickedCopyRole)
	ON_BN_CLICKED(IDC_LIST_ROLE_ORDER_UP, &CPropertyPageStrategyGUI::OnBnClickedListRoleOrderUp)
	ON_BN_CLICKED(IDC_LIST_ROLE_ORDER_DOWN, &CPropertyPageStrategyGUI::OnBnClickedListRoleOrderDown)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_SITUATION, &CPropertyPageStrategyGUI::OnSetfocusListSituation)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_SITUATION_ROLE_ASSIGN, &CPropertyPageStrategyGUI::OnSetfocusListSituationRoleAssign)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_ROLE, &CPropertyPageStrategyGUI::OnSetfocusListRole)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_ROLE_DEFINITION, &CPropertyPageStrategyGUI::OnSetfocusListRoleDefinition)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_ROLE_DEFINITION, &CPropertyPageStrategyGUI::OnEndlabeleditListRoleDefinition)
	ON_BN_CLICKED(IDC_LIST_SITUATION_ROLE_ASSIGN_ORDER_UP, &CPropertyPageStrategyGUI::OnBnClickedListSituationRoleAssignOrderUp)
	ON_BN_CLICKED(IDC_LIST_SITUATION_ROLE_ASSIGN_ORDER_DOWN, &CPropertyPageStrategyGUI::OnBnClickedListSituationRoleAssignOrderDown)
	ON_CBN_SELCHANGE(IDC_COMBO_ROLE_ASSIGN2, &CPropertyPageStrategyGUI::OnSelchangeComboRoleAssign2)
	ON_BN_CLICKED(IDC_CHECK_SHOW_VERIFY_SITUATION, &CPropertyPageStrategyGUI::OnBnClickedCheckShowVerifySituation)
	ON_CBN_SELCHANGE(IDC_COMBO_SITUATION_PRIORITY, &CPropertyPageStrategyGUI::OnSelchangeComboSituationPriority)
	ON_CBN_SELCHANGE(IDC_COMBO_BEHAVIOR_CONTROL_TYPE, &CPropertyPageStrategyGUI::OnSelchangeComboBehaviorControlType)
	ON_BN_CLICKED(IDC_COPY_BEHAVIOR, &CPropertyPageStrategyGUI::OnBnClickedCopyBehavior)
	ON_BN_CLICKED(IDC_PASTE_BEHAVIOR, &CPropertyPageStrategyGUI::OnBnClickedPasteBehavior)
END_MESSAGE_MAP()
// CPropertyPageStrategyGUI message handlers



BOOL CPropertyPageStrategyGUI::OnInitDialog()
{
	__super::OnInitDialog();

	if( ROBOT_SOCCER_RROGRAM_ROBOT_N == ROBOT_SOCCER_RROGRAM_ROBOT_5 )
	{
		int shift_y = 31;
		MoveDlgItem( IDC_LIST_ROLE, CPoint(0,shift_y) );
		ChangeSizeDlgItem( IDC_LIST_ROLE, CPoint(0,-shift_y) );

		MoveDlgItem( IDC_LIST_ROLE_DEFINITION, CPoint(0,shift_y) );
		ChangeSizeDlgItem( IDC_LIST_ROLE_DEFINITION, CPoint(0,-shift_y) );

		MoveDlgItem( IDC_ASSIGN_ROLE_TO_SITUATION, CPoint(0,shift_y) );
		MoveDlgItem( IDC_COMBO_ROLE_ASSIGN2, CPoint(0,shift_y) );
		MoveDlgItem( IDC_COMBO_ROLE_ASSIGN, CPoint(0,shift_y) );
		MoveDlgItem( IDC_LIST_SITUATION_ROLE_ASSIGN_ORDER_UP, CPoint(0,shift_y) );
		MoveDlgItem( IDC_LIST_SITUATION_ROLE_ASSIGN_ORDER_DOWN, CPoint(0,shift_y) );

		ChangeSizeDlgItem( IDC_LIST_SITUATION_ROLE_ASSIGN, CPoint(0,shift_y) );
	}

	if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_5vs5 )
	{
		m_ground.SetGround( CGround::_5vs5, m_pDC->GetRect(), 180 );
		m_ground.SetCenter( CPoint(320, 210) );
	}

	if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_AndroSot )
	{
		m_ground.SetGround( CGround::_AndroSot, m_pDC->GetRect(), 180 );
		m_ground.SetCenter( CPoint(320, 210) );
	}

	if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_3vs3 )
	{
		m_ground.SetGround( CGround::_3vs3, m_pDC->GetRect(), 240 );
		m_ground.SetCenter( CPoint(320, 240) );
	}

	m_sliderBallOwnerDistance.SetOption( _T("ball owner dist (m)"), false, 0, 2, 0.01, 2 );
	m_sliderBallOwnerDistance.SetValue( 0.3 );

	m_sliderSituationTime.SetOption( _T("time(s)"), true, 0, MAX_SITUATION_TIME, 1, 0 );
	m_sliderSituationTime.SetValue( 0, 600 );

	for( unsigned int i=0 ; i<m_strategyGUI.m_vecSituationPriority.size() ; i++ )
		m_comboSituationPriority.AddString( m_strategyGUI.TypeToName( m_strategyGUI.m_vecSituationPriority[i] ) );

	for( unsigned int i=0 ; i<m_strategyGUI.m_vecRoleAssignMethod.size() ; i++ )
		m_comboRoleAssign.AddString( m_strategyGUI.TypeToName( m_strategyGUI.m_vecRoleAssignMethod[i] ) );

	for( unsigned int i=0 ; i<m_strategyGUI.m_vecRoleAssignOption_Hold.size() ; i++ )
		m_comboRoleAssign_Hold.AddString( m_strategyGUI.TypeToName( m_strategyGUI.m_vecRoleAssignOption_Hold[i] ) );

	m_comboRoleAssign_Hold.SetCurSel( 0 );

	for( unsigned int i=0 ; i<m_strategyGUI.m_vecBehaviorType.size() ; i++ )
		m_comboBehavior.AddString( m_strategyGUI.TypeToName( m_strategyGUI.m_vecBehaviorType[i] ) );

	m_comboBehavior.SetCurSel( 0 );

	for( unsigned int i=0 ; i<m_strategyGUI.m_vecBehaviorControlType.size() ; i++ )
		m_comboBehaviorControlType.AddString( m_strategyGUI.TypeToName( m_strategyGUI.m_vecBehaviorControlType[i] ) );

	m_comboBehaviorControlType.SetCurSel( 0 );
	
	{
		m_ImageListSituation.Create(IDB_BITMAP_LIST_SITUATION, 16, 1, RGB(0, 128, 128));
		m_listSituation.SetImageList(&m_ImageListSituation, LVSIL_SMALL);

		CRect rect;
		CHeaderCtrl* pHdr = m_listSituation.GetHeaderCtrl();
		pHdr->GetWindowRect(rect);

		/*
		LV_COLUMN lvcolumn;
		lvcolumn.mask = LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.cx = rect.Width();
		lvcolumn.pszText = _T("»óÈ²");
		*/
		//m_listSituation.InsertColumn( 0, &lvcolumn );

		
		m_listSituation.InsertColumn( 0, _T("Situation"), LVCFMT_LEFT, rect.Width() - 40 - 85, -1 );
		m_listSituation.InsertColumn( 1, _T("Select"), LVCFMT_LEFT, 40, -1 );
		m_listSituation.InsertColumn( 2, _T("Applied Time"), LVCFMT_LEFT, 85, -1 );
		ListView_SetExtendedListViewStyle(m_listSituation.m_hWnd,  
										  //LVS_EX_CHECKBOXES |
										  LVS_EX_GRIDLINES |  
										  LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	}

	{
		m_ImageListRole.Create( IDB_BITMAP_LIST_ROLE, 16, 1, RGB(0,128,128) );
		m_listRole.SetImageList(&m_ImageListRole, LVSIL_SMALL);

		CRect rect;
		CHeaderCtrl* pHdr = m_listRole.GetHeaderCtrl();
		pHdr->GetWindowRect(rect);

		m_listRole.InsertColumn( 0, _T("Role"), LVCFMT_LEFT, rect.Width(), -1 );
		ListView_SetExtendedListViewStyle(m_listRole.m_hWnd,  
										  //LVS_EX_CHECKBOXES |
										  LVS_EX_GRIDLINES |  
										  LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);

	}
	{
		m_ImageListBehavior.Create( IDB_BITMAP_LIST_BEHAVIOR, 16, 1, RGB(0,128,128) );
		m_listRoleDefinition.SetImageList(&m_ImageListBehavior, LVSIL_SMALL);

		CRect rect;
		CHeaderCtrl* pHdr = m_listRoleDefinition.GetHeaderCtrl();
		pHdr->GetWindowRect(rect);

		m_listRoleDefinition.InsertColumn( 0, _T("∞/↓"), LVCFMT_LEFT, 35, -1 );
		m_listRoleDefinition.InsertColumn( 1, _T("Action"), LVCFMT_LEFT, rect.Width()-35, -1 );
		ListView_SetExtendedListViewStyle(m_listRoleDefinition.m_hWnd,  
										  //LVS_EX_CHECKBOXES |
										  LVS_EX_GRIDLINES |  
										  LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	}
	{
		m_ImageListSituationRoleAssign.Create(IDB_BITMAP_LIST_ROLE_ASSIGN, 16, 1, RGB(0, 128, 128));
		m_listSituationRoleAssign.SetImageList(&m_ImageListSituationRoleAssign, LVSIL_SMALL);

		// XP error ¹æÁö : ¿øÀÎ ºÒ¸í
		CRect rect(693, 283, 962, 307);

		/*
		m_listSituationRoleAssign.InsertColumn( 0, _T("¿ªÇÒ"), LVCFMT_LEFT, 50, -1 );
		m_listSituationRoleAssign.DeleteColumn( 0 );
		
		CRect rect;
		CHeaderCtrl* pHdr = m_listSituationRoleAssign.GetHeaderCtrl();
		pHdr->GetWindowRect(rect);
		*/

		m_listSituationRoleAssign.InsertColumn( 0, _T("Role"), LVCFMT_LEFT, rect.Width()/3, -1 );
		m_listSituationRoleAssign.InsertColumn( 1, _T("Maintain Role"), LVCFMT_LEFT, rect.Width()/3-10, -1 );
		m_listSituationRoleAssign.InsertColumn( 2, _T("Robot selection method"), LVCFMT_LEFT, rect.Width() - rect.Width()/3 - rect.Width()/3 + 10, -1 );
		ListView_SetExtendedListViewStyle(m_listSituationRoleAssign.m_hWnd,  
										  //LVS_EX_CHECKBOXES |
										  LVS_EX_GRIDLINES |  
										  LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	}
	CClientDC dc(this);
	{
		m_dcFitness.UpdateRect( CRect(0,0,m_pDC->Width(),m_pDC->Height()));
		m_dcFitness.Init( &dc );	
		m_dcFitness_share.UpdateRect( CRect(0,0,m_pDC->Width(),m_pDC->Height()));
		m_dcFitness_share.Init( &dc );	
	}

	UpdateListRole();
	UpdateListSituation();

	m_strategyGUI.VerifyStrategy();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageStrategyGUI::GenerateDrawInformation()
{
	CString method;
	CPointDouble target_pos;
	CStrategyGUI::Situation situation;

	EnterCriticalSection(&m_critPropertyPageStrategyGUI);
	if( m_focusedSituationID >= 0 && m_focusedSituationRoleID >= 0 )
	{
		situation = m_strategyGUI.GetSituation( m_focusedSituationID );

		method = situation.role_assign.role[m_focusedSituationRoleID].assign.method;
		target_pos = situation.role_assign.role[m_focusedSituationRoleID].assign.pos;
	}

	if( m_focusedSituationID >= 0 )
	{
		situation = m_strategyGUI.GetSituation( m_focusedSituationID );

		if( situation.condition.ball.owner_distance != m_sliderBallOwnerDistance.GetValue() )
		{
			situation.condition.ball.owner_distance = m_sliderBallOwnerDistance.GetValue();
			m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );
		}

		if( situation.time.begin_sec != m_sliderSituationTime.GetValueLeft()
		 || situation.time.end_sec != m_sliderSituationTime.GetValueRight() )
		{
			situation.time.begin_sec = (int)m_sliderSituationTime.GetValueLeft();
			situation.time.end_sec   = (int)m_sliderSituationTime.GetValueRight();
			m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );

			CString tmp;
			tmp.Format(_T("%d:%02d~%d:%02d")
				, situation.time.begin_sec/60, situation.time.begin_sec%60
				, situation.time.end_sec/60, situation.time.end_sec%60 );
			
			m_listSituation.SetItemText(m_focusedSituationID, 2, tmp );

 		}		
	}

	LeaveCriticalSection(&m_critPropertyPageStrategyGUI);

	m_dcFitness.Clear( RGB(0,0,0) );
	m_ground.Draw( &m_dcFitness, RGB(255,255,255), true, false );

	if( method == StrategyGUI_RoleAssignMethod::GoodToKick )
	{
		CPointDouble left_top( 0, 1.8 );

		if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_3vs3 )
			left_top = CPointDouble( 0, 1.3 );
		if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_5vs5 )
			left_top = CPointDouble( 0, 1.8 );
		if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_AndroSot )
			left_top = CPointDouble( 0, 1.8 );

		CPointDouble right_bottom( 2.2, 0 );

		if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_3vs3 )
			right_bottom = CPointDouble( 1.5, 0 );
		if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_5vs5 )
			right_bottom = CPointDouble( 2.2, 0 );
		if( ROBOT_SOCCER_RROGRAM_GROUND == ROBOT_SOCCER_RROGRAM_GROUND_AndroSot )
			right_bottom = CPointDouble( 2.2, 0 );


		CPointDouble left_top_screen = left_top;
		m_ground.GroundToScreen( left_top_screen );

		CPointDouble right_bottom_screen = right_bottom;
		m_ground.GroundToScreen( right_bottom_screen );		
		int p_size = 3;

		CPointDouble pos_ball = m_posBallClink_screen;
		m_ground.ScreenToGround( pos_ball );
		
		for( int px=(int)left_top_screen.x ; px<(int)right_bottom_screen.x ; px+=p_size )
		{
			for( int py=(int)left_top_screen.y ; py<(int)right_bottom_screen.y ; py+=p_size )
			{
				CPointDouble pos(px,py);
				m_ground.ScreenToGround( pos );

				CRobot robot;
				robot.SetPosition( pos );

				double fitness = robot.CalcKickFitness( pos_ball, target_pos);
				

				int c = (int)(255*(fitness-0.5)*2);
				c = max(0,c);

				COLORREF color;
				color = RGB( c, c, c);

				m_dcFitness.SetPixel( px, py, color );
			}
		}
		
	}

	EnterCriticalSection(&m_critPropertyPageStrategyGUI);
	m_dcFitness.Copy( &m_dcFitness_share );
	LeaveCriticalSection(&m_critPropertyPageStrategyGUI);
}

void CPropertyPageStrategyGUI::DrawSituation( CStrategyGUI::Situation situation )
{
	CRectMouse rectSituationArea;
				
	{
		CPointDouble left_top, right_bottom;

		left_top = CPointDouble( situation.condition.area.rect.left, situation.condition.area.rect.top );
		right_bottom = CPointDouble( situation.condition.area.rect.right, situation.condition.area.rect.bottom );

		m_ground.GroundToScreen( left_top );
		m_ground.GroundToScreen( right_bottom );

		rectSituationArea.Init( left_top.x, right_bottom.y, right_bottom.x, left_top.y );
		rectSituationArea.SetColor( RGB(32,96,32) );
		rectSituationArea.SetTitle( situation.name );
	}

	DrawSituation( rectSituationArea );
}

void CPropertyPageStrategyGUI::DrawSituation( CRectMouse rectSituationArea )
{
	m_pDC->SelectPen( rectSituationArea.GetColor(), PS_SOLID, 1 );
	m_pDC->SelectBrush( false );

		
	//if( situation.condition.area.type == CStrategyGUI::CONDITION_AREA_RECTANGLE )
		m_pDC->Rectangle( rectSituationArea.GetRect() );

	CPointDouble left_top = rectSituationArea.GetRect().TopLeft();
	CPointDouble right_bottom = rectSituationArea.GetRect().BottomRight();
	m_ground.ScreenToGround( left_top );
	m_ground.ScreenToGround( right_bottom );

	CString tmp;
	tmp.Format(_T("%s\n\r(%.2lf,%.2lf)-(%.2lf,%.2lf)\n\r(%.2lf,%.2lf)"),
		rectSituationArea.Title(), left_top.x, left_top.y, right_bottom.x, right_bottom.y,
		right_bottom.x-left_top.x, left_top.y-right_bottom.y );

	CRect rectText = rectSituationArea.GetRect();
	rectText.left   -= 200;
	rectText.right  += 200;
	rectText.bottom += 200;
	rectText = rectText + CPoint(0, rectSituationArea.GetRect().Height()/2-20 );

	m_pDC->SetTextColor( rectSituationArea.GetColor() );
	m_pDC->DrawText( tmp, rectText,	DT_CENTER );
}

void CPropertyPageStrategyGUI::DrawDisplay_Situation( CString& strTitle, CString& strTitleInfo, CString& strMsg )
{
	strTitle      = _T("[Define Situation]");
	strTitleInfo  = _T(" > You can edit situtation area by dragging with left mouse button.");
	strTitleInfo += _T("\n");
	strTitleInfo += _T("  (Common) If you press the right mouse button, you can change the position of the ball.");

	// Situation:Verify
	{
		bool bSituation = false;
		for( int i=0 ; i<3 ; i++ )
		{
			if( m_bShowVerifySituation )
			{
				m_pDC->SelectPen( RGB(64,0,0), PS_SOLID, 1 );
				m_pDC->SelectBrush( RGB(64,0,0) );

				for( int j=0 ; j<m_strategyGUI.GetVerifyVerifySituationRectN(i) ; j++ )
				{
					CRectDouble rect = m_strategyGUI.GetVerifyVerifySituationRect( i, j );

					CPointDouble left_top, right_bottom;

					left_top = rect.TopLeft();
					right_bottom = rect.BottomRight();

					m_ground.GroundToScreen( left_top );
					m_ground.GroundToScreen( right_bottom );

					CRect rectDraw( (int)left_top.x, (int)right_bottom.y, (int)right_bottom.x, (int)left_top.y );

					m_pDC->Rectangle( rectDraw );

					bSituation = true;
				}
			}
		}

		m_ground.Draw( m_pDC, RGB(255,255,255), true, false );
	
		if( bSituation )
		{
			strMsg = _T("[Situation Definition test result]");
			strMsg += _T("\n");
			strMsg += m_strategyGUI.GetErrorMsg();
		}
	}
}

void CPropertyPageStrategyGUI::DrawDisplay_RoleAssign( CString& strTitle, CString& strTitleInfo, CString& strMsg )
{
	static int countDraw = 0;
	countDraw++;

	strTitle = _T("[Role Assignment]");

	CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );

	if( m_focusedSituationRoleID >= 0 )
	if( situation.role_assign.role[m_focusedSituationRoleID].assign.method == StrategyGUI_RoleAssignMethod::CloseToLocation )
	{
		strTitleInfo = _T(" > Location of closest Robot: With left mouse button, you can change the target point.");

		CPointDouble pos_screen = situation.role_assign.role[m_focusedSituationRoleID].assign.pos;
		m_ground.GroundToScreen( pos_screen );

		m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
		m_pDC->SelectBrush( false );

		m_pDC->Square( (int)pos_screen.x, (int)pos_screen.y, 5, true );
		int a = 3;
		int b = 9;
		m_pDC->MoveTo( (int)pos_screen.x-a, (int)pos_screen.y );
		m_pDC->LineTo( (int)pos_screen.x-b, (int)pos_screen.y );
		m_pDC->MoveTo( (int)pos_screen.x+a, (int)pos_screen.y );
		m_pDC->LineTo( (int)pos_screen.x+b, (int)pos_screen.y );
		m_pDC->MoveTo( (int)pos_screen.x,   (int)pos_screen.y-a );
		m_pDC->LineTo( (int)pos_screen.x,   (int)pos_screen.y-b );
		m_pDC->MoveTo( (int)pos_screen.x,   (int)pos_screen.y+a );
		m_pDC->LineTo( (int)pos_screen.x,   (int)pos_screen.y+b );

		double t = (double)(countDraw%1000)/1000.0;
		int r = (int)(t*100);

		r = min(r,95);

		int c = (int)((2-t*2)*255);
		c = min(c,255);
		m_pDC->SelectPen( RGB(0,c,c), PS_SOLID, 1 );
		m_pDC->Circle( (int)pos_screen.x, (int)pos_screen.y, r, true );
	}
	else
	if( situation.role_assign.role[m_focusedSituationRoleID].assign.method == StrategyGUI_RoleAssignMethod::CloseToBall )
	{
		strTitleInfo = _T(" > robot approaching Ball: (Common) When you press the right mouse button, you can change the position of the ball.");

		CPointDouble pos_screen = m_posBallClink_screen;

		m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
		m_pDC->SelectBrush( false );

		m_pDC->Square( (int)pos_screen.x, (int)pos_screen.y, 5, true );
		int a = 3;
		int b = 9;
		m_pDC->MoveTo( (int)pos_screen.x-a, (int)pos_screen.y );
		m_pDC->LineTo( (int)pos_screen.x-b, (int)pos_screen.y );
		m_pDC->MoveTo( (int)pos_screen.x+a, (int)pos_screen.y );
		m_pDC->LineTo( (int)pos_screen.x+b, (int)pos_screen.y );
		m_pDC->MoveTo( (int)pos_screen.x,   (int)pos_screen.y-a );
		m_pDC->LineTo( (int)pos_screen.x,   (int)pos_screen.y-b );
		m_pDC->MoveTo( (int)pos_screen.x,   (int)pos_screen.y+a );
		m_pDC->LineTo( (int)pos_screen.x,   (int)pos_screen.y+b );

		double t = (double)(countDraw%1000)/1000.0;
		int r = (int)(t*100);

		r = min(r,95);

		int c = (int)((2-t*2)*255);
		c = min(c,255);
		m_pDC->SelectPen( RGB(0,c,c), PS_SOLID, 1 );
		m_pDC->Circle( (int)pos_screen.x, (int)pos_screen.y, r, true );
	}
	else
	if( situation.role_assign.role[m_focusedSituationRoleID].assign.method == StrategyGUI_RoleAssignMethod::GoodToKick )
	{
		strTitleInfo  = _T(" > Robot With Kick chance: If you press the left mouse button, you can change the target point.");
		strTitleInfo += _T("\n");
		strTitleInfo += _T("  (Common) With right mouse button, you can change the position of the ball.");

		CPointDouble posShootDestination_screen = situation.role_assign.role[m_focusedSituationRoleID].assign.pos;
		m_ground.GroundToScreen( posShootDestination_screen );

		CRect rect = m_rectSituationArea.GetRect();

		m_pDC->SelectPen( RGB(0,128,0), PS_SOLID, 1 );
		m_pDC->MoveTo( m_posBallClink_screen.Integer() );
		m_pDC->LineTo( posShootDestination_screen.Integer() );


		m_pDC->SelectPen( RGB(255,0,0), PS_SOLID, 1 );
		m_pDC->SelectBrush( RGB(255,128,0) );
		int r = 3;
		m_pDC->Circle( (int)m_posBallClink_screen.Integer().x, (int)m_posBallClink_screen.Integer().y, r, true );

		{
			double t = (double)(countDraw%1000)/1000.0;

			CPointDouble p0 = m_posBallClink_screen;
			CPointDouble p1 = posShootDestination_screen;

			CPointDouble p = p0*(1.0-t) + p1*t;

			m_pDC->SelectPen( RGB(128,0,0), PS_SOLID, 1 );
			m_pDC->Circle( (int)p.x, (int)p.y, r, true );
		}


		m_pDC->SelectPen( RGB(0,255,0), PS_SOLID, 1 );				
		m_pDC->SelectBrush( false );

		m_pDC->Circle( (int)posShootDestination_screen.x, (int)posShootDestination_screen.y, 5, true );
		int a = 3;
		int b = 9;
		m_pDC->MoveTo( (int)posShootDestination_screen.x-a, (int)posShootDestination_screen.y );
		m_pDC->LineTo( (int)posShootDestination_screen.x-b, (int)posShootDestination_screen.y );
		m_pDC->MoveTo( (int)posShootDestination_screen.x+a, (int)posShootDestination_screen.y );
		m_pDC->LineTo( (int)posShootDestination_screen.x+b, (int)posShootDestination_screen.y );
		m_pDC->MoveTo( (int)posShootDestination_screen.x,   (int)posShootDestination_screen.y-a );
		m_pDC->LineTo( (int)posShootDestination_screen.x,   (int)posShootDestination_screen.y-b );
		m_pDC->MoveTo( (int)posShootDestination_screen.x,   (int)posShootDestination_screen.y+a );
		m_pDC->LineTo( (int)posShootDestination_screen.x,   (int)posShootDestination_screen.y+b );
	}
}

void CPropertyPageStrategyGUI::DrawDisplay_Behavior( CString& strTitle, CString& strTitleInfo, CString& strMsg )
{
	static int countDraw = 0;
	countDraw++;

	strTitle = _T("[Define Action]");

	CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );
	CStrategyGUI::Behavior behavior = role.vecBehavior[m_focusedBehaviorID];

	if( behavior.type == StrategyGUI_BehaviorType::Goalkeep )
		// If the action is GOALKEEPER
	{
		strTitleInfo = _T(" > Goal Keeper");

		// Enemy Goalkeeper
	//	CPointDouble posA_clear_screen(m_ground.Width() - behavior.options.goalkeep.clear_x_size, m_ground.Height()/2 + behavior.options.goalkeep.clear_y_size );
	//	CPointDouble posB_clear_screen(m_ground.Width(), m_ground.Height()/2 - behavior.options.goalkeep.clear_y_size );
		
		// Home Team Goalkeeper
		CPointDouble posA_clear_screen(0, m_ground.Height() / 2 + behavior.options.goalkeep.clear_y_size);
		CPointDouble posB_clear_screen(behavior.options.goalkeep.clear_x_size, m_ground.Height() / 2 - behavior.options.goalkeep.clear_y_size);
		
		m_ground.GroundToScreen( posA_clear_screen );
		m_ground.GroundToScreen( posB_clear_screen );
		{
			m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
			m_pDC->SelectBrush( false );

			m_pDC->Rectangle( (int)posA_clear_screen.x, (int)posA_clear_screen.y, (int)posB_clear_screen.x, (int)posB_clear_screen.y );
		}

		// Enemy Goalkeeper
	//	CPointDouble posA(m_ground.Width() - behavior.options.goalkeep.x_pos, m_ground.Height() / 2 - behavior.options.goalkeep.y_size);
	//	CPointDouble posB(m_ground.Width() - behavior.options.goalkeep.x_pos, m_ground.Height() / 2 + behavior.options.goalkeep.y_size);
			
		// Home Team Goalkeeper
		CPointDouble posA( behavior.options.goalkeep.x_pos, m_ground.Height()/2 - behavior.options.goalkeep.y_size );
		CPointDouble posB( behavior.options.goalkeep.x_pos, m_ground.Height()/2 + behavior.options.goalkeep.y_size );
		double orientation = 90;

		CPointDouble posA_screen = posA;
		CPointDouble posB_screen = posB;
		m_ground.GroundToScreen( posA_screen );
		m_ground.GroundToScreen( posB_screen );

		// ¼öºñ ¶óÀÎ
		{
			m_pDC->SelectPen( RGB(0,255,0), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(0,255,0) );

			m_pDC->MoveTo( posA_screen.Integer() );
			m_pDC->LineTo( posB_screen.Integer() );

			m_pDC->Square( (int)posA_screen.x, (int)posA_screen.y, 1, true );
			m_pDC->Square( (int)posB_screen.x, (int)posB_screen.y, 1, true );
		}

		// ÀÌµ¿ ·Îº¿
		{
			double t = (double)(countDraw%1000)/1000.0;

			if( t > 0.5 )
				t = 1 - t;

			CRobot robot;
			robot.SetGround( m_ground );
			robot.SetState( OBJECT_STATE_REAL );

			CPointDouble pos;
			pos = posA * t*2 + posB * (1-t*2);

			robot.SetPosition( pos );
			robot.SetOrientationDegree( orientation );

			if( ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_AndroSot )
			{
				robot.SetOrientationDegree( orientation - 90 );
			}

			CRobotDraw robotDraw;
			robotDraw.DrawBody( m_pDC, &m_ground, &robot );
		}


		// ÆÄ¶ó¸ÞÅÍ Á¶ÀÛ¿ë GUI
		{
			CRect m_rect( 200, 320, 300, 340 );

			m_pDC->SelectPen( RGB(128,255,255), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			//m_pDC->Rectangle( m_rect );

			{
				CPoint posGK_GUI(230,140);
				{
					CRect rect = CRect( 0,0,15,8 ) + CPoint(-28,3) + posGK_GUI;
					m_rectGK_clear_ball_speed_up = rect;
					DrawRectArrowButton( rect, _T("up"), RGB(0,255,0) );
				}
				{
					CRect rect = CRect( 0,0,15,8 ) + CPoint(-28,14) + posGK_GUI;
					m_rectGK_clear_ball_speed_down = rect;
					DrawRectArrowButton( rect, _T("down"), RGB(0,255,0) );
				}
				{
					CRect rect = CRect( 0,0,200,25 ) + posGK_GUI;

					m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
					m_pDC->SelectBrush( RGB(16, 32, 32) );
					m_pDC->Rectangle( rect );

					m_pDC->SetBkMode( TRANSPARENT );
					m_pDC->SetTextColor( RGB( 0,255,255 ) );
					CString tmp;
					tmp.Format(_T("kick out condition : ball velocity< %.4lf m/s"), behavior.options.goalkeep.clear_ball_speed );
					m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
				}
			}
			{
				CPoint posGK_GUI(230,170);
				{
					CRect rect = CRect( 0,0,15,8 ) + CPoint(-28,3) + posGK_GUI;
					m_rectGK_clear_y_size_up = rect;
					DrawRectArrowButton( rect, _T("up"), RGB(0,255,0) );
				}
				{
					CRect rect = CRect( 0,0,15,8 ) + CPoint(-28,14) + posGK_GUI;
					m_rectGK_clear_y_size_down = rect;
					DrawRectArrowButton( rect, _T("down"), RGB(0,255,0) );
				}
				{
					CRect rect = CRect( 0,0,200,25 ) + posGK_GUI;

					m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
					m_pDC->SelectBrush( RGB(16, 32, 32) );
					m_pDC->Rectangle( rect );

					m_pDC->SetBkMode( TRANSPARENT );
					m_pDC->SetTextColor( RGB( 0,255,255 ) );
					CString tmp;
					tmp.Format(_T("kick out range (Y) : ¡¾ %.3lf m"), behavior.options.goalkeep.clear_y_size );
					m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
				}
			}
			{
				CPoint posGK_GUI(230,200);
				{
					CRect rect = CRect( 0,0,8,15 ) + CPoint(-30,5) + posGK_GUI;
					m_rectGK_clear_x_pos_left = rect;
					DrawRectArrowButton( rect, _T("left"), RGB(0,255,0) );
				}
				{
					CRect rect = CRect( 0,0,8,15 ) + CPoint(-19,5) + posGK_GUI;
					m_rectGK_clear_x_pos_right = rect;
					DrawRectArrowButton( rect, _T("right"), RGB(0,255,0) );
				}
				{
					CRect rect = CRect( 0,0,200,25 ) + posGK_GUI;

					m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
					m_pDC->SelectBrush( RGB(16, 32, 32) );
					m_pDC->Rectangle( rect );

					m_pDC->SetBkMode( TRANSPARENT );
					m_pDC->SetTextColor( RGB( 0,255,255 ) );
					CString tmp;
					tmp.Format(_T("Kickout Range (X) :    %.3lf m"), behavior.options.goalkeep.clear_x_size );
					m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
				}
			}
				
			{
				CPoint posGK_GUI(230,240);
				{
					CRect rect = CRect( 0,0,15,8 ) + CPoint(-28,3) + posGK_GUI;
					m_rectGK_y_size_up = rect;
					DrawRectArrowButton( rect, _T("up"), RGB(0,255,0) );
				}
				{
					CRect rect = CRect( 0,0,15,8 ) + CPoint(-28,14) + posGK_GUI;
					m_rectGK_y_size_down = rect;
					DrawRectArrowButton( rect, _T("down"), RGB(0,255,0) );
				}
				{
					CRect rect = CRect( 0,0,200,25 ) + posGK_GUI;

					m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
					m_pDC->SelectBrush( RGB(16, 32, 32) );
					m_pDC->Rectangle( rect );

					m_pDC->SetBkMode( TRANSPARENT );
					m_pDC->SetTextColor( RGB( 0,255,255 ) );
					CString tmp;
					tmp.Format(_T("Goalkeeper normal range (Y) : ¡¾ %.3lf m"), behavior.options.goalkeep.y_size );
					m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
				}
			}
			{
				CPoint posGK_GUI(230,270);
				{
					CRect rect = CRect( 0,0,8,15 ) + CPoint(-30,5) + posGK_GUI;
					m_rectGK_x_pos_left = rect;
					DrawRectArrowButton( rect, _T("left"), RGB(0,255,0) );
				}
				{
					CRect rect = CRect( 0,0,8,15 ) + CPoint(-19,5) + posGK_GUI;
					m_rectGK_x_pos_right = rect;
					DrawRectArrowButton( rect, _T("right"), RGB(0,255,0) );
				}
				{
					CRect rect = CRect( 0,0,200,25 ) + posGK_GUI;

					m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
					m_pDC->SelectBrush( RGB(16, 32, 32) );
					m_pDC->Rectangle( rect );

					m_pDC->SetBkMode( TRANSPARENT );
					m_pDC->SetTextColor( RGB( 0,255,255 ) );
					CString tmp;
					tmp.Format(_T("Goalkeeper normal position (X) :    %.3lf m"), behavior.options.goalkeep.x_pos );
					m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
				}
			}
		}
	}
	else
	if( behavior.type == StrategyGUI_BehaviorType::Defense_Wall )
		// If the action is DEFENSE
	{
		strTitleInfo = _T(" > Defense : With left, right button of Mouse, you can change the position of defense.");

		CPointDouble posA = behavior.options.defense_wall.posA;
		CPointDouble posB = behavior.options.defense_wall.posB;
		double orientation = (posA-posB).AngleDegree();

		CPointDouble posA_screen = posA;
		CPointDouble posB_screen = posB;

		m_ground.GroundToScreen( posA_screen );
		m_ground.GroundToScreen( posB_screen );

		// ¼öºñ ¶óÀÎ
		{
			m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(0,255,255) );

			m_pDC->MoveTo( posA_screen.Integer() );
			m_pDC->LineTo( posB_screen.Integer() );

			m_pDC->Square( (int)posA_screen.x, (int)posA_screen.y, 1, true );
			m_pDC->Square( (int)posB_screen.x, (int)posB_screen.y, 1, true );
		}

		// ¼öºñ ¿µ¿ª
		{
			CPointDouble posA2;
			posA2.x = posA.x + cos( (posA-posB).AngleRadian() - M_PI/2 ) * behavior.options.defense_wall.clear_x_size;
			posA2.y = posA.y + sin( (posA-posB).AngleRadian() - M_PI/2 ) * behavior.options.defense_wall.clear_x_size;

			CPointDouble posB2;
			posB2.x = posB.x + cos( (posA-posB).AngleRadian() - M_PI/2 ) * behavior.options.defense_wall.clear_x_size;
			posB2.y = posB.y + sin( (posA-posB).AngleRadian() - M_PI/2 ) * behavior.options.defense_wall.clear_x_size;

			CPointDouble posA2_screen = posA2;
			CPointDouble posB2_screen = posB2;

			m_ground.GroundToScreen( posA2_screen );
			m_ground.GroundToScreen( posB2_screen );

			m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
			m_pDC->SelectBrush( false );

			m_pDC->MoveTo( posA_screen.Integer() );
			m_pDC->LineTo( posA2_screen.Integer() );
			m_pDC->LineTo( posB2_screen.Integer() );
			m_pDC->LineTo( posB_screen.Integer() );
		}

		// Á¤Áö »óÅÂ ·Îº¿
		/*
		{
			CRobot robot;
			robot.SetGround( m_ground );
			robot.SetState( OBJECT_STATE_NOT_EXIST );

			robot.SetPosition( posA );
			robot.SetOrientationDegree( orientation );

			if( ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_AndroSot )
			{
				robot.SetOrientationDegree( orientation - 90 );
			}

			CRobotDraw robotDraw;
			robotDraw.DrawBody( m_pDC, &m_ground, &robot );

			robot.SetPosition( posB );
			robot.SetOrientationDegree( orientation );

			if( ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_AndroSot )
			{
				robot.SetOrientationDegree( orientation - 90 );
			}

			robotDraw.DrawBody( m_pDC, &m_ground, &robot );
		}
		*/

		// ÀÌµ¿ ·Îº¿
		{
			double t = (double)(countDraw%1000)/1000.0;

			if( t > 0.5 )
				t = 1 - t;

			CRobot robot;
			robot.SetGround( m_ground );
			robot.SetState( OBJECT_STATE_REAL );

			CPointDouble pos;
			pos = posA * t*2 + posB * (1-t*2);

			robot.SetPosition( pos );
			robot.SetOrientationDegree( orientation );

			if( ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_AndroSot )
			{
				robot.SetOrientationDegree( orientation - 90 );
			}


			CRobotDraw robotDraw;
			robotDraw.DrawBody( m_pDC, &m_ground, &robot );
		}
			
		{
			CRect rect = CRect( 0,0,100,20 ) + CPoint(-50,-40) + posA_screen.Integer();

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			m_pDC->Rectangle( rect );

			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( RGB( 0,255,255 ) );
			CString tmp;
			tmp.Format(_T("(%.3lf, %.3lf)"), behavior.options.defense_wall.posA.x, behavior.options.defense_wall.posA.y );
			m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		}
		{
			CRect rect = CRect( 0,0,100,20 ) + CPoint(-50,20) + posB_screen.Integer();

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			m_pDC->Rectangle( rect );

			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( RGB( 0,255,255 ) );
			CString tmp;
			tmp.Format(_T("(%.3lf, %.3lf)"), behavior.options.defense_wall.posB.x, behavior.options.defense_wall.posB.y );
			m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		}

		{
			CPoint posGK_GUI(310,185);
			{
				CRect rect = CRect( 0,0,15,8 ) + CPoint(-28,3) + posGK_GUI;
				m_rectGK_clear_ball_speed_up = rect;
				DrawRectArrowButton( rect, _T("up"), RGB(0,255,0) );
			}
			{
				CRect rect = CRect( 0,0,15,8 ) + CPoint(-28,14) + posGK_GUI;
				m_rectGK_clear_ball_speed_down = rect;
				DrawRectArrowButton( rect, _T("down"), RGB(0,255,0) );
			}
			{
				CRect rect = CRect( 0,0,200,25 ) + posGK_GUI;

				m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
				m_pDC->SelectBrush( RGB(16, 32, 32) );
				m_pDC->Rectangle( rect );

				m_pDC->SetBkMode( TRANSPARENT );
				m_pDC->SetTextColor( RGB( 0,255,255 ) );
				CString tmp;
				tmp.Format(_T("Kickout condition : ball velocity < %.4lf m/s"), behavior.options.defense_wall.clear_ball_speed );
				m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
			}
		}			
		{
			CPoint posGK_GUI(310,220);
			{
				CRect rect = CRect( 0,0,8,15 ) + CPoint(-30,5) + posGK_GUI;
				m_rectGK_clear_x_pos_left = rect;
				DrawRectArrowButton( rect, _T("left"), RGB(0,255,0) );
			}
			{
				CRect rect = CRect( 0,0,8,15 ) + CPoint(-19,5) + posGK_GUI;
				m_rectGK_clear_x_pos_right = rect;
				DrawRectArrowButton( rect, _T("right"), RGB(0,255,0) );
			}
			{
				CRect rect = CRect( 0,0,200,25 ) + posGK_GUI;

				m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
				m_pDC->SelectBrush( RGB(16, 32, 32) );
				m_pDC->Rectangle( rect );

				m_pDC->SetBkMode( TRANSPARENT );
				m_pDC->SetTextColor( RGB( 0,255,255 ) );
				CString tmp;
				tmp.Format(_T("kickout range (X) :    %.3lf m"), behavior.options.defense_wall.clear_x_size );
				m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
			}
		}
	}
	else
	if( behavior.type == StrategyGUI_BehaviorType::MoveTo )
		// If the action is MOVE TO
	{
		DisplayPositionErrorUI( behavior.options.move_to.destination.error, behavior.options.move_to.destination.bBall );
		DisplayBallDestination( behavior.options.move_to.destination.bBall );



		strTitleInfo = _T(" > Movement : If you press the left mouse button, move the target point can be changed.");

		CPointDouble posDestination_screen;
		posDestination_screen = behavior.options.move_to.destination.pos;
		m_ground.GroundToScreen( posDestination_screen );

		CString strDestination;

		if( behavior.options.move_to.destination.bBall )
		{
			posDestination_screen = m_posBallClink_screen;

			strDestination = _T("target=ball");
			m_pDC->SelectPen( RGB(255,128,0), PS_SOLID, 1 );
		}
		else
		{
			strDestination = _T("target=fixed position");
			m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
		}


		{
			int size1 = 5;
			int size2 = 3;
			m_pDC->MoveTo( (int)posDestination_screen.x - size1        , (int)posDestination_screen.y - size1         );
			m_pDC->LineTo( (int)posDestination_screen.x - size1 + size2, (int)posDestination_screen.y - size1         );
			m_pDC->MoveTo( (int)posDestination_screen.x - size1        , (int)posDestination_screen.y - size1         );
			m_pDC->LineTo( (int)posDestination_screen.x - size1        , (int)posDestination_screen.y - size1 + size2 );

			m_pDC->MoveTo( (int)posDestination_screen.x + size1        , (int)posDestination_screen.y - size1         );
			m_pDC->LineTo( (int)posDestination_screen.x + size1 - size2, (int)posDestination_screen.y - size1         );
			m_pDC->MoveTo( (int)posDestination_screen.x + size1        , (int)posDestination_screen.y - size1         );
			m_pDC->LineTo( (int)posDestination_screen.x + size1        , (int)posDestination_screen.y - size1 + size2 );

			m_pDC->MoveTo( (int)posDestination_screen.x - size1        , (int)posDestination_screen.y + size1         );
			m_pDC->LineTo( (int)posDestination_screen.x - size1 + size2, (int)posDestination_screen.y + size1         );
			m_pDC->MoveTo( (int)posDestination_screen.x - size1        , (int)posDestination_screen.y + size1         );
			m_pDC->LineTo( (int)posDestination_screen.x - size1        , (int)posDestination_screen.y + size1 - size2 );

			m_pDC->MoveTo( (int)posDestination_screen.x + size1        , (int)posDestination_screen.y + size1         );
			m_pDC->LineTo( (int)posDestination_screen.x + size1 - size2, (int)posDestination_screen.y + size1         );
			m_pDC->MoveTo( (int)posDestination_screen.x + size1        , (int)posDestination_screen.y + size1         );
			m_pDC->LineTo( (int)posDestination_screen.x + size1        , (int)posDestination_screen.y + size1 - size2 );

			int size3 = 4;
			m_pDC->MoveTo( (int)posDestination_screen.x        , (int)posDestination_screen.y                 );
			m_pDC->LineTo( (int)posDestination_screen.x + size3, (int)posDestination_screen.y                 );

			m_pDC->MoveTo( (int)posDestination_screen.x        , (int)posDestination_screen.y                 );
			m_pDC->LineTo( (int)posDestination_screen.x - size3, (int)posDestination_screen.y                 );

			m_pDC->MoveTo( (int)posDestination_screen.x        , (int)posDestination_screen.y                 );
			m_pDC->LineTo( (int)posDestination_screen.x        , (int)posDestination_screen.y + size3         );

			m_pDC->MoveTo( (int)posDestination_screen.x        , (int)posDestination_screen.y                 );
			m_pDC->LineTo( (int)posDestination_screen.x        , (int)posDestination_screen.y - size3         );
		}

		//m_pDC->SetTextColor( RGB( 255,255,0 ) );
		//CRect rectDestination = CRect( 0, 0, 100, 20 ) + posDestination + CPoint(10, 10);
		//m_pDC->DrawText( strDestination, rectDestination, DT_LEFT );


		double t = (double)(countDraw%500)/500;
		if( t < 0.5 )
		{
			t = t * 2;

			int r = (int)((1-t)*50);

			r = min(r,95);
			int c = (int)((2-t*2)*255);
			c = min(c,255);
			m_pDC->SelectPen( RGB(c,c,0), PS_SOLID, 1 );
			m_pDC->SelectBrush(false);
			m_pDC->Circle( (int)posDestination_screen.x, (int)posDestination_screen.y, r, true );
		}
	}
	else
	if( behavior.type == StrategyGUI_BehaviorType::Kick_C )
		// If the action is KICK C
	{
		DisplayPosApproach( behavior.options.kick_C.approach.bPosDirection, _T("approach direction") );
		DisplayPosDirection( behavior.options.kick_C.target.bPosDirection, _T("kick position") );



		strTitleInfo = _T(" > Combined ball kick: Press the left mouse button and the right approach, you can change the direction and the next direction.");


		CPointDouble posBall        = m_posBallClink_screen;
		CPointDouble posBall_screen = m_posBallClink_screen;
		m_ground.ScreenToGround( posBall );


		CPointDouble posDirectionApproach;
		CPointDouble posDirectionApproach_screen;
		double directionApproach;

		CPointDouble posDirectionKick;
		CPointDouble posDirectionKick_screen;
		double directionKick;


		if( behavior.options.kick_C.approach.bPosDirection )
		{
			CPointDouble posApproach        = behavior.options.kick_C.approach.posDirection;
			CPointDouble posApproach_screen = posApproach;
			m_ground.GroundToScreen( posApproach_screen );

			directionApproach = (posApproach-posBall).AngleDegree();
		}
		else
		{
			directionApproach = behavior.options.kick_C.approach.direction;
		}
		posDirectionApproach.x = posBall.x + cos( directionApproach * M_PI / 180 ) * 0.2;
		posDirectionApproach.y = posBall.y + sin( directionApproach * M_PI / 180 ) * 0.2;
		posDirectionApproach_screen = posDirectionApproach;
		m_ground.GroundToScreen( posDirectionApproach_screen );

		CPointDouble posDirectionApproach_text;
		posDirectionApproach_text.x = posBall.x + cos( directionApproach * M_PI / 180 ) * 0.4;
		posDirectionApproach_text.y = posBall.y + sin( directionApproach * M_PI / 180 ) * 0.4;
		CPointDouble posDirectionApproach_text_screen = posDirectionApproach_text;
		m_ground.GroundToScreen( posDirectionApproach_text_screen );


		if( behavior.options.kick_C.target.bPosDirection )
		{
			CPointDouble posKick        = behavior.options.kick_C.target.posDirection;
			CPointDouble posKick_screen = posKick;
			m_ground.GroundToScreen( posKick_screen );

			directionKick = (posKick - posBall).AngleDegree();
		}
		else
		{
			directionKick = behavior.options.kick_C.target.direction;
		}
		posDirectionKick.x = posBall.x + cos( directionKick * M_PI / 180 ) * 0.2;
		posDirectionKick.y = posBall.y + sin( directionKick * M_PI / 180 ) * 0.2;
		posDirectionKick_screen = posDirectionKick;
		m_ground.GroundToScreen( posDirectionKick_screen );

		CPointDouble posDirectionKick_text;
		posDirectionKick_text.x = posBall.x + cos( directionKick * M_PI / 180 ) * 0.4;
		posDirectionKick_text.y = posBall.y + sin( directionKick * M_PI / 180 ) * 0.4;
		CPointDouble posDirectionKick_text_screen = posDirectionKick_text;
		m_ground.GroundToScreen( posDirectionKick_text_screen );

			

		if( behavior.options.kick_C.approach.bPosDirection )
		{
			CPointDouble posMarker_screen = behavior.options.kick_C.approach.posDirection;
			m_ground.GroundToScreen( posMarker_screen );

			CRect rect = CRect( 0,0,120,20 ) + CPoint(10,5) + posMarker_screen.Integer();

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			m_pDC->Rectangle( rect );

			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( RGB( 0,255,255 ) );
			CString tmp;
			tmp.Format(_T("( %.3lfm, %.3lfm )"), behavior.options.kick_C.approach.posDirection.x, behavior.options.kick_C.approach.posDirection.y );
			m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );


			m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
			m_pDC->SelectBrush( false );

			int size = 3;
			m_pDC->MoveTo( posMarker_screen.Integer() );
			m_pDC->LineTo( posMarker_screen.Integer() + CPoint(0,size) );
			m_pDC->MoveTo( posMarker_screen.Integer() );
			m_pDC->LineTo( posMarker_screen.Integer() + CPoint(0,-size) );
			m_pDC->MoveTo( posMarker_screen.Integer() );
			m_pDC->LineTo( posMarker_screen.Integer() + CPoint(size,0) );
			m_pDC->MoveTo( posMarker_screen.Integer() );
			m_pDC->LineTo( posMarker_screen.Integer() + CPoint(-size,0) );

			int r = 5;
			m_pDC->Circle( (int)posMarker_screen.x, (int)posMarker_screen.y, r, true );
		}
		else
		{
			CRect rect = CRect( -30,-10,30,10 ) + posDirectionApproach_text_screen.Integer();

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			m_pDC->Rectangle( rect );

			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( RGB( 0,255,255 ) );
			CString tmp;
			tmp.Format(_T("%.1lf¡Æ"), behavior.options.kick_C.approach.direction );
			m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		}


		if( behavior.options.kick_C.target.bPosDirection )
		{
			CPointDouble posMarker_screen = behavior.options.kick_C.target.posDirection;
			m_ground.GroundToScreen( posMarker_screen );

			CRect rect = CRect( 0,0,120,20 ) + CPoint(10,5) + posMarker_screen.Integer();

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			m_pDC->Rectangle( rect );

			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( RGB( 0,255,255 ) );
			CString tmp;
			tmp.Format(_T("( %.3lfm, %.3lfm )"), behavior.options.kick_C.target.posDirection.x, behavior.options.kick_C.target.posDirection.y );
			m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );


			m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
			m_pDC->SelectBrush( false );

			int size = 3;
			m_pDC->MoveTo( posMarker_screen.Integer() );
			m_pDC->LineTo( posMarker_screen.Integer() + CPoint(0,size) );
			m_pDC->MoveTo( posMarker_screen.Integer() );
			m_pDC->LineTo( posMarker_screen.Integer() + CPoint(0,-size) );
			m_pDC->MoveTo( posMarker_screen.Integer() );
			m_pDC->LineTo( posMarker_screen.Integer() + CPoint(size,0) );
			m_pDC->MoveTo( posMarker_screen.Integer() );
			m_pDC->LineTo( posMarker_screen.Integer() + CPoint(-size,0) );

			int r = 5;
			m_pDC->Circle( (int)posMarker_screen.x, (int)posMarker_screen.y, r, true );
		}
		else
		{
			CRect rect = CRect( -30,-10,30,10 ) + posDirectionKick_text_screen.Integer();

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			m_pDC->Rectangle( rect );

			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( RGB( 0,255,255 ) );
			CString tmp;
			tmp.Format(_T("%.1lf¡Æ"), behavior.options.kick_C.target.direction );
			m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		}

		m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
		m_pDC->SelectBrush( false );
		DrawArrow( posBall             , posDirectionKick, directionKick        , 0.04, 20, RGB(0,255,255) );
		DrawArrow( posDirectionApproach, posBall         , directionApproach+180, 0.04, 20, RGB(0,255,255) );


		double t = (double)(countDraw%500)/500;
		if( t < 0.5 )
		{
			t = t * 2;

			CPointDouble p1 = posBall;
			CPointDouble p0;
			p0.x = posBall.x + cos( directionApproach * M_PI / 180 ) * 0.2;
			p0.y = posBall.y + sin( directionApproach * M_PI / 180 ) * 0.2;

			CPointDouble p = p1*t + p0*(1-t);
			m_ground.GroundToScreen( p );
				
			m_pDC->SelectPen( RGB(255,255,0), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(0,0,0) );
			m_pDC->Circle( (int)p.x, (int)p.y, 2, true);
		}
		else
		if( t < 1.0 )
		{
			t = (t-0.5)*2;

			CPointDouble p0 = posBall;
			CPointDouble p1;
			p1.x = posBall.x + cos( directionKick * M_PI / 180 ) * 0.2;
			p1.y = posBall.y + sin( directionKick * M_PI / 180 ) * 0.2;

			CPointDouble p = p1*t + p0*(1-t);
			m_ground.GroundToScreen( p );
				
			m_pDC->SelectPen( RGB(255,255,0), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(0,0,0) );
			m_pDC->Circle( (int)p.x, (int)p.y, 2, true);
		}
	}
	else
	if( behavior.type == StrategyGUI_BehaviorType::Kick_B )
		// If the action is KICK B
	{
		strTitleInfo = _T(" > Wait & Shoot :Press the left mouse button and the right atmosphere can change the position and direction of the next.");


		CPointDouble posDestination = behavior.options.kick_B.posA;

		CPointDouble posDestination_ = posDestination;
		m_ground.GroundToScreen( posDestination_ );
		CPoint posDestination_screen = posDestination_.Integer();


		CString strDestination;

		// behavior.options.bBallDestination == false
		strDestination = _T("Moving target = fixed position");
		m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
			

		CPoint dir;
		double direction;

		// behavior.options.bPosDirection == true
		direction = (behavior.options.kick_B.posB - posDestination).AngleDegree();

		dir.x = (int)(  cos( direction * M_PI / 180 ) * 20 );
		dir.y = (int)( -sin( direction * M_PI / 180 ) * 20 );



		{
			int size1 = 5;
			int size2 = 3;
			m_pDC->MoveTo( posDestination_screen.x - size1        , posDestination_screen.y - size1         );
			m_pDC->LineTo( posDestination_screen.x - size1 + size2, posDestination_screen.y - size1         );
			m_pDC->MoveTo( posDestination_screen.x - size1        , posDestination_screen.y - size1         );
			m_pDC->LineTo( posDestination_screen.x - size1        , posDestination_screen.y - size1 + size2 );

			m_pDC->MoveTo( posDestination_screen.x + size1        , posDestination_screen.y - size1         );
			m_pDC->LineTo( posDestination_screen.x + size1 - size2, posDestination_screen.y - size1         );
			m_pDC->MoveTo( posDestination_screen.x + size1        , posDestination_screen.y - size1         );
			m_pDC->LineTo( posDestination_screen.x + size1        , posDestination_screen.y - size1 + size2 );

			m_pDC->MoveTo( posDestination_screen.x - size1        , posDestination_screen.y + size1         );
			m_pDC->LineTo( posDestination_screen.x - size1 + size2, posDestination_screen.y + size1         );
			m_pDC->MoveTo( posDestination_screen.x - size1        , posDestination_screen.y + size1         );
			m_pDC->LineTo( posDestination_screen.x - size1        , posDestination_screen.y + size1 - size2 );

			m_pDC->MoveTo( posDestination_screen.x + size1        , posDestination_screen.y + size1         );
			m_pDC->LineTo( posDestination_screen.x + size1 - size2, posDestination_screen.y + size1         );
			m_pDC->MoveTo( posDestination_screen.x + size1        , posDestination_screen.y + size1         );
			m_pDC->LineTo( posDestination_screen.x + size1        , posDestination_screen.y + size1 - size2 );

			int size3 = 4;
			m_pDC->MoveTo( posDestination_screen.x        , posDestination_screen.y                 );
			m_pDC->LineTo( posDestination_screen.x + size3, posDestination_screen.y                 );

			m_pDC->MoveTo( posDestination_screen.x        , posDestination_screen.y                 );
			m_pDC->LineTo( posDestination_screen.x - size3, posDestination_screen.y                 );

			m_pDC->MoveTo( posDestination_screen.x        , posDestination_screen.y                 );
			m_pDC->LineTo( posDestination_screen.x        , posDestination_screen.y + size3         );

			m_pDC->MoveTo( posDestination_screen.x        , posDestination_screen.y                 );
			m_pDC->LineTo( posDestination_screen.x        , posDestination_screen.y - size3         );

		}

		m_pDC->SetTextColor( RGB( 255,0,0 ) );
		CRect rectDestination = CRect( 0, 0, 150, 20 ) + posDestination_screen + CPoint(10, 10);
		//m_pDC->DrawText( strDestination, rectDestination, DT_LEFT );
			
			
		//if( behavior.options.bPosDirection )
			CPointDouble posDirection = behavior.options.kick_B.posB;
			CPointDouble posDirection_screen = behavior.options.kick_B.posB;
			m_ground.GroundToScreen( posDirection_screen );

			CRect rect = CRect( 0,0,120,20 ) + CPoint(10,5) + posDirection_screen.Integer();

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			m_pDC->Rectangle( rect );

			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( RGB( 0,255,255 ) );
			CString tmp;
			tmp.Format(_T("( %.3lfm, %.3lfm )"), behavior.options.kick_B.posB.x, behavior.options.kick_B.posB.y );
			m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );


			m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
			m_pDC->SelectBrush( false );

			int size = 3;
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(0,size) );
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(0,-size) );
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(size,0) );
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(-size,0) );

			int r = 5;
			m_pDC->Circle( (int)posDirection_screen.x, (int)posDirection_screen.y, r, true );


		{
			CPointDouble posArrowOrigin;
			posArrowOrigin.x = posDestination.x + cos( direction * M_PI / 180 ) * 0.2;
			posArrowOrigin.y = posDestination.y + sin( direction * M_PI / 180 ) * 0.2;


			CPointDouble p = (posDestination + posArrowOrigin)/2;

			double r = 0.1;
			m_ground.GroundToScreen( r );

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( false );


			m_pDC->MoveTo( posDestination_screen );
			m_pDC->LineTo( posDirection_screen.Integer() );
			DrawArrow( posDestination, posArrowOrigin, direction, 0.04, 20, RGB(0,255,255) );
		}


		// ÀÌµ¿ ·Îº¿
		{
			double t = (double)(countDraw%1000)/1000.0;

			if( t > 0.66 )
			{
				t = (1-t)/(1-0.66);
			}
			else
			{
				t = t/0.66;
			}

			CRobot robot;
			robot.SetGround( m_ground );
			robot.SetState( OBJECT_STATE_REAL );

			CPointDouble pos;
			pos = posDestination * t + posDirection * (1-t);

			robot.SetPosition( pos );
			robot.SetOrientationDegree( (posDirection-posDestination).AngleDegree() );

			if( ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_AndroSot )
			{
				robot.SetOrientationDegree( (posDirection-posDestination).AngleDegree() - 90 );
			}


			CRobotDraw robotDraw;
			robotDraw.DrawBody( m_pDC, &m_ground, &robot );
		}
		/*
		double t = (double)(countDraw%500)/500;
		if( t < 0.5 )
		{
			t = t * 2;

			int r = (int)((1-t)*50);

			r = min(r,95);
			int c = (int)((2-t*2)*255);
			c = min(c,255);
			m_pDC->SelectPen( RGB(c,c,0), PS_SOLID, 1 );
			m_pDC->SelectBrush(false);
			m_pDC->Circle( (int)posDestination_screen.x, (int)posDestination_screen.y, r, true );
		}
		else
		{
			t = (t-0.5)*2;

			CPointDouble p0 = posDestination;
			CPointDouble p1;
			p1.x = posDestination.x + cos( direction * M_PI / 180 ) * 0.2;
			p1.y = posDestination.y + sin( direction * M_PI / 180 ) * 0.2;

			CPointDouble p = p1*t + p0*(1-t);
			m_ground.GroundToScreen( p );
				
			m_pDC->SelectPen( RGB(255,255,0), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(0,0,0) );
			m_pDC->Circle( (int)p.x, (int)p.y, 2, true);
		}
		*/
	}
	else
	if( behavior.type == StrategyGUI_BehaviorType::Kick_A )
		// If the action is KICK A
	{
		DisplayPositionErrorUI( behavior.options.kick_A.destination.error, behavior.options.kick_A.destination.bBall );

		if( behavior.type == StrategyGUI_BehaviorType::Kick_A )
			DisplayBallDestination( behavior.options.kick_A.destination.bBall );

		DisplayPosDirection( behavior.options.kick_A.direction.bPosDirection, _T("Approaching Position") );



		strTitleInfo = _T(" > Movement (direction): By pressing the left mouse button and right button and aim the direction of the target point can be changed.");


		CPointDouble posDestination = behavior.options.kick_A.destination.pos;

		CPointDouble posDestination_ = posDestination;
		m_ground.GroundToScreen( posDestination_ );
		CPoint posDestination_screen = posDestination_.Integer();


		CString strDestination;

		if( behavior.options.kick_A.destination.bBall )
		{
			posDestination_screen = m_posBallClink_screen.Integer();

			posDestination = posDestination_screen;
			m_ground.ScreenToGround( posDestination );

			//m_pDC->Circle( posDestination.x, posDestination.y, 5, true );
			strDestination = _T("Movement Target = Ball");

			m_pDC->SelectPen( RGB(255,0,0), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(255,128,0) );
			int r = 3;
			m_pDC->Circle( (int)posDestination.x, (int)posDestination.y, r, true );

			m_pDC->SelectPen( RGB(255,128,0), PS_SOLID, 1 );
		}
		else
		{
			strDestination = _T("Movement Target = Fixed Position");

			m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
		}


		CPoint dir;
		double direction;

		if( behavior.options.kick_A.direction.bPosDirection )
		{
			direction = (behavior.options.kick_A.direction.posDirection - posDestination).AngleDegree();
		}
		else
		{
			direction = behavior.options.kick_A.direction.direction;
		}

		dir.x = (int)(  cos( direction * M_PI / 180 ) * 20 );
		dir.y = (int)( -sin( direction * M_PI / 180 ) * 20 );



		{
			int size1 = 5;
			int size2 = 3;
			m_pDC->MoveTo( posDestination_screen.x - size1        , posDestination_screen.y - size1         );
			m_pDC->LineTo( posDestination_screen.x - size1 + size2, posDestination_screen.y - size1         );
			m_pDC->MoveTo( posDestination_screen.x - size1        , posDestination_screen.y - size1         );
			m_pDC->LineTo( posDestination_screen.x - size1        , posDestination_screen.y - size1 + size2 );

			m_pDC->MoveTo( posDestination_screen.x + size1        , posDestination_screen.y - size1         );
			m_pDC->LineTo( posDestination_screen.x + size1 - size2, posDestination_screen.y - size1         );
			m_pDC->MoveTo( posDestination_screen.x + size1        , posDestination_screen.y - size1         );
			m_pDC->LineTo( posDestination_screen.x + size1        , posDestination_screen.y - size1 + size2 );

			m_pDC->MoveTo( posDestination_screen.x - size1        , posDestination_screen.y + size1         );
			m_pDC->LineTo( posDestination_screen.x - size1 + size2, posDestination_screen.y + size1         );
			m_pDC->MoveTo( posDestination_screen.x - size1        , posDestination_screen.y + size1         );
			m_pDC->LineTo( posDestination_screen.x - size1        , posDestination_screen.y + size1 - size2 );

			m_pDC->MoveTo( posDestination_screen.x + size1        , posDestination_screen.y + size1         );
			m_pDC->LineTo( posDestination_screen.x + size1 - size2, posDestination_screen.y + size1         );
			m_pDC->MoveTo( posDestination_screen.x + size1        , posDestination_screen.y + size1         );
			m_pDC->LineTo( posDestination_screen.x + size1        , posDestination_screen.y + size1 - size2 );

			int size3 = 4;
			m_pDC->MoveTo( posDestination_screen.x        , posDestination_screen.y                 );
			m_pDC->LineTo( posDestination_screen.x + size3, posDestination_screen.y                 );

			m_pDC->MoveTo( posDestination_screen.x        , posDestination_screen.y                 );
			m_pDC->LineTo( posDestination_screen.x - size3, posDestination_screen.y                 );

			m_pDC->MoveTo( posDestination_screen.x        , posDestination_screen.y                 );
			m_pDC->LineTo( posDestination_screen.x        , posDestination_screen.y + size3         );

			m_pDC->MoveTo( posDestination_screen.x        , posDestination_screen.y                 );
			m_pDC->LineTo( posDestination_screen.x        , posDestination_screen.y - size3         );

		}

		m_pDC->SetTextColor( RGB( 255,0,0 ) );
		CRect rectDestination = CRect( 0, 0, 150, 20 ) + posDestination_screen + CPoint(10, 10);
		//m_pDC->DrawText( strDestination, rectDestination, DT_LEFT );
			
			
		{
			CPointDouble posArrowOrigin;
			posArrowOrigin.x = posDestination.x + cos( direction * M_PI / 180 ) * 0.2;
			posArrowOrigin.y = posDestination.y + sin( direction * M_PI / 180 ) * 0.2;


			CPointDouble p = (posDestination + posArrowOrigin)/2;

			double r = 0.1;
			m_ground.GroundToScreen( r );

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( false );



			DrawArrow( posDestination, posArrowOrigin, direction, 0.04, 20, RGB(0,255,255) );
		}

		if( behavior.options.kick_A.direction.bPosDirection )
		{
			CPointDouble posDirection_screen = behavior.options.kick_A.direction.posDirection;
			m_ground.GroundToScreen( posDirection_screen );

			CRect rect = CRect( 0,0,120,20 ) + CPoint(10,5) + posDirection_screen.Integer();

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			m_pDC->Rectangle( rect );

			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( RGB( 0,255,255 ) );
			CString tmp;
			tmp.Format(_T("( %.3lfm, %.3lfm )"), behavior.options.kick_A.direction.posDirection.x, behavior.options.kick_A.direction.posDirection.y );
			m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );


			m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
			m_pDC->SelectBrush( false );

			int size = 3;
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(0,size) );
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(0,-size) );
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(size,0) );
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(-size,0) );

			int r = 5;
			m_pDC->Circle( (int)posDirection_screen.x, (int)posDirection_screen.y, r, true );
		}
		else
		{
			CRect rect = CRect( 0,0,60,20 ) + CPoint(40,20) + posDestination_screen;

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			m_pDC->Rectangle( rect );

			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( RGB( 0,255,255 ) );
			CString tmp;
			tmp.Format(_T("%.1lf¡Æ"), behavior.options.kick_A.direction.direction );
			m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		}


		double t = (double)(countDraw%500)/500;
		if( t < 0.5 )
		{
			t = t * 2;

			int r = (int)((1-t)*50);

			r = min(r,95);
			int c = (int)((2-t*2)*255);
			c = min(c,255);
			m_pDC->SelectPen( RGB(c,c,0), PS_SOLID, 1 );
			m_pDC->SelectBrush(false);
			m_pDC->Circle( (int)posDestination_screen.x, (int)posDestination_screen.y, r, true );
		}
		else
		{
			t = (t-0.5)*2;

			CPointDouble p0 = posDestination;
			CPointDouble p1;
			p1.x = posDestination.x + cos( direction * M_PI / 180 ) * 0.2;
			p1.y = posDestination.y + sin( direction * M_PI / 180 ) * 0.2;

			CPointDouble p = p1*t + p0*(1-t);
			m_ground.GroundToScreen( p );
				
			m_pDC->SelectPen( RGB(255,255,0), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(0,0,0) );
			m_pDC->Circle( (int)p.x, (int)p.y, 2, true);
		}
	}
	else
	if( behavior.type == StrategyGUI_BehaviorType::OrientationTo )
		// If the action is ORIENTATION
	{
		DisplayPosDirection( behavior.options.orientation.orientation.bPosDirection, _T("Approaching Direction") );


		strTitleInfo = _T(" > Change Direction : If you press the right mouse button, you can change the direction of the target.");

		CRobot robot;
		robot.SetGround( m_ground );
		robot.SetState( OBJECT_STATE_REAL );
			
		double direction;

		CPointDouble posDestination_screen;
		posDestination_screen = m_posRobotGUI;
		m_ground.GroundToScreen( posDestination_screen );

		if( behavior.options.orientation.orientation.bPosDirection )
		{
			CPointDouble d_pos = behavior.options.orientation.orientation.posDirection;
			direction = (d_pos - m_posRobotGUI).AngleDegree();

		}
		else
		{
			direction = behavior.options.orientation.orientation.direction;
		}

		{
			CPointDouble pos;
			pos = m_posRobotGUI;

			robot.SetPosition( pos );
			robot.SetOrientationDegree( direction );

			CRobotDraw robotDraw;
			robotDraw.DrawBody( m_pDC, &m_ground, &robot );
		}

		{
			CPointDouble posArrowOrigin;
			posArrowOrigin.x = m_posRobotGUI.x + cos( direction * M_PI / 180 ) * 0.2;
			posArrowOrigin.y = m_posRobotGUI.y + sin( direction * M_PI / 180 ) * 0.2;


			CPointDouble p = (m_posRobotGUI + posArrowOrigin)/2;

			double r = 0.1;
			m_ground.GroundToScreen( r );

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( false );


			double t = (double)(countDraw%500)/500;
			if( t < 0.5 )
			{
				t = t * 2;

				int theta = 40;
				theta = (int)((1-t)*120+10);
				{
					CPointDouble posSideArrow;
					posSideArrow.x = m_posRobotGUI.x + cos( (direction+theta) * M_PI / 180 ) * 0.1;
					posSideArrow.y = m_posRobotGUI.y + sin( (direction+theta) * M_PI / 180 ) * 0.1;

					DrawArrow( posSideArrow, posSideArrow, direction-90+10+theta, 0.03, 20, RGB(64,192,192) );

					CPointDouble posSideArrow_screen = posSideArrow;
					m_ground.GroundToScreen( posSideArrow_screen );
					m_pDC->MoveTo( posSideArrow_screen.Integer() );
					//m_pDC->AngleArc( (int)posDestination_screen.x, (int)posDestination_screen.y, (int)r, (int)direction+10+theta, 180-theta*2-10 );
					m_pDC->AngleArc( (int)posDestination_screen.x, (int)posDestination_screen.y, (int)r, (float)(direction+10+theta), 50.f );
				}
				{
					CPointDouble posSideArrow;
					posSideArrow.x = m_posRobotGUI.x + cos( (direction-theta) * M_PI / 180 ) * 0.1;
					posSideArrow.y = m_posRobotGUI.y + sin( (direction-theta) * M_PI / 180 ) * 0.1;

					DrawArrow( posSideArrow, posSideArrow, direction+90-10-theta, 0.03, 20, RGB(64,192,192) );

					CPointDouble posSideArrow_screen = posSideArrow;
					m_ground.GroundToScreen( posSideArrow_screen );
					m_pDC->MoveTo( posSideArrow_screen.Integer() );
					//m_pDC->AngleArc( (int)posDestination_screen.x, (int)posDestination_screen.y, (int)r, (int)direction-10-theta, -180+theta*2+10 );
					m_pDC->AngleArc( (int)posDestination_screen.x, (int)posDestination_screen.y, (int)r, (float)(direction-10-theta), -50.f );
				}
			}

			DrawArrow( m_posRobotGUI, posArrowOrigin, direction, 0.04, 20, RGB(0,255,255) );
		}

		if( behavior.options.orientation.orientation.bPosDirection )
		{
			CPointDouble posDirection_screen = behavior.options.orientation.orientation.posDirection;
			m_ground.GroundToScreen( posDirection_screen );

			CRect rect = CRect( 0,0,120,20 ) + CPoint(10,5) + posDirection_screen.Integer();

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			m_pDC->Rectangle( rect );

			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( RGB( 0,255,255 ) );
			CString tmp;
			tmp.Format(_T("( %.3lfm, %.3lfm )"), behavior.options.orientation.orientation.posDirection.x, behavior.options.orientation.orientation.posDirection.y );
			m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );


			m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
			m_pDC->SelectBrush( false );

			int size = 3;
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(0,size) );
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(0,-size) );
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(size,0) );
			m_pDC->MoveTo( posDirection_screen.Integer() );
			m_pDC->LineTo( posDirection_screen.Integer() + CPoint(-size,0) );

			int r = 6;
			m_pDC->Circle( (int)posDirection_screen.x, (int)posDirection_screen.y, r, true );
		}
		else
		{
			CRect rect = CRect( 0,0,60,20 ) + CPoint(40,20) + posDestination_screen.Integer();

			m_pDC->SelectPen( RGB(64,128,128), PS_SOLID, 1 );
			m_pDC->SelectBrush( RGB(16, 32, 32) );
			m_pDC->Rectangle( rect );

			m_pDC->SetBkMode( TRANSPARENT );
			m_pDC->SetTextColor( RGB( 0,255,255 ) );
			CString tmp;
			tmp.Format(_T("%.1lf¡Æ"), behavior.options.orientation.orientation.direction );
			m_pDC->DrawText( tmp, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		}
	}
	else
	if( behavior.type == StrategyGUI_BehaviorType::Velocity )
		// If the action is VELOCITY
	{
		strTitleInfo = _T(" > Velocity/Time");

		CPoint posVelocityUI( 530, 225 );

		CRect rectErrorBackground = CRect(0,0,100,145) + posVelocityUI;
		rectErrorBackground.InflateRect(2,2,2,2);
		m_pDC->SelectPen( RGB(64,64,128), PS_SOLID, 1 );
		m_pDC->SelectBrush( RGB(16,16,32) );
		m_pDC->Rectangle( rectErrorBackground );

		CRect rectVelocityTitle = CRect(0,0,110,20) + posVelocityUI;
		rectVelocityTitle.DeflateRect(3,3,3,3);
		m_pDC->SetTextColor( RGB( 255,255,255 ) );
		m_pDC->DrawText( _T("Fixed Velocity Set"), rectVelocityTitle, DT_CENTER );


		m_pDC->SelectPen( RGB(0,255,0), PS_SOLID, 1 );
		m_pDC->SelectBrush( false );

		CRect button( 0, 0, 13, 7 );

		{
			COLORREF colorButton = RGB(0,255,0);
			COLORREF colorFrame = RGB(32,32,192);
			CPoint posOption = posVelocityUI + CPoint(5,25);

			CRect buttonVelocityLinearUp   = button + posOption + CPoint(72,10);
			DrawRectArrowButton( buttonVelocityLinearUp  , _T("up")  , colorButton );

			CRect buttonVelocityLinearDown = button + posOption + CPoint(72,20);
			DrawRectArrowButton( buttonVelocityLinearDown, _T("down"), colorButton );

			CRect rectVelocityLinear       = CRect(0,0,90,35) + posOption;
			m_pDC->SelectPen( colorFrame, PS_SOLID, 1 );
			m_pDC->Rectangle( rectVelocityLinear );

			rectVelocityLinear.DeflateRect( 3,3,3+19,3 );
			//m_pDC->Rectangle( rectVelocityLinear );

			m_pDC->SetTextColor( RGB( 255, 255, 255 ) );
			m_pDC->DrawText( _T("Linear Velocity"), rectVelocityLinear, DT_LEFT );
			CString tmp;
			tmp.Format(_T("\n%.3lf m/s"), behavior.options.manual_velocity.vLinear );
			m_pDC->DrawText( tmp, rectVelocityLinear, DT_RIGHT );

			m_rectVelocityButton[0] = buttonVelocityLinearUp;
			m_rectVelocityButton[1] = buttonVelocityLinearDown;
		}

		{
			COLORREF colorButton = RGB(0,255,0);
			COLORREF colorFrame = RGB(32,32,192);
			CPoint posOption = posVelocityUI + CPoint(5,65);
				
			CRect buttonVelocityAngularUp   = button + posOption + CPoint(72,10);
			DrawRectArrowButton( buttonVelocityAngularUp  , _T("up")  , colorButton );

			CRect buttonVelocityAngularDown = button + posOption + CPoint(72,20);
			DrawRectArrowButton( buttonVelocityAngularDown, _T("down"), colorButton );

			CRect rectVelocityAngular       = CRect(0,0,90,35) + posOption;
			m_pDC->SelectPen( colorFrame, PS_SOLID, 1 );
			m_pDC->Rectangle( rectVelocityAngular );

			rectVelocityAngular.DeflateRect( 3,3,3+19,3 );
			//m_pDC->Rectangle( rectVelocityAngular );

			m_pDC->SetTextColor( RGB( 255, 255, 255 ) );
			m_pDC->DrawText( _T("Rotation velocity"), rectVelocityAngular, DT_LEFT );
			CString tmp;
			tmp.Format(_T("\n%.0lf ¡Æ/s"), behavior.options.manual_velocity.vAngular );
			m_pDC->DrawText( tmp, rectVelocityAngular, DT_RIGHT );

			m_rectVelocityButton[2] = buttonVelocityAngularUp;
			m_rectVelocityButton[3] = buttonVelocityAngularDown;
		}


		{
			COLORREF colorButton = RGB(0,255,0);
			COLORREF colorFrame = RGB(32,32,192);
			CPoint posOption = posVelocityUI + CPoint(5,105);
				
			CRect buttonVelocityTimeUp   = button + posOption + CPoint(72,10);
			DrawRectArrowButton( buttonVelocityTimeUp  , _T("up")  , colorButton );

			CRect buttonVelocityTimeDown = button + posOption + CPoint(72,20);
			DrawRectArrowButton( buttonVelocityTimeDown, _T("down"), colorButton );

			CRect rectVelocityTime       = CRect(0,0,90,35) + posOption;
			m_pDC->SelectPen( colorFrame, PS_SOLID, 1 );
			m_pDC->Rectangle( rectVelocityTime );

			rectVelocityTime.DeflateRect( 3,3,3+19,3 );
			//m_pDC->Rectangle( rectVelocityTime );

			m_pDC->SetTextColor( RGB( 255, 255, 255 ) );
			m_pDC->DrawText( _T("Time"), rectVelocityTime, DT_LEFT );
			CString tmp;
			tmp.Format(_T("\n%.2lf s"), behavior.options.manual_velocity.time );
			m_pDC->DrawText( tmp, rectVelocityTime, DT_RIGHT );

			m_rectVelocityButton[4] = buttonVelocityTimeUp;
			m_rectVelocityButton[5] = buttonVelocityTimeDown;
		}

		{
			CRobot robot;
			robot.SetGround( m_ground );
			robot.SetState( OBJECT_STATE_REAL );
			
			CPointDouble pos;
			pos = m_posRobotGUI;

			robot.SetPosition( pos );

			m_ground.GroundToScreen( pos );

			//CPointDouble d_pos = m_posRobotGUI_direction;
			//m_ground.GroundToScreen( d_pos );

			double direction = m_orientationRobotGUI;
				
			//if( d_pos != pos )
			//	direction = -(d_pos - pos).AngleDegree();

			robot.SetOrientationDegree( direction );

			CRobotDraw robotDraw;
			//robotDraw.DrawBody( m_pDC, &m_ground, &robot );

			robot.SetVelocity( VelocityCommandType::LINEAR_ANGULAR_DEGREE, behavior.options.manual_velocity.vLinear, behavior.options.manual_velocity.vAngular );

			m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );

			CPointDouble posRobotScreen = robot.Position();
			m_ground.GroundToScreen( posRobotScreen );
			m_pDC->MoveTo( posRobotScreen.Integer() );
			double dt = behavior.options.manual_velocity.time/20;
			for( int i=0 ; i<20 ; i++ )
			{
				robot.RobotSimulationMove( dt );
				//robot.RobotEnemySimulationMove(dt);
				CPointDouble posRobotScreen = robot.Position();
				m_ground.GroundToScreen( posRobotScreen );
				m_pDC->LineTo( posRobotScreen.Integer() );
			}

			robot.SetState( OBJECT_STATE_NOT_EXIST );
			robotDraw.DrawBody( m_pDC, &m_ground, &robot );

			robot.SetState( OBJECT_STATE_REAL );
			robot.SetPosition( m_posRobotGUI );
			robot.SetOrientationDegree( direction );
				
			robotDraw.DrawBody( m_pDC, &m_ground, &robot );
		}
	}

	if( behavior.type == StrategyGUI_BehaviorType::Wait )
		// If the action is WAIT
	{
		strTitleInfo = _T(" > Wait");

		CPoint posVelocityUI( 530, 305 );

		CRect rectErrorBackground = CRect(0,0,100,65) + posVelocityUI;
		rectErrorBackground.InflateRect(2,2,2,2);
		m_pDC->SelectPen( RGB(64,64,128), PS_SOLID, 1 );
		m_pDC->SelectBrush( RGB(16,16,32) );
		m_pDC->Rectangle( rectErrorBackground );

		CRect rectVelocityTitle = CRect(0,0,110,20) + posVelocityUI;
		rectVelocityTitle.DeflateRect(3,3,3,3);
		m_pDC->SetTextColor( RGB( 255,255,255 ) );
		m_pDC->DrawText( _T("Wait Time Set"), rectVelocityTitle, DT_CENTER );


		m_pDC->SelectPen( RGB(0,255,0), PS_SOLID, 1 );
		m_pDC->SelectBrush( false );

		CRect button( 0, 0, 13, 7 );

		{
			COLORREF colorButton = RGB(0,255,0);
			COLORREF colorFrame = RGB(32,32,192);
			CPoint posOption = posVelocityUI + CPoint(5,25);
				
			CRect buttonVelocityTimeUp   = button + posOption + CPoint(72,10);
			DrawRectArrowButton( buttonVelocityTimeUp  , _T("up")  , colorButton );

			CRect buttonVelocityTimeDown = button + posOption + CPoint(72,20);
			DrawRectArrowButton( buttonVelocityTimeDown, _T("down"), colorButton );

			CRect rectVelocityTime       = CRect(0,0,90,35) + posOption;
			m_pDC->SelectPen( colorFrame, PS_SOLID, 1 );
			m_pDC->Rectangle( rectVelocityTime );

			rectVelocityTime.DeflateRect( 3,3,3+19,3 );
			//m_pDC->Rectangle( rectVelocityTime );

			m_pDC->SetTextColor( RGB( 255, 255, 255 ) );
			m_pDC->DrawText( _T("Time"), rectVelocityTime, DT_LEFT );
			CString tmp;
			tmp.Format(_T("\n%.1lf s"), behavior.options.wait.time );
			m_pDC->DrawText( tmp, rectVelocityTime, DT_RIGHT );

			m_rectVelocityButton[4] = buttonVelocityTimeUp;
			m_rectVelocityButton[5] = buttonVelocityTimeDown;
		}
	}
}

void CPropertyPageStrategyGUI::DrawDisplay()
{
	static int countDraw = 0;
	countDraw++;

	EnterCriticalSection(&m_critPropertyPageStrategyGUI);
	
	m_pDC->FillSolidRect(0, 0, m_pDC->Width(), m_pDC->Height(), RGB(0,0,0) );

	m_pDC->SetBkMode( TRANSPARENT );


	//m_ground.Draw( m_pDC, RGB(255,255,255), true, false );
	m_dcFitness_share.Copy(m_pDC);



	// Draw the ball
	{
		CPointDouble pos = m_posBallClink_screen;
		
		double t = (double)(countDraw%5000)/2500;

		double push_direction;
		
		if( t < 1 )
			push_direction = t*360-90;
		else
			push_direction = -t*360-90;

		CPointDouble d_pos;
		double push_distance = 0.04;
		d_pos.x = cos( push_direction*M_PI/180.0 ) * push_distance;
		d_pos.y = sin( push_direction*M_PI/180.0 ) * push_distance;

		m_posBallClink_screen = m_posBallClink_screen + d_pos;

		m_pDC->SelectPen( RGB(255,0,0), PS_SOLID, 1 );
		m_pDC->SelectBrush( RGB(255,128,0) );
		int ball_r = 3;
		m_pDC->Circle( (int)m_posBallClink_screen.x, (int)m_posBallClink_screen.y, ball_r, true );
	}

	CString strTitle;
	CRect rectTitle( 30, 15, 640-30, 30 );
	COLORREF colorTitle = RGB(255,255,255);
	//m_pDC->SelectPen( RGB(64,64,128), PS_SOLID, 1 );
	//m_pDC->SelectBrush( RGB(32,32,64) );
	//m_pDC->Rectangle( rectTitle );

	CString strTitleInfo;
	CRect rectTitleInfo( 30, 30, 640-30, 80 );
	COLORREF colorTitleInfo = RGB(255,255,255);

	CString strMsg;
	CRect rectMsg( 120, 380, 640-20, 470 );
	COLORREF colorMsg = RGB(255,255,255);
	//m_pDC->SelectPen( RGB(64,64,128), PS_SOLID, 1 );
	//m_pDC->SelectBrush( RGB(16,16,32) );
	//m_pDC->Rectangle( rectMsg );


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Situation
	if( m_focusedList == StrategyGUI_List::Situation )
	{
		DrawDisplay_Situation( strTitle, strTitleInfo, strMsg );
	}

	// Situation : Ç×»ó Ãâ·Â
	int situationN = m_strategyGUI.GetSituationN();

	if( m_bShowAllSituation )
	{
		for( int situationID = 0 ; situationID < situationN ; situationID++ )
		{
			if( situationID == m_focusedSituationID )
				continue;

			CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( situationID );

			//if( m_bShowVerifySituation )
			{
				DrawSituation( situation );
			}
		}
	}

	// °¡Àå À§¿¡ Ãâ·ÂÇÏ±â À§ÇØ µû·Î ´Ù½Ã Ãâ·Â
	if( m_focusedSituationID != -1 )
	{
		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );
		CRectMouse rectSituationArea = m_rectSituationArea;

		if( m_focusedList != StrategyGUI_List::Situation )
			rectSituationArea.SetColor( RGB(64,192,64) );

		DrawSituation( rectSituationArea );

		if( m_focusedList == StrategyGUI_List::Situation )
		{
			double ball_owner_distance = situation.condition.ball.owner_distance;
			m_ground.GroundToScreen( ball_owner_distance );
		
			m_pDC->SelectPen( RGB(255,0,0), PS_DOT, 1 );
			m_pDC->Circle( (int)m_posBallClink_screen.x, (int)m_posBallClink_screen.y, (int)ball_owner_distance, true );
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SituationRoleAssign
	if( m_focusedList == StrategyGUI_List::RoleAssign && m_focusedSituationID != -1 )
	{
		DrawDisplay_RoleAssign( strTitle, strTitleInfo, strMsg );
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Role
	if( m_focusedList == StrategyGUI_List::Role && m_focusedRoleID >= 0 )
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Behavior
	if( m_focusedList == StrategyGUI_List::Behavior && m_focusedRoleID >= 0 && m_focusedBehaviorID >= 0 )
	{
		DrawDisplay_Behavior( strTitle, strTitleInfo, strMsg );
	}

	m_pDC->SetTextColor( colorTitle );
	m_pDC->DrawText( strTitle, rectTitle, DT_LEFT );

	m_pDC->SetTextColor( colorTitleInfo );
	m_pDC->DrawText( strTitleInfo, rectTitleInfo, DT_LEFT );

	m_pDC->SetTextColor( colorMsg );
	m_pDC->DrawText( strMsg, rectMsg, DT_LEFT );

	LeaveCriticalSection(&m_critPropertyPageStrategyGUI);
}

void CPropertyPageStrategyGUI::DisplayPositionErrorUI( double error, bool bBall )
{
	CPoint posErrorUI( 510, 272 );

	CRect rectErrorBackground = CRect(0,0,120,100) + posErrorUI;
	//rectErrorBackground.InflateRect(2,2,2,2);
	m_pDC->SelectPen( RGB(64,64,128), PS_SOLID, 1 );
	m_pDC->SelectBrush( RGB(16,16,32) );
	m_pDC->Rectangle( rectErrorBackground );

	CRect rectPositionTitle = CRect(0,0,120,20) + posErrorUI;
	rectPositionTitle.DeflateRect(4,4,4,4);
	m_pDC->SetTextColor( RGB( 255,255,255 ) );
	m_pDC->DrawText( _T("Tolerance of a moving target"), rectPositionTitle, DT_CENTER );

	CGround ground = m_ground;
	ground.SetScreenRatio( 540 );

	CRobot robot;
	robot.SetGround( ground );
	robot.SetState( OBJECT_STATE_NOT_EXIST );
	

	CPoint posError( 40, 50 );
	posError = posError + posErrorUI;
	
	CPointDouble pos = posError;
	ground.ScreenToGround( pos );
	robot.SetPosition( pos );
	robot.SetOrientationDegree( 26.65 );


	CRobotDraw robotDraw;
	robotDraw.DrawBody( m_pDC, &ground, &robot );

	double error_screen = error;
	ground.GroundToScreen( error_screen );

	double robot_r = 0.04;
	ground.GroundToScreen( robot_r );

	int size = (int)error_screen;
	m_pDC->SelectPen( RGB(200,32,32), PS_SOLID, 1 );
	m_pDC->SelectBrush( false );
	m_pDC->Circle( posError.x, posError.y, size, true );
				

	m_pDC->MoveTo( posError );
	m_pDC->LineTo( posError.x + size, posError.y );

	m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );

	m_pDC->MoveTo( posError.x       , posError.y + (int)robot_r + 8 );
	m_pDC->LineTo( posError.x + size, posError.y + (int)robot_r + 8 );

	m_pDC->MoveTo( posError.x       , posError.y + (int)robot_r + 8 - 2 );
	m_pDC->LineTo( posError.x       , posError.y + (int)robot_r + 8 + 3 );

	m_pDC->MoveTo( posError.x + size, posError.y + (int)robot_r + 8 - 2 );
	m_pDC->LineTo( posError.x + size, posError.y + (int)robot_r + 8 + 3 );

	for( int y=posError.y ; y<=posError.y + (int)robot_r + 8 ; y+=3 )
	{
		m_pDC->SetPixel( posError.x, y, RGB(255,0,0));
		m_pDC->SetPixel( posError.x+size, y, RGB(255,0,0));
	}
	
	m_pDC->SetTextColor( RGB( 0,255,255 ) );
	CRect rectError = CRect( 0, 0, 50, 14 ) + posError + CPoint( 0, (int)robot_r+12 );
	
	CString strError;
	strError.Format(_T("%.3lfm"), error );
	m_pDC->DrawText( strError, rectError, DT_CENTER );

	//m_pDC->SetTextColor( RGB( 255,255,255 ) );
	//CRect rectErrorTitle = CRect( 0, 0, 90, 14 ) + posError + CPoint( -20, (int)robot_r+12+15 );
	//m_pDC->DrawText( _T("À§Ä¡ Çã¿ë ¿ÀÂ÷"), rectErrorTitle, DT_CENTER );

	//m_pDC->Rectangle( rectError );


	int button_size = rectError.Height()/2;
	CPoint posErrorButton = rectError.TopLeft() + CPoint(-button_size, button_size);

	CRect rectErrorButtonL = CRect( 0, 0, button_size-1, (button_size-1)*2-1 ) + posErrorButton + CPoint( -2, -button_size+2 );
	DrawRectArrowButton( rectErrorButtonL, _T("left"), RGB(0,255,0) );
	rectErrorButtonL.InflateRect( 2, 2, 2, 2 );
	//m_pDC->Rectangle( rectErrorButtonL );
	m_rectErrorButtonL = rectErrorButtonL;

	CRect rectErrorButtonR = CRect( 0, 0, button_size-1, (button_size-1)*2-1 ) + posErrorButton + CPoint( 2 + rectError.Width() + button_size, -button_size+2 );
	DrawRectArrowButton( rectErrorButtonR, _T("right"), RGB(0,255,0) );
	rectErrorButtonR.InflateRect( 2, 2, 2, 2 );
	//m_pDC->Rectangle( rectErrorButtonR );
	m_rectErrorButtonR = rectErrorButtonR;



	/*

	CPoint posBall = posError + CPoint(50, -50);
	
	double ball_r = 0.047/2.0;
	ground.GroundToScreen( ball_r ); 

	int size_r = (int)ball_r;

	//m_rectBallDestination = CRect( posBall.x - size_r, posBall.y - size_r, posBall.x + size_r, posBall.y + size_r );


	if( bBall )
	{
		m_pDC->SelectPen( RGB(255,32,0), PS_SOLID, 1 );
		m_pDC->SelectBrush( RGB(255,64,0) );
		m_pDC->Circle( posBall.x, posBall.y, size_r, true );

		CRect rectBallTitle = CRect( 0, 0, 110, 20 )+posBall+CPoint(-size_r-60, -7);
		m_pDC->SetTextColor( RGB( 255,255,255 ) );
		m_pDC->DrawText( _T("¸ñÇ¥:°ø"), rectBallTitle, DT_LEFT );	
		//m_pDC->Rectangle( rectBallTitle );
	}
	else
	{
		m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
		//m_pDC->SelectBrush( RGB(255,255,0) );
		//m_pDC->Square( posBall.x, posBall.y, size_r, true );

			{
				int size1 = size_r;
				int size2 = size_r/2;
				m_pDC->MoveTo( posBall.x - size1        , posBall.y - size1         );
				m_pDC->LineTo( posBall.x - size1 + size2, posBall.y - size1         );
				m_pDC->MoveTo( posBall.x - size1        , posBall.y - size1         );
				m_pDC->LineTo( posBall.x - size1        , posBall.y - size1 + size2 );

				m_pDC->MoveTo( posBall.x + size1        , posBall.y - size1         );
				m_pDC->LineTo( posBall.x + size1 - size2, posBall.y - size1         );
				m_pDC->MoveTo( posBall.x + size1        , posBall.y - size1         );
				m_pDC->LineTo( posBall.x + size1        , posBall.y - size1 + size2 );

				m_pDC->MoveTo( posBall.x - size1        , posBall.y + size1         );
				m_pDC->LineTo( posBall.x - size1 + size2, posBall.y + size1         );
				m_pDC->MoveTo( posBall.x - size1        , posBall.y + size1         );
				m_pDC->LineTo( posBall.x - size1        , posBall.y + size1 - size2 );

				m_pDC->MoveTo( posBall.x + size1        , posBall.y + size1         );
				m_pDC->LineTo( posBall.x + size1 - size2, posBall.y + size1         );
				m_pDC->MoveTo( posBall.x + size1        , posBall.y + size1         );
				m_pDC->LineTo( posBall.x + size1        , posBall.y + size1 - size2 );

				int size3 = size2+2;
				m_pDC->MoveTo( posBall.x        , posBall.y                 );
				m_pDC->LineTo( posBall.x + size3, posBall.y                 );

				m_pDC->MoveTo( posBall.x        , posBall.y                 );
				m_pDC->LineTo( posBall.x - size3, posBall.y                 );

				m_pDC->MoveTo( posBall.x        , posBall.y                 );
				m_pDC->LineTo( posBall.x        , posBall.y + size3         );

				m_pDC->MoveTo( posBall.x        , posBall.y                 );
				m_pDC->LineTo( posBall.x        , posBall.y - size3         );

			}


		CRect rectBallTitle = CRect( 0, 0, 110, 20 )+posBall+CPoint(-size_r-60, -7);
		m_pDC->SetTextColor( RGB( 255,255,255 ) );
		m_pDC->DrawText( _T("¸ñÇ¥:°íÁ¤"), rectBallTitle, DT_LEFT );	
	}


	m_pDC->SelectPen( RGB(0,0,255), PS_SOLID, 1 );
	m_pDC->SelectBrush( false );
	m_pDC->MoveTo( posError );
	m_pDC->LineTo( posBall );
	{
		int size = 5;
		for( int j=0 ; j<size ; j++ )
		{
			for( int i=j ; i<size ; i++ )
			{
				int x = posBall.x + i - size + 1;
				int y = posBall.y + j;
				m_pDC->SetPixel( x, y, RGB(0,0,255) );
			}
		}
	}
	*/
}

void CPropertyPageStrategyGUI::DisplayBallDestination( bool bBall )
{
	//m_rectBallDestination = CRect( posBall.x - size_r, posBall.y - size_r, posBall.x + size_r, posBall.y + size_r );


	CPoint posGUI( 510, 60 );

	CRect rectBallDestination = CRect(0,0,120,48) + posGUI;
	//rectBallDestination.InflateRect(2,2,2,2);
	m_pDC->SelectPen( RGB(64,64,128), PS_SOLID, 1 );
	m_pDC->SelectBrush( RGB(16,16,32) );
	m_pDC->Rectangle( rectBallDestination );

	CRect rectTitle = CRect(0,0,120,20) + posGUI;
	rectTitle.DeflateRect(4,4,4,4);
	m_pDC->SetTextColor( RGB( 255,255,255 ) );
	m_pDC->DrawText( _T("Moving Target Pos"), rectTitle, DT_CENTER );


	CPoint posMark = CPoint(15,32) + posGUI;
	CString strState;

	if( bBall )
	{
		m_pDC->SelectPen( RGB(255,0,0), PS_SOLID, 1 );
		m_pDC->SelectBrush( RGB(255,128,0) );
		int r = 3;
		m_pDC->Circle( posMark.x, posMark.y, r, true );

		m_pDC->SelectPen( RGB(255,128,0), PS_SOLID, 1 );

		strState = _T("ball pos");
	}
	else
	{
		m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );

		strState = _T("fixed pos");
	}


	{
		int size1 = 5;
		int size2 = 3;
		m_pDC->MoveTo( posMark.x - size1        , posMark.y - size1         );
		m_pDC->LineTo( posMark.x - size1 + size2, posMark.y - size1         );
		m_pDC->MoveTo( posMark.x - size1        , posMark.y - size1         );
		m_pDC->LineTo( posMark.x - size1        , posMark.y - size1 + size2 );
		
		m_pDC->MoveTo( posMark.x + size1        , posMark.y - size1         );
		m_pDC->LineTo( posMark.x + size1 - size2, posMark.y - size1         );
		m_pDC->MoveTo( posMark.x + size1        , posMark.y - size1         );
		m_pDC->LineTo( posMark.x + size1        , posMark.y - size1 + size2 );
		
		m_pDC->MoveTo( posMark.x - size1        , posMark.y + size1         );
		m_pDC->LineTo( posMark.x - size1 + size2, posMark.y + size1         );
		m_pDC->MoveTo( posMark.x - size1        , posMark.y + size1         );
		m_pDC->LineTo( posMark.x - size1        , posMark.y + size1 - size2 );
		
		m_pDC->MoveTo( posMark.x + size1        , posMark.y + size1         );
		m_pDC->LineTo( posMark.x + size1 - size2, posMark.y + size1         );
		m_pDC->MoveTo( posMark.x + size1        , posMark.y + size1         );
		m_pDC->LineTo( posMark.x + size1        , posMark.y + size1 - size2 );

		int size3 = 4;
		m_pDC->MoveTo( posMark.x        , posMark.y                 );
		m_pDC->LineTo( posMark.x + size3, posMark.y                 );

		m_pDC->MoveTo( posMark.x        , posMark.y                 );
		m_pDC->LineTo( posMark.x - size3, posMark.y                 );

		m_pDC->MoveTo( posMark.x        , posMark.y                 );
		m_pDC->LineTo( posMark.x        , posMark.y + size3         );

		m_pDC->MoveTo( posMark.x        , posMark.y                 );
		m_pDC->LineTo( posMark.x        , posMark.y - size3         );

	}

	{
		m_pDC->SelectPen( RGB(0,255,0), PS_SOLID, 1 );
		m_pDC->SelectBrush( RGB(0,32,0) );
		m_pDC->SetTextColor( RGB(0,255,0) );

		CRect rectState = CRect(0,0,75,20) + CPoint(15, -9) + posMark;
		m_pDC->Rectangle( rectState );
		m_pDC->DrawText( strState, rectState, DT_CENTER|DT_VCENTER|DT_SINGLELINE );

		m_rectBallDestination = rectState;
	}


	/*
	if( bBall )
	{
		m_pDC->DrawText( _T("¸ñÇ¥:°ø1"), rectBallDestination, DT_CENTER );
	}
	else
	{
		m_pDC->DrawText( _T("¸ñÇ¥:°íÁ¤1"), rectBallDestination, DT_CENTER );
	}
	*/
}

void CPropertyPageStrategyGUI::DisplayPosDirection( bool bPosDirection, CString strTitle )
{
	//m_rectBallDestination = CRect( posBall.x - size_r, posBall.y - size_r, posBall.x + size_r, posBall.y + size_r );


	CPoint posGUI( 510, 110 );

	CRect rectBallDestination = CRect(0,0,120,48) + posGUI;
	//rectBallDestination.InflateRect(2,2,2,2);
	m_pDC->SelectPen( RGB(64,64,128), PS_SOLID, 1 );
	m_pDC->SelectBrush( RGB(16,16,32) );
	m_pDC->Rectangle( rectBallDestination );

	CRect rectTitle = CRect(0,0,120,20) + posGUI;
	rectTitle.DeflateRect(4,4,4,4);
	m_pDC->SetTextColor( RGB( 255,255,255 ) );
	m_pDC->DrawText( strTitle, rectTitle, DT_CENTER );


	CPoint posMark = CPoint(15,32) + posGUI;
	CString strState;

	if( bPosDirection )
	{
		m_pDC->SelectPen( RGB(255,0,0), PS_SOLID, 1 );
		m_pDC->SelectBrush( RGB(255,128,0) );
		int r = 3;
		//m_pDC->Circle( posMark.x, posMark.y, r, true );

		m_pDC->SelectPen( RGB(255,128,0), PS_SOLID, 1 );

		strState = _T("fixed pos");




			{
				CPoint posDirectionMarker = CPoint(0, 0) + posMark;
				//CPointDouble posDirection_screen = behavior.options.posDirection;
				//m_ground.GroundToScreen( posDirection_screen );

				m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
				m_pDC->SelectBrush( false );

				int size = 3;
				m_pDC->MoveTo( posDirectionMarker );
				m_pDC->LineTo( posDirectionMarker + CPoint(0,size) );
				m_pDC->MoveTo( posDirectionMarker );
				m_pDC->LineTo( posDirectionMarker + CPoint(0,-size) );
				m_pDC->MoveTo( posDirectionMarker );
				m_pDC->LineTo( posDirectionMarker + CPoint(size,0) );
				m_pDC->MoveTo( posDirectionMarker );
				m_pDC->LineTo( posDirectionMarker + CPoint(-size,0) );

				int r = 6;
				m_pDC->Circle( posDirectionMarker.x, posDirectionMarker.y, r, true );
			}

	}
	else
	{
		m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );

		strState = _T("absolute direction");
	}

	/*
	{
		int size1 = 5;
		int size2 = 3;
		m_pDC->MoveTo( posMark.x - size1        , posMark.y - size1         );
		m_pDC->LineTo( posMark.x - size1 + size2, posMark.y - size1         );
		m_pDC->MoveTo( posMark.x - size1        , posMark.y - size1         );
		m_pDC->LineTo( posMark.x - size1        , posMark.y - size1 + size2 );
		
		m_pDC->MoveTo( posMark.x + size1        , posMark.y - size1         );
		m_pDC->LineTo( posMark.x + size1 - size2, posMark.y - size1         );
		m_pDC->MoveTo( posMark.x + size1        , posMark.y - size1         );
		m_pDC->LineTo( posMark.x + size1        , posMark.y - size1 + size2 );
		
		m_pDC->MoveTo( posMark.x - size1        , posMark.y + size1         );
		m_pDC->LineTo( posMark.x - size1 + size2, posMark.y + size1         );
		m_pDC->MoveTo( posMark.x - size1        , posMark.y + size1         );
		m_pDC->LineTo( posMark.x - size1        , posMark.y + size1 - size2 );
		
		m_pDC->MoveTo( posMark.x + size1        , posMark.y + size1         );
		m_pDC->LineTo( posMark.x + size1 - size2, posMark.y + size1         );
		m_pDC->MoveTo( posMark.x + size1        , posMark.y + size1         );
		m_pDC->LineTo( posMark.x + size1        , posMark.y + size1 - size2 );

		int size3 = 4;
		m_pDC->MoveTo( posMark.x        , posMark.y                 );
		m_pDC->LineTo( posMark.x + size3, posMark.y                 );

		m_pDC->MoveTo( posMark.x        , posMark.y                 );
		m_pDC->LineTo( posMark.x - size3, posMark.y                 );

		m_pDC->MoveTo( posMark.x        , posMark.y                 );
		m_pDC->LineTo( posMark.x        , posMark.y + size3         );

		m_pDC->MoveTo( posMark.x        , posMark.y                 );
		m_pDC->LineTo( posMark.x        , posMark.y - size3         );

	}
	*/

	{
		m_pDC->SelectPen( RGB(0,255,0), PS_SOLID, 1 );
		m_pDC->SelectBrush( RGB(0,32,0) );
		m_pDC->SetTextColor( RGB(0,255,0) );

		CRect rectState = CRect(0,0,75,20) + CPoint(15, -9) + posMark;
		m_pDC->Rectangle( rectState );
		m_pDC->DrawText( strState, rectState, DT_CENTER|DT_VCENTER|DT_SINGLELINE );

		m_rectPosDirection = rectState;
	}
}

void CPropertyPageStrategyGUI::DisplayPosApproach( bool bPosApproach, CString strTitle )
{
	//m_rectBallDestination = CRect( posBall.x - size_r, posBall.y - size_r, posBall.x + size_r, posBall.y + size_r );


	CPoint posGUI( 510, 60 );

	CRect rectBallDestination = CRect(0,0,120,48) + posGUI;
	//rectBallDestination.InflateRect(2,2,2,2);
	m_pDC->SelectPen( RGB(64,64,128), PS_SOLID, 1 );
	m_pDC->SelectBrush( RGB(16,16,32) );
	m_pDC->Rectangle( rectBallDestination );

	CRect rectTitle = CRect(0,0,120,20) + posGUI;
	rectTitle.DeflateRect(4,4,4,4);
	m_pDC->SetTextColor( RGB( 255,255,255 ) );
	m_pDC->DrawText( strTitle, rectTitle, DT_CENTER );


	CPoint posMark = CPoint(15,32) + posGUI;
	CString strState;

	if( bPosApproach )
	{
		m_pDC->SelectPen( RGB(255,0,0), PS_SOLID, 1 );
		m_pDC->SelectBrush( RGB(255,128,0) );
		int r = 3;
		//m_pDC->Circle( posMark.x, posMark.y, r, true );

		m_pDC->SelectPen( RGB(255,128,0), PS_SOLID, 1 );

		strState = _T("fixed pos");




			{
				CPoint posDirectionMarker = CPoint(0, 0) + posMark;
				//CPointDouble posDirection_screen = behavior.options.posDirection;
				//m_ground.GroundToScreen( posDirection_screen );

				m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
				m_pDC->SelectBrush( false );

				int size = 3;
				m_pDC->MoveTo( posDirectionMarker );
				m_pDC->LineTo( posDirectionMarker + CPoint(0,size) );
				m_pDC->MoveTo( posDirectionMarker );
				m_pDC->LineTo( posDirectionMarker + CPoint(0,-size) );
				m_pDC->MoveTo( posDirectionMarker );
				m_pDC->LineTo( posDirectionMarker + CPoint(size,0) );
				m_pDC->MoveTo( posDirectionMarker );
				m_pDC->LineTo( posDirectionMarker + CPoint(-size,0) );

				int r = 6;
				m_pDC->Circle( posDirectionMarker.x, posDirectionMarker.y, r, true );
			}

	}
	else
	{
		m_pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );

		strState = _T("absolute direction");
	}
	
	{
		m_pDC->SelectPen( RGB(0,255,0), PS_SOLID, 1 );
		m_pDC->SelectBrush( RGB(0,32,0) );
		m_pDC->SetTextColor( RGB(0,255,0) );

		CRect rectState = CRect(0,0,75,20) + CPoint(15, -9) + posMark;
		m_pDC->Rectangle( rectState );
		m_pDC->DrawText( strState, rectState, DT_CENTER|DT_VCENTER|DT_SINGLELINE );

		m_rectPosApproach = rectState;
	}
}

void CPropertyPageStrategyGUI::DrawArrow(CPointDouble posBegin, CPointDouble posEnd, double orientation, double size_length, double size_angle, COLORREF color ) 
{
	double arrow_size = size_length;
	double arrow_width = size_angle;
	CPointDouble p0 = posEnd;
	CPointDouble p1;
	p1.x = p0.x + cos( (orientation+arrow_width+180) * M_PI / 180 ) * arrow_size;
	p1.y = p0.y + sin( (orientation+arrow_width+180) * M_PI / 180 ) * arrow_size;
	CPointDouble p2;
	p2.x = p0.x + cos( (orientation-arrow_width+180) * M_PI / 180 ) * arrow_size;
	p2.y = p0.y + sin( (orientation-arrow_width+180) * M_PI / 180 ) * arrow_size;


	CPointDouble posBegin_screen = posBegin;
	m_ground.GroundToScreen( posBegin_screen );

	CPointDouble posEnd_screen = posEnd;
	m_ground.GroundToScreen( posEnd_screen );



	int width  = abs(posEnd_screen.Integer().x - posBegin_screen.Integer().x);
	int height = abs(posEnd_screen.Integer().y - posBegin_screen.Integer().y);

	int x_sign = 1;
	if( posEnd_screen.Integer().x < posBegin_screen.Integer().x )
		x_sign = -1;

	int y_sign = 1;
	if( posEnd_screen.Integer().y < posBegin_screen.Integer().y )
		y_sign = -1;

	for( int i = 0 ; i<=width ; i++)
	{
		for( int j = 0 ; j<=height ; j++ )
		{
			CPointDouble p(i*x_sign,j*y_sign);
			p = p + posBegin_screen;
			m_ground.ScreenToGround( p );

			double d = fabs( ccw( posEnd, posBegin, p ) / (posEnd-posBegin).Distance() );
			double d_line = 0.005;
			if( d <= d_line )
			{
				int c_r = (int)( (d_line - d)/d_line * GetRValue(color) );
				int c_g = (int)( (d_line - d)/d_line * GetGValue(color) );
				int c_b = (int)( (d_line - d)/d_line * GetBValue(color) );
				COLORREF dColor;
				dColor = RGB(c_r,c_g,c_b);
				m_pDC->SetPixel( (int)posBegin_screen.x + i*x_sign, (int)posBegin_screen.y + j*y_sign, dColor );
			}
			else
			{
				//m_pDC->SetPixel( (int)posBegin_screen.x + i*x_sign, (int)posBegin_screen.y + j*y_sign, RGB(255,255,0) );
			}
		}
	}


	int area = 10;
	for( int i=-area ; i<=area ; i++ )
	{
		for( int j=-area ; j<=area ; j++ )
		{
			CPointDouble p(i,j);
			p = p + posEnd_screen;
			m_ground.ScreenToGround( p );

			double r01 = ccw( p0, p1, p );
			double r12 = ccw( p1, p2, p );
			double r20 = ccw( p2, p0, p );

			if( r01 <= 0 && r12 <= 0 && r20 <= 0 )
			{
				m_pDC->SetPixel( (int)posEnd_screen.x + i, (int)posEnd_screen.y + j, color );
			}
			else
			{
				//m_pDC->SetPixel( posTest.x + i, posTest.y + j, RGB(0,255,0) );				
			}

			double d = 0.003;
			if( r01 >  0 && r12 <= 0 && r20 <= 0 && r01/(p0-p1).Distance() < d)
			{
				int c_r = (int)( (d - r01/(p0-p1).Distance())/d * GetRValue(color) );
				int c_g = (int)( (d - r01/(p0-p1).Distance())/d * GetGValue(color) );
				int c_b = (int)( (d - r01/(p0-p1).Distance())/d * GetBValue(color) );
				COLORREF dColor;
				dColor = RGB(c_r,c_g,c_b);
				m_pDC->SetPixel( (int)posEnd_screen.x + i, (int)posEnd_screen.y + j, dColor );
			}

			if( r01 <= 0 && r12 >  0 && r20 <= 0 && r12/(p1-p2).Distance() < d)
			{
				int c_r = (int)( (d - r12/(p1-p2).Distance())/d * GetRValue(color) );
				int c_g = (int)( (d - r12/(p1-p2).Distance())/d * GetGValue(color) );
				int c_b = (int)( (d - r12/(p1-p2).Distance())/d * GetBValue(color) );
				COLORREF dColor;
				dColor = RGB(c_r,c_g,c_b);
				m_pDC->SetPixel( (int)posEnd_screen.x + i, (int)posEnd_screen.y + j, dColor );
			}

			if( r01 <= 0 && r12 <= 0 && r20 >  0 && r20/(p2-p0).Distance() < d)
			{
				int c_r = (int)( (d - r20/(p2-p0).Distance())/d * GetRValue(color) );
				int c_g = (int)( (d - r20/(p2-p0).Distance())/d * GetGValue(color) );
				int c_b = (int)( (d - r20/(p2-p0).Distance())/d * GetBValue(color) );
				COLORREF dColor;
				dColor = RGB(c_r,c_g,c_b);
				m_pDC->SetPixel( (int)posEnd_screen.x + i, (int)posEnd_screen.y + j, dColor );
			}

		}
	}
}

double CPropertyPageStrategyGUI::ccw(CPointDouble p1, CPointDouble p2, CPointDouble p3)
{
	//	p1.x p2.x p3.x
	//	p1.y p2.y p3.y

	return p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - p1.x*p3.y - p2.x*p1.y  - p3.x*p2.y;
}


void CPropertyPageStrategyGUI::DrawRectArrowButton( CRect rect, CString type, COLORREF color )
{
	m_pDC->SelectPen( color, PS_SOLID, 1 );

	int height = rect.Height();
	int width = rect.Width();
	int half_size;

	if( type == _T("up") || type == _T("down") )
	{
		if( height*2 < width+1 )
			width = height*2-1;
		else
		if( height*2 > width+1 )
			height = (width+1)/2;

		half_size = height;
	}
	if( type == _T("left") || type == _T("right") )
	{
		if( width*2 < height+1 )
			height = width*2-1;
		else
		if( width*2 > height+1 )
			width = (height+1)/2;

		half_size = width;
	}

	/*

	 *  *    **   **
	**  **    *   *

	up    : 1 2
	down  : 3 4
	left  : 1 3
	right : 2 4

	*/


	// 1
	if( type == _T("up") || type ==_T("left") )
	{
		CPoint posCenter = CPoint( half_size-1, half_size-1 ) + rect.TopLeft();
		for( int j=0 ; j<half_size ; j++ )
		{
			for( int i=0 ; i<=j ; i++ )
			{
				CPoint pos;					
				pos = posCenter + CPoint(-i,-half_size+j+1);
				m_pDC->SetPixel( pos, color );
			}
		}
	}

	// 2
	if( type == _T("up") || type ==_T("right") )
	{
		CPoint posCenter = CPoint( half_size-1, half_size-1 ) + rect.TopLeft();

		if( type == _T("right") )
			posCenter -= CPoint( half_size-1, 0 );

		for( int j=0 ; j<half_size ; j++ )
		{
			for( int i=0 ; i<=j ; i++ )
			{
				CPoint pos;					
				pos = posCenter + CPoint(i,-half_size+j+1);
				m_pDC->SetPixel( pos, color );
			}
		}
	}

	// 3
	if( type == _T("down") || type ==_T("left") )
	{
		CPoint posCenter = CPoint( half_size-1, half_size-1 ) + rect.TopLeft();

		if( type == _T("down") )
			posCenter -= CPoint( 0, half_size-1 );

		for( int j=0 ; j<half_size ; j++ )
		{
			for( int i=0 ; i<=j ; i++ )
			{
				CPoint pos;					
				pos = posCenter + CPoint(-i,half_size-j-2+1);
				m_pDC->SetPixel( pos, color );
			}
		}
	}

	// 4
	if( type == _T("down") || type ==_T("right") )
	{
		CPoint posCenter = CPoint( half_size-1, half_size-1 ) + rect.TopLeft();

		if( type == _T("right") )
			posCenter -= CPoint( half_size-1, 0 );

		if( type == _T("down") )
			posCenter -= CPoint( 0, half_size-1 );

		for( int j=0 ; j<half_size ; j++ )
		{
			for( int i=0 ; i<=j ; i++ )
			{
				CPoint pos;					
				pos = posCenter + CPoint(i,half_size-j-2+1);
				m_pDC->SetPixel( pos, color );
			}
		}
	}
}

MouseCapture::Enum CPropertyPageStrategyGUI::DisplayLButtonDown( UINT nFlags, CPoint point )
{
	if( m_focusedList == StrategyGUI_List::Situation && m_focusedSituationID >= 0 )
		m_rectSituationArea.MouseLDown( point );

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

MouseCapture::Enum CPropertyPageStrategyGUI::DisplayLButtonUp( UINT nFlags, CPoint point )
{
	if( m_bLButton )
	{
		if( m_focusedList == StrategyGUI_List::Behavior )
		{
			if( m_focusedRoleID >= 0 && m_focusedBehaviorID >= 0 )
			{
				CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );
				CStrategyGUI::Behavior behavior = role.vecBehavior[m_focusedBehaviorID];

				if( behavior.type == StrategyGUI_BehaviorType::Goalkeep )
				{
					if( m_rectGK_clear_ball_speed_up.Inside( CPointDouble(point) ) )
					{
						behavior.options.goalkeep.clear_ball_speed += 0.005;
					}
					else
					if( m_rectGK_clear_ball_speed_down.Inside( CPointDouble(point) ) )
					{
						behavior.options.goalkeep.clear_ball_speed = max( behavior.options.goalkeep.clear_ball_speed - 0.005, 0 );
					}
					else
					if( m_rectGK_clear_y_size_up.Inside( CPointDouble(point) ) )
					{
						behavior.options.goalkeep.clear_y_size += 0.01;
					}
					else
					if( m_rectGK_clear_y_size_down.Inside( CPointDouble(point) ) )
					{
						behavior.options.goalkeep.clear_y_size -= 0.01;
					}
					else
					if( m_rectGK_clear_x_pos_left.Inside( CPointDouble(point) ) )
					{
						behavior.options.goalkeep.clear_x_size -= 0.01;
					}
					else
					if( m_rectGK_clear_x_pos_right.Inside( CPointDouble(point) ) )
					{
						behavior.options.goalkeep.clear_x_size += 0.01;
					}
					else
					if( m_rectGK_y_size_up.Inside( CPointDouble(point) ) )
					{
						behavior.options.goalkeep.y_size += 0.01;
					}
					else
					if( m_rectGK_y_size_down.Inside( CPointDouble(point) ) )
					{
						behavior.options.goalkeep.y_size -= 0.01;
					}
					else
					if( m_rectGK_x_pos_left.Inside( CPointDouble(point) ) )
					{
						behavior.options.goalkeep.x_pos -= 0.005;
					}
					else
					if( m_rectGK_x_pos_right.Inside( CPointDouble(point) ) )
					{
						behavior.options.goalkeep.x_pos += 0.005;
					}
				}

				if( behavior.type == StrategyGUI_BehaviorType::Defense_Wall )
				{
					if( m_rectGK_clear_ball_speed_up.Inside( CPointDouble(point) ) )
					{
						behavior.options.defense_wall.clear_ball_speed += 0.005;
					}
					else
					if( m_rectGK_clear_ball_speed_down.Inside( CPointDouble(point) ) )
					{
						behavior.options.defense_wall.clear_ball_speed = max( behavior.options.defense_wall.clear_ball_speed - 0.005, 0 );
					}
					else
					if( m_rectGK_clear_x_pos_left.Inside( CPointDouble(point) ) )
					{
						behavior.options.defense_wall.clear_x_size -= 0.01;
					}
					else
					if( m_rectGK_clear_x_pos_right.Inside( CPointDouble(point) ) )
					{
						behavior.options.defense_wall.clear_x_size += 0.01;
					}
					else
					{
						CPointDouble pos = point;
						m_ground.ScreenToGround( pos );

						pos.x = (int)((pos.x+0.005)*100) / 100.0;
						pos.y = (int)((pos.y+0.005)*100) / 100.0;

						behavior.options.defense_wall.posA = pos;
					}
				}

				if( behavior.type == StrategyGUI_BehaviorType::Kick_B )
				{
					CPointDouble pos = point;
					m_ground.ScreenToGround( pos );

					pos.x = (int)((pos.x+0.005)*100) / 100.0;
					pos.y = (int)((pos.y+0.005)*100) / 100.0;

					behavior.options.kick_B.posA = pos;
				}

				if( behavior.type == StrategyGUI_BehaviorType::Kick_A )
				{
					if( m_rectErrorButtonL.Inside( CPointDouble(point) ) )
					{
						behavior.options.kick_A.destination.error = max( 0.005, behavior.options.kick_A.destination.error-0.005 );
					}
					else
					if( m_rectErrorButtonR.Inside( CPointDouble(point) ) )
					{
						behavior.options.kick_A.destination.error = min( 0.10, behavior.options.kick_A.destination.error+0.005 );
					}
					else
					if( m_rectPosDirection.Inside( CPointDouble(point) ) )
					{
						behavior.options.kick_A.direction.bPosDirection = !behavior.options.kick_A.direction.bPosDirection;
					}
					else
					if( m_rectBallDestination.Inside( CPointDouble(point) ) )
					{
						behavior.options.kick_A.destination.bBall = !behavior.options.kick_A.destination.bBall;
					}
					else
					{
						CPointDouble pos = point;
						m_ground.ScreenToGround( pos );

						CPointDouble posBall = m_posBallClink_screen;
						m_ground.ScreenToGround( posBall );

						if( behavior.options.kick_A.destination.bBall )
						{
							m_posBallClink_screen = point;
						}
						else
						{
							behavior.options.kick_A.destination.pos = pos;
						}
					}
				}

				if( behavior.type == StrategyGUI_BehaviorType::MoveTo )
				{
					if( m_rectErrorButtonL.Inside( CPointDouble(point) ) )
					{
						behavior.options.move_to.destination.error = max( 0.005, behavior.options.move_to.destination.error-0.005 );
					}
					else
					if( m_rectErrorButtonR.Inside( CPointDouble(point) ) )
					{
						behavior.options.move_to.destination.error = min( 0.10, behavior.options.move_to.destination.error+0.005 );
					}
					else
					if( m_rectBallDestination.Inside( CPointDouble(point) ) )
					{
						behavior.options.move_to.destination.bBall = !behavior.options.move_to.destination.bBall;
					}
					else
					{
						CPointDouble pos = point;
						m_ground.ScreenToGround( pos );

						CPointDouble posBall = m_posBallClink_screen;
						m_ground.ScreenToGround( posBall );

						if( behavior.options.move_to.destination.bBall )
						{
							m_posBallClink_screen = point;
						}
						else
						{
							behavior.options.move_to.destination.pos = pos;
						}
					}
				}

				if( behavior.type == StrategyGUI_BehaviorType::Velocity )
				{
					if( m_rectVelocityButton[0].Inside( CPointDouble(point) ) )
					{
						//behavior.options.manual_velocity.vLinear = behavior.options.manual_velocity.vLinear + 0.05;
						behavior.options.manual_velocity.vLinear = min( 4.0, behavior.options.manual_velocity.vLinear + 0.05 );
					}
					else
					if( m_rectVelocityButton[1].Inside( CPointDouble(point) ) )
					{
						//behavior.options.manual_velocity.vLinear = behavior.options.manual_velocity.vLinear - 0.05;
						behavior.options.manual_velocity.vLinear = max( -4.0, behavior.options.manual_velocity.vLinear - 0.05 );
					}
					else
					if( m_rectVelocityButton[2].Inside( CPointDouble(point) ) )
					{
						//behavior.options.manual_velocity.vAngular = behavior.options.manual_velocity.vAngular + 90;
						behavior.options.manual_velocity.vAngular = min( 7200, behavior.options.manual_velocity.vAngular + 90 );
					}
					else
					if( m_rectVelocityButton[3].Inside( CPointDouble(point) ) )
					{
						//behavior.options.manual_velocity.vAngular = behavior.options.manual_velocity.vAngular - 90;
						behavior.options.manual_velocity.vAngular = max( -7200, behavior.options.manual_velocity.vAngular - 90 );
					}
					else
					if( m_rectVelocityButton[4].Inside( CPointDouble(point) ) )
					{
						behavior.options.manual_velocity.time = behavior.options.manual_velocity.time + 0.5;
					}
					else
					if( m_rectVelocityButton[5].Inside( CPointDouble(point) ) )
					{
						behavior.options.manual_velocity.time = max( 0, behavior.options.manual_velocity.time - 0.5 );
					}
					else
					{
						CPointDouble pos = point;
						m_ground.ScreenToGround( pos );

						m_posRobotGUI = pos;
					}
				}

				if( behavior.type == StrategyGUI_BehaviorType::Wait )
				{
					if( m_rectVelocityButton[4].Inside( CPointDouble(point) ) )
					{
						behavior.options.wait.time = behavior.options.wait.time + 0.5;
					}
					else
					if( m_rectVelocityButton[5].Inside( CPointDouble(point) ) )
					{
						behavior.options.wait.time = max( 0, behavior.options.wait.time - 0.5 );
					}
				}

				if( behavior.type == StrategyGUI_BehaviorType::OrientationTo )
				{
					if( m_rectPosDirection.Inside( CPointDouble(point) ) )
					{
						behavior.options.orientation.orientation.bPosDirection = !behavior.options.orientation.orientation.bPosDirection;
					}
					else
					{
						CPointDouble pos = point;
						m_ground.ScreenToGround( pos );

						m_posRobotGUI = pos;
					}
				}

				if( behavior.type == StrategyGUI_BehaviorType::Kick_C )
				{
					if( m_rectPosDirection.Inside( CPointDouble(point) ) )
					{
						behavior.options.kick_C.target.bPosDirection = !behavior.options.kick_C.target.bPosDirection;
					}
					else
					if( m_rectPosApproach.Inside( CPointDouble(point) ) )
					{
						behavior.options.kick_C.approach.bPosDirection = !behavior.options.kick_C.approach.bPosDirection;
					}
					else
					if( nFlags&MK_CONTROL )
					{
						CPointDouble pos = point;
						m_ground.ScreenToGround( pos );

						if( behavior.options.kick_C.approach.bPosDirection )
						{
							behavior.options.kick_C.approach.posDirection = pos;
						}
						else
						{
							CPointDouble posBall = m_posBallClink_screen;
							m_ground.ScreenToGround( posBall );

							behavior.options.kick_C.approach.direction = (double)(int)(pos - posBall).AngleDegree();
						}
					}
					else
					{
						CPointDouble pos = point;
						m_ground.ScreenToGround( pos );

						CPointDouble posBall = m_posBallClink_screen;
						m_ground.ScreenToGround( posBall );

						m_posBallClink_screen = point;
					}
				}


				/*
				{
					// °æ±âÀå Å¬¸¯

					if( bPosApproach )
					{
						CPointDouble pos = point;
						m_ground.ScreenToGround( pos );

						CPointDouble posBall = m_posBallClink_screen;
						m_ground.ScreenToGround( posBall );

						if( behavior.options.bPosApproach )
						{
							behavior.options.posApproach = pos;
						}
						else
						{
							behavior.options.orientationApproach = (double)(int)(pos - posBall).AngleDegree();
						}
					}

				}
				*/

				role.vecBehavior[ m_focusedBehaviorID ] = behavior;
				m_strategyGUI.UpdateRole( m_focusedRoleID, role );

				//CString tmp = m_strategyGUI.RoleOptionString( m_focusedRoleID, m_focusedBehaviorID );
				//m_listRoleDefinition.SetItemText( m_focusedBehaviorID, 1, tmp );
			}
		}
		else
		if( m_focusedList == StrategyGUI_List::RoleAssign )
		{
			if( m_focusedSituationID >= 0 && m_focusedSituationRoleID >= 0 )
			{
				CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );

				if( situation.role_assign.role[ m_focusedSituationRoleID ].assign.method == StrategyGUI_RoleAssignMethod::CloseToLocation
				 || situation.role_assign.role[ m_focusedSituationRoleID ].assign.method == StrategyGUI_RoleAssignMethod::GoodToKick )
				{
					CPointDouble pos = point;
					m_ground.ScreenToGround( pos );

					situation.role_assign.role[ m_focusedSituationRoleID ].assign.pos = pos;
					m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );
				}
				else
				if( situation.role_assign.role[ m_focusedSituationRoleID ].assign.method == StrategyGUI_RoleAssignMethod::CloseToBall )
				{
					m_posBallClink_screen = point;
				}
			}
		}
		else
		if( m_focusedList == StrategyGUI_List::Situation && m_focusedSituationID >= 0 )
		{
			m_rectSituationArea.MouseLUp( point );

			CRect rect = m_rectSituationArea.GetRect();

			CPointDouble left_top = rect.TopLeft();
			CPointDouble right_bottom = rect.BottomRight();
			m_ground.ScreenToGround( left_top );
			m_ground.ScreenToGround( right_bottom );

			CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );

			situation.condition.area.rect.left   = left_top.x;
			situation.condition.area.rect.top    = right_bottom.y;
			situation.condition.area.rect.right  = right_bottom.x;
			situation.condition.area.rect.bottom = left_top.y;

			m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );
		}


		m_mouseUpPoint = point;

		m_bLButton = false;
	}

	return MouseCapture::RELEASE;
}


MouseCapture::Enum CPropertyPageStrategyGUI::DisplayRButtonDown( UINT nFlags, CPoint point )
{
	if( m_focusedList == 0 && m_focusedSituationID >= 0 )
	{
		m_rectSituationArea.MouseRDown( point );
	}

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

		return MouseCapture::SET;
	}
	
	return MouseCapture::NOTHING;
}

MouseCapture::Enum CPropertyPageStrategyGUI::DisplayRButtonUp( UINT nFlags, CPoint point )
{
	if( m_bRButton )
	{
		if( !(nFlags&MK_CONTROL) )
		{
			if( m_focusedList == StrategyGUI_List::Behavior )
			{
				CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );
				CStrategyGUI::Behavior behavior = role.vecBehavior[m_focusedBehaviorID];

				if( behavior.type == StrategyGUI_BehaviorType::Goalkeep )
				{
				}

				if( behavior.type == StrategyGUI_BehaviorType::Defense_Wall )
				{
					CPointDouble pos = point;
					m_ground.ScreenToGround( pos );

					pos.x = (int)((pos.x+0.005)*100) / 100.0;
					pos.y = (int)((pos.y+0.005)*100) / 100.0;

					behavior.options.defense_wall.posB = pos;
				}

				if( behavior.type == StrategyGUI_BehaviorType::Kick_B )
				{
					CPointDouble pos = point;
					m_ground.ScreenToGround( pos );

					pos.x = (int)((pos.x+0.005)*100) / 100.0;
					pos.y = (int)((pos.y+0.005)*100) / 100.0;

					behavior.options.kick_B.posB = pos;
				}

				if( behavior.type == StrategyGUI_BehaviorType::Kick_A )
				{
					CPointDouble pos = point;
					m_ground.ScreenToGround( pos );

					if( behavior.options.kick_A.direction.bPosDirection )
					{
						behavior.options.kick_A.direction.posDirection = pos;
					}
					else
					{
						behavior.options.kick_A.direction.direction = (double)(int)(pos - behavior.options.kick_A.destination.pos).AngleDegree();
					}
				}

				if( behavior.type == StrategyGUI_BehaviorType::MoveTo )
				{
				}

				if( behavior.type == StrategyGUI_BehaviorType::Velocity )
				{
					if( m_rectVelocityButton[0].Inside( CPointDouble(point) ) )
					{
						//behavior.options.manual_velocity.vLinear = behavior.options.manual_velocity.vLinear + 0.01;
						behavior.options.manual_velocity.vLinear = min( 4.0, behavior.options.manual_velocity.vLinear + 0.01 );
					}
					else
					if( m_rectVelocityButton[1].Inside( CPointDouble(point) ) )
					{
						//behavior.options.manual_velocity.vLinear = behavior.options.manual_velocity.vLinear - 0.01;
						behavior.options.manual_velocity.vLinear = max( -4.0, behavior.options.manual_velocity.vLinear - 0.01 );
					}
					else
					if( m_rectVelocityButton[2].Inside( CPointDouble(point) ) )
					{
						//behavior.options.manual_velocity.vAngular = behavior.options.manual_velocity.vAngular + 10;
						behavior.options.manual_velocity.vAngular = min( 7200, behavior.options.manual_velocity.vAngular + 10 );
					}
					else
					if( m_rectVelocityButton[3].Inside( CPointDouble(point) ) )
					{
						//behavior.options.manual_velocity.vAngular = behavior.options.manual_velocity.vAngular - 10;
						behavior.options.manual_velocity.vAngular = max( -7200, behavior.options.manual_velocity.vAngular - 10 );
					}
					else
					if( m_rectVelocityButton[4].Inside( CPointDouble(point) ) )
					{
						behavior.options.manual_velocity.time = behavior.options.manual_velocity.time + 0.05;
					}
					else
					if( m_rectVelocityButton[5].Inside( CPointDouble(point) ) )
					{
						behavior.options.manual_velocity.time = max( 0, behavior.options.manual_velocity.time - 0.05 );
					}
					else
					{
						CPointDouble pos = point;
						m_ground.ScreenToGround( pos );

						m_orientationRobotGUI = (pos - m_posRobotGUI).AngleDegree();
					}
				}

				if( behavior.type == StrategyGUI_BehaviorType::OrientationTo )
				{
					CPointDouble pos = point;
					m_ground.ScreenToGround( pos );

					if( behavior.options.orientation.orientation.bPosDirection )
					{
						behavior.options.orientation.orientation.posDirection = pos;
					}
					else
					{
						behavior.options.orientation.orientation.direction = (double)(int)(pos - m_posRobotGUI).AngleDegree();
					}
				}

				if( behavior.type == StrategyGUI_BehaviorType::Kick_C )
				{
					CPointDouble pos = point;
					m_ground.ScreenToGround( pos );

					if( behavior.options.kick_C.target.bPosDirection )
					{
						behavior.options.kick_C.target.posDirection = pos;
					}
					else
					{
						CPointDouble posBall = m_posBallClink_screen;
						m_ground.ScreenToGround( posBall );

						behavior.options.kick_C.target.direction = (double)(int)(pos - posBall).AngleDegree();
					}
				}

				role.vecBehavior[ m_focusedBehaviorID ] = behavior;
				m_strategyGUI.UpdateRole( m_focusedRoleID, role );
			}
			else
			if( m_focusedList == StrategyGUI_List::Situation && m_focusedSituationID >= 0 )
			{
				m_rectSituationArea.MouseRUp( point );
			}
		}

		if( m_focusedList == StrategyGUI_List::Situation || m_focusedList == StrategyGUI_List::RoleAssign || m_focusedList == StrategyGUI_List::Role )
			m_posBallClink_screen = point;

		if( m_focusedList == StrategyGUI_List::Behavior && nFlags&MK_CONTROL )
			m_posBallClink_screen = point;

		m_mouseUpPoint = point;


		m_bRButton = false;
	}

	return MouseCapture::RELEASE;
}

MouseCapture::Enum CPropertyPageStrategyGUI::DisplayMouseMove( UINT nFlags, CPoint point )
{
	if( m_focusedList == StrategyGUI_List::Situation && m_focusedSituationID >= 0 )
		m_rectSituationArea.MouseMove( point );


	m_mouseMovePoint = point;

	if( m_bLButton )
	{
		if( m_bDragMove )
		{
		}
		else
		{
			//´Ü¼ø ¼±ÅÃ -> skip
		}

		return MouseCapture::SET;
	}

	if( m_bRButton )
	{
		if( m_bDragMove )
		{
		}
		else
		{
		}

		return MouseCapture::SET;
	}

	return MouseCapture::NOTHING;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Situation <begin> //////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CPropertyPageStrategyGUI::UpdateListSituation()
{
	m_listSituation.DeleteAllItems();

	int situationN = m_strategyGUI.GetSituationN();
 	for(int n=0 ; n<situationN ; n++ )
	{
		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( n );


		LV_ITEM lvitem;
		lvitem.iItem = m_listSituation.GetItemCount();
		lvitem.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iSubItem = 0;
		lvitem.iImage = 0;
		lvitem.state = INDEXTOSTATEIMAGEMASK(1);
		lvitem.stateMask = LVIS_STATEIMAGEMASK;
		
		std::wstring test;
		test = (CStringW)situation.name;
		lvitem.pszText = (LPWSTR)( test.c_str() );

		m_listSituation.InsertItem(&lvitem);

		m_listSituation.SetItemText(lvitem.iItem, 1, m_strategyGUI.TypeToName(situation.priority) );

		CString tmp;
		tmp.Format(_T("%d:%02d~%d:%02d")
			, situation.time.begin_sec/60, situation.time.begin_sec%60
			, situation.time.end_sec/60, situation.time.end_sec%60 );

		m_listSituation.SetItemText(lvitem.iItem, 2, tmp );
	}

	m_listSituation.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );
	if( situationN > 0 )
		m_listSituation.EnsureVisible( 0, TRUE );


	SelectSituation(-1);
}


void CPropertyPageStrategyGUI::OnItemchangedListSituation(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//	#define LVIS_FOCUSED            0x0001
	//	#define LVIS_SELECTED           0x0002
	//	#define LVIS_CUT                0x0004
	//	#define LVIS_DROPHILITED        0x0008
	//	#define LVIS_GLOW               0x0010
	//	#define LVIS_ACTIVATING         0x0020
	//	#define LVIS_OVERLAYMASK        0x0F00
	//	#define LVIS_STATEIMAGEMASK     0xF000
	//	
	//	#define LVIF_TEXT               0x00000001
	//	#define LVIF_IMAGE              0x00000002
	//	#define LVIF_PARAM              0x00000004
	//	#define LVIF_STATE              0x00000008
	//	#if (_WIN32_IE >= 0x0300)
	//	#define LVIF_INDENT             0x00000010
	//	#define LVIF_NORECOMPUTE        0x00000800
	//	#endif
	//	#if (_WIN32_WINNT >= 0x0501)
	//	#define LVIF_GROUPID            0x00000100
	//	#define LVIF_COLUMNS            0x00000200
	//	#endif
	//	
	//	#if _WIN32_WINNT >= 0x0600
	//	#define LVIF_COLFMT             0x00010000 // The piColFmt member is valid in addition to puColumns
	//	#endif


	if( pNMLV->uChanged == LVIF_STATE )
	{
		if( pNMLV->uNewState & (LVIS_SELECTED | LVIS_FOCUSED) )
		{
			m_listSituation.SetItem( pNMLV->iItem, 0, LVIF_IMAGE, NULL, 1, 0, 0, 0 );
			SelectSituation( pNMLV->iItem );
		}

		if( pNMLV->uNewState == 0 )
		{
			m_listSituation.SetItem( pNMLV->iItem, 0, LVIF_IMAGE, NULL, 0, 0, 0, 0 );
			SelectSituation( -1 );
		}
	}
}


void CPropertyPageStrategyGUI::OnEndlabeleditListSituation(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	*pResult = 0;

	if( pDispInfo->item.mask == LVIF_TEXT )
	{
		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );
		CString new_name = pDispInfo->item.pszText;

		if( m_strategyGUI.FindSituation( new_name ) >= 0 )
		{
			AfxMessageBox(_T("Same name situation already exist."), MB_OK|MB_ICONEXCLAMATION );
		}
		else
		{
			m_listSituation.SetItemText(m_focusedSituationID, 0, new_name );

			situation.name = new_name;
			m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );

			m_rectSituationArea.SetTitle( situation.name );
		}
	}
}


void CPropertyPageStrategyGUI::OnBnClickedAddSituation()
{
	int insert_i = m_focusedSituationID;

	if( m_focusedSituationID == -1 )
	{
		insert_i = m_listSituation.GetItemCount();
	}


	CStrategyGUI::Situation situation;

	{
		situation.condition.area.type = CStrategyGUI::CONDITION_AREA_RECTANGLE;
		situation.condition.area.rect = CRectDouble( 1.10-0.30, 0.90-0.30, 1.10+0.30, 0.90+0.30 );

		situation.condition.ball.bHome = true;
		situation.condition.ball.bOpp  = true;
		situation.condition.ball.bFree = true;
		situation.condition.ball.owner_distance = 0.3;

		for( int i=0 ; i<CStrategyGUI::MAX_SITUATION_ROBOT_N ; i++ )
		{
			situation.role_assign.role[i].name = "(None)";
			situation.role_assign.role[i].assign.option_hold = StrategyGUI_RoleAssignOptionHold::Refresh;
			situation.role_assign.role[i].assign.method      = StrategyGUI_RoleAssignMethod::Rest;
		}

		int new_situation_i=1;
		do
		{
			situation.name.Format(_T("New Situation (%d)"), new_situation_i );
			new_situation_i++;
		}
		while( m_strategyGUI.FindSituation( situation.name ) >= 0 );

		situation.priority = StrategyGUI_SituationPriority::Default;

		situation.time.begin_sec = 0;
		situation.time.end_sec   = MAX_SITUATION_TIME;
	}


		m_strategyGUI.InsertSituation( insert_i, situation );

	{
		LV_ITEM lvitem;
		lvitem.iItem = insert_i;
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iSubItem = 0;
		lvitem.iImage = 1;
		lvitem.state = LVIS_SELECTED | LVIS_FOCUSED;
		lvitem.stateMask = LVIS_SELECTED | LVIS_FOCUSED;

		std::wstring test;
		test = (CStringW)situation.name;
		lvitem.pszText = (LPWSTR)( test.c_str() );

		m_listSituation.InsertItem(&lvitem);

		m_listSituation.SetItemText(lvitem.iItem, 1, m_strategyGUI.TypeToName(situation.priority) );

		CString tmp;
		tmp.Format(_T("%d:%02d~%d:%02d")
			, situation.time.begin_sec/60, situation.time.begin_sec%60
			, situation.time.end_sec/60, situation.time.end_sec%60 );

		m_listSituation.SetItemText(lvitem.iItem, 2, tmp );

 	}	

	m_listSituation.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );
	m_listSituation.EnsureVisible( insert_i, TRUE );

	m_focusedList = StrategyGUI_List::Situation;
}

void CPropertyPageStrategyGUI::OnBnClickedCopySituation()
{
	int source_i = m_focusedSituationID;
	int insert_i = m_focusedSituationID+1;

	if( m_focusedSituationID == -1 )
	{
		insert_i = m_listSituation.GetItemCount();
	}


	CStrategyGUI::Situation situation;
	situation = m_strategyGUI.GetSituation( m_focusedSituationID );

	{
		int new_situation_i=1;
		CString new_name;
		do
		{
			new_name.Format(_T("%s (%d)"), situation.name, new_situation_i );
			new_situation_i++;
		}
		while( m_strategyGUI.FindSituation( new_name ) >= 0 );

		situation.name = new_name;
	}

		m_strategyGUI.InsertSituation( insert_i, situation );

	{
		LV_ITEM lvitem;
		lvitem.iItem = insert_i;
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iSubItem = 0;
		lvitem.iImage = 1;
		lvitem.state = LVIS_SELECTED | LVIS_FOCUSED;
		lvitem.stateMask = LVIS_SELECTED | LVIS_FOCUSED;

		std::wstring test;
		test = (CStringW)situation.name;
		lvitem.pszText = (LPWSTR)( test.c_str() );

		m_listSituation.InsertItem(&lvitem);

		m_listSituation.SetItemText(lvitem.iItem, 1, m_strategyGUI.TypeToName(situation.priority) );

		CString tmp;
		tmp.Format(_T("%d:%02d~%d:%02d")
			, situation.time.begin_sec/60, situation.time.begin_sec%60
			, situation.time.end_sec/60, situation.time.end_sec%60 );
		
		m_listSituation.SetItemText(lvitem.iItem, 2, tmp );
 	}	

	m_listSituation.SetItemState(source_i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	m_listSituation.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );
	m_listSituation.EnsureVisible( insert_i, TRUE );
}


void CPropertyPageStrategyGUI::OnBnClickedDeleteSituation()
{
	if( m_focusedSituationID >= 0 )
	{
		int delete_i = m_focusedSituationID;

		m_listSituation.DeleteItem( delete_i );
		m_strategyGUI.DeleteSituation( delete_i );

		int new_i = delete_i;
		if( new_i >= m_listSituation.GetItemCount() )
		{
			new_i = m_listSituation.GetItemCount()-1;
		}

		m_listSituation.SetItemState(new_i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

		m_listSituation.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );
		m_listSituation.EnsureVisible( new_i, TRUE );
	}
}


void CPropertyPageStrategyGUI::OnBnClickedListSituationPriorityUp()
{
	if( m_focusedSituationID == -1 || m_focusedSituationID == 0 )
		return;

	int item1 = m_focusedSituationID-1;
	int item2 = m_focusedSituationID;

	CStrategyGUI::Situation situation1 = m_strategyGUI.GetSituation( item1 );
	CStrategyGUI::Situation situation2 = m_strategyGUI.GetSituation( item2 );

	m_strategyGUI.UpdateSituation( item1, situation2 );
	m_strategyGUI.UpdateSituation( item2, situation1 );



	m_listSituation.SetItemText( item1, 0, situation2.name );
	m_listSituation.SetItemText( item2, 0, situation1.name );


	m_listSituation.SetItemText( item1, 1, m_strategyGUI.TypeToName( situation2.priority ) );
	m_listSituation.SetItemText( item2, 1, m_strategyGUI.TypeToName( situation1.priority ) );


	CString tmp1;
	tmp1.Format(_T("%d:%02d~%d:%02d")
		, situation1.time.begin_sec/60, situation1.time.begin_sec%60
		, situation1.time.end_sec/60, situation1.time.end_sec%60 );

	CString tmp2;
	tmp2.Format(_T("%d:%02d~%d:%02d")
		, situation2.time.begin_sec/60, situation2.time.begin_sec%60
		, situation2.time.end_sec/60, situation2.time.end_sec%60 );

	m_listSituation.SetItemText( item1, 2, tmp2 );
	m_listSituation.SetItemText( item2, 2, tmp1 );



	m_listSituation.SetItemState(item1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	m_listSituation.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );
	m_listSituation.EnsureVisible( item1, TRUE );
}


void CPropertyPageStrategyGUI::OnBnClickedListSituationPriorityDown()
{
	if( m_focusedSituationID == -1 || m_focusedSituationID == m_listSituation.GetItemCount()-1 )
		return;

	int item1 = m_focusedSituationID+1;
	int item2 = m_focusedSituationID;

	CStrategyGUI::Situation situation1 = m_strategyGUI.GetSituation( item1 );
	CStrategyGUI::Situation situation2 = m_strategyGUI.GetSituation( item2 );

	m_strategyGUI.UpdateSituation( item1, situation2 );
	m_strategyGUI.UpdateSituation( item2, situation1 );


	m_listSituation.SetItemText( item1, 0, situation2.name );
	m_listSituation.SetItemText( item2, 0, situation1.name );

	m_listSituation.SetItemText( item1, 1, m_strategyGUI.TypeToName( situation2.priority ) );
	m_listSituation.SetItemText( item2, 1, m_strategyGUI.TypeToName( situation1.priority ) );


	CString tmp1;
	tmp1.Format(_T("%d:%02d~%d:%02d")
		, situation1.time.begin_sec/60, situation1.time.begin_sec%60
		, situation1.time.end_sec/60, situation1.time.end_sec%60 );

	CString tmp2;
	tmp2.Format(_T("%d:%02d~%d:%02d")
		, situation2.time.begin_sec/60, situation2.time.begin_sec%60
		, situation2.time.end_sec/60, situation2.time.end_sec%60 );

	m_listSituation.SetItemText( item1, 2, tmp2 );
	m_listSituation.SetItemText( item2, 2, tmp1 );


	m_listSituation.SetItemState(item1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	m_listSituation.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );
	m_listSituation.EnsureVisible( item1, TRUE );
}


void CPropertyPageStrategyGUI::OnBnClickedCheckBallSituation1()
{
	UpdateData(TRUE);

	if( m_focusedSituationID >= 0 )
	{
		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );

		situation.condition.ball.bHome = ( m_bBallHome ) ? true : false;
		situation.condition.ball.bOpp  = ( m_bBallOpp  ) ? true : false;
		situation.condition.ball.bFree = ( m_bBallFree ) ? true : false;

		m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );
	}
}


void CPropertyPageStrategyGUI::OnBnClickedCheckBallSituation2()
{
	OnBnClickedCheckBallSituation1();
}


void CPropertyPageStrategyGUI::OnBnClickedCheckBallSituation3()
{
	OnBnClickedCheckBallSituation1();
}


void CPropertyPageStrategyGUI::OnBnClickedCheckShowAllSituation()
{
	UpdateData(TRUE);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Situation <end> ////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Role <begin> ///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CPropertyPageStrategyGUI::UpdateListRole()
{
	m_listRole.DeleteAllItems();

	int roleN = m_strategyGUI.GetRoleN();
 	for(int n=0 ; n<roleN ; n++ )
	{
		CStrategyGUI::Role role = m_strategyGUI.GetRole( n );


		LV_ITEM lvitem;
		lvitem.iItem = n;
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iSubItem = 0;
		lvitem.iImage = 0;
		lvitem.state = 0;
		lvitem.stateMask = 0;

		std::wstring test;
		test = (CStringW)role.name;
		lvitem.pszText = (LPWSTR)( test.c_str() );

		m_listRole.InsertItem(&lvitem);
	}

	m_listRole.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
	if( roleN > 0 )
		m_listRole.EnsureVisible( 0, TRUE );

	SelectRole(-1);
}


void CPropertyPageStrategyGUI::OnItemchangedListRole(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if( pNMLV->uChanged == LVIF_STATE )
	{
		if( pNMLV->uNewState & (LVIS_SELECTED | LVIS_FOCUSED) )
		{
			m_listRole.SetItem( pNMLV->iItem, 0, LVIF_IMAGE, NULL, 1, 0, 0, 0 );
			SelectRole( pNMLV->iItem );
		}

		if( pNMLV->uNewState == 0 )
		{
			m_listRole.SetItem( pNMLV->iItem, 0, LVIF_IMAGE, NULL, 0, 0, 0, 0 );
			SelectRole( -1 );
		}
	}
}


void CPropertyPageStrategyGUI::OnEndlabeleditListRole(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	*pResult = 0;

	if( pDispInfo->item.mask == LVIF_TEXT )
	{
		CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );
		CString new_name = pDispInfo->item.pszText;
		CString old_name = role.name;


		if( m_strategyGUI.FindRole( new_name ) >= 0 )
		{
			AfxMessageBox(_T("Same name of role already exists."), MB_OK|MB_ICONEXCLAMATION );
		}
		else
		{
			int countRole = m_strategyGUI.CountRoleInSituation( old_name );
			if( countRole > 0 )
			{
				CString tmp;
				tmp.Format(_T("Information on the role you want to modify this situation used. (%d)\n\n Modify altogether?"), countRole );
				if( AfxMessageBox(tmp, MB_YESNO|MB_ICONQUESTION ) == IDYES )
				{
					m_strategyGUI.ChangeRoleInSituation( old_name, new_name );
					SelectSituation_UpdatePage();
				}
			}

			m_listRole.SetItemText(m_focusedRoleID, 0, new_name );

			role.name = new_name;
			m_strategyGUI.UpdateRole( m_focusedRoleID, role );
		}
	}
}


void CPropertyPageStrategyGUI::SelectRole( int nSelect )
{
	m_focusedRoleID = nSelect;

	if( m_focusedRoleID >= 0 )
	{
		CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );

		m_listRoleDefinition.DeleteAllItems();

		for( unsigned int i=0 ; i<role.vecBehavior.size() ; i++ )
		{
			LV_ITEM lvitem;
			lvitem.iItem = i;
			lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
			lvitem.iSubItem = 0;
			lvitem.iImage = 0;
			lvitem.state = 0;
			lvitem.stateMask = 0;

			std::wstring test;
			test = (CStringW)m_strategyGUI.TypeToName(role.vecBehavior[i].controlType );
			lvitem.pszText = (LPWSTR)( test.c_str() );

			m_listRoleDefinition.InsertItem(&lvitem);
 
			m_listRoleDefinition.SetItemText(lvitem.iItem, 1, m_strategyGUI.TypeToName(role.vecBehavior[i].type) );	

			//CString tmp = m_strategyGUI.RoleOptionString( m_focusedRoleID, i );
			//m_listRoleDefinition.SetItemText(lvitem.iItem, 1, tmp );	
		}

		m_focusedBehaviorID = -1;
	}
	else
	{
		m_listRoleDefinition.DeleteAllItems();
		m_focusedBehaviorID = -1;
	}

	m_listRoleDefinition.SetColumnWidth( 1, LVSCW_AUTOSIZE_USEHEADER );
}

void CPropertyPageStrategyGUI::OnBnClickedAddRole()
{
	int insert_i = m_focusedRoleID;

	if( m_focusedRoleID == -1 )
	{
		insert_i = m_listRole.GetItemCount();
	}


	CStrategyGUI::Role role;

	{
		int new_role_i=1;
		do
		{
			role.name.Format(_T("new Role (%d)"), new_role_i );
			new_role_i++;
		}
		while( m_strategyGUI.FindRole( role.name ) >= 0 );
	}

		m_strategyGUI.InsertRole( insert_i, role );

	{
		LV_ITEM lvitem;
		lvitem.iItem = insert_i;
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iSubItem = 0;
		lvitem.iImage = 1;
		lvitem.state = LVIS_SELECTED | LVIS_FOCUSED;
		lvitem.stateMask = LVIS_SELECTED | LVIS_FOCUSED;

		std::wstring test;
		test = (CStringW)role.name;
		lvitem.pszText = (LPWSTR)( test.c_str() );

		m_listRole.InsertItem(&lvitem);
 	}	

	m_listRole.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
	m_listRole.EnsureVisible( insert_i, TRUE );

	m_focusedList = StrategyGUI_List::Role;
}


void CPropertyPageStrategyGUI::OnBnClickedCopyRole()
{
	int source_i = m_focusedRoleID;
	int insert_i = m_focusedRoleID+1;

	if( m_focusedRoleID == -1 )
	{
		insert_i = m_listRole.GetItemCount();
	}


	CStrategyGUI::Role role;
	role = m_strategyGUI.GetRole( m_focusedRoleID );

	{
		int new_role_i=1;
		do
		{
			role.name.Format(_T("new Role(%d)"), new_role_i );
			new_role_i++;
		}
		while( m_strategyGUI.FindRole( role.name ) >= 0 );
	}

		m_strategyGUI.InsertRole( insert_i, role );

	{
		LV_ITEM lvitem;
		lvitem.iItem = insert_i;
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iSubItem = 0;
		lvitem.iImage = 1;
		lvitem.state = LVIS_SELECTED | LVIS_FOCUSED;
		lvitem.stateMask = LVIS_SELECTED | LVIS_FOCUSED;

		std::wstring test;
		test = (CStringW)role.name;
		lvitem.pszText = (LPWSTR)( test.c_str() );

		m_listRole.InsertItem(&lvitem);
 	}	

	m_listRole.SetItemState(source_i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	m_listRole.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
	m_listRole.EnsureVisible( insert_i, TRUE );
}


void CPropertyPageStrategyGUI::OnBnClickedDeleteRole()
{
	if( m_focusedRoleID >= 0 )
	{
		int delete_i = m_focusedRoleID;

		m_listRole.DeleteItem( delete_i );
		m_strategyGUI.DeleteRole( delete_i );

		int new_i = delete_i;
		if( new_i >= m_listRole.GetItemCount() )
		{
			new_i = m_listRole.GetItemCount()-1;
		}

		m_listRole.SetItemState(new_i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

		m_listRole.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
		m_listRole.EnsureVisible( new_i, TRUE );
	}
}


void CPropertyPageStrategyGUI::OnBnClickedListRoleOrderUp()
{
	if( m_focusedRoleID == -1 || m_focusedRoleID == 0 )
		return;

	int item1 = m_focusedRoleID-1;
	int item2 = m_focusedRoleID;

	CStrategyGUI::Role role1 = m_strategyGUI.GetRole( item1 );
	CStrategyGUI::Role role2 = m_strategyGUI.GetRole( item2 );

	m_listRole.SetItemText( item1, 0, role2.name );
	m_listRole.SetItemText( item2, 0, role1.name );

	m_strategyGUI.UpdateRole( item1, role2 );
	m_strategyGUI.UpdateRole( item2, role1 );

	m_listRole.SetItemState(item1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	m_listRole.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
	m_listRole.EnsureVisible( item1, TRUE );
}


void CPropertyPageStrategyGUI::OnBnClickedListRoleOrderDown()
{
	if( m_focusedRoleID == -1 || m_focusedRoleID == m_listRole.GetItemCount()-1 )
		return;

	int item1 = m_focusedRoleID+1;
	int item2 = m_focusedRoleID;

	CStrategyGUI::Role role1 = m_strategyGUI.GetRole( item1 );
	CStrategyGUI::Role role2 = m_strategyGUI.GetRole( item2 );

	m_listRole.SetItemText( item1, 0, role2.name );
	m_listRole.SetItemText( item2, 0, role1.name );

	m_strategyGUI.UpdateRole( item1, role2 );
	m_strategyGUI.UpdateRole( item2, role1 );

	m_listRole.SetItemState(item1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	m_listRole.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
	m_listRole.EnsureVisible( item1, TRUE );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Role <end> /////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Role-Situation <begin> /////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CPropertyPageStrategyGUI::SelectSituation( int nSelect )
{
	EnterCriticalSection(&m_critPropertyPageStrategyGUI);
	m_focusedSituationID = nSelect;
	if( m_focusedSituationID >= 0 )
	{
		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );
		m_sliderBallOwnerDistance.SetValue( situation.condition.ball.owner_distance );

		m_sliderSituationTime.SetValue( situation.time.begin_sec, situation.time.end_sec );
	}
	LeaveCriticalSection(&m_critPropertyPageStrategyGUI);

	{
		m_comboRoleAssign.SelectString(0, _T(""));
		m_comboRoleAssign_Hold.SelectString(0, _T(""));
		m_comboSituationPriority.SelectString(0, _T(""));
	}

	if( m_focusedSituationID >= 0 )
	{
		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );


		// for modification by drag

		CPointDouble left_top, right_bottom;

		left_top = CPointDouble( situation.condition.area.rect.left, situation.condition.area.rect.top );
		right_bottom = CPointDouble( situation.condition.area.rect.right, situation.condition.area.rect.bottom );

		m_ground.GroundToScreen( left_top );
		m_ground.GroundToScreen( right_bottom );

		m_rectSituationArea.Init( left_top.x, right_bottom.y, right_bottom.x, left_top.y );
		m_rectSituationArea.SetColor( RGB(0,255,0) );
		m_rectSituationArea.SetTitle( situation.name );

		m_comboSituationPriority.SelectString(0, m_strategyGUI.TypeToName(situation.priority) );
	}

	SelectSituation_UpdatePage();
	UpdateData(FALSE);
}


void CPropertyPageStrategyGUI::SelectSituation_UpdatePage()
{
	if( m_focusedSituationID >= 0 )
	{
		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );

		m_bBallHome = (situation.condition.ball.bHome) ? TRUE : FALSE ;
		m_bBallOpp  = (situation.condition.ball.bOpp ) ? TRUE : FALSE ;
		m_bBallFree = (situation.condition.ball.bFree) ? TRUE : FALSE ;

		int role_i = m_listSituationRoleAssign.GetSelectionMark();

		if( role_i >= 0 )
		{
			m_comboRoleAssign.SelectString( 0, m_strategyGUI.TypeToName(situation.role_assign.role[role_i].assign.method ) );
			m_comboRoleAssign_Hold.SelectString( 0, m_strategyGUI.TypeToName(situation.role_assign.role[role_i].assign.option_hold ) );

			//m_comboRoleAssign.SetCurSel( situation.role_assign.role[role_i].assign.method );
		}

		m_listSituationRoleAssign.DeleteAllItems();


		for( int i=0 ; i<CStrategyGUI::MAX_SITUATION_ROBOT_N ; i++ )
		{
			LV_ITEM lvitem;
			lvitem.iItem = i;
			lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
			lvitem.iSubItem = 0;
			lvitem.iImage = 0;
			lvitem.iImage = 0;
			lvitem.state =  0;
			lvitem.stateMask = 0;

			std::wstring test;
			test = (CStringW)situation.role_assign.role[i].name;
			lvitem.pszText = (LPWSTR)( test.c_str() );

			m_listSituationRoleAssign.InsertItem(&lvitem);

			m_listSituationRoleAssign.SetItemText(lvitem.iItem, 1, m_strategyGUI.TypeToName( situation.role_assign.role[i].assign.option_hold ) );
			m_listSituationRoleAssign.SetItemText(lvitem.iItem, 2, m_strategyGUI.TypeToName( situation.role_assign.role[i].assign.method      ) );
		}
	}
	else
	{
		m_listSituationRoleAssign.DeleteAllItems();
	}
}


void CPropertyPageStrategyGUI::OnItemchangedListSituationRole(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;


	if( pNMLV->uChanged == LVIF_STATE )
	{
		if( pNMLV->uNewState & (LVIS_SELECTED | LVIS_FOCUSED) )
		{
			EnterCriticalSection(&m_critPropertyPageStrategyGUI);

			m_listSituationRoleAssign.SetItem( pNMLV->iItem, 0, LVIF_IMAGE, NULL, 1, 0, 0, 0 );
			m_focusedSituationRoleID = pNMLV->iItem;

			if( m_focusedSituationRoleID >= 0 )
			{
				CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );
				m_comboRoleAssign.SelectString( 0, m_strategyGUI.TypeToName( situation.role_assign.role[m_focusedSituationRoleID].assign.method ) );
				m_comboRoleAssign_Hold.SelectString( 0, m_strategyGUI.TypeToName( situation.role_assign.role[m_focusedSituationRoleID].assign.option_hold ) );
			}

			LeaveCriticalSection(&m_critPropertyPageStrategyGUI);
		}

		if( pNMLV->uNewState == 0 )
		{
			EnterCriticalSection(&m_critPropertyPageStrategyGUI);
			m_listSituationRoleAssign.SetItem( pNMLV->iItem, 0, LVIF_IMAGE, NULL, 0, 0, 0, 0 );
			m_focusedSituationRoleID = -1;
			LeaveCriticalSection(&m_critPropertyPageStrategyGUI);
		}
	}
}


void CPropertyPageStrategyGUI::OnBnClickedAssignRoleToSituation()
{
	if( m_focusedSituationID < 0 )
		return;

	if( m_focusedRoleID < 0 )
		return;

	if( m_focusedSituationRoleID < 0 )
		return;

	CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );
	CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );

	situation.role_assign.role[ m_focusedSituationRoleID ].name = role.name;
	m_listSituationRoleAssign.SetItemText( m_focusedSituationRoleID, 0, situation.role_assign.role[m_focusedSituationRoleID].name );

	m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );

	//SelectSituation_UpdatePage();
}


void CPropertyPageStrategyGUI::OnSelchangeComboRoleAssign()
{
	UpdateData(TRUE);

	if( m_focusedSituationID >= 0 )
	{
		int nRoleAssign = m_comboRoleAssign.GetCurSel();

		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );

		int role_i = m_listSituationRoleAssign.GetSelectionMark();
		situation.role_assign.role[ role_i ].assign.method = m_strategyGUI.m_vecRoleAssignMethod[ nRoleAssign ];

		m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );

		m_listSituationRoleAssign.SetItemText( role_i, 2, m_strategyGUI.TypeToName( m_strategyGUI.m_vecRoleAssignMethod[ nRoleAssign ] ) );
	}
}

void CPropertyPageStrategyGUI::OnSelchangeComboRoleAssign2()
{
	UpdateData(TRUE);

	if( m_focusedSituationID >= 0 )
	{
		int nRoleAssign = m_comboRoleAssign_Hold.GetCurSel();

		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );

		int role_i = m_listSituationRoleAssign.GetSelectionMark();
		situation.role_assign.role[ role_i ].assign.option_hold = m_strategyGUI.m_vecRoleAssignOption_Hold[ nRoleAssign ];

		m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );

		m_listSituationRoleAssign.SetItemText( role_i, 1, m_strategyGUI.TypeToName(m_strategyGUI.m_vecRoleAssignOption_Hold[ nRoleAssign ]) );
	}
}

void CPropertyPageStrategyGUI::OnSelchangeComboSituationPriority()
{
	UpdateData(TRUE);

	if( m_focusedSituationID >= 0 )
	{
		int nSituationPriority = m_comboSituationPriority.GetCurSel();

		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );

		situation.priority = m_strategyGUI.m_vecSituationPriority[ nSituationPriority ];

		m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );

		m_listSituation.SetItemText( m_focusedSituationID, 1, m_strategyGUI.TypeToName( situation.priority ) );
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Role-Situation <end> ///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Behavior <begin> ///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CPropertyPageStrategyGUI::OnItemchangedListRoleDefinition(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if( pNMLV->uChanged == LVIF_STATE )
	{
		if( pNMLV->uNewState & (LVIS_SELECTED | LVIS_FOCUSED) )
		{
			m_listRoleDefinition.SetItem( pNMLV->iItem, 0, LVIF_IMAGE, NULL, 1, 0, 0, 0 );
		    m_focusedBehaviorID = pNMLV->iItem;

			CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );
			m_comboBehaviorControlType.SelectString(0, m_strategyGUI.TypeToName( role.vecBehavior[m_focusedBehaviorID ].controlType ) );
		}

		if( pNMLV->uNewState == 0 )
		{
			m_listRoleDefinition.SetItem( pNMLV->iItem, 0, LVIF_IMAGE, NULL, 0, 0, 0, 0 );
			m_focusedBehaviorID = -1;
		}
	}
}


void CPropertyPageStrategyGUI::OnBnClickedCopyBehavior()
{
	if( m_focusedRoleID != -1 &&  m_focusedBehaviorID != -1 )
	{
		CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );
		m_behaviorCopy = role.vecBehavior[m_focusedBehaviorID ];
	}
}


void CPropertyPageStrategyGUI::OnBnClickedPasteBehavior()
{
	if( m_focusedRoleID < 0 )
		return;

	int insert_i = m_focusedBehaviorID;

	if( m_focusedBehaviorID == -1 )
	{
		insert_i = m_listRoleDefinition.GetItemCount();
	}


	CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );

	int new_behavior_id = m_comboBehavior.GetCurSel();

	CStrategyGUI::Behavior behavior = m_behaviorCopy;

	auto it = role.vecBehavior.begin() + insert_i;
	role.vecBehavior.insert( it, behavior );

	m_strategyGUI.UpdateRole( m_focusedRoleID, role );

	{
		LV_ITEM lvitem;
		lvitem.iItem = insert_i;
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iSubItem = 0;
		lvitem.iImage = 1;
		lvitem.state = LVIS_SELECTED | LVIS_FOCUSED;
		lvitem.stateMask = LVIS_SELECTED | LVIS_FOCUSED;

		std::wstring test;
		test = (CStringW)m_strategyGUI.TypeToName( role.vecBehavior[insert_i].controlType );
		lvitem.pszText = (LPWSTR)( test.c_str() );

		m_listRoleDefinition.InsertItem(&lvitem);
 
		m_listRoleDefinition.SetItemText(lvitem.iItem, 1, m_strategyGUI.TypeToName( role.vecBehavior[insert_i].type ) );	

		//CString tmp = m_strategyGUI.RoleOptionString( m_focusedRoleID, insert_i );
		//m_listRoleDefinition.SetItemText(lvitem.iItem, 1, tmp );	
	}


	m_listRoleDefinition.SetColumnWidth( 1, LVSCW_AUTOSIZE_USEHEADER );
	m_listRoleDefinition.EnsureVisible( insert_i, TRUE );

	m_focusedList = StrategyGUI_List::Behavior;	
}

void CPropertyPageStrategyGUI::OnBnClickedAddBehavior()
{
	if( m_focusedRoleID < 0 )
		return;

	int insert_i = m_focusedBehaviorID;

	if( m_focusedBehaviorID == -1 )
	{
		insert_i = m_listRoleDefinition.GetItemCount();
	}


	CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );

	int new_behavior_id = m_comboBehavior.GetCurSel();

	CStrategyGUI::Behavior behavior;
	behavior.type = m_strategyGUI.m_vecBehaviorType[ new_behavior_id ];
	behavior.controlType = m_strategyGUI.m_vecBehaviorControlType[ m_comboBehaviorControlType.GetCurSel() ];


	// 1.5 x 1.3
	behavior.options.goalkeep.x_pos = 0.04;
	behavior.options.goalkeep.y_size = 0.20;
	behavior.options.goalkeep.clear_x_size = 0.10;
	behavior.options.goalkeep.clear_y_size = 0.25;
	behavior.options.goalkeep.clear_ball_speed = 0.02;

	behavior.options.defense_wall.clear_x_size = 0.10;
	behavior.options.defense_wall.clear_ball_speed = 0.02;
	behavior.options.defense_wall.posA = CPointDouble( 0.20, 0.85 );
	behavior.options.defense_wall.posB = CPointDouble( 0.20, 0.45 );

	behavior.options.move_to.destination.bBall = false;
	behavior.options.move_to.destination.pos = CPointDouble( 0.75, 0.65 );
	behavior.options.move_to.destination.error = 0.05;

	behavior.options.kick_A.destination.bBall = false;
	behavior.options.kick_A.destination.pos = CPointDouble( 0.75, 0.65 );
	behavior.options.kick_A.destination.error = 0.05;
	behavior.options.kick_A.direction.bPosDirection = false;
	behavior.options.kick_A.direction.posDirection = CPointDouble( 1.2, 0.65 );
	behavior.options.kick_A.direction.direction = 0;


	behavior.options.orientation.orientation.bPosDirection = false;
	behavior.options.orientation.orientation.posDirection = CPointDouble( 1.2, 0.65 );
	behavior.options.orientation.orientation.direction = 0;

	behavior.options.wait.time = 5.0;

	behavior.options.kick_B.posA = CPointDouble( 1.0, 0.65 );
	behavior.options.kick_B.posB = CPointDouble( 1.3, 0.65 );

	behavior.options.manual_velocity.vLinear  = 0;
	behavior.options.manual_velocity.vAngular = 0;
	behavior.options.manual_velocity.time     = 0;

	behavior.options.kick_C.approach.bPosDirection = true;
	behavior.options.kick_C.approach.posDirection = CPointDouble( 0, 0.65 );
	behavior.options.kick_C.approach.direction = 180;
	behavior.options.kick_C.target.bPosDirection = true;
	behavior.options.kick_C.target.posDirection = CPointDouble( 1.2, 0.65 );
	behavior.options.kick_C.target.direction = 0;

	auto it = role.vecBehavior.begin() + insert_i;
	role.vecBehavior.insert( it, behavior );

	m_strategyGUI.UpdateRole( m_focusedRoleID, role );

	{
		LV_ITEM lvitem;
		lvitem.iItem = insert_i;
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iSubItem = 0;
		lvitem.iImage = 1;
		lvitem.state = LVIS_SELECTED | LVIS_FOCUSED;
		lvitem.stateMask = LVIS_SELECTED | LVIS_FOCUSED;

		std::wstring test;
		test = (CStringW) m_strategyGUI.TypeToName( role.vecBehavior[insert_i].controlType );
		lvitem.pszText = (LPWSTR)( test.c_str() );

		m_listRoleDefinition.InsertItem(&lvitem);
 
		m_listRoleDefinition.SetItemText(lvitem.iItem, 1, m_strategyGUI.TypeToName( role.vecBehavior[insert_i].type ) );	

		//CString tmp = m_strategyGUI.RoleOptionString( m_focusedRoleID, insert_i );
		//m_listRoleDefinition.SetItemText(lvitem.iItem, 1, tmp );	
	}


	m_listRoleDefinition.SetColumnWidth( 1, LVSCW_AUTOSIZE_USEHEADER );
	m_listRoleDefinition.EnsureVisible( insert_i, TRUE );

	m_focusedList = StrategyGUI_List::Behavior;
}


void CPropertyPageStrategyGUI::OnBnClickedDeleteBehavior()
{
	if( m_focusedBehaviorID < 0 )
		return;

	if( m_focusedRoleID >= 0 )
	{
		int delete_i = m_focusedBehaviorID;

		m_listRoleDefinition.DeleteItem( delete_i );


		CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );
		auto it = role.vecBehavior.begin() + delete_i;
		role.vecBehavior.erase( it );
		m_strategyGUI.UpdateRole( m_focusedRoleID, role );


		int new_i = delete_i;
		if( new_i >= m_listRoleDefinition.GetItemCount() )
		{
			new_i = m_listRoleDefinition.GetItemCount()-1;
		}

		m_listRoleDefinition.SetItemState(new_i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

		m_listRoleDefinition.SetColumnWidth( 1, LVSCW_AUTOSIZE_USEHEADER );
		m_listRoleDefinition.EnsureVisible( new_i, TRUE );
	}
}


void CPropertyPageStrategyGUI::OnBnClickedListBehaviorOrderUp()
{
	if( m_focusedRoleID < 0 )
		return;

	if( m_focusedBehaviorID == -1 || m_focusedBehaviorID == 0 )
		return;

	int item1 = m_focusedBehaviorID-1;
	int item2 = m_focusedBehaviorID;

	CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );
	CStrategyGUI::Behavior behavior1 = role.vecBehavior[item1];
	CStrategyGUI::Behavior behavior2 = role.vecBehavior[item2];

	m_listRoleDefinition.SetItemText( item1, 0, m_strategyGUI.TypeToName( behavior2.controlType ) );
	m_listRoleDefinition.SetItemText( item2, 0, m_strategyGUI.TypeToName( behavior1.controlType ) );

	m_listRoleDefinition.SetItemText( item1, 1, m_strategyGUI.TypeToName( behavior2.type ) );
	m_listRoleDefinition.SetItemText( item2, 1, m_strategyGUI.TypeToName( behavior1.type ) );

	//CString option1 = m_listRoleDefinition.GetItemText( item1, 1 );
	//CString option2 = m_listRoleDefinition.GetItemText( item2, 1 );
	//m_listRoleDefinition.SetItemText( item1, 1, option2 );
	//m_listRoleDefinition.SetItemText( item2, 1, option1 );

	role.vecBehavior[item1] = behavior2;
	role.vecBehavior[item2] = behavior1;

	m_strategyGUI.UpdateRole( m_focusedRoleID, role );

	m_listRoleDefinition.SetItemState(item1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	m_listRoleDefinition.SetColumnWidth( 1, LVSCW_AUTOSIZE_USEHEADER );
	m_listRoleDefinition.EnsureVisible( item1, TRUE );
}


void CPropertyPageStrategyGUI::OnBnClickedListBehaviorOrderDown()
{
	if( m_focusedRoleID < 0 )
		return;

	if( m_focusedBehaviorID == -1 || m_focusedBehaviorID == m_listRoleDefinition.GetItemCount()-1 )
		return;

	int item1 = m_focusedBehaviorID+1;
	int item2 = m_focusedBehaviorID;

	CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );
	CStrategyGUI::Behavior behavior1 = role.vecBehavior[item1];
	CStrategyGUI::Behavior behavior2 = role.vecBehavior[item2];

	m_listRoleDefinition.SetItemText( item1, 0, m_strategyGUI.TypeToName( behavior2.controlType ) );
	m_listRoleDefinition.SetItemText( item2, 0, m_strategyGUI.TypeToName( behavior1.controlType ) );

	m_listRoleDefinition.SetItemText( item1, 1, m_strategyGUI.TypeToName( behavior2.type ) );
	m_listRoleDefinition.SetItemText( item2, 1, m_strategyGUI.TypeToName( behavior1.type ) );

	//CString option1 = m_listRoleDefinition.GetItemText( item1, 1 );
	//CString option2 = m_listRoleDefinition.GetItemText( item2, 1 );
	//m_listRoleDefinition.SetItemText( item1, 1, option2 );
	//m_listRoleDefinition.SetItemText( item2, 1, option1 );

	role.vecBehavior[item1] = behavior2;
	role.vecBehavior[item2] = behavior1;

	m_strategyGUI.UpdateRole( m_focusedRoleID, role );

	m_listRoleDefinition.SetItemState(item1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	m_listRoleDefinition.SetColumnWidth( 1, LVSCW_AUTOSIZE_USEHEADER );
	m_listRoleDefinition.EnsureVisible( item1, TRUE );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Behavior <end> /////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


// void CPropertyPageStrategyGUI::OnBnClickedTutorialGui()
// {
//	 // TODO: Tutorial functionality for Strategry page
//
// }


void CPropertyPageStrategyGUI::OnBnClickedOpenStrategyGui()
{
	UpdateData(TRUE);

	BeginWaitCursor();
	
	TCHAR szFilter[] = _T("Strategy File(*.S)|*.S|All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("default"), _T("default"), NULL, szFilter);
	
	if( dlg.DoModal() == IDOK )
	{
		RestoreWaitCursor();
		OpenFile( dlg.GetPathName() );
	}

	EndWaitCursor();
}


void CPropertyPageStrategyGUI::OnBnClickedSaveStrategyGui()
{
	UpdateData(TRUE);

	BeginWaitCursor();

	TCHAR szFilter[] = _T("Strategy File(*.S)|*.S|All Files(*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("default"), _T("default"), NULL, szFilter);
	
	if( dlg.DoModal() == IDOK )
	{
		RestoreWaitCursor();
		SaveFile( dlg.GetPathName() );
	}

	EndWaitCursor();
}


void CPropertyPageStrategyGUI::OpenFile(CString filename)
{
	EnterCriticalSection(&m_critPropertyPageStrategyGUI);

	CFile file;

	m_strFileName = filename;
	
	if( file.Open(m_strFileName, CFile::modeRead ) == FALSE )
	{
		AfxMessageBox(_T("failed to open File. (CPropertyPageStrategyGUI::OpenFile)"));
	}
	else
	{
		CArchive ar( &file, CArchive::load );
	
		m_strategyGUI.OpenFile( ar );
	
		ar.Close();
		file.Close();
	
		UpdateListRole();
		UpdateListSituation();
	}

	LeaveCriticalSection(&m_critPropertyPageStrategyGUI);

	UpdateData(FALSE);
}

void CPropertyPageStrategyGUI::SaveFile(CString filename)
{
	CFile file;
	
	m_strFileName = filename;

	file.Open( m_strFileName, CFile::modeCreate | CFile::modeWrite );
	CArchive ar( &file, CArchive::store );
	
	m_strategyGUI.SaveFile( ar );
	
	ar.Close();
	file.Close();

	UpdateData(FALSE);
}




//void CPropertyPageStrategyGUI::OnSelchangeComboBehaviorApproach()
//{
//	UpdateData(TRUE);
//
//	int nBehavior = m_comboBehaviorApproach.GetCurSel();
//
//	CString strBehavior;
//	int n = m_comboBehaviorApproach.GetLBTextLen( nBehavior );
//	m_comboBehaviorApproach.GetLBText( nBehavior, strBehavior.GetBuffer(n) );
//	strBehavior.ReleaseBuffer();
//	//CString str2;
//	//str2.Format(_T("item %d: %s\r\n"),nBehavior , strBehavior.GetBuffer(0));
//
//	//m_strategyGUI.ChangeBehavior( m_focusedRoleID, CStrategyGUI::_BEHAVIOR_APPROACH, strBehavior );
//}


//void CPropertyPageStrategyGUI::OnSelchangeComboBehaviorKick()
//{
//	UpdateData(TRUE);
//
//	int nBehavior = m_comboBehaviorKick.GetCurSel();
//
//	CString strBehavior;
//	int n = m_comboBehaviorKick.GetLBTextLen( nBehavior );
//	m_comboBehaviorKick.GetLBText( nBehavior, strBehavior.GetBuffer(n) );
//	strBehavior.ReleaseBuffer();
//	//CString str2;
//	//str2.Format(_T("item %d: %s\r\n"),nBehavior , strBehavior.GetBuffer(0));
//
//	//m_strategyGUI.ChangeBehavior( m_focusedRoleID, CStrategyGUI::_BEHAVIOR_KICK, strBehavior );
//}




void CPropertyPageStrategyGUI::OnSetfocusListSituation(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_focusedList = StrategyGUI_List::Situation;
	*pResult = 0;
}


void CPropertyPageStrategyGUI::OnSetfocusListSituationRoleAssign(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_focusedList = StrategyGUI_List::RoleAssign;
	*pResult = 0;
}


void CPropertyPageStrategyGUI::OnSetfocusListRole(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_focusedList = StrategyGUI_List::Role;
	*pResult = 0;
}


void CPropertyPageStrategyGUI::OnSetfocusListRoleDefinition(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_focusedList = StrategyGUI_List::Behavior;
	*pResult = 0;
}


void CPropertyPageStrategyGUI::OnEndlabeleditListRoleDefinition(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	*pResult = 0;

	if( pDispInfo->item.mask == LVIF_TEXT )
	{
		/*
		CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );
		CStrategyGUI::Behavior behavior = role.vecBehavior[ m_focusedBehaviorID ];
	
		CString new_name = pDispInfo->item.pszText;
		behavior.name = new_name;

		m_listRoleDefinition.SetItemText(m_focusedBehaviorID, 0, new_name );

		role.vecBehavior[ m_focusedBehaviorID ] = behavior;
		m_strategyGUI.UpdateRole( m_focusedRoleID, role );
		*/
	}
}


void CPropertyPageStrategyGUI::OnBnClickedListSituationRoleAssignOrderUp()
{
	int role_i = m_focusedSituationRoleID;

	if( m_focusedSituationID >= 0 && role_i > 0 )
	{
		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );

		int item1 = role_i-1;
		int item2 = role_i;

		CString tmp;
		tmp = situation.role_assign.role[item1].name;
		situation.role_assign.role[item1].name = situation.role_assign.role[item2].name;
		situation.role_assign.role[item2].name = tmp;

		tmp = situation.role_assign.role[item1].assign.option_hold;
		situation.role_assign.role[item1].assign.option_hold = situation.role_assign.role[item2].assign.option_hold;
		situation.role_assign.role[item2].assign.option_hold = tmp;

		tmp = situation.role_assign.role[item1].assign.method;
		situation.role_assign.role[item1].assign.method = situation.role_assign.role[item2].assign.method;
		situation.role_assign.role[item2].assign.method = tmp;

		CPointDouble tmp_pos = situation.role_assign.role[item1].assign.pos;
		situation.role_assign.role[item1].assign.pos = situation.role_assign.role[item2].assign.pos;
		situation.role_assign.role[item2].assign.pos = tmp_pos;

		m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );


		m_listSituationRoleAssign.SetItemText( item1, 0, situation.role_assign.role[item1].name );
		m_listSituationRoleAssign.SetItemText( item2, 0, situation.role_assign.role[item2].name );

		m_listSituationRoleAssign.SetItemText( item1, 1, m_strategyGUI.TypeToName( situation.role_assign.role[item1].assign.option_hold ) );
		m_listSituationRoleAssign.SetItemText( item2, 1, m_strategyGUI.TypeToName( situation.role_assign.role[item2].assign.option_hold ) );
		
		m_listSituationRoleAssign.SetItemText( item1, 2, m_strategyGUI.TypeToName( situation.role_assign.role[item1].assign.method ) );
		m_listSituationRoleAssign.SetItemText( item2, 2, m_strategyGUI.TypeToName( situation.role_assign.role[item2].assign.method ) );


		m_listSituationRoleAssign.SetItemState(item1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

		m_listSituationRoleAssign.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );
		m_listSituationRoleAssign.EnsureVisible( item1, TRUE );

		UpdateData(TRUE);
	}
}


void CPropertyPageStrategyGUI::OnBnClickedListSituationRoleAssignOrderDown()
{
	int role_i = m_focusedSituationRoleID;

	if( m_focusedSituationID >= 0 && role_i < CStrategyGUI::MAX_SITUATION_ROBOT_N-1 )
	{
		CStrategyGUI::Situation situation = m_strategyGUI.GetSituation( m_focusedSituationID );

		int item1 = role_i+1;
		int item2 = role_i;

		CString tmp;
		tmp = situation.role_assign.role[item1].name;
		situation.role_assign.role[item1].name = situation.role_assign.role[item2].name;
		situation.role_assign.role[item2].name = tmp;

		tmp = situation.role_assign.role[item1].assign.option_hold;
		situation.role_assign.role[item1].assign.option_hold = situation.role_assign.role[item2].assign.option_hold;
		situation.role_assign.role[item2].assign.option_hold = tmp;

		tmp = situation.role_assign.role[item1].assign.method;
		situation.role_assign.role[item1].assign.method = situation.role_assign.role[item2].assign.method;
		situation.role_assign.role[item2].assign.method = tmp;


		m_strategyGUI.UpdateSituation( m_focusedSituationID, situation );


		m_listSituationRoleAssign.SetItemText( item1, 0, situation.role_assign.role[item1].name );
		m_listSituationRoleAssign.SetItemText( item2, 0, situation.role_assign.role[item2].name );

		m_listSituationRoleAssign.SetItemText( item1, 1, m_strategyGUI.TypeToName( situation.role_assign.role[item1].assign.option_hold ) );
		m_listSituationRoleAssign.SetItemText( item2, 1, m_strategyGUI.TypeToName( situation.role_assign.role[item2].assign.option_hold ) );
		
		m_listSituationRoleAssign.SetItemText( item1, 2, m_strategyGUI.TypeToName( situation.role_assign.role[item1].assign.method ) );
		m_listSituationRoleAssign.SetItemText( item2, 2, m_strategyGUI.TypeToName( situation.role_assign.role[item2].assign.method ) );


		m_listSituationRoleAssign.SetItemState(item1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

		m_listSituationRoleAssign.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );
		m_listSituationRoleAssign.EnsureVisible( item1, TRUE );

		UpdateData(TRUE);
	}
}


void CPropertyPageStrategyGUI::OnBnClickedCheckShowVerifySituation()
{
	UpdateData(TRUE);
}




void CPropertyPageStrategyGUI::OnSelchangeComboBehaviorControlType()
{
	UpdateData(TRUE);

	if( m_focusedRoleID >= 0 && m_focusedBehaviorID >= 0 )
	{
		int nBehaviorControlType = m_comboBehaviorControlType.GetCurSel();

		CStrategyGUI::Role role = m_strategyGUI.GetRole( m_focusedRoleID );
		role.vecBehavior[m_focusedBehaviorID ].controlType = m_strategyGUI.m_vecBehaviorControlType[ nBehaviorControlType ];

		m_strategyGUI.UpdateRole( m_focusedRoleID, role );

		m_listRoleDefinition.SetItemText( m_focusedBehaviorID, 0, m_strategyGUI.TypeToName( role.vecBehavior[m_focusedBehaviorID ].controlType ) );
	}
}

