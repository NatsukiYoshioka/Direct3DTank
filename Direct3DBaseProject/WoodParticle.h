#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class WoodParticle
{
public:
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="woodParticleModelHandle"></param>
    /// <param name="pos"></param>
    WoodParticle(DirectX::Model* woodParticleModelHandle, Vector3 pos);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~WoodParticle();

    /// <summary>
    /// �p�[�e�B�N���X�V
    /// </summary>
    /// <param name="world"></param>
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// �p�[�e�B�N���`��
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    DirectX::Model* m_woodParticleModelHandle;      //�؃p�[�e�B�N�����f���n���h��
    Vector3 m_pos;                                  //�p�[�e�B�N�����W
    Matrix m_world;                                 
    Matrix m_local;                                 //�p�[�e�B�N���̍s����W
    float m_degree;                                 //�p�[�e�B�N���̊p�x
    Vector3 m_direction;                            //�p�[�e�B�N���̔�ԕ���

    float m_upPower;                                //��ɔ�ԗ�

    static constexpr float m_scale = 0.075f;        //�p�[�e�B�N���̃X�P�[��
    static constexpr float m_speed = 0.005f;        //�p�[�e�B�N���̐����ړ����x

    static constexpr float m_minDirection = 0.f;    //��Ԑ��������̍ŏ�
    static constexpr float m_maxDirection = 2.f;    //��Ԑ��������̍ő�

    static constexpr float m_minUpPower = 0.01f;    //������̍ŏ��͗�
    static constexpr float m_maxUpPower = 0.04f;    //������̍ő�͗�
    static constexpr float m_decreaseY = 0.001f;    //Y���������x
    static constexpr float m_minY = 0.5f;           //�p�[�e�B�N������������EY��

    static constexpr float m_rotationSpeed = 10.f;  //�p�[�e�B�N���̉�]���x
};

