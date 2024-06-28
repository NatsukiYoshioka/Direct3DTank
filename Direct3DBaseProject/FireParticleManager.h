#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class FireParticle;
class TankManager;

class FireParticleManager
{
public:
    /// <summary>
    /// �}�l�[�W���[�̏�����
    /// </summary>
    /// <param name="fireParticle"></param>
    FireParticleManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> fireParticle);

    /// <summary>
    /// �f�[�^���
    /// </summary>
    ~FireParticleManager();

    /// <summary>
    /// ������
    /// </summary>
    void Init();

    /// <summary>
    /// �}�l�[�W���[�X�V
    /// </summary>
    /// <param name="tankManager"></param>
    void Update(TankManager* tankManager);

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
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fireParticleHandle;      //�p�[�e�B�N���̃n���h��
    vector<FireParticle*> m_fireParticles;                                      //�p�[�e�B�N���̃C���X�^���X

    vector<bool> m_isUseParticle;               //�p�[�e�B�N�����g�p���Ă��邩�ǂ���
        
    static constexpr int m_particleSize = 30;   //�p�[�e�B�N���`�搔
};

