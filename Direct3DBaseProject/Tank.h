#pragma once
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Tank
{
public:
    /// <summary>
    /// タンクの初期化
    /// </summary>
    /// <param name="tankModelHandle"></param>
    /// <param name="pos"></param>
    Tank(unique_ptr<DirectX::Model>&& tankModelHandle, Vector3 pos, float angle);

    /// <summary>
    /// インスタンス破棄
    /// </summary>
    ~Tank();

    /// <summary>
    /// タンク更新処理
    /// </summary>
    /// <param name="world">単位行列</param>
    void Update(DirectX::SimpleMath::Matrix world, DirectX::GamePad::State padState);

    /// <summary>
    /// タンク描画
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* deviceContext, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    /// <summary>
    /// タンクの座標取得
    /// </summary>
    /// <returns>タンク座標</returns>
    Vector3 GetPos() const { return m_pos; }

    /// <summary>
    /// 入力更新処理
    /// </summary>
    void UpdateInput(DirectX::GamePad::State padState);

private:
    unique_ptr<DirectX::Model> m_tankModelHandle;       //タンクモデルハンドル
    DirectX::ModelBone::TransformArray m_drawBones;     //タンクの描画用ボーン
    DirectX::ModelBone::TransformArray m_animBones;     //タンクのアニメーション用ボーン

    //タンクのボーンの種類
    uint32_t m_leftBackWheelBone;
    uint32_t m_rightBackWheelBone;
    uint32_t m_leftFrontWheelBone;
    uint32_t m_rightFrontWheelBone;
    uint32_t m_turretBone;
    uint32_t m_canonBone;
    uint32_t m_hatchBone;

    Vector2 m_direction;    //タンクの向きベクトル
    Vector3 m_pos;          //タンクのベクトル座標
    XMMATRIX m_local;       //タンクの行列座標
    float m_angle;          //タンクの向き
    static constexpr float m_speed = 0.01f;    //タンクのスピード

    //タンクのボーン名
    static const string m_tankBonesName;
    static const string m_leftBackWheelName;
    static const string m_rightBackWheelName;
    static const string m_leftFrontWheelName;
    static const string m_rightFrontWheelName;
    static const string m_turretName;
    static const string m_canonName;
    static const string m_hatchName;

    static constexpr float m_scale = 0.2f;
};

