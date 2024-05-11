#include "pch.h"
#include"WoodParticle.h"
#include"common.h"
#include "ParticleManager.h"

ParticleManager::ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle):
    m_woodParticles()
{
    for (int i = initializeNum; i < woodModelHandle.size(); i++)
    {
        m_woodParticleModelHandle.push_back(move(woodModelHandle.at(i)));
    }
}

ParticleManager::~ParticleManager()
{

}

void ParticleManager::Update()
{

}

void ParticleManager::Draw()
{

}