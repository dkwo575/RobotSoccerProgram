#pragma once

#include "PointDouble.h"
#include<vector>

#include "StrategyGUI.h"

namespace MissionType
{
	enum Enum
	{
		None,

		Goalkeeper_Escape,
		Goalkeeper_Clear,
		Goalkeeper_Basic,
		Goalkeeper_Trace,

		Defense_Wall_Clear,
		Defense_Wall,
		Defense_Wall_Trace,

		MoveTo,
		MoveToKick,
		OrientationTo,
		Wait,
		ManualVelocity,

		WaitAndKick,
		// New Action
		CornerKick,
	};
}

class CMission
{
public:
	void Reset();

	CPointDouble tmp;


	bool bTemporary;
	bool bComplete;

	int type;	
	CString strState;
	CStrategyGUI::Behavior behavior;

	int VP2_id;
	CString text;

	CPointDouble posDestination;
	double orientationDestination;

	// CMission::SPLINE_PATH
	std::vector<CPointDouble> posPath;
	void ChangePointControl( int i , CPointDouble p );
	void AddPointControl( CPointDouble p );

	CMission(void);
	~CMission(void);
};

