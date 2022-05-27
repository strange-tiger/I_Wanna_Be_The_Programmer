#include "stdafx.h"
#include "Framework.h"
#include "Player.h"
#include "Animation.h"

//#### 기본 함수
void Player_Init(Player* player, SoundEffect* dieSound) 
{
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
	player->dieSound = dieSound;

	//에니메이션
	Animation_Init(&player->animation);
}

void Player_Update(Player* player, Map* map)
{
	//기본 이동 및 점프 처리
	Player_Move(player, map);
	Player_Jump(player, map);
	Player_StayStill(player);

	//애니메이션 업데이트
	Aniamtion_Update(player);
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

//완
void Player_Move(Player* player, Map* map)
{
	//플레이어가 움직일 수 있다면
	if (Player_IsMovable(player, map))
	{
		//입력을 받아 이동
		if (Input_GetKey(VK_LEFT))
		{
			// 걷는 상태로 전환, 방향 결정
			player->state = PLAYER_MOVE;
			player->direction = PLAYER_LEFT;

			//이동 연산
			player->position.X -= PLAYER_WALK_SPEED * Timer_GetDeltaTime();
		}

		if (Input_GetKey(VK_RIGHT))
		{
			// 걷는 상태로 전환, 방향 결정
			player->state = PLAYER_MOVE;
			player->direction = PLAYER_RIGHT;

			//이동 연산
			player->position.X += PLAYER_WALK_SPEED * Timer_GetDeltaTime();
		}
	}

}

//
void Player_Jump(Player* player, Map* map)
{
	
}

//
bool Player_IsMovable(Player* player, Map* map)
{

}

//
bool Player_IsHitTrap(Player* player, Map* map)
{

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

	player->state = PLAYER_MOVE;
}

//완
void Player_Die(Player* player)
{
	player->isPlayerDie = true;
}

//완
bool Player_isDead(Player* player)
{
	return player->isPlayerDie;
}
