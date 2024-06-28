#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class ReflectionParticle;
class BulletManager;

class ReflectionParticleManager
{
public:
    /// <summary>
    /// ���˃p�[�e�B�N���̃}�l�[�W���[������
    /// </summary>
    /// <param name="reflectionParticleHandle"></param>
    ReflectionParticleManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> reflectionParticleHandle);

    /// <summary>
    /// �f�[�^���
    /// </summary>
    ~ReflectionParticleManager();

    /// <summary>
    /// ������
    /// </summary>
    void Init();

    /// <summary>
    /// �}�l�[�W���[�X�V
    /// </summary>
    /// <param name="bulletManager"></param>
    void Update(BulletManager* bulletManager);

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
private:
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_reflectionParticleHandle;    //�p�[�e�B�N���̃e�N�X�`���n���h��
    vector<ReflectionParticle*> m_reflectionParticles;          //�p�[�e�B�N���̃C���X�^���X
};

