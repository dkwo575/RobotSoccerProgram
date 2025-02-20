#include "StdAfx.h"
#include "TimeGraph.h"


CTimeGraph::CTimeGraph()
{
	InitializeCriticalSection(&m_critGraph);

	m_bInit = false;

	// Font
	m_logFont.lfHeight		= 13;
	m_logFont.lfWidth		= 0;
	m_logFont.lfEscapement	= 0;
	m_logFont.lfOrientation	= 0;
	m_logFont.lfWeight		= FW_NORMAL;
	m_logFont.lfItalic		= FALSE;
	m_logFont.lfUnderline	= FALSE;
	m_logFont.lfStrikeOut	= FALSE;
	m_logFont.lfCharSet		= DEFAULT_CHARSET;
	m_logFont.lfOutPrecision	= OUT_CHARACTER_PRECIS;
	m_logFont.lfClipPrecision	= CLIP_CHARACTER_PRECIS;
	m_logFont.lfQuality		= DEFAULT_QUALITY;
	m_logFont.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
	wcscpy(m_logFont.lfFaceName, _T("Tahoma"));

	m_marginLeft = 50;
	m_marginRight = 100;
	m_marginTop = 10;
	m_marginBottom = 30;
	m_minX = m_minY = m_maxX = m_maxY = 0;
	m_gridSizeX = 5;
	m_gridSizeY = 5;

//	m_colorMargin = RGB(255,255,255);
//	m_colorBackground = RGB(0,0,0);
//	m_colorGrid = RGB(128,128,128);

	m_formatX.Format(_T("%.2lf"));
	m_formatY.Format(_T("%.2lf"));


	m_colorGraph[0] = RGB(255,0,0);
	m_colorGraph[1] = RGB(0,192,0);	 
	m_colorGraph[2] = RGB(0,128,255);
	m_colorGraph[3] = RGB(128,0,0);	 
	m_colorGraph[4] = RGB(0,128,0);	 
	m_colorGraph[5] = RGB(0,128,128); 
	m_colorGraph[6] = RGB(255,0,255); 
	m_colorGraph[7] = RGB(128,0,128); 
	m_colorGraph[8] = RGB(255,255,0);
	m_colorGraph[9] = RGB(128,128,0);
	m_colorGraph[10] = RGB(0,0,255);

	SetMarginColor( GetSysColor(COLOR_BTNFACE) );
	SetGridColor( RGB(64,64,64) );
	SetBackgroundColor( RGB(0,0,0) );

	InitData();
}

CTimeGraph::~CTimeGraph()
{
	if( m_bInit )
	{
		SelectObject( m_pOldFont );
		SelectObject(m_pOldBitmap);
	}

	DeleteCriticalSection(&m_critGraph);
}

bool CTimeGraph::Init(CDC *pDC, CRect rect )
{
	if( m_bInit ) return false;

	m_Rect = rect;
	
	CreateCompatibleDC(pDC);
	m_Bitmap.CreateCompatibleBitmap(pDC, m_Rect.Width(), m_Rect.Height() );
	m_pOldBitmap = (CBitmap*)SelectObject( &m_Bitmap );

	m_newFont.CreateFontIndirect(&m_logFont);
	m_pOldFont = (CFont *)SelectObject(&m_newFont);

	m_bInit = true;

	return true;
}

bool CTimeGraph::Init(CDC *pDC )
{
	if( m_bInit ) return false;

	CreateCompatibleDC(pDC);
	m_Bitmap.CreateCompatibleBitmap(pDC, m_Rect.Width(), m_Rect.Height() );
	m_pOldBitmap = (CBitmap*)SelectObject( &m_Bitmap );

	m_newFont.CreateFontIndirect(&m_logFont);
	m_pOldFont = (CFont *)SelectObject(&m_newFont);

	m_bInit = true;

	return true;
}

void CTimeGraph::BitBlt(CDC *pDC)
{
	pDC->BitBlt(m_Rect.left, m_Rect.top, m_Rect.Width(), m_Rect.Height(), this, 0, 0, SRCCOPY);
}

void CTimeGraph::SetTextFormatXAxis( CString str )
{
	m_formatX = str;
}

void CTimeGraph::SetTextFormatYAxis( CString str )
{
	m_formatY = str;
}

void CTimeGraph::SetRegionX(double x1, double x2)
{
	EnterCriticalSection(&m_critGraph);

	m_minX = x1;
	m_maxX = x2;

	LeaveCriticalSection(&m_critGraph);
}

void CTimeGraph::SetRegionY(double y1, double y2)
{
	m_minY = y1;
	m_maxY = y2;
}

void CTimeGraph::SetMargin( int left, int top, int right, int bottom )
{
	m_marginLeft = left;
	m_marginTop = top;
	m_marginRight = right;
	m_marginBottom = bottom;
}

void CTimeGraph::SetGridSize( double x, double y )
{
	m_gridSizeX = x;	
	m_gridSizeY = y;	
}

void CTimeGraph::SetMarginColor( COLORREF color )
{
	m_colorMargin = color;
}

void CTimeGraph::SetGridColor( COLORREF color )
{
	m_colorGrid = color;
}

void CTimeGraph::SetBackgroundColor( COLORREF color )
{
	m_colorBackground = color;
}

void CTimeGraph::SetGraphColor( int p, COLORREF color )
{
	m_colorGraph[p] = color;
}

void CTimeGraph::SetGraphLabel( int p, CString label )
{
	m_label[p] = label;
}

void CTimeGraph::InitData()
{
	m_minX = -10;
	m_minY = -10;
	m_maxX = 10;
	m_maxY = +10;

	for( int i=0 ; i<GRAPH_DATA_ARRAY_MAX_N ; i++ )
	{
		m_data[i].InitData();
	}
}

void CTimeGraph::AddData(int data_id, double x, double y)
{
	EnterCriticalSection(&m_critGraph);

	m_data[data_id].AddData( x, y );

	LeaveCriticalSection(&m_critGraph);
}

void CTimeGraph::FillSolid(COLORREF color)
{
	FillSolidRect( m_Rect.left, m_Rect.top, m_Rect.Width(), m_Rect.Height(), color );
}

void CTimeGraph::DrawGraph()
{
	EnterCriticalSection(&m_critGraph);

	CString tmp;

	// Draw Margin
	CRect rect = m_Rect-m_Rect.TopLeft();
	FillSolidRect( rect, m_colorMargin );
	
	// Background
	rect.DeflateRect( m_marginLeft, m_marginTop, m_marginRight, m_marginBottom );
	FillSolidRect( rect, m_colorBackground );

	CRect text_rect( rect.right+5, rect.top, (m_Rect.right-m_Rect.left)-5, rect.bottom );

	// Label
	{
		for( int i=0, p=0 ; i<GRAPH_DATA_ARRAY_MAX_N ; i++ )
		{
			if( m_data[i].DataN() > 0 )
			{
				double x, y;
				m_data[i].GetData( m_data[i].DataN()-1, x, y );
				tmp.Format(_T("%7.3lf"), y);
				SetBkMode( TRANSPARENT );
				SetTextColor( m_colorGraph[i] );
				DrawText( m_label[i], text_rect, DT_LEFT);
				DrawText( tmp, text_rect, DT_RIGHT);

				text_rect += CPoint(0,15);
				p++;
			}
		}
	}

	// Draw Grid
	{
		CPen pen, *pOldPen;
		pen.CreatePen( PS_SOLID, 1, m_colorGrid );
		pOldPen = (CPen*)SelectObject( &pen );

		double x1 = rect.left;
		double y1 = rect.top;
		double x2 = rect.right;
		double y2 = rect.bottom;

		GraphToReal( x1, y1, rect );
		GraphToReal( x2, y2, rect );

		double x_begin = (int)(x1/m_gridSizeX +1) * m_gridSizeX; // 실수 계산 특성상 X축만 +1 해야한다.
		double y_begin = (int)(y1/m_gridSizeY) * m_gridSizeY;

		for( double gx=x_begin ; gx<x2 ; gx+= m_gridSizeX )
		{
			double x=gx, y=0;
			RealToGraph( x, y, rect );
			MoveTo( (int)x, rect.bottom );
			LineTo( (int)x, rect.bottom+5 );

			// grid
			MoveTo( (int)x, rect.top );
			LineTo( (int)x, rect.bottom );

			CString tmp;
			tmp.Format(m_formatX, gx );
			SetBkMode( TRANSPARENT );
			SetTextColor( RGB( 0,0,0 ) );
			TextOut( (int)x, rect.bottom+5, tmp );
		}

		for( double gy=y_begin ; gy>y2 ; gy-= m_gridSizeY )
		{
			double x=0, y=gy;
			RealToGraph( x, y, rect );
			MoveTo( rect.left, (int)y );
			LineTo( rect.left-5, (int)y );

			// grid
			MoveTo( rect.left, (int)y );
			LineTo( rect.right, (int)y );

//			CString tmp;
//			tmp.Format(m_formatY, gy );
//			SetBkMode( TRANSPARENT );
//			SetTextColor( RGB( 0,0,0 ) );
//			TextOut( rect.left-20, (int)y, tmp );
		}

		SelectObject( pOldPen );
	}

	// Draw Graph
	for( int i=0 ; i<GRAPH_DATA_ARRAY_MAX_N ; i++ )
	{
		CPen pen, *pOldPen;
		pen.CreatePen( PS_SOLID, 1, m_colorGraph[i] );
		pOldPen = (CPen*)SelectObject( &pen );

		bool bFirst = true;
		for( int j=0 ; j< m_data[i].DataN() ; j++ )
		{
			double x, y;
			m_data[i].GetData( j, x, y );
			RealToGraph( x, y, rect );

			double pre_x=x, pre_y=y;
			if( j==0 )
			{
				pre_x = x;
				pre_y = y;
			}

//			SetPixel( (int)x, (int)y, m_colorGraph[i] );
//			if( j==0 )
//				MoveTo( (int)x, (int)y );
//			else
//				LineTo( (int)x, (int)y );

			if( x < rect.left )
			{
				pre_x = x;
				pre_y = y;
			}
			else
			if( x > rect.right )
			{
				break;
			}
			else
			{
				if( bFirst )
				{
					bFirst = false;
					MoveTo( (int)pre_x, (int)pre_y );
				}

				LineTo( (int)x, (int)y );
			}

		}

		SelectObject( pOldPen );
	}

	{
		{
			CRect rect = m_Rect-m_Rect.TopLeft();
			rect.right = rect.left + m_marginLeft-1;
			FillSolidRect( rect, m_colorMargin );
		}

		// Draw Grid
		{
			CPen pen, *pOldPen;
			pen.CreatePen( PS_SOLID, 1, m_colorGrid );
			pOldPen = (CPen*)SelectObject( &pen );

			double x1 = rect.left;
			double y1 = rect.top;
			double x2 = rect.right;
			double y2 = rect.bottom;

			GraphToReal( x1, y1, rect );
			GraphToReal( x2, y2, rect );

			double x_begin = (int)(x1/m_gridSizeX +1) * m_gridSizeX; // 실수 계산 특성상 X축만 +1 해야한다.
			double y_begin = (int)(y1/m_gridSizeY) * m_gridSizeY;

			for( double gy=y_begin ; gy>y2 ; gy-= m_gridSizeY )
			{
				double x=0, y=gy;
				RealToGraph( x, y, rect );
				MoveTo( rect.left, (int)y );
				LineTo( rect.left-5, (int)y );
	//			MoveTo( rect.left, (int)y );
	//			LineTo( rect.right, (int)y );
				CString tmp;
				tmp.Format(m_formatY, gy );
				SetBkMode( TRANSPARENT );
				SetTextColor( RGB( 0,0,0 ) );
//				TextOut( rect.left-20, (int)y, tmp );

				CRect x_rect( 5, (int)y-8, rect.left-10, (int)y+8 );
				DrawText( tmp, x_rect, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

			}

			SelectObject( pOldPen );
		}
	}

	LeaveCriticalSection(&m_critGraph);
}

void CTimeGraph::RealToGraph(double &x, double &y, CRect rect )
{
	x = (double)(x - m_minX) * rect.Width() / (m_maxX - m_minX);
	y = (double)(y - m_minY) * rect.Height() / (m_maxY - m_minY);

	x = rect.left + x;
	y = rect.bottom - y;
}

void CTimeGraph::GraphToReal(double &x, double &y, CRect rect )
{
	x = x - rect.left;
	y = rect.bottom - y;

	x = x * (m_maxX - m_minX) / rect.Width() + m_minX;
	y = y * (m_maxY - m_minY) / rect.Height() + m_minY;
}


// MyGraphData.cpp: implementation of the CTimeGraphData class.
//
//////////////////////////////////////////////////////////////////////

CTimeGraph::CTimeGraphData::CTimeGraphData()
{
	InitData();
}

CTimeGraph::CTimeGraphData::~CTimeGraphData()
{

}

void CTimeGraph::CTimeGraphData::InitData()
{
	m_dataN = 0;
	m_dataBegin = 0;
}

void CTimeGraph::CTimeGraphData::AddData(double x, double y)
{
	int p = (m_dataBegin + m_dataN)%GRAPH_DATA_MAX_N;

	m_data[p][0] = x;
	m_data[p][1] = y;

	if( m_dataN >= GRAPH_DATA_MAX_N )
	{
		m_dataBegin = (m_dataBegin+1)%GRAPH_DATA_MAX_N;
	}
	else
	{
		m_dataN++;
	}
}

int CTimeGraph::CTimeGraphData::DataN()
{
	return m_dataN;
}

void CTimeGraph::CTimeGraphData::GetData( int n, double &x, double &y)
{
	int p = (m_dataBegin + n)%GRAPH_DATA_MAX_N;

	x = m_data[p][0];
	y = m_data[p][1];
}
