#pragma once
#include"common.h"

class Bullet;
class TankManager;
class BlockManager;

using namespace DirectX;
using namespace std;

class BulletManager
{
public:
    /// <summary>
    /// インスタンス生成
    /// </summary>
    /// <param name="bulletModelHandle"></param>
    BulletManager(vector<unique_ptr<DirectX::Model>>&& bulletModelHandle);

    /// <summary>
    /// インスタンス破棄
    /// </summary>
    ~BulletManager();

    /// <summary>
    /// 弾全体の更新
    /// </summary>
    /// <param name="world">ワールド単位行列</param>
    /// <param name="tankManager">戦車管理クラス</param>
    /// <param name="blockManager">ブロック管理クラス</param>
    void Update(DirectX::SimpleMath::Matrix world, TankManager* tankManager, BlockManager* blockManager);

    /// <summary>
    /// 弾の描画
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    /// <summary>
    /// 各弾の取得
    /// </summary>
    /// <returns></returns>
    vector<Bullet*> *GetBullets() { return m_bullets; }

private:
    vector<Bullet*> m_bullets[playerNum];               //プレイヤーごとの弾のクラス配列
    vector<unique_ptr<DirectX::Model>> m_bulletModelHandle;//弾のモデルハンドル

    static constexpr int m_maxBulletNum = 3;            //自分がステージ上に撃てる弾の最大数
    static constexpr float m_maxFireRecast = 5.f;       //リキャスト時間

    bool m_isUsedBullet[m_maxBulletNum * playerNum];
};

