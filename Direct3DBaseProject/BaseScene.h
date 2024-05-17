#pragma once

using namespace DirectX;

class BaseScene
{
public:
	virtual void Update(DirectX::GamePad::State) = 0;
	virtual void Draw() = 0;
	virtual bool GetIsFinish() = 0;
};

