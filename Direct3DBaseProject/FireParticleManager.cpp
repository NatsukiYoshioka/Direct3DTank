#include "pch.h"
#include<random>
#define _USE_MATH_DEFINES
#include"TankManager.h"
#include"Tank.h"
#include"common.h"
#include"FireParticle.h"
#include "FireParticleManager.h"

FireParticleManager::FireParticleManager(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> fireParticle, vector<unique_ptr<DirectX::BasicEffect>>&& fireBasicEffect, vector<Microsoft::WRL::ComPtr<ID3D11InputLayout>> fireInputLayout):
    m_fireBasicEffect(move(fireBasicEffect)),
    m_fireInputLayout(fireInputLayout)
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
        m_fireBasicEffect.at(i).reset();
        m_fireInputLayout.at(i).Reset();
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
                    m_fireParticles.push_back(new FireParticle(m_fireParticleHandle.at(j).Get(), j, tankManager->GetTanks().at(i)->GetPos(), m_fireBasicEffect.at(j).get(), m_fireInputLayout.at(j).Get()));
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

void FireParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch)
{
    for (int i = initializeNum; i < m_fireParticles.size(); i++)
    {
        m_fireParticles.at(i)->Draw(context, states, view, projection, primitiveBatch);
    }
}