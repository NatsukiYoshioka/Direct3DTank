#pragma once

class BaseScene;

class MainGameScene:public BaseScene
{
public:
	/// <summary>
	/// ���C���Q�[���V�[������
	/// </summary>
	MainGameScene();

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
	void Draw();

	/// <summary>
	/// �V�[�����I���������ǂ����擾
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	bool isFinish;		//�V�[�����I���������ǂ���
};

