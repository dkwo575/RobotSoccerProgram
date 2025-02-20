#include "StdAfx.h"
#include "ScreenObject.h"


CScreenObject::CScreenObject(void)
{
	m_bScreenDrag = false;
	m_bScreenSelect = false;

	m_bScreenSelect = false;
	m_dragPoint = CPoint(0,0);

	m_pos = CPointDouble(0,0);
	m_acceleration = CPointDouble(0,0);
	m_mass = 0.1;
	m_frictionK = 5.0;
}


CScreenObject::~CScreenObject(void)
{
}

//////////////////////////////////////////////////////////////////////////
// Mouse
//////////////////////////////////////////////////////////////////////////

void CScreenObject::Drag(CPointDouble point)
{
	m_dragPoint = point;
}

void CScreenObject::Drop(CPointDouble point)
{
	m_pos = m_posCurrent = m_posCurrent + point;
	m_dragPoint = CPointDouble(0,0);
	
	Drop();
}

bool CScreenObject::IsClick(CPointDouble p, double margin )
{
	return ( (m_posCurrent - p).Distance() < margin );
}

bool CScreenObject::IsSelect(){ return m_bScreenSelect; }
void CScreenObject::Select(){ m_bScreenSelect = true; }
void CScreenObject::Deselect(){ m_bScreenSelect = false; }

bool CScreenObject::IsGrasp(){ return m_bScreenDrag; }
void CScreenObject::Grasp(){ m_bScreenDrag = true; }
void CScreenObject::Drop(){ m_bScreenDrag = false; }

CPointDouble CScreenObject::DragPoint(){ return m_dragPoint; }


bool CScreenObject::Intersection(CPointDouble P1, CPointDouble P2, CPointDouble Q1, CPointDouble Q2, CPointDouble &Intersection)
{
	P2 = P2 - P1;
	Q2 = Q2 - Q1;
	
	double k = -P2.x*Q2.y + P2.y*Q2.x;
	
	if( k == 0 )
		return false;
	
	
	double t = ( -Q2.y*(-P1.x+Q1.x) + Q2.x*(-P1.y+Q1.y) )/k;
	double s = ( -P2.y*(-P1.x+Q1.x) + P2.x*(-P1.y+Q1.y) )/k;
	
	CPointDouble Test1 = P1 + P2*t;
	CPointDouble Test2 = Q1 + Q2*s;
	
	if( t < 0 || t > 1 || s < 0 || s > 1 )
		return false;
	
	Intersection = P1 + P2 * t;
	
	return true;
}

CPointDouble CScreenObject::InsideGround(CPointDouble A, CPointDouble B, CPointDouble W1, CPointDouble W2 )
{
	CPointDouble Result = B;
	CPointDouble Pwall;
	
	if(    B.x >= W1.x && B.y >= W1.y
		&& B.x <= W2.x && B.y <= W2.y )
		return Result;
	
	
	if( Intersection(
		A,
		B,
		CPointDouble( W1.x, W1.y ),
		CPointDouble( W1.x, W2.y ),
		Pwall ) )
	{
		Result = Pwall;
	}
	
	if( Intersection(
		A,
		B,
		CPointDouble( W2.x, W1.y ),
		CPointDouble( W2.x, W2.y ),
		Pwall ) )
	{
		Result = Pwall;
	}
	
	if( Intersection(
		A,
		B,
		CPointDouble( W1.x, W1.y ),
		CPointDouble( W2.x, W1.y ),
		Pwall ) )
	{
		Result = Pwall;
	}
	
	if( Intersection(
		A,
		B,
		CPointDouble( W1.x, W2.y ),
		CPointDouble( W2.x, W2.y ),
		Pwall ) )
	{
		Result = Pwall;
	}
	
	return Result;
}
