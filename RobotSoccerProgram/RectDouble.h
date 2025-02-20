#pragma once

#include "PointDouble.h"

class CRectDouble
{
public:
	double Width();
	double Height();

	bool Inside( CPointDouble point );
	CRectDouble Intersection( CRectDouble rect );

	CPointDouble TopLeft();
	CPointDouble BottomRight();

	double left;
	double right;
	double top;
	double bottom;

	CRectDouble();
	CRectDouble( CRect rect );
	CRectDouble( double l, double t, double r, double b );
	~CRectDouble(void);
};

