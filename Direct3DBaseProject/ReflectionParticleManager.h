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
    /// 反射パーティクルのマネージャー初期化
    /// </summary>
    /// <param name="reflectionParticleHandle"></param>
    ReflectionParticleManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> reflectionParticleHandle);

    /// <summary>
    /// データ解放
    /// </summary>
    ~ReflectionParticleManager();

    /// <summary>
    /// 初期化
    /// </summary>
    void Init();

    /// <summary>
    /// マネージャー更新
    /// </summary>
    /// <param name="bulletManager"></param>
    void Update(BulletManager* bulletManager);

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
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_reflectionParticleHandle;    //パーティクルのテクスチャハンドル
    vector<ReflectionParticle*> m_reflectionParticles;          //パーティクルのインスタンス
};

