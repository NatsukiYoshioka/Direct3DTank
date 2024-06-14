#include "pch.h"
#include"TankManager.h"
#include"Tank.h"
#include"common.h"
#include"FireParticle.h"
#include "FireParticleManager.h"

FireParticleManager::FireParticleManager(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> fireParticle)
{
    for (int i = initializeNum; i < fireParticle.size(); i++)
    {
        m_fireParticleHandle.push_back(fireParticle.at(i));
    }
    m_isUseParticle.assign(m_fireParticleHandle.size(), false);
}

FireParticleManager::~FireParticleManager()
{
    for (int i = initializeNum; i < m_fireParticleHandle.size(); i++)
    {
        m_fireParticleHandle.at(i).Reset();
    }
}

void FireParticleManager::Init()
{
    m_fireParticles.clear();
}

void FireParticleManager::Update(DirectX::SimpleMath::Matrix world, TankManager* tankmanager)
{
    auto tankManager = tankmanager;
    for (int i = initializeNum; i < tankManager->GetTanks().size(); i++)
    {
        if (tankManager->GetTanks().at(i)->GetIsBreak())
        {
            for (int j = initializeNum; j < m_fireParticleHandle.size(); j++)
            {
                if (!m_isUseParticle.at(j))
                {
                    m_fireParticles.push_back(new FireParticle(m_fireParticleHandle.at(j).Get(), j, tankManager->GetTanks().at(i)->GetPos()));
                    m_isUseParticle.at(j) = true;
                }
            }
            break;
        }
    }

    for (int i = initializeNum; i < m_fireParticles.size(); i++)
    {
        m_fireParticles.at(i)->Update(world);
    }

    for (int i = initializeNum; i < m_fireParticles.size(); i++)
    {
        if (m_fireParticles.at(i)->GetIsFinish())
        {
            m_isUseParticle.at(m_fireParticles.at(i)->GetHandleIndex()) = false;
        }
    }
}

void FireParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch)
{
    for (int i = initializeNum; i < m_fireParticles.size(); i++)
    {
        m_fireParticles.at(i)->Draw(context, states, view, projection, primitiveBatch);
    }
}