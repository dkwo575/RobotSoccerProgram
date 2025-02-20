#pragma once

#include<vector>
#include<set>

class CSetPlayData
{
public:
	typedef struct _setplay_data_for_robot
	{
		CString name;
		CString strSetPlayRole;
	} Robot;

	typedef struct _setplay_data_for_team
	{
		bool bValid;
		std::vector<Robot> robot;
		CString situation;
	} Team;

	void OpenFile(CString filename);
	void SaveFile(CString filename);

	bool UpdateSetplayData(Team team_data);
	Team GetSetplayData(CString situation);
	

	std::vector<Team> m_data;
	std::set<CString> m_setRobotName;
	std::set<CString> m_setSituationName;

	CSetPlayData(void);
	~CSetPlayData(void);
};

