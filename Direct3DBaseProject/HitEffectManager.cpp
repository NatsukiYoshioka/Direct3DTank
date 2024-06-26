#include "pch.h"
#include"AnimatedTexture.h"
#include "HitEffectManager.h"

HitEffectManager::HitEffectManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitFlameParticleHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitAroundFlameParticleHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitSmokeParticleHandle):
    m_hitFlameParticleHandle(hitFlameParticleHandle),
    m_hitAroundFlameParticleHandle(hitAroundFlameParticleHandle),
    m_hitSmokeParticleHandle(hitSmokeParticleHandle)
{
    m_hitFlameAnimatedParticleHandle = make_unique<AnimatedTexture>();
    m_hitAroundFlameAnimatedParticleHandle = make_unique<AnimatedTexture>();
    m_hitSmokeAnimatedParticleHandle = make_unique<AnimatedTexture>();

    m_hitFlameAnimatedParticleHandle->Load(m_hitFlameParticleHandle.Get(), m_flameWarpCount, m_flameSideCount, m_framesPerSecond);
    m_hitAroundFlameAnimatedParticleHandle->Load(m_hitAroundFlameParticleHandle.Get(), m_aroundFlameWarpCount, m_aroundFlameSideCount, m_framesPerSecond);
    m_hitSmokeAnimatedParticleHandle->Load(m_hitSmokeParticleHandle.Get(), m_smokeWarpCount, m_smokeSideCount, m_framesPerSecond);
}

HitEffectManager::~HitEffectManager()
{
    m_hitFlameParticleHandle.Reset();
    m_hitAroundFlameParticleHandle.Reset();
    m_hitSmokeParticleHandle.Reset();

    m_hitFlameAnimatedParticleHandle.reset();
    m_hitAroundFlameAnimatedParticleHandle.reset();
    m_hitSmokeAnimatedParticleHandle.reset();
}

void HitEffectManager::Init()
{

}

void HitEffectManager::Update()
{

}

void HitEffectManager::Draw()
{

}