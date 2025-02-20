#include "StdAfx.h"
#include "Revision.h"



CRevision::CRevision()
	: m_matH(3, 3, CV_64F)
	, m_matinvH(3, 3, CV_64F)
{
}

CRevision::~CRevision()
{

}

void CRevision::SetVisionCenter(int cx, int cy)
{
	m_VisionCenter.x = cx;
	m_VisionCenter.y = cy;
}

void CRevision::SetVisionParam(double k1, double k2)
{
	m_VisionK1 = k1;
	m_VisionK2 = k2;
}

void CRevision::FlatToVision(double &x, double &y)
{
	return;
	double old_x = x - m_VisionCenter.x;
	double old_y = y - m_VisionCenter.y;

	double angle = atan2( old_y, old_x );
	double r_real = sqrt( old_x*old_x + old_y*old_y );

	double CameraHeight = m_VisionK1;
	double zoom = m_VisionK2;

	double theta = atan2( r_real, CameraHeight );	// tan(theta) = D_real/Height
	double r_vision = CameraHeight * theta;			// D_vistion = theta*H
	
	r_vision /= zoom;

	x = r_vision * cos( angle ) + m_VisionCenter.x;
	y = r_vision * sin( angle ) + m_VisionCenter.y;
}

void CRevision::VisionToFlat(double &x, double &y)
{
	return;

	double old_x = x - m_VisionCenter.x;
	double old_y = y - m_VisionCenter.y;

	double angle = atan2( old_y, old_x );
	double r_vision = sqrt( old_x*old_x + old_y*old_y );

	double CameraHeight = m_VisionK1;
	double zoom = m_VisionK2;

	r_vision *= zoom;

	double theta = r_vision/CameraHeight;
	double r_real = tan(theta) * CameraHeight; // D_real = H*tan(theta)

	x = r_real * cos( angle ) + m_VisionCenter.x;
	y = r_real * sin( angle ) + m_VisionCenter.y;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


void CRevision::SetFlatPoints(CPolygonMouse fp )
{
	m_FlatPoints = fp;
}

void CRevision::SetGroundRect( double l, double t, double r, double b )
{
	m_GroundRect.left = l;
	m_GroundRect.right = r;
	m_GroundRect.top = t;
	m_GroundRect.bottom = b;
}

bool CRevision::IsInDCGround(int x, int y)
{
	return ( m_GroundRect.left <= x && x <= m_GroundRect.right
		&& m_GroundRect.top <= y && y <= m_GroundRect.bottom );
}

void CRevision::GenerateRevisionMatrix()
{
	CalcH();
/*
	CPointDouble point[4];
	point[0].x = m_GroundRect.left;		point[0].y = m_GroundRect.top;
	point[1].x = m_GroundRect.right;	point[1].y = m_GroundRect.top;
	point[2].x = m_GroundRect.right;	point[2].y = m_GroundRect.bottom;
	point[3].x = m_GroundRect.left;		point[3].y = m_GroundRect.bottom;

		for( int i=0 ; i<4 ; i++ )
		{
			CMatrix x1, x2;
			x1.Create( 3, 1 );
			x2.Create( 3, 1 );

			x1.Set(0, 0, m_FlatPoints.GetPoint(i).x );
			x1.Set(1, 0, m_FlatPoints.GetPoint(i).y );
			x1.Set(2, 0, 1 );
			x2.Set(0, 0, point[i].x );
			x2.Set(1, 0, point[i].y );
			x2.Set(2, 0, 1 );

			CMatrix q;
			q = m_H * x1;

			double q1x = x2.Get(0,0);
			double q1y = x2.Get(1,0);
			double q2x = q.Get(0,0);
			double q2y = q.Get(1,0);

			double s = q.Get(2,0);
		}
*/
	m_matinvH = m_matH.inv();

/*
	GenerateRevisionMatrix( 0,  m_FlatPoints.GetPoint(1)-m_FlatPoints.GetPoint(0),
								m_FlatPoints.GetPoint(2)-m_FlatPoints.GetPoint(0),
								point[1]-point[0], point[2]-point[0]);

	GenerateRevisionMatrix( 1,  m_FlatPoints.GetPoint(2)-m_FlatPoints.GetPoint(0),
								m_FlatPoints.GetPoint(3)-m_FlatPoints.GetPoint(0),
							 point[2]-point[0], point[3]-point[0]);

*/
	


	// New //////////////////////////////////////////////////////////////////////////

	CPointDouble LeftTop = m_FlatPoints.GetPoint(0); 
	CPointDouble RightTop = m_FlatPoints.GetPoint(1); 
	CPointDouble RightBottom = m_FlatPoints.GetPoint(2); 
	CPointDouble LeftBottom = m_FlatPoints.GetPoint(3);

	CPointDouble Center = GetCrossPoint( LeftTop, RightBottom, RightTop, LeftBottom );
	
	if( m_bTopFocus = IsCrossPointExist( LeftTop, LeftBottom, RightTop, RightBottom ) )
	{
		m_TopFocus = GetCrossPoint( LeftTop, LeftBottom, RightTop, RightBottom );

		double angle_x1 = (Center - m_TopFocus).AngleDegree() - (LeftTop - m_TopFocus).AngleDegree();
		double angle_x2 = (RightTop - m_TopFocus).AngleDegree() - (Center - m_TopFocus).AngleDegree();

		while( angle_x1 > 180 ) angle_x1 -= 360;
		while( angle_x1 <-180 ) angle_x1 += 360;
		while( angle_x2 > 180 ) angle_x2 -= 360;
		while( angle_x2 <-180 ) angle_x2 += 360;

		m_TopAngle1 = (LeftTop - m_TopFocus).AngleDegree(); 
		m_TopAngle = angle_x1 + angle_x2;
		m_kx = fabs(angle_x1) / fabs(m_TopAngle);
	}
	else
	{
		m_kx = (LeftTop-Center).Distance() / (LeftTop-RightBottom).Distance();
	}


	if( m_bLeftFocus = IsCrossPointExist( LeftTop, RightTop, LeftBottom, RightBottom ) )
	{
		m_LeftFocus = GetCrossPoint( LeftTop, RightTop, LeftBottom, RightBottom );

		double angle_y1 = (Center - m_LeftFocus).AngleDegree() - (LeftTop - m_LeftFocus).AngleDegree();
		double angle_y2 = (LeftBottom - m_LeftFocus).AngleDegree() - (Center - m_LeftFocus).AngleDegree();

		while( angle_y1 > 180 ) angle_y1 -= 360;
		while( angle_y1 <-180 ) angle_y1 += 360;
		while( angle_y2 > 180 ) angle_y2 -= 360;
		while( angle_y2 <-180 ) angle_y2 += 360;
		
		m_LeftAngle1 = (LeftTop - m_LeftFocus).AngleDegree(); 
		m_LeftAngle = angle_y1 + angle_y2;
		m_ky = fabs(angle_y1) / fabs(m_LeftAngle);
	}
	else
	{
		m_ky = (LeftTop-Center).Distance() / (LeftTop-RightBottom).Distance();
	}
}

void CRevision::GenerateRevisionMatrix(int i, CPoint p1, CPoint p2, CPointDouble q1, CPointDouble q2)
{
	/*
	q1.x q2.x				p1.x p2.x;
	q1.y q2.y	=	A	*	p1.y p2.y;
	*/

	double i00 =  (double)p2.y/(double)(p1.x*p2.y - p2.x*p1.y);
	double i01 = -(double)p2.x/(double)(p1.x*p2.y - p2.x*p1.y);
	double i10 = -(double)p1.y/(double)(p1.x*p2.y - p2.x*p1.y);
	double i11 =  (double)p1.x/(double)(p1.x*p2.y - p2.x*p1.y);
	/*
	i00 i01
	i10 i11
	*/

	m_revisionMatrix[i][0][0] = (double)q1.x * i00 + (double)q2.x * i10;
	m_revisionMatrix[i][0][1] = (double)q1.x * i01 + (double)q2.x * i11;
	m_revisionMatrix[i][1][0] = (double)q1.y * i00 + (double)q2.y * i10;
	m_revisionMatrix[i][1][1] = (double)q1.y * i01 + (double)q2.y * i11;


	/*
	p1.x p2.x				q1.x q2.x;
	p1.y p2.y	=	B	*	q1.y q2.y;
	*/
	double k = m_revisionMatrix[i][0][0]*m_revisionMatrix[i][1][1] - m_revisionMatrix[i][0][1]*m_revisionMatrix[i][1][0];

	m_revisionInverse[i][0][0] =  m_revisionMatrix[i][1][1]/k;
	m_revisionInverse[i][0][1] = -m_revisionMatrix[i][0][1]/k;
	m_revisionInverse[i][1][0] = -m_revisionMatrix[i][1][0]/k;
	m_revisionInverse[i][1][1] =  m_revisionMatrix[i][0][0]/k;
}

void CRevision::ScreenToFlat2(double &x, double &y)
{
	int mtxID = 0;
	if( ccw(m_GroundRect.TopLeft(), m_GroundRect.BottomRight(), x, y ) > 0 )
	{
		// 0 2 3
		mtxID = 1;
	}
//	else
//	{
//		// 0 1 2
//		mtxID = 0;
//	}

	CPoint p0 = m_FlatPoints.GetPoint(0);


	double x2 = (	m_revisionInverse[mtxID][0][0] * (x-m_GroundRect.left)
				  + m_revisionInverse[mtxID][0][1] * (y-m_GroundRect.top) ) + p0.x;

	double y2 = (	m_revisionInverse[mtxID][1][0] * (x-m_GroundRect.left)
				  + m_revisionInverse[mtxID][1][1] * (y-m_GroundRect.top) ) + p0.y;

	x = x2;
	y = y2;
}

bool CRevision::IsCrossPointExist( CPointDouble A1, CPointDouble A2, CPointDouble B1, CPointDouble B2 )
{
	CPointDouble P1 = A1;
	CPointDouble P2 = (A2-A1);
	CPointDouble Q1 = B1;
	CPointDouble Q2 = (B2-B1);

	if( P2.Normalize() - Q2.Normalize() == CPointDouble(0,0)
		|| P2.Normalize() + Q2.Normalize() == CPointDouble(0,0) )
	{
		// Parallel
		return false;
	}

	return true;
}

CPointDouble CRevision::GetCrossPoint( CPointDouble A1, CPointDouble A2, CPointDouble B1, CPointDouble B2 )
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

void CRevision::ScreenToFlat(double &x, double &y)
{
	cv::Mat q(3, 1, CV_64F);

	q.at<double>(0,0)  = x;
	q.at<double>(1,0)  = y;
	q.at<double>(2,0)  = 1;

	cv::Mat p(3, 1, CV_64F);

	p = m_matinvH * q;

	x = p.at<double>(0,0) / p.at<double>(2,0);
	y = p.at<double>(1,0) / p.at<double>(2,0);
}

void CRevision::FlatToScreen2(double &x, double &y)
{
	int mtxID = 0;
	if( ccw(m_FlatPoints.GetPoint(0), m_FlatPoints.GetPoint(2), x, y ) > 0 )
	{
		// 0 2 3
		mtxID = 1;
	}
//	else
//	{
//		// 0 1 2
//		mtxID = 0;
//	}

	CPoint p0 = m_FlatPoints.GetPoint(0);


	double x2 = (	m_revisionMatrix[mtxID][0][0] * (x-m_FlatPoints.GetPoint(0).x)
				  + m_revisionMatrix[mtxID][0][1] * (y-m_FlatPoints.GetPoint(0).y) ) + m_GroundRect.left;

	double y2 = (	m_revisionMatrix[mtxID][1][0] * (x-m_FlatPoints.GetPoint(0).x)
				  + m_revisionMatrix[mtxID][1][1] * (y-m_FlatPoints.GetPoint(0).y) ) + m_GroundRect.top;

	x = x2;
	y = y2;
}

void CRevision::FlatToScreen(double &x, double &y)
{
	cv::Mat p(3, 1, CV_64F);

	p.at<double>(0,0)  = x;
	p.at<double>(1,0)  = y;
	p.at<double>(2,0)  = 1;

	cv::Mat q(3, 1, CV_64F);

	q = m_matH * p;

	x = q.at<double>(0,0) / q.at<double>(2,0);
	y = q.at<double>(1,0) / q.at<double>(2,0);
}

double CRevision::ccw(CPointDouble p1, CPointDouble p2, double x, double y)
{
	//	p1.x p2.x x
	//	p1.y p2.y y

	return p1.x*p2.y + p2.x*y + x*p1.y - p1.x*y - p2.x*p1.y  - x*p2.y;
}

double CRevision::ccw(CPoint p1, CPoint p2, double x, double y)
{
	//	p1.x p2.x x
	//	p1.y p2.y y

	return p1.x*p2.y + p2.x*y + x*p1.y - p1.x*y - p2.x*p1.y  - x*p2.y;
}

void CRevision::SetImageSize(int height, int width)
{
	m_ImageWidth = width;
	m_ImageHeight = height;
}

void CRevision::OpenFile(CArchive &ar)
{
	m_FlatPoints.OpenFile( ar );

	ar >> m_GroundRect.left;
	ar >> m_GroundRect.right;
	ar >> m_GroundRect.top;
	ar >> m_GroundRect.bottom;

	ar >> m_ImageHeight;
	ar >> m_ImageWidth;

	ar >> m_revisionInverse[0][0][0];
	ar >> m_revisionInverse[0][0][1];
	ar >> m_revisionInverse[0][1][0];
	ar >> m_revisionInverse[0][1][1];
	ar >> m_revisionInverse[1][0][0];
	ar >> m_revisionInverse[1][0][1];
	ar >> m_revisionInverse[1][1][0];
	ar >> m_revisionInverse[1][1][1];

	ar >> m_revisionMatrix[0][0][0];
	ar >> m_revisionMatrix[0][0][1];
	ar >> m_revisionMatrix[0][1][0];
	ar >> m_revisionMatrix[0][1][1];
	ar >> m_revisionMatrix[1][0][0];
	ar >> m_revisionMatrix[1][0][1];
	ar >> m_revisionMatrix[1][1][0];
	ar >> m_revisionMatrix[1][1][1];

	ar >> m_VisionCenter;
	ar >> m_VisionK1;
	ar >> m_VisionK2;
}

void CRevision::SaveFile(CArchive &ar)
{
	m_FlatPoints.SaveFile( ar );

	ar << m_GroundRect.left;
	ar << m_GroundRect.right;
	ar << m_GroundRect.top;
	ar << m_GroundRect.bottom;

	ar << m_ImageHeight;
	ar << m_ImageWidth;

	ar << m_revisionInverse[0][0][0];
	ar << m_revisionInverse[0][0][1];
	ar << m_revisionInverse[0][1][0];
	ar << m_revisionInverse[0][1][1];
	ar << m_revisionInverse[1][0][0];
	ar << m_revisionInverse[1][0][1];
	ar << m_revisionInverse[1][1][0];
	ar << m_revisionInverse[1][1][1];

	ar << m_revisionMatrix[0][0][0];
	ar << m_revisionMatrix[0][0][1];
	ar << m_revisionMatrix[0][1][0];
	ar << m_revisionMatrix[0][1][1];
	ar << m_revisionMatrix[1][0][0];
	ar << m_revisionMatrix[1][0][1];
	ar << m_revisionMatrix[1][1][0];
	ar << m_revisionMatrix[1][1][1];

	ar << m_VisionCenter;
	ar << m_VisionK1;
	ar << m_VisionK2;
}

void CRevision::CalcH()
{
	cv::Mat PointA(4, 3, CV_64F);
	cv::Mat PointB(4, 3, CV_64F);

	CPointDouble point[4];
	point[0].x = m_GroundRect.left;		point[0].y = m_GroundRect.top;
	point[1].x = m_GroundRect.right;	point[1].y = m_GroundRect.top;
	point[2].x = m_GroundRect.right;	point[2].y = m_GroundRect.bottom;
	point[3].x = m_GroundRect.left;		point[3].y = m_GroundRect.bottom;

	for( int i=0 ; i<4 ; i++ )
	{
		PointA.at<double>(i,0) = m_FlatPoints.GetPoint(i).x;
		PointA.at<double>(i,1) = m_FlatPoints.GetPoint(i).y;
		PointA.at<double>(i,2) = 1;

		PointB.at<double>(i,0) = point[i].x;
		PointB.at<double>(i,1) = point[i].y;
		PointB.at<double>(i,2) = 1;
	}
	
	cv::Mat A(8, 9, CV_64F);

	for( int i=0 ; i<4 ; i++ )
	{
		{
			// 0 0 0 a b c d e f
			cv::Mat c012(1, 3, CV_64F);
			cv::Mat c345(1, 3, CV_64F);
			cv::Mat c678(1, 3, CV_64F);

			c012.at<double>(0,0) = 0;
			c012.at<double>(0,1) = 0;
			c012.at<double>(0,2) = 0;
			c345 = -1 * PointB.at<double>(i,2) * PointA.row(i);
			c678 =      PointB.at<double>(i,1) * PointA.row(i);

			for( int c=0 ; c<3 ; c++ )
			{
				A.at<double>(i*2,c  ) = c012.at<double>(0,c);
				A.at<double>(i*2,c+3) = c345.at<double>(0,c);
				A.at<double>(i*2,c+6) = c678.at<double>(0,c);
			}
		}
		{
			// a b c 0 0 0 d e f
			cv::Mat c012(1, 3, CV_64F);
			cv::Mat c345(1, 3, CV_64F);
			cv::Mat c678(1, 3, CV_64F);

			c012 = PointB.at<double>(i,2) * PointA.row(i);

			c345.at<double>(0,0) = 0;
			c345.at<double>(0,1) = 0;
			c345.at<double>(0,2) = 0;

			c678 = -1 * PointB.at<double>(i,0) * PointA.row(i);

			for( int c=0 ; c<3 ; c++ )
			{
				A.at<double>(i*2+1,c  ) = c012.at<double>(0,c);
				A.at<double>(i*2+1,c+3) = c345.at<double>(0,c);
				A.at<double>(i*2+1,c+6) = c678.at<double>(0,c);
			}
		}
	}


	{
		cv::Mat U(8, 8, CV_64F);
		cv::Mat W(8, 9, CV_64F);
		cv::Mat V(9, 9, CV_64F);

		cv::SVD svd(A, cv::SVD::FULL_UV);

		for( int i=0 ; i<9 ; i++ )
		{
			m_matH.at<double>(i/3,i%3) = svd.vt.at<double>(8,i);
		}
	}
}
