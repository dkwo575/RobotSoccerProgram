#include "StdAfx.h"
#include "ObjectVelocityInfo.h"


CObjectVelocityInfo::CObjectVelocityInfo(void)
{
	Reset();
}


CObjectVelocityInfo::~CObjectVelocityInfo(void)
{
}

void CObjectVelocityInfo::Reset()
{
	for( int i=0 ; i<VELOCITY_INFO_ROBOT_N ; i++ )
	{
		m_VelocityLeft[i] = 0;
		m_VelocityRight[i] = 0;

		m_LinearVelocity[i] = 0;
		m_AngularVelocity[i] = 0;

		m_Behavior[i] = 32;
	}
}
