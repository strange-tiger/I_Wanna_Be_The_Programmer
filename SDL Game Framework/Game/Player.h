#pragma once

#include "Framework.h";
#include "Map.h"

#define PLAYER_WALK_SPEED 15		//플레이어 이동 속도
#define PLAYER_JUMP_SPEED -35		//플레이어 점프 속도(위쪽이 -라)
#define PLAYER_MAX_JUMPING_COUNT 2	//플레이어 점프 카운트
#define	PLAYER_IMAGE_COUNT 5
#define PLAYER_MAX_LIFE_TIME 4.5f

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
	enum Player_State		state;		//플레이어 이동 상태
	enum Player_Direction	direction;	//플레이어 이동 방향

	//위치 관련
	Position			position;	//플레이어 좌표 값

	//점프 관련
	bool				isJumpting;	//점프 중인지
	int32				currentJumpingCount;//현재 점프 카운트

	//게임 종료 관련
	bool				isPlayerDie; //플레이어 사망 했는지
	float				elapsedTime; //플레이어가 가만히 있던 시간 모음

	//효과음
	SoundEffect			dieSound;	//사망시 효과음 

	//플레이어 이미지
	Image				images[PLAYER_IMAGE_COUNT]; //플레이어 이미지

} Player;

//#### 기본 함수
void Player_Init(Player* player);

void Player_Update(Player* player);

//나중에 다른 파일로 뺄 수도... 고민중
void Player_Render(Player* player);

void Player_Release(Player* player);


//#### 추가 함수(추가 예정)

/// <summary>
/// 플레이어가 움직일 수 있는지
/// </summary>
void Player_SetPosition(Player* player, const Position newPosition);

/// <summary>
/// 플레이어 좌표 값 반환
/// </summary>
Position Player_GetPosition(Player* player);

/// <summary>
/// 플레이어 좌표 값 반환
/// </summary>
int32 Player_GetDirection(Player* player);

/// <summary>
/// 플레이어의 이동
/// </summary>
void Player_Move(Player* player, Platform* platforms);

/// <summary>
/// 플레이어의 점프 연산
/// </summary>
void Player_Jump(Player* player, Trap* traps);

/// <summary>
/// 플레이어가 움직일 수 있는지
/// </summary>
/// <param name="platforms">맵의 플랫폼 배열</param>
bool Player_IsMovable(Player* player, Platform* platforms);

/// <summary>
/// 플레이어가 죽었는지
/// </summary>
/// <param name="traps">맵의 함정 배열</param>
bool Player_IsHitTrap(Player* player, Trap* traps);

/// <summary>
/// 플레이어가 가만히 있는지에 대한 처리
/// </summary>
void Player_StayStill(Player* player);

/// <summary>
/// 플레이어죽음
/// </summary>
/// <param name="platforms">맵의 플랫폼 배열</param>
void Player_Die(Player* player);

/// <summary>
/// 플레이어죽음
/// </summary>
/// <param name="platforms">맵의 플랫폼 배열</param>
bool Player_isDead(Player* player);

