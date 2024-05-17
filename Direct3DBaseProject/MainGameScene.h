#pragma once

class BaseScene;

class MainGameScene:public BaseScene
{
public:
	MainGameScene();
	~MainGameScene();

	void Update(DirectX::GamePad::State);
	void Draw();

	bool GetIsFinish() { return isFinish; }
private:
	bool isFinish;
};

