#include "StdAfx.h"
#include "TimeCheck.h"



CTimeCheck::CTimeCheck()
{
	m_bStart = false;
	m_timeMS = 0;
	QueryPerformanceFrequency(&m_PCFrequency);
}

CTimeCheck::~CTimeCheck()
{

}

void CTimeCheck::Start()
{
	m_bStart = true;
	QueryPerformanceCounter( &m_start );
}

double CTimeCheck::Check()
{
	QueryPerformanceCounter( &m_stop );
	if( m_bStart )
		m_timeMS = ((double)(m_stop.QuadPart - m_start.QuadPart)/((double)m_PCFrequency.QuadPart/1000.0));
	else
		m_timeMS = 0;

	return m_timeMS;
}

double CTimeCheck::Stop()
{
	QueryPerformanceCounter( &m_stop );
	if( m_bStart )
		m_timeMS = ((double)(m_stop.QuadPart - m_start.QuadPart)/((double)m_PCFrequency.QuadPart/1000.0));
	else
		m_timeMS = 0;

	m_bStart = false;

	return m_timeMS;
}

double CTimeCheck::GetTimeSec()
{
	return m_timeMS/1000.0;
}

double CTimeCheck::GetTimeMS()
{
	return m_timeMS;
}
