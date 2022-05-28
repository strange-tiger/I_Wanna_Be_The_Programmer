#pragma once

#include "Framework.h"
#include "Map.h"
#include "Animation.h"

#define PLAYER_WALK_SPEED 15		//�÷��̾� �̵� �ӵ�

#define PLAYER_JUMP_SPEED -35		//�÷��̾� ���� �ӵ�(������ -��)
#define PLAYER_MAX_JUMPING_COUNT 2	//�÷��̾� ���� ī��Ʈ
#define PLAYER_MAX_JUMP_TIME 2.5f	//�÷��̾ �ִ�� ���� �� �� �ִ� �ð�

#define PLAYER_MAX_STATE_COUNT 2	//�÷��̾� ���� ���� ����

#define	PLAYER_MAX_DIRECTION_COUNT 2 //�÷��̾� ���� ���� ����

#define PLAYER_MAX_LIFE_TIME 4.5f	//�÷��̾ ������ ���� �� �ִ� �ִ� �ð�

//�÷��̾� �̵� ����
enum Player_State
{
	PLAYER_IDLE = PLAYER_IDE_PIC_COUNT,
	PLAYER_MOVE = PLAYER_MOVE_PIC_COUNT,
	PLAYER_DIE = PLAYER_DEATH_PIC_COUNT,
	PLAYER_CLIMB = PLAYER_CLIMB_PIC_COUNT
};

//�÷��̾� �̵� ����
enum Player_Direction 
{
	PLAYER_LEFT,
	PLAYER_RIGHT
};

typedef struct Player 
{
	//���� ����
	RECT					Rect;		//�÷��̾� ����

	//�̵� ����
	enum Player_State		state;		//�÷��̾� �̵� ����
	enum Player_Direction	direction;	//�÷��̾� �̵� ����

	//��ġ ����
	Position			position;		//�÷��̾� ��ǥ ��
	Position			addPosition;	//�߰��� ��ǥ ��

	//���� ����
	int32				currentJumpingCount;//���� ���� ī��Ʈ
	bool				isJumping;		//���� ������
	bool				isFalling;		//���� �ϰ� �������� ������
	float				jumpPressTime;	//����Ű�� �󸶳� ������ �־�����

	//���� ���� ����
	float				elapsedTime;	//�÷��̾ ������ �ִ� �ð� ����
	bool				isPlayerDie;	//�÷��̾� ��� �ߴ���

	//ȿ����
	SoundEffect*		dieSound;		//����� ȿ���� 

	//�÷��̾� �̹���
	Animation			animation;		//�÷��̾� �̹��� �ִϸ��̼�
	
} Player;

//#### �⺻ �Լ�
void Player_Init(Player* player); // , SoundEffect* deathEffectSound);

void Player_Update(Player* player, struct Map* map);

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
void Player_SetState(Player* player, enum Player_State state);

/// <summary>
/// �÷��̾� �ִϸ��̼� ��ȯ
/// </summary>
Animation* Player_GetAnimation(Player* player);

/// <summary>
/// �÷��̾��� �̵�
/// </summary>
void Player_Move(Player* player, struct Map* map);

/// <summary>
/// �÷��̾��� ���� ����
/// </summary>
void Player_Jump(Player* player,struct Map* map);

/// <summary>
/// �÷��̾ ������ �� �ִ���
/// </summary>
/// <param name="platforms">���� �÷��� �迭</param>
bool Player_IsMovable(Player* player, struct Map* map);

/// <summary>
/// �÷��̾ �׾�����
/// </summary>
/// <param name="traps">���� ���� �迭</param>
bool Player_IsHitTrap(Player* player, struct Map* map);

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

