#pragma once


#include"PropertyPageRobotSoccer.h"
#include"RobotSoccerCommon.h"
#include "afxwin.h"

#include"Ground.h"
#include"StrategyGUI.h"
#include"RectMouse.h"

#include"RobotDraw.h"

#include"DualSlider.h"


// CPropertyPageStrategyGUI dialog

namespace StrategyGUI_List 
{
	enum Enum
	{
		Situation,
		RoleAssign,
		Role,
		Behavior,
		None
	};
}


class CPropertyPageStrategyGUI : public CPropertyPageRobotSoccer, public CRobotSoccerCommon
{
	DECLARE_DYNAMIC(CPropertyPageStrategyGUI)
public:
	CStrategyGUI m_strategyGUI;

	void OpenFile(CString filename);
	void SaveFile(CString filename);

	CFrameDC m_dcFitness;
	CFrameDC m_dcFitness_share;
	void GenerateDrawInformation();
	void DrawSituation( CRectMouse rectSituationArea );
	void DrawSituation( CStrategyGUI::Situation situation );
	void DrawDisplay(void);
	void DrawDisplay_Situation( CString& strTitle, CString& strTitleInfo, CString& strMsg );
	void DrawDisplay_RoleAssign( CString& strTitle, CString& strTitleInfo, CString& strMsg );
	void DrawDisplay_Behavior( CString& strTitle, CString& strTitleInfo, CString& strMsg );

	MouseCapture::Enum DisplayRButtonDown( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayRButtonUp( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayLButtonDown( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayLButtonUp( UINT nFlags, CPoint point );
	MouseCapture::Enum DisplayMouseMove( UINT nFlags, CPoint point );


	CPropertyPageStrategyGUI();
	virtual ~CPropertyPageStrategyGUI();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_STRATEGY_GUI };

protected:
	CRITICAL_SECTION m_critPropertyPageStrategyGUI;

	void DrawRectArrowButton( CRect rect, CString type, COLORREF color );
	void DisplayPositionErrorUI( double error, bool bBall );
	void DisplayBallDestination( bool bBall );
	void DisplayPosDirection( bool bPosDirection, CString strTitle );
	void DisplayPosApproach( bool bPosDestinationGuide, CString strTitle );

	void DrawArrow(CPointDouble posBegin, CPointDouble posEnd, double orientation, double size_length, double size_angle, COLORREF color );
	double ccw(CPointDouble p1, CPointDouble p2, CPointDouble p3);

	struct OptionsGUI
	{
		struct OptionsGUI_Goalkeep
		{

		} goalkeep;
	} m_optionsGUI;

	CRectDouble m_rectGK_y_size_up;
	CRectDouble m_rectGK_y_size_down;
	CRectDouble m_rectGK_x_pos_left;
	CRectDouble m_rectGK_x_pos_right;
	CRectDouble m_rectGK_clear_y_size_up;
	CRectDouble m_rectGK_clear_y_size_down;
	CRectDouble m_rectGK_clear_x_pos_left;
	CRectDouble m_rectGK_clear_x_pos_right;
	CRectDouble m_rectGK_clear_ball_speed_up;
	CRectDouble m_rectGK_clear_ball_speed_down;

	CRectDouble m_rectErrorButtonL;
	CRectDouble m_rectErrorButtonR;
	CRectDouble m_rectBallDestination;
	CRectDouble m_rectPosDirection;
	CRectDouble m_rectPosApproach;

	CRectDouble m_rectVelocityButton[6];

	CImageList m_ImageListSituation;
	CImageList m_ImageListSituationRoleAssign;
	CImageList m_ImageListRole;
	CImageList m_ImageListBehavior;

	void SelectSituation( int nSelect );
	void SelectRole( int nSelect );

	CRectMouse m_rectSituationArea;
	void SelectSituation_UpdatePage();

	int m_focusedSituationID;
	int m_focusedSituationRoleID;
	int m_focusedRoleID;
	int m_focusedBehaviorID;

	StrategyGUI_List::Enum m_focusedList;

	bool m_bEditLabelMode;
	bool m_bEditLabelEnter;


	void UpdateListSituation();

	void UpdateListRole();

	CGround m_ground;

	bool m_bLButton;
	bool m_bRButton;
	CPoint m_mouseDownPoint;
	CPoint m_mouseMovePoint;
	CPoint m_mouseUpPoint;
	CPointDouble m_posBallClink_screen;

	bool m_bDragMove;

	CPointDouble m_posRobotGUI;
	double m_orientationRobotGUI;

	CStrategyGUI::Behavior m_behaviorCopy;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_comboRoleAssign;
	CString m_strFileName;
	afx_msg void OnBnClickedAssignRoleToSituation();
	// afx_msg void OnBnClickedTutorialGui();
	afx_msg void OnBnClickedOpenStrategyGui();
	afx_msg void OnBnClickedSaveStrategyGui();
	afx_msg void OnSelchangeComboRoleAssign();
	BOOL m_bBallHome;
	BOOL m_bBallOpp;
	BOOL m_bBallFree;
	afx_msg void OnBnClickedCheckBallSituation1();
	afx_msg void OnBnClickedCheckBallSituation2();
	afx_msg void OnBnClickedCheckBallSituation3();
	afx_msg void OnBnClickedCheckShowAllSituation();
	BOOL m_bShowAllSituation;
	CListCtrl m_listSituationRoleAssign;
	afx_msg void OnItemchangedListSituationRole(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listSituation;
	afx_msg void OnItemchangedListSituation(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listRole;
	afx_msg void OnItemchangedListRole(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listRoleDefinition;
	CComboBox m_comboBehavior;
	afx_msg void OnBnClickedAddBehavior();
	afx_msg void OnBnClickedDeleteBehavior();
	afx_msg void OnItemchangedListRoleDefinition(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAddRole();
	afx_msg void OnBnClickedDeleteRole();
	afx_msg void OnEndlabeleditListRole(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAddSituation();
	afx_msg void OnBnClickedDeleteSituation();
	afx_msg void OnEndlabeleditListSituation(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedListSituationPriorityUp();
	afx_msg void OnBnClickedListSituationPriorityDown();
	afx_msg void OnBnClickedListBehaviorOrderUp();
	afx_msg void OnBnClickedListBehaviorOrderDown();
	afx_msg void OnBnClickedCopySituation();
	afx_msg void OnBnClickedCopyRole();
	afx_msg void OnBnClickedListRoleOrderUp();
	afx_msg void OnBnClickedListRoleOrderDown();
	afx_msg void OnSetfocusListSituation(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSetfocusListSituationRoleAssign(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSetfocusListRole(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSetfocusListRoleDefinition(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEndlabeleditListRoleDefinition(NMHDR *pNMHDR, LRESULT *pResult);
	CDualSlider m_sliderBallOwnerDistance;
	afx_msg void OnBnClickedListSituationRoleAssignOrderUp();
	afx_msg void OnBnClickedListSituationRoleAssignOrderDown();
//	CString m_strRoleAssign;
	CComboBox m_comboRoleAssign_Hold;
	afx_msg void OnSelchangeComboRoleAssign2();
	CDualSlider m_sliderSituationTime;
	BOOL m_bShowVerifySituation;
	afx_msg void OnBnClickedCheckShowVerifySituation();
	CComboBox m_comboSituationPriority;
	afx_msg void OnSelchangeComboSituationPriority();
	CComboBox m_comboBehaviorControlType;
	afx_msg void OnSelchangeComboBehaviorControlType();
	afx_msg void OnBnClickedCopyBehavior();
	afx_msg void OnBnClickedPasteBehavior();
};
