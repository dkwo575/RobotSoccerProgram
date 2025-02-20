#pragma once

#include <afxwin.h>
#include <atltypes.h>
#include <Windows.h>
#include <Wingdi.h>

class CFrameDC :
	public CDC
{
public:
	CFrameDC(void);
	~CFrameDC(void);

	void Square(int center_x, int center_y, int size, bool bOdd = false );
	void Circle( int center_x, int center_y, int r, bool bOdd = false );
	void DeselectBrush();
	void DeselectPen();
	CPoint GetCenter();
	CRect GetRectSize();
	void SelectPen( bool bColor, COLORREF color = RGB(0,0,0), int fnPenStyle = PS_SOLID, int nWidth = 1 );
	void SelectBrush( bool bColor, COLORREF color = RGB(0,0,0) );
	void SelectPen( COLORREF color = RGB(0,0,0), int fnPenStyle = PS_SOLID, int nWidth = 1 );
	void SelectBrush( COLORREF color = RGB(0,0,0) );

	void Clear( COLORREF color );
	CPoint TopLeft();
	CPoint BottomRight();
	bool IsPointInRect( CPoint p );
	CRect GetRect();
	long Height();
	long Width();
	void UpdateRect( CRect rect );
	CBitmap* GetMyBitmap();
	void BitBlt( CDC* pDC );
	void Copy( CDC* pDC );
	bool Init( CDC *pDC, CRect rect );
	bool Init( CDC *pDC );


protected:
	CPen* m_pPen;
	CPen* m_pOldPen;
	CBrush* m_pBrush;
	CBrush* m_pOldBrush;


	LOGFONT m_logFont;
	CFont m_newFont;
	CFont *m_pOldFont;

	CBitmap m_Bitmap;
	CBitmap* m_pOldBitmap;

	CRect m_Rect;
	
	bool m_bInit;
};

