#pragma once

#include "stdafx.h"
#include "Framework.h"
#include "Trap.h"

//최대 플랫폼 개수
#define MAX_PLATFORM_COUNT 3
#define MAX_TRAP_COUNT 1

//플랫폼 스트럭트(추후 수정/추가 예정)
typedef struct tagPlatform
{
	//기본 연산
	Image		Image;			//플랫폼 이미지 
	Position	Position;		//플랫폼 위치
	int32		Width;			//플랫폼 이미지의 가로 값
	int32		Height;			//플랫폼 이미지의 세로 값
	RECT		Rect;			//플랫폼 충돌 처리 범위

	float		ActiveTime;		//플랫폼 이벤트 델타타임 적용

} Platform;

//기본적인 맵에 대한 스트럭트(추후 수정/추가 예정)
typedef struct tagMap
{

	//배경
	Image	BackGroundImage;	//배경화면
	Music	BGM;				//배경 음악
	Music	DieBGM;				//죽었을 때 음악

	//맵(플랫폼)
	Platform	PlatformList[MAX_PLATFORM_COUNT];
	Trap		TrapList[MAX_TRAP_COUNT];

} Map;

//####기본 함수
void Map_Init(Map* map);

void Map_Update(Map* map);

void Map_Render(Map* map);

void Map_Release(Map* map);

//####추가 함수