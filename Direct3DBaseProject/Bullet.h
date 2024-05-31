#pragma once
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Bullet
{
public:
    /// <summary>
    /// 弾発射時の情報設定
    /// </summary>
    /// <param name="bulletModelHandle"></param>
    /// <param name="pos"></param>
    /// <param name="angle"></param>
    Bullet(DirectX::Model* bulletModelHandle, DirectX::SimpleMath::Vector3 pos, float angle, int bulletIndex);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Bullet();

    /// <summary>
    /// 弾の更新
    /// </summary>
    /// <param name="world"></param>
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// 弾の描画
    /// </summary>
    /// <param name="deviceContext"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* deviceContext, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    /// <summary>
    /// 弾のモデルハンドル取得
    /// </summary>
    /// <returns></returns>
    DirectX::Model* GetBulletModelHandle() { return m_bulletModelHandle; }

    /// <summary>
    /// 座標の取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetPos() { return m_pos; }

    /// <summary>
    /// ステージブロックとの当たり判定
    /// </summary>
    /// <param name="blockBox"></param>
    /// <param name="blockPos"></param>
    bool CheckHitBlock(BoundingBox blockBox, Vector3 blockPos);

    /// <summary>
    /// 弾が壊れたか取得
    /// </summary>
    /// <returns></returns>
    bool GetIsBreak() { return m_isBreak; }

    /// <summary>
    /// 弾のモデル配列の番号を取得
    /// </summary>
    /// <returns></returns>
    const int GetBulletIndex() { return m_bulletIndex; }

    /// <summary>
    /// タンクに当たった時に呼び出し
    /// </summary>
    void HitTank() { m_isBreak = true; }

private:
    DirectX::Model* m_bulletModelHandle;            //弾モデルハンドル
    const int m_bulletIndex;
    Vector3 m_pos;                                  //弾の座標
    XMMATRIX m_local;                               //弾の情報を格納した行列
    XMMATRIX m_world;
    static constexpr float m_scale = 0.1f;          //弾の大きさ
    float m_angle;                                  //弾の向き
    Vector3 m_direction;                            //弾の方向ベクトル
    static constexpr float m_speed = 0.04f;         //弾の動くスピード         

    //弾の当たり判定範囲
    static constexpr float m_boundingboxExtentsX = 0.2f;
    static constexpr float m_boundingboxExtentsY = 0.1f;
    static constexpr float m_boundingboxExtentsZ = 0.2f;

    bool m_isHitBlock;                              //ブロックと当たったかどうか
    bool m_isBreak;                                 //弾が壊れたかどうか
    int m_boundBlockCount;                          //ブロックに跳ね返った回数
    static constexpr int m_maxBoundCount = 5;       //ブロックに跳ね返る最大回数

    static constexpr float m_fireFrontWidth = 1.f;  //弾の発射幅
};

