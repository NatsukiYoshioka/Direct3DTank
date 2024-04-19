#pragma once
#include<vector>
#include"Model.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Tank;

class TankManager
{
public:
    /// <summary>
    /// 全タンクの初期化
    /// </summary>
    /// <param name="tankModelHandle">タンクのモデルハンドル</param>
    /// <param name="pos">タンクの初期座標</param>
    TankManager(vector<unique_ptr<DirectX::Model>>&& tankModelHandle, vector<Vector3> pos);

    /// <summary>
    /// インスタンス破棄
    /// </summary>
    ~TankManager();

    /// <summary>
    /// 全タンクの更新処理
    /// </summary>
    /// <param name="world">単位行列</param>
    void Update(DirectX::SimpleMath::Matrix world);

    /// <summary>
    /// 全タンクの描画
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    static constexpr int m_player1 = 0;         //プレイヤー1のindex
    static constexpr int m_player2 = 1;         //プレイヤー2のindex
    static constexpr int m_playerNum = 2;       //プレイヤー数

    Tank* m_tank[m_playerNum];                  //各タンクのインスタンス
};

