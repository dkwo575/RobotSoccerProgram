#pragma once
#include "visioncore.h"
class CVisionCoreDiagonalPatch :
	public CVisionCore
{
/*
public:

	void SetPatchDirectionOffset( double offset );

	void SetTeamIDDistance( double distance );

	void Draw_IDPatch( CDC *pDC, int id, COLORREF color );
	void Draw_TeamIDDistance( CDC *pDC, COLORREF color );

	void SetIDSelectData(int data[][2]);

	CVisionCoreDiagonalPatch(void);
	~CVisionCoreDiagonalPatch(void);

	void Run();

	int m_IDSelect[5][2];
	

protected:
	double m_valueTeamIDDistance;

	void Run_SearchPatch();
	void Run_FindRobot();
	void Run_FindAssistant();
	void Run_InitFlags();
	*/
protected:
	CPointDouble m_SelectRobotPosition;
	double m_valueTeamIDDistance;

	int m_valueAssistantMin;
	int m_valueAssistantMax;
	int m_valueSegmentThreshold;
	int m_valueSegmentCheckDistance;
	int m_selectSegmentID;

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

	void PatchFilter(patch_Structure& patch);
	void Run_FindRobot();
	void Run_InitFlags();
	void Run_SearchPatch();

public:
	CVisionCoreDiagonalPatch(void);
	~CVisionCoreDiagonalPatch(void);
	void SetPatchDirectionOffset(double offset);
	int m_IDSelect[5][2];

	//void Draw_IDPatch(CDC* pDC, int id, COLORREF color);
	void Draw_TeamIDDistance(CDC* pDC, COLORREF color);

	void SetTeamIDDistance(double distance);
	void SetIDSelectData(int data[][2]);

	int m_SegCombination[MAX_OF_ROBOT_ID][2];
	CPointDouble m_SegmentPosition[2];
	void CopyData(CVisionCoreDiagonalPatch& vision);

	void Display_SegmentImage(CDC* pDC, int width, int height, BOOL bInverse, BOOL bAntiBlack, BOOL bTeamColorOnly, COLORREF segcolor, COLORREF anitcolor, BOOL bMask, COLORREF maskcolor, BOOL bBackgound, COLORREF bgcolor, int select_seg_id = -1);

	void Display_AssistantPart(int ass_id, CDC* pDC, COLORREF color);
	void Display_TeamAssistantDistance(CDC* pDC, COLORREF color);


	CPointDouble GetSelectRobotPosition();
	void SetSelectRobotPosition(CPoint point);

	void Display_RobotImage(CDC* pDC, int width, int height, int robot_i);


	void SetAssistantMinMax(int valueAssistantMin, int valueAssistantMax);
	void SetSegmentThreshold(int valueSegmentThreshold);
	void SetSegmentCheckDistance(int distance);
	void SetTeamAssistantDistance(double distance);

	void Run();
};

