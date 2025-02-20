#pragma once

#include"PointDouble.h"
#include<vector>
#include"RectDouble.h"

class CSituation
{
public:
	typedef struct
	{
		CString name;
		CRectDouble rect;
	} st_situation;

	void Reset();
	void Update( CPointDouble pos );

	CString GetCurrentSituation();
	void SetCurrentSituation( CString situation );

	int BallChaser();
	void SetBallChaser( int chaser );

	int BallOwner();
	void SetBallOwner( int owner );


	CSituation(void);
	~CSituation(void);

protected:
	std::vector<st_situation> m_DB;

	CString m_current;
	CString m_previous;

	int m_ballChaserID;
	int m_ballOwnerID;

	int m_offenseType;
	int m_defenseType;
};

