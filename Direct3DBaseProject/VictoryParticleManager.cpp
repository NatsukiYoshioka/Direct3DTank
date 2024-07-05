#include "pch.h"
#include"VictoryParticle.h"
#include"common.h"
#include "VictoryParticleManager.h"

VictoryParticleManager::VictoryParticleManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> victoryParticleHandle):
    m_victoryParticleHandle(victoryParticleHandle)
{
    Init();
}

VictoryParticleManager::~VictoryParticleManager()
{
    m_victoryParticleHandle.Reset();
}

void VictoryParticleManager::Init()
{
    m_victoryParticles.clear();
}

void VictoryParticleManager::Update()
{
    for (int i = initializeNum; i < m_particleNum; i++)
    {
        if (m_victoryParticles.size() < m_particleNum)
        {
            m_victoryParticles.push_back(new VictoryParticle(m_victoryParticleHandle.Get()));
        }
        else break;
    }

    for (int i = initializeNum; i < m_victoryParticles.size(); i++)
    {
        m_victoryParticles.at(i)->Update();
    }

    for (int i = initializeNum; i < m_victoryParticles.size(); i++)
    {
        if (m_victoryParticles.at(i)->GetIsFinish())
        {
            m_victoryParticles.erase(m_victoryParticles.begin() + i);
        }
    }
}

void VictoryParticleManager::Draw(DirectX::SpriteBatch* spritebatch)
{
    for (int i = initializeNum; i < m_victoryParticles.size(); i++)
    {
        m_victoryParticles.at(i)->Draw(spritebatch);
    }
}
