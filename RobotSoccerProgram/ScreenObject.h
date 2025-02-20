#pragma once

#include"PointDouble.h"

class CScreenObject
{
protected:
	bool m_bScreenSelect;
	bool m_bScreenDrag;

	CPointDouble m_dragPoint;
	CPointDouble m_posCurrent;
	CPointDouble m_enemyposCurrent;

public:
	double m_frictionK;
	double m_mass;
	CPointDouble m_acceleration;
	CPointDouble m_pos;
	CPointDouble m_enemypos;

	// Mouse
	bool IsClick(CPointDouble p, double margin );
	void Drop( CPointDouble point );
	void Drag( CPointDouble point );

	bool IsSelect();
	void Select();
	void Deselect();
	
	bool IsGrasp();
	void Grasp();
	void Drop();

	CPointDouble DragPoint();

	CPointDouble InsideGround(CPointDouble A, CPointDouble B, CPointDouble W1, CPointDouble W2 );
	bool Intersection(CPointDouble P1, CPointDouble P2, CPointDouble Q1, CPointDouble Q2, CPointDouble &Intersection);

	CScreenObject(void);
	~CScreenObject(void);
};

