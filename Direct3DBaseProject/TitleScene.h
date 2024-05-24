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
	bool GetIsFinish() { return m_isFinish; }
private:
	static const Vector2 m_titlePos;	//�^�C�g���̍��W
	static const Vector2 m_titleScale;	//�^�C�g���̃X�P�[��
	static constexpr const wchar_t* m_title = L"vs TANK!";	//�^�C�g����

	static const Vector2 m_confirmPos;							//confirm�̍��W
	static constexpr const wchar_t* m_confirm = L"CONFIRM";		//confirm������

	static const Vector2 m_backPos;								//back�̍��W
	static constexpr const wchar_t* m_back = L"BACK";			//back������

	static const Vector2 m_selectPos;							//select�̍��W
	static constexpr const wchar_t* m_select = L"SELECT";		//select������

	static const Vector2 m_playPos;						//PLAY�{�^�����W
	static constexpr const wchar_t* m_play = L"PLAY";	//PLAY������

	static const Vector2 m_controlsPos;							//����{�^�������̍��W
	static constexpr const wchar_t* m_controls = L"CONTROLS";	//CONTROLS������

	static const Vector2 m_movePos;							//move�����̍��W
	static constexpr const wchar_t* m_move = L"MOVE";		//move������

	static const Vector2 m_anglePos;						//angle�����̍��W
	static constexpr const wchar_t* m_angle = L"ANGLE";		//angle������

	static const Vector2 m_shotPos;							//shot�����̍��W
	static constexpr const wchar_t* m_shot = L"SHOT";		//shot������

	static const Vector2 m_descriptionStringScale;

	static constexpr float m_fixButtonY = 20.f;					//�{�^���̕�����Y���C����

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_titleUI;//�^�C�g��UI
	vector<Vector2> m_titleUIPos;									   //�^�C�g��UI���W
	vector<float> m_titleUIScale;									   //�^�C�g��UI�X�P�[��

	int m_nowSelect;									//�I�����Ă���index
	int m_choose;										//�I�����肵���{�^����index
	static constexpr float m_timeSpeed = 2.f;			//���Ԃ̐i�ރX�s�[�h
	static constexpr int m_leftIndex = 3;				//�{�^����
	static constexpr int m_rightIndex = 4;				//�{�^���E
	static constexpr int m_descriptionUIIndex = 5;		//UI�\���p�X���C�h
	static constexpr int m_descriptionButtonUIIndex = 9;//����{�^��UI

	static constexpr float m_UIDepth = 0.f;
	static constexpr float m_stringDepth = 0.1f;
	static constexpr float m_descriptionUIDepth = 0.2f;
	static constexpr float m_descriptionStringDepth = 0.3f;

	bool m_isFinish;			//�V�[�����I���������ǂ���
};

