#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class BlockManager;
class BulletManager;
class TankManager;
class WoodParticleManager;
class ReflectionParticleManager;
class FireParticleManager;
class HitEffectManager;
class SceneManager;

class ParticleManager
{
public:
    /// <summary>
    /// �f�[�^�擾
    /// </summary>
    /// <param name="woodModelHandle"></param>
    /// <param name="fireParticle"></param>
    ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> reflectionParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitFlameParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitSmokeParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitAroundFlameParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> fireParticle, ID3D11Device* deviceResources);

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
    void Update(DirectX::SimpleMath::Matrix world, BlockManager* blockManager, BulletManager* bulletManager, TankManager* tankManager, SceneManager* sceneManager, float elapsedTime);

    /// <summary>
    /// �p�[�e�B�N���̕`��
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, SceneManager* sceneManager, ID3D11Device* deviceResources);

    /// <summary>
    /// �`��f�o�C�X�擾
    /// </summary>
    /// <returns></returns>
    BasicEffect* GetBasicEffect() { return m_basicEffect.get(); }

    /// <summary>
    /// ���C�A�E�g�擾
    /// </summary>
    /// <returns></returns>
    Microsoft::WRL::ComPtr<ID3D11InputLayout> GetInputLayout() { return m_inputLayout; }
private:
    WoodParticleManager* m_woodParticleManager;             //�ؕЃp�[�e�B�N���}�l�[�W���[
    ReflectionParticleManager* m_reflectionParticleManager; //���˃p�[�e�B�N���}�l�[�W���[
    HitEffectManager* m_hitEffectManager;                   //�q�b�g�G�t�F�N�g�Ǘ��}�l�[�W���[
    FireParticleManager* m_fireParticleManager;             //���p�[�e�B�N���}�l�[�W���[

    unique_ptr<DirectX::BasicEffect> m_basicEffect;         //�`��I�v�V�����̐ݒ�N���X
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;//�`��p���C�A�E�g�N���X
};

