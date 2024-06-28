#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class ReflectionParticle
{
public:
    /// <summary>
    /// ���˃p�[�e�B�N���̐���
    /// </summary>
    /// <param name="pos"></param>
    ReflectionParticle(Vector3 pos);

    /// <summary>
    /// �f�[�^���
    /// </summary>
    ~ReflectionParticle();

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
    /// <param name="basicEffect"></param>
    /// <param name="inputLayout"></param>
    /// <param name="primitiveBatch"></param>
    /// <param name="deviceResources"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources);

    /// <summary>
    /// �p�[�e�B�N���X�V�I�����邩�ǂ����擾
    /// </summary>
    /// <returns></returns>
    bool GetIsFinish()const { return m_isFinish; }
private:
    Vector3 m_pos;          //�p�[�e�B�N���̍��W

    float m_textureWidth;   //�p�[�e�B�N���̃e�N�X�`����

    static constexpr float m_textureWidthExpansionSpeed = 0.01f;    //�e�N�X�`���̊g��X�s�[�h
    static constexpr float m_maxTextureWidth = 0.6f;                //�e�N�X�`���̍ő啝

    bool m_isFinish;        //�p�[�e�B�N���X�V�I�����邩�ǂ���
};

