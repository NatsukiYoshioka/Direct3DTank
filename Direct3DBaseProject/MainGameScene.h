#pragma once

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
	void Update(DirectX::GamePad::State);

	/// <summary>
	/// ���C���Q�[���V�[���`��
	/// </summary>
	void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch);

	/// <summary>
	/// �V�[�����I���������ǂ����擾
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_mainGameUI; //�^�C�g��UI
	vector<Vector2> m_mainGameUIPos;									   //�^�C�g��UI���W
	vector<float> m_mainGameUIScale;									   //�^�C�g��UI�X�P�[��

	static constexpr float m_UIDepth = 0.1f;

	bool isFinish;		//�V�[�����I���������ǂ���
};

