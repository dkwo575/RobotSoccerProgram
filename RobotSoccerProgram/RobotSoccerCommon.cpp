#include "StdAfx.h"
#include "RobotSoccerCommon.h"


CRobotSoccerCommon::CRobotSoccerCommon(void)
{
	m_pLookUpTable = NULL;
	m_pImageGrabber = NULL;
	m_pGround = NULL;
}


CRobotSoccerCommon::~CRobotSoccerCommon(void)
{
}

void CRobotSoccerCommon::SetLookUpTable(CLookUpTable *pLUT)
{
	m_pLookUpTable = pLUT;
}

void CRobotSoccerCommon::SetImageGrabber(CImageGrabber_Standard* pImageGrabber)
{
	m_pImageGrabber = pImageGrabber;
}

void CRobotSoccerCommon::SetGround(CGround* pGround)
{
	m_pGround = pGround;
}
