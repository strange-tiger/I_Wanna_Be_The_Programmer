#include "stdafx.h"
#include "Framework.h"
#include "Player.h"
#include "Animation.h"
#include "Map.h"

//#### 기본 함수
void Player_Init(Player* player) // , SoundEffect* dieSound) << SE는 바로 넣어줘도 되지 않을까 합니다.
{
	//범위
	player->Rect.left = player->position.X;
	player->Rect.top = player->position.Y;
	player->Rect.right = player->position.X + player->animation.playerIdleImages[0][0].Width;
	player->Rect.bottom = player->position.Y + player->animation.playerIdleImages[0][0].Height;

	//기본 상태 설정
	player->state = PLAYER_IDLE;
	player->direction = PLAYER_RIGHT;

	//점프
	player->isJumping = false;
	player->currentJumpingCount = PLAYER_MAX_JUMPING_COUNT;

	//죽는 판정
	player->isPlayerDie = false;
	player->elapsedTime = 0.0f;

	//효과음
	// player->dieSound = dieSound;
	Audio_LoadSoundEffect(&player->dieSound,"");
	Audio_SetEffectVolume(&player->dieSound, 1.0f); // SE 크기 설정이 필요하면 변수로 받으면 될 듯 합니다.

	//에니메이션
	Animation_Init(&player->animation);
}

void Player_Update(Player* player, Map* map)
{
	//기본 이동 및 점프 처리
	Player_Move(player, map);
	Player_Jump(player, map);
	Player_StayStill(player);
	
	//만약 플레이어가 트랩에 부딪치면 플레이어 사망 처리
	if(Player_IsHitTrap(player, map) == true)
	{
		Player_Die(player);
	}
}

void Player_Render(Player* player) 
{
	//에니메이션만 렌더
	Animation_Render(&player->animation, &player->position);
}

void Player_Release(Player* player) 
{
	//플레이어 관련 Release
	Audio_FreeSoundEffect(player->dieSound);

	//에니메이션 Release
	Animation_Release(&player->animation);
}


//#### 추가 함수(추가 예정)
 
#pragma region GetSet
//완
void Player_SetPosition(Player* player, const Position newPosition)
{
	player->position.X = newPosition.X;
	player->position.Y = newPosition.Y;
}

//완
Position Player_GetPosition(Player* player) 
{
	return player->position;
}

//완
int32 Player_GetDirection(Player* player)
{
	return player->direction;
}

//완
int32 Player_GetState(Player* player)
{
	return player->state;
}

//완
void Player_SetState(Player* player, enum Player_State state)
{
	player->state = state;
}

//완
Animation* Player_GetAnimation(Player* player)
{
	return &player->animation;
}
#pragma endregion

#pragma region 
//완
void Player_Move(Player* player, Map* map)
{
	//입력을 받아 이동
	if (Input_GetKey(VK_LEFT))
	{
		// 걷는 상태로 전환, 방향 결정
		player->state = PLAYER_MOVE;
		player->direction = PLAYER_LEFT;

		//이동 연산
		player->addPosition.X = -PLAYER_WALK_SPEED * Timer_GetDeltaTime();	// ?
	}

	if (Input_GetKey(VK_RIGHT))
	{
		// 걷는 상태로 전환, 방향 결정
		player->state = PLAYER_MOVE;
		player->direction = PLAYER_RIGHT;

		//이동 연산
		player->addPosition.X = PLAYER_WALK_SPEED * Timer_GetDeltaTime();	// ?
	}

	//이동 한 만큼 좌표 값 이동
	player->position.X += player->addPosition.X;

	//만약 이동한 결과로 플레이어가 플랫폼과 겹치면 다시 원래로 돌린다.
	if (Player_IsMovable(player, map) == false)
	{
		player->position.X -= player->addPosition.X;
	}
}

//
void Player_Jump(Player* player, Map* map)
{
	//점프 처리 (점프 키를 누른 시간 만큼 올라가고, 때면 떨어진다.)	// ?
	if (Input_GetKey(VK_SPACE))
	{
		//이동 연산
		player->addPosition.X = PLAYER_JUMP_SPEED * Timer_GetDeltaTime();	// ?

		player->position.X += player->addPosition.X;
	}
	else
	{
		if (Player_IsMovable(player, map))		// 낙하할 수 있는 상황 (밑에 플랫폼 없음) 이면	  // ?
		{
			player->position.X -= PLAYER_JUMP_SPEED * Timer_GetDeltaTime();		// 점프 속도와 같은 속도로 낙하 // ?
		}
	}

}

//완
bool Player_IsMovable(Player* player, Map* map)
{
	for (int32 i = 0; i < MAX_PLATFORM_COUNT; i++) 
	{
		if (Platform_GetIsGround(&map->PlatformList[i], player))	// 수정 // ?
		{
			return false;
		}
	}

	return true;
}

//완
bool Player_IsHitTrap(Player* player, Map* map)
{
	RECT tempRect;

	for (int32 i = 0; i < MAX_TRAP_COUNT; i++)
	{
		if (IntersectRect(&tempRect, &player->Rect, &map->TrapList[i].Platform.Rect))	// 수정
		{
			return true;
		}
	}

	return false;
}

//완
void Player_StayStill(Player* player)
{
	if (player->state == PLAYER_IDLE && player->isJumping == false)
	{
		player->elapsedTime += Timer_GetDeltaTime();

		if (player->elapsedTime >= PLAYER_MAX_LIFE_TIME)
		{
			player->elapsedTime = 0;
			Player_Die(player);
		}
	}

	player->state = PLAYER_MOVE;	// ?
}

//완
void Player_Die(Player* player)
{
	player->isPlayerDie = true;
	player->state = PLAYER_DIE;
	Audio_PlaySoundEffect(&player->dieSound, 0);
}

//완
bool Player_isDead(Player* player)
{
	return player->isPlayerDie;
}
