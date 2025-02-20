#include "StdAfx.h"
#include "Situation.h"


CSituation::CSituation(void)
{
	Reset();

	st_situation st;
	st.name = "Defense";
	st.rect = CRectDouble( 0.00, 0.00, 0.50, 1.30 );
	m_DB.push_back( st );

	st.name = "Offense";
	st.rect = CRectDouble( 0.50, 0.00, 1.50, 1.30 );
	m_DB.push_back( st );
}


CSituation::~CSituation(void)
{
}

void CSituation::Reset()
{
	m_current = "";
	m_previous = "";
	m_ballChaserID = -1;
	m_ballOwnerID = -1;

	m_DB.clear();
}

void CSituation::Update( CPointDouble pos )
{
	for( int i=0 ; i<(int)m_DB.size() ; i++ )
	{
		if( m_DB[i].rect.left <= pos.x && pos.x <= m_DB[i].rect.right 
		 && m_DB[i].rect.top  <= pos.y && pos.y <= m_DB[i].rect.bottom )
		{
			SetCurrentSituation( m_DB[i].name );
			break;
		}
	}
}

CString CSituation::GetCurrentSituation(){ return m_current; }
void CSituation::SetCurrentSituation( CString situation )
{
	m_previous = m_current;
	m_current = situation;
}

int CSituation::BallChaser(){ return m_ballChaserID; }
void CSituation::SetBallChaser( int chaser ){ m_ballChaserID = chaser; }

int CSituation::BallOwner(){ return m_ballOwnerID; }
void CSituation::SetBallOwner( int owner ){ m_ballOwnerID = owner; }

