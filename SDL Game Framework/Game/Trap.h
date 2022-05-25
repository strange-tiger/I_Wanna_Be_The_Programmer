#pragma once

#include "stdafx.h"
#include "Framework.h"

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
	Image		Image;			//함정 이미지
	Position	Position;		//함정 위치
	int32		Width;			//함정 이미지의 가로 값
	int32		Height;			//함정 이미지의 세로 값
	RECT		Rect;			//함정 충돌 처리 범위

	float		ActiveTime;		//함정 이벤트 델타타임 적용
	//효과
	enum Trap_Type	Type;		//함정 타입

	//날아오는/추적 함정에서 쓰일 목표 지점
	Position	TargetPosition;	//목표 지점 좌표값

	//스위칭 함정용
	int32		ImageAlpha;		//투명화
	Image		Image2;			//(파랑/빨강) 바꿀 이미지

	//효과음
	SoundEffect	effectSound;	//날아오는 등의 효과에서 나오는 효과음
} Trap;

//####추가 함수