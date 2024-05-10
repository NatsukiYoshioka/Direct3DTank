#include "pch.h"
#include"Bullet.h"
#include"Tank.h"
#include"Block.h"
#include"TankManager.h"
#include"BlockManager.h"
#include"common.h"
#include "BulletManager.h"

BulletManager::BulletManager(vector<unique_ptr<DirectX::Model>>&& bulletModelHandle):
    m_bullets()
{
    for (int i = initializeNum; i < bulletModelHandle.size(); i++)
    {
        m_bulletModelHandle.push_back(move(bulletModelHandle.at(i)));
    }
}

BulletManager::~BulletManager()
{
    
}

void BulletManager::Update(DirectX::SimpleMath::Matrix world, TankManager* tankManager, BlockManager* blockManager)
{
    
    for (int i = initializeNum; i < playerNum; i++)
    {
        if (tankManager->GetTanks().at(i)->GetIsFire() && tankManager->GetTanks().at(i)->GetFireRecast() >= static_cast<float>(initializeNum) && m_bullets[i].size() < m_maxBulletNum)
        {
            m_bullets[i].push_back(new Bullet(m_bulletModelHandle.at(i * m_maxBulletNum + m_bullets[i].size()).get(), tankManager->GetTanks().at(i)->GetPos(), tankManager->GetTanks().at(i)->GetTurretAngle()));
        }
    }
    for (int i = initializeNum; i < playerNum; i++)
    {
        for (int j = initializeNum; j < m_bullets[i].size(); j++)
        {
            m_bullets[i].at(j)->Update(world);
        }
    }
    for (int i = initializeNum; i < playerNum; i++)
    {
        for (int j = initializeNum; j < m_bullets[i].size(); j++)
        {
            for (int l = initializeNum; l < blockManager->GetBlocks().size(); l++)
            {
                if (blockManager->GetBlocks().at(l)->GetBlockType() != BlockManager::BlockType::YELLOW)
                {
                    if (m_bullets[i][j]->CheckHitBlock(blockManager->GetBlocks().at(l)->GetModelMesh().at(initializeNum)->boundingBox, blockManager->GetBlocks().at(l)->GetPos()))
                    {
                        break;
                    }
                }
            }
        }
    }
    for (int i = initializeNum; i < playerNum; i++)
    {
        for (int j = initializeNum; j < m_bullets[i].size(); j++)
        {
            if (m_bullets[i][j]->GetIsBreak())m_bullets[i].erase(m_bullets[i].begin() + j);
        }
    }
}

void BulletManager::Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        for (int j = initializeNum; j < m_bullets[i].size(); j++)
        {
            m_bullets[i].at(j)->Draw(context, move(states), view, projection);
        }
    }
}