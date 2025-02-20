#include "StdAfx.h"
#include "Mission.h"


CMission::CMission(void)
{
	Reset();
}


CMission::~CMission(void)
{
}

void CMission::Reset()
{
	bComplete = false;
	bTemporary = false;

	VP2_id = 1; // VP2M_MOVE_TO_WAIT

	type = MissionType::None;
	text = _T("None");
	strState = _T("None");
	
	posDestination.x = 0;
	posDestination.y = 0;

	orientationDestination = 0;
	
	posPath.clear();
}

void CMission::AddPointControl(CPointDouble p)
{
	posPath.push_back( p );
}

void CMission::ChangePointControl(int i, CPointDouble p)
{
	if( i < (int)posPath.size() )
		posPath[i] = p;
}
