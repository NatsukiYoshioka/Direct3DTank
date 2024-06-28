#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class FireParticle
{
public:
    /// <summary>
    /// ����G�t�F�N�g�p�[�e�B�N���̒ǉ�
    /// </summary>
    /// <param name="pos"></param>
    FireParticle(Vector3 pos);

    /// <summary>
    /// �f�[�^���
    /// </summary>
    ~FireParticle();

    /// <summary>
    /// �p�[�e�B�N���X�V
    /// </summary>
    void Update();

    /// <summary>
    /// �p�[�e�B�N���`��
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    /// <param name="primitiveBatch"></param>
    /// <param name="basicEffect"></param>
    /// <param name="inputLayout"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, ID3D11InputLayout* inputLayout);

    /// <summary>
    /// �p�[�e�B�N���X�V���I�����邩�ǂ����擾
    /// </summary>
    /// <returns></returns>
    bool GetIsFinish()const { return m_isFinish; }

private:
    Vector3 m_direction;        //�p�[�e�B�N���̓�������
    Vector3 m_pos;              //�p�[�e�B�N���̍��W

    bool m_isFinish;            //�p�[�e�B�N���X�V���I�����邩

    float m_maxUpVectorY;       //�p�[�e�B�N���̍ő�㏸���W
    const float m_firstHeight;  //�p�[�e�B�N���̍ŏ��̍���

    static constexpr float m_minDistributionUpVectorY = 0.2f;   //�ŏ��㏸��
    static constexpr float m_maxDistributionUpVectorY = 0.6f;   //�ő�㏸��

    float m_upSpeed;        //�㏸�X�s�[�h
    static constexpr float m_minUpSpeed = 0.001f;               //�ŏ��㏸�X�s�[�h
    static constexpr float m_maxUpSpeed = 0.004f;               //�ő�㏸�X�s�[�h

    static constexpr float m_minDirection = 0.f;                //�ŏ�����(���W�A��)
    static constexpr float m_maxDirection = 0.2f;               //�ő����

    static constexpr float m_minWidth = 0.0005f;                //��������ŏ�������
    static constexpr float m_maxWidth = 0.0025f;                //��������ő吅����

    static constexpr float m_scale = 0.1f;          //�p�[�e�B�N���̃X�P�[��

    static constexpr float m_textureWidth = 0.3f;   //�e�N�X�`���̕�
    static constexpr float m_sponeHeight = 0.8f;    //�������鍂��
};

