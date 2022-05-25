#pragma once

#include "Framework.h";

#define PLAYER_WALK_SPEED 15		//�÷��̾� �̵� �ӵ�
#define PLAYER_JUMP_SPEED -35		//�÷��̾� ���� �ӵ�(������ -��)
#define PLAYER_MAX_JUMPING_COUNT 2	//�÷��̾� ���� ī��Ʈ

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
	enum Player_State		State;		//�÷��̾� �̵� ����
	enum Player_Direction	Direction;	//�÷��̾� �̵� ����

	//��ġ ����
	Position			Position;	//�÷��̾� ��ǥ ��

	//���� ����
	bool				isJumpting;	//���� ������
	int32				CurrentJumpingCount;//���� ���� ī��Ʈ

	//���� ���� ����
	bool				isPlayerDie; //�÷��̾� ��� �ߴ���

	//ȿ����
	SoundEffect			DieSound;	//����� ȿ����

} Player;

//#### �⺻ �Լ�
void Player_Init(Player* player);

void Player_Update(Player* player);

//���߿� �ٸ� ���Ϸ� �� ����... �����
void Player_Render(Player* player);

void Map_Release(Player* player);


//#### �߰� �Լ�(�߰� ����)
