#include "StdAfx.h"
#include "ImageGrabber_USBCam.h"



CImageGrabber_USBCam::CImageGrabber_USBCam()
{
	CImageGrabber_File::CImageGrabber_File();

	m_Capture = NULL;

	m_bFileMode = false;
	m_bSimulationMode = false;
	m_bVideoMode = false;
}

CImageGrabber_USBCam::~CImageGrabber_USBCam()
{
	Free();
}

bool CImageGrabber_USBCam::Initialize()
{
	bool result;
	result = Initialize(0);
	return result;
}

bool CImageGrabber_USBCam::ChangeCamera(const char* filename)
{
	bool result;

	CString strAVI(filename);
	CString strType = strAVI.Right(4);
	strType.MakeUpper();

	if( strType == _T(".AVI") )
	{
		EnterCriticalSection(&m_critImageGrabber);

		Free();

		m_bFileMode = false;
		m_bVideoMode = true;

		m_Capture = cvCreateFileCapture( filename );

		if( !m_Capture )
		{
			//AfxMessageBox(_T("cvCaptureFromCAM Error"), MB_ICONERROR);
			AfxMessageBox(_T("Cannot open the video file."), MB_ICONERROR);
			result = false;
			m_bInitialize = false;
		}
		else
		{
			m_bInitialize = true;

			m_ImageSizeX = 640;
			m_ImageSizeY = 480;

			m_imageAccess = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 3);
		
			UpdateImage();

			result = true;
		}

		LeaveCriticalSection(&m_critImageGrabber);
	}
	else
	{
		EnterCriticalSection(&m_critImageGrabber);

		Free();

		m_bFileMode = true;
		m_bVideoMode = false;

		result = CImageGrabber_File::Initialize( filename );

		LeaveCriticalSection(&m_critImageGrabber);
	}

	return result;
}

bool CImageGrabber_USBCam::ChangeCamera( int id )
{
	bool result = true;
	EnterCriticalSection(&m_critImageGrabber);

	Free();

	m_bFileMode = false;

	m_Capture = cvCaptureFromCAM(id);

	if( !m_Capture )
	{
		//AfxMessageBox(_T("cvCaptureFromCAM Error"), MB_ICONERROR);
		AfxMessageBox(_T("Cannot recognise the camera."), MB_ICONERROR);
		result = false;
		m_bInitialize = false;
	}
	else
	{
		m_bInitialize = true;

		m_ImageSizeX = 640;
		m_ImageSizeY = 480;

		m_imageAccess = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 3);
		
		UpdateImage();
	}
	
	LeaveCriticalSection(&m_critImageGrabber);

	return result;
}


bool CImageGrabber_USBCam::Initialize(const char* filename)
{
	bool result;
	
	CString strAVI(filename);
	CString strType = strAVI.Right(4);
	strType.MakeUpper();

	if( strType == _T(".AVI") )
	{
		// Video
		EnterCriticalSection(&m_critImageGrabber);

		m_bFileMode = false;
		m_bVideoMode = true;

		m_Capture = cvCreateFileCapture( filename );

		if( !m_Capture )
		{
			//AfxMessageBox(_T("cvCaptureFromCAM Error"), MB_ICONERROR);
			AfxMessageBox(_T("Cannot open the video file"), MB_ICONERROR);
			result = false;
			m_bInitialize = false;
		}
		else
		{
			m_bInitialize = true;

			m_ImageSizeX = 640;
			m_ImageSizeY = 480;

			m_imageAccess = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 3);
		
			UpdateImage();

			result = true;
		}

		LeaveCriticalSection(&m_critImageGrabber);
	}
	else
	{
		// Image

		EnterCriticalSection(&m_critImageGrabber);

		m_bFileMode = true;
		m_bVideoMode = false;

		result = CImageGrabber_File::Initialize( filename );

		LeaveCriticalSection(&m_critImageGrabber);
	}
	return result;
}

bool CImageGrabber_USBCam::Initialize( int id )
{
	bool result = true;
	EnterCriticalSection(&m_critImageGrabber);


	m_bFileMode = false;
	m_bVideoMode = false;

	m_Capture = cvCaptureFromCAM(id);

	if( !m_Capture )
	{
		//AfxMessageBox(_T("cvCaptureFromCAM Error"), MB_ICONERROR);
		AfxMessageBox(_T("Cannot recognise the camera."), MB_ICONERROR);
		result = false;
		m_bInitialize = false;
	}
	else
	{
		m_bInitialize = true;

		m_ImageSizeX = 640;
		m_ImageSizeY = 480;

		m_imageAccess = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 3);
		
		UpdateImage();
	}
	
	LeaveCriticalSection(&m_critImageGrabber);

	return result;
}

bool CImageGrabber_USBCam::Free()
{
	if( m_bFileMode )
	{
		return CImageGrabber_File::Free();
	}
	else
	{
		bool result = true;

		if( !m_bInitialize ) return false;

		m_bInitialize = false;

		cvReleaseImage( &m_imageAccess );

		if( m_Capture )
		{
			cvReleaseCapture( &m_Capture );
		}
		else
		{
			result = false;
		}
	
		return result;
	}
}

void CImageGrabber_USBCam::UpdateImage()
{
	if( m_bFileMode )
	{
		CImageGrabber_File::UpdateImage();
	}
	else
	{
		if( m_bInitialize )
		{
			if( m_bVideoMode )
			{
				if( cvGrabFrame( m_Capture ) == 0 )
				{
					cvSetCaptureProperty(m_Capture, CV_CAP_PROP_POS_FRAMES, 0);
					cvGrabFrame( m_Capture );
				}

				m_imageSource = cvRetrieveFrame( m_Capture );

				if( m_imageSource->width != 640 || m_imageSource->height != 480 )
				{
					EnterCriticalSection(&m_critImageGrabber);
					cvResize(m_imageSource,m_imageAccess);
					LeaveCriticalSection(&m_critImageGrabber);
				}				
				else
				{
					EnterCriticalSection(&m_critImageGrabber);
					cvCopy( m_imageSource, m_imageAccess );
					LeaveCriticalSection(&m_critImageGrabber);
				}
			}
			else
			{
			//	m_imageSource = cvQueryFrame(m_Capture);
				cvGrabFrame( m_Capture );
				m_imageSource = cvRetrieveFrame( m_Capture );

				EnterCriticalSection(&m_critImageGrabber);
				cvCopy( m_imageSource, m_imageAccess );

				LeaveCriticalSection(&m_critImageGrabber);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////
// Hook
/////////////////////////////////////////////////////////////////////////
bool m_bThreadCore_USBCam;
//CCriticalSection g_CriticalSection;
UINT threadCore_OpenCV(LPVOID pParam)
{	
	((CImageGrabber_USBCam*)pParam)->InfiniteLoop();
	
	return 0;
}

#include <mmsystem.h>

void CImageGrabber_USBCam::InfiniteLoop()
{
	double THREAD_LOOP_TIME = (1000.0/30.0);// 30 frame
	DWORD curTime, preTime;
	
	curTime = timeGetTime();
	preTime = curTime;
	
	
	while( m_bThreadCore_USBCam )
	{
		if( m_bFileMode || m_bSimulationMode )
		{
			while( m_bInitialize
				&& curTime < preTime+THREAD_LOOP_TIME )
			{
				curTime = timeGetTime();
			
				if( curTime < 0 ) break;
			
				if( !m_bThreadCore_USBCam )
					return;
			}
		
			preTime = curTime;

			//UpdateImage();	// do nothing

			m_HookFunction(m_HookParameter);
		}
		else
		if( m_bVideoMode )
		{
			while( m_bInitialize
				&& curTime < preTime+THREAD_LOOP_TIME )
			{
				curTime = timeGetTime();
			
				if( curTime < 0 ) break;
			
				if( !m_bThreadCore_USBCam )
					return;
			}
		
			preTime = curTime;

			UpdateImage();

			m_HookFunction(m_HookParameter);
		}
		else
		{
			if( !m_bThreadCore_USBCam )
					return;
		
			UpdateImage();

			m_HookFunction(m_HookParameter);
		}
	}
}

void CImageGrabber_USBCam::HookFunction( void (*hFunc)(void* main_class), void* UserPtr )
{
	m_HookFunction = hFunc;
	m_HookParameter = UserPtr;
	
	m_bThreadCore_USBCam = true;
	m_bThreadSuspend = true;
	m_pThreadCore = AfxBeginThread(threadCore_OpenCV, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_pThreadCore->m_bAutoDelete = true;
	
	m_pThreadCore->ResumeThread();
	m_bThreadSuspend = false;
}

void CImageGrabber_USBCam::UnhookFunction( void (*hFunc)(void* main_class), void* UserPtr )
{
	m_bThreadCore_USBCam = false;
	if( m_bThreadSuspend )
		m_pThreadCore->ResumeThread();
	
	//	AfxMessageBox("end thread");
	
	CloseHandle(m_pThreadCore->m_hThread);
	m_pThreadCore->m_hThread = NULL;
	
	
	//	DWORD dwRetCode = WaitForSingleObject(m_pThreadCore->m_hThread, INFINITE);
	
	m_HookFunction = NULL;
	m_HookParameter = NULL;
}

void CImageGrabber_USBCam::UnhookFunction()
{
	if( m_bThreadCore_USBCam )
	{
		UnhookFunction( m_HookFunction, m_HookParameter );
	}
}


void CImageGrabber_USBCam::DrawToDC(CDC *pDC, int x, int y)
{
	CvvImage m_cImage;

	EnterCriticalSection(&m_critImageGrabber);
	m_cImage.CopyOf(m_imageAccess);
	LeaveCriticalSection(&m_critImageGrabber);

	CRect rect( -x, -y, -x+m_ImageSizeX, -y+m_ImageSizeY );
	m_cImage.DrawToHDC(pDC->m_hDC, rect);
}

void CImageGrabber_USBCam::SimulationMode( bool bSimulationMode )
{
	m_bSimulationMode = bSimulationMode;
}