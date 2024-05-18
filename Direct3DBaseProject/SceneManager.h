#pragma once

class BaseScene;
class TankManager;

class SceneManager
{
private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="gamePad">DirectX::GamePad</param>
	SceneManager(DirectX::GamePad* gamePad);

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
	static void CreateInstance(DirectX::GamePad* gamePad);

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
	void Draw();

private:
	static SceneManager* m_sceneManager;			//�V���O���g���̃C���X�^���X
	BaseScene* m_nowScene;							//�V�[���̃C���X�^���X
	SCENE m_sceneState;								//�V�[���̏��

	DirectX::GamePad* m_gamePad;					//�Q�[���p�b�h�w���p�[�I�u�W�F�N�g

	bool isChange;									//�V�[�����ς�������ǂ���
};

