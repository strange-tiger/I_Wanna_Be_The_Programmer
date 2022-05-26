#include "stdafx.h"
#include "Player.h"
#include "Framework.h"

//#### 기본 함수
void Player_Init(Player* player) 
{

}

void Player_Update(Player* player) 
{

}

void Player_Render(Player* player) 
{

}

void Player_Release(Player* player) 
{

}


//#### 추가 함수(추가 예정)
void Player_SetPosition(Player* player, const Position newPosition)
{
	player->position.X = newPosition.X;
	player->position.Y = newPosition.Y;
}

Position Player_GetPosition(Player* player) 
{
	return player->position;
}

int32 Player_GetDirection(Player* player)
{
	return player->direction;
}

void Player_Move(Player* player, Platform* platforms)
{
	//플레이어가 움직일 수 있다면
	if (Player_IsMovable(player, platforms))
	{
		//입력을 받아 이동
		if (Input_GetKey(VK_LEFT))
		{
			// 걷는 상태로 전환, 방향 결정
			player->state = PLAYER_WALKING;
			player->direction = PLAYER_LEFT;

			//이동 연산
			player->position.X -= PLAYER_WALK_SPEED * Timer_GetDeltaTime();
		}

		if (Input_GetKey(VK_RIGHT))
		{
			// 걷는 상태로 전환, 방향 결정
			player->state = PLAYER_WALKING;
			player->direction = PLAYER_RIGHT;

			//이동 연산
			player->position.Y += PLAYER_WALK_SPEED * Timer_GetDeltaTime();
		}
	}

}

void Player_Jump(Player* player, Trap* traps)
{

}

bool Player_IsMovable(Player* player, Platform* platforms)
{

}


bool Player_IsHitTrap(Player* player, Trap* traps)
{

}

void Player_StayStill(Player* player)
{
	if (!player->isJumpting && player->state == PLAYER_WALKING) 
	{
		player->elapsedTime += Timer_GetDeltaTime();

		if (player->elapsedTime >= PLAYER_MAX_LIFE_TIME)
		{
			player->elapsedTime = 0;
			Player_Die(player);
		}
	}

	player->state = PLAYER_WALKING;
}

void Player_Die(Player* player)
{
	player->isPlayerDie = true;
}

bool Player_isDead(Player* player)
{
	return player->isPlayerDie;
}
