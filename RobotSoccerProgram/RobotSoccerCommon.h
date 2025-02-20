#pragma once

#include"LookUpTable.h"
#include"ImageGrabber_Standard.h"
#include"Ground.h"


class CRobotSoccerCommon
{
public:
	void SetLookUpTable(CLookUpTable *pLUT);
	void SetImageGrabber(CImageGrabber_Standard* pImageGrabber);
	void SetGround(CGround* pGround);

	CRobotSoccerCommon(void);
	~CRobotSoccerCommon(void);

protected:
	CLookUpTable* m_pLookUpTable;
	CImageGrabber_Standard* m_pImageGrabber;
	CGround* m_pGround;


};

