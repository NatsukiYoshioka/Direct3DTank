#include "pch.h"
#include"Tank.h"
#include"common.h"
#include "TankManager.h"

//全タンクの初期化
TankManager::TankManager(vector<unique_ptr<DirectX::Model>>&& tankModelHandle, vector<Vector3> pos):
    m_gamePad(make_unique<GamePad>())
{
    float playerAngle[playerNum];
    playerAngle[player1] = atan2f(pos.at(player1).z - pos.at(player2).z, pos.at(player1).x - pos.at(player2).x);
    playerAngle[player2] = atan2f(pos.at(player2).z - pos.at(player1).z, pos.at(player2).x - pos.at(player1).x);
    for (int i = initializeNum; i < playerNum; i++)
    {
        m_tank[i] = new Tank(move(tankModelHandle.at(i)), pos.at(i), playerAngle[i]);
    }
}

//インスタンス破棄
TankManager::~TankManager()
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        delete(m_tank[i]);
    }
}

//全タンクの更新
void TankManager::Update(DirectX::SimpleMath::Matrix world) const
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        m_tank[i]->Update(world, m_gamePad->GetState(i));
    }
}

//全タンクの描画
void TankManager::Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) const
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        m_tank[i]->Draw(context, move(states), view, projection);
    }
}

//コントローラーの中断処理
void TankManager::SuspendGamePad()
{
    m_gamePad->Suspend();
}

//コントローラーの再開処理
void TankManager::ResumeGamePad()
{
    m_gamePad->Resume();
}