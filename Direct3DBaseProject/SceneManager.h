#pragma once

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class BaseScene;
class TankManager;

class SceneManager
{
private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="gamePad">DirectX::GamePad</param>
	SceneManager(DirectX::GamePad* gamePad, unique_ptr<DirectX::SpriteFont>&& defaultFontHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneManager();
public:
	/// <summary>
	/// �V�[���̎��
	/// </summary>
	enum class SCENE
	{
		TITLE,
		MAINGAME,
		RESULT
	};

	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <param name="gamePad">DIrectX::GamePad</param>
	static void CreateInstance(DirectX::GamePad* gamePad, unique_ptr<DirectX::SpriteFont>&& defaultFontHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale);

	/// <summary>
	/// �C���X�^���X�j��
	/// </summary>
	static void DestroyInstance();

	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns></returns>
	static SceneManager* GetInstance() { return m_sceneManager; }

	/// <summary>
	/// �V�[���̏�Ԏ擾
	/// </summary>
	/// <returns></returns>
	SCENE GetNowSceneState()const { return m_sceneState; }

	/// <summary>
	/// �V�[�����ς�������ǂ����擾
	/// </summary>
	/// <returns></returns>
	bool GetIsChange() { return isChange; }

	/// <summary>
	/// �V�[���̑J�ڏ���
	/// </summary>
	/// <param name="sceneState"></param>
	void ChangeScene(SCENE sceneState);

	/// <summary>
	/// �V�[���̍X�V
	/// </summary>
	/// <param name="tankManager"></param>
	void Update(TankManager* tankManager);

	/// <summary>
	/// �V�[���̕`��
	/// </summary>
	void Draw(DirectX::SpriteBatch* spriteBatch);

private:
	static SceneManager* m_sceneManager;				//�V���O���g���̃C���X�^���X
	BaseScene* m_nowScene;								//�V�[���̃C���X�^���X
	SCENE m_sceneState;									//�V�[���̏��

	DirectX::GamePad* m_gamePad;						//�Q�[���p�b�h�w���p�[�I�u�W�F�N�g

	unique_ptr<DirectX::SpriteFont> m_defaultFontHandle;//�f�t�H���g�t�H���g�n���h��

	vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_titleUI;//�^�C�g��UI
	vector<Vector2> m_titleUIPos;									   //�^�C�g��UI���W
	vector<float> m_titleUIScale;									   //�^�C�g��UI�X�P�[��

	bool isChange;										//�V�[�����ς�������ǂ���
};

