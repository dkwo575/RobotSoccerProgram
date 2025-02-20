#include "StdAfx.h"
#include "Curve.h"

#define _USE_MATH_DEFINES
#include<math.h>

CCurve::CCurve(void)
{
}


CCurve::CCurve(double ax,double ay,double bx,double by,double cx,double cy,int ndiv) 
{
	Ax = ax;
	Ay = ay;
	Bx = bx;
	By = by;
	Cx = cx;
	Cy = cy;
	Ndiv = ndiv;
}

CCurve::CCurve(double ax,double ay,double bx,double by,double cx,double cy)
{
	Ax = ax; 
	Ay = ay;
	Bx = bx; 
	By = by;
	Cx = cx; 
	Cy = cy;
	Ndiv = (int)(max(abs((int)Ax),abs((int)Ay))/DIV_FACTOR);
}

CCurve::~CCurve(void)
{
}


void CCurve::PutCurve(double ax,double ay,double bx,double by,double cx,double cy) 
{
	Ax = ax;
	Ay = ay;
	Bx = bx; 
	By = by;
	Cx = cx; 
	Cy = cy;
	Ndiv = (int)(max(abs((int)Ax),abs((int)Ay))/DIV_FACTOR);
}

void CCurve::Draw(CDC *pDC,double x,double y, double left, double top, double zoom_k) 
{
	double OrigX,OrigY,NewX,NewY;
	double  t,f,g,h;
	if (Ndiv==0)
		Ndiv=1;

	OrigX = x; 
	OrigY= y;
	for(int i=1; i<=Ndiv ; i++)
	{
		t = 1.0f / (double)Ndiv * (double)i;
		f = t*t*(3.0f-2.0f*t);
		g = t*(t-1.0f)*(t-1.0f);
		h = t*t*(t-1.0f);
		NewX = (x + Ax*f + Bx*g + Cx*h);
		NewY = (y + Ay*f + By*g + Cy*h);
		pDC->MoveTo( (int)(left+OrigX*zoom_k), (int)(top+OrigY*zoom_k));
		pDC->LineTo( (int)(left+NewX*zoom_k), (int)(top+NewY*zoom_k));

		pDC->Ellipse( (int)(left+OrigX*zoom_k-1),
						(int)(top+OrigY*zoom_k-1),
						(int)(left+OrigX*zoom_k+1),
						(int)(top+OrigY*zoom_k+1) );

		OrigX = NewX;  
		OrigY = NewY;
	}
}
int CCurve::GetCount()
{
	if (Ndiv==0)
		Ndiv=1;
	int PointCount = 1;

	for(int i=1; i<=Ndiv ; i++)
	{
		PointCount++;
	}
	return PointCount;
}
void CCurve::GetCurve(double x,double y, CPointDouble points[], int& PointCount)
{
	double X,Y;
	double  t,f,g,h;
	if (Ndiv==0)
		Ndiv=1;

	X = x; 
	Y= y;
	points[PointCount].x = X;
	points[PointCount].y = Y;
	PointCount++;

	for(int i=1; i<=Ndiv ; i++)
	{
		t = 1.0f / (double)Ndiv * (double)i;
		f = t*t*(3.0f-2.0f*t);
		g = t*(t-1.0f)*(t-1.0f);
		h = t*t*(t-1.0f);
		X = (x + Ax*f + Bx*g + Cx*h);
		Y = (y + Ay*f + By*g + Cy*h);
		points[PointCount].x = X;
		points[PointCount].y = Y;
		PointCount++;
	}
}

void CCurve::GetFrontPoints( double x, double y, CPointDouble points[], int &PointCount, int point_n )
{
	double X,Y;
	double  t,f,g,h;
	if (Ndiv==0)
		Ndiv=1;

	if( PointCount == 0 )
	{
		X = x; 
		Y = y;
		points[PointCount].x = X;
		points[PointCount].y = Y;
		PointCount++;

		if( PointCount >= point_n ) return;
	}

	for(int i=1; i<=Ndiv ; i++)
	{
		t = 1.0f / (double)Ndiv * (double)i;
		f = t*t*(3.0f-2.0f*t);
		g = t*(t-1.0f)*(t-1.0f);
		h = t*t*(t-1.0f);
		X = (x + Ax*f + Bx*g + Cx*h);
		Y = (y + Ay*f + By*g + Cy*h);
		points[PointCount].x = X;
		points[PointCount].y = Y;
		PointCount++;

		if( PointCount >= point_n ) return;
	}
}

bool CCurve::GetNthPoint( double x, double y, int n, CPointDouble &p)
{
	double X,Y;
	double  t,f,g,h;
	if (Ndiv==0)
		Ndiv=1;

	if( n==1 )
	{
		p.x = x; 
		p.y = y;
		return true;
	}

	n--;

//	points[PointCount].x = X;
//	points[PointCount].y = Y;
//	PointCount++;

	for(int i=1; i<Ndiv ; i++)
	{
		t = 1.0f / (double)Ndiv * (double)i;
		f = t*t*(3.0f-2.0f*t);
		g = t*(t-1.0f)*(t-1.0f);
		h = t*t*(t-1.0f);
		X = (x + Ax*f + Bx*g + Cx*h);
		Y = (y + Ay*f + By*g + Cy*h);

		if( n==1 )
		{
			p.x = X; 
			p.y = Y;
			return true;
		}
		n--;
	}

	return false;
}
