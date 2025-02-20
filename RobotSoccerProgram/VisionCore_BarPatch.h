#pragma once
#include "visioncore.h"

class CVisionCore_BarPatch :
	public CVisionCore
{
protected:
	CPointDouble m_SelectRobotPosition;


	int m_valueAssistantMin;
	int m_valueAssistantMax;
	int m_valueSegmentThreshold;
	int m_valueSegmentCheckDistance;
	double m_valueTeamAssistantDistance;
	
	struct S_Segment_Count
	{
		int count[6];
		bool bInverseOrientation;
		int team_patch_id;
		int robot_id;
		double orientation_rad;
		double orientation_screen;
	};

	std::vector<S_Segment_Count> m_vecSegmentCount;

	void Run_FindAssistant();

	void PatchFilter( patch_Structure& patch );
	void Run_FindRobot();
	void Run_InitFlags();
	void Run_SearchPatch();
	
public:
	int m_SegCombination[MAX_OF_ROBOT_ID][4];
	CPointDouble m_SegmentPosition[4];
	void CopyData(CVisionCore_BarPatch& vision);

	void Display_SegmentImage(CDC *pDC, int width, int height, BOOL bInverse, BOOL bAntiBlack, BOOL bTeamColorOnly, COLORREF segcolor, COLORREF anitcolor, BOOL bMask, COLORREF maskcolor, BOOL bBackgound, COLORREF bgcolor, int select_seg_id = -1 );

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
	
	CVisionCore_BarPatch(void);
	~CVisionCore_BarPatch(void);
};

