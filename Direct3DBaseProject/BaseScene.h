#pragma once

using namespace DirectX;

class TankManager;

/// <summary>
/// �V�[���̊��N���X
/// </summary>
class BaseScene
{
public:
	virtual void Update(DirectX::GamePad::State,TankManager* tankManager) = 0;
	virtual void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch) = 0;
	virtual bool GetIsFinish() = 0;
};

