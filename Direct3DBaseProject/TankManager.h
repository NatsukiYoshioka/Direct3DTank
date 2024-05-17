#pragma once
#include<vector>
#include"SceneManager.h"
#include"common.h"
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Tank;
class BlockManager;
class BulletManager;

class TankManager
{
public:
    /// <summary>
    /// 全タンクの初期化
    /// </summary>
    /// <param name="tankModelHandle">タンクのモデルハンドル</param>
    /// <param name="pos">タンクの初期座標</param>
    TankManager(vector<unique_ptr<DirectX::Model>>&& tankModelHandle, vector<Vector3> pos, DirectX::GamePad* gamePad);

    /// <summary>
    /// インスタンス破棄
    /// </summary>
    ~TankManager();

    /// <summary>
    /// タイトル時の初期化
    /// </summary>
    void InitTitle();

    /// <summary>
    /// メインゲームシーン時の初期化
    /// </summary>
    void InitMainGame();

    /// <summary>
    /// リザルトシーンでの初期化
    /// </summary>
    void InitResult();

    /// <summary>
    /// 全タンクの更新処理
    /// </summary>
    /// <param name="world">単位行列</param>
    void Update(DirectX::SimpleMath::Matrix world, BlockManager* blockManager, BulletManager* bulletManager, SceneManager::SCENE sceneState);

    /// <summary>
    /// 全タンクの描画
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)const;

    /// <summary>
    /// タンクの取得
    /// </summary>
    /// <returns></returns>
    vector<Tank*> GetTanks() { return m_tank; }
private:
    vector<Tank*> m_tank;                  //各タンクのインスタンス
    DirectX::GamePad* m_gamePad;   //コントローラーの状態を管理するポインタ

    static const Vector3 m_initTitleTankPos[playerNum];
    static const Vector3 m_initResultTankPos[playerNum];

    static constexpr int m_maxBulletNum = 3;            //自分がステージ上に撃てる弾の最大数
};

