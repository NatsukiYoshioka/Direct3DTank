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
	TitleScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale);

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

	static const Vector2 m_playPos;						//PLAY�{�^�����W
	static const Vector2 m_playScale;					//PLAY�{�^���̃X�P�[��
	static constexpr const wchar_t* m_play = L"PLAY";	//PLAY������

	static const Vector2 m_controlsPos;							//��������{�^�����W
	static const Vector2 m_controlsScale;						//��������{�^���̃X�P�[��
	static constexpr const wchar_t* m_controls = L"CONTROLS";	//CONTROLS������

	static constexpr float m_fixButtonY = 20.f;					//�{�^���̕�����Y���C����

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_titleUI;//�^�C�g��UI
	vector<Vector2> m_titleUIPos;									   //�^�C�g��UI���W
	vector<float> m_titleUIScale;									   //�^�C�g��UI�X�P�[��

	int m_nowSelect;									//�I�����Ă���index
	static constexpr float m_timeSpeed = 2.f;			//���Ԃ̐i�ރX�s�[�h
	static constexpr int m_leftIndex = 3;				//�{�^����
	static constexpr int m_rightIndex = 4;				//�{�^���E
	static constexpr int m_descriptionUIIndex = 5;

	static constexpr float m_UIDepth = 0.f;
	static constexpr float m_stringDepth = 0.1f;
	static constexpr float m_descriptionUIDepth = 0.1f;

	bool isFinish;			//�V�[�����I���������ǂ���
};

