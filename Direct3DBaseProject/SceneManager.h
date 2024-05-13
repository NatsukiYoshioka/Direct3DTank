#pragma once

class BaseScene;

class SceneManager
{
private:
	SceneManager();
	~SceneManager();
public:
	enum class SCENE
	{
		TITLE,
		MAINGAME,
		RESULT
	};

	static void CreateInstance();
	static void DestroyInstance();
	static SceneManager* GetInstance() { return m_sceneManager; }
	SCENE GetNowSceneState()const { return m_sceneState; }
	void ChangeScene(SCENE sceneState);
	void Update();
	void Draw();



private:
	static SceneManager* m_sceneManager;
	BaseScene* m_nowScene;
	SCENE m_sceneState;
};

