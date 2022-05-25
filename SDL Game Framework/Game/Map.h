#pragma once

#include "stdafx.h"
#include "Framework.h"
#include "Trap.h"

//최대 플랫폼 개수
#define MAX_PLATFORM_COUNT 3
#define MAX_TRAP_COUNT 1

#define PLATFORM_MOVE_SPEED 1
#define PLATFORM_MOVE_CYCLE 3.0f

//플랫폼 스트럭트(추후 수정/추가 예정)
typedef struct tagPlatform
{
	//기본 연산
	Image		Image;			//플랫폼 이미지 
	Position	Position;		//플랫폼 위치
	int32		Width;			//플랫폼 이미지의 가로 값
	int32		Height;			//플랫폼 이미지의 세로 값
	RECT		Rect;			//플랫폼 충돌 처리 범위

} Platform;

//기본적인 맵에 대한 스트럭트(추후 수정/추가 예정)
typedef struct tagMap
{
	//배경
	Image		BackGroundImage;	//배경화면
	Music		BGM;				//배경 음악
	Music		DieBGM;				//죽었을 때 음악

	

	//맵(플랫폼)
	Platform	PlatformList[MAX_PLATFORM_COUNT];
	Trap		TrapList[MAX_TRAP_COUNT];
	
	Position	StartPoint;
	Position	DestinationPoint;

	float		ActiveTime;		//이벤트 델타타임 적용

} Map;

//####기본 함수
void Map_Init(Map* map);

void Map_Update(Map* map);

void Map_Render(Map* map);

void Map_Release(Map* map);

//####추가 함수

/// <summary>
/// 플랫폼의 위에 Player가 있는지 판별한다?
/// </summary>
bool Map_DetectIsGround(Map* map);

/// <summary>
/// 플랫폼을 주기에 따라 가로로 반복하여 움직인다.
/// </summary>
void Map_PlatformHorizontalMove(Map* map, int32 platformNum);

/// <summary>
/// 플랫폼을 주기에 따라 세로로 반복하여 움직인다.
/// </summary>
void Map_PlatformVerticalMove(Map* map, int32 platformNum);

/// <summary>
/// 맵의 세이브 포인트를 검사한다.
/// </summary>
/// <returns>세이브 포인트의 좌표값 int32 배열</returns>
int32* Map_DetectSavePoint(Map* map);

