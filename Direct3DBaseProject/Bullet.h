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
    Bullet(DirectX::Model* bulletModelHandle, DirectX::SimpleMath::Vector3 pos, float angle);

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
    void Draw(ID3D11DeviceContext1* deviceContext, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    DirectX::Model* m_bulletModelHandle;            //弾モデルハンドル
    Vector3 m_pos;                                  //弾の座標
    XMMATRIX m_local;                               //弾の情報を格納した行列
    static constexpr float m_scale = 0.1f;          //弾の大きさ
    float m_angle;                                  //弾の向き
    Vector3 m_direction;                            //弾の方向ベクトル
    static constexpr float m_speed = 0.02f;         //弾の動くスピード                
};

