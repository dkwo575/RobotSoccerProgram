#include "StdAfx.h"
#include "ImageGrabber_Standard.h"



CImageGrabber_Standard::CImageGrabber_Standard()
{
	m_bInitialize = false;

	m_ImageSizeX = 0;
	m_ImageSizeY = 0;
}

CImageGrabber_Standard::~CImageGrabber_Standard()
{
	Free();
}

/////////////////////////////////////////////////////////////////////////
// Image grabber
/////////////////////////////////////////////////////////////////////////

bool CImageGrabber_Standard::Initialize()
{
	m_bInitialize = true;

	return true;
}

bool CImageGrabber_Standard::Free()
{
	m_bInitialize = false;

	return true;
}

void CImageGrabber_Standard::UpdateImage()
{

}

bool CImageGrabber_Standard::IsReady()
{
	return m_bInitialize;
}

void CImageGrabber_Standard::Suspend()
{
	m_pThreadCore->SuspendThread();
}

void CImageGrabber_Standard::Resume()
{
	m_pThreadCore->ResumeThread();
}

/////////////////////////////////////////////////////////////////////////
// Camera & Framegrabber
/////////////////////////////////////////////////////////////////////////

void CImageGrabber_Standard::DrawToDC(CDC *pDC, int x, int y)
{
}

/////////////////////////////////////////////////////////////////////////
// Color indexing
/////////////////////////////////////////////////////////////////////////

COLORREF CImageGrabber_Standard::GetColor( int x, int y, int camera )
{
	return RGB(0,0,0);
}

COLORREF CImageGrabber_Standard::GetColor( int p, int camera )
{
	return RGB(0,0,0);
}

COLORREF CImageGrabber_Standard::GetColorFloat( double x, double y, int camera )
{
	return RGB(0,0,0);
}

void CImageGrabber_Standard::GetColor( unsigned char &r, unsigned char &g, unsigned char &b, int x, int y, int camera )
{
	r = g = b =0;
}

int CImageGrabber_Standard::Width()
{
	return m_ImageSizeX;
}

int CImageGrabber_Standard::Height()
{
	return m_ImageSizeY;
}

void CImageGrabber_Standard::SetShowPosition( CPoint posShow )
{
	m_posShow = posShow;
}

/////////////////////////////////////////////////////////////////////////
// Hook
/////////////////////////////////////////////////////////////////////////

void CImageGrabber_Standard::InfiniteLoop()
{
}

void CImageGrabber_Standard::HookFunction( void (*hFunc)(void* main_class), void* UserPtr )
{
}

void CImageGrabber_Standard::UnhookFunction( void (*hFunc)(void* main_class), void* UserPtr )
{
}

void CImageGrabber_Standard::UnhookFunction()
{
}