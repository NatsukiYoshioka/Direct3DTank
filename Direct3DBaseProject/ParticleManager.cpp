#include "pch.h"
#include"BlockManager.h"
#include"TankManager.h"
#include"WoodParticleManager.h"
#include"FireParticleManager.h"
#include"SceneManager.h"
#include"common.h"
#include "ParticleManager.h"

//データ取得
ParticleManager::ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> fireParticle, ID3D11Device* deviceResources)
{
    m_basicEffect = make_unique<BasicEffect>(deviceResources);
    m_basicEffect->SetTextureEnabled(true);

    m_woodParticleManager = new WoodParticleManager(move(woodModelHandle));
    m_fireParticleManager = new FireParticleManager(fireParticle);
    Init();
}

//データ破棄
ParticleManager::~ParticleManager()
{
    delete(m_woodParticleManager);
    delete(m_fireParticleManager);
    m_basicEffect.reset();
    m_inputLayout.Reset();
}

//初期化
void ParticleManager::Init()
{
    m_woodParticleManager->Init();
    m_fireParticleManager->Init();
}

//パーティクルの更新
void ParticleManager::Update(DirectX::SimpleMath::Matrix world, BlockManager* blockmanager, TankManager* tankManager, SceneManager* sceneManager)
{
    m_woodParticleManager->Update(world, blockmanager);
    if (sceneManager->GetNowSceneState() == SceneManager::SCENE::RESULT)m_fireParticleManager->Update(world, tankManager);
}

//パーティクルの描画
void ParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, SceneManager* sceneManager, ID3D11Device* deviceResources)
{
    m_woodParticleManager->Draw(context, states, view, projection);
    if (sceneManager->GetNowSceneState() == SceneManager::SCENE::RESULT)
    {
        m_fireParticleManager->Draw(context, states, view, projection, m_basicEffect.get(), m_inputLayout, primitiveBatch, deviceResources);
    }
}