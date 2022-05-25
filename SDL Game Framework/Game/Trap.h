#pragma once

#include "Type.h"
#include "Framework.h"
#include "stdafx.h"

//함정 종류
typedef enum Trap_Type {
	TRAP_BASIC,
	TRAP_FLYING,
	TRAP_TRACK,
	TRAP_SWITCH
} Trap_Type;

//함정 스트럭트(추후 수정/추가 예정)
typedef struct tagTrap
{
	//기본
	Image		TrapImage;		//함정 이미지
	Position	TrapPosition;	//함정 위치
	int32		Width;		//함정 이미지의 가로 값
	int32		Height;		//함정 이미지의 세로 값

	//효과
	Trap_Type	Type;	//함정 타입
	
	//날아오는/추적 함정에서 쓰일 목표 지점
	Position	TargetPosition;	//목표 지점 좌표값

	//스위칭 함정용
	int32		ImageAlpha;		//투명화
	Image		Image2;			//(파랑/빨강) 바꿀 이미지

} Trap;

//####추가 함수