#pragma once

/*
	Last updated : 2012. 5. 24.
	Imagegrabber class based on OpenCV
	 - This class has "image buffer" implemmented by IplImage.
*/

#include"cv.h"
#include"highgui.h"
#include "imagegrabber_standard.h"

class CImageGrabber_File :
	public CImageGrabber_Standard
{
public:
//	void SetShowPosition( CPoint posShow );

//	int Width();
//	int Height();

//	bool IsReady();

//	virtual void Suspend();
//	virtual void Resume();

	virtual bool Initialize(const char* filename);
	bool Initialize();
	virtual bool Free();
	virtual void UpdateImage();
	
	void GetColor( unsigned char &r, unsigned char &g, unsigned char &b, int x, int y, int camera );
	COLORREF GetColor( int x, int y, int camera = 0 );
	COLORREF GetColor( int p, int camera = 0 );
	COLORREF GetColorFloat( double x, double y, int camera = 0 );
	
	virtual void DrawToDC( CDC *pDC, int x, int y );

	void HookFunction( void (*hFunc)(void* main_class), void* UserPtr );
	void UnhookFunction( void (*hFunc)(void* main_class), void* UserPtr );
	void UnhookFunction();
	void InfiniteLoop();


	CImageGrabber_File(void);
	~CImageGrabber_File(void);

protected:
	CRITICAL_SECTION m_critImageGrabber;

	IplImage* m_imageSource;
	IplImage* m_imageAccess;
};

