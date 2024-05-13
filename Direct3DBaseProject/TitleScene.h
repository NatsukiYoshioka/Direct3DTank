#pragma once

class BaseScene;

class TitleScene:public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	void Update();
	void Draw();
};

