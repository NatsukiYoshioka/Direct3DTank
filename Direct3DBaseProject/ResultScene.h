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
	ResultScene();

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
	void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch);

	/// <summary>
	/// �V�[�����I���������ǂ����擾
	/// </summary>
	/// <returns></returns>
	bool GetIsFinish() { return isFinish; }
private:
	bool isFinish;			//�V�[�����I���������ǂ���
};

