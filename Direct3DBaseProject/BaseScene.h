#pragma once

using namespace DirectX;

/// <summary>
/// シーンの基底クラス
/// </summary>
class BaseScene
{
public:
	virtual void Update(DirectX::GamePad::State) = 0;
	virtual void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch) = 0;
	virtual bool GetIsFinish() = 0;
};

