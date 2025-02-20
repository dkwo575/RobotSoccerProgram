#pragma once

#include"cv.h"
#include"PolygonMouse.h"
#include"RectDouble.h"

class CRevision
{
public:
	void OpenFile(CArchive &ar);
	void SaveFile(CArchive &ar);
	void SetImageSize( int height, int width );
	void FlatToScreen(double &x, double &y);
	void FlatToScreen2(double &x, double &y);
	void VisionToFlat( double &x, double &y );
	bool IsInDCGround( int x, int y );
	void ScreenToFlat( double &x, double &y );
	void ScreenToFlat2( double &x, double &y );
	void GenerateRevisionMatrix();
	void SetGroundRect( double l, double t, double r, double b );
	void SetFlatPoints( CPolygonMouse fp );

	void FlatToVision( double &x, double &y );
	void SetVisionParam( double k1, double k2 );
	void SetVisionCenter( int cx, int cy );
	CRevision(void);
	~CRevision(void);

protected:
	cv::Mat m_matH;
	cv::Mat m_matinvH;

	void CalcH();
	bool m_bTopFocus;
	bool m_bLeftFocus;

	double m_TopAngle1;
	double m_TopAngle;
	double m_LeftAngle1;
	double m_LeftAngle;
	CPointDouble m_TopFocus;
	CPointDouble m_LeftFocus;
	double m_kx;
	double m_ky;
	bool IsCrossPointExist( CPointDouble A1, CPointDouble A2, CPointDouble B1, CPointDouble B2 );
	CPointDouble GetCrossPoint( CPointDouble A1, CPointDouble A2, CPointDouble B1, CPointDouble B2 );
	int m_ImageHeight;
	int m_ImageWidth;

	double ccw(CPointDouble p1, CPointDouble p2, double x, double y);
	double ccw(CPoint p1, CPoint p2, double x, double y);
	void GenerateRevisionMatrix(int i, CPoint p1, CPoint p2, CPointDouble q1, CPointDouble q2);
	double m_revisionMatrix[2][2][2];
	double m_revisionInverse[2][2][2];
	
	CPolygonMouse m_FlatPoints;
	CRectDouble m_GroundRect;

	double m_VisionK1;
	double m_VisionK2;
	CPoint m_VisionCenter;
};

