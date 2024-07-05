#include "pch.h"
#include"BlockManager.h"
#include"BulletManager.h"
#include"TankManager.h"
#include"WoodParticleManager.h"
#include"ReflectionParticleManager.h"
#include"HitEffectManager.h"
#include"FireParticleManager.h"
#include"VictoryParticleManager.h"
#include"SceneManager.h"
#include"common.h"
#include "ParticleManager.h"

//データ取得
ParticleManager::ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> reflectionParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitFlameParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitSmokeParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitAroundFlameParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> fireParticle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> victoryParticle, ID3D11Device* deviceResources)
{
    m_basicEffect = make_unique<BasicEffect>(deviceResources);
    m_basicEffect->SetTextureEnabled(true);

    m_woodParticleManager = new WoodParticleManager(move(woodModelHandle));
    m_reflectionParticleManager = new ReflectionParticleManager(reflectionParticle);
    m_hitEffectManager = new HitEffectManager(hitFlameParticle, hitAroundFlameParticle, hitSmokeParticle);
    m_fireParticleManager = new FireParticleManager(fireParticle);
    m_victoryParticleManager = new VictoryParticleManager(victoryParticle);
    Init();
}

//データ破棄
ParticleManager::~ParticleManager()
{
    delete(m_woodParticleManager);
    delete(m_reflectionParticleManager);
    delete(m_hitEffectManager);
    delete(m_fireParticleManager);
    delete(m_victoryParticleManager);
    m_basicEffect.reset();
    m_inputLayout.Reset();
}

//初期化
void ParticleManager::Init()
{
    m_woodParticleManager->Init();
    m_reflectionParticleManager->Init();
    m_hitEffectManager->Init();
    m_fireParticleManager->Init();
    m_victoryParticleManager->Init();
}

//パーティクルの更新
void ParticleManager::Update(DirectX::SimpleMath::Matrix world, BlockManager* blockmanager, BulletManager* bulletManager, TankManager* tankManager, SceneManager* sceneManager, float elapsedTime)
{
    m_woodParticleManager->Update(world, blockmanager);
    if (sceneManager->GetNowSceneState() == SceneManager::SCENE::MAINGAME)
    {
        m_reflectionParticleManager->Update(bulletManager);
        m_hitEffectManager->Update(elapsedTime, tankManager);
    }
    if (sceneManager->GetNowSceneState() == SceneManager::SCENE::RESULT)
    {
        m_fireParticleManager->Update(tankManager);
        m_victoryParticleManager->Update();
    }
}

//パーティクルの描画
void ParticleManager::Draw(DirectX::SpriteBatch* spritebatch, ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, SceneManager* sceneManager, ID3D11Device* deviceResources)
{
    m_woodParticleManager->Draw(context, states, view, projection);
    if (sceneManager->GetNowSceneState() == SceneManager::SCENE::MAINGAME)
    {
        m_reflectionParticleManager->Draw(context, states, view, projection, m_basicEffect.get(), m_inputLayout, primitiveBatch, deviceResources);
        m_hitEffectManager->Draw(context, states, view, projection, m_basicEffect.get(), m_inputLayout, primitiveBatch, deviceResources);
    }
    if (sceneManager->GetNowSceneState() == SceneManager::SCENE::RESULT)
    {
        m_fireParticleManager->Draw(context, states, view, projection, m_basicEffect.get(), m_inputLayout, primitiveBatch, deviceResources);
        m_victoryParticleManager->Draw(spritebatch);
    }
}