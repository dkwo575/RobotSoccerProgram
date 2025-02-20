#include "StdAfx.h"
#include "VelocityParameter.h"


CVelocityParameter::CVelocityParameter(void)
{
	m_Acceleration = 3.0;
	m_Deceleration = 3.0;
	m_CentripetalAcceleration = 4.1;
	m_MaxAccelerationLimit = 2.3;
	m_MaxVelocityLimit = 2.5;
	m_PathErrorGain = 13.3;
	m_AngularVelocityErrorPGain = 12;
	m_AngularVelocityErrorDGain = 24;
}


CVelocityParameter::~CVelocityParameter(void)
{
}


void CVelocityParameter::Save(CArchive &ar)
{
	ar << m_Acceleration;
	ar << m_Deceleration;
	ar << m_CentripetalAcceleration;
	ar << m_MaxAccelerationLimit;
	ar << m_MaxVelocityLimit;
	ar << m_PathErrorGain;
	ar << m_AngularVelocityErrorPGain;
	ar << m_AngularVelocityErrorDGain;
}

void CVelocityParameter::Open(CArchive &ar)
{
	ar >> m_Acceleration;
	ar >> m_Deceleration;
	ar >> m_CentripetalAcceleration;
	ar >> m_MaxAccelerationLimit;
	ar >> m_MaxVelocityLimit;
	ar >> m_PathErrorGain;
	ar >> m_AngularVelocityErrorPGain;
	ar >> m_AngularVelocityErrorDGain;
}
