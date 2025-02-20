#pragma once
class CPointDouble
{
public:
	CPointDouble Normalize();
	CPointDouble Normalize( double size );
	CPoint Integer();
	double Distance();
	double AngleRadian();
	double AngleDegree();
	CPointDouble operator =(CPoint point);
	BOOL operator ==(CPointDouble point);
	BOOL operator !=(CPointDouble point);
	void operator +=(CPointDouble point);
	void operator -=(CPointDouble point);
	CPointDouble operator +(CPointDouble point);
	CPointDouble operator -(CPointDouble point);
	CPointDouble operator +(CPoint point);
	CPointDouble operator -(CPoint point);

	void operator *=(double k);
	void operator /=(double k);
	CPointDouble operator *(double k);
	CPointDouble operator /(double k);

	double x;
	double y;

	CPointDouble();
	CPointDouble( double x, double y );
	CPointDouble( CPoint p );
	~CPointDouble(void);
};

