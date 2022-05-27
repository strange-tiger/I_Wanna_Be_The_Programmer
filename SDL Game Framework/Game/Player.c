#include "stdafx.h"
#include "Framework.h"
#include "Player.h"
#include "Animation.h"

//#### �⺻ �Լ�
void Player_Init(Player* player, SoundEffect* dieSound) 
{
	//�⺻ ���� ����
	player->state = PLAYER_IDLE;
	player->direction = PLAYER_RIGHT;

	//����
	player->isJumping = false;
	player->currentJumpingCount = PLAYER_MAX_JUMPING_COUNT;

	//�״� ����
	player->isPlayerDie = false;
	player->elapsedTime = 0.0f;

	//ȿ����
	player->dieSound = dieSound;

	//���ϸ��̼�
	Animation_Init(&player->animation);
}

void Player_Update(Player* player, Map* map)
{
	//�⺻ �̵� �� ���� ó��
	Player_Move(player, map);
	Player_Jump(player, map);
	Player_StayStill(player);

	//�ִϸ��̼� ������Ʈ
	Aniamtion_Update(player);
}

void Player_Render(Player* player) 
{
	//���ϸ��̼Ǹ� ����
	Animation_Render(&player->animation, &player->position);
}

void Player_Release(Player* player) 
{
	//�÷��̾� ���� Release
	Audio_FreeSoundEffect(player->dieSound);

	//���ϸ��̼� Release
	Animation_Release(&player->animation);
}


//#### �߰� �Լ�(�߰� ����)
//��
void Player_SetPosition(Player* player, const Position newPosition)
{
	player->position.X = newPosition.X;
	player->position.Y = newPosition.Y;
}

//��
Position Player_GetPosition(Player* player) 
{
	return player->position;
}

//��
int32 Player_GetDirection(Player* player)
{
	return player->direction;
}

//��
int32 Player_GetState(Player* player)
{
	return player->state;
}

//��
void Player_SetState(Player* player, enum Player_State state)
{
	player->state = state;
}

//��
Animation* Player_GetAnimation(Player* player)
{
	return &player->animation;
}

//��
void Player_Move(Player* player, Map* map)
{
	//�÷��̾ ������ �� �ִٸ�
	if (Player_IsMovable(player, map))
	{
		//�Է��� �޾� �̵�
		if (Input_GetKey(VK_LEFT))
		{
			// �ȴ� ���·� ��ȯ, ���� ����
			player->state = PLAYER_MOVE;
			player->direction = PLAYER_LEFT;

			//�̵� ����
			player->position.X -= PLAYER_WALK_SPEED * Timer_GetDeltaTime();
		}

		if (Input_GetKey(VK_RIGHT))
		{
			// �ȴ� ���·� ��ȯ, ���� ����
			player->state = PLAYER_MOVE;
			player->direction = PLAYER_RIGHT;

			//�̵� ����
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

//��
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

//��
void Player_Die(Player* player)
{
	player->isPlayerDie = true;
}

//��
bool Player_isDead(Player* player)
{
	return player->isPlayerDie;
}
