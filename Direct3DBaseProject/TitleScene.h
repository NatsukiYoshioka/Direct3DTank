#pragma once

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class BaseScene;

class TitleScene:public BaseScene
{
public:
	/// <summary>
	/// �^�C�g���V�[���̐���
	/// </summary>
	TitleScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos);

	/// <summary>
	/// �^�C�g���V�[���̔j��
	/// </summary>
	~TitleScene();

	/// <summary>
	/// �^�C�g���V�[���̍X�V
	/// </summary>
	/// <param name="">pad state</param>
	void Update(DirectX::GamePad::State);

	/// <summary>
	/// �^�C�g���V�[���̕`��
	/// </summary>
	void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch);

	/// <summary>
	/// �V�[�����I���������ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	static const Vector2 m_titlePos;	//�^�C�g���̍��W
	static const Vector2 m_titleScale;	//�^�C�g���̃X�P�[��
	static constexpr const wchar_t* m_title = L"vs TANK!";	//�^�C�g����

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_titleUI;//�^�C�g��UI
	vector<Vector2> m_titleUIPos;									   //�^�C�g��UI���W

	bool isFinish;			//�V�[�����I���������ǂ���
};

