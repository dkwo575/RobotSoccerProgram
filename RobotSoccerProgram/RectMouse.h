#pragma once

#define SAME_POINT 5

class CRectMouse
{
public:
	void SaveFile(CArchive &ar);
	void OpenFile(CArchive &ar);

	void SetTitle( CString title );
	CString Title();
	CString GetTextInfo();
	CRect GetZeroOffsetRect();
	COLORREF GetColor();
	void SetColor( COLORREF color );
	void MouseMove( CPoint point );
	void MouseLUp( CPoint point );
	void MouseLDown( CPoint point );
	void MouseRUp( CPoint point );
	void MouseRDown( CPoint point );
	CRect GetRect();
	void Init( double l, double t, double r, double b );
	void Init( CRect rect );

	double m_left;
	double m_top;
	double m_right;
	double m_bottom;
	
	CRectMouse(void);
	~CRectMouse(void);

protected:
	COLORREF m_color;
	CString m_title;

	void ReleaseAll();
	void CaptureLeft();
	void CaptureTop();
	void CaptureRight();
	void CaptureBottom();
	bool m_bCapture;

	CPoint m_capturePoint;
	bool m_bCaptureLeft;
	bool m_bCaptureTop;
	bool m_bCaptureRight;
	bool m_bCaptureBottom;

	double m_left_bak;
	double m_top_bak;
	double m_right_bak;
	double m_bottom_bak;
};

