#pragma once

/*
	Last updated : 2012. 5. 24.
	Empty class for Inheritancing
	 - This class does not have "image buffer", "processing algorithm", etc.
*/

class CImageGrabber_Standard
{
public:
	void SetShowPosition( CPoint posShow );

	int Width();
	int Height();
	
	bool IsReady();

	virtual void Suspend();	// not using
	virtual void Resume();	// not using

	virtual bool Initialize();
	virtual bool Free();
	virtual void UpdateImage();
	
	virtual void GetColor( unsigned char &r, unsigned char &g, unsigned char &b, int x, int y, int camera = 0 );
	virtual COLORREF GetColor( int x, int y, int camera = 0 );
	virtual COLORREF GetColor( int p, int camera = 0 );
	virtual COLORREF GetColorFloat( double x, double y, int camera = 0 );
	
	virtual void DrawToDC(CDC *pDC, int x, int y);

	virtual void HookFunction( void (*hFunc)(void* main_class), void* UserPtr );
	virtual void UnhookFunction( void (*hFunc)(void* main_class), void* UserPtr );
	virtual void UnhookFunction();
	void InfiniteLoop();

	CImageGrabber_Standard(void);
	~CImageGrabber_Standard(void);

protected:
	CWinThread *m_pThreadCore;
	bool m_bThreadSuspend;
	void (*m_HookFunction)(void* main_class);
	void *m_HookParameter;

	bool m_bInitialize;

	long m_ImageSizeX;
	long m_ImageSizeY;

	CPoint m_posShow;
};

