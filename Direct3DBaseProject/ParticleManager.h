#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class BlockManager;
class WoodParticleManager;
class FireParticleManager;

class ParticleManager
{
public:
    /// <summary>
    /// データ取得
    /// </summary>
    /// <param name="woodModelHandle"></param>
    /// <param name="fireParticle"></param>
    ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> fireParticle);

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
    void Update(DirectX::SimpleMath::Matrix world, BlockManager* blockManager);

    /// <summary>
    /// パーティクルの描画
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    WoodParticleManager* m_woodParticleManager;     //木片パーティクルマネージャー
    FireParticleManager* m_fireParticleManager;     //炎パーティクルマネージャー
};

