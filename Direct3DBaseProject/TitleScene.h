#pragma once

class BaseScene;

class TitleScene:public BaseScene
{
public:
	/// <summary>
	/// タイトルシーンの生成
	/// </summary>
	TitleScene();

	/// <summary>
	/// タイトルシーンの破棄
	/// </summary>
	~TitleScene();

	/// <summary>
	/// タイトルシーンの更新
	/// </summary>
	/// <param name="">pad state</param>
	void Update(DirectX::GamePad::State);

	/// <summary>
	/// タイトルシーンの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// シーンが終了したかどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	bool isFinish;			//シーンが終了したかどうか
};

