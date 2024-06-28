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
    /// マネージャーの初期化
    /// </summary>
    /// <param name="fireParticle"></param>
    FireParticleManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> fireParticle);

    /// <summary>
    /// データ解放
    /// </summary>
    ~FireParticleManager();

    /// <summary>
    /// 初期化
    /// </summary>
    void Init();

    /// <summary>
    /// マネージャー更新
    /// </summary>
    /// <param name="tankManager"></param>
    void Update(TankManager* tankManager);

    /// <summary>
    /// パーティクル描画
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
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fireParticleHandle;      //パーティクルのハンドル
    vector<FireParticle*> m_fireParticles;                                      //パーティクルのインスタンス

    vector<bool> m_isUseParticle;               //パーティクルを使用しているかどうか
        
    static constexpr int m_particleSize = 30;   //パーティクル描画数
};

