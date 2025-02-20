#pragma once
class CTimeCheck
{
public:
	double GetTimeMS();
	void Start();
	double Stop();
	double Check();
	double GetTimeSec();

	CTimeCheck(void);
	~CTimeCheck(void);

protected:
	LARGE_INTEGER m_PCFrequency;
	LARGE_INTEGER m_start;
	LARGE_INTEGER m_stop;
	double m_timeMS;
	bool m_bStart;
};

