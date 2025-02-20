#include "StdAfx.h"
#include "RectDouble.h"



CRectDouble::CRectDouble()
{

}

CRectDouble::CRectDouble( CRect rect )
{
	left   = rect.left;
	top    = rect.top;
	right  = rect.right;
	bottom = rect.bottom;
}

CRectDouble::CRectDouble( double l, double t, double r, double b )
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

CRectDouble::~CRectDouble()
{

}

double CRectDouble::Width()
{
	return right-left;
}

double CRectDouble::Height()
{
	return bottom-top;
}

CPointDouble CRectDouble::TopLeft()
{
	return CPointDouble( left, top );
}

CPointDouble CRectDouble::BottomRight()
{
	return CPointDouble( right, bottom );
}

bool CRectDouble::Inside( CPointDouble point )
{
	if( left <= point.x && point.x <= right
	 && top  <= point.y && point.y <= bottom )
		return true;

	return false;
}

CRectDouble CRectDouble::Intersection( CRectDouble rect )
{
	CRectDouble rectInter(0,0,0,0);

	CPointDouble p[4];
	p[0].x = left;
	p[0].y = top;
	p[1].x = left;
	p[1].y = bottom;
	p[2].x = right;
	p[2].y = bottom;
	p[3].x = right;
	p[3].y = top;

	CPointDouble q[4];
	q[0].x = rect.left;
	q[0].y = rect.top;
	q[1].x = rect.left;
	q[1].y = rect.bottom;
	q[2].x = rect.right;
	q[2].y = rect.bottom;
	q[3].x = rect.right;
	q[3].y = rect.top;

	if( rect.right <= left )
		return rectInter;

	if( rect.left >= right )
		return rectInter;

	if( rect.bottom <= top )
		return rectInter;

	if( rect.top >= bottom )
		return rectInter;


	int countInside_p = 0;
	for( int pi=0 ; pi<4 ; pi++ )
	{
		if( rect.Inside( p[pi] ) )
		{
			countInside_p++;
		}
	}


	int countInside_q = 0;
	for( int qi=0 ; qi<4 ; qi++ )
	{
		if( Inside( q[qi] ) )
		{
			countInside_q++;
		}
	}

	return rectInter;
}