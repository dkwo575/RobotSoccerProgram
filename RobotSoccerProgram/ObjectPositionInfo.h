#pragma once

#include"PointDouble.h"

#define POSITION_INFO_ROBOT_N 11

#if !defined(OBJECT_STATE_NOT_EXIST)
#define OBJECT_STATE_NOT_EXIST	0
#define OBJECT_STATE_REAL		1
#define OBJECT_STATE_VIRTUAL	2
#endif

class CObjectPositionInfo
{
public:
	void Reset();

	struct st_object
	{
		int state;
		CPointDouble pos;
		CPointDouble acceleration;

		CPointDouble velocity;

		int countLost;
	} m_Ball, m_Opp[POSITION_INFO_ROBOT_N];

	struct st_robot
	{
		int state;
		CPointDouble pos;
		CPointDouble acceleration;

		double orientation;
		int countLost;
	} m_Robot[POSITION_INFO_ROBOT_N];
	
	CObjectPositionInfo(void);
	~CObjectPositionInfo(void);
};

