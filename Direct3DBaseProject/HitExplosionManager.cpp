#include "pch.h"
#include"AnimatedTexture.h"
#include "HitExplosionManager.h"

HitExplosionManager::HitExplosionManager(ID3D11ShaderResourceView* hitFlameParticleHandle, ID3D11ShaderResourceView* hitSmokeParticleHandle, int framesPerSecond)
{
    m_hitFlameAnimatedParticleHandle = make_unique<AnimatedTexture>();
    m_hitSmokeAnimatedParticleHandle = make_unique<AnimatedTexture>();

    m_hitFlameAnimatedParticleHandle->Load(hitFlameParticleHandle, m_flameWarpCount, m_flameSideCount, framesPerSecond);
    m_hitSmokeAnimatedParticleHandle->Load(hitSmokeParticleHandle, m_smokeWarpCount, m_smokeSideCount, framesPerSecond);
}

HitExplosionManager::~HitExplosionManager()
{
    m_hitFlameAnimatedParticleHandle.reset();
    m_hitSmokeAnimatedParticleHandle.reset();
}

void HitExplosionManager::Init()
{

}

void  HitExplosionManager::Update()
{

}

void HitExplosionManager::Draw()
{

}