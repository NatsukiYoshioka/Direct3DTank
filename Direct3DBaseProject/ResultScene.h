#pragma once

class BaseScene;

class ResultScene :public BaseScene
{
public:
	ResultScene();
	~ResultScene();

	void Update(DirectX::GamePad::State);
	void Draw();

	bool GetIsFinish() { return isFinish; }
private:
	bool isFinish;
};

