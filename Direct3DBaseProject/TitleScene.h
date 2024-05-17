#pragma once

class BaseScene;

class TitleScene:public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	void Update(DirectX::GamePad::State);
	void Draw();

	bool GetIsFinish() { return isFinish; }
private:
	bool isFinish;
};

