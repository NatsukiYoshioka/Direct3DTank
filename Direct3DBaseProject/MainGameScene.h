#pragma once
#include"common.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class BaseScene;

class MainGameScene:public BaseScene
{
public:
	/// <summary>
	/// メインゲームシーン生成
	/// </summary>
	MainGameScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mainGameUI, vector<Vector2> mainGameUIPos, vector<float> mainGameUIScale);

	/// <summary>
	/// メインゲームシーン破棄
	/// </summary>
	~MainGameScene();

	/// <summary>
	/// メインゲームシーン更新
	/// </summary>
	/// <param name=""></param>
	void Update(DirectX::GamePad::State, TankManager* tankManager);

	/// <summary>
	/// メインゲームシーン描画
	/// </summary>
	void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch);

	/// <summary>
	/// シーンが終了したかどうか取得
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_mainGameUI; //タイトルUI
	vector<Vector2> m_mainGameUIPos;									   //タイトルUI座標
	vector<float> m_mainGameUIScale;									   //タイトルUIスケール

	bool m_isEnableHeartUI[playerNum * maxHp];			//ハートUIが描画有効かどうか

	static constexpr float m_UIDepth = 0.1f;

	bool isFinish;		//シーンが終了したかどうか
};

