#pragma once

class BaseScene;
class TankManager;

class SceneManager
{
private:
	SceneManager(DirectX::GamePad* gamePad);
	~SceneManager();
public:
	enum class SCENE
	{
		TITLE,
		MAINGAME,
		RESULT
	};

	static void CreateInstance(DirectX::GamePad* gamePad);
	static void DestroyInstance();
	static SceneManager* GetInstance() { return m_sceneManager; }
	SCENE GetNowSceneState()const { return m_sceneState; }
	bool GetIsChange() { return isChange; }
	void ChangeScene(SCENE sceneState);
	void Update(TankManager* tankManager);
	void Draw();

private:
	static SceneManager* m_sceneManager;
	BaseScene* m_nowScene;
	SCENE m_sceneState;

	DirectX::GamePad* m_gamePad;

	bool isChange;
};

