#include "pch.h"
#include"BaseScene.h"
#include"TitleScene.h"
#include"MainGameScene.h"
#include"ResultScene.h"
#include "SceneManager.h"

SceneManager* SceneManager::m_sceneManager = nullptr;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::CreateInstance()
{
	if (!m_sceneManager)
	{
		m_sceneManager = new SceneManager();
	}
}

void SceneManager::DestroyInstance()
{
	if (m_sceneManager)
	{
		delete(m_sceneManager);
	}
}

void SceneManager::ChangeScene(SCENE sceneState)
{
	if (m_nowScene != NULL)
	{
		delete(m_nowScene);
	}

	m_sceneState = sceneState;

	switch (m_sceneState)
	{
	case SCENE::TITLE:
		m_nowScene = new TitleScene();
		break;
	case SCENE::MAINGAME:
		m_nowScene = new MainGameScene();
		break;
	case SCENE::RESULT:
		m_nowScene = new ResultScene();
		break;
	}
}

void SceneManager::Update()
{
	m_nowScene->Update();
}

void SceneManager::Draw()
{
	m_nowScene->Draw();
}