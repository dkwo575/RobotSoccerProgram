#include "StdAfx.h"
#include "VelocityParameter2.h"


CVelocityParameter2::CVelocityParameter2(void)
{
	m_VcValue = 2.0;
	m_K_Vc    = 10.0;
	m_VmaxMin = 0.1;
	m_VmaxMax = 4.0;
	m_K_Vmax  = 10.0;
	m_dVMin   = 0.5;
	m_dVMax   = 1.0;
	m_K_dV    = 10.0;

	m_Ak1     = 0.1;
	m_Ak2     = 0.1;
	m_Ak3     = 0.1;
}


CVelocityParameter2::~CVelocityParameter2(void)
{
}


void CVelocityParameter2::Save(CArchive &ar)
{
	ar << m_VcValue;
	ar << m_K_Vc   ;
	ar << m_VmaxMin;
	ar << m_VmaxMax;
	ar << m_K_Vmax ;
	ar << m_dVMin  ;
	ar << m_dVMax  ;
	ar << m_K_dV   ;

	ar << m_Ak1    ;
	ar << m_Ak2    ;
	ar << m_Ak3    ;
}

void CVelocityParameter2::Open(CArchive &ar)
{
	ar >> m_VcValue;
	ar >> m_K_Vc   ;
	ar >> m_VmaxMin;
	ar >> m_VmaxMax;
	ar >> m_K_Vmax ;
	ar >> m_dVMin  ;
	ar >> m_dVMax  ;
	ar >> m_K_dV   ;

	ar >> m_Ak1    ;
	ar >> m_Ak2    ;
	ar >> m_Ak3    ;
}
