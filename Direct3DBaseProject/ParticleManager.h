#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class BlockManager;
class TankManager;
class WoodParticleManager;
class FireParticleManager;
class SceneManager;

class ParticleManager
{
public:
    /// <summary>
    /// �f�[�^�擾
    /// </summary>
    /// <param name="woodModelHandle"></param>
    /// <param name="fireParticle"></param>
    ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> fireParticle, vector<unique_ptr<DirectX::BasicEffect>>&& fireBasicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> fireInputLayout);

    /// <summary>
    /// �f�[�^�j��
    /// </summary>
    ~ParticleManager();

    /// <summary>
    /// ������
    /// </summary>
    void Init();

    /// <summary>
    /// �p�[�e�B�N���̍X�V
    /// </summary>
    /// <param name="world"></param>
    /// <param name="blockManager"></param>
    void Update(DirectX::SimpleMath::Matrix world, BlockManager* blockManager, TankManager* tankManager, SceneManager* sceneManager);

    /// <summary>
    /// �p�[�e�B�N���̕`��
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, SceneManager* sceneManager);

private:
    WoodParticleManager* m_woodParticleManager;     //�ؕЃp�[�e�B�N���}�l�[�W���[
    FireParticleManager* m_fireParticleManager;     //���p�[�e�B�N���}�l�[�W���[
};

