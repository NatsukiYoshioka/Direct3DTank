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
    /// データ取得
    /// </summary>
    /// <param name="woodModelHandle"></param>
    /// <param name="fireParticle"></param>
    ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> reflectionParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitFlameParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitSmokeParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitAroundFlameParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> fireParticle, ID3D11Device* deviceResources);

    /// <summary>
    /// データ破棄
    /// </summary>
    ~ParticleManager();

    /// <summary>
    /// 初期化
    /// </summary>
    void Init();

    /// <summary>
    /// パーティクルの更新
    /// </summary>
    /// <param name="world"></param>
    /// <param name="blockManager"></param>
    void Update(DirectX::SimpleMath::Matrix world, BlockManager* blockManager, BulletManager* bulletManager, TankManager* tankManager, SceneManager* sceneManager, float elapsedTime);

    /// <summary>
    /// パーティクルの描画
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, SceneManager* sceneManager, ID3D11Device* deviceResources);

    /// <summary>
    /// 描画デバイス取得
    /// </summary>
    /// <returns></returns>
    BasicEffect* GetBasicEffect() { return m_basicEffect.get(); }

    /// <summary>
    /// レイアウト取得
    /// </summary>
    /// <returns></returns>
    Microsoft::WRL::ComPtr<ID3D11InputLayout> GetInputLayout() { return m_inputLayout; }
private:
    WoodParticleManager* m_woodParticleManager;             //木片パーティクルマネージャー
    ReflectionParticleManager* m_reflectionParticleManager; //反射パーティクルマネージャー
    HitEffectManager* m_hitEffectManager;                   //ヒットエフェクト管理マネージャー
    FireParticleManager* m_fireParticleManager;             //炎パーティクルマネージャー

    unique_ptr<DirectX::BasicEffect> m_basicEffect;         //描画オプションの設定クラス
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;//描画用レイアウトクラス
};

