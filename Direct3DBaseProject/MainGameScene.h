#pragma once

class BaseScene;

class MainGameScene:public BaseScene
{
public:
	/// <summary>
	/// メインゲームシーン生成
	/// </summary>
	MainGameScene();

	/// <summary>
	/// メインゲームシーン破棄
	/// </summary>
	~MainGameScene();

	/// <summary>
	/// メインゲームシーン更新
	/// </summary>
	/// <param name=""></param>
	void Update(DirectX::GamePad::State);

	/// <summary>
	/// メインゲームシーン描画
	/// </summary>
	void Draw();

	/// <summary>
	/// シーンが終了したかどうか取得
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	bool isFinish;		//シーンが終了したかどうか
};

