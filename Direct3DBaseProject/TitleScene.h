#pragma once

class BaseScene;

class TitleScene:public BaseScene
{
public:
	/// <summary>
	/// �^�C�g���V�[���̐���
	/// </summary>
	TitleScene();

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
	void Draw();

	/// <summary>
	/// �V�[�����I���������ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	bool isFinish;			//�V�[�����I���������ǂ���
};

