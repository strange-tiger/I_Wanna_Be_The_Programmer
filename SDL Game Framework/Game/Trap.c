#include "Trap.h"

void Trap_TrapMove(Trap* trap, Player* player)
{
	if (!(trap->Type == TRAP_FLYING) && !(trap->Type == TRAP_TRACK))	// ���� ���� : ���ƿ���, �������
	{
		return;
	}
	if (!trap->Active) // �ߵ� ����
	{
		return;
	}
	if (trap->ActiveTime < TRAP_SWITCH_CYCLE)
	{
		return;
	}
	Trap_GetTrackTargetPosition(trap, player);

	int32 trapX = trap->Platform.Position.X;
	int32 trapY = trap->Platform.Position.Y;
	int32 targetX = trap->TargetPosition.X;
	int32 targetY = trap->TargetPosition.Y;

	if (trapX > targetX)
	{
		if (trapX - trap->Speed > targetX)
		{
			trap->Platform.Position.X -= trap->Speed;
		}
		else
		{
			trap->Platform.Position.X = targetX;
		}
	}
	else if (trapX < targetX)
	{
		if (trapX + trap->Speed < targetX)
		{
			trap->Platform.Position.X += trap->Speed;
		}
		else
		{
			trap->Platform.Position.X = targetX;
		}
	}

	if (trapY > targetY)
	{
		if (trapY - trap->Speed > targetY)
		{
			trap->Platform.Position.Y -= trap->Speed;
		}
		else
		{
			trap->Platform.Position.Y = targetY;
		}
	}
	else if (trapY < targetY)
	{
		if (trapY + trap->Speed < targetY)
		{
			trap->Platform.Position.Y += trap->Speed;
		}
		else
		{
			trap->Platform.Position.Y = targetY;
		}
	}
	trap->ActiveTime = 0.0f;

}

void Trap_InitializeTargetPosition(Trap* trap, int32 x, int32 y)
{
	if (trap->Type == TRAP_FLYING)
	{
		trap->TargetPosition.X = x;
		trap->TargetPosition.Y = y;
	}
	else
	{
		trap->TargetPosition = trap->Platform.Position;
	}
}

void Trap_GetTrackTargetPosition(Trap* trap, Player* player)
{
	if (trap->Type == TRAP_TRACK)
	{
		trap->TargetPosition = player->Position;
	}

	/*return trap->TargetPosition;*/
}

void Trap_TrapSwitch(Trap* trap)
{
	trap->ActiveTime += Timer_GetDeltaTime(); // ���������� �𸥴�.
	if (trap->Type == TRAP_SWITCH)
	{
		return;
	}

	if (trap->ActiveTime >= TRAP_SWITCH_CYCLE)
	{
		trap->Active = !trap->Active;

		trap->ActiveTime = 0.0f;
	}
}