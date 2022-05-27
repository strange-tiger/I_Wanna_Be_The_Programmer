#include "stdafx.h"
#include "Framework.h"
#include "Player.h"
#include "Animation.h"
#include "Map.h"

//#### �⺻ �Լ�
void Player_Init(Player* player, SoundEffect* dieSound) 
{
	//����
	player->Rect.left = player->position.X;
	player->Rect.top = player->position.Y;
	player->Rect.right = player->position.X + player->animation.playerIdleImages[0][0].Width;
	player->Rect.bottom = player->position.Y + player->animation.playerIdleImages[0][0].Height;

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
	
	//���� �÷��̾ Ʈ���� �ε�ġ�� �÷��̾� ��� ó��
	if(Player_IsHitTrap(player, map) == true)
	{
		Player_Die(player);
	}
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
 
#pragma region GetSet
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
#pragma endregion

#pragma region 
//��
void Player_Move(Player* player, Map* map)
{
	//�Է��� �޾� �̵�
	if (Input_GetKey(VK_LEFT))
	{
		// �ȴ� ���·� ��ȯ, ���� ����
		player->state = PLAYER_MOVE;
		player->direction = PLAYER_LEFT;

		//�̵� ����
		player->addPosition.X = -PLAYER_WALK_SPEED * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_RIGHT))
	{
		// �ȴ� ���·� ��ȯ, ���� ����
		player->state = PLAYER_MOVE;
		player->direction = PLAYER_RIGHT;

		//�̵� ����
		player->addPosition.X += PLAYER_WALK_SPEED * Timer_GetDeltaTime();
	}

	//�̵� �� ��ŭ ��ǥ �� �̵�
	player->position.X += player->addPosition.X;

	//���� �̵��� ����� �÷��̾ �÷����� ��ġ�� �ٽ� ������ ������.
	if (Player_IsMovable(player, map) == false)
	{
		player->position.X -= player->addPosition.X;
	}
}

//
void Player_Jump(Player* player, Map* map)
{
	//���� ó�� (���� Ű�� ���� �ð� ��ŭ �ö󰡰�, ���� ��������.)
	if (Input_GetKey(VK_SPACE))
	{

	}

}

//��
bool Player_IsMovable(Player* player, Map* map)
{
	for (int32 i = 0; i < MAX_PLATFORM_COUNT; i++) 
	{
		if (Platform_DetectIsGround(&map->PlatformList[i], player))
		{
			return false;
		}
	}

	return true;
}

//��
bool Player_IsHitTrap(Player* player, Map* map)
{
	for (int32 i = 0; i < MAX_TRAP_COUNT; i++)
	{
		if (player->Rect.left <= map->TrapList[i].Platform.Rect.right &&
			player->Rect.right >= map->TrapList[i].Platform.Rect.left &&
			player->Rect.bottom <= map->TrapList[i].Platform.Rect.top)
		{
			return true;
		}
	}

	return false;
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
	player->state = PLAYER_DIE;
}

//��
bool Player_isDead(Player* player)
{
	return player->isPlayerDie;
}
