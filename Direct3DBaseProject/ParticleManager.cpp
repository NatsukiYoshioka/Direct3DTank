#include "pch.h"
#include"WoodParticle.h"
#include"BlockManager.h"
#include"Block.h"
#include"common.h"
#include "ParticleManager.h"

ParticleManager::ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle):
    m_woodParticles()
{
    for (int i = initializeNum; i < woodModelHandle.size(); i++)
    {
        m_woodParticleModelHandle.push_back(move(woodModelHandle.at(i)));
    }
    m_isUseWoodParticle.assign(m_woodParticleModelHandle.size(), false);
}

ParticleManager::~ParticleManager()
{
    for (int i = initializeNum; i < m_woodParticleModelHandle.size(); i++)
    {
        m_woodParticleModelHandle.at(i).reset();
    }
}

void ParticleManager::Update(DirectX::SimpleMath::Matrix world, BlockManager* blockmanager)
{
    auto blockManager = blockmanager;
    auto blockNum = blockManager->GetWoodBlockNum();
    int woodIndex = initializeNum;
    for (int i = initializeNum; i < blockManager->GetBlocks().size(); i++)
    {
        if (blockManager->GetBlocks().at(i)->GetBlockType() == BlockManager::BlockType::WOOD&& blockManager->GetBlocks().at(i)->GetIsDestroy())
        {
            for (int j = initializeNum; j < m_woodParticleModelHandle.size() / blockNum; j++)
            {
                if (!m_isUseWoodParticle.at(woodIndex * (m_woodParticleModelHandle.size() / blockNum) + j))
                {
                    m_woodParticles.push_back(new WoodParticle(m_woodParticleModelHandle.at(woodIndex * (m_woodParticleModelHandle.size() / blockNum) + j).get(), blockManager->GetBlocks().at(i)->GetPos()));
                    m_isUseWoodParticle.at(woodIndex * (m_woodParticleModelHandle.size() / blockNum) + j) = true;
                }
            }
            woodIndex++;
        }
    }

    for (int i = initializeNum; i < m_woodParticles.size(); i++)
    {
        m_woodParticles.at(i)->Update(world);
    }
}

void ParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    for (int i = initializeNum; i < m_woodParticles.size(); i++)
    {
        m_woodParticles.at(i)->Draw(context, states, view, projection);
    }
}