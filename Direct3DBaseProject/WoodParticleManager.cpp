#include "pch.h"
#include"common.h"
#include"BlockManager.h"
#include"Block.h"
#include"WoodParticle.h"
#include "WoodParticleManager.h"

//初期化とデータの取得
WoodParticleManager::WoodParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle)
{
    for (int i = initializeNum; i < woodModelHandle.size(); i++)
    {
        m_woodParticleModelHandle.push_back(move(woodModelHandle.at(i)));
    }
}

//データ解放
WoodParticleManager::~WoodParticleManager()
{
    for (int i = initializeNum; i < m_woodParticleModelHandle.size(); i++)
    {
        m_woodParticleModelHandle.at(i).reset();
    }
}

//初期化
void WoodParticleManager::Init()
{
    m_woodParticles.clear();
    m_woodIndex = initializeNum;
    m_isUseWoodParticle.assign(m_woodParticleModelHandle.size(), false);
    m_isSponeWoodParticle.assign(mapSize * mapSize, false);
}

//パーティクルの更新
void WoodParticleManager::Update(DirectX::SimpleMath::Matrix world, BlockManager* blockmanager)
{
    auto blockManager = blockmanager;
    auto blockNum = blockManager->GetWoodBlockNum();
    for (int i = initializeNum; i < blockManager->GetBlocks().size(); i++)
    {
        if (blockManager->GetBlocks().at(i)->GetBlockType() == BlockManager::BlockType::WOOD && blockManager->GetBlocks().at(i)->GetIsDestroy())
        {
            if (!m_isSponeWoodParticle.at(i))
            {
                m_isSponeWoodParticle.at(i) = true;
                for (int j = initializeNum; j < m_woodParticleModelHandle.size() / blockNum; j++)
                {
                    if (!m_isUseWoodParticle.at(m_woodIndex * (m_woodParticleModelHandle.size() / blockNum) + j))
                    {
                        m_woodParticles.push_back(new WoodParticle(m_woodParticleModelHandle.at(m_woodIndex * (m_woodParticleModelHandle.size() / blockNum) + j).get(), blockManager->GetBlocks().at(i)->GetPos()));
                        m_isUseWoodParticle.at(m_woodIndex * (m_woodParticleModelHandle.size() / blockNum) + j) = true;
                    }
                }
                m_woodIndex++;
            }
        }
    }

    for (int i = initializeNum; i < m_woodParticles.size(); i++)
    {
        m_woodParticles.at(i)->Update(world);
    }
}

//パーティクルの描画
void WoodParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    for (int i = initializeNum; i < m_woodParticles.size(); i++)
    {
        m_woodParticles.at(i)->Draw(context, states, view, projection);
    }
}