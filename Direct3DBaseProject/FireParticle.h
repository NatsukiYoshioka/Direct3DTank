#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class FireParticle
{
public:
    /// <summary>
    /// 炎上エフェクトパーティクルの追加
    /// </summary>
    /// <param name="pos"></param>
    FireParticle(Vector3 pos);

    /// <summary>
    /// データ解放
    /// </summary>
    ~FireParticle();

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
    /// <param name="primitiveBatch"></param>
    /// <param name="basicEffect"></param>
    /// <param name="inputLayout"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, ID3D11InputLayout* inputLayout);

    /// <summary>
    /// パーティクル更新を終了するかどうか取得
    /// </summary>
    /// <returns></returns>
    bool GetIsFinish()const { return m_isFinish; }

private:
    Vector3 m_direction;        //パーティクルの動く向き
    Vector3 m_pos;              //パーティクルの座標

    bool m_isFinish;            //パーティクル更新を終了するか

    float m_maxUpVectorY;       //パーティクルの最大上昇座標
    const float m_firstHeight;  //パーティクルの最初の高さ

    static constexpr float m_minDistributionUpVectorY = 0.2f;   //最小上昇量
    static constexpr float m_maxDistributionUpVectorY = 0.6f;   //最大上昇量

    float m_upSpeed;        //上昇スピード
    static constexpr float m_minUpSpeed = 0.001f;               //最小上昇スピード
    static constexpr float m_maxUpSpeed = 0.004f;               //最大上昇スピード

    static constexpr float m_minDirection = 0.f;                //最小向き(ラジアン)
    static constexpr float m_maxDirection = 0.2f;               //最大向き

    static constexpr float m_minWidth = 0.0005f;                //生成する最小水平幅
    static constexpr float m_maxWidth = 0.0025f;                //生成する最大水平幅

    static constexpr float m_scale = 0.1f;          //パーティクルのスケール

    static constexpr float m_textureWidth = 0.3f;   //テクスチャの幅
    static constexpr float m_sponeHeight = 0.8f;    //生成する高さ
};

