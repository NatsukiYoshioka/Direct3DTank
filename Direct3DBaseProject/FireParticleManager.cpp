#include "pch.h"
#include"common.h"
#include"FireParticle.h"
#include "FireParticleManager.h"

FireParticleManager::FireParticleManager(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> fireParticle)
{
    for (int i = initializeNum; i < fireParticle.size(); i++)
    {
        m_fireParticleHandle.push_back(fireParticle.at(i));
    }
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

void FireParticleManager::Update(DirectX::SimpleMath::Matrix world)
{

}

void FireParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{

}