#pragma once

class BaseScene;

class MainGameScene:public BaseScene
{
public:
	MainGameScene();
	~MainGameScene();

	void Update();
	void Draw();
};

