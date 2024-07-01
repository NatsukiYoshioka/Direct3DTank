#include "pch.h"
#include"HitFlameParticle.h"
#include"HitSmokeParticle.h"
#include"AnimatedTexture.h"
#include"TankManager.h"
#include"Tank.h"
#include "HitExplosionManager.h"

HitExplosionManager::HitExplosionManager(ID3D11ShaderResourceView* hitFlameParticleHandle, ID3D11ShaderResourceView* hitSmokeParticleHandle, int framesPerSecond):
    m_hitFlameParticleHandle(hitFlameParticleHandle),
    m_hitSmokeParticleHandle(hitSmokeParticleHandle)
{
    m_hitFlameAnimatedParticleHandle = make_unique<AnimatedTexture>();
    m_hitSmokeAnimatedParticleHandle = make_unique<AnimatedTexture>();

    m_hitFlameAnimatedParticleHandle->Load(m_hitFlameParticleHandle, m_flameWarpCount, m_flameSideCount, framesPerSecond);
    m_hitSmokeAnimatedParticleHandle->Load(m_hitSmokeParticleHandle, m_smokeWarpCount, m_smokeSideCount, framesPerSecond);

    Init();
}

HitExplosionManager::~HitExplosionManager()
{
    m_hitFlameAnimatedParticleHandle.reset();
    m_hitSmokeAnimatedParticleHandle.reset();
}

void HitExplosionManager::Init()
{
    m_hitFlameParticles.clear();
    m_hitSmokeParticles.clear();
}

void  HitExplosionManager::Update(float elapsedTime, TankManager* tankManager)
{
    for (int i = initializeNum; i < tankManager->GetTanks().size(); i++)
    {
        if (tankManager->GetTanks().at(i)->GetIsHitBullet())
        {
            m_hitFlameParticles.push_back(new HitFlameParticle(m_hitFlameAnimatedParticleHandle.get(), tankManager->GetTanks().at(i)->GetPos(), i));
            m_hitSmokeParticles.push_back(new HitSmokeParticle(m_hitSmokeAnimatedParticleHandle.get(), tankManager->GetTanks().at(i)->GetPos()));
        }
    }

    for (int i = initializeNum; i < m_hitFlameParticles.size(); i++)
    {
        m_hitFlameParticles.at(i)->Update(elapsedTime, tankManager->GetTanks().at(m_hitFlameParticles.at(i)->GetTankIndex())->GetPos());
        m_hitSmokeParticles.at(i)->Update(elapsedTime, tankManager->GetTanks().at(m_hitFlameParticles.at(i)->GetTankIndex())->GetPos());
    }

    for (int i = initializeNum; i < m_hitFlameParticles.size(); i++)
    {
        if (m_hitFlameParticles.at(i)->GetIsFinish())
        {
            m_hitFlameParticles.erase(m_hitFlameParticles.begin() + i);
        }
    }

    for (int i = initializeNum; i < m_hitSmokeParticles.size(); i++)
    {
        if (m_hitSmokeParticles.at(i)->GetIsFinish())
        {
            m_hitSmokeParticles.erase(m_hitSmokeParticles.begin() + i);
        }
    }
}

void HitExplosionManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources)
{
    basicEffect->SetTexture(m_hitFlameParticleHandle);
    DX::ThrowIfFailed(CreateInputLayoutFromEffect<VertexPositionTexture>(deviceResources, basicEffect, inputLayout.ReleaseAndGetAddressOf()));
    for (int i = initializeNum; i < m_hitFlameParticles.size(); i++)
    {
        m_hitFlameParticles.at(i)->Draw(context, states, view, projection, primitiveBatch, basicEffect, inputLayout.Get());
    }

    basicEffect->SetTexture(m_hitSmokeParticleHandle);
    DX::ThrowIfFailed(CreateInputLayoutFromEffect<VertexPositionTexture>(deviceResources, basicEffect, inputLayout.ReleaseAndGetAddressOf()));
    for (int i = initializeNum; i < m_hitSmokeParticles.size(); i++)
    {
        m_hitSmokeParticles.at(i)->Draw(context, states, view, projection, primitiveBatch, basicEffect, inputLayout.Get());
    }
}