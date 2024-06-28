#include "pch.h"
#include"BulletManager.h"
#include"Bullet.h"
#include"ReflectionParticle.h"
#include"common.h"
#include "ReflectionParticleManager.h"

//反射パーティクルのマネージャー初期化
ReflectionParticleManager::ReflectionParticleManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> reflectionParticleHandle):
    m_reflectionParticleHandle(reflectionParticleHandle)
{
    Init();
}

//データ解放
ReflectionParticleManager::~ReflectionParticleManager()
{
    m_reflectionParticleHandle.Reset();
}

//初期化
void ReflectionParticleManager::Init()
{
    m_reflectionParticles.clear();
}

//マネージャー更新
void ReflectionParticleManager::Update(BulletManager* bulletManager)
{
    //ブロックに弾が当たったらパーティクル生成
    for (int i = initializeNum; i < bulletManager->GetBullets()->size(); i++)
    {
        if (bulletManager->GetBullets()->at(i)->GetIsHitBlock())
        {
            m_reflectionParticles.push_back(new ReflectionParticle(bulletManager->GetBullets()->at(i)->GetPos()));
        }
    }

    //パーティクル更新
    for (int i = initializeNum; i < m_reflectionParticles.size(); i++)
    {
        m_reflectionParticles.at(i)->Update();
    }

    //パーティクル削除
    for (int i = initializeNum; i < m_reflectionParticles.size(); i++)
    {
        if (m_reflectionParticles.at(i)->GetIsFinish())
        {
            m_reflectionParticles.erase(m_reflectionParticles.begin() + i);
        }
    }
}

//パーティクル描画
void ReflectionParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources)
{
    basicEffect->SetTexture(m_reflectionParticleHandle.Get());
    DX::ThrowIfFailed(CreateInputLayoutFromEffect<VertexPositionTexture>(deviceResources, basicEffect, inputLayout.ReleaseAndGetAddressOf()));
    for (int i = initializeNum; i < m_reflectionParticles.size(); i++)
    {
        m_reflectionParticles.at(i)->Draw(context, states, view, projection, basicEffect, inputLayout, primitiveBatch, deviceResources);
    }
}