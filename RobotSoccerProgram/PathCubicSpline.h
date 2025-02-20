#pragma once

#include "CubicSpline.h"	// Added by ClassView
#include "PointDouble.h"
#include<vector>
#define PATH_POINT_MAX 500

class CPathCubicSpline
{
public:
	void MakeSmooth();
	void SafeGroundPath( double width, double height, double safe_dis );
	void FindClosePointErrorAndDirection( CPointDouble pos, CPointDouble& error, CPointDouble& dir );
	void UpdateTracePoint( CPointDouble pos );
	CPointDouble GetTracePointDirection();
	CPointDouble GetTracePointPosition();

	bool ValidPath();
	void PassTracePoint();

	void InfiniteLoop( double Ox, double Oy, double r, double d );
	void PathFollow( std::vector<CPointDouble> &vecPoints );
	void Turn( CPointDouble pos, double angle1, double angle2 );

	void AddPoint( CPointDouble p, CPointDouble dir );
	void Reset();

	CPathCubicSpline(void);
	~CPathCubicSpline(void);

	CPointDouble point[PATH_POINT_MAX];	// Cm
	CPointDouble direction[PATH_POINT_MAX]; // vector
	int pointN;

	int tracePoint;
	bool bLoop;

protected:
	CPointDouble m_traceDirectionInterpolation;
	CPointDouble m_tracePointInterpolation;
	CCubicSpline m_spline;

	bool CheckIntersect( CPointDouble A1, CPointDouble A2, CPointDouble B1, CPointDouble B2 );
	double ccw(CPointDouble p1, CPointDouble p2, CPointDouble p3);
	CPointDouble GetCrossPoint( CPointDouble A1, CPointDouble A2, CPointDouble B1, CPointDouble B2 );
};

