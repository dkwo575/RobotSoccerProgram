#include "StdAfx.h"
#include "RobotDraw.h"

#define _USE_MATH_DEFINES
#include <math.h>

CRobotDraw::CRobotDraw(void)
{
	for( int i=0 ; i<2 ; i++ )
	{
		m_colorPenBodySelect[i] = RGB(0,255,0);
		m_colorPenWheelSelect[i] = RGB(255,92,0);
		
		m_colorPenBody[i][0] = RGB(128,128,128);
		m_colorPenWheel[i][0] = RGB(128,128,128);
		m_colorPenBody[i][1] = RGB(192,192,64);
		m_colorPenWheel[i][1] = RGB(255,92,0);
		m_colorPenBody[i][2] = RGB(255,0,0);
		m_colorPenWheel[i][2] = RGB(128,46,0);
	}

	for( int i=0 ; i<2 ; i++ )
	{
		m_colorPenBodySelect[i] = RGB(0,255,0);
		m_colorPenWheelSelect[i] = RGB(255,92,0);

		m_colorPenBody[i][0] = RGB(128,128,128);
		m_colorPenWheel[i][0] = RGB(128,128,128);
		m_colorPenBody[i][1] = RGB(192,192,64);
		m_colorPenWheel[i][1] = RGB(255,92,0);
		m_colorPenBody[i][2] = RGB(255,0,0);
		m_colorPenWheel[i][2] = RGB(128,46,0);
	}
}


CRobotDraw::~CRobotDraw(void)
{
}


void CRobotDraw::SetColor( int type, int state, COLORREF body, COLORREF wheel )
{
	if( state == 3 )
	{
		m_colorPenBodySelect[type] = body;
		m_colorPenWheelSelect[type] = wheel;
	}
	
	m_colorPenBody[type][state] = body;
	m_colorPenWheel[type][state] = wheel;
}

void CRobotDraw::DrawBodyCurrent(CFrameDC *pDC, CGround *pGround, CRobot *pRobot)
{
	int state = pRobot->State();

	CPointDouble pos = pRobot->PositionCurrent();
	CPointDouble posDC = pos + pRobot->DragPoint();

	double sizeDC = ROBOT_LENGTH/4;
	pGround->GroundToScreen( posDC );
	pGround->GroundToScreen( sizeDC );

	COLORREF colorBody, colorWheel;

	if( pRobot->IsSelect() || pRobot->IsGrasp() )
	{
		colorBody = m_colorPenBodySelect[0];
		colorWheel = m_colorPenWheelSelect[0];
		
		pDC->SelectBrush( colorBody );
	}
	else
	{
		colorBody = m_colorPenBody[0][state];
		colorWheel = m_colorPenWheel[0][state];

		pDC->SelectBrush();
	}


	{	//Fast Draw...
		pDC->SelectPen( colorBody, PS_SOLID, 1 );

		pDC->Circle( (int)posDC.x, (int)posDC.y, (int)sizeDC );

//		Past Position
//		{
//			CPointDouble past = m_posPast + m_dragPoint;
//			CPointDouble c = past * m_ground.GetZoom() + m_ground.TopLeft();
//			pDC->Ellipse( (int)c.x-size, (int)c.y-size, (int)c.x+size, (int)c.y+size );
//		}
	}	
}

void CRobotDraw::DrawBody(CFrameDC *pDC, CGround *pGround, CRobot *pRobot, double robot_size)
{
	if( ROBOT_SOCCER_RROGRAM_ROBOT_TYPE == ROBOT_SOCCER_RROGRAM_ROBOT_TYPE_AndroSot )
		DrawBody_AndroSot( pDC, pGround, pRobot, robot_size * 0.1 );
	else
		DrawBody_MiroSot( pDC, pGround, pRobot, robot_size * ROBOT_LENGTH );
}

void CRobotDraw::DrawBody_MiroSot(CFrameDC *pDC, CGround *pGround, CRobot *pRobot, double robot_size)
{
	int state = pRobot->State();

	CPointDouble pos = pRobot->Position();
	CPointDouble posDC = pos + pRobot->DragPoint();

	double orientation = pRobot->OrientationDegree();

	pGround->GroundToScreen( posDC );


	COLORREF colorBody, colorWheel;

//	if( IsSelect() )
//	{
//		posDisplay = m_pos + m_dragPoint;
//		colorBody = m_colorPenBodySelect;
//		colorWheel = m_colorPenWheelSelect;
//	}
//	else
	{
		colorBody = m_colorPenBody[1][state];
		colorWheel = m_colorPenWheel[1][state];
	}


	//Fast Draw...
//	{
//		CPen pen, *pOldPen;
//		pen.CreatePen( PS_SOLID, 1, colorBody );
//		pOldPen = (CPen*)pDC->SelectObject( &pen );
//
//		int size= (int)(ROBOT_LENGTH/2 * m_ground.GetZoom());
//		CPointDouble c = posDisplay * m_ground.GetZoom() + m_ground.TopLeft();
//		pDC->Ellipse( (int)c.x-size, (int)c.y-size, (int)c.x+size, (int)c.y+size );
//
//		pDC->MoveTo( (int)c.x, (int)c.y );
//
//		CPointDouble head = c + CPointDouble( cos(m_orientation*M_PI/180.0), sin(m_orientation*M_PI/180.0) )*ROBOT_LENGTH/2*m_ground.GetZoom();
//		pDC->LineTo( (int)head.x, (int)head.y );
//
//		pDC->SelectObject( pOldPen );
//		return;
//	}


	CPointDouble p[4];
	p[0].x = cos((orientation+ 45.0)*M_PI/180.0);
	p[0].y = sin((orientation+ 45.0)*M_PI/180.0);
	p[1].x = cos((orientation+135.0)*M_PI/180.0);
	p[1].y = sin((orientation+135.0)*M_PI/180.0);
	p[2].x = cos((orientation+225.0)*M_PI/180.0);
	p[2].y = sin((orientation+225.0)*M_PI/180.0);
	p[3].x = cos((orientation+315.0)*M_PI/180.0);
	p[3].y = sin((orientation+315.0)*M_PI/180.0);

	p[0] = (p[0]*(robot_size*sqrt(2.0)/2.0) + pos);
	p[1] = (p[1]*(robot_size*sqrt(2.0)/2.0) + pos);
	p[2] = (p[2]*(robot_size*sqrt(2.0)/2.0) + pos);
	p[3] = (p[3]*(robot_size*sqrt(2.0)/2.0) + pos);

	pGround->GroundToScreen( p[0] );
	pGround->GroundToScreen( p[1] );
	pGround->GroundToScreen( p[2] );
	pGround->GroundToScreen( p[3] );

	CPointDouble q[4];
	q[0] = (p[1]*0.012+p[0]*(robot_size-0.012))/robot_size;
	q[1] = (p[0]*0.012+p[1]*(robot_size-0.012))/robot_size;
	q[2] = (p[3]*0.012+p[2]*(robot_size-0.012))/robot_size;
	q[3] = (p[2]*0.012+p[3]*(robot_size-0.012))/robot_size;

	CPointDouble r[4];
	r[0] = (q[3]*0.006+q[0]*(robot_size-0.006))/robot_size;
	r[3] = (q[0]*0.006+q[3]*(robot_size-0.006))/robot_size;
	r[1] = (q[2]*0.006+q[1]*(robot_size-0.006))/robot_size;
	r[2] = (q[1]*0.006+q[2]*(robot_size-0.006))/robot_size;
	

	CPointDouble c = posDC;

	CPointDouble head = (p[0]+p[3])/2;

	// Robot Body
	{
		pDC->SelectPen( colorBody, PS_SOLID, 1 );

		pDC->MoveTo( p[0].Integer() );
		pDC->LineTo( q[0].Integer() );
		pDC->MoveTo( p[1].Integer() );
		pDC->LineTo( q[1].Integer() );
		pDC->MoveTo( p[2].Integer() );
		pDC->LineTo( q[2].Integer() );
		pDC->MoveTo( p[3].Integer() );
		pDC->LineTo( q[3].Integer() );

		pDC->MoveTo( q[0].Integer() );
		pDC->LineTo( q[3].Integer() );
		pDC->MoveTo( q[1].Integer() );
		pDC->LineTo( q[2].Integer() );

		pDC->MoveTo( r[0].Integer() );
		pDC->LineTo( r[1].Integer() );
		pDC->MoveTo( r[2].Integer() );
		pDC->LineTo( r[3].Integer() );

//		pDC->MoveTo( r[0].Integer() );
//		pDC->LineTo( c.Integer() );
//		pDC->LineTo( r[3].Integer() );

		CPointDouble front1 = (r[0]+r[3])/2;
		CPointDouble front2 = (p[0]+p[3])/2;
		pDC->MoveTo( front2.Integer() );
		pDC->LineTo( front1.Integer() );
	}

	q[0] = (p[1]*0.015+p[0]*(robot_size-0.015))/robot_size;
	q[1] = (p[0]*0.015+p[1]*(robot_size-0.015))/robot_size;
	q[2] = (p[3]*0.015+p[2]*(robot_size-0.015))/robot_size;
	q[3] = (p[2]*0.015+p[3]*(robot_size-0.015))/robot_size;

	r[0] = (q[3]*0.006+q[0]*(robot_size-0.006))/robot_size;
	r[3] = (q[0]*0.006+q[3]*(robot_size-0.006))/robot_size;
	r[1] = (q[2]*0.006+q[1]*(robot_size-0.006))/robot_size;
	r[2] = (q[1]*0.006+q[2]*(robot_size-0.006))/robot_size;

	// Robot Wheel
	{
		pDC->SelectPen( colorWheel, PS_SOLID, 1 );

		pDC->MoveTo( q[0].Integer() );
		pDC->LineTo( q[1].Integer() );
//		pDC->MoveTo( r[0].Integer() );
//		pDC->LineTo( r[1].Integer() );

		pDC->MoveTo( q[2].Integer() );
		pDC->LineTo( q[3].Integer() );
//		pDC->MoveTo( r[2].Integer() );
//		pDC->LineTo( r[3].Integer() );

//		pDC->MoveTo( q[0].Integer() );
//		pDC->LineTo( r[0].Integer() );
//		pDC->MoveTo( q[1].Integer() );
//		pDC->LineTo( r[1].Integer() );
//
//		pDC->MoveTo( q[2].Integer() );
//		pDC->LineTo( r[2].Integer() );
//		pDC->MoveTo( q[3].Integer() );
//		pDC->LineTo( r[3].Integer() );
//
//		for( double i=0.0 ; i<=1.0 ; i+=0.05 )
//		{
//			pDC->MoveTo( (q[0]*i+r[0]*(1.0-i)).Integer() );
//			pDC->LineTo( (q[1]*i+r[1]*(1.0-i)).Integer() );
//
//			pDC->MoveTo( (q[2]*i+r[2]*(1.0-i)).Integer() );
//			pDC->LineTo( (q[3]*i+r[3]*(1.0-i)).Integer() );
//		}
	}
}

void CRobotDraw::DrawBody_AndroSot(CFrameDC *pDC, CGround *pGround, CRobot *pRobot, double robot_size)
{
	int state = pRobot->State();

	CPointDouble pos = pRobot->Position() + pRobot->DragPoint();
	CPointDouble posDC = pos;

	double orientation = pRobot->OrientationDegree();

	pGround->GroundToScreen( posDC );

	COLORREF colorBody, colorWheel;
	colorBody = m_colorPenBody[1][state];
	colorWheel = m_colorPenWheel[1][state];

	pDC->SelectPen( colorBody, PS_SOLID, 1 );

	// Robot Body
	{
		CPointDouble p[4];
		p[0].x = cos((orientation+ 45.0)*M_PI/180.0);
		p[0].y = sin((orientation+ 45.0)*M_PI/180.0);
		p[1].x = cos((orientation+135.0)*M_PI/180.0);
		p[1].y = sin((orientation+135.0)*M_PI/180.0);
		p[2].x = cos((orientation+225.0)*M_PI/180.0);
		p[2].y = sin((orientation+225.0)*M_PI/180.0);
		p[3].x = cos((orientation+315.0)*M_PI/180.0);
		p[3].y = sin((orientation+315.0)*M_PI/180.0);

		p[0] = (p[0]*(robot_size*sqrt(2.0)/2.0) + pos);
		p[1] = (p[1]*(robot_size*sqrt(2.0)/2.0) + pos);
		p[2] = (p[2]*(robot_size*sqrt(2.0)/2.0) + pos);
		p[3] = (p[3]*(robot_size*sqrt(2.0)/2.0) + pos);

		pGround->GroundToScreen( p[0] );
		pGround->GroundToScreen( p[1] );
		pGround->GroundToScreen( p[2] );
		pGround->GroundToScreen( p[3] );

		CPointDouble front[2];
		{
			double t = 0.01;
			front[0] = ( p[1]*t + p[0]*(robot_size-t) )/robot_size;
			front[1] = ( p[2]*t + p[3]*(robot_size-t) )/robot_size;
		}

		CPointDouble back[2];
		{
			double t = -0.02;
			back[0] = ( p[0]*t + p[1]*(robot_size-t) )/robot_size;
			back[1] = ( p[3]*t + p[2]*(robot_size-t) )/robot_size;
		}


		pDC->MoveTo( front[0].Integer() );
		pDC->LineTo( back[0].Integer() );
		pDC->LineTo( back[1].Integer() );
		pDC->LineTo( front[1].Integer() );
		pDC->LineTo( front[0].Integer() );
	
	}


	// Robot Left Arm
	{
		double should_size = robot_size / 0.1 * 0.07;
		CPointDouble arm_center;
		arm_center.x = pos.x + cos((orientation + 90.0)*M_PI/180.0) * should_size;
		arm_center.y = pos.y + sin((orientation + 90.0)*M_PI/180.0) * should_size;

		CPointDouble p[4];
		p[0].x = cos((orientation+ 30.0)*M_PI/180.0);
		p[0].y = sin((orientation+ 30.0)*M_PI/180.0);
		p[1].x = cos((orientation+150.0)*M_PI/180.0);
		p[1].y = sin((orientation+150.0)*M_PI/180.0);
		p[2].x = cos((orientation+210.0)*M_PI/180.0);
		p[2].y = sin((orientation+210.0)*M_PI/180.0);
		p[3].x = cos((orientation+330.0)*M_PI/180.0);
		p[3].y = sin((orientation+330.0)*M_PI/180.0);

		double arm_size = robot_size / 0.1 * 0.04;
		p[0] = (p[0]*arm_size + arm_center);
		p[1] = (p[1]*arm_size + arm_center);
		p[2] = (p[2]*arm_size + arm_center);
		p[3] = (p[3]*arm_size + arm_center);

		pGround->GroundToScreen( p[0] );
		pGround->GroundToScreen( p[1] );
		pGround->GroundToScreen( p[2] );
		pGround->GroundToScreen( p[3] );

		pDC->MoveTo( p[0].Integer() );
		pDC->LineTo( p[1].Integer() );
		pDC->LineTo( p[2].Integer() );
		pDC->LineTo( p[3].Integer() );
		pDC->LineTo( p[0].Integer() );
	}

	// Robot Right Arm
	{
		double should_size = robot_size / 0.1 * 0.07;
		CPointDouble arm_center;
		arm_center.x = pos.x + cos((orientation - 90.0)*M_PI/180.0) * should_size;
		arm_center.y = pos.y + sin((orientation - 90.0)*M_PI/180.0) * should_size;

		CPointDouble p[4];
		p[0].x = cos((orientation+ 30.0)*M_PI/180.0);
		p[0].y = sin((orientation+ 30.0)*M_PI/180.0);
		p[1].x = cos((orientation+150.0)*M_PI/180.0);
		p[1].y = sin((orientation+150.0)*M_PI/180.0);
		p[2].x = cos((orientation+210.0)*M_PI/180.0);
		p[2].y = sin((orientation+210.0)*M_PI/180.0);
		p[3].x = cos((orientation+330.0)*M_PI/180.0);
		p[3].y = sin((orientation+330.0)*M_PI/180.0);

		double arm_size = robot_size / 0.1 * 0.04;
		p[0] = (p[0]*arm_size + arm_center);
		p[1] = (p[1]*arm_size + arm_center);
		p[2] = (p[2]*arm_size + arm_center);
		p[3] = (p[3]*arm_size + arm_center);

		pGround->GroundToScreen( p[0] );
		pGround->GroundToScreen( p[1] );
		pGround->GroundToScreen( p[2] );
		pGround->GroundToScreen( p[3] );

		pDC->MoveTo( p[0].Integer() );
		pDC->LineTo( p[1].Integer() );
		pDC->LineTo( p[2].Integer() );
		pDC->LineTo( p[3].Integer() );
		pDC->LineTo( p[0].Integer() );
	}

	// Head
	{
		CPointDouble p[4];
		p[0].x = cos((orientation+ 45.0)*M_PI/180.0);
		p[0].y = sin((orientation+ 45.0)*M_PI/180.0);
		p[1].x = cos((orientation+135.0)*M_PI/180.0);
		p[1].y = sin((orientation+135.0)*M_PI/180.0);
		p[2].x = cos((orientation+225.0)*M_PI/180.0);
		p[2].y = sin((orientation+225.0)*M_PI/180.0);
		p[3].x = cos((orientation+315.0)*M_PI/180.0);
		p[3].y = sin((orientation+315.0)*M_PI/180.0);

		double head_size = robot_size / 0.1 * 0.05;
		p[0] = (p[0]*(head_size*sqrt(2.0)/2.0) + pos);
		p[1] = (p[1]*(head_size*sqrt(2.0)/2.0) + pos);
		p[2] = (p[2]*(head_size*sqrt(2.0)/2.0) + pos);
		p[3] = (p[3]*(head_size*sqrt(2.0)/2.0) + pos);

		pGround->GroundToScreen( p[0] );
		pGround->GroundToScreen( p[1] );
		pGround->GroundToScreen( p[2] );
		pGround->GroundToScreen( p[3] );

		double ground_head_size = head_size*sqrt(2.0)/2.0;
		pGround->GroundToScreen( ground_head_size );

		CPointDouble back[2];
		double t = -0.02;
		back[0] = ( p[0]*t + p[1]*(robot_size-t) )/robot_size;
		back[1] = ( p[3]*t + p[2]*(robot_size-t) )/robot_size;

		//pDC->MoveTo( p[0].Integer() );
		//pDC->LineTo( back[0].Integer() );
		//pDC->LineTo( back[1].Integer() );
		//pDC->LineTo( p[3].Integer() );
		//pDC->AngleArc( (int)posDC.x, (int)posDC.y, ground_head_size, -45, 90 );
		//pDC->LineTo( p[0].Integer() );

		pDC->Circle( (int)posDC.x, (int)posDC.y, (int)ground_head_size );

	}
}

void CRobotDraw::DrawMission(CFrameDC *pDC, CGround *pGround, CRobot *pRobot)
{
	CMission mission = pRobot->GetRecentMission();

	CPointDouble posRobot_screen = pRobot->Position();
	pGround->GroundToScreen( posRobot_screen );

	if( mission.type == MissionType::Goalkeeper_Escape
	 || mission.type == MissionType::Goalkeeper_Clear
	 || mission.type == MissionType::Goalkeeper_Basic
	 || mission.type == MissionType::Defense_Wall_Clear
	 || mission.type == MissionType::Defense_Wall
	 || mission.type == MissionType::WaitAndKick
	 || mission.type == MissionType::MoveTo
	 || mission.type == MissionType::MoveToKick
	 )
	{
		pDC->SelectBrush( false );

		CPointDouble posDestination = mission.posDestination;
		pGround->GroundToScreen( posDestination );

		int size = (int)(ROBOT_LENGTH/4 * pGround->ScreenRatio());
		pDC->SelectPen( RGB(0,255,255), PS_SOLID, 1 );
		pDC->Square( (int)posDestination.x, (int)posDestination.y, size );
		
		pDC->SelectPen( RGB(0,128,128), PS_DOT, 1 );
		pDC->MoveTo( posRobot_screen.Integer() );
		pDC->LineTo( posDestination.Integer() );
	}

	if( mission.type == MissionType::Goalkeeper_Escape )
	{
		pDC->SelectPen( RGB(0,128,128), PS_SOLID, 1 );
		pDC->SelectBrush( false );

		CPointDouble areaLeftTop(     - 0.10, pGround->Height()/2+pGround->Goalsize()/2 );
		CPointDouble areaRightBottom( mission.behavior.options.goalkeep.x_pos, pGround->Height()/2-pGround->Goalsize()/2 );
		
		pGround->GroundToScreen( areaLeftTop );
		pGround->GroundToScreen( areaRightBottom );

		pDC->Rectangle( areaLeftTop.Integer().x, areaLeftTop.Integer().y, areaRightBottom.Integer().x, areaRightBottom.Integer().y );			
	}

	if( mission.type == MissionType::Goalkeeper_Clear )
	{
		pDC->SelectPen( RGB(0,128,128), PS_SOLID, 1 );
		pDC->SelectBrush( false );


		CPointDouble areaLeftTop(                                                  0, pGround->Height()/2 + mission.behavior.options.goalkeep.clear_y_size );
		CPointDouble areaRightBottom( mission.behavior.options.goalkeep.clear_x_size, pGround->Height()/2 - mission.behavior.options.goalkeep.clear_y_size );
		
		pGround->GroundToScreen( areaLeftTop );
		pGround->GroundToScreen( areaRightBottom );

		pDC->Rectangle( areaLeftTop.Integer().x, areaLeftTop.Integer().y, areaRightBottom.Integer().x, areaRightBottom.Integer().y );			
	}

	if( mission.type == MissionType::Goalkeeper_Basic )
	{
		pDC->SelectPen( RGB(0,128,128), PS_SOLID, 1 );
		pDC->SelectBrush( false );

		CPointDouble A( mission.behavior.options.goalkeep.x_pos, pGround->Height()/2+mission.behavior.options.goalkeep.y_size );
		CPointDouble B( mission.behavior.options.goalkeep.x_pos, pGround->Height()/2-mission.behavior.options.goalkeep.y_size );

		pGround->GroundToScreen( A );
		pGround->GroundToScreen( B );

		pDC->MoveTo( A.Integer() );
		pDC->LineTo( B.Integer() );
	}

	if( mission.type == MissionType::Goalkeeper_Trace )
	{
		pDC->SelectPen( RGB(128,128,0), PS_SOLID, 1 );
		pDC->SelectBrush( false );

		CPointDouble A( mission.behavior.options.goalkeep.x_pos, pGround->Height()/2+mission.behavior.options.goalkeep.y_size );
		CPointDouble B( mission.behavior.options.goalkeep.x_pos, pGround->Height()/2-mission.behavior.options.goalkeep.y_size );

		pGround->GroundToScreen( A );
		pGround->GroundToScreen( B );

		pDC->MoveTo( A.Integer() );
		pDC->LineTo( B.Integer() );
	}

	if( mission.type == MissionType::Defense_Wall_Clear )
	{
		pDC->SelectPen( RGB(0,128,128), PS_SOLID, 1 );
		pDC->SelectBrush( false );

		CPointDouble A         = mission.behavior.options.defense_wall.posA;
		CPointDouble B         = mission.behavior.options.defense_wall.posB;
		double x_clear_size    = mission.behavior.options.defense_wall.clear_x_size;

		CPointDouble A2;
		CPointDouble B2; 
		A2.x = A.x + cos( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
		A2.y = A.y + sin( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
		B2.x = B.x + cos( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;
		B2.y = B.y + sin( (A-B).AngleRadian() - M_PI/2 ) * x_clear_size;

		pGround->GroundToScreen( A  );
		pGround->GroundToScreen( B  );
		pGround->GroundToScreen( A2 );
		pGround->GroundToScreen( B2 );

		pDC->MoveTo( A.Integer() );
		pDC->LineTo( A2.Integer() );
		pDC->LineTo( B2.Integer() );
		pDC->LineTo( B.Integer() );
		pDC->LineTo( A.Integer() );
	}

	if( mission.type == MissionType::Defense_Wall )
	{
		pDC->SelectPen( RGB(0,128,128), PS_SOLID, 1 );
		pDC->SelectBrush( false );

		CPointDouble A         = mission.behavior.options.defense_wall.posA;
		CPointDouble B         = mission.behavior.options.defense_wall.posB;

		pGround->GroundToScreen( A  );
		pGround->GroundToScreen( B  );

		pDC->MoveTo( A.Integer() );
		pDC->LineTo( B.Integer() );
	}

	if( mission.type == MissionType::Defense_Wall_Trace )
	{
		pDC->SelectPen( RGB(128,128,0), PS_SOLID, 1 );
		pDC->SelectBrush( false );

		CPointDouble A         = mission.behavior.options.defense_wall.posA;
		CPointDouble B         = mission.behavior.options.defense_wall.posB;

		pGround->GroundToScreen( A  );
		pGround->GroundToScreen( B  );

		pDC->MoveTo( A.Integer() );
		pDC->LineTo( B.Integer() );
	}

	if( mission.type == MissionType::MoveTo )
	{
	}

	if( mission.type == MissionType::MoveToKick )
	{
		pDC->SelectPen( RGB(128,128,0), PS_SOLID, 1 );
		pDC->SelectBrush( false );

		CPointDouble tmp = mission.tmp;
		pGround->GroundToScreen( tmp );

		int r = (int)(ROBOT_LENGTH/2 * pGround->ScreenRatio());

		pDC->Circle( (int)tmp.x, (int)tmp.y, r );
	}

	if( mission.type == MissionType::OrientationTo )
	{
		double orientation = mission.orientationDestination;
		CPointDouble posArrow;
		posArrow.x = pRobot->Position().x + cos( orientation * M_PI / 180.0 ) * 0.10;
		posArrow.y = pRobot->Position().y + sin( orientation * M_PI / 180.0 ) * 0.10;

		DrawArrow( pDC, pGround, pRobot->Position(), posArrow, orientation, 0.02, 20, RGB(0,255,255) );
	}

	if( mission.type == MissionType::Wait )
	{
		
	}

	if( mission.type == MissionType::ManualVelocity )
	{
	}

	if( mission.type == MissionType::WaitAndKick )
	{
		pDC->SelectPen( RGB(0,128,128), PS_SOLID, 1 );
		pDC->SelectBrush( false );

		CPointDouble A         = mission.behavior.options.kick_B.posA;
		CPointDouble B         = mission.behavior.options.kick_B.posB;

		pGround->GroundToScreen( A  );
		pGround->GroundToScreen( B  );

		pDC->MoveTo( A.Integer() );
		pDC->LineTo( B.Integer() );



		pDC->SelectPen( RGB(0,255,0), PS_SOLID, 1 );
		pDC->SelectBrush( false );

		CPointDouble tmp = mission.tmp;
		pGround->GroundToScreen( tmp );

		int r = (int)(ROBOT_LENGTH/5 * pGround->ScreenRatio());

		pDC->Circle( (int)tmp.x, (int)tmp.y, r );
	}
}

CPointDouble CRobotDraw::MakeVector(CGround *pGround, CRobot *pRobot, CPointDouble vector_pos )
{
			CPointDouble Ball = pRobot->m_ball.Position();
			CPointDouble Goal( pGround->Width(), pGround->Height()/2.0 );
			CPointDouble R = vector_pos;//pRobot->Position();

			double r = 0.10;///
			if( (R-Ball).Distance()/2 < r )
				r = (R-Ball).Distance()/2;

	
			double prepare_pos_distance = r;
			CPointDouble B2 = (Ball-Goal).Normalize() * prepare_pos_distance + Ball;


					double direction = 1;

					double test_angle = (vector_pos-Ball).AngleDegree() - (Goal-Ball).AngleDegree();

					while( test_angle >  180.0 ) test_angle -= 360.0;
					while( test_angle < -180.0 ) test_angle += 360.0;

					if( test_angle > 0 )
						direction = -1;

					CPointDouble C;
		
					C.x = cos( (Goal-B2).AngleRadian() - M_PI/2*direction );
					C.y = sin( (Goal-B2).AngleRadian() - M_PI/2*direction );

					C = C * (r+0.0) + B2;

					CPointDouble displayC = C;

					pGround->GroundToScreen( displayC );
					double display_r = r;
					pGround->GroundToScreen( display_r );


					double d = (R-C).Distance();

					double target_angle_radian = (R-C).AngleRadian() - atan2( sqrt(d*d-r*r), r ) * direction;
		

					CPointDouble Target;
					Target.x = C.x + r * cos( target_angle_radian );
					Target.y = C.y + r * sin( target_angle_radian );

					CPointDouble p = vector_pos - C;

					double theta = p.AngleRadian();
					double Kr = 0.01;
					double vector_angle;
					if( p.Distance() > r )
					{
						vector_angle = theta - direction * M_PI/2 * (2 - (r+Kr)/(p.Distance()+Kr) ); 
					}
					else
					{
						vector_angle = theta - direction * M_PI/2 * sqrt( p.Distance() / r );
					}

			
					CPointDouble vector;
					vector.x = cos( vector_angle );
					vector.y = sin( vector_angle );

	return vector;
}

void CRobotDraw::DrawInfoToGround(CFrameDC *pDC, CGround *pGround, CRobot *pRobot, CString strInfo)
{
	int state = pRobot->State();

	CPointDouble pos = pRobot->PositionCurrent();
	CPointDouble posDC = pos + pRobot->DragPoint();

	double orientation = pRobot->OrientationDegree();

	pGround->GroundToScreen( posDC );

	CRect text_rect(0, 0, 500, 50);
	text_rect += posDC.Integer();
	text_rect += CPoint(0, (int)(0.05*pGround->ScreenRatio()) );
	
	pDC->SetBkMode( OPAQUE );
	//pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( RGB( 255,255,255 ) );
	
	CString tmp;
	if( strInfo == _T("") )
		tmp.Format(_T("[%d] %s\n    %s\n%s"), pRobot->ID(), pRobot->Name(), pRobot->Role(), pRobot->m_strMsg );
	else
		tmp = strInfo;
	
	//	pDC->FillSolidRect( text_rect, RGB(64,0,0));
	pDC->DrawText( tmp, text_rect, DT_LEFT);
}

void CRobotDraw::DrawArrow(CFrameDC *pDC, CGround *pGround, CPointDouble posBegin, CPointDouble posEnd, double orientation, double size_length, double size_angle, COLORREF color ) 
{
	double arrow_size = size_length;
	double arrow_width = size_angle;
	CPointDouble p0 = posEnd;
	CPointDouble p1;
	p1.x = p0.x + cos( (orientation+arrow_width+180) * M_PI / 180 ) * arrow_size;
	p1.y = p0.y + sin( (orientation+arrow_width+180) * M_PI / 180 ) * arrow_size;
	CPointDouble p2;
	p2.x = p0.x + cos( (orientation-arrow_width+180) * M_PI / 180 ) * arrow_size;
	p2.y = p0.y + sin( (orientation-arrow_width+180) * M_PI / 180 ) * arrow_size;


	CPointDouble posBegin_screen = posBegin;
	pGround->GroundToScreen( posBegin_screen );

	CPointDouble posEnd_screen = posEnd;
	pGround->GroundToScreen( posEnd_screen );



	int width  = abs(posEnd_screen.Integer().x - posBegin_screen.Integer().x);
	int height = abs(posEnd_screen.Integer().y - posBegin_screen.Integer().y);

	int x_sign = 1;
	if( posEnd_screen.Integer().x < posBegin_screen.Integer().x )
		x_sign = -1;

	int y_sign = 1;
	if( posEnd_screen.Integer().y < posBegin_screen.Integer().y )
		y_sign = -1;

	for( int i = 0 ; i<=width ; i++)
	{
		for( int j = 0 ; j<=height ; j++ )
		{
			CPointDouble p(i*x_sign,j*y_sign);
			p = p + posBegin_screen;
			pGround->ScreenToGround( p );

			double d = fabs( ccw( posEnd, posBegin, p ) / (posEnd-posBegin).Distance() );
			double d_line = 0.005;
			if( d <= d_line )
			{
				int c_r = (int)( (d_line - d)/d_line * GetRValue(color) );
				int c_g = (int)( (d_line - d)/d_line * GetGValue(color) );
				int c_b = (int)( (d_line - d)/d_line * GetBValue(color) );
				COLORREF dColor;
				dColor = RGB(c_r,c_g,c_b);
				pDC->SetPixel( (int)posBegin_screen.x + i*x_sign, (int)posBegin_screen.y + j*y_sign, dColor );
			}
			else
			{
				//m_pDC->SetPixel( (int)posBegin_screen.x + i*x_sign, (int)posBegin_screen.y + j*y_sign, RGB(255,255,0) );
			}
		}
	}


	int area = 10;
	for( int i=-area ; i<=area ; i++ )
	{
		for( int j=-area ; j<=area ; j++ )
		{
			CPointDouble p(i,j);
			p = p + posEnd_screen;
			pGround->ScreenToGround( p );

			double r01 = ccw( p0, p1, p );
			double r12 = ccw( p1, p2, p );
			double r20 = ccw( p2, p0, p );

			if( r01 <= 0 && r12 <= 0 && r20 <= 0 )
			{
				pDC->SetPixel( (int)posEnd_screen.x + i, (int)posEnd_screen.y + j, color );
			}
			else
			{
				//m_pDC->SetPixel( posTest.x + i, posTest.y + j, RGB(0,255,0) );				
			}

			double d = 0.003;
			if( r01 >  0 && r12 <= 0 && r20 <= 0 && r01/(p0-p1).Distance() < d)
			{
				int c_r = (int)( (d - r01/(p0-p1).Distance())/d * GetRValue(color) );
				int c_g = (int)( (d - r01/(p0-p1).Distance())/d * GetGValue(color) );
				int c_b = (int)( (d - r01/(p0-p1).Distance())/d * GetBValue(color) );
				COLORREF dColor;
				dColor = RGB(c_r,c_g,c_b);
				pDC->SetPixel( (int)posEnd_screen.x + i, (int)posEnd_screen.y + j, dColor );
			}

			if( r01 <= 0 && r12 >  0 && r20 <= 0 && r12/(p1-p2).Distance() < d)
			{
				int c_r = (int)( (d - r12/(p1-p2).Distance())/d * GetRValue(color) );
				int c_g = (int)( (d - r12/(p1-p2).Distance())/d * GetGValue(color) );
				int c_b = (int)( (d - r12/(p1-p2).Distance())/d * GetBValue(color) );
				COLORREF dColor;
				dColor = RGB(c_r,c_g,c_b);
				pDC->SetPixel( (int)posEnd_screen.x + i, (int)posEnd_screen.y + j, dColor );
			}

			if( r01 <= 0 && r12 <= 0 && r20 >  0 && r20/(p2-p0).Distance() < d)
			{
				int c_r = (int)( (d - r20/(p2-p0).Distance())/d * GetRValue(color) );
				int c_g = (int)( (d - r20/(p2-p0).Distance())/d * GetGValue(color) );
				int c_b = (int)( (d - r20/(p2-p0).Distance())/d * GetBValue(color) );
				COLORREF dColor;
				dColor = RGB(c_r,c_g,c_b);
				pDC->SetPixel( (int)posEnd_screen.x + i, (int)posEnd_screen.y + j, dColor );
			}

		}
	}
}

double CRobotDraw::ccw(CPointDouble p1, CPointDouble p2, CPointDouble p3)
{
	return p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - p1.x*p3.y - p2.x*p1.y  - p3.x*p2.y;
}

void CRobotDraw::DrawPath(CFrameDC *pDC, CGround *pGround, CPathCubicSpline& path)
{
	if( !path.ValidPath() )
		return;

	{
		COLORREF color = RGB(0,255,0);

		CPen pen, *pOldPen;
		pen.CreatePen( PS_SOLID, 1, color );
		pOldPen = (CPen*)pDC->SelectObject( &pen );

		for( int i=0 ; i<path.pointN ; i+=1 )
		{
			if( path.tracePoint > i )
				color = RGB(255,0,0);

			CPointDouble p = path.point[i];
			pGround->GroundToScreen( p );
			pDC->SetPixel( p.Integer(), color );


//				if( i==0 )
//					pDC->MoveTo( p.Integer() );
//				else
//					pDC->LineTo( p.Integer() );

		}

		pDC->SelectObject( pOldPen );
	}


	{
//		for( int i=0 ; i<m_dynamicPath.pointN ; i+=10 )
//		{
//			COLORREF color = RGB(0,255,255);
//			CPointDouble p = m_dynamicPath.point[i] * m_ground.GetZoom() + m_ground.TopLeft();
//			pDC->SetPixel( p.Integer(), color );
//			{
//				CPen pen, *pOldPen;
//				pen.CreatePen( PS_SOLID, 1, color );
//				pOldPen = (CPen*)pDC->SelectObject( &pen );
//
//				CPointDouble p = m_dynamicPath.point[i] * m_ground.GetZoom() + m_ground.TopLeft();
//				CPointDouble d = (m_dynamicPath.point[i]+m_dynamicPath.direction[i]) * m_ground.GetZoom() + m_ground.TopLeft();
//
//				int size=1;
////				pDC->Ellipse( (int)p.x-size, (int)p.y-size, (int)p.x+size, (int)p.y+size );
//
////				pDC->MoveTo( p.Integer() );
////				pDC->LineTo( d.Integer() );
//
//				pDC->SelectObject( pOldPen );
//			}
//		}
	}
}