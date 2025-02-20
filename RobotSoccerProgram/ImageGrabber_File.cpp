#include "StdAfx.h"
#include "ImageGrabber_File.h"



CImageGrabber_File::CImageGrabber_File()
{
	InitializeCriticalSection(&m_critImageGrabber);

	CImageGrabber_Standard::CImageGrabber_Standard();

	m_imageSource = NULL;
	m_imageAccess = NULL;
}

CImageGrabber_File::~CImageGrabber_File()
{
	Free();
	DeleteCriticalSection(&m_critImageGrabber);
}

/////////////////////////////////////////////////////////////////////////
// Image grabber
/////////////////////////////////////////////////////////////////////////

bool CImageGrabber_File::Initialize()
{
	return Initialize(NULL);
}

bool CImageGrabber_File::Initialize(const char* filename)
{
	if( m_bInitialize ) return false; // 이미 로딩이 되었으면 삭제하고 다시 로딩해야하는데...
	
	CString pathname;

	if( filename == NULL || filename[0] == '\0' )
	{
		TCHAR szFilter[] = _T("Image (*.bmp,*.jpg, *.gif, *.png, *.tif, *.mng, *.ico, *.pcx, *.tga, *.wmf, *.jbg, *.j2k)|*.bmp;*.jpg;*.gif;*.png;*.tif;*.mng;*.ico;*.pcx;*.tga;*.wmf;*.jbg;*.j2k|All Files(*.*)|*.*||");
		CFileDialog fileDlg(TRUE, _T("default"), _T("default"), NULL, szFilter);
		
		if(IDOK == fileDlg.DoModal())
		{
			pathname = fileDlg.GetPathName();
		}
		else
		{
			return false;
		}
	}
	else
	{
		pathname = filename;
	} 

	m_imageSource = cvLoadImage( (CStringA)pathname, -1);

	if( m_imageSource == NULL )
	{
		AfxMessageBox(_T("Cannot open the image file."), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if( m_imageSource->width != 640 || m_imageSource->height != 480 )
	{
		if( AfxMessageBox(_T("Image file resolution is not 640x480. Force the change?"), MB_YESNO | MB_ICONQUESTION) == IDYES )
		{
			IplImage* tmp = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 3);
	        cvResize(m_imageSource,tmp);
			cvReleaseImage( &m_imageSource );
			m_imageSource = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 3);
			cvCopy( tmp, m_imageSource );
			cvReleaseImage( &tmp );
		}
	}

	m_imageAccess = cvCreateImage(cvSize(m_imageSource->width,m_imageSource->height), IPL_DEPTH_8U, 3);

	m_ImageSizeX = m_imageSource->width;
	m_ImageSizeY = m_imageSource->height;

	m_bInitialize = true;

	UpdateImage();

	return true;
}

bool CImageGrabber_File::Free()
{
	if( !m_bInitialize ) return false;

	m_bInitialize = false;

	cvReleaseImage( &m_imageSource );
	cvReleaseImage( &m_imageAccess );

	return true;
}

void CImageGrabber_File::UpdateImage()
{
	if( m_bInitialize )
	{
	//	m_imageSource = cvQueryFrame(m_Capture);

		EnterCriticalSection(&m_critImageGrabber);

		cvCopy( m_imageSource, m_imageAccess );

		LeaveCriticalSection(&m_critImageGrabber);
	}
}

void CImageGrabber_File::DrawToDC(CDC *pDC, int x, int y)
{
	CvvImage m_cImage;
	CRect rect( -x, -y, -x+m_ImageSizeX, -y+m_ImageSizeY );

	EnterCriticalSection(&m_critImageGrabber);
	m_cImage.CopyOf(m_imageAccess);
	LeaveCriticalSection(&m_critImageGrabber);

	m_cImage.DrawToHDC(pDC->m_hDC, rect);
}

COLORREF CImageGrabber_File::GetColor(int x, int y, int camera)
{
	if( !m_bInitialize ) return false;
	
	if( x < 0 || y < 0 || m_ImageSizeX <= x || m_ImageSizeY <= y )
		return RGB(0,0,0);
	
	unsigned char r=0,g=0,b=0;
	
	int p = x*3+m_imageAccess->widthStep*y;
	r = m_imageAccess->imageData[p+2];
	g = m_imageAccess->imageData[p+1];
	b = m_imageAccess->imageData[p  ];
	
	
	return RGB( r,g,b );
}

COLORREF CImageGrabber_File::GetColor( int p, int camera )
{
	if( !m_bInitialize ) return false;
	
	unsigned char r=0,g=0,b=0;
	
	r = m_imageAccess->imageData[p+2];
	g = m_imageAccess->imageData[p+1];
	b = m_imageAccess->imageData[p  ];
	
	return RGB( r,g,b );
}

void CImageGrabber_File::GetColor(unsigned char &r, unsigned char &g, unsigned char &b, int x, int y, int camera)
{
	r = g = b = 0;
	
	if( !m_bInitialize ) return;
	
	if( x < 0 || y < 0 || m_ImageSizeX <= x || m_ImageSizeY <= y )
		return;
	
	int p = x*3+m_imageAccess->widthStep*y;
	r = m_imageAccess->imageDataOrigin[p+2];
	g = m_imageAccess->imageDataOrigin[p+1];
	b = m_imageAccess->imageDataOrigin[p  ];
}

COLORREF CImageGrabber_File::GetColorFloat( double x, double y, int camera )
{
	if( !m_bInitialize ) return false;
//	if( x < 0 || y < 0 || m_ImageSizeX <= x || m_ImageSizeY <= y )
//		return RGB(0,0,0);
//	if( x < 1 || y < 1 || m_ImageSizeX-1 <= x || m_ImageSizeY-1 <= y )
//		return RGB(0,0,0);
	
	int int_x[2];
	int int_y[2];
	
	int_x[0] = (int)x;
	int_x[1] = int_x[0]+1;
	int_y[0] = (int)y;
	int_y[1] = int_y[0]+1;


	// 01
	// 23

	
	double weight_y1 = (y-int_y[0]);
	double weight_y2 = (int_y[1]-y);
	
	double weight_x1 = (x-int_x[0]);
	double weight_x2 = (int_x[1]-x);

	
	//weight_y1 = 0;
	//weight_y2 = 1;
	//weight_x1 = 0;
	//weight_x2 = 1;


	

	int p[4];
	p[0] = int_x[0]*3 + m_imageAccess->widthStep*int_y[0];
	p[1] = int_x[1]*3 + m_imageAccess->widthStep*int_y[0];
	p[2] = int_x[0]*3 + m_imageAccess->widthStep*int_y[1];
	p[3] = int_x[1]*3 + m_imageAccess->widthStep*int_y[1];

//	p[1] = p[0] + 3;
//	p[2] = p[0] + m_ImageSizeX*3;// m_Image->widthStep;
//	p[3] = p[2] + 3;

	double G[4] = {0,0,0,0}, R[4] = {0,0,0,00}, B[4] = {0,0,0,0};
	
	if( int_x[0] > 0 && int_y[0] > 0 && m_ImageSizeX > int_x[0] && m_ImageSizeY > int_y[0] )
	{
		R[0] = (unsigned char)m_imageAccess->imageData[p[0]+2];
		G[0] = (unsigned char)m_imageAccess->imageData[p[0]+1];
		B[0] = (unsigned char)m_imageAccess->imageData[p[0]+0];
	}

	if( int_x[1] > 0 && int_y[0] > 0 && m_ImageSizeX > int_x[1] && m_ImageSizeY > int_y[0] )
	{
		R[1] = (unsigned char)m_imageAccess->imageData[p[1]+2];
		G[1] = (unsigned char)m_imageAccess->imageData[p[1]+1];
		B[1] = (unsigned char)m_imageAccess->imageData[p[1]+0];
	}

	if( int_x[0] > 0 && int_y[1] > 0 && m_ImageSizeX > int_x[0] && m_ImageSizeY > int_y[1] )
	{
		R[2] = (unsigned char)m_imageAccess->imageData[p[2]+2];
		G[2] = (unsigned char)m_imageAccess->imageData[p[2]+1];
		B[2] = (unsigned char)m_imageAccess->imageData[p[2]+0];
	}

	if( int_x[1] > 0 && int_y[1] > 0 && m_ImageSizeX > int_x[1] && m_ImageSizeY > int_y[1] )
	{
		R[3] = (unsigned char)m_imageAccess->imageData[p[3]+2];
		G[3] = (unsigned char)m_imageAccess->imageData[p[3]+1];
		B[3] = (unsigned char)m_imageAccess->imageData[p[3]+0];
	}

	
	double R_left  = weight_y1*R[2] + weight_y2*R[0];
	double G_left  = weight_y1*G[2] + weight_y2*G[0];
	double B_left  = weight_y1*B[2] + weight_y2*B[0];
	
	double R_right = weight_y1*R[3] + weight_y2*R[1];
	double G_right = weight_y1*G[3] + weight_y2*G[1];
	double B_right = weight_y1*B[3] + weight_y2*B[1];
	
	double resultR = weight_x1*R_right + weight_x2*R_left;
	double resultG = weight_x1*G_right + weight_x2*G_left;
	double resultB = weight_x1*B_right + weight_x2*B_left;
	

	/*
	R = std::min( 255.0, R ); 
	R = std::max(   0.0, R ); 
	G = std::min( 255.0, G ); 
	G = std::max(   0.0, G ); 
	B = std::min( 255.0, B ); 
	B = std::max(   0.0, B ); 
	*/
	
	return RGB( resultR, resultG, resultB );
}


/////////////////////////////////////////////////////////////////////////
// Hook
/////////////////////////////////////////////////////////////////////////
bool m_bThreadCore;
//CCriticalSection g_CriticalSection;
UINT threadCoreRIT(LPVOID pParam)
{	
	((CImageGrabber_File*)pParam)->InfiniteLoop();
	
	return 0;
}

#include <mmsystem.h>

void CImageGrabber_File::InfiniteLoop()
{
	double THREAD_LOOP_TIME = (1000.0/30.0);// 30 frame

	DWORD curTime, preTime;
	
	curTime = timeGetTime();
	preTime = curTime;
	
	
	while( m_bThreadCore )
	{
		while( m_bInitialize
			&& curTime < preTime+THREAD_LOOP_TIME )
		{
			curTime = timeGetTime();
			
			if( curTime < 0 ) break;
			
			if( !m_bThreadCore )
				return;
		}
		
		preTime = curTime;

		UpdateImage();	// do nothing

		m_HookFunction(m_HookParameter);
	}
}

void CImageGrabber_File::HookFunction( void (*hFunc)(void* main_class), void* UserPtr )
{
	m_HookFunction = hFunc;
	m_HookParameter = UserPtr;
	
	m_bThreadCore = true;
	m_bThreadSuspend = true;
	m_pThreadCore = AfxBeginThread(threadCoreRIT, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_pThreadCore->m_bAutoDelete = true;
	
	m_pThreadCore->ResumeThread();
	m_bThreadSuspend = false;
}

void CImageGrabber_File::UnhookFunction( void (*hFunc)(void* main_class), void* UserPtr )
{
	m_bThreadCore = false;
	if( m_bThreadSuspend )
		m_pThreadCore->ResumeThread();
	
	//	AfxMessageBox("end thread");
	
	CloseHandle(m_pThreadCore->m_hThread);   
	m_pThreadCore->m_hThread = NULL;  
	
	
	//	DWORD dwRetCode = WaitForSingleObject(m_pThreadCore->m_hThread, INFINITE);
	
	m_HookFunction = NULL;
	m_HookParameter = NULL;
}

void CImageGrabber_File::UnhookFunction()
{
	if( m_bThreadCore )
	{
		UnhookFunction( m_HookFunction, m_HookParameter );
	}
}
