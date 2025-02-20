#include "StdAfx.h"
#include "PathCubicSpline.h"

#define _USE_MATH_DEFINES
#include <math.h>

CPathCubicSpline::CPathCubicSpline(void)
{
	Reset();
}


CPathCubicSpline::~CPathCubicSpline(void)
{
}


void CPathCubicSpline::Reset()
{
	bLoop = false;
	pointN = 0;
	tracePoint = 0;
}

void CPathCubicSpline::AddPoint(CPointDouble p, CPointDouble dir)
{
	if( pointN >= PATH_POINT_MAX ) return;

	point[ pointN ] = p;
	direction[ pointN ] = dir;

	pointN++;
}

//////////////////////////////////////////////////////////////////////////
// Mission
//////////////////////////////////////////////////////////////////////////

void CPathCubicSpline::Turn(CPointDouble pos, double angle1, double angle2)
{
	Reset();
	
	double dangle = angle2-angle1;

	while( dangle>=360 ) dangle-=360;
	while( dangle<0 ) dangle+=360;

	if( dangle > 180 )
		dangle = dangle - 360;

	int n=10;
	dangle /= 10;

	for( int i=1 ; i<=n ; i++ )
	{
		CPointDouble dir;
		dir.x = 0.05*cos((angle1+dangle*i)*M_PI/180.0);
		dir.y = 0.05*sin((angle1+dangle*i)*M_PI/180.0);

		AddPoint( pos, dir );
	}
}

void CPathCubicSpline::PathFollow( std::vector<CPointDouble> &vecPoints )
{
	CPointDouble* p = new CPointDouble[ vecPoints.size() ];
	int n = vecPoints.size();

	int tracePointBackup = tracePoint;
	Reset();
	tracePoint = tracePointBackup;

	for( int i=0 ; i<n ; i++ )
	{
		p[i] = vecPoints[i];
		p[i] *= 100;
	}

	m_spline.InitSpline(p, n);
	m_spline.Generate();

	m_spline.GetFrontPoints( point, pointN, PATH_POINT_MAX );

	for( int j=0 ; j<pointN ; j++ )
		point[j] /= 100;

	if( pointN >= 2 )
	{
		for( int i=0 ; i<pointN-1 ; i++ )
		{
			direction[i] = point[i+1]-point[i];

			double d = (point[i+1]-point[i]).Distance();
		}

		direction[pointN-1] = direction[pointN-2];
	}

	if( tracePoint >= pointN )
		tracePoint = 0;

	delete[] p;
}

void CPathCubicSpline::InfiniteLoop( double Ox, double Oy, double r, double d )
{
	Reset();
	bLoop = true;

	double size=2;
	{
		for( double theta=270 ; theta>90 ; theta -= size )
		{
			double x = r * cos( theta * M_PI / 180.0 ) + Ox-d;
			double y = r * sin( theta * M_PI / 180.0 ) + Oy;

//			if( theta==270 )
//				m_pDC->MoveTo( (int)x, (int)y );
//			else
//				m_pDC->LineTo( (int)x, (int)y );

			AddPoint( CPointDouble(x,y), CPointDouble(0,0) );
		}
	}
	{
		for( double theta=-90 ; theta<90 ; theta += size )
		{
			double x = theta*d/90 + Ox;
			double y = -r * sin( theta * M_PI / 180.0 ) + Oy;

//			m_pDC->LineTo( (int)x, (int)y );

			AddPoint( CPointDouble(x,y), CPointDouble(0,0) );
		}
	}
	{
		for( double theta=-90 ; theta<90 ; theta += size )
		{
			double x = r * cos( theta * M_PI / 180.0 ) + Ox+d;
			double y = r * sin( theta * M_PI / 180.0 ) + Oy;

//			m_pDC->LineTo( (int)x, (int)y );

			AddPoint( CPointDouble(x,y), CPointDouble(0,0) );
		}
	}
	{
		for( double theta=-90 ; theta<90 ; theta += size )
		{
			double x = -theta*d/90 + Ox;
			double y = -r * sin( theta * M_PI / 180.0 ) + Oy;

//			m_pDC->LineTo( (int)x, (int)y );

			AddPoint( CPointDouble(x,y), CPointDouble(0,0) );
		}
	}


	if( pointN >= 2)
	{
		for( int i=0 ; i<pointN-1 ; i++ )
		{
			direction[i] = point[i+1]-point[i];
		}

		direction[pointN-1] =  point[0]-point[pointN-1];
	}
}

//////////////////////////////////////////////////////////////////////////
// Useful Method
//////////////////////////////////////////////////////////////////////////

void CPathCubicSpline::PassTracePoint()
{
	tracePoint++;

	if( tracePoint >= pointN )
	{
		if( bLoop )
			tracePoint = 0;
		else
			Reset();
	}
}

bool CPathCubicSpline::ValidPath()
{
	if( tracePoint >= pointN )
		return false;

	return true;
}

void CPathCubicSpline::UpdateTracePoint( CPointDouble pos )
{
	if( pointN == 0 )
	{
		tracePoint = 0;
		return;
	}

	int UpdateMargin=5;

	if( pointN < UpdateMargin )
		UpdateMargin = pointN/2;

	int i_begin = -UpdateMargin;
	int i_end = +UpdateMargin;
	
	if( !bLoop )
	{
		if( tracePoint - UpdateMargin < 0 )
			i_begin = -tracePoint;

		if( tracePoint + UpdateMargin >= pointN )
			i_end = pointN-tracePoint;
	}

	int close_point = tracePoint;
	for( int i=i_begin ; i<=i_end ; i++ )
	{
		int p = ( tracePoint + i + pointN )%pointN;

		if( (point[p] - pos).Distance() < (point[close_point] - pos).Distance() )
		{
			close_point = p;
		}
	}

	tracePoint = close_point;

	tracePoint = max( tracePoint, 2 );
//
//	if( tracePoint >= pointN-1 )
//	{
//		return;
//	}
//	else
//	{
//		tracePoint++;
//		return;
//	}


	int p0 = (tracePoint-1+pointN)%pointN;
	int p1 = (tracePoint+1+pointN)%pointN;

	if( !bLoop )
	{
		if( tracePoint == 0 )
		{
			m_tracePointInterpolation = point[tracePoint];
			m_traceDirectionInterpolation = direction[tracePoint];
			return;
		}
		if( tracePoint == pointN-1 )
		{
			m_tracePointInterpolation = point[tracePoint];
			m_traceDirectionInterpolation = CPointDouble(0,0);
			return;
		}
	}

	CPointDouble close0, close1;
	CPointDouble dir0, dir1;
	if( (point[p0] - pos).Distance() < (point[p1] - pos).Distance() )
	{
		close0 = point[p0];
		close1 = point[tracePoint];
		dir0 = direction[p0];
		dir1 = direction[tracePoint];
	}
	else
	{
		close0 = point[tracePoint];
		close1 = point[p1];
		dir0 = direction[tracePoint];
		dir1 = direction[p1];
	}

	double dis0 = (pos - close0).x * (close1 - close0).x + (pos - close0).y * (close1 - close0).y / (close1 - close0).Distance();
	double dis1 = (close1 - close0).Distance() - dis0;

	m_tracePointInterpolation = (close1 * dis0 + close0 * dis1) / ( dis0 + dis1 );
	m_traceDirectionInterpolation = (dir1 * dis0 + dir0 * dis1) / ( dis0 + dis1 );
}

CPointDouble CPathCubicSpline::GetTracePointDirection()
{
	return m_traceDirectionInterpolation;
//	return direction[tracePoint];
}

CPointDouble CPathCubicSpline::GetTracePointPosition()
{
	return m_tracePointInterpolation;
//	return point[tracePoint];
}

void CPathCubicSpline::FindClosePointErrorAndDirection(CPointDouble pos, CPointDouble &error, CPointDouble &dir)
{
	int closePoint = 0;
	CPointDouble m_closePointInterpolation;
	CPointDouble m_closeDirectionInterpolation;

	for( int i=0 ; i<pointN ; i++ )
	{
		if( (point[i] - pos).Distance() < (point[closePoint] - pos).Distance() )
		{
			closePoint = i;
		}
	}


	int p0 = (closePoint-1+pointN)%pointN;
	int p1 = (closePoint+1+pointN)%pointN;

	if( !bLoop )
	{
		if( closePoint == 0 )
		{
			m_closePointInterpolation = point[closePoint];
			m_closeDirectionInterpolation = direction[closePoint];
			return;
		}
		if( tracePoint == pointN-1 )
		{
			m_closePointInterpolation = point[closePoint];
			m_closeDirectionInterpolation = CPointDouble(0,0);
			return;
		}
	}

	CPointDouble close0, close1;
	CPointDouble dir0, dir1;
	if( (point[p0] - pos).Distance() < (point[p1] - pos).Distance() )
	{
		close0 = point[p0];
		close1 = point[closePoint];
		dir0 = direction[p0];
		dir1 = direction[closePoint];
	}
	else
	{
		close0 = point[closePoint];
		close1 = point[p1];
		dir0 = direction[closePoint];
		dir1 = direction[p1];
	}

	double dis0 = (pos - close0).x * (close1 - close0).x + (pos - close0).y * (close1 - close0).y / (close1 - close0).Distance();
	double dis1 = (close1 - close0).Distance() - dis0;

	m_closePointInterpolation = (close1 * dis0 + close0 * dis1) / ( dis0 + dis1 );
	m_closeDirectionInterpolation = (dir1 * dis0 + dir0 * dis1) / ( dis0 + dis1 );

	error = m_closePointInterpolation - pos;
	dir = m_closeDirectionInterpolation;
}

void CPathCubicSpline::SafeGroundPath(double width, double height, double safe_dis)
{
	safe_dis += 0.01;
	CPointDouble center(width/2, height/2);

	CPointDouble GroundLine[4];
	GroundLine[0] = CPointDouble( safe_dis, safe_dis );
	GroundLine[1] = CPointDouble( safe_dis, height-safe_dis );
	GroundLine[2] = CPointDouble( width-safe_dis, height-safe_dis );
	GroundLine[3] = CPointDouble( width-safe_dis, safe_dis );

	for( int j=0 ; j<pointN ; j++ )
	{
//		CPointDouble p = point[j] - center;

		if( CheckIntersect( center, point[j], GroundLine[0], GroundLine[1] ) )
		{
			point[j] = GetCrossPoint( center, point[j], GroundLine[0], GroundLine[1] );
		}
		else
		if( CheckIntersect( center, point[j], GroundLine[1], GroundLine[2] ) )
		{
			point[j] = GetCrossPoint( center, point[j], GroundLine[1], GroundLine[2] );
		}
		else
		if( CheckIntersect( center, point[j], GroundLine[2], GroundLine[3] ) )
		{
			point[j] = GetCrossPoint( center, point[j], GroundLine[2], GroundLine[3] );
		}
		else
		if( CheckIntersect( center, point[j], GroundLine[3], GroundLine[0] ) )
		{
			point[j] = GetCrossPoint( center, point[j], GroundLine[3], GroundLine[0] );
		}
//
//
//		if( point[j].x < safe_dis )
//			point[j].x = safe_dis;
//		if( point[j].x > width-safe_dis )
//			point[j].x = width-safe_dis;
//		if( point[j].y < safe_dis )
//			point[j].y = safe_dis;
//		if( point[j].y > height-safe_dis )
//			point[j].y = height-safe_dis;
//
//
//		while( point[j].x + point[j].y < 0.07+safe_dis )
//		{
//			point[j].x += 0.005;
//			point[j].y += 0.005;
//		}
//
//		while( (width-point[j].x) + (height-point[j].y) < 0.07+safe_dis )
//		{
//			point[j].x -= 0.005;
//			point[j].y -= 0.005;
//		}
//
//		while( point[j].x + (height-point[j].y) < 0.07+safe_dis )
//		{
//			point[j].x += 0.005;
//			point[j].y -= 0.005;
//		}
//
//		while( (width-point[j].x) + point[j].y < 0.07+safe_dis )
//		{
//			point[j].x -= 0.005;
//			point[j].y += 0.005;
//		}
	}

	if( pointN >= 2)
	{
		for( int i=0 ; i<pointN-1 ; i++ )
		{
			direction[i] = point[i+1]-point[i];

			double d = (point[i+1]-point[i]).Distance();
		}

		direction[pointN-1] = direction[pointN-2];
	}
}



bool CPathCubicSpline::CheckIntersect( CPointDouble A1, CPointDouble A2, CPointDouble B1, CPointDouble B2 )
{
	if( ccw( A1, A2, B1 ) * ccw( A1, A2, B2 ) <= 0 && ccw( B1, B2, A1 ) * ccw( B1, B2, A2 ) <= 0 )
		return true;
	
	return false;
}

double CPathCubicSpline::ccw(CPointDouble p1, CPointDouble p2, CPointDouble p3)
{
	//	p1.x p2.x p3.x
	//	p1.y p2.y p3.y

	return p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - p1.x*p3.y - p2.x*p1.y  - p3.x*p2.y;
}

CPointDouble CPathCubicSpline::GetCrossPoint( CPointDouble A1, CPointDouble A2, CPointDouble B1, CPointDouble B2 )
{
	CPointDouble P1 = A1;
	CPointDouble P2 = (A2-A1);
	CPointDouble Q1 = B1;
	CPointDouble Q2 = (B2-B1);

	double p;

	//	P1 + P2 * p = Q1 + Q2 * q;
	//	((P1.x-Q1.x) + P2.x * p )/Q2.x = q;

	if( Q2.x == 0 )
	{
		//( P2.x != 0 ) because This is not Parallel Line Processing
		p = (Q1.x-P1.x)/P2.x;
	}
	else
	{
		//	(P1.x-Q1.x)/Q2.x + (P2.x/Q2.x) * p = q;
		//	(P2.y-Q2.y*(P2.x/Q2.x)) * p = Q1.y + Q2.y*(P1.x-Q1.x)/Q2.x - P1.y;
	
		p = (Q1.y + Q2.y*(P1.x-Q1.x)/Q2.x - P1.y)/(P2.y-Q2.y*(P2.x/Q2.x));
	}

	return (P1 + P2 * p);
}

void CPathCubicSpline::MakeSmooth()
{
	for( int j=0 ; j<pointN-2 ; j++ )
	{
		int p1 = j;
		int p2 = j+1;
		int p3 = j+2;

		point[p2] = ((point[p1]+point[p3])/2 + point[p2])/2;
	}

	if( pointN >= 2)
	{
		for( int i=0 ; i<pointN-1 ; i++ )
		{
			direction[i] = point[i+1]-point[i];
		}

		direction[pointN-1] =  point[pointN-2];
	}
}

