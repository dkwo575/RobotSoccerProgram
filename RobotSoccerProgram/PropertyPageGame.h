#pragma once

#include"GameGUI.h"
#include"PropertyPageRobotSoccer.h"
#include"RobotSoccerCommon.h"

#include "ObjectPositionInfo.h"
#include "ObjectVelocityInfo.h"
#include "afxwin.h"

#include "VelocityParameterDlg.h"
#include "VelocityParameterDlg2.h"
#include "StrategyParameterDlg.h"
#include "DualSlider.h"

#include "SetPlayData.h"

// CPropertyPageGame dialog

class CPropertyPageGame : public CPropertyPageRobotSoccer, public CRobotSoccerCommon, public CGameGUI
{
	DECLARE_DYNAMIC(CPropertyPageGame)

	enum enumGameState
	{
		GAME_STOP,
		GAME_READY,
		GAME_PLAY,
		GAME_STEP
	};

	enum enumMouseState
	{
		MOUSE_Ldown,
		MOUSE_Lup  ,
		MOUSE_Rdown,
		MOUSE_Rup  ,
		MOUSE_move
	};

protected:
	CRITICAL_SECTION m_critPropGameGUI;

	struct MouseInput
	{
		enum enumMouseState state;
		UINT nFlags;
		CPoint point;
	};

	std::vector< struct MouseInput > m_vecMouseInput;

	bool m_bDebugWheel;

	CSetPlayData m_SetPlayData;

	bool m_bStepFirst;

	bool m_bLButton;
	bool m_bRButton;
	CPoint m_mouseDownPoint;
	CPoint m_mouseMovePoint;
	CPoint m_mouseUpPoint;

	bool m_bDragMove;
	bool m_bDragScreen;

	int m_GameState;

public:
	bool m_bCopyStrategyGUI;
	void UpdateSetPlayRole();

	void OpenStrategyFile(CString filename);


	void OpenFile_Parameters(CString filename);
	void SaveFile_Parameters(CString filename);

	CStrategyParameterDlg* m_pStrategyParameterDlg;

	CVelocityParameter2 m_VelocityParameter2[5];
	CVelocityParameterDlg2* m_pVelocityParameterDlg2;

	CVelocityParameter m_VelocityParameter;
	CVelocityParameterDlg* m_pVelocityParameterDlg;
	void GameRun( double runningTime );


	MouseCapture::Enum DisplayRButtonDown( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayRButtonUp( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayLButtonDown( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayLButtonUp( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayMouseMove( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayMouseWheel( UINT nFlags, short zDelta, CPoint point );

	void OnRadioSituation( bool bBasicSituation );

	void OpenAutopositionFile( CString filename );
	void SaveAutopositionFile( CString filename );

	CObjectVelocityInfo Velocity();
	void SetObjectInfomation(CObjectPositionInfo futureInfo, CObjectPositionInfo currentInfo, CObjectPositionInfo pastInfo, CObjectPositionInfo errorInfo );
	CObjectPositionInfo GetObjectInfomation();


	void DrawDisplay(void);

	CPropertyPageGame();
	virtual ~CPropertyPageGame();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_GAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedGameReady();
	afx_msg void OnBnClickedGameStart();
	afx_msg void OnBnClickedGameStop();
	CString m_strAutoPositionFileName;
	afx_msg void OnBnClickedOpenAutopositionFile();
	afx_msg void OnBnClickedSaveAutopositionFile();
//	BOOL m_radioSituationOffenseDefence;
	BOOL m_radioSituation;
	afx_msg void OnBnClickedAutoposUpdate();
	afx_msg void OnBnClickedRadioSituation1();
	afx_msg void OnBnClickedRadioSituation2();
	afx_msg void OnBnClickedRadioSituation3();
	afx_msg void OnBnClickedRadioSituation4();
	afx_msg void OnBnClickedRadioSituation5();
	afx_msg void OnBnClickedRadioSituation6();
	afx_msg void OnBnClickedRadioSituation7();
	afx_msg void OnBnClickedRadioSituation8();
	CString m_strSituationOption;
	BOOL m_bRobotMessage;
	BOOL m_bRobotMessageSelectOnly;
	afx_msg void OnBnClickedCheckShowRobotMessage();
	afx_msg void OnBnClickedCheckShowRobotMessageOnly();
	afx_msg void OnBnClickedRadioMoveType1();
	afx_msg void OnBnClickedRadioMoveType2();
	afx_msg void OnBnClickedRadioMoveType3();
	afx_msg void OnBnClickedRadioMoveType4();
	afx_msg void OnBnClickedRadioMoveType5();
	afx_msg void OnBnClickedRadioMoveType6();
	BOOL m_radioMoveType;
	afx_msg void OnBnClickedOpenStrategyFile();
	afx_msg void OnBnClickedSaveStrategyFile();
	afx_msg void OnBnClickedVelocityParameter();
	afx_msg void OnBnClickedVelocityParameter2();
	afx_msg void OnBnClickedStrategyParameter();
	afx_msg void OnBnClickedPathTest();
	CDualSlider m_sliderPathTest1;
	CDualSlider m_sliderPathTest2;
	CDualSlider m_sliderPathTest3;
	CDualSlider m_sliderPathTest4;
	CString m_strStrategyFile;
	afx_msg void OnBnClickedGameStartStep();
	CComboBox m_comboRobot01Name;
	CComboBox m_comboRobot02Name;
	CComboBox m_comboRobot03Name;
	CComboBox m_comboRobot04Name;
	CComboBox m_comboRobot05Name;
	CComboBox m_comboRobot06Name;
	CComboBox m_comboRobot07Name;
	CComboBox m_comboRobot08Name;
	CComboBox m_comboRobot09Name;
	CComboBox m_comboRobot10Name;
	CComboBox m_comboRobot11Name;
	CString m_strRobot01Name;
	CString m_strRobot02Name;
	CString m_strRobot03Name;
	CString m_strRobot04Name;
	CString m_strRobot05Name;
	CString m_strRobot06Name;
	CString m_strRobot07Name;
	CString m_strRobot08Name;
	CString m_strRobot09Name;
	CString m_strRobot10Name;
	CString m_strRobot11Name;
	afx_msg void OnBnClickedKickTest();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedResetScreen();
	BOOL m_checkRobot01;
	BOOL m_checkRobot02;
	BOOL m_checkRobot03;
	BOOL m_checkRobot04;
	BOOL m_checkRobot05;
	BOOL m_checkRobot06;
	BOOL m_checkRobot07;
	BOOL m_checkRobot08;
	BOOL m_checkRobot09;
	BOOL m_checkRobot10;
	BOOL m_checkRobot11;
	afx_msg void OnBnClickedCheckRobot01();
	afx_msg void OnBnClickedCheckRobot02();
	afx_msg void OnBnClickedCheckRobot03();
	afx_msg void OnBnClickedCheckRobot04();
	afx_msg void OnBnClickedCheckRobot05();
	afx_msg void OnBnClickedCheckRobot06();
	afx_msg void OnBnClickedCheckRobot07();
	afx_msg void OnBnClickedCheckRobot08();
	afx_msg void OnBnClickedCheckRobot09();
	afx_msg void OnBnClickedCheckRobot10();
	afx_msg void OnBnClickedCheckRobot11();
	BOOL m_checkRoleChange;
	afx_msg void OnBnClickedCheckRoleChange();
	afx_msg void OnBnClickedLoadSetPlay();
	afx_msg void OnBnClickedOpenStrategy();
	CString m_strStrategyFileName;
//	BOOL m_bStrategyGUI;
//	afx_msg void OnBnClickedCheckStrategyGui();
	CComboBox m_comobRobot01Role;
	CComboBox m_comobRobot02Role;
	CComboBox m_comobRobot03Role;
	CComboBox m_comobRobot04Role;
	CComboBox m_comobRobot05Role;
	CComboBox m_comobRobot06Role;
	CComboBox m_comobRobot07Role;
	CComboBox m_comobRobot08Role;
	CComboBox m_comobRobot09Role;
	CComboBox m_comobRobot10Role;
	CComboBox m_comobRobot11Role;
	CString m_strRobot01Role;
	CString m_strRobot02Role;
	CString m_strRobot03Role;
	CString m_strRobot04Role;
	CString m_strRobot05Role;
	CString m_strRobot06Role;
	CString m_strRobot07Role;
	CString m_strRobot08Role;
	CString m_strRobot09Role;
	CString m_strRobot10Role;
	CString m_strRobot11Role;
//	afx_msg void OnBnClickedRadioSituationAttack3();
	afx_msg void OnBnClickedRadioGameStrategyType01();
	afx_msg void OnBnClickedRadioGameStrategyType02();
	BOOL m_radioGameStrategyType;
	afx_msg void OnBnClickedCopyStrategyGui();
	afx_msg void OnBnClickedRobotIdAssign();
	afx_msg void OnBnClickedCheckShowAutoposition();
	BOOL m_bShowAutoposition;
	afx_msg void OnBnClickedAutoposAssign();
	CString m_strSituation;
	CComboBox m_comboSituation;
	afx_msg void OnBnClickedRadioSituation9();
	afx_msg void OnBnClickedRadioSituation10();
	afx_msg void OnBnClickedRadioSituation11();
	afx_msg void OnSelchangeComboSituation();
	afx_msg void OnCbnSelchangeComboRobot04Name();
	afx_msg void OnStnClickedStaticPropGameRobot04();
	afx_msg void OnStnClickedStaticPropGameRobot05();
};
