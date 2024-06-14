#include "pch.h"
#include"BlockManager.h"
#include"TankManager.h"
#include"WoodParticleManager.h"
#include"FireParticleManager.h"
#include"common.h"
#include "ParticleManager.h"

//データ取得
ParticleManager::ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> fireParticle)
{
    m_woodParticleManager = new WoodParticleManager(move(woodModelHandle));
    m_fireParticleManager = new FireParticleManager(fireParticle);
    Init();
}

//データ破棄
ParticleManager::~ParticleManager()
{
    delete(m_woodParticleManager);
    delete(m_fireParticleManager);
}

//初期化
void ParticleManager::Init()
{
    m_woodParticleManager->Init();
    m_fireParticleManager->Init();
}

//パーティクルの更新
void ParticleManager::Update(DirectX::SimpleMath::Matrix world, BlockManager* blockmanager, TankManager* tankManager)
{
    m_woodParticleManager->Update(world, blockmanager);
    m_fireParticleManager->Update(world, tankManager);
}

//パーティクルの描画
void ParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch)
{
    m_woodParticleManager->Draw(context, states, view, projection);
    m_fireParticleManager->Draw(context, states, view, projection, primitiveBatch);
}