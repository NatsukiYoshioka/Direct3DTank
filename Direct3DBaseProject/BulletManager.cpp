#include "pch.h"
#include"Bullet.h"
#include"Tank.h"
#include"Block.h"
#include"TankManager.h"
#include"BlockManager.h"
#include"common.h"
#include "BulletManager.h"

//インスタンス生成
BulletManager::BulletManager(vector<unique_ptr<DirectX::Model>>&& bulletModelHandle):
    m_bullets()
{
    for (int i = initializeNum; i < bulletModelHandle.size(); i++)
    {
        m_bulletModelHandle.push_back(move(bulletModelHandle.at(i)));
    }
    for (int i = initializeNum; i < m_maxBulletNum * playerNum; i++)
    {
        m_isUsedBullet[i] = false;
    }
}

//インスタンス破棄
BulletManager::~BulletManager()
{
    for (int i = initializeNum; m_bulletModelHandle.size(); i++)
    {
        m_bulletModelHandle.at(i).reset();
    }
}

//弾全体の更新
void BulletManager::Update(DirectX::SimpleMath::Matrix world, TankManager* tankManager, BlockManager* blockManager)
{
    
    for (int i = initializeNum; i < playerNum; i++)
    {
        if (tankManager->GetTanks().at(i)->GetIsFire() && tankManager->GetTanks().at(i)->GetFireRecast() >= static_cast<float>(initializeNum) && m_bullets[i].size() < m_maxBulletNum)
        {
            for (int j = initializeNum; j < m_maxBulletNum; j++)
            {
                if (!m_isUsedBullet[i * m_maxBulletNum + j])
                {
                    m_bullets[i].push_back(new Bullet(m_bulletModelHandle.at(i * m_maxBulletNum + j).get(), tankManager->GetTanks().at(i)->GetPos(), tankManager->GetTanks().at(i)->GetTurretAngle(), i * m_maxBulletNum + j));
                    m_isUsedBullet[i * m_maxBulletNum + j] = true;
                    break;
                }
            }
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
                if (blockManager->GetBlocks().at(l)->GetBlockType() != BlockManager::BlockType::YELLOW && !blockManager->GetBlocks().at(l)->GetIsDestroy())
                {
                    if (m_bullets[i][j]->CheckHitBlock(blockManager->GetBlocks().at(l)->GetModelMesh().at(initializeNum)->boundingBox, blockManager->GetBlocks().at(l)->GetPos()))
                    {
                        if (blockManager->GetBlocks().at(l)->GetBlockType() == BlockManager::BlockType::WOOD)
                        {
                            blockManager->GetBlocks().at(l)->DecreaseEndurance();
                        }
                        break;
                    }
                }
            }
        }
    }
}

void BulletManager::CheckIsBreak()
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        for (int j = initializeNum; j < m_bullets[i].size(); j++)
        {
            if (m_bullets[i][j]->GetIsBreak())
            {
                m_isUsedBullet[m_bullets[i][j]->GetBulletIndex()] = false;
                m_bullets[i].erase(m_bullets[i].begin() + j);
            }
        }
    }
}

//弾全体の描画
void BulletManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    for (int i = initializeNum; i < playerNum; i++)
    {
        for (int j = initializeNum; j < m_bullets[i].size(); j++)
        {
            m_bullets[i].at(j)->Draw(context, states, view, projection);
        }
    }
}