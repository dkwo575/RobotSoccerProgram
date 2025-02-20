#pragma once

#include<afxcmn.h>

#define CPN_DRAW_DUALSLIDER         WM_USER + 1001

class CDualSlider : public CProgressCtrl  
{
    DECLARE_DYNAMIC(CDualSlider)
		
		// Constructors
public:
    CDualSlider();
	
	// Methods
public:
	int GetLeftPos();
	int GetRightPos();

	double GetRangeMin();
	double GetRangeMax();
	
	// Attributes
private:
	bool m_bLeftSliderSelect;
	bool m_bRightSliderSelect;

    BOOL m_bCaptured;
    CPoint m_ptOld;
    LOGBRUSH m_logbrush;
	
    BOOL m_bRightSlider;
    BOOL m_bLeftSlider;
	
	CRect m_rcClient;
	
    CPoint m_ptRightPos;
    CPoint m_ptLeftPos;
    COLORREF m_penColor;
	
	bool m_bDual;
	double m_valueMin;
	double m_valueMax;
	double m_valueLeft;
	double m_valueRight;
	double m_valueTick;
	double m_valueStep;
	
	COLORREF m_colorRegion;
	COLORREF m_colorSelect;
	COLORREF m_colorBar;
	COLORREF m_colorBackground;
	CString m_name;
	
	int m_valueResolution;
	
	// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CRulerSlider)
public:
    virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	CDualSlider& operator =(CDualSlider& s);

	double GetValueRight();
	double GetValueLeft();
	double GetValue();
	void SetValue( double left );
	void SetValue( double left, double right );
	void SetOption( CString name, bool bDual, double min, double max, double step, int resolution );
	void SetColor( COLORREF region, COLORREF bar, COLORREF select, COLORREF background );
    virtual ~CDualSlider();
protected:
	double PointToValue( int point );
	int ValueToPoint( double value );
    void Init(const CRect rect);
    void DrawTicks(CDC* pDC);
	
    // Generated message map functions
    //{{AFX_MSG(CRulerSlider)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

