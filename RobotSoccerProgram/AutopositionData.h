#pragma once

#include<vector>
#include<set>

class CAutopositionData
{
public:
	typedef struct _autoposition_data_for_robot
	{
		CString name;
		double x;		// meter
		double y;		// meter
		double orientation;	// degree
	} Robot;

	typedef struct _autoposition_data_for_team
	{
		bool bValid;
		std::vector<Robot> robot;
		CString situation;
	} Team;

	void OpenFile(CString filename);
	void SaveFile(CString filename);

	bool UpdateAutoPositionData(Team team_data);
	Team GetAutoPositionData(CString situation);
	
	CAutopositionData(void);
	~CAutopositionData(void);

	std::vector<Team> m_data;
	std::set<CString> m_setRobotName;
	std::set<CString> m_setSituationName;
};

