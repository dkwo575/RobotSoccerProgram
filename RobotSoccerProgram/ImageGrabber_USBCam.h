#pragma once

/*
	Last updated : 2012. 5. 24.
	Imagegrabber class for USB camera
*/

#include"cv.h"
#include"highgui.h"
#include "imagegrabber_file.h"

class CImageGrabber_USBCam :
	public CImageGrabber_File
{
public:
//	void SetShowPosition( CPoint posShow );

//	int Width();
//	int Height();

//	bool IsReady();

//	virtual void Suspend();
//	virtual void Resume();

	void SimulationMode( bool bSimulationMode );

	bool ChangeCamera(const char* filename);
	bool ChangeCamera(int id);

	bool Initialize(const char* filename);
	bool Initialize(int id);
	bool Initialize();
	bool Free();
	void UpdateImage();
	
	void DrawToDC( CDC *pDC, int x, int y );

	void HookFunction( void (*hFunc)(void* main_class), void* UserPtr );
	void UnhookFunction( void (*hFunc)(void* main_class), void* UserPtr );
	void UnhookFunction();
	void InfiniteLoop();


	CImageGrabber_USBCam(void);
	~CImageGrabber_USBCam(void);

protected:
	bool m_bSimulationMode;
	bool m_bFileMode;
	bool m_bVideoMode;

	CvCapture* m_Capture;
};

