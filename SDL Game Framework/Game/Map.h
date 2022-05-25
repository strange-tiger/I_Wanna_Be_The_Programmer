#pragma once

#include "stdafx.h"
#include "Framework.h"
#include "Trap.h"

//�ִ� �÷��� ����
#define MAX_PLATFORM_COUNT 3
#define MAX_TRAP_COUNT 1

//�÷��� ��Ʈ��Ʈ(���� ����/�߰� ����)
typedef struct tagPlatform
{
	//�⺻ ����
	Image		Image;			//�÷��� �̹��� 
	Position	Position;		//�÷��� ��ġ
	int32		Width;			//�÷��� �̹����� ���� ��
	int32		Height;			//�÷��� �̹����� ���� ��
	RECT		Rect;			//�÷��� �浹 ó�� ����

	float		ActiveTime;		//�÷��� �̺�Ʈ ��ŸŸ�� ����

} Platform;

//�⺻���� �ʿ� ���� ��Ʈ��Ʈ(���� ����/�߰� ����)
typedef struct tagMap
{

	//���
	Image	BackGroundImage;	//���ȭ��
	Music	BGM;				//��� ����
	Music	DieBGM;				//�׾��� �� ����

	//��(�÷���)
	Platform	PlatformList[MAX_PLATFORM_COUNT];
	Trap		TrapList[MAX_TRAP_COUNT];

} Map;

//####�⺻ �Լ�
void Map_Init(Map* map);

void Map_Update(Map* map);

void Map_Render(Map* map);

void Map_Release(Map* map);

//####�߰� �Լ�