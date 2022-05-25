#pragma once

#include "Framework.h";

#define PLAYER_WALK_SPEED 15		//플레이어 이동 속도
#define PLAYER_JUMP_SPEED -35		//플레이어 점프 속도(위쪽이 -라)
#define PLAYER_MAX_JUMPING_COUNT 2	//플레이어 점프 카운트

//플레이어 이동 상태
enum Player_State 
{
	PLAYER_WALKING,
	PLAYER_STOP
};

//플래이어 이동 방향
enum Player_Direction 
{
	PLAYER_RIGHT,
	PLAYER_LEFT
};

typedef struct tagPlayer 
{

	//이동 관련
	enum Player_State		State;		//플레이어 이동 상태
	enum Player_Direction	Direction;	//플레이어 이동 방향

	//위치 관련
	Position			Position;	//플레이어 좌표 값

	//점프 관련
	bool				isJumpting;	//점프 중인지
	int32				CurrentJumpingCount;//현재 점프 카운트

	//게임 종료 관련
	bool				isPlayerDie; //플레이어 사망 했는지

	//효과음
	SoundEffect			DieSound;	//사망시 효과음

} Player;

//#### 기본 함수
void Player_Init(Player* player);

void Player_Update(Player* player);

//나중에 다른 파일로 뺄 수도... 고민중
void Player_Render(Player* player);

void Map_Release(Player* player);


//#### 추가 함수(추가 예정)
