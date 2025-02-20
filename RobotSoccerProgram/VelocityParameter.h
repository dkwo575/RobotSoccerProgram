#pragma once
class CVelocityParameter
{
public:
	CVelocityParameter(void);
	~CVelocityParameter(void);

	void Open(CArchive &ar);
	void Save(CArchive &ar);

	double m_Acceleration;
	double m_Deceleration;
	double m_CentripetalAcceleration;
	double m_MaxAccelerationLimit;
	double m_MaxVelocityLimit;
	double m_PathErrorGain;
	double m_AngularVelocityErrorPGain;
	double m_AngularVelocityErrorDGain;
};

