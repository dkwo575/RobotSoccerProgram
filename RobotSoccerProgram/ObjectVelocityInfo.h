#pragma once

#define VELOCITY_INFO_ROBOT_N 11

class CObjectVelocityInfo
{
public:
	int m_Behavior[VELOCITY_INFO_ROBOT_N]; // for AndroSot

	double m_VelocityLeft[VELOCITY_INFO_ROBOT_N];
	double m_VelocityRight[VELOCITY_INFO_ROBOT_N];

	double m_LinearVelocity[VELOCITY_INFO_ROBOT_N];
	double m_AngularVelocity[VELOCITY_INFO_ROBOT_N];

	void Reset();

	CObjectVelocityInfo(void);
	~CObjectVelocityInfo(void);
};

