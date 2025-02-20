#pragma once

#include"RectDouble.h"
#include<vector>

#define MAX_SITUATION_TIME 300

namespace StrategyGUI_BehaviorType
{
	const CString Velocity              = _T("Behavior_101");
	const CString Wait                  = _T("Behavior_102");
	const CString MoveTo                = _T("Behavior_103");
	const CString OrientationTo         = _T("Behavior_104");
	const CString Goalkeep              = _T("Behavior_105");
	const CString Defense_Wall          = _T("Behavior_106");

	const CString Kick_A                = _T("Behavior_201");
	const CString Kick_B                = _T("Behavior_202");
	const CString Kick_C                = _T("Behavior_203");
	// New Action defined
	const CString Corner_Kick			= _T("Behavior_204");

	const CString AndroSot_Kick1        = _T("Behavior_301");
	const CString AndroSot_Kick2        = _T("Behavior_302");
	const CString AndroSot_Kick3        = _T("Behavior_303");
	const int N = 13; // Increased to 13
}

namespace StrategyGUI_SituationPriority
{
	const CString Default  = _T("SituationPriority_01");
	const CString First    = _T("SituationPriority_02");
	const int N = 2;
}

namespace StrategyGUI_RoleAssignOptionHold
{
	const CString Refresh  = _T("RoleAssignOption_Hold_01");
	const CString Hold     = _T("RoleAssignOption_Hold_02"  );
	const int N = 2;
}

namespace StrategyGUI_RoleAssignMethod
{
	const CString CloseToLocation = _T("RoleAssignMethod_01");
	const CString CloseToBall     = _T("RoleAssignMethod_02");
	const CString GoodToKick      = _T("RoleAssignMethod_03");
	const CString Rest            = _T("RoleAssignMethod_04");
	const int N = 4;
}

namespace StrategyGUI_BehaviorControlType
{
	const CString Once      = _T("BehaviorControl_01");
	const CString Keep      = _T("BehaviorControl_02");
	const CString Temporary = _T("BehaviorControl_03");
	const int N = 3;
}

class CStrategyGUI
{
public:
	CStrategyGUI(void);
	~CStrategyGUI(void);

	enum
	{
		MAX_SITUATION_ROBOT_N = ROBOT_SOCCER_RROGRAM_ROBOT_N,
	};

public:

	enum enumConditionArea
	{
		CONDITION_AREA_RECTANGLE,
		CONDITION_AREA_ELLIPSE
	};

	enum enumConditionBall
	{
		CONDITION_BALL_HOME,
		CONDITION_BALL_OPP,
		CONDITION_BALL_FREE,
		CONDITION_BALL_ALWAYS,
	};




	struct Situation
	{
		CString name;

		CString priority;

		struct SituationValidTime
		{
			int begin_sec;
			int end_sec;
		} time;

		// 상황 정의
		struct SituationCondition
		{
			struct SituationConditionArea
			{
				enumConditionArea type;
				CRectDouble rect;
			} area;

			struct SituationConditionBall
			{
				//enumConditionBall type;
				bool bHome;
				bool bOpp;
				bool bFree;
				double owner_distance;
			} ball;

		} condition;


		// 역할 배정
		struct SituationRoleAssign
		{		
			struct SituationRole
			{
				CString name;

				struct SituationRoleAssignMethod
				{
					CString option_hold;

					CString method;
					CPointDouble pos;
				} assign;
			} role[ROBOT_SOCCER_RROGRAM_ROBOT_N];
		} role_assign;
	};

	struct DirectionInfo
	{
		bool bPosDirection;
		CPointDouble posDirection;
		double direction;
	};

	struct PositionTagetInfo
	{
		bool bBall;
		CPointDouble pos;
		double error;
	};

	struct PositionInfo
	{
		CPointDouble pos;
		double error;
	};

	struct Behavior
	{
		CString type;

		CString controlType;

		struct BehaviorParam
		{
			// 속도/시간
			struct OptionManualVelocity
			{
				double vLinear;
				double vAngular;
				double time;
			} manual_velocity;

			// 대기
			struct OptionWait
			{
				double time;
			} wait;

			// 이동
			struct OptionMove
			{
				struct PositionTagetInfo destination;
			} move_to;

			// 방향 전환
			struct OptionOrientation
			{
				struct DirectionInfo orientation;
			} orientation;

			// 골키퍼
			struct OptionGoalkeep
			{
				double x_pos;
				double y_size;
				double clear_x_size;
				double clear_y_size;
				double clear_ball_speed;
			} goalkeep;

			// 수비 기본
			struct OptionDefenseWall
			{
				CPointDouble posA;
				CPointDouble posB;
				double clear_x_size;
				double clear_ball_speed;
			} defense_wall;

			// 킥 - 기본
			struct OptionKick_A
			{
				struct PositionTagetInfo destination;
				struct DirectionInfo direction;
			} kick_A;

			// 킥 - 발리슛
			struct OptionKick_B
			{
				CPointDouble posA;
				CPointDouble posB;
			} kick_B;

			// 킥 - 공차기 복합 - soty
			struct OptionKick_C
			{
				struct DirectionInfo target;
				struct DirectionInfo approach;
			} kick_C;

		}options;
	};

	struct Role
	{
		CString name;

		std::vector<struct Behavior> vecBehavior;
	};


	Situation GetSituation( int i );
	int GetSituationN();
	void UpdateSituation( int n, Situation situation );
	bool VerifyStrategy();
	void AddSituation( Situation situation );
	void InsertSituation( int n, Situation situation );
	void DeleteSituation( int n );
	int FindSituation( CString name );

	int GetVerifyVerifySituationRectN( int category );
	CRectDouble GetVerifyVerifySituationRect( int category, int rect_i );

	CString GetFileName();
	void SetFileName( CString filename );

	int GetRoleN();
	void AddRole( Role role );
	void InsertRole( int n, Role role );
	Role GetRole( int n );

	int FindRole( CString name );
	int CountRoleInSituation( CString name );
	void ChangeRoleInSituation( CString old_name, CString new_name );

	void UpdateRole( int n, Role role );
	void DeleteRole( int n );

	void OpenFile(CArchive &ar);
	void SaveFile(CArchive &ar);

	void OpenFile_version_1_0(CArchive &ar);


	CString RoleOptionString( int roleID, int behaviorID );

	std::vector<CString> m_vecSituationPriority;
	std::vector<CString> m_vecRoleAssignMethod;
	std::vector<CString> m_vecRoleAssignOption_Hold;
	std::vector<CString> m_vecBehaviorType;
	std::vector<CString> m_vecBehaviorControlType;

	CString GetErrorMsg();

	CRITICAL_SECTION m_critStrategyGUI;

	CString TypeToName( CString type );

protected:

	std::vector<CRectDouble> m_vecVerifySituationRect[3];

	std::vector<Situation> m_vecSituation;
	CString m_filename;

	std::vector<Role> m_vecRole;

	std::vector<CString> m_vecError;
};

