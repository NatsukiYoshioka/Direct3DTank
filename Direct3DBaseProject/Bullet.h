#pragma once
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Bullet
{
public:
    /// <summary>
    /// �e���ˎ��̏��ݒ�
    /// </summary>
    /// <param name="bulletModelHandle"></param>
    /// <param name="pos"></param>
    /// <param name="angle"></param>
    Bullet(DirectX::Model* bulletModelHandle, DirectX::SimpleMath::Vector3 pos, float angle);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Bullet();

    /// <summary>
    /// �e�̍X�V
    /// </summary>
    /// <param name="world"></param>
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// �e�̕`��
    /// </summary>
    /// <param name="deviceContext"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* deviceContext, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    DirectX::Model* m_bulletModelHandle;            //�e���f���n���h��
    Vector3 m_pos;                                  //�e�̍��W
    XMMATRIX m_local;                               //�e�̏����i�[�����s��
    static constexpr float m_scale = 0.1f;          //�e�̑傫��
    float m_angle;                                  //�e�̌���
    Vector3 m_direction;                            //�e�̕����x�N�g��
    static constexpr float m_speed = 0.02f;         //�e�̓����X�s�[�h                
};

