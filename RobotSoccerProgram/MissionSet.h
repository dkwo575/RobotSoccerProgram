#pragma once

#include "Mission.h"	// Added by ClassView

class CMissionSet
{
public:
	void DeleteMission( int i );
	void UpdateRecentMission( CMission mission, int i );
	CMission GetRecentMission();

	int GetRecentMissionID();

	CMission GetMission( int i );

	int MissionN();
	void Complete();
	CMission GetCurrentMission();
	bool HasMission();
	void Reset();
	void Reset_without_Setplay();
	void Add( CMission mission, bool bOverwrite = false );
	void Change( int i, CMission mission );

	CMissionSet(void);
	~CMissionSet(void);

protected:
	void UpdateRecentMission();
	CMission m_missionRecent;
	std::vector<CMission> m_vecMission;
	int m_missionRecentID;
};

