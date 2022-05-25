#pragma once

#include "Type.h"
#include "Framework.h"
#include "stdafx.h"

//���� ����
typedef enum Trap_Type {
	TRAP_BASIC,
	TRAP_FLYING,
	TRAP_TRACK,
	TRAP_SWITCH
} Trap_Type;

//���� ��Ʈ��Ʈ(���� ����/�߰� ����)
typedef struct tagTrap
{
	//�⺻
	Image		TrapImage;		//���� �̹���
	Position	TrapPosition;	//���� ��ġ
	int32		Width;		//���� �̹����� ���� ��
	int32		Height;		//���� �̹����� ���� ��

	//ȿ��
	Trap_Type	Type;	//���� Ÿ��
	
	//���ƿ���/���� �������� ���� ��ǥ ����
	Position	TargetPosition;	//��ǥ ���� ��ǥ��

	//����Ī ������
	int32		ImageAlpha;		//����ȭ
	Image		Image2;			//(�Ķ�/����) �ٲ� �̹���

} Trap;

//####�߰� �Լ�