#include "StdAfx.h"
#include "MissionSet.h"


CMissionSet::CMissionSet(void)
{
	Reset();
}


CMissionSet::~CMissionSet(void)
{
}


void CMissionSet::Reset()
{
	UpdateRecentMission();

	m_vecMission.clear();

	m_missionRecentID = -1;
}

void CMissionSet::Reset_without_Setplay()
{
}

void CMissionSet::Add(CMission mission, bool bOverwrite )
{
	bool bAdd = true;
	/*
	int n = m_vecMission.size();
	
	if( bOverwrite )
	{

		if( n > 1 )
		{
			if( mission.type == m_vecMission[n-1].type )
			{
				m_vecMission[n-1] = mission;
				bAdd = false;
			}
		}

		if( n == 1 )
		{
			if( mission.type == m_vecMission[n-1].type && mission.type != CMission::MANUAL_VELOCITY )
			{
				m_vecMission[0] = mission;
				bAdd = false;

				UpdateRecentMission();
			}

		}
	}
	*/


	if( bAdd )
	{
		m_vecMission.push_back( mission );
	}

	UpdateRecentMission();
}

void CMissionSet::Change( int i, CMission mission)
{
	if( i < (int)m_vecMission.size() )
	{
		m_vecMission[i] = mission;
		UpdateRecentMission();
	}
}

void CMissionSet::DeleteMission( int i )
{
	if( i >= 0 && i < (int)m_vecMission.size() )
	{
		auto it = m_vecMission.begin()+i;
		m_vecMission.erase( it );
	}
}


bool CMissionSet::HasMission()
{
	bool bResult;

	bResult = (m_vecMission.size() != 0);		

	return bResult;
}

CMission CMissionSet::GetMission( int i )
{
	CMission mission;
		
	if( i < (int)m_vecMission.size() )
	{
		mission = m_vecMission[i];
	}

	return mission;

}

CMission CMissionSet::GetCurrentMission()
{
	CMission mission;
		
	if( HasMission() )
	{
		mission = m_vecMission[0];
	}

	return mission;
}

CMission CMissionSet::GetRecentMission()
{
	return m_missionRecent;
}


void CMissionSet::Complete()
{
	if( HasMission() )
	{
		UpdateRecentMission();

		m_vecMission.erase( m_vecMission.begin() );

		if( HasMission() )
		{
			UpdateRecentMission();
		}
	}
}

int CMissionSet::MissionN()
{
	int missionN;

	missionN = m_vecMission.size();

	return missionN;
}


void CMissionSet::UpdateRecentMission()
{
	/*
	if( HasMission() )
	{
		m_missionRecent = *m_vecMission.begin();
	}
	else
	{
		m_missionRecent.type = MissionType::None;
	}
	*/
}

void CMissionSet::UpdateRecentMission( CMission mission, int i )
{
	m_missionRecent = mission;
	m_missionRecentID = i;
}

int CMissionSet::GetRecentMissionID()
{
	return m_missionRecentID;
}