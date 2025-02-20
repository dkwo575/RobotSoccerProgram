#pragma once


#include "Revision.h"
#include "Ground.h"
#include "ObjectPositionInfo.h"

#include "RobotSoccerCommon.h"

#include<vector>

#define CAMERA_WIDTH_MAX  640
#define CAMERA_HEIGHT_MAX 480


class CVisionCore : public CRobotSoccerCommon
{
public:
	virtual void CopyData(CVisionCore& vision);


#define MAX_OF_ROBOT_ID ROBOT_SOCCER_RROGRAM_ROBOT_N

typedef struct {
	std::vector<CPoint> pixels;

	CPointDouble Center;
	
	CPointDouble revisionCenter;
	CPointDouble realCenter;

	bool bFound;
	int related_id;
} patch_Structure;


typedef struct {
	bool bValid;
	int id;
	CPointDouble pixelPos;
	CPointDouble revisionPos;
	CPointDouble realPos;
	double direction;
	double pixeldirection;
} position_Structure;

	struct ExistanceCheck
	{
		int ball;
		int robot[MAX_OF_ROBOT_ID];
	} m_countLost;

public:
	unsigned char* m_pProcessingArea;


	CVisionCore(void);
	~CVisionCore(void);


	virtual void SetPatchDirectionOffset( double offset );
	virtual void UpdateObjectPositionInfo( CObjectPositionInfo &info );
	void Draw_Robot( CDC *pDC, BOOL bAllRobot, BOOL bRobot[]);
	void Draw_BallPatch( CDC *pDC, COLORREF color );
	void Draw_OpponentsPatch(CDC *pDC, COLORREF color);
	void Draw_TeamPatch( CDC *pDC, COLORREF color );
	void Draw_IDPatch(CDC* pDC, int id, COLORREF color);

	void DrawProcessingArea( CDC *pDC, COLORREF color );
	void ProcessingAreaUpdate( int x, int y, bool bCheck, int size );


	void SetScanInterval( int valueScanInterval );
	void SetBallMinMax( int valueBallMin, int valueBallMax );
	void SetTeamMinMax( int valueTeamMin, int valueTeamMax );
	void SetIDMinMax( int valueIDMin, int valueIDMax );
	void SetOppMinMax( int valueOppMin, int valueOppMax );
	void SetRevision(CRevision *pRvs, CRevision *pRvs_ball);
	void SetGround(CGround* pGround);

	void PatchFilter( patch_Structure& patch );

	virtual void Run();




protected:

	CPointDouble m_revisionBallPos;
	CPointDouble m_realBallPos;
	bool m_foundBall;
	std::vector<patch_Structure> m_patchBall;
	std::vector<patch_Structure> m_patchOpponent;
	std::vector<patch_Structure> m_patchAssistant[3];
	std::vector<patch_Structure> m_patchTeam;

	position_Structure m_RobotHome[MAX_OF_ROBOT_ID];
	position_Structure m_RobotOpp[MAX_OF_ROBOT_ID];
	

	int NEXT_Y;
	unsigned char* m_pMarkTable;

	int m_cameraID;

	void Run_FindBall();
	virtual void Run_InitFlags();
	virtual void Run_FindRobot();
	virtual void Run_SearchPatch();

	void Run_FindPatchPosition( std::vector<patch_Structure> & patch );
	void Run_FindPatchPosition( patch_Structure& patch );

	void SearchPatchRecursive( int p, int x, int y, patch_Structure& patch, unsigned char mask, int scan_interval, int valueMax);
	void FindPatch( int p, int x, int y, std::vector<patch_Structure> & patch, unsigned char mask, int valueMin, int valueMax, int scan_interval);
	

	CRect m_rectImage;

	int m_valueScanInterval;
	int m_valueBallMin;
	int m_valueBallMax;
	int m_valueTeamMin;
	int m_valueTeamMax;
	int m_valueIDMin;
	int m_valueIDMax;
	int m_valueOppMin;
	int m_valueOppMax;
	double m_PatchDirectionOffset;

	CRevision* m_pRevision;
	CRevision* m_pRevision_ball;
	CGround* m_pGround;
};

