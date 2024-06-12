#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class WoodParticle
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="woodParticleModelHandle"></param>
    /// <param name="pos"></param>
    WoodParticle(DirectX::Model* woodParticleModelHandle, Vector3 pos);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~WoodParticle();

    /// <summary>
    /// パーティクル更新
    /// </summary>
    /// <param name="world"></param>
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// パーティクル描画
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    DirectX::Model* m_woodParticleModelHandle;      //木パーティクルモデルハンドル
    Vector3 m_pos;                                  //パーティクル座標
    Matrix m_world;                                 
    Matrix m_local;                                 //パーティクルの行列座標
    float m_degree;                                 //パーティクルの角度
    Vector3 m_direction;                            //パーティクルの飛ぶ方向

    float m_upPower;                                //上に飛ぶ量

    static constexpr float m_scale = 0.075f;        //パーティクルのスケール
    static constexpr float m_speed = 0.005f;        //パーティクルの水平移動速度

    static constexpr float m_minDirection = 0.f;    //飛ぶ水平方向の最小
    static constexpr float m_maxDirection = 2.f;    //飛ぶ水平方向の最大

    static constexpr float m_minUpPower = 0.01f;    //上方向の最小力量
    static constexpr float m_maxUpPower = 0.04f;    //上方向の最大力量
    static constexpr float m_decreaseY = 0.001f;    //Y軸減少速度
    static constexpr float m_minY = 0.5f;           //パーティクルが落ちる限界Y軸

    static constexpr float m_rotationSpeed = 10.f;  //パーティクルの回転速度
};

