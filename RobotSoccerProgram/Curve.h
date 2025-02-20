#pragma once

#define DIV_FACTOR 3 //adjust this factor to adjust the curve smoothness
#include"PointDouble.h"

class CCurve
{
public:
	bool GetNthPoint( double x, double y,  int n, CPointDouble &p );
	void GetFrontPoints( double x, double y, CPointDouble points[], int &PointCount, int point_n );
	double  Ax,Ay;
	double  Bx,By;
	double  Cx,Cy;
	int    Ndiv;

	CCurve(void);
	~CCurve(void);

	CCurve(double ax,double ay,double bx,double by,double cx,double cy,int ndiv);
	CCurve(double ax,double ay,double bx,double by,double cx,double cy);
	void PutCurve(double ax,double ay,double bx,double by,double cx,double cy) ;
	void Draw(CDC *pDC,double x,double y, double left, double top, double zoom_k) ;
	int GetCount();
	void GetCurve(double x,double y, CPointDouble points[], int& PointCount);
};

