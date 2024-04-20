#include "pch.h"
#include"Tank.h"
#include"common.h"
#include "TankManager.h"

TankManager::TankManager(vector<unique_ptr<DirectX::Model>>&& tankModelHandle, vector<Vector3> pos)
{
    float playerAngle[m_playerNum];
    playerAngle[m_player1] = atan2f(pos.at(m_player1).z - pos.at(m_player2).z, pos.at(m_player1).x - pos.at(m_player2).x);
    playerAngle[m_player2] = atan2f(pos.at(m_player2).z - pos.at(m_player1).z, pos.at(m_player2).x - pos.at(m_player1).x);
    for (int i = initializeNum; i < m_playerNum; i++)
    {
        m_tank[i] = new Tank(move(tankModelHandle.at(i)), pos.at(i), playerAngle[i]);
    }
}

TankManager::~TankManager()
{
    for (int i = initializeNum; i < m_playerNum; i++)
    {
        delete(m_tank[i]);
    }
}

void TankManager::Update(DirectX::SimpleMath::Matrix world)
{
    for (int i = initializeNum; i < m_playerNum; i++)
    {
        m_tank[i]->Update(world);
    }
}

void TankManager::Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    for (int i = initializeNum; i < m_playerNum; i++)
    {
        m_tank[i]->Draw(context, move(states), view, projection);
    }
}