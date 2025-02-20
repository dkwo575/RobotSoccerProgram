#pragma once

#define REVISION_SAME_POINT 15

class CPolygonMouse
{
public:
	void SaveFile(CArchive &ar);
	void OpenFile(CArchive &ar);
	CString Title();
	CPoint TitlePos();
	COLORREF ColorLine();
	COLORREF ColorPoint();
	COLORREF ColorText();
//	void SetColorLine( COLORREF color );
//	void SetColorPoint( COLORREF color );
//	void SetColorText( COLORREF color );
	CString GetTextInfo( int id );
	CPoint GetTextPos( int id );
	CPoint GetPoint( int id );
	void SetTitle( CString title );
	void MouseMove( CPoint point );
	void MouseLUp( CPoint point );
	bool MouseLDown( CPoint point );
	void MouseRUp( CPoint point );
	void MouseRDown( CPoint point );
	void Init( int l, int t, int r, int b );

	CPolygonMouse(void);
	~CPolygonMouse(void);

protected:
	long m_width;
	long m_height;
	bool AboutZero( CPoint point );
	COLORREF m_colorLine;
	COLORREF m_colorPoint;
	COLORREF m_colorText;
	CString m_title;

	CPoint m_capturePoint;
	CPoint m_point[5];
	CPoint m_backup[4];
	bool m_bCapture[4];
};

