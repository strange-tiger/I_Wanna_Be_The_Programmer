#pragma once

#include "stdafx.h"
#include "Framework.h"
#include "Player.h"
#include "Trap.h"

//최대 플랫폼 개수
#define MAX_PLATFORM_COUNT 3
#define MAX_TRAP_COUNT 1
#define MAX_SAVE_POINT_COUNT 1

#define PLATFORM_MOVE_SPEED 1
#define PLATFORM_MOVE_CYCLE 3.0f

//플랫폼 스트럭트(추후 수정/추가 예정)
typedef struct tagPlatform
{
	//기본 연산
	Image		Image;				//플랫폼 이미지 
	Position	Position;			//플랫폼 위치
	int32		Width;				//플랫폼 이미지의 가로 값
	int32		Height;				//플랫폼 이미지의 세로 값
	RECT		Rect;				//플랫폼 충돌 처리 범위

	bool		Direction;			//플랫폼 이동 방향
	int32		Move;				//플랫폼이 움직이는가 : 0: 아니오 1: 가로 2: 세로
} Platform;

typedef struct SavePoint
{
	Platform	Platform;			//플랫폼의 일종
	bool		Active;				//플레이어가 세이브 포인트를 지났는가/활성화했는가
} SavePoint;

//기본적인 맵에 대한 스트럭트(추후 수정/추가 예정)
typedef struct tagMap
{
	//배경
	Image		BackGroundImage;	//배경화면
	Music		BGM;				//배경 음악
	Music		DieBGM;				//죽었을 때 음악

	//맵(플랫폼)
	Platform	PlatformList[MAX_PLATFORM_COUNT];
	//맵(함정)
	Trap		TrapList[MAX_TRAP_COUNT];
	
	Position	StartPoint;			//시작 좌표
	Position	DestinationPoint;	//목적 좌표

	Position	RespawnPoint;		//리스폰 지점 좌표
	//세이브 포인트 (좌표/활성화 여부)
	SavePoint	SavePointList[MAX_SAVE_POINT_COUNT];

	float		ActiveTime;			//이벤트 델타타임 적용
} Map;


//####기본 함수
void Map_Init(Map* map);

void Map_Update(Map* map);

void Map_Render(Map* map);

void Map_Release(Map* map);

//####추가 함수

/// <summary>
/// 플랫폼의 위에 Player가 있는지 판별한다.
/// </summary>
/// <returns>
/// 플레이어가 플랫폼 좌우로 걸치는 범위 안, 플랫폼 바로 위에 있다면 true, 아니면 false
/// </returns>
bool Platform_DetectIsGround(Platform* platform, Player* player);

/// <summary>
/// 플랫폼을 주기에 따라 가로로 반복하여 움직인다.
/// </summary>
void Platform_PlatformHorizontalMove(Map* map, Platform* platform);

/// <summary>
/// 플랫폼을 주기에 따라 세로로 반복하여 움직인다.
/// </summary>
void Platform_PlatformVerticalMove(Map* map, Platform* platform);

/// <summary>
/// 맵의 세이브 포인트를 검사한다.
/// </summary>
/// <returns>세이브 포인트의 좌표값 int32 배열</returns>
void Map_DetectSavePoint(Map* map, Player* player);