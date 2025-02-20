#include "StdAfx.h"
#include "LookUpTable.h"



CLookUpTable::CLookUpTable()
{
	ZeroMemory( m_LUT, sizeof(m_LUT) );

	for( int i=0 ; i<8 ; i++ )
		m_bValid[i] = false;
}

CLookUpTable::~CLookUpTable()
{
}

COLORREF CLookUpTable::GetLUTColor(unsigned char mask)
{
	for( int i=0 ; i<8 ; i++ )
	{
		unsigned char mask2 = (unsigned char)(1<<i);

		if( mask &  mask2 )
			return m_color[i];
	}

	return RGB(0,0,0); // logically impossible
}

COLORREF CLookUpTable::GetColor(int n)
{
	if( n<0 || n>=8 ) return RGB(0,0,0);

	if( !m_bValid[n] ) return RGB(0,0,0);
	
	return m_color[n];
}

void CLookUpTable::ClearLUT(int n)
{
	if( n<0 || n>=8 ) return;

	unsigned char mask = (unsigned char)(1<<n);
	unsigned char unmask = 0xFF-mask;

	for( int r=0 ; r<256 ; r++ )
		for( int g=0 ; g<256 ; g++ )
			for( int b=0 ; b<256 ; b++ )
			{
				m_LUT[r][g][b] &= unmask;
			}

	m_color[n] = RGB(0,0,0);
	m_bValid[n] = false;
}

unsigned char CLookUpTable::GetLUTData(int r, int g, int b)
{
	return m_LUT[r][g][b];
}

void CLookUpTable::SaveFile(CArchive &ar)
{
	for( int i=0 ; i<8 ; i++ )
	{
		ar << m_bValid[i];
		ar << m_color[i];
	}

	for( int r=0 ; r<256 ; r++ )
	{
		for( int g=0 ; g<256 ; g++ )
		{
			for( int b=0 ; b<256 ; b++ )
			{
				ar << m_LUT[r][g][b];
			}
		}
	}
}

void CLookUpTable::OpenFile(CArchive &ar)
{
	for( int i=0 ; i<8 ; i++ )
	{
		ar >> m_bValid[i];
		ar >> m_color[i];
	}

	for( int r=0 ; r<256 ; r++ )
	{
		for( int g=0 ; g<256 ; g++ )
		{
			for( int b=0 ; b<256 ; b++ )
			{
				ar >> m_LUT[r][g][b];
			}
		}
	}
}

bool CLookUpTable::IsValidData(int n)
{
	if( n<0 || n>=8 ) return false;

	return m_bValid[n];
}


void CLookUpTable::SetData( int p, int r, int g, int b, bool state )
{
	unsigned char mask = (unsigned char)(1<<p);
	unsigned char unmask = !mask;

	//m_LUT[r][g][b] &= unmask;
	m_LUT[r][g][b] |= mask;
}

bool CLookUpTable::GetData(int p, int r, int g, int b)
{
	unsigned char mask = (unsigned char)(1<<p);

	if(m_LUT[r][g][b]&mask)
		return true;

	return false;
}

void CLookUpTable::SetColor(int n, int r, int g, int b)
{
	m_bValid[n] = true;
	m_color[n] = RGB( r, g, b );
}
