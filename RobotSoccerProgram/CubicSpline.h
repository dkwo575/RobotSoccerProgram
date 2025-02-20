#pragma once

#include"Curve.h"
#include"PointDouble.h"

#define MAX_NP 20

class CCubicSpline
{
public:
	bool GetNthPoint( int n, CPointDouble &p );
	void GetFrontPoints(CPointDouble points[], int &PointCount, int point_n );
	CCubicSpline(CPointDouble pt[], int np);
	void InitSpline(CPointDouble pt[], int np);
	CCubicSpline(double px[] , double py[] , int np);
	
	void MatrixSolveEX(double B[]);
	void GenClosed();
	void GetCurve(CPointDouble points[], int& PointCount);
	int GetCurveCount();
	void Draw(CDC *pDC, double left, double top, double zoom_k);
	void MatrixSolve(double B[]);
	void Generate();
/*
	double* Px;
	double* Py;
	double* Ax;
	double* Ay;
	double* Bx;
	double* By;
	double* Cx;
	double* Cy;
	double*  k;
	double*  Mat[3];
*/
	double Px[MAX_NP];
	double Py[MAX_NP];
	double Ax[MAX_NP];
	double Ay[MAX_NP];
	double Bx[MAX_NP];
	double By[MAX_NP];
	double Cx[MAX_NP];
	double Cy[MAX_NP];
	double  k[MAX_NP];
	double  Mat[3][MAX_NP];

	int  NP;


	CCubicSpline(void);
	~CCubicSpline(void);
};

