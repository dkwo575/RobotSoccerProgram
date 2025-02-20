#pragma once
class CVelocityParameter2
{
public:
	void Open(CArchive &ar);
	void Save(CArchive &ar);

	CVelocityParameter2(void);
	~CVelocityParameter2(void);

	double m_VcValue;
	double m_K_Vc   ;
	double m_VmaxMin;
	double m_VmaxMax;
	double m_K_Vmax ;
	double m_dVMin  ;
	double m_dVMax  ;
	double m_K_dV   ;

	double m_Ak1;
	double m_Ak2;
	double m_Ak3;
};

