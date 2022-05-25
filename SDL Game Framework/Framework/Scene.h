#pragma once

#include "Type.h"

//���� ����
static bool s_isGameClose = false;

typedef struct Scene
{
	void (*Init)(void);		// ���� �ʱ�ȭ �ϴ� �Լ�
	void (*Update)(void);	// ������Ʈ
	void (*Render)(void);	// ����
	void (*Release)(void);	// ������ ����� �ڿ��� ����
	void* Data;
} Scene;

typedef enum SceneType
{
	SCENE_NULL,
	SCENE_TITLE,
	SCENE_MAIN,
	SCENE_CREDIT,
	SCENE_MAX
} ESceneType;

extern Scene g_Scene;

/// <summary>
/// ���� ������ ��ȯ�� �����ΰ�?
/// </summary>
/// <returns>���� ������ ��ȯ�� �����̸� true, �ƴϸ� false</returns>
bool Scene_IsSetNextScene(void);

/// <summary>
/// ���� ���� �����Ѵ�.
/// </summary>
/// <param name="scene">��</param>
void Scene_SetNextScene(ESceneType scene);

/// <summary>
/// �� ��ȯ
/// </summary>
/// <param name=""></param>
void Scene_Change(void);


/// <summary>
/// �� ��ȯ
/// </summary>
/// <returns>s_isGameClose ��ȯ</returns>
bool Scene_IsGameClose(void);