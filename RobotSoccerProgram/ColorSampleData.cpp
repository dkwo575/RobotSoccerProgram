#include "StdAfx.h"
#include "ColorSampleData.h"


CColorSampleData::CColorSampleData(void)
{
	Clear();
}


CColorSampleData::~CColorSampleData(void)
{
}


void CColorSampleData::AddData(COLORREF color)
{
	struct SAMPLE_DATA new_data; 

	new_data.r = GetRValue(color);
	new_data.g = GetGValue(color);
	new_data.b = GetBValue(color);

	for( int i=0 ; i<(int)m_data.size() ; i++ )
	{
		if( m_data[i].r == new_data.r
		 && m_data[i].g == new_data.g 
		 && m_data[i].b == new_data.b )
		{
			return;
		}
	}

	if( m_data.size() == 0 )
	{
		m_min = new_data.r+new_data.g+new_data.b;
		m_max = new_data.r+new_data.g+new_data.b;
	}
	else
	{
		m_min = min( m_min, new_data.r+new_data.g+new_data.b );
		m_max = max( m_max, new_data.r+new_data.g+new_data.b );
	}

	m_data.push_back( new_data );
}

int CColorSampleData::DataN()
{
	return (int)m_data.size();
}

int CColorSampleData::RGBMin()
{
	return m_min;
}

int CColorSampleData::RGBMax()
{
	return m_max;
}

void CColorSampleData::Clear()
{
	m_data.clear();
	m_min = 0;
	m_max = 0;

	m_paramRGBmin = 0;
	m_paramRGBmax = 765;
	m_paramKeySampleSize = 0.05;
	m_paramKeySampleN = 0;
}

COLORREF CColorSampleData::GetRGBData(int p)
{
	if( p<0 || p > (int)m_data.size() )
		return RGB(0,0,0);

	return RGB( m_data[p].r, m_data[p].g, m_data[p].b );
}

void CColorSampleData::GetMu( double mu[] )
{
	if( m_data.size() <= 0 )
	{
		mu[0] = 0;
		mu[1] = 0;
		mu[2] = 0;

		return;
	}

	int sum[3] = {0,0,0};
	for( int i=0 ; i<(int)m_data.size() ; i++ )
	{
		sum[0] += m_data[i].r;
		sum[1] += m_data[i].g;
		sum[2] += m_data[i].b;
	}

	mu[0] = (double)sum[0]/m_data.size();
	mu[1] = (double)sum[1]/m_data.size();
	mu[2] = (double)sum[2]/m_data.size();
}

COLORREF CColorSampleData::GetColorREF()
{
	double mu[3];
	GetMu( mu );

	return RGB( (int)mu[0], (int)mu[1], (int)mu[2] );
}

void CColorSampleData::OpenFile(CArchive &ar)
{
	int dataN;
	ar >> dataN;
	ar >> m_min;
	ar >> m_max;
	
	for( int i=0 ; i<dataN ; i++ )
	{
		struct SAMPLE_DATA new_data;
		ar >> new_data.r;
		ar >> new_data.g;
		ar >> new_data.b;

		m_data.push_back( new_data );
	}
}

void CColorSampleData::SaveFile(CArchive &ar)
{
	ar << (int)m_data.size();
	ar << m_min;
	ar << m_max;

	for( int i=0 ; i<(int)m_data.size() ; i++ )
	{
		ar << m_data[i].r;
		ar << m_data[i].g;
		ar << m_data[i].b;
	}
}

