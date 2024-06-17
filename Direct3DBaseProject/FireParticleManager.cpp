#include "pch.h"
#include<random>
#define _USE_MATH_DEFINES
#include"TankManager.h"
#include"Tank.h"
#include"common.h"
#include"FireParticle.h"
#include "FireParticleManager.h"

FireParticleManager::FireParticleManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> fireParticle):
    m_fireParticleHandle(fireParticle)
{
    m_isUseParticle.assign(m_particleSize, false);
}

FireParticleManager::~FireParticleManager()
{
    m_fireParticleHandle.Reset();
}

void FireParticleManager::Init()
{
    m_fireParticles.clear();
    m_isUseParticle.assign(m_particleSize, false);
}

void FireParticleManager::Update(DirectX::SimpleMath::Matrix world, TankManager* tankmanager)
{
    auto tankManager = tankmanager;
    int tankIndex;
    for (int i = initializeNum; i < tankManager->GetTanks().size(); i++)
    {
        if (tankManager->GetTanks().at(i)->GetIsBreak())
        {
            tankIndex = i;
            for (int j = initializeNum; j < m_particleSize; j++)
            {
                if (!m_isUseParticle.at(j))
                {
                    m_fireParticles.push_back(new FireParticle(m_fireParticleHandle.Get(), j, tankManager->GetTanks().at(tankIndex)->GetPos()));
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
            m_fireParticles.erase(m_fireParticles.begin() + i);
        }
    }
}

void FireParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources)
{
    basicEffect->SetTexture(m_fireParticleHandle.Get());
    DX::ThrowIfFailed(CreateInputLayoutFromEffect<VertexPositionTexture>(deviceResources, basicEffect, inputLayout.ReleaseAndGetAddressOf()));
    for (int i = initializeNum; i < m_fireParticles.size(); i++)
    {
        m_fireParticles.at(i)->Draw(context, states, view, projection, primitiveBatch, basicEffect, inputLayout.Get());
    }
}