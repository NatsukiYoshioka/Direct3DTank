#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class ReflectionParticle
{
public:
    /// <summary>
    /// 反射パーティクルの生成
    /// </summary>
    /// <param name="pos"></param>
    ReflectionParticle(Vector3 pos);

    /// <summary>
    /// データ解放
    /// </summary>
    ~ReflectionParticle();

    /// <summary>
    /// パーティクル更新
    /// </summary>
    void Update();

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

    /// <summary>
    /// パーティクル更新終了するかどうか取得
    /// </summary>
    /// <returns></returns>
    bool GetIsFinish()const { return m_isFinish; }
private:
    Vector3 m_pos;          //パーティクルの座標

    float m_textureWidth;   //パーティクルのテクスチャ幅

    static constexpr float m_textureWidthExpansionSpeed = 0.01f;    //テクスチャの拡大スピード
    static constexpr float m_maxTextureWidth = 0.6f;                //テクスチャの最大幅

    bool m_isFinish;        //パーティクル更新終了するかどうか
};

