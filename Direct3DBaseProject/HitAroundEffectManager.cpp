#include "pch.h"
#include"AnimatedTexture.h"
#include"HitAroundFlameParticle.h"
#include"TankManager.h"
#include"Tank.h"
#include"common.h"
#include "HitAroundEffectManager.h"

HitAroundEffectManager::HitAroundEffectManager(ID3D11ShaderResourceView* hitAroundFlameParticleHandle, int framesPerSecond):
    m_hitAroundFlameParticleHandle(hitAroundFlameParticleHandle)
{
    m_hitAroundFlameAnimatedParticleHandle = make_unique<AnimatedTexture>();

    m_hitAroundFlameAnimatedParticleHandle->Load(m_hitAroundFlameParticleHandle, m_aroundFlameWarpCount, m_aroundFlameSideCount, framesPerSecond);

    Init();
}

HitAroundEffectManager::~HitAroundEffectManager()
{
    m_hitAroundFlameAnimatedParticleHandle.reset();
}

void HitAroundEffectManager::Init()
{
    m_hitAroundFlameParticles.clear();
}

void HitAroundEffectManager::Update(float elapsedTime, TankManager* tankManager)
{
    for (int i = initializeNum; i < tankManager->GetTanks().size(); i++)
    {
        if (tankManager->GetTanks().at(i)->GetIsHitBullet())
        {
            for (int j = initializeNum; j < m_particleNum; j++)
            {
                m_hitAroundFlameParticles.push_back(new HitAroundFlameParticle(m_hitAroundFlameAnimatedParticleHandle.get(), tankManager->GetTanks().at(i)->GetPos()));
            }
        }
    }

    for (int i = initializeNum; i < m_hitAroundFlameParticles.size(); i++)
    {
        m_hitAroundFlameParticles.at(i)->Update(elapsedTime);
    }

    for (int i = initializeNum; i < m_hitAroundFlameParticles.size(); i++)
    {
        if (m_hitAroundFlameParticles.at(i)->GetIsFinish())
        {
            m_hitAroundFlameParticles.erase(m_hitAroundFlameParticles.begin() + i);
        }
    }
}

void HitAroundEffectManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources)
{
    basicEffect->SetTexture(m_hitAroundFlameParticleHandle);
    DX::ThrowIfFailed(CreateInputLayoutFromEffect<VertexPositionTexture>(deviceResources, basicEffect, inputLayout.ReleaseAndGetAddressOf()));
    for (int i = initializeNum; i < m_hitAroundFlameParticles.size(); i++)
    {
        m_hitAroundFlameParticles.at(i)->Draw(context, states, view, projection, primitiveBatch, basicEffect, inputLayout.Get());
    }
}