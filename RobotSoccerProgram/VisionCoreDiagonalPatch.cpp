#include "StdAfx.h"
#include "VisionCoreDiagonalPatch.h"
#include <iostream>
using namespace std;

#define _USE_MATH_DEFINES
#include <math.h>

void CVisionCoreDiagonalPatch::SetPatchDirectionOffset( double offset )
{
	// Offset for the correct orientation.
	m_PatchDirectionOffset = offset - 90;
}

CVisionCoreDiagonalPatch::~CVisionCoreDiagonalPatch(void)
{
}

void CVisionCoreDiagonalPatch::SetTeamIDDistance(double distance)
{
	m_valueTeamIDDistance = distance;
}
CVisionCoreDiagonalPatch::CVisionCoreDiagonalPatch(void) 
{
	CVisionCore::CVisionCore();

	m_SelectRobotPosition.x = 0;
	m_SelectRobotPosition.y = 0;

	m_SegmentPosition[0] = CPointDouble(2.5, 7.5/4);
	m_SegmentPosition[1] = CPointDouble(-2.5, -7.5/4);

	// The values of each segment position to match respective robot id's
	int matching_data[5][2] =
	{
		{  1, 0, }, // 1
		{  2, 0, }, // 2
		{  3, 0, }, // 3
		{  1, 2, }, // 4
		{  1, 3, }, // 5
	};
	// Set segCombination to data
	for (int id = 0; id < MAX_OF_ROBOT_ID; id++)
		for (int seg = 0; seg < 2; seg++)
			m_SegCombination[id][seg] = matching_data[id][seg];

	m_valueSegmentCheckDistance = 1;

}


void CVisionCoreDiagonalPatch::SetAssistantMinMax(int valueAssistantMin, int valueAssistantMax)
{
	m_valueAssistantMin = valueAssistantMin;
	m_valueAssistantMax = valueAssistantMax;
}

void CVisionCoreDiagonalPatch::SetSegmentThreshold(int valueSegmentThreshold)
{
	m_valueSegmentThreshold = 1;
}

void CVisionCoreDiagonalPatch::SetSegmentCheckDistance(int distance)
{
	m_valueSegmentCheckDistance = distance;
}

void CVisionCoreDiagonalPatch::SetTeamAssistantDistance(double distance)
{
	m_valueTeamAssistantDistance = distance;
}

void CVisionCoreDiagonalPatch::Run()
{
	Run_InitFlags();
	Run_SearchPatch();

	Run_FindBall();
	Run_FindPatchPosition(m_patchOpponent);
	Run_FindPatchPosition(m_patchTeam);

	for (int i = 0; i < 3; i++)
		Run_FindPatchPosition(m_patchAssistant[i]);

	Run_FindAssistant();

	Run_FindRobot();
}

void CVisionCoreDiagonalPatch::SetIDSelectData(int data[][2])
{
	m_IDSelect[0][0] = data[0][0];
	m_IDSelect[0][1] = data[0][1];
	m_IDSelect[1][0] = data[1][0];
	m_IDSelect[1][1] = data[1][1];
	m_IDSelect[2][0] = data[2][0];
	m_IDSelect[2][1] = data[2][1];
	m_IDSelect[3][0] = data[3][0];
	m_IDSelect[3][1] = data[3][1];
	m_IDSelect[4][0] = data[4][0];
	m_IDSelect[4][1] = data[4][1];
}


void CVisionCoreDiagonalPatch::Run_InitFlags()
{
	CVisionCore::Run_InitFlags();

	m_vecSegmentCount.clear();
}

void CVisionCoreDiagonalPatch::Run_SearchPatch()
// Looks for each sampled patch based off the colours set in colour patch list
{
	m_rectImage = CRect(0, 0, m_pImageGrabber->Width() - 1, m_pImageGrabber->Height() - 1);

	if (m_valueScanInterval == 0)
		m_valueScanInterval = 1;

	unsigned char r, g, b;
	unsigned char patchLUTData;

	int NEXT_X;
	int NEXT_Y3;

	//1.8 + x = 4.2
	int p = 0;
	NEXT_X = m_valueScanInterval * 3;
	NEXT_Y = m_pImageGrabber->Width() * 3;	// 다른 함수에서 쓰이므로 멤버 변수로 정의
	NEXT_Y3 = m_pImageGrabber->Width() * 3 * (m_valueScanInterval - 1);


	int total = (m_pImageGrabber->Width() * m_pImageGrabber->Height() / m_valueScanInterval);
	//set colours based on colour patch list
	unsigned char mask_id[3], mask_team, mask_opp, mask_ball;
	mask_ball = VISION_PATCH_MASK_0;
	mask_id[0] = VISION_PATCH_MASK_1;
	mask_id[1] = VISION_PATCH_MASK_2;
	mask_id[2] = VISION_PATCH_MASK_3;
	mask_team = VISION_PATCH_MASK_4;
	mask_opp = VISION_PATCH_MASK_7;


	while (total--)
	{
		int x = (p / 3) % m_pImageGrabber->Width();
		int y = p / m_pImageGrabber->Width() / 3;

		if (x > m_rectImage.left && y > m_rectImage.top
			&& x < m_rectImage.right && y < m_rectImage.bottom)
		{
		}
		else
		{
			p += NEXT_X;
			continue;
		}

		if (m_pProcessingArea[x + y * CAMERA_WIDTH_MAX] == 0)
		{
		}
		else
		{
			p += NEXT_X;
			continue;
		}

		m_pImageGrabber->GetColor(r, g, b, x, y, m_cameraID);
		patchLUTData = m_pLookUpTable->GetLUTData(r, g, b);

		if ((patchLUTData & mask_ball))
			FindPatch(p, x, y, m_patchBall, mask_ball, m_valueBallMin, m_valueBallMax, 1);

		if ((patchLUTData & mask_team))
			FindPatch(p, x, y, m_patchTeam, mask_team, m_valueTeamMin, m_valueTeamMax, 1);

		if ((patchLUTData & mask_opp))
			FindPatch(p, x, y, m_patchOpponent, mask_opp, m_valueOppMin, m_valueOppMax, 1);
		
		// Finding the sampled ID colours
		
		if ((patchLUTData & mask_id[0]))
			FindPatch(p, x, y, m_patchAssistant[0], mask_id[0], m_valueIDMin, m_valueIDMax, 1);
		
		if ((patchLUTData & mask_id[1]))
			FindPatch(p, x, y, m_patchAssistant[1], mask_id[1], m_valueIDMin, m_valueIDMax, 1);

		if ((patchLUTData & mask_id[2]))
			FindPatch(p, x, y, m_patchAssistant[2], mask_id[2], m_valueIDMin, m_valueIDMax, 1);
			
		p += NEXT_X;

	}
}


void CVisionCoreDiagonalPatch::Run_FindAssistant()
{
	const int ASS_DIVIDE_K = 16;

	unsigned char mask_ass[3];
	mask_ass[0] = VISION_PATCH_MASK_1;
	mask_ass[1] = VISION_PATCH_MASK_2;
	mask_ass[2] = VISION_PATCH_MASK_3;

	for (int ass_id = 0; ass_id < 3; ass_id++)
	{
		for (int i = 0; i < (int)m_patchTeam.size(); i++)
		{
			double cx = m_patchTeam[i].realCenter.x;
			double cy = m_patchTeam[i].realCenter.y;

			for (double a = 0; a < 2 * M_PI; a += M_PI / ASS_DIVIDE_K)
			{
				double px = cx + m_valueTeamIDDistance * cos(a);
				double py = cy + m_valueTeamIDDistance * sin(a);

				m_pGround->GroundToScreen(px, py);
				m_pRevision->ScreenToFlat(px, py);
				m_pRevision->FlatToVision(px, py);

				COLORREF color = m_pImageGrabber->GetColorFloat(px, py, m_cameraID);
				unsigned char patchLUTData = m_pLookUpTable->GetLUTData(GetRValue(color),
					GetGValue(color),
					GetBValue(color));

				int x = (int)px;
				int y = (int)py;
				int p = (y * m_pImageGrabber->Width() + x) * 3;

				if ((patchLUTData & mask_ass[ass_id]))
				{
					if (!(m_pMarkTable[p / 3] & mask_ass[ass_id]))
					{
						patch_Structure new_patch;
						new_patch.related_id = i;

						unsigned char mask = mask_ass[ass_id];
						SearchPatchRecursive(p, x, y, new_patch, mask, 1, m_valueIDMax);

						if (m_valueIDMin <= (int)new_patch.pixels.size() && (int)new_patch.pixels.size() <= m_valueIDMax)
						{
							Run_FindPatchPosition(new_patch);
							m_patchAssistant[ass_id].push_back(new_patch);
							break;
						}
					}
				}
			}
		}
	}
}

void CVisionCoreDiagonalPatch::PatchFilter(patch_Structure& patch)
{
	if ((int)patch.pixels.size() <= 0)
		return;

	double k = 0.85;

	patch.Center.x = 0;
	patch.Center.y = 0;

	for (int p = 0; p < (int)patch.pixels.size(); p++)
	{
		patch.Center.x += patch.pixels[p].x;
		patch.Center.y += patch.pixels[p].y;
	}

	patch.Center.x = patch.Center.x / patch.pixels.size();
	patch.Center.y = patch.Center.y / patch.pixels.size();

	std::vector<double> d;
	for (int p = 0; p < (int)patch.pixels.size(); p++)
	{

		d.push_back(sqrt((patch.pixels[p].x - patch.Center.x) * (patch.pixels[p].x - patch.Center.x)
			+ (patch.pixels[p].y - patch.Center.y) * (patch.pixels[p].y - patch.Center.y)));
	}

	for (int p1 = 0; p1 < (int)patch.pixels.size(); p1++)
	{
		for (int p2 = p1 + 1; p2 < (int)patch.pixels.size(); p2++)
		{
			if (d[p1] > d[p2])
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


	patch.Center.x = 0;
	patch.Center.y = 0;

	int new_NofPixels = (int)(patch.pixels.size() * k);
	if (new_NofPixels == 0)
		new_NofPixels = 1;

	for (int p = 0; p < new_NofPixels; p++)
	{
		patch.Center.x += patch.pixels[p].x;
		patch.Center.y += patch.pixels[p].y;
	}

	patch.Center.x = patch.Center.x / new_NofPixels;
	patch.Center.y = patch.Center.y / new_NofPixels;
}


// 주변 점 Interporation해서 보기
// Don't care value 추가
void CVisionCoreDiagonalPatch::Run_FindRobot()
// Find robot based on team patch and id colours, also orientates the robot based on the team patch 
{

	// Bar Patch Function
	
	unsigned char mask_team, mask_id[3];
	mask_team = VISION_PATCH_MASK_4;
	mask_id[0] = VISION_PATCH_MASK_1;
	mask_id[1] = VISION_PATCH_MASK_2;
	mask_id[2] = VISION_PATCH_MASK_3;
	// unsigned char patchLUTData_0, patchLUTData_1;

	bool id1 = FALSE;
	bool id2 = FALSE;
	bool id3 = FALSE;

	for (int i = 0; i < (int)m_patchTeam.size(); i++)
	{
		int segment_count[2];
		segment_count[0] = 0;
		segment_count[1] = 0;

		double robot_angle[2];
		double robot_angle_screen[2];

		{
			double a = 0, b = 0, c = 0;
			//		a += (xi - x_min)^2
			//		b += (xi - x_min) (yi - y_min)
			//		c += (yi - y_min)^2
			for (int p = 0; p < (int)m_patchTeam[i].pixels.size(); p++)
			{
				a += (m_patchTeam[i].pixels[p].x - m_patchTeam[i].Center.x) * (m_patchTeam[i].pixels[p].x - m_patchTeam[i].Center.x);
				b += (m_patchTeam[i].pixels[p].x - m_patchTeam[i].Center.x) * (m_patchTeam[i].pixels[p].y - m_patchTeam[i].Center.y);
				c += (m_patchTeam[i].pixels[p].y - m_patchTeam[i].Center.y) * (m_patchTeam[i].pixels[p].y - m_patchTeam[i].Center.y);
			}

			//double angle_rad = atan2( b, a-c + sqrt( (a-c)*(a-c) + b*b) ); // 90도일때 문제있음.
			// Arc tangent (b/a-c) in radians
			double angle_rad = atan2(b, a - c) / 2;

			{
				double angle_visoin_degree = angle_rad * 180 / M_PI;

				while (angle_visoin_degree > 180) angle_visoin_degree -= 360;
				while (angle_visoin_degree < -180) angle_visoin_degree += 360;
				

				double k1 = -angle_visoin_degree * 4;

				double k2 = sin(k1 / 180 * M_PI) * 10;

				angle_rad = angle_rad - k2 * M_PI / 180;
			}


			CPointDouble angle_point;

			angle_point.x = m_patchTeam[i].Center.x + 0.1 * cos(angle_rad);
			angle_point.y = m_patchTeam[i].Center.y + 0.1 * sin(angle_rad);

			robot_angle_screen[0] = (angle_point - m_patchTeam[i].Center).AngleRadian() - 3 * M_PI / 4;
			robot_angle_screen[1] = (angle_point - m_patchTeam[i].Center).AngleRadian() + M_PI / 4;

			CPointDouble angle_point_pixel = angle_point;

			m_pRevision->VisionToFlat(angle_point.x, angle_point.y);
			m_pRevision->FlatToScreen(angle_point.x, angle_point.y);
			m_pGround->ScreenToGround(angle_point.x, angle_point.y);

			robot_angle[0] = (angle_point - m_patchTeam[i].realCenter).AngleRadian() - 3*M_PI/4;
			robot_angle[1] = (angle_point - m_patchTeam[i].realCenter).AngleRadian() + M_PI/4;

			

			int matched_i = 0;
			int matched_id_i[2] = { -1, -1 };
			int matched_id_pi[2] = { -1, -1 };

			for (int id_i = 0; id_i < 5; id_i++)
			{
				for (int id_pi = 0; id_pi < (int)m_patchAssistant[id_i].size(); id_pi++)
				{
					if (m_patchTeam[i].bFound
						&& m_patchAssistant[id_i][id_pi].bFound
						&& m_patchAssistant[id_i][id_pi].related_id == i)
					{
						if (matched_i < 2)
						{
							matched_id_i[matched_i] = id_i;
							matched_id_pi[matched_i] = id_pi;
							matched_i++;
						}
					}
				}
			}

			if (matched_id_i[0] != -1 || matched_id_i[1] != -1)
			{
				int find_id = -1;

				for (int robot_id = 0; robot_id < 5; robot_id++)
				{
					if (m_IDSelect[robot_id][0] == matched_id_i[0] + 1 && m_IDSelect[robot_id][1] == matched_id_i[1] + 1)
					{
						find_id = robot_id;
					}
					else
						if (m_IDSelect[robot_id][1] == matched_id_i[0] + 1 && m_IDSelect[robot_id][0] == matched_id_i[1] + 1)
						{
							find_id = robot_id;

							int tmp = matched_id_i[0];
							matched_id_i[0] = matched_id_i[1];
							matched_id_i[1] = tmp;

							tmp = matched_id_pi[0];
							matched_id_pi[0] = matched_id_pi[1];
							matched_id_pi[1] = tmp;
						}
				}

				if (find_id >= 0)
				{
					m_RobotHome[find_id].bValid = true;
					m_RobotHome[find_id].id = find_id;
					m_RobotHome[find_id].pixelPos = m_patchTeam[i].Center;
					m_RobotHome[find_id].revisionPos = m_patchTeam[i].revisionCenter;
					m_RobotHome[find_id].realPos = m_patchTeam[i].realCenter;

					double robot_angle1 = (angle_point - m_patchTeam[i].realCenter).AngleRadian();
					double robot_angle2 = (angle_point - m_patchTeam[i].realCenter).AngleRadian() + M_PI;

					double robot_angle1_pixel = (angle_point_pixel - m_patchTeam[i].Center).AngleRadian();
					double robot_angle2_pixel = (angle_point_pixel - m_patchTeam[i].Center).AngleRadian() + M_PI;

					double id_angle_rad = 0;

					if (matched_id_i[0] != -1)
						id_angle_rad = (m_patchAssistant[matched_id_i[0]][matched_id_pi[0]].realCenter - m_patchTeam[i].realCenter).AngleRadian();
					else
						if (matched_id_i[1] != -1)
							id_angle_rad = (m_patchAssistant[matched_id_i[1]][matched_id_pi[1]].realCenter - m_patchTeam[i].realCenter).AngleRadian() + M_PI;

					double temp_robot_angle = id_angle_rad - M_PI / 2;

					double d_angle1 = temp_robot_angle - robot_angle1;
					double d_angle2 = temp_robot_angle - robot_angle2;


					while (d_angle1 > M_PI) d_angle1 -= M_PI * 2;
					while (d_angle1 < -M_PI) d_angle1 += M_PI * 2;
					while (d_angle2 > M_PI) d_angle2 -= M_PI * 2;
					while (d_angle2 < -M_PI) d_angle2 += M_PI * 2;

					if (fabs(d_angle1) < fabs(d_angle2))
					{
						m_RobotHome[find_id].direction = robot_angle1;
						m_RobotHome[find_id].pixeldirection = robot_angle1_pixel;
					}
					else
					{
						m_RobotHome[find_id].direction = robot_angle2;
						m_RobotHome[find_id].pixeldirection = robot_angle2_pixel;
					}

					m_RobotHome[find_id].direction += m_PatchDirectionOffset / 180.0 * M_PI;
					m_RobotHome[find_id].pixeldirection = m_PatchDirectionOffset / 180.0 * M_PI - m_RobotHome[find_id].pixeldirection;
				}
			}

		}



		double RadAngle = robot_angle[0] - (M_PI);
		
		double cx = m_patchTeam[i].realCenter.x;
		double cy = m_patchTeam[i].realCenter.y;
		

		{
			double rad = RadAngle;
			double cosTheta = cos(rad);
			double sinTheta = sin(rad);

			int total_count = 0;

			// Find the colour at each segment point and check it against the sampled id colours.
			for (int s = 0; s < 2; s++)
			{
				double d = (double)m_valueSegmentCheckDistance / 1000.0;
				double dx[5] = { 0, -d, -d,  d, d };
				double dy[5] = { 0, -d,  d, -d, d };
				for (int p = 0; p < 5; p++)
				{
					double x = m_SegmentPosition[s].x / 100.0 + dx[p];
					double y = m_SegmentPosition[s].y / 100.0 + dy[p];

					double seg_x = cx + cosTheta * x - sinTheta * y;
					double seg_y = cy + sinTheta * x + cosTheta * y;

					m_pGround->GroundToScreen(seg_x, seg_y);
					m_pRevision->ScreenToFlat(seg_x, seg_y);
					m_pRevision->FlatToVision(seg_x, seg_y);

					double i = seg_x;
					double j = seg_y;

					COLORREF color = m_pImageGrabber->GetColorFloat(i, j, m_cameraID);
					unsigned char patchLUTData = m_pLookUpTable->GetLUTData(GetRValue(color),
						GetGValue(color),
						GetBValue(color));

					if (patchLUTData == mask_id[0]) {
						segment_count[s] = 1;
						total_count++;
						id1 = TRUE;
					} else if(patchLUTData == mask_id[1]) {
						segment_count[s] = 2;
						total_count++;
						id2 = TRUE;
					} else if (patchLUTData == mask_id[2]) {
						segment_count[s] = 3;
						total_count++;
						id3 = TRUE;
					} else {
						segment_count[s] = 4;
					}
					
				}

			}
		}

		// Making sure that the robot image orientation the right way
		if ((segment_count[0] > segment_count[1])) {
			robot_angle[0] += M_PI;
			robot_angle_screen[0] += M_PI;
			robot_angle[1] += M_PI;
			robot_angle_screen[1] += M_PI;

			int temp = segment_count[0];
			segment_count[0] = segment_count[1];
			segment_count[1] = temp;
		}

		S_Segment_Count new_segment_count;
		new_segment_count.team_patch_id = i;
		new_segment_count.bInverseOrientation = false;
		new_segment_count.orientation_rad = robot_angle[0];
		new_segment_count.orientation_screen = robot_angle_screen[0];

		for (int s = 0; s < 2; s++)
		{
			new_segment_count.count[s] = segment_count[s];
		}

		m_vecSegmentCount.push_back(new_segment_count);

		
		new_segment_count.team_patch_id = i;
		new_segment_count.bInverseOrientation = true;
		new_segment_count.orientation_rad = robot_angle[1];
		new_segment_count.orientation_screen = robot_angle_screen[1];
		for (int s = 0; s < 2; s++)
		{
			new_segment_count.count[1 - s] = segment_count[s];
		}

		m_vecSegmentCount.push_back(new_segment_count);
	}


	int best_robot_seg_id[MAX_OF_ROBOT_ID];

	for (int i = 0; i < MAX_OF_ROBOT_ID; i++)
	{
		best_robot_seg_id[i] = -1;
	}

	for (int i = 0; i < (int)m_vecSegmentCount.size(); i++)
	{
		int match_id = -1;

		for (int id = 0; id < MAX_OF_ROBOT_ID; id++)
		{
			int match = 0;
			int id0_match = 0;
			int id1_match = 0;
			int id2_match = 0;
			int id3_match = 0;
			
			for (int s = 0; s < 2; s++)
			{
				// Checking the segment combination and ID-ing the robots
				if (m_SegCombination[id][s] == -1)
				{
					match++;
				}
				else
				{
					if (m_vecSegmentCount[i].count[s] == 4
						&& (m_SegCombination[id][s] == 0 | m_SegCombination[id][!s] == 0) && !id0_match)
					{
						match++;
						id0_match = 1;
					} else if (m_vecSegmentCount[i].count[s] == 1
						&& (m_SegCombination[id][s] == 1 | m_SegCombination[id][!s] == 1)  && !id1_match)
					{
						match++;
						id1_match = 1;
					} else if (m_vecSegmentCount[i].count[s] == 2
						&& (m_SegCombination[id][s] == 2 | m_SegCombination[id][!s] == 2) && !id2_match)
					{
						match++;
						id2_match = 1;
					} else if (m_vecSegmentCount[i].count[s] == 3
						&& (m_SegCombination[id][s] == 3 | m_SegCombination[id][!s] == 3) && !id3_match)
					{
						match++;
						id3_match = 1;
					}

				}
			}

			if (match == 2)
			{
				match_id = id;

			}
		}

		if (match_id >= 0)
		{
			if (best_robot_seg_id[match_id] == -1)
			{
				best_robot_seg_id[match_id] = i;
			}
			else
			{
				int team_patch_i_best = m_vecSegmentCount[best_robot_seg_id[match_id]].team_patch_id;

				int team_patch_i = m_vecSegmentCount[i].team_patch_id;

				if (m_patchTeam[team_patch_i].pixels.size() > m_patchTeam[team_patch_i_best].pixels.size())
				{
					best_robot_seg_id[match_id] = i;
				}
			}
		}
	}

	for (int id = 0; id < MAX_OF_ROBOT_ID; id++)
	{
		if (best_robot_seg_id[id] != -1)
		{
			int team_patch_i = m_vecSegmentCount[best_robot_seg_id[id]].team_patch_id;

			m_RobotHome[id].bValid = true;
			m_RobotHome[id].id = team_patch_i;

			m_RobotHome[id].pixelPos = m_patchTeam[team_patch_i].Center;
			m_RobotHome[id].realPos = m_patchTeam[team_patch_i].realCenter;
			m_RobotHome[id].revisionPos = m_patchTeam[team_patch_i].revisionCenter;

			m_RobotHome[id].direction = m_vecSegmentCount[best_robot_seg_id[id]].orientation_rad;
			m_RobotHome[id].pixeldirection = m_vecSegmentCount[best_robot_seg_id[id]].orientation_screen;
			m_RobotHome[id].direction += m_PatchDirectionOffset / 180.0 * M_PI;
			m_RobotHome[id].pixeldirection = m_PatchDirectionOffset / 180.0 * M_PI - m_RobotHome[id].pixeldirection;
		}
		else
		{
			m_RobotHome[id].bValid = false;
			m_RobotHome[id].id = -1;

			m_RobotHome[id].pixelPos = CPointDouble(0, 0);
			m_RobotHome[id].realPos = CPointDouble(0, 0);
			m_RobotHome[id].revisionPos = CPointDouble(0, 0);

			m_RobotHome[id].direction = 0;
			m_RobotHome[id].pixeldirection = 0;
		}
	}
}

void CVisionCoreDiagonalPatch::Display_RobotImage(CDC* pDC, int width, int height, int robot_i)
{
	if (robot_i < 0)
	{
		double min_distance = 15;

		for (int i = 0; i < (int)m_patchTeam.size(); i++)
		{
			//if( robot_i<0 || (m_pTeam->patch[i].Center - m_SelectRobotPosition).Distance() < min_distance )
			if ((m_patchTeam[i].Center - m_SelectRobotPosition).Distance() < min_distance)
			{
				robot_i = i;
			}
		}
	}

	if (robot_i < 0 || robot_i >= (int)m_patchTeam.size()) return;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			double x = m_patchTeam[robot_i].Center.x + (i - width / 2) / 2;
			double y = m_patchTeam[robot_i].Center.y + (j - height / 2) / 2;

			x = (int)x;
			y = (int)y;

			COLORREF color = m_pImageGrabber->GetColorFloat(x, y, m_cameraID);

			pDC->SetPixel(i, j, color);
		}
	}
}

void CVisionCoreDiagonalPatch::SetSelectRobotPosition(CPoint point)
{
	m_SelectRobotPosition = point;
}

CPointDouble CVisionCoreDiagonalPatch::GetSelectRobotPosition()
{
	return m_SelectRobotPosition;
}

void CVisionCoreDiagonalPatch::Display_TeamAssistantDistance(CDC* pDC, COLORREF color)
{
	unsigned char mask_ass[2];
	mask_ass[0] = VISION_PATCH_MASK_1;
	mask_ass[1] = VISION_PATCH_MASK_2;

	const int ASS_DIVIDE_K = 16;

	for (int i = 0; i < (int)m_patchTeam.size(); i++)
	{
		double cx = m_patchTeam[i].realCenter.x;
		double cy = m_patchTeam[i].realCenter.y;

		for (double a = 0; a < 2 * M_PI; a += M_PI / ASS_DIVIDE_K)
		{
			double px2 = cx + m_valueTeamAssistantDistance * 2 * cos(a);
			double py2 = cy + m_valueTeamAssistantDistance * 2 * sin(a);

			m_pGround->GroundToScreen(px2, py2);
			m_pRevision->ScreenToFlat(px2, py2);
			m_pRevision->FlatToVision(px2, py2);


			double px = cx + m_valueTeamAssistantDistance * cos(a);
			double py = cy + m_valueTeamAssistantDistance * sin(a);

			m_pGround->GroundToScreen(px, py);
			m_pRevision->ScreenToFlat(px, py);
			m_pRevision->FlatToVision(px, py);

			COLORREF pcolor = m_pImageGrabber->GetColorFloat(px, py, m_cameraID);
			unsigned char patchLUTData = m_pLookUpTable->GetLUTData(GetRValue(pcolor),
				GetGValue(pcolor),
				GetBValue(pcolor));

			pDC->SetPixel((int)px, (int)py, color);

			if (patchLUTData & mask_ass[0])
			{
				pDC->SetPixel((int)px2, (int)py2, RGB(0, 255, 0));
			}

			if (patchLUTData & mask_ass[1])
			{
				pDC->SetPixel((int)px2, (int)py2, RGB(255, 255, 255));
			}
		}
	}
}

void CVisionCoreDiagonalPatch::Display_AssistantPart(int ass_id, CDC* pDC, COLORREF color)
{
	for (int p = 0; p < (int)m_patchAssistant[ass_id].size(); p++)
	{
		for (int pixel = 0; pixel < (int)m_patchAssistant[ass_id][p].pixels.size(); pixel++)
		{
			int x = m_patchAssistant[ass_id][p].pixels[pixel].x;
			int y = m_patchAssistant[ass_id][p].pixels[pixel].y;

			pDC->SetPixel(x, y, color);
		}

		pDC->SetPixel((int)m_patchAssistant[ass_id][p].Center.x, (int)m_patchAssistant[ass_id][p].Center.y, RGB(255, 0, 0));

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(color);
		CString tmp;
		tmp.Format(_T("%d"), (int)m_patchAssistant[ass_id][p].pixels.size());
		pDC->TextOut((int)m_patchAssistant[ass_id][p].Center.x, (int)m_patchAssistant[ass_id][p].Center.y + 10, tmp);
	}
}

void CVisionCoreDiagonalPatch::Display_SegmentImage(CDC* pDC, int width, int height, BOOL bInverse, BOOL bAntiBlack, BOOL bTeamColorOnly, COLORREF segcolor, COLORREF anitcolor, BOOL bMask, COLORREF maskcolor, BOOL bBackgound, COLORREF bgcolor, int select_seg_id)
// Function to display the close up patch image
{
	bool bInverseOrientation = (bInverse == TRUE);

	unsigned char mask_team, mask_id[3];
	mask_team = VISION_PATCH_MASK_4;
	mask_id[0] = VISION_PATCH_MASK_1;
	mask_id[1] = VISION_PATCH_MASK_2;
	mask_id[2] = VISION_PATCH_MASK_3;

	int team_patch_i = -1;

	{
		double min_distance = 15;

		for (int i = 0; i < (int)m_patchTeam.size(); i++)
		{
			if (team_patch_i < 0 || (m_patchTeam[i].Center - m_SelectRobotPosition).Distance() < min_distance)
			{
				team_patch_i = i;
			}
		}
	}

	if (team_patch_i < 0 || team_patch_i >= (int)m_patchTeam.size()) return;
	if (m_pRevision == NULL) return;

	int segment_i = -1;
	for (int i = 0; i < (int)m_vecSegmentCount.size(); i++)
	{
		if (m_vecSegmentCount[i].team_patch_id == team_patch_i)
		{
			if (bInverseOrientation == m_vecSegmentCount[i].bInverseOrientation)
				segment_i = i;
		}
	}

	if (segment_i < 0)
		return;

	double rad = -m_vecSegmentCount[segment_i].orientation_screen - M_PI / 2;

	double cosTheta = cos(rad);
	double sinTheta = sin(rad);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			//			double x = (i-width/2)/2;
			//			double y = (j-height/2)/2;

			double x, y;

			x = (i - width / 2) / 1000.0;
			y = -(j - height / 2) / 1000.0;

			//			double px = m_Team.patch[team_patch_i].Center.x + cosTheta*x - sinTheta*y;
			//			double py = m_Team.patch[team_patch_i].Center.y + sinTheta*x + cosTheta*y;
			double px = m_patchTeam[team_patch_i].realCenter.x + cosTheta * x - sinTheta * y;
			double py = m_patchTeam[team_patch_i].realCenter.y + sinTheta * x + cosTheta * y;


			m_pGround->GroundToScreen(px, py);
			m_pRevision->ScreenToFlat(px, py);
			m_pRevision->FlatToVision(px, py);

			COLORREF color = m_pImageGrabber->GetColorFloat(px, py, m_cameraID);

			if (bBackgound)
				pDC->SetPixel(i, j, bgcolor);
			else
			{
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				unsigned char patchLUTData = m_pLookUpTable->GetLUTData(r, g, b);

				if (bTeamColorOnly)
				{
					if (!(patchLUTData & mask_team))
						pDC->SetPixel(i, j, anitcolor);
					else
						pDC->SetPixel(i, j, color);
				}
				else
					if (bAntiBlack)
					{
						if (patchLUTData)
							pDC->SetPixel(i, j, anitcolor);
						else
							pDC->SetPixel(i, j, color);
					}
					else
					{
						pDC->SetPixel(i, j, color);
					}
			}
		}
	}


	CPoint text_pos[4];
	text_pos[0] = CPoint(0, 0);
	text_pos[1] = CPoint(0, 0);
	text_pos[2] = CPoint(0, 0);
	text_pos[3] = CPoint(0, 0);


	for (int s = 0; s < 2; s++)
	{
		double px = m_patchTeam[team_patch_i].realCenter.x + m_SegmentPosition[s].x / 100.0;
		double py = m_patchTeam[team_patch_i].realCenter.y + m_SegmentPosition[s].y / 100.0;

		m_pGround->GroundToScreen(px, py);
		m_pRevision->ScreenToFlat(px, py);
		m_pRevision->FlatToVision(px, py);


		int dc_x = (int)(m_SegmentPosition[s].x * 10 + width / 2);
		int dc_y = (int)(-m_SegmentPosition[s].y * 10 + height / 2);

		{
			// Printing the Segment Count on each segment
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(segcolor);
			CString tmp;
			tmp.Format(_T("%d"), m_vecSegmentCount[segment_i].count[s]);
			pDC->TextOut(dc_x + text_pos[s].x + m_valueSegmentCheckDistance, dc_y + text_pos[s].y + m_valueSegmentCheckDistance, tmp);
		}


		COLORREF color;

		if (bMask)
			color = maskcolor;
		else
			color = segcolor;

		pDC->SetPixel(dc_x, dc_y, color);

		CPen pen, * pOldPen;
		pen.CreatePen(PS_SOLID, 1, color);
		pOldPen = (CPen*)pDC->SelectObject(&pen);
		pDC->SelectStockObject(NULL_BRUSH);

		pDC->Rectangle(dc_x - m_valueSegmentCheckDistance,
			dc_y - m_valueSegmentCheckDistance,
			dc_x + m_valueSegmentCheckDistance + 1,
			dc_y + m_valueSegmentCheckDistance + 1);

		pDC->SelectObject(pOldPen);

		if (s == select_seg_id)
		{
			COLORREF color_inv = RGB(255 - GetRValue(color), 255 - GetGValue(color), 255 - GetBValue(color));

			CPen pen, * pOldPen;
			pen.CreatePen(PS_SOLID, 1, color_inv);
			pOldPen = (CPen*)pDC->SelectObject(&pen);
			pDC->SelectStockObject(NULL_BRUSH);

			int k = 2;
			pDC->MoveTo(dc_x - m_valueSegmentCheckDistance * k, dc_y);
			pDC->LineTo(dc_x + m_valueSegmentCheckDistance * k + 1, dc_y);

			pDC->MoveTo(dc_x, dc_y - m_valueSegmentCheckDistance * k);
			pDC->LineTo(dc_x, dc_y + m_valueSegmentCheckDistance * k + 1);

			pDC->SelectObject(pOldPen);
		}
	}

	// Original points used in bar patch
	CPointDouble patch_frame_ground[8];
	patch_frame_ground[0] = CPointDouble(-0.075 / 2, -0.075 / 2); // Bottom Left
	patch_frame_ground[1] = CPointDouble(0.075 / 2, -0.075 / 6); // - Left Line Bottom
	patch_frame_ground[2] = CPointDouble(0.075 / 6, -0.075 / 2); // Right Line Bottom
	patch_frame_ground[3] = CPointDouble(0.075 / 2, -0.075 / 2); // Bottom Right
	patch_frame_ground[4] = CPointDouble(-0.075 / 2, 0.075 / 2); // Top Left
	patch_frame_ground[5] = CPointDouble(-0.075 / 6, 0.075 / 2); // Left Line Top
	patch_frame_ground[6] = CPointDouble(-0.075 / 2, 0.075 / 6); // - Right Line Top
	patch_frame_ground[7] = CPointDouble(0.075 / 2, 0.075 / 2); // Top Right


	CPointDouble patch_frame_dc[8];

	for (int i = 0; i < 8; i++)
	{
		patch_frame_dc[i].x = patch_frame_ground[i].x * 1000.0 + width / 2;
		patch_frame_dc[i].y = -patch_frame_ground[i].y * 1000.0 + height / 2;
	}

	// Points for the frames around team patch
	CPoint Pt[11];
	Pt[0] = patch_frame_dc[4].Integer(); // Top Left
	Pt[1] = patch_frame_dc[5].Integer(); // Left Line Top
	Pt[2] = patch_frame_dc[1].Integer();
	Pt[3] = patch_frame_dc[3].Integer(); // Bottom Right
	Pt[4] = patch_frame_dc[2].Integer(); // Right Line Bottom
	Pt[5] = patch_frame_dc[6].Integer();
	Pt[6] = patch_frame_dc[0].Integer();
	Pt[7] = patch_frame_dc[3].Integer();
	Pt[8] = patch_frame_dc[7].Integer();
	Pt[9] = patch_frame_dc[4].Integer();
	Pt[10] = patch_frame_dc[6].Integer();
	
	// Drawing the frame
	pDC->Polygon(Pt, 11);
}


void CVisionCoreDiagonalPatch::CopyData(CVisionCoreDiagonalPatch& vision)
{
	// UI는 Set으로 draw -> process 으로 전달만 함.

	//m_SelectRobotPosition = vision.m_SelectRobotPosition;

	m_valueAssistantMin = vision.m_valueAssistantMin;
	m_valueAssistantMax = vision.m_valueAssistantMax;
	m_valueSegmentThreshold = vision.m_valueSegmentThreshold;
	m_valueSegmentCheckDistance = vision.m_valueSegmentCheckDistance;
	m_valueTeamAssistantDistance = vision.m_valueTeamAssistantDistance;


	m_vecSegmentCount = vision.m_vecSegmentCount;

	CVisionCore::CopyData(vision);
}

void CVisionCoreDiagonalPatch::Draw_TeamIDDistance(CDC* pDC, COLORREF color)
{
	unsigned char mask_id[3];
	mask_id[0] = VISION_PATCH_MASK_1;
	mask_id[1] = VISION_PATCH_MASK_2;
	mask_id[2] = VISION_PATCH_MASK_3;

	const int ASS_DIVIDE_K = 16;

	for (int i = 0; i < (int)m_patchTeam.size(); i++)
	{
		double cx = m_patchTeam[i].realCenter.x;
		double cy = m_patchTeam[i].realCenter.y;

		for (double a = 0; a < 2 * M_PI; a += M_PI / ASS_DIVIDE_K)
		{
			double px2 = cx + m_valueTeamIDDistance * 2 * cos(a);
			double py2 = cy + m_valueTeamIDDistance * 2 * sin(a);

			m_pGround->GroundToScreen(px2, py2);
			m_pRevision->ScreenToFlat(px2, py2);
			m_pRevision->FlatToVision(px2, py2);


			double px = cx + m_valueTeamIDDistance * cos(a);
			double py = cy + m_valueTeamIDDistance * sin(a);

			m_pGround->GroundToScreen(px, py);
			m_pRevision->ScreenToFlat(px, py);
			m_pRevision->FlatToVision(px, py);

			COLORREF pcolor = m_pImageGrabber->GetColorFloat(px, py, m_cameraID);
			unsigned char patchLUTData = m_pLookUpTable->GetLUTData(GetRValue(pcolor),
				GetGValue(pcolor),
				GetBValue(pcolor));

			pDC->SetPixel((int)px, (int)py, color);

			if (patchLUTData & mask_id[0])
			{
				pDC->SetPixel((int)px2, (int)py2, m_pLookUpTable->GetColor(1));
			}

			if (patchLUTData & mask_id[1])
			{
				pDC->SetPixel((int)px2, (int)py2, m_pLookUpTable->GetColor(2));
			}

			if (patchLUTData & mask_id[2])
			{
				pDC->SetPixel((int)px2, (int)py2, m_pLookUpTable->GetColor(3));
			}
		}
	}
}
