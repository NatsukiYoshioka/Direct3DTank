#include "pch.h"
#include"HitExplosionManager.h"
#include"HitAroundEffectManager.h"
#include"AnimatedTexture.h"
#include "HitEffectManager.h"

HitEffectManager::HitEffectManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitFlameParticleHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitAroundFlameParticleHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitSmokeParticleHandle):
    m_hitFlameParticleHandle(hitFlameParticleHandle),
    m_hitAroundFlameParticleHandle(hitAroundFlameParticleHandle),
    m_hitSmokeParticleHandle(hitSmokeParticleHandle)
{
    m_hitExplosionManager = new HitExplosionManager(m_hitFlameParticleHandle.Get(), m_hitSmokeParticleHandle.Get(), m_framesPerSecond);
    m_hitAroundEffectManager = new HitAroundEffectManager(m_hitAroundFlameParticleHandle.Get(), m_framesPerSecond);
}

HitEffectManager::~HitEffectManager()
{
    delete(m_hitExplosionManager);
    delete(m_hitAroundEffectManager);

    m_hitFlameParticleHandle.Reset();
    m_hitAroundFlameParticleHandle.Reset();
    m_hitSmokeParticleHandle.Reset();
}

void HitEffectManager::Init()
{
    m_hitAroundEffectManager->Init();
}

void HitEffectManager::Update(float elapsedTime, TankManager* tankManager)
{
    m_hitAroundEffectManager->Update(elapsedTime, tankManager);
}

void HitEffectManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources)
{
    m_hitAroundEffectManager->Draw(context, states, view, projection, basicEffect, inputLayout, primitiveBatch, deviceResources);
}