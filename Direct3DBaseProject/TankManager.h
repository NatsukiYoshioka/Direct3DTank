#pragma once
#include<vector>
#include"common.h"
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
    TankManager(vector<unique_ptr<DirectX::Model>>&& tankModelHandle, unique_ptr<DirectX::Model>&& bulletModelHandle, vector<Vector3> pos);

    /// <summary>
    /// インスタンス破棄
    /// </summary>
    ~TankManager();

    /// <summary>
    /// 全タンクの更新処理
    /// </summary>
    /// <param name="world">単位行列</param>
    void Update(DirectX::SimpleMath::Matrix world)const;

    /// <summary>
    /// 全タンクの描画
    /// </summary>
    /// <param name="context"></param>
    /// <param name="states"></param>
    /// <param name="view"></param>
    /// <param name="projection"></param>
    void Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)const;

    /// <summary>
    /// コントローラーの中断処理
    /// </summary>
    void SuspendGamePad();

    /// <summary>
    /// コントローラーの再開処理
    /// </summary>
    void ResumeGamePad();
private:
    Tank* m_tank[playerNum];                  //各タンクのインスタンス
    unique_ptr<DirectX::Model> m_bulletModelHandle; //弾のモデルハンドル
    unique_ptr<DirectX::GamePad> m_gamePad;   //コントローラーの状態を管理するポインタ
};

