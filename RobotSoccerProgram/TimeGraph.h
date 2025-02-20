#pragma once

#define GRAPH_DATA_ARRAY_MAX_N 20

class CTimeGraph : public CDC
{
	#define GRAPH_DATA_MAX_N 200

	class CTimeGraphData  
	{
	public:
		void GetData( int n, double &x, double &y );
		int DataN();
		void InitData();
		void AddData( double x, double y );
		CTimeGraphData();
		virtual ~CTimeGraphData();

	protected:
		double m_data[GRAPH_DATA_MAX_N][2];
		int m_dataBegin;
		int m_dataN;
	};


public:
	void SetTextFormatXAxis( CString str );
	void SetTextFormatYAxis( CString str );
	void SetGraphColor( int p, COLORREF color );
	void SetGraphLabel( int p, CString label );

	void SetGridSize( double x, double y );
	void SetMarginColor( COLORREF color );
	void SetGridColor( COLORREF color );
	void SetBackgroundColor( COLORREF color );

	void DrawGraph();
	void FillSolid( COLORREF color );
	void AddData( int data_id, double x, double y );
	void InitData();
	void SetRegionX( double x1, double x2 );
	void SetRegionY( double y1, double y3 );
	void SetMargin( int left, int top, int right, int bottom );

	void BitBlt( CDC* pDC );
	bool Init( CDC *pDC, CRect rect );
	bool Init( CDC *pDC );

	CTimeGraph(void);
	~CTimeGraph(void);

protected:
	CRITICAL_SECTION m_critGraph;

	CString m_formatX;
	CString m_formatY;

	void RealToGraph( double &x, double &y, CRect rect );
	void GraphToReal( double &x, double &y, CRect rect );

	LOGFONT m_logFont;
	CFont m_newFont;
	CFont *m_pOldFont;

	CBitmap m_Bitmap;
	CBitmap* m_pOldBitmap;

	CRect m_Rect;
	CRect m_MarginRect;
	CRect m_GraphRect;

	bool m_bInit;

	int m_marginLeft, m_marginRight, m_marginTop, m_marginBottom;
	double m_minX, m_minY, m_maxX, m_maxY;
	double m_gridSizeX;
	double m_gridSizeY;
	COLORREF m_colorBackground;
	COLORREF m_colorGrid;
	COLORREF m_colorMargin;
	COLORREF m_colorGraph[GRAPH_DATA_ARRAY_MAX_N];

	CTimeGraphData m_data[GRAPH_DATA_ARRAY_MAX_N];
	CString m_label[GRAPH_DATA_ARRAY_MAX_N];
};

