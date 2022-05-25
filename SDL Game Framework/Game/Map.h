#pragma once

#include "stdafx.h"
#include "Framework.h"

#define MAX_PLATFORM_COUNT 3
#define CSV_FILE ""

//�÷��� ��Ʈ��Ʈ(���� ����/�߰� ����)
typedef struct tagPlatform 
{
	//�⺻ ����
	Image		Image;		//�÷��� �̹��� 
	Position	Position; //�÷��� ��ġ
	int32		Width;		//�÷��� �̹����� ���� ��
	int32		Height;		//�÷��� �̹����� ���� ��
} Platform;

//�⺻���� �ʿ� ���� ��Ʈ��Ʈ(���� ����/�߰� ����)
typedef struct tagMap 
{

	//���
	Image BackGroundImage;
	Music BGM;

	//��(�÷���)
	Platform PlatformList[MAX_PLATFORM_COUNT];

} Map;

void Map_Init(Map* map, int32 StageNum);

void Map_Update(Map* map);

void Map_Render(Map* map);

void Map_Release(Map* map);
