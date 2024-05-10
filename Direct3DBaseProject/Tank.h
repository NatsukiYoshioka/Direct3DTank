#pragma once
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Bullet;

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

    /// <summary>
    /// アニメーション更新
    /// </summary>
    void UpdateAnimation();

    /// <summary>
    /// 弾の発射更新処理
    /// </summary>
    void UpdateBullets(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// ブロックとの当たり判定
    /// </summary>
    /// <param name="blockBox"></param>
    void CheckHitBlock(BoundingBox blockBox, Vector3 blockPos);

    /// <summary>
    /// 弾との当たり判定
    /// </summary>
    /// <param name="bulletBox"></param>
    /// <param name="bulletPos"></param>
    bool CheckHitBullet(BoundingBox bulletBox, Vector3 bulletPos);

    /// <summary>
    /// 座標の取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetPos() { return m_pos; }

    /// <summary>
    /// タンクのタレットのアングルを取得
    /// </summary>
    /// <returns></returns>
    float GetTurretAngle() { return m_turretRotation; }

    /// <summary>
    /// 弾の発射リキャスト時間取得
    /// </summary>
    /// <returns></returns>
    float GetFireRecast() { return m_fireRecast; }

    /// <summary>
    /// 撃ったかどうか取得
    /// </summary>
    /// <returns></returns>
    bool GetIsFire() { return m_isFire; }

    int GetHP() { return m_hp; }

private:
    int m_hp;
    static constexpr int m_maxHp = 5;

    float m_fireRecast;                                 //弾を再度打てるようになるまでの時間
    static constexpr float m_maxFireRecast = 2.5f;       //リキャスト時間
    static constexpr float m_recastSpeed = 0.01f;        //リキャストクールタイムスピード

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
    XMMATRIX m_world;        
    XMMATRIX m_local;       //タンクの行列座標
    XMMATRIX m_hitLocal;    //ブロックに当たった時の行列
    float m_angle;          //タンクの向き
    static constexpr float m_speed = 0.02f;    //タンクのスピード

    bool m_isMove;            //動いているかどうか
    bool m_isMoveLeft;        //タレットが左に動いたか
    bool m_isMoveRight;       //タレットが右に動いたか
    bool m_isFire;            //弾を発射したかどうか
    bool m_isHitBlock;        //ブロックと当たったかどうか
    bool m_isHitBullet;       //弾と当たったかどうか
    static constexpr float m_wheelRotationSpeed = 5.f;  //タンクのホイールの回転スピード
    float m_turretRotation;                             //タレットの回転値
    static constexpr float m_turretRotationSpeed = 0.05f; //タンクのタレットの回転スピード

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
    static constexpr float m_boundingboxExtents = 0.5f;
};

