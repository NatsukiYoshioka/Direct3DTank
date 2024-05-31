#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class BaseScene;

class ResultScene :public BaseScene
{
public:
	/// <summary>
	/// リザルトシーン生成
	/// </summary>
	ResultScene();

	/// <summary>
	/// リザルトシーン破棄
	/// </summary>
	~ResultScene();

	/// <summary>
	/// リザルトシーン更新
	/// </summary>
	/// <param name="">pad state</param>
	void Update(DirectX::GamePad::State, TankManager* tankManager);

	/// <summary>
	/// リザルトシーン描画
	/// </summary>
	void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch);

	/// <summary>
	/// シーンが終了したかどうか取得
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	bool isFinish;			//シーンが終了したかどうか
};

