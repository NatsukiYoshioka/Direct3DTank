#include "pch.h"
#include"Tank.h"
#include"common.h"
#include "TankManager.h"

TankManager::TankManager(vector<unique_ptr<DirectX::Model>>&& tankModelHandle, vector<Vector3> pos)
{
    for (int i = initializeNum; i < m_playerNum; i++)
    {
        m_tank[i] = new Tank(move(tankModelHandle.at(i)), pos.at(i));
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