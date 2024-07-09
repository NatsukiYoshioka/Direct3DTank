#pragma once
#include"common.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class BaseScene;
class AnimatedTexture;

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
	void Update(DirectX::GamePad::State, TankManager* tankManager, float elapsedTime);

	/// <summary>
	/// メインゲームシーン描画
	/// </summary>
	void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch, ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources);

	/// <summary>
	/// シーンが終了したかどうか取得
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }

	void DrawBackGround(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources);
private:
	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_mainGameUI; //タイトルUI
	vector<unique_ptr<AnimatedTexture>> m_animatedTexture;
	vector<Vector2> m_mainGameUIPos;									   //タイトルUI座標
	vector<float> m_mainGameUIScale;									   //タイトルUIスケール

	bool m_isEnableHeartUI[playerNum * maxHp];			//ハートUIが描画有効かどうか

	unique_ptr<DirectX::BasicEffect> m_basicEffect;         //描画オプションの設定クラス

	static constexpr float m_UIDepth = 0.1f;

	static constexpr int m_maxFrame = 7;

	static constexpr float m_framesPerSencond = 5.f;

	static constexpr int m_backgroundIndex = 20;
	static constexpr float m_backgroundHeight = -10.f;
	static constexpr float m_backgroundWidth = 50.f;

	bool isFinish;		//シーンが終了したかどうか
};

