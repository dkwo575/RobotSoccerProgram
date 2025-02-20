#include "StdAfx.h"
#include "VisionCore.h"

#define _USE_MATH_DEFINES
#include <math.h>


CVisionCore::CVisionCore(void)
{
	//m_pBall = new patches_Structure;
	//m_pOpponent = new patches_Structure;
	//m_pID[0] = new patches_Structure;
	//m_pID[1] = new patches_Structure;
	//m_pID[2] = new patches_Structure;
	//m_pTeam = new patches_Structure;

	m_pMarkTable = new unsigned char[CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX];
	m_pProcessingArea = new unsigned char[CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX];
	ZeroMemory( m_pProcessingArea, sizeof(unsigned char)*CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX );

	Run_InitFlags();

	m_pRevision = NULL;
	m_pImageGrabber = NULL;

	m_cameraID = 0;	// 본 프로그램은 1대의 카메라를 사용하므로 기본값(0)을 사용

	m_PatchDirectionOffset = 0;

	m_countLost.ball = 0;
	for( int id=0 ; id<MAX_OF_ROBOT_ID ; id++ )
	{
		m_countLost.robot[id] = 0;
	}
}

CVisionCore::~CVisionCore(void)
{
	//delete m_pBall;
	//delete m_pOpponent;
	//delete m_pID[0];
	//delete m_pID[1];
	//delete m_pID[2];
	//delete m_pTeam;

	if( m_pMarkTable != NULL )
	{
		delete[] m_pMarkTable;
		m_pMarkTable = NULL;
	}
	if( m_pProcessingArea != NULL )
	{
		delete[] m_pProcessingArea;
		m_pProcessingArea = NULL;
	}
}

void CVisionCore::SetScanInterval( int valueScanInterval )
{
	m_valueScanInterval = valueScanInterval;
}

void CVisionCore::SetBallMinMax( int valueBallMin, int valueBallMax )
{
	m_valueBallMin = valueBallMin;
	m_valueBallMax = valueBallMax;
}

void CVisionCore::SetTeamMinMax( int valueTeamMin, int valueTeamMax )
{
	m_valueTeamMin = valueTeamMin;
	m_valueTeamMax = valueTeamMax;
}

void CVisionCore::SetIDMinMax( int valueIDMin, int valueIDMax )
{
	m_valueIDMin = valueIDMin;
	m_valueIDMax = valueIDMax;
}

void CVisionCore::SetOppMinMax( int valueOppMin, int valueOppMax )
{
	m_valueOppMin = valueOppMin;
	m_valueOppMax = valueOppMax;
}

void CVisionCore::SetRevision(CRevision *pRvs, CRevision *pRvs_ball)
{
	m_pRevision = pRvs;
	m_pRevision_ball = pRvs_ball;
}

void CVisionCore::SetGround(CGround* pGround)
{
	m_pGround = pGround;
}

void CVisionCore::Run()
{
	Run_InitFlags();
	Run_SearchPatch();

	Run_FindBall();

	Run_FindPatchPosition( m_patchOpponent );
	Run_FindPatchPosition( m_patchTeam );

	for( int i=0 ; i<3 ; i++ )
		Run_FindPatchPosition( m_patchAssistant[i] );

	Run_FindRobot();
}

void CVisionCore::Run_FindRobot()
{
}

void CVisionCore::Run_InitFlags()
{
	m_patchBall.clear();
	m_patchOpponent.clear();
	m_patchTeam.clear();
	
	for( int id=0 ; id<3 ; id++ )
	{
		m_patchAssistant[id].clear();
	}

	m_foundBall = false;
	
	for( int id=0 ; id<MAX_OF_ROBOT_ID ; id++ )
	{
		m_RobotHome[id].bValid = false;
		m_RobotOpp[id].bValid = false;
	}
	
	ZeroMemory( m_pMarkTable, sizeof(unsigned char)*CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX );
}

void CVisionCore::Run_SearchPatch()
{
}

void CVisionCore::FindPatch( int p, int x, int y, std::vector<patch_Structure>& patch, unsigned char mask, int valueMin, int valueMax, int scan_interval)
{
	/*
	if( !(m_pMarkTable[p/3] & mask))
	{
		patch_Structure new_patch;
			
		SearchPatchRecursive( p, x, y, new_patch, mask, scan_interval, valueMax);
			
		if( valueMin <= (int)new_patch.pixels.size() && (int)new_patch.pixels.size() <= valueMax )
		{
			patch.push_back( new_patch );
		}
	}
	*/

	if( !(m_pMarkTable[p/3] & mask))
	{
		patch_Structure new_patch;
			
		SearchPatchRecursive( p, x, y, new_patch, mask, scan_interval, valueMax);

		//patch.push_back( new_patch );
			
		//if( false )
		if( valueMin <= (int)new_patch.pixels.size() && (int)new_patch.pixels.size() <= valueMax )
		{
			patch_Structure new_patch_filter;

			CPoint p[4];
			unsigned char r,g,b;
			unsigned char patchLUTData;
			int check_neighbor;

			for( auto it = new_patch.pixels.begin() ; it != new_patch.pixels.end() ; it++ )
			{
				if( it->x > m_rectImage.left+scan_interval
				 && it->x < m_rectImage.right-scan_interval
				 && it->y > m_rectImage.top+scan_interval
				 && it->y < m_rectImage.bottom-scan_interval )
				{
					p[0] = *it + CPoint(-scan_interval,0);
					p[1] = *it + CPoint( scan_interval,0);
					p[2] = *it + CPoint(0,-scan_interval);
					p[3] = *it + CPoint(0, scan_interval);

					check_neighbor = 0;

					for( int i=0 ; i<4 ; i++ )
					{
						m_pImageGrabber->GetColor( r, g, b, p[i].x, p[i].y, m_cameraID );

						patchLUTData = m_pLookUpTable->GetLUTData(r,g,b);
		
						if( patchLUTData & mask)
						{
							check_neighbor++;
						}
					}

					if( check_neighbor > 2 )
						new_patch_filter.pixels.push_back( *it );
				}
			}

			if( valueMin <= (int)new_patch_filter.pixels.size() && (int)new_patch_filter.pixels.size() <= valueMax )
				patch.push_back( new_patch_filter );
		}
	}
}

void CVisionCore::SearchPatchRecursive( int p, int x, int y, patch_Structure& patch, unsigned char mask, int scan_interval, int valueMax )
{
	int q = p/3;

	patch.pixels.push_back( CPoint(x,y) );

	if( (int)patch.pixels.size() < valueMax )
	{	
		if( scan_interval > 1 )
		{
			for( int i=0 ; i<scan_interval ; i++ )
				for( int j=0 ; j<scan_interval ; j++ )
				{
					if( x+i < CAMERA_WIDTH_MAX && y+j < CAMERA_HEIGHT_MAX )
						m_pMarkTable[(x+i) + (y+j)*m_pImageGrabber->Width()] |= mask;
				}
		}
		else
		{
			m_pMarkTable[q] |= mask;
		}

		if( m_pProcessingArea[x+y*CAMERA_WIDTH_MAX] == 1 )
			return;
	
		unsigned char r, g, b;
		unsigned char patchLUTData;
	
		// LEFT
		if (x > m_rectImage.left && !(m_pMarkTable[q-scan_interval] & mask))
		{
			m_pImageGrabber->GetColor( r, g, b, x-scan_interval, y, m_cameraID );
		
			patchLUTData = m_pLookUpTable->GetLUTData(r,g,b);
		
			if( patchLUTData & mask)
				SearchPatchRecursive( p - 3*scan_interval, x - scan_interval, y, patch, mask, scan_interval, valueMax );
		}
	
		// UP
		if (y > m_rectImage.top && !(m_pMarkTable[q-scan_interval*m_pImageGrabber->Width()] & mask))
		{
			m_pImageGrabber->GetColor( r, g, b, x, y-scan_interval, m_cameraID );
		
			patchLUTData = m_pLookUpTable->GetLUTData(r,g,b);
		
			if( patchLUTData & mask)
				SearchPatchRecursive( p - NEXT_Y*scan_interval, x, y-scan_interval, patch, mask, scan_interval, valueMax );
		}
	
		// RIGHT
		if (x < m_rectImage.right && !(m_pMarkTable[q+scan_interval] & mask))
		{
			m_pImageGrabber->GetColor( r, g, b, x+scan_interval, y, m_cameraID );
		
			patchLUTData = m_pLookUpTable->GetLUTData(r,g,b);
		
			if( patchLUTData & mask)
				SearchPatchRecursive( p+3*scan_interval, x+scan_interval, y, patch, mask, scan_interval, valueMax );
		}
	
		// DOWN
		if (y < m_rectImage.bottom && !(m_pMarkTable[q+scan_interval*m_pImageGrabber->Width()] & mask))
		{
			m_pImageGrabber->GetColor( r, g, b, x, y+scan_interval, m_cameraID );
		
			patchLUTData = m_pLookUpTable->GetLUTData(r,g,b);
		
			if( patchLUTData & mask)
				SearchPatchRecursive( p+NEXT_Y*scan_interval, x, y+scan_interval, patch, mask, scan_interval, valueMax);
		}
	
		//	unsigned char unmask = (0xFF - mask);
		//	m_markTable[x][y] &= unmask;
	}
}


void CVisionCore::Run_FindBall()
{
	if( (int)m_patchBall.size()  == 0 )
		return;

	int numPixels=0, maxIndex=-1;
		
	for (int l=0; l<(int)m_patchBall.size() ; l++)
	{
		int sumX = 0, sumY = 0;
		for( int p=0 ; p<(int)m_patchBall[l].pixels.size() ; p++)
		{
			sumX += m_patchBall[l].pixels[p].x;
			sumY += m_patchBall[l].pixels[p].y;
		}
		m_patchBall[l].Center.x = (double)sumX / (double)m_patchBall[l].pixels.size();
		m_patchBall[l].Center.y = (double)sumY / (double)m_patchBall[l].pixels.size();
			
			
		if( numPixels < (int)m_patchBall[l].pixels.size() )
		{
			numPixels = (int)m_patchBall[l].pixels.size() ;
			maxIndex = l;
		}
	}
	
	int sumX = 0,  sumY = 0;
	if( maxIndex >= 0 )
	{
		for (int p=0; p<numPixels; p++) {
			sumX += m_patchBall[ maxIndex ].pixels[p].x;
			sumY += m_patchBall[ maxIndex ].pixels[p].y;
		}
	}

	if( m_pRevision_ball != NULL )
	{
		if( numPixels > 0 )
		{
			m_foundBall = true;
			m_revisionBallPos.x = (double)sumX / numPixels;
			m_revisionBallPos.y = (double)sumY / numPixels;
		}
		else
		{
			m_foundBall = false;
			m_revisionBallPos.x = 0;
			m_revisionBallPos.y = 0;
		}


		m_pRevision_ball->VisionToFlat( m_revisionBallPos.x, m_revisionBallPos.y );
		m_pRevision_ball->FlatToScreen( m_revisionBallPos.x, m_revisionBallPos.y );
			
		double x = m_revisionBallPos.x;
		double y = m_revisionBallPos.y;
		m_pGround->ScreenToGround( x, y );
		m_realBallPos.x = x;
		m_realBallPos.y = y;
			
	}
	else
	{
		m_revisionBallPos = CPointDouble(0,0);
		m_realBallPos = CPointDouble(0,0);
	}
}


void CVisionCore::Draw_BallPatch( CDC *pDC, COLORREF color )
{
	for( int p=0 ; p<(int)m_patchBall.size() ; p++ )
	{
		for( int pixel=0 ; pixel<(int)m_patchBall[p].pixels.size() ; pixel++ )
		{
			int x = m_patchBall[p].pixels[pixel].x;
			int y = m_patchBall[p].pixels[pixel].y;
			
			pDC->SetPixel( x, y, color );
		}
		
		pDC->SetPixel( (int)m_patchBall[p].Center.x, (int)m_patchBall[p].Center.y, RGB(0,255,255) );
		
		pDC->SetBkMode( TRANSPARENT );
		pDC->SetTextColor( color );
		CString tmp;
		tmp.Format(_T("%d"), (int)m_patchBall[p].pixels.size());
		pDC->TextOut( (int)m_patchBall[p].Center.x, (int)m_patchBall[p].Center.y+10, tmp);
	}
}


void CVisionCore::Draw_OpponentsPatch(CDC *pDC, COLORREF color)
{
	for( int p=0 ; p<(int)m_patchOpponent.size() ; p++ )
	{
		for( int pixel=0 ; pixel<(int)m_patchOpponent[p].pixels.size() ; pixel++ )
		{
			int x = m_patchOpponent[p].pixels[pixel].x;
			int y = m_patchOpponent[p].pixels[pixel].y;
			
			pDC->SetPixel( x, y, color );
		}
		
		pDC->SetPixel( (int)m_patchOpponent[p].Center.x, (int)m_patchOpponent[p].Center.y, RGB(0,255,255) );
		
		pDC->SetBkMode( TRANSPARENT );
		pDC->SetTextColor( color );
		CString tmp;
		tmp.Format(_T("%d"), m_patchOpponent[p].pixels.size() );
		pDC->TextOut( (int)m_patchOpponent[p].Center.x, (int)m_patchOpponent[p].Center.y+10, tmp);
	}
}


void CVisionCore::Draw_TeamPatch( CDC *pDC, COLORREF color )
{
	for( int p=0 ; p<(int)m_patchTeam.size() ; p++ )
	{
		for( int pixel=0 ; pixel<(int)m_patchTeam[p].pixels.size() ; pixel++ )
		{
			int x = m_patchTeam[p].pixels[pixel].x;
			int y = m_patchTeam[p].pixels[pixel].y;
			
			pDC->SetPixel( x, y, color );
		}
		
		pDC->SetPixel( (int)m_patchTeam[p].Center.x, (int)m_patchTeam[p].Center.y, RGB(0,255,255) );
		
		pDC->SetBkMode( TRANSPARENT );
		pDC->SetTextColor( color );
		CString tmp;
		tmp.Format(_T("%d"), m_patchTeam[p].pixels.size() );
		pDC->TextOut( (int)m_patchTeam[p].Center.x, (int)m_patchTeam[p].Center.y+10, tmp);
	}
}

void CVisionCore::Draw_IDPatch(CDC* pDC, int id, COLORREF color)
{
	int ass_id = id;
	for (int p = 0; p < (int)m_patchAssistant[ass_id].size(); p++)
	{
		for (int pixel = 0; pixel < (int)m_patchAssistant[ass_id][p].pixels.size(); pixel++)
		{
			int x = m_patchAssistant[ass_id][p].pixels[pixel].x;
			int y = m_patchAssistant[ass_id][p].pixels[pixel].y;

			pDC->SetPixel(x, y, color);
		}

		pDC->SetPixel((int)m_patchAssistant[ass_id][p].Center.x, (int)m_patchAssistant[ass_id][p].Center.y, RGB(0, 255, 255));

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(color);
		CString tmp;
		tmp.Format(_T("%d"), (int)m_patchAssistant[ass_id][p].pixels.size());
		pDC->TextOut((int)m_patchAssistant[ass_id][p].Center.x, (int)m_patchAssistant[ass_id][p].Center.y + 10, tmp);

	}
}


void CVisionCore::Run_FindPatchPosition( std::vector<patch_Structure> & patch )
{
	if( m_pRevision != NULL )
	{
		for (int l=0; l<(int)patch.size() ; l++)
		{
			//PatchFilter( patch[l] );
			
			int sumX = 0, sumY = 0;
			for (int p=0; p<(int)patch[ l ].pixels.size() ; p++)
			{
				sumX += patch[ l ].pixels[p].x;
				sumY += patch[ l ].pixels[p].y;
			}
			
			patch[l].bFound = true;
				
			// pixel position
			patch[ l ].Center.x = (double)sumX / patch[ l ].pixels.size();
			patch[ l ].Center.y = (double)sumY / patch[ l ].pixels.size();
			
			// calc revision position
			patch[l].revisionCenter.x = patch[ l ].Center.x;
			patch[l].revisionCenter.y = patch[ l ].Center.y;
			m_pRevision->VisionToFlat( patch[l].revisionCenter.x, patch[l].revisionCenter.y );
			m_pRevision->FlatToScreen( patch[l].revisionCenter.x, patch[l].revisionCenter.y );
				
			// calc real position
			patch[l].realCenter = patch[l].revisionCenter;
			m_pGround->ScreenToGround( patch[l].realCenter.x, patch[l].realCenter.y );
		}
	}	
}

void CVisionCore::Run_FindPatchPosition( patch_Structure& patch )
{
	int numPixels=0, maxIndex=0;
		
	int sumX = 0, sumY = 0;
	for (int p=0; p<(int)patch.pixels.size(); p++)
	{
		sumX += patch.pixels[p].x;
		sumY += patch.pixels[p].y;
	}
			
	if( m_pRevision != NULL )
	{
		patch.bFound = true;
				
		// pixel position
		patch.Center.x = (double)sumX / patch.pixels.size();
		patch.Center.y = (double)sumY / patch.pixels.size();
			
		// calc revision position
		patch.revisionCenter.x = patch.Center.x;
		patch.revisionCenter.y = patch.Center.y;
		m_pRevision->VisionToFlat( patch.revisionCenter.x, patch.revisionCenter.y );
		m_pRevision->FlatToScreen( patch.revisionCenter.x, patch.revisionCenter.y );
				
		// calc real position
		patch.realCenter = patch.revisionCenter;
		m_pGround->ScreenToGround( patch.realCenter.x, patch.realCenter.y );
	}	
}


void CVisionCore::Draw_Robot( CDC *pDC, BOOL bAllRobot, BOOL bRobot[])
{
	CPen pen, *pOldPen;
	pen.CreatePen( PS_SOLID, 1, RGB(255,255,255) );
	pOldPen = (CPen*)pDC->SelectObject( &pen );
	
	pDC->SelectStockObject( NULL_BRUSH );
	
	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( RGB( 128,128,128 ) );

	for( int i=0 ; i<MAX_OF_ROBOT_ID ; i++ )
	{
		if( m_RobotHome[i].bValid && ( bAllRobot || bRobot[i] ) )
		{
			CPointDouble pos;
			double orientation=0;
			int size;
			
			pos = m_RobotHome[i].pixelPos;
			orientation = m_RobotHome[i].direction;
			//orientation = m_RobotHome[i].pixeldirection;
			size = 20;
			
			pDC->Ellipse( (int)pos.x - size, (int)pos.y - size,
				(int)pos.x + size, (int)pos.y + size);
			
			int x =  (int)( size * cos( orientation ) );
			int y = -(int)( size * sin( orientation ) );
			
			pDC->MoveTo( pos.Integer() );
			pDC->LineTo( (int)pos.x+x, (int)pos.y+y );
			
			CString tmp;
			tmp.Format(_T("[%d] X=%.2lfm, Y=%.2lfm, ori=%.0lf°"), i+1, m_RobotHome[i].realPos.x, m_RobotHome[i].realPos.y, orientation*180/M_PI);

			pDC->SetTextColor( RGB(255,128,64));
			pDC->TextOut(  (int)pos.x, (int)pos.y, tmp );
		}
	}
	
	pDC->SelectObject( pOldPen );
}

void CVisionCore::UpdateObjectPositionInfo(CObjectPositionInfo &info)
{
	if( m_foundBall )
	{
		info.m_Ball.state = OBJECT_STATE_REAL;
		info.m_Ball.pos.x = m_realBallPos.x;
		info.m_Ball.pos.y = m_realBallPos.y;

		m_countLost.ball = 0;
	}
	else
	{
		m_countLost.ball++;
		info.m_Ball.countLost = m_countLost.ball;
	}
	
	for( int i=0 ; i<MAX_OF_ROBOT_ID ; i++ )
	{
		if( m_RobotHome[i].bValid )
		{
			info.m_Robot[i].state = OBJECT_STATE_REAL;
			info.m_Robot[i].pos.x = m_RobotHome[i].realPos.x;
			info.m_Robot[i].pos.y = m_RobotHome[i].realPos.y;
			info.m_Robot[i].orientation = m_RobotHome[i].direction*180/M_PI;

			m_countLost.robot[i] = 0;
		}
		else
		{
			m_countLost.robot[i]++;

			info.m_Robot[i].countLost = m_countLost.robot[i];
		}
		
		// MAX_LABEL_NUMBER > MAX_OF_ROBOT_ID
		if( (int)m_patchOpponent.size() > i )
		{
			info.m_Opp[i].state = OBJECT_STATE_REAL;
			info.m_Opp[i].pos.x = m_patchOpponent[i].realCenter.x;
			info.m_Opp[i].pos.y = m_patchOpponent[i].realCenter.y;
		}
	}
}

void CVisionCore::SetPatchDirectionOffset(double offset)
{
	m_PatchDirectionOffset = offset;
}


void CVisionCore::DrawProcessingArea( CDC *pDC, COLORREF color )
{
	for( int i=0 ; i<CAMERA_WIDTH_MAX ; i++)
	{
		for( int j=0 ; j<CAMERA_HEIGHT_MAX ; j++)
		{
			if( m_pProcessingArea[ i + j*CAMERA_WIDTH_MAX ] )
				pDC->SetPixel( i, j, color );
		}
	}
}

void CVisionCore::ProcessingAreaUpdate( int x, int y, bool bCheck, int size )
{
	int left   = std::max(0, x-size+1);
	int right  = std::min(CAMERA_WIDTH_MAX-1, x+size);
	int top    = std::max(0, y-size+1);
	int bottom = std::min(CAMERA_HEIGHT_MAX-1, y+size);

	unsigned char check = 0;
	if( bCheck )
		check = 1;


	for( int i=left ; i<=right ; i++)
	{
		for( int j=top ; j<=bottom; j++)
		{
			m_pProcessingArea[ i + j*CAMERA_WIDTH_MAX ] = check;
		}
	}
}

void CVisionCore::CopyData(CVisionCore& vision)
{
	//unsigned char* m_pProcessingArea;
	//CopyMemory( m_pProcessingArea, vision.m_pProcessingArea, sizeof(unsigned char)*CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX );


	m_revisionBallPos = vision.m_revisionBallPos    ;
	m_realBallPos     = vision.m_realBallPos        ;
	m_foundBall       = vision.m_foundBall          ;
	m_patchBall       = vision.m_patchBall          ;
	m_patchOpponent       = vision.m_patchOpponent          ;
	m_patchAssistant[0]       = vision.m_patchAssistant[0]          ;
	m_patchAssistant[1]       = vision.m_patchAssistant[1]          ;
	m_patchAssistant[2]       = vision.m_patchAssistant[2]          ;
	m_patchTeam       = vision.m_patchTeam          ;

	for( int i=0 ; i<MAX_OF_ROBOT_ID ; i++ )
	{
		m_RobotHome[i] = vision.m_RobotHome[i];
		m_RobotOpp[i]  = vision.m_RobotOpp[i] ;
	}

	NEXT_Y = vision.NEXT_Y;

	//unsigned char* m_pMarkTable;
	//CopyMemory( m_pMarkTable     , vision.m_pMarkTable     , sizeof(unsigned char)*CAMERA_WIDTH_MAX*CAMERA_HEIGHT_MAX );

	m_cameraID = vision.m_cameraID;

	m_rectImage = vision.m_rectImage;
	m_valueScanInterval = vision.m_valueScanInterval;
	m_valueBallMin      = vision.m_valueBallMin     ;
	m_valueBallMax      = vision.m_valueBallMax     ;
	m_valueTeamMin      = vision.m_valueTeamMin     ;
	m_valueTeamMax      = vision.m_valueTeamMax     ;
	m_valueIDMin        = vision.m_valueIDMin       ;
	m_valueIDMax        = vision.m_valueIDMax       ;
	m_valueOppMin       = vision.m_valueOppMin      ;
	m_valueOppMax       = vision.m_valueOppMax      ;
	m_PatchDirectionOffset = vision.m_PatchDirectionOffset;

	//CRevision* m_pRevision;
	//CGround* m_pGround;
}



void CVisionCore::PatchFilter( patch_Structure& patch )
{
	if( (int)patch.pixels.size() <= 0 )
		return;

	double k = 0.75;

	patch.Center.x = 0;
	patch.Center.y = 0;

	for(int p=0; p<(int)patch.pixels.size(); p++)
	{
		patch.Center.x += patch.pixels[p].x;
		patch.Center.y += patch.pixels[p].y;
	}

	patch.Center.x = patch.Center.x / patch.pixels.size();
	patch.Center.y = patch.Center.y / patch.pixels.size();

	std::vector<double> d;
	for( int p=0; p<(int)patch.pixels.size() ; p++ )
	{

		d.push_back( sqrt( (patch.pixels[p].x - patch.Center.x)*(patch.pixels[p].x - patch.Center.x)
			+ (patch.pixels[p].y - patch.Center.y)*(patch.pixels[p].y - patch.Center.y) ) );
	}

	for(int p1=0; p1<(int)patch.pixels.size() ; p1++)
	{
		for (int p2=p1+1; p2<(int)patch.pixels.size() ; p2++)
		{
			if( d[p1] > d[p2] )
			{
				double imsi = d[p1];
				d[p1] = d[p2];
				d[p2] = imsi;

				CPoint tmp = patch.pixels[p1];
				patch.pixels[p1] = patch.pixels[p2];
				patch.pixels[p2] = tmp;

			}
		}
	}

	int delete_NofPixels = (int)(patch.pixels.size() * (1.0-k));

	for( int i=0 ; i<delete_NofPixels ; i++ )
	{
		auto it = patch.pixels.end()-1;
		patch.pixels.erase(it);
	}

	/*
	patch.Center.x = 0;
	patch.Center.y = 0;

	int new_NofPixels = (int)(patch.pixels.size() * k);
	if( new_NofPixels == 0 )
		new_NofPixels = 1;

	for ( int p=0; p<new_NofPixels; p++)
	{
		patch.Center.x += patch.pixels[p].x;
		patch.Center.y += patch.pixels[p].y;
	}

	patch.Center.x = patch.Center.x / new_NofPixels;
	patch.Center.y = patch.Center.y / new_NofPixels;
	*/
}
