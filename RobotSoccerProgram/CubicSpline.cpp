#include "StdAfx.h"
#include "CubicSpline.h"

#include<math.h>

CCubicSpline::CCubicSpline(void)
{
}

void CCubicSpline::InitSpline(CPointDouble pt[], int np)
{
	NP = np;

	int p=0;
	for(int i=0;i<NP ;i++) 
	{
		if( i>0 )
		{
			if( pt[i-1].x == pt[i].x && pt[i-1].y == pt[i].y )
				continue;
		}

		Px[p] = (double)pt[i].x;  
		Py[p] = (double)pt[i].y;
		p++;
	}

	NP = p;
}

CCubicSpline::~CCubicSpline(void)
{
}


CCubicSpline::CCubicSpline(CPointDouble pt[], int np)
{
	NP = np;
/*
	Px = new double[NP];
	Py = new double[NP];
	Ax = new double[NP];
	Ay = new double[NP];
	Bx = new double[NP];
	By = new double[NP];
	Cx = new double[NP];
	Cy = new double[NP];
	k = new double[NP];
	Mat[0] = new double[NP];
	Mat[1] = new double[NP];
	Mat[2] = new double[NP];
*/
	for(int i=0;i<NP ;i++) 
	{
		Px[i] = (double)pt[i].x;  
		Py[i] = (double)pt[i].y;
	}
}

CCubicSpline::CCubicSpline(double px[] , double py[] , int np)
{
	NP = np;
/*
	Px = new double[NP];
	Py = new double[NP];
	Ax = new double[NP];
	Ay = new double[NP];
	Bx = new double[NP];
	By = new double[NP];
	Cx = new double[NP];
	Cy = new double[NP];
	k = new double[NP];
	Mat[0] = new double[NP];
	Mat[1] = new double[NP];
	Mat[2] = new double[NP];
*/
	for(int i=0;i<NP ;i++) 
	{
		Px[i] = px[i];  
		Py[i] = py[i];
	}
}

void CCubicSpline::Generate()
{
	double AMag , AMagOld;
    // vector A
	for(int i= 0 ; i<=NP-2 ; i++ ) 
	{
		Ax[i] = Px[i+1] - Px[i];
		Ay[i] = Py[i+1] - Py[i];
	}
	// k
	AMagOld = (double)sqrt(Ax[0]*Ax[0] + Ay[0]*Ay[0]);
	for(int i=0 ; i<=NP-3 ; i++) 
	{
		AMag = (double)sqrt(Ax[i+1]*Ax[i+1] + Ay[i+1]*Ay[i+1]);
		k[i] = AMagOld / AMag;
		AMagOld = AMag;
	}
	k[NP-2] = 1.0f;

	// Matrix
	for(int i=1; i<=NP-2;i++) 
	{
		Mat[0][i] = 1.0f;
		Mat[1][i] = 2.0f*k[i-1]*(1.0f + k[i-1]);
		Mat[2][i] = k[i-1]*k[i-1]*k[i];
	}
	Mat[1][0] = 2.0f;
	Mat[2][0] = k[0];
	Mat[0][NP-1] = 1.0f;
	Mat[1][NP-1] = 2.0f*k[NP-2];

	// 
	for(int i=1; i<=NP-2;i++) 
	{
		Bx[i] = 3.0f*(Ax[i-1] + k[i-1]*k[i-1]*Ax[i]);
		By[i] = 3.0f*(Ay[i-1] + k[i-1]*k[i-1]*Ay[i]);
	}
	Bx[0] = 3.0f*Ax[0];
	By[0] = 3.0f*Ay[0];
	Bx[NP-1] = 3.0f*Ax[NP-2];
	By[NP-1] = 3.0f*Ay[NP-2];

	//
	MatrixSolve(Bx);
	MatrixSolve(By);

	for(int i=0 ; i<=NP-2 ; i++ ) 
	{
		Cx[i] = k[i]*Bx[i+1];
		Cy[i] = k[i]*By[i+1];
	}
}

void CCubicSpline::MatrixSolve(double B[])
{
	double* Work = new double[NP];
	double* WorkB = new double[NP];
	for(int i=0;i<=NP-1;i++) 
	{
		Work[i] = B[i] / Mat[1][i];
		WorkB[i] = Work[i];
	}

	for(int j=0 ; j<10 ; j++) 
	{ ///  need convergence judge
		Work[0] = (B[0] - Mat[2][0]*WorkB[1])/Mat[1][0];
		for(int i=1; i<NP-1 ; i++ ) 
		{
			Work[i] = (B[i]-Mat[0][i]*WorkB[i-1]-Mat[2][i]*WorkB[i+1])
						/Mat[1][i];
		}
		Work[NP-1] = (B[NP-1] - Mat[0][NP-1]*WorkB[NP-2])/Mat[1][NP-1];

		for(int i=0 ; i<=NP-1 ; i++ ) 
		{
			WorkB[i] = Work[i];
		}
	}
	for(int i=0 ; i<=NP-1 ; i++ ) 
	{
		B[i] = Work[i];
	}
	delete[] Work;
	delete[] WorkB;
}

void CCubicSpline::Draw(CDC *pDC, double left, double top, double zoom_k)
{
	CCurve c;
	for(int i=0; i<NP-1 ; i++) 
	{
		c.PutCurve(Ax[i],Ay[i],Bx[i],By[i],Cx[i],Cy[i]);
		c.Draw(pDC,Px[i],Py[i], left, top, zoom_k);
	}
}

int CCubicSpline::GetCurveCount()
{
	CCurve c;
	int count = 0;
	for(int i=0; i<NP-1 ; i++) 
	{
		c.PutCurve(Ax[i],Ay[i],Bx[i],By[i],Cx[i],Cy[i]);
		count += c.GetCount();
	}
	return count-(NP-2);
}


void CCubicSpline::GetCurve(CPointDouble points[], int &PointCount)
{
	CCurve c;
	for(int i=0; i<NP-1 ; i++) 
	{
		c.PutCurve(Ax[i],Ay[i],Bx[i],By[i],Cx[i],Cy[i]);
		c.GetCurve(Px[i],Py[i], points, PointCount);
	}
}

void CCubicSpline::GetFrontPoints(CPointDouble points[], int &PointCount, int point_n )
{
	PointCount = 0;
	
	CCurve c;
	for(int i=0; i<NP-1 ; i++) 
	{
		c.PutCurve(Ax[i],Ay[i],Bx[i],By[i],Cx[i],Cy[i]);
		c.GetFrontPoints(Px[i],Py[i], points, PointCount, point_n);

		if( PointCount >= point_n ) return;
	}
}

bool CCubicSpline::GetNthPoint(int n, CPointDouble &p)
{
	CCurve c;
	int i=1;

	c.PutCurve(Ax[i],Ay[i],Bx[i],By[i],Cx[i],Cy[i]);
	return c.GetNthPoint(Px[i],Py[i], n, p);

}

void CCubicSpline::GenClosed()
{
	double AMag , AMagOld , AMag0;
    // vector A
	for(int i= 0 ; i<=NP-2 ; i++ ) 
	{
		Ax[i] = Px[i+1] - Px[i];
		Ay[i] = Py[i+1] - Py[i];
	}
	Ax[NP-1] = Px[0] - Px[NP-1];
	Ay[NP-1] = Py[0] - Py[NP-1];

	// k
	AMag0 = AMagOld = (double)sqrt(Ax[0]*Ax[0] + Ay[0]*Ay[0]);
	for(int i=0 ; i<=NP-2 ; i++) 
	{
		AMag = (double)sqrt(Ax[i+1]*Ax[i+1] + Ay[i+1]*Ay[i+1]);
		k[i] = AMagOld / AMag;
		AMagOld = AMag;
	}
	k[NP-1]=AMagOld/AMag0; 

	// Matrix
	for(int i=1; i<=NP-1;i++) 
	{
		Mat[0][i] = 1.0f;
		Mat[1][1] = 2.0f*k[i-1]*(1.0f + k[i-1]);
		Mat[2][i] = k[i-1]*k[i-1]*k[i];
	}
	Mat[0][0] = 1.0f;
	Mat[1][0] = 2.0f*k[NP-1]*(1.0f + k[NP-1]);
	Mat[2][0] = k[NP-1]*k[NP-1]*k[0];

	// 
	for(int i=1; i<=NP-1;i++) 
	{
		Bx[i] = 3.0f*(Ax[i-1] + k[i-1]*k[i-1]*Ax[i]);
		By[i] = 3.0f*(Ay[i-1] + k[i-1]*k[i-1]*Ay[i]);
	}
	Bx[0] = 3.0f*(Ax[NP-1] + k[NP-1]*k[NP-1]*Ax[0]);
	By[0] = 3.0f*(Ay[NP-1] + k[NP-1]*k[NP-1]*Ay[0]);

	//
	MatrixSolveEX(Bx);
	MatrixSolveEX(By);

	for(int i=0 ; i<=NP-2 ; i++ ) 
	{
		Cx[i] = k[i]*Bx[i+1];
		Cy[i] = k[i]*By[i+1];
	}
	Cx[NP-1] = k[NP-1]*Bx[0];
	Cy[NP-1] = k[NP-1]*By[0];
}

void CCubicSpline::MatrixSolveEX(double B[])
{
	double* Work = new double[NP];
	double* WorkB = new double[NP];

	for(int i=0;i<=NP-1;i++) 
	{
		Work[i] = B[i] / Mat[1][i];
		WorkB[i] = Work[i];
	}

	for(int j=0 ; j<10 ; j++) 
	{  // need judge of convergence
		Work[0] = (B[0]-Mat[0][0]*WorkB[NP-1]-Mat[2][0]*WorkB[1])
				/Mat[1][0];
		for(int i=1; i<NP-1 ; i++ ) 
		{
			Work[i] = (B[i]-Mat[0][i]*WorkB[i-1]-Mat[2][i]*WorkB[i+1])
						/Mat[1][i];
		}
		Work[NP-1] = (B[NP-1]-Mat[0][NP-1]*WorkB[NP-2]-Mat[2][NP-1]*WorkB[0])
						/Mat[1][NP-1];

		for(int i=0 ; i<=NP-1 ; i++ ) 
		{
			WorkB[i] = Work[i];
		}
	}

	for(int i=0 ; i<=NP-1 ; i++ ) 
	{
		B[i] = Work[i];
	}
}


