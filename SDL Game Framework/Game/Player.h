#pragma once

#include "Framework.h";
#include "Map.h"
#include "Animation.h"

#define PLAYER_WALK_SPEED 15		//�÷��̾� �̵� �ӵ�
#define PLAYER_JUMP_SPEED -35		//�÷��̾� ���� �ӵ�(������ -��)
#define PLAYER_MAX_JUMPING_COUNT 2	//�÷��̾� ���� ī��Ʈ
#define PLAYER_MAX_STATE_COUNT 2	//�÷��̾� ���� ���� ����
#define	PLAYER_MAX_DIRECTION_COUNT 2 //�÷��̾� ���� ���� ����
#define PLAYER_MAX_IMAGE_COUNT 8	//�� ������ �ִ� ����
#define PLAYER_MAX_LIFE_TIME 4.5f	//�÷��̾ ������ ���� �� �ִ� �ִ� �ð�

//�÷��̾� �̵� ����
enum Player_State 
{
	PLAYER_IDLE = 2,
	PLAYER_MOVE = 8,
	PLAYER_DIE = 9
};

//�÷��̾� �̵� ����
enum Player_Direction 
{
	PLAYER_LEFT,
	PLAYER_RIGHT
};

typedef struct Player 
{

	//�̵� ����
	enum Player_State		state;		//�÷��̾� �̵� ����
	enum Player_Direction	direction;	//�÷��̾� �̵� ����

	//��ġ ����
	Position			position;		//�÷��̾� ��ǥ ��

	//���� ����
	int32				currentJumpingCount;//���� ���� ī��Ʈ
	bool				isJumping;		//���� ������

	//���� ���� ����
	float				elapsedTime;	//�÷��̾ ������ �ִ� �ð� ����
	bool				isPlayerDie;	//�÷��̾� ��� �ߴ���

	//ȿ����
	SoundEffect*			dieSound;	//����� ȿ���� 

	//�÷��̾� �̹���
	Animation			animation;		//�÷��̾� �̹��� �ִϸ��̼�
	
} Player;

//#### �⺻ �Լ�
void Player_Init(Player* player, SoundEffect* deathEffectSound);

void Player_Update(Player* player, Map* map);

//���߿� �ٸ� ���Ϸ� �� ����... �����
void Player_Render(Player* player);

void Player_Release(Player* player);


//#### �߰� �Լ�(�߰� ����)

/// <summary>
/// �÷��̾��� ��ǥ �� ����
/// </summary>
void Player_SetPosition(Player* player, const Position newPosition);

/// <summary>
/// �÷��̾� ��ǥ �� ��ȯ
/// </summary>
Position Player_GetPosition(Player* player);

/// <summary>
/// �÷��̾� ���� ��ȯ
/// </summary>
int32 Player_GetDirection(Player* player);

/// <summary>
/// �÷��̾� ���� ��ȯ
/// </summary>
int32 Player_GetState(Player* player);

/// <summary>
/// �÷��̾� ���� ��ȯ
/// </summary>
int32 Player_SetState(Player* player, enum Player_State state);

/// <summary>
/// �÷��̾� �ִϸ��̼� ��ȯ
/// </summary>
Animation* Player_GetAnimation(Player* player);

/// <summary>
/// �÷��̾��� �̵�
/// </summary>
void Player_Move(Player* player, Map* map);

/// <summary>
/// �÷��̾��� ���� ����
/// </summary>
void Player_Jump(Player* player, Map* map);

/// <summary>
/// �÷��̾ ������ �� �ִ���
/// </summary>
/// <param name="platforms">���� �÷��� �迭</param>
bool Player_IsMovable(Player* player, Map* map);

/// <summary>
/// �÷��̾ �׾�����
/// </summary>
/// <param name="traps">���� ���� �迭</param>
bool Player_IsHitTrap(Player* player, Map* map);

/// <summary>
/// �÷��̾ ������ �ִ����� ���� ó��
/// </summary>
void Player_StayStill(Player* player);

/// <summary>
/// �÷��̾�����
/// </summary>
/// <param name="platforms">���� �÷��� �迭</param>
void Player_Die(Player* player);

/// <summary>
/// �÷��̾�����
/// </summary>
/// <param name="platforms">���� �÷��� �迭</param>
bool Player_isDead(Player* player);

