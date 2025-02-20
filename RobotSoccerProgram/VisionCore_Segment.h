#pragma once
#include "visioncore.h"
class CVisionCore_Segment :
	public CVisionCore
{
protected:
	CPointDouble m_SelectRobotPosition;


	int m_valueAssistantMin;
	int m_valueAssistantMax;
	int m_valueSegmentThreshold;
	int m_valueSegmentCheckDistance;
	double m_valueTeamAssistantDistance;
	
	int m_SegmentCount[MAX_OF_ROBOT_ID][6];

	void Run_FindAssistant();

	void PatchFilter( patch_Structure& patch );
	void Run_FindRobot();
	void Run_InitFlags();
	void Run_SearchPatch();

public:
	int m_SegCombination[MAX_OF_ROBOT_ID][6];
	CPointDouble m_SegmentPosition[6];
	void CopyData(CVisionCore_Segment& vision);

	void Display_SegmentImage(CDC *pDC, int width, int height, BOOL bSegment, COLORREF segcolor, COLORREF anitcolor, BOOL bMask, COLORREF maskcolor, BOOL bBackgound, COLORREF bgcolor, int select_seg_id = -1 );

	void Display_AssistantPart( int ass_id, CDC *pDC, COLORREF color );
	void Display_TeamAssistantDistance(CDC *pDC, COLORREF color);


	CPointDouble GetSelectRobotPosition();
	void SetSelectRobotPosition( CPoint point );

	void Display_RobotImage( CDC *pDC, int width, int height, int robot_i );


	void SetAssistantMinMax( int valueAssistantMin, int valueAssistantMax );
	void SetSegmentThreshold( int valueSegmentThreshold );
	void SetSegmentCheckDistance( int distance );
	void SetTeamAssistantDistance( double distance );

	void Run();
	
	CVisionCore_Segment(void);
	~CVisionCore_Segment(void);
};

