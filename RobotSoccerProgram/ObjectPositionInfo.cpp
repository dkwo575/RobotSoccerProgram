#include "StdAfx.h"
#include "ObjectPositionInfo.h"

CObjectPositionInfo::CObjectPositionInfo()
{
	Reset();
}

CObjectPositionInfo::~CObjectPositionInfo()
{
}

void CObjectPositionInfo::Reset()
{
	m_Ball.state        = OBJECT_STATE_NOT_EXIST;
	m_Ball.pos          = CPointDouble(0,0);
	m_Ball.acceleration = CPointDouble(0,0);
	m_Ball.velocity     = CPointDouble(0,0);

	m_Ball.countLost = 0;

	for( int i=0 ; i<POSITION_INFO_ROBOT_N ; i++ )
	{
		m_Opp[i].state        = OBJECT_STATE_NOT_EXIST;
		m_Opp[i].pos          = CPointDouble(0,0);
		m_Opp[i].acceleration = CPointDouble(0,0);
		m_Opp[i].velocity     = CPointDouble(0,0);
		m_Opp[i].countLost = 0;

		m_Robot[i].state        = OBJECT_STATE_NOT_EXIST;
		m_Robot[i].pos          = CPointDouble(0,0);
		m_Robot[i].orientation        = 0;
		m_Robot[i].acceleration = CPointDouble(0,0);
		m_Robot[i].countLost = 0;
	}
}
