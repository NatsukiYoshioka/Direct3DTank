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
	/// ���C���Q�[���V�[������
	/// </summary>
	MainGameScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mainGameUI, vector<Vector2> mainGameUIPos, vector<float> mainGameUIScale);

	/// <summary>
	/// ���C���Q�[���V�[���j��
	/// </summary>
	~MainGameScene();

	/// <summary>
	/// ���C���Q�[���V�[���X�V
	/// </summary>
	/// <param name=""></param>
	void Update(DirectX::GamePad::State, TankManager* tankManager);

	/// <summary>
	/// ���C���Q�[���V�[���`��
	/// </summary>
	void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch, ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources);

	/// <summary>
	/// �V�[�����I���������ǂ����擾
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }

	void DrawBackGround(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources);
private:
	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_mainGameUI; //�^�C�g��UI
	vector<Vector2> m_mainGameUIPos;									   //�^�C�g��UI���W
	vector<float> m_mainGameUIScale;									   //�^�C�g��UI�X�P�[��

	bool m_isEnableHeartUI[playerNum * maxHp];			//�n�[�gUI���`��L�����ǂ���

	static constexpr float m_UIDepth = 0.1f;

	static constexpr int m_backgroundIndex = 20;
	static constexpr float m_backgroundHeight = -10.f;
	static constexpr float m_backgroundWidth = 50.f;

	bool isFinish;		//�V�[�����I���������ǂ���
};

