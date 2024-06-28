#include "pch.h"
#include"AnimatedTexture.h"
#include "HitAroundEffectManager.h"

HitAroundEffectManager::HitAroundEffectManager(ID3D11ShaderResourceView* hitAroundFlameParticleHandle, int framesPerSecond)
{
    m_hitAroundFlameAnimatedParticleHandle = make_unique<AnimatedTexture>();

    m_hitAroundFlameAnimatedParticleHandle->Load(hitAroundFlameParticleHandle, m_aroundFlameWarpCount, m_aroundFlameSideCount, framesPerSecond);
}

HitAroundEffectManager::~HitAroundEffectManager()
{
    m_hitAroundFlameAnimatedParticleHandle.reset();
}

void HitAroundEffectManager::Init()
{

}

void HitAroundEffectManager::Update()
{

}

void HitAroundEffectManager::Draw()
{
    
}