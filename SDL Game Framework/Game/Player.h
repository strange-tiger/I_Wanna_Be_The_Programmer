#pragma once

#include "Framework.h";
#include "Map.h"

#define PLAYER_WALK_SPEED 15		//�÷��̾� �̵� �ӵ�
#define PLAYER_JUMP_SPEED -35		//�÷��̾� ���� �ӵ�(������ -��)
#define PLAYER_MAX_JUMPING_COUNT 2	//�÷��̾� ���� ī��Ʈ
#define	PLAYER_IMAGE_COUNT 5
#define PLAYER_MAX_LIFE_TIME 4.5f

//�÷��̾� �̵� ����
enum Player_State 
{
	PLAYER_WALKING,
	PLAYER_STOP
};

//�÷��̾� �̵� ����
enum Player_Direction 
{
	PLAYER_RIGHT,
	PLAYER_LEFT
};

typedef struct tagPlayer 
{

	//�̵� ����
	enum Player_State		state;		//�÷��̾� �̵� ����
	enum Player_Direction	direction;	//�÷��̾� �̵� ����

	//��ġ ����
	Position			position;	//�÷��̾� ��ǥ ��

	//���� ����
	bool				isJumpting;	//���� ������
	int32				currentJumpingCount;//���� ���� ī��Ʈ

	//���� ���� ����
	bool				isPlayerDie; //�÷��̾� ��� �ߴ���
	float				elapsedTime; //�÷��̾ ������ �ִ� �ð� ����

	//ȿ����
	SoundEffect			dieSound;	//����� ȿ���� 

	//�÷��̾� �̹���
	Image				images[PLAYER_IMAGE_COUNT]; //�÷��̾� �̹���

} Player;

//#### �⺻ �Լ�
void Player_Init(Player* player);

void Player_Update(Player* player);

//���߿� �ٸ� ���Ϸ� �� ����... �����
void Player_Render(Player* player);

void Player_Release(Player* player);


//#### �߰� �Լ�(�߰� ����)

/// <summary>
/// �÷��̾ ������ �� �ִ���
/// </summary>
void Player_SetPosition(Player* player, const Position newPosition);

/// <summary>
/// �÷��̾� ��ǥ �� ��ȯ
/// </summary>
Position Player_GetPosition(Player* player);

/// <summary>
/// �÷��̾� ��ǥ �� ��ȯ
/// </summary>
int32 Player_GetDirection(Player* player);

/// <summary>
/// �÷��̾��� �̵�
/// </summary>
void Player_Move(Player* player, Platform* platforms);

/// <summary>
/// �÷��̾��� ���� ����
/// </summary>
void Player_Jump(Player* player, Trap* traps);

/// <summary>
/// �÷��̾ ������ �� �ִ���
/// </summary>
/// <param name="platforms">���� �÷��� �迭</param>
bool Player_IsMovable(Player* player, Platform* platforms);

/// <summary>
/// �÷��̾ �׾�����
/// </summary>
/// <param name="traps">���� ���� �迭</param>
bool Player_IsHitTrap(Player* player, Trap* traps);

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

