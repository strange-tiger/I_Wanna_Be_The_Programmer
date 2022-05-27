#pragma once

#include "Type.h"
#include "Framework.h"
#include "Common.h"

//���� ����
enum Trap_Type {
	TRAP_BASIC,
	TRAP_FLYING,
	TRAP_TRACK,
	TRAP_SWITCH
};

//���� ��Ʈ��Ʈ(���� ����/�߰� ����)
typedef struct tagTrap
{
	//�⺻
	Platform	Platform;		//������ �÷����� �� ����

	//ȿ��
	enum Trap_Type	Type;	//���� Ÿ��
	bool		Active;
	float		ActiveTime;
	int32		Speed;
	
	//���ƿ���/���� �������� ���� ��ǥ ����
	Position	TargetPosition;	//��ǥ ���� ��ǥ��

	//����Ī ������
	int32		ImageAlpha;		//����ȭ
	Image		Image2;			//(�Ķ�/����) �ٲ� �̹���

	//ȿ����
	SoundEffect	effectSound;	//���ƿ��� ���� ȿ������ ������ ȿ����
} Trap;

//####�߰� �Լ�
/// <summary>
/// ������ TargetPosition���� �����δ�.
/// </summary>
void Trap_TrapMove(Trap* trap, struct Player* player, int32 x, int32 y);

/// <summary>
/// ��ǥ���� ��ġ TargetPosition ���� �޴´�.
/// </summary>
void Trap_GetTargetPosition(Trap* trap, struct Player* player, int32 x, int32 y);

/// <summary>
/// ����ġ ������ �ֱ⿡ ���� �����δ�.
/// </summary>
void Trap_TrapSwitch(Trap* trap);
