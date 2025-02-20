#include "StdAfx.h"
#include "PointDouble.h"

#define _USE_MATH_DEFINES
#include <math.h>

CPointDouble::CPointDouble()
{
	x = y = 0;
}

CPointDouble::CPointDouble( double _x, double _y )
{
	x = _x;
	y = _y;
}

CPointDouble::CPointDouble( CPoint p )
{
	x = p.x;
	y = p.y;
}

CPointDouble::~CPointDouble()
{

}

CPointDouble CPointDouble::operator =(CPoint point)
{
	x = (double)point.x;
	y = (double)point.y;

	return *(this);
}

BOOL CPointDouble::operator ==(CPointDouble point)
{
	if( x == point.x && y == point.y )
		return TRUE;

	return FALSE;
}

BOOL CPointDouble::operator !=(CPointDouble point)
{
	if( x != point.x || y != point.y )
		return TRUE;

	return FALSE;
}

void CPointDouble::operator +=(CPointDouble point)
{
	x += point.x;
	y += point.y;
}

void CPointDouble::operator -=(CPointDouble point)
{
	x -= point.x;
	y -= point.y;
}

CPointDouble CPointDouble::operator +(CPointDouble point)
{
	return CPointDouble( x+point.x , y+point.y );
}

CPointDouble CPointDouble::operator -(CPointDouble point)
{
	return CPointDouble( x-point.x , y-point.y );
}

CPointDouble CPointDouble::operator +(CPoint point)
{
	return CPointDouble( x+point.x , y+point.y );
}

CPointDouble CPointDouble::operator -(CPoint point)
{
	return CPointDouble( x-point.x , y-point.y );
}


CPoint CPointDouble::Integer()
{
	return CPoint( (int)x, (int)y );
}

double CPointDouble::Distance()
{
	return sqrt( x*x+y*y );
}

double CPointDouble::AngleDegree()
{
	double angle = atan2( y, x ) * 180.0 / M_PI;
	while( angle < -180 ) angle+=360;
	while( angle >  180 ) angle-=360;
	
	return  angle;
}

double CPointDouble::AngleRadian()
{
	double angle = atan2( y, x );
	while( angle < -M_PI )
		angle+=(M_PI*2);
	while( angle >  M_PI )
		angle-=(M_PI*2);
	
	return angle;
}

CPointDouble CPointDouble::operator *(double k)
{
	return CPointDouble( x*k , y*k );
}

CPointDouble CPointDouble::operator /(double k)
{
	return CPointDouble( x/k , y/k );
}

void CPointDouble::operator *=(double k)
{
	x*=k;
	y*=k;
}

void CPointDouble::operator /=(double k)
{
	x/=k;
	y/=k;
}

CPointDouble CPointDouble::Normalize()
{
	double dis = Distance();

	if( dis != 0 )
	{
		x /= dis;
		y /= dis;
	}

	return *this;
}

CPointDouble CPointDouble::Normalize( double size )
{
	double dis = Distance();

	if( dis != 0 )
	{
		x = x*size/dis;
		y = y*size/dis;
	}

	return *this;
}