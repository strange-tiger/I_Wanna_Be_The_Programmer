#pragma once

#include "stdafx.h"
#include "Framework.h"
#include "Player.h"
#include "Map.h"

#define TRAP_SWITCH_CYCLE 1.0f

//함정 종류
enum Trap_Type {
	TRAP_BASIC,
	TRAP_FLYING,
	TRAP_TRACK,
	TRAP_SWITCH
};

//함정 스트럭트(추후 수정/추가 예정)
typedef struct tagTrap
{
	//기본
	Platform	Platform;		//함정도 플랫폼의 한 종류

	//효과
	enum Trap_Type	Type;		//함정 타입
	bool		Active;
	float		ActiveTime;
	int32		Speed;


	//날아오는/추적 함정에서 쓰일 목표 지점
	Position	TargetPosition;	//목표 지점 좌표값

	//스위칭 함정용
	int32		ImageAlpha;		//투명화
	Image		Image2;			//(파랑/빨강) 바꿀 이미지

	//효과음
	SoundEffect	effectSound;	//날아오는 등의 효과에서 나오는 효과음
} Trap;

//####추가 함수

/// <summary>
/// 함정을 TargetPosition까지 움직인다.
/// </summary>
void Trap_TrapMove(Trap* trap, Player* player, int32 x, int32 y);

/// <summary>
/// 목표물의 위치 TargetPosition 값을 받는다.
/// </summary>
void Trap_GetTargetPosition(Trap* trap, Player* player, int32 x, int32 y);

/// <summary>
/// 스위치 함정을 주기에 따라 깜박인다.
/// </summary>
void Trap_TrapSwitch(Trap* trap);
