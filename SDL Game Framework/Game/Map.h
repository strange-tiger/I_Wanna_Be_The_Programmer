#pragma once

#include "stdafx.h"
#include "Framework.h"

#define MAX_PLATFORM_COUNT 3
#define CSV_FILE ""

//플랫폼 스트럭트(추후 수정/추가 예정)
typedef struct tagPlatform 
{
	//기본 연산
	Image		Image;		//플랫폼 이미지 
	Position	Position; //플랫폼 위치
	int32		Width;		//플랫폼 이미지의 가로 값
	int32		Height;		//플랫폼 이미지의 세로 값
} Platform;

//기본적인 맵에 대한 스트럭트(추후 수정/추가 예정)
typedef struct tagMap 
{

	//배경
	Image BackGroundImage;
	Music BGM;

	//맵(플랫폼)
	Platform PlatformList[MAX_PLATFORM_COUNT];

} Map;

void Map_Init(Map* map, int32 StageNum);

void Map_Update(Map* map);

void Map_Render(Map* map);

void Map_Release(Map* map);
