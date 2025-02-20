#pragma once

#define VISION_ARRAY_ID_0 0
#define VISION_ARRAY_ID_1 1
#define VISION_ARRAY_ID_2 2
#define VISION_ARRAY_ID_3 3
#define VISION_ARRAY_ID_4 4
#define VISION_ARRAY_ID_5 5
#define VISION_ARRAY_ID_6 6
#define VISION_ARRAY_ID_7 7

#define VISION_PATCH_MASK_0 (unsigned char)(1<<VISION_ARRAY_ID_0)
#define VISION_PATCH_MASK_1 (unsigned char)(1<<VISION_ARRAY_ID_1)
#define VISION_PATCH_MASK_2 (unsigned char)(1<<VISION_ARRAY_ID_2)
#define VISION_PATCH_MASK_3 (unsigned char)(1<<VISION_ARRAY_ID_3)
#define VISION_PATCH_MASK_4 (unsigned char)(1<<VISION_ARRAY_ID_4)
#define VISION_PATCH_MASK_5 (unsigned char)(1<<VISION_ARRAY_ID_5)
#define VISION_PATCH_MASK_6 (unsigned char)(1<<VISION_ARRAY_ID_6)
#define VISION_PATCH_MASK_7 (unsigned char)(1<<VISION_ARRAY_ID_7)

class CLookUpTable
{
public:
	void SetColor( int n, int r, int g, int b );
	bool GetData( int p, int r, int g, int b );
	void SetData( int p, int r, int g, int b, bool state );
	bool IsValidData( int n );
	COLORREF GetLUTColor( unsigned char mask );
	void OpenFile(CArchive &ar);
	void SaveFile(CArchive &ar);
	unsigned char GetLUTData( int r, int g, int b );
	void ClearLUT( int n );
	COLORREF GetColor( int n );


	CLookUpTable(void);
	~CLookUpTable(void);

	unsigned char m_LUT[256][256][256];

protected:
	bool m_bValid[8];
	COLORREF m_color[8];
};

