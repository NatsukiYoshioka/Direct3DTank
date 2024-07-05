#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class BaseScene;

class ResultScene :public BaseScene
{
public:
	/// <summary>
	/// ���U���g�V�[������
	/// </summary>
	ResultScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resultUI, vector<Vector2> resultUIPos, vector<float> resultUIScale);

	/// <summary>
	/// ���U���g�V�[���j��
	/// </summary>
	~ResultScene();

	/// <summary>
	/// ���U���g�V�[���X�V
	/// </summary>
	/// <param name="">pad state</param>
	void Update(DirectX::GamePad::State, TankManager* tankManager);

	/// <summary>
	/// ���U���g�V�[���`��
	/// </summary>
	void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch, ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources);

	/// <summary>
	/// �V�[�����I���������ǂ����擾
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_resultUI;	//���U���gUI
	vector<Vector2> m_resultUIPos;											//���U���gUI���W
	vector<float> m_resultUIScale;											//���U���gUI�X�P�[��

	static constexpr float m_UIDepth = 0.1f;

	bool isFinish;			//�V�[�����I���������ǂ���
};

