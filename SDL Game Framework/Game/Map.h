#pragma once

#include "stdafx.h"
#include "Framework.h"
#include "Player.h"
#include "Trap.h"

//�ִ� �÷��� ����
#define MAX_PLATFORM_COUNT 3
#define MAX_TRAP_COUNT 1
#define MAX_SAVE_POINT_COUNT 1
#define MAX_SWITCH_COUNT 1

#define PLATFORM_MOVE_SPEED 1
#define PLATFORM_MOVE_CYCLE 3.0f

//�÷��� ��Ʈ��Ʈ(���� ����/�߰� ����)
typedef struct tagPlatform
{
	//�⺻ ����
	Image		Image;				//�÷��� �̹��� 
	Position	Position;			//�÷��� ��ġ
	int32		Width;				//�÷��� �̹����� ���� ��
	int32		Height;				//�÷��� �̹����� ���� ��
	RECT		Rect;				//�÷��� �浹 ó�� ����

	bool		DirectionForCycle;		//�÷��� �̵� �ֱ� ������ ����
	int32		MoveState;				//�÷����� �����̴°� : 0: �ƴϿ� 1: ���� 2: ����
} Platform;

typedef struct tagSavePoint
{
	Platform	Platform;			//�÷����� ����
	bool		Active;				//�÷��̾ ���̺� ����Ʈ�� �����°�/Ȱ��ȭ�ߴ°�
} SavePoint;

typedef struct tagSwitch
{
	Platform	Platform;			//�÷����� ����
	bool		Active;				//�÷��̾ ����ġ�� �����°�/Ȱ��ȭ�ߴ°�
	void(*Event);					//����ġ�� ����� �̺�Ʈ
} Switch;

//�⺻���� �ʿ� ���� ��Ʈ��Ʈ(���� ����/�߰� ����)
typedef struct tagMap
{
	//ID
	int32		ID;					//�ĺ� ��

	//���
	Image		BackGroundImage;	//���ȭ��
	Music		BGM;				//��� ����
	Music		DieBGM;				//�׾��� �� ����

	//��(�÷���)
	Platform	PlatformList[MAX_PLATFORM_COUNT];
	//��(����)
	Trap		TrapList[MAX_TRAP_COUNT];
	//���̺� ����Ʈ (��ǥ/Ȱ��ȭ ����)
	SavePoint	SavePointList[MAX_SAVE_POINT_COUNT];
	//����ġ (��ǥ/Ȱ��ȭ ����)
	Switch		SwitchList[MAX_SWITCH_COUNT];
	
	Position	StartPoint;			//���� ��ǥ
	Position	DestinationPoint;	//���� ��ǥ
	Switch		Radder;				//���� ���������� ��ٸ� �̺�Ʈ/�ִϸ��̼�

	Position	RespawnPoint;		//������ ���� ��ǥ

	float		ActiveTime;			//�̺�Ʈ ��ŸŸ�� ����
} Map;


//####�⺻ �Լ�
void Map_Init(Map* map);

void Map_Update(Map* map);

void Map_Render(Map* map);

void Map_Release(Map* map);

//####�߰� �Լ�

/// <summary>
/// �÷����� ���� Player�� �ִ��� �Ǻ��Ѵ�.
/// </summary>
/// <returns>
/// �÷��̾ �÷��� �¿�� ��ġ�� ���� ��, �÷��� �ٷ� ���� �ִٸ� true, �ƴϸ� false
/// </returns>
bool Platform_GetIsGround(Platform* platform, Player* player);

/// <summary>
/// �÷����� ���� Player�� �ִ��� �Ǻ��ϰ� �����Ѵ�.
/// </summary>
void Platform_SetIsGround(Platform* platform, Player* player);

/// <summary>
/// �÷����� ��Ʈ�� �����Ѵ�.
/// </summary>
void Platform_CreateRect(Platform* platform);

/// <summary>
/// �÷����� �ֱ⿡ ���� ���η� �ݺ��Ͽ� �����δ�.
/// </summary>
void Platform_PlatformHorizontalMove(Map* map, Platform* platform);

/// <summary>
/// �÷����� �ֱ⿡ ���� ���η� �ݺ��Ͽ� �����δ�.
/// </summary>
void Platform_PlatformVerticalMove(Map* map, Platform* platform);

/// <summary>
/// ���� ��� �÷����� �ֱ⿡ ���� �����δ�.
/// </summary>
void Map_PlatformMove(Map* map);

/// <summary>
/// ���� ���̺� ����Ʈ�� �˻��Ѵ�.
/// </summary>
void Map_DetectSavePoint(Map* map, Player* player);

/// <summary>
/// ���� ������ �ֱ⿡ ���� �۵���Ų��.
/// </summary>
void Map_TrapActivate(Map* map, Player* player);

/// <summary>
/// ���� ��� �÷��� ���� �÷��̾ �ִ��� �Ǻ��Ѵ�.
/// </summary>
void Map_PlatformIsGround(Map* map, Player* player);

/// <summary>
/// ���� ������Ʈ �Ѵ�. �÷��̾�� ������ �ִ� ������ ������Ʈ�Ѵ�.
/// </summary>
void Map_UpdateWithPlayer(Map* map, Player* player);