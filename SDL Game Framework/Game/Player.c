#include "stdafx.h"
#include "Player.h"
#include "Framework.h"

//#### �⺻ �Լ�
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


//#### �߰� �Լ�(�߰� ����)
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
	//�÷��̾ ������ �� �ִٸ�
	if (Player_IsMovable(player, platforms))
	{
		//�Է��� �޾� �̵�
		if (Input_GetKey(VK_LEFT))
		{
			// �ȴ� ���·� ��ȯ, ���� ����
			player->state = PLAYER_WALKING;
			player->direction = PLAYER_LEFT;

			//�̵� ����
			player->position.X -= PLAYER_WALK_SPEED * Timer_GetDeltaTime();
		}

		if (Input_GetKey(VK_RIGHT))
		{
			// �ȴ� ���·� ��ȯ, ���� ����
			player->state = PLAYER_WALKING;
			player->direction = PLAYER_RIGHT;

			//�̵� ����
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
