#pragma once

#include "stdafx.h"
#include "Framework.h"
#include "Trap.h"

//�ִ� �÷��� ����
#define MAX_PLATFORM_COUNT 3
#define MAX_TRAP_COUNT 1

#define PLATFORM_MOVE_SPEED 1
#define PLATFORM_MOVE_CYCLE 3.0f

//�÷��� ��Ʈ��Ʈ(���� ����/�߰� ����)
typedef struct tagPlatform
{
	//�⺻ ����
	Image		Image;			//�÷��� �̹��� 
	Position	Position;		//�÷��� ��ġ
	int32		Width;			//�÷��� �̹����� ���� ��
	int32		Height;			//�÷��� �̹����� ���� ��
	RECT		Rect;			//�÷��� �浹 ó�� ����

} Platform;

//�⺻���� �ʿ� ���� ��Ʈ��Ʈ(���� ����/�߰� ����)
typedef struct tagMap
{
	//���
	Image		BackGroundImage;	//���ȭ��
	Music		BGM;				//��� ����
	Music		DieBGM;				//�׾��� �� ����

	

	//��(�÷���)
	Platform	PlatformList[MAX_PLATFORM_COUNT];
	Trap		TrapList[MAX_TRAP_COUNT];
	
	Position	StartPoint;
	Position	DestinationPoint;

	float		ActiveTime;		//�̺�Ʈ ��ŸŸ�� ����

} Map;

//####�⺻ �Լ�
void Map_Init(Map* map);

void Map_Update(Map* map);

void Map_Render(Map* map);

void Map_Release(Map* map);

//####�߰� �Լ�

/// <summary>
/// �÷����� ���� Player�� �ִ��� �Ǻ��Ѵ�?
/// </summary>
bool Map_DetectIsGround(Map* map);

/// <summary>
/// �÷����� �ֱ⿡ ���� ���η� �ݺ��Ͽ� �����δ�.
/// </summary>
void Map_PlatformHorizontalMove(Map* map, int32 platformNum);

/// <summary>
/// �÷����� �ֱ⿡ ���� ���η� �ݺ��Ͽ� �����δ�.
/// </summary>
void Map_PlatformVerticalMove(Map* map, int32 platformNum);

/// <summary>
/// ���� ���̺� ����Ʈ�� �˻��Ѵ�.
/// </summary>
/// <returns>���̺� ����Ʈ�� ��ǥ�� int32 �迭</returns>
int32* Map_DetectSavePoint(Map* map);

