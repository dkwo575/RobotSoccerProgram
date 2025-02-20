#include "StdAfx.h"
#include "AutopositionData.h"


CAutopositionData::CAutopositionData(void)
{
	m_data.clear();
}


CAutopositionData::~CAutopositionData(void)
{
}


CAutopositionData::Team CAutopositionData::GetAutoPositionData(CString situation)
{
	for( int i=0 ; i<(int)m_data.size() ; i++ )
	{
		if( m_data[i].situation == situation )
		{
			return m_data[i];
		}
	}

	CAutopositionData::Team null_data;
	null_data.bValid = false;

	return null_data;
}

bool CAutopositionData::UpdateAutoPositionData(CAutopositionData::Team team_data)
{
	for( int i=0 ; i<(int)m_data.size() ; i++ )
	{
		if( m_data[i].situation == team_data.situation )
		{
			m_data[i] = team_data;
	
			for( int j=0 ; j<(int)team_data.robot.size() ; j++ )
			{
				m_setRobotName.insert( team_data.robot[j].name );
			}

			m_setSituationName.insert( team_data.situation );

			return false;
		}
	}

	m_data.push_back( team_data );

	for( int j=0 ; j<(int)team_data.robot.size() ; j++ )
	{
		m_setRobotName.insert( team_data.robot[j].name );
	}

	m_setSituationName.insert( team_data.situation );

	return true;
}

void CAutopositionData::OpenFile(CString filename)
{
	CFile file;
	
	if( file.Open(filename, CFile::modeRead ) == FALSE )
	{
		AfxMessageBox(_T("Failed to open the file. (CAutopositionData::OpenFile)"));
		return;
	}
	
	CArchive ar( &file, CArchive::load );
	

	m_data.clear();
	m_setRobotName.clear();
	m_setSituationName.clear();

	CString tmp;


	while(1)
	{
		ar >> tmp;
		if( tmp == _T("-END-") )
			break;

		if( tmp == _T("team data begin") )
		{
			CAutopositionData::Team new_data;
			new_data.bValid = true;

			while(1)
			{
				ar >> tmp;

				if( tmp == _T("team data end") )
				{
					m_data.push_back( new_data );
					break;
				}

				if( tmp == _T("situation") )
				{
					ar >> new_data.situation;
					m_setSituationName.insert( new_data.situation );
				}

				if( tmp == _T("robot data") )
				{
					CAutopositionData::Robot robot;
					ar >> robot.name;
					ar >> robot.x;
					ar >> robot.y;
					ar >> robot.orientation;
					new_data.robot.push_back( robot );

					m_setRobotName.insert( robot.name );
				}
			}
		}
	}
	
	ar.Close();
	file.Close();
}

void CAutopositionData::SaveFile(CString filename)
{
	CFile file;
	
	file.Open( filename, CFile::modeCreate | CFile::modeWrite );
	CArchive ar( &file, CArchive::store );
	
	CString tmp;
	for( int i=0 ; i<(int)m_data.size() ; i++ )
	{
		if( m_data[i].bValid )
		{
			tmp = _T("team data begin");
			ar << tmp;

			tmp = _T("situation");
			ar << tmp;
			ar << m_data[i].situation;

			for( int j=0 ; j<(int)m_data[i].robot.size() ; j++ )
			{
				tmp = _T("robot data");
				ar << tmp;
				ar << m_data[i].robot[j].name;
				ar << m_data[i].robot[j].x;
				ar << m_data[i].robot[j].y;
				ar << m_data[i].robot[j].orientation;
			}

			tmp = _T("team data end");
			ar << tmp;
		}
	}
	

	tmp = _T("-END-");
	ar << tmp;

	ar.Close();
	file.Close();
}
