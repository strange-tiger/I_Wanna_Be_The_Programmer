#pragma once

#include "Type.h"
#include "Framework.h"
#include "stdafx.h"

#define PLAYER_DIRECTION_TYPE 2		//방향 개수
#define PLAYER_IDE_PIC_COUNT 2		//멈췄을 때 이미지 개수
#define PLAYER_MOVE_PIC_COUNT 8		//움직일 때 이미지 개수
#define PLAYER_DEATH_PIC_COUNT 9	//죽었을 때 이미지 개수

typedef struct tagAnimation{
	int32 picCount;			//현재 사진 번호
	float animSpeed;		//사진 넘기는 속도
	float elapsedTime;		//누적 시간(위에서 사용)
	bool isLoop;			//에니메이션이 계속 돌아가는지

	//플레이어의 평소 이미지
	Image playerIdleImages[PLAYER_DIRECTION_TYPE][PLAYER_IDE_PIC_COUNT];
	//플레이어의 이동 이미지
	Image playerMoveImages[PLAYER_DIRECTION_TYPE][PLAYER_MOVE_PIC_COUNT];
	//플레이어의 사망 이미지
	Image playerDEATHImages[PLAYER_DEATH_PIC_COUNT];

	Image* showImage;		//화면에 보일 이미지
} Animation;

//이전 상태
static int32 prevState = -1;

void Animation_Init(Animation* animation);

void Aniamtion_Update(struct Player* player);

void Animation_Render(Animation* animation, Position* position);

void Animation_Release(Animation* animation);