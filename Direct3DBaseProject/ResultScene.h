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
	ResultScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resultUI, vector<Vector2> resultUIPos, vector<float> resultUIScale);

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
	void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch, ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources);

	/// <summary>
	/// シーンが終了したかどうか取得
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_resultUI;	//リザルトUI
	vector<Vector2> m_resultUIPos;											//リザルトUI座標
	vector<float> m_resultUIScale;											//リザルトUIスケール

	static constexpr float m_UIDepth = 0.1f;

	bool isFinish;			//シーンが終了したかどうか
};

