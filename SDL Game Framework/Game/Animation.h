#pragma once

#include "Type.h"
#include "Framework.h"
#include "stdafx.h"

#define PLAYER_DIRECTION_TYPE 2		//���� ����
#define PLAYER_IDE_PIC_COUNT 2		//������ �� �̹��� ����
#define PLAYER_MOVE_PIC_COUNT 8		//������ �� �̹��� ����
#define PLAYER_DEATH_PIC_COUNT 9	//�׾��� �� �̹��� ����

typedef struct tagAnimation{
	int32 picCount;					//���� ���� ��ȣ
	float animSpeed;				//���� �ѱ�� �ӵ�
	float elapsedTime;				//���� �ð�
	bool isLoop;					//����

	//�÷��̾��� ��� �̹���
	Image playerIdleImages[PLAYER_DIRECTION_TYPE][PLAYER_IDE_PIC_COUNT];
	//�÷��̾��� �̵� �̹���
	Image playerMoveImages[PLAYER_DIRECTION_TYPE][PLAYER_MOVE_PIC_COUNT];
	//�÷��̾��� ��� �̹���
	Image playerDEATHImages[PLAYER_DEATH_PIC_COUNT];

	Image* showImage;	//ȭ�鿡 ���� �̹���
} Animation;

static int32 prevState = -1;

void Animation_Init(Animation* animation);

void Aniamtion_Update(struct Player* player);

void Animation_Render(Animation* animation, Position* position);

void Animation_Release(Animation* animation);