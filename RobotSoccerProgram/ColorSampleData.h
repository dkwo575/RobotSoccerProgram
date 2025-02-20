#pragma once

#include<vector>

class CColorSampleData
{
public:
	COLORREF GetColorREF();
	void SaveFile(CArchive &ar);
	void OpenFile(CArchive &ar);
	void GetMu( double mu[] );
	COLORREF GetRGBData( int p );
	void Clear();
	int RGBMax();
	int RGBMin();
	int DataN();
	void AddData( COLORREF color );

	struct SAMPLE_DATA
	{
		int r;
		int g;
		int b;
	};

	std::vector<struct SAMPLE_DATA> m_data;

	int m_paramRGBmin;
	int m_paramRGBmax;
	double m_paramKeySampleSize;
	int m_paramKeySampleN;

	CColorSampleData();
	~CColorSampleData();


protected:
	int m_min;
	int m_max;
};

