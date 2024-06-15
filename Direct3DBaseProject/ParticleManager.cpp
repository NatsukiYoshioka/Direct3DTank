#include "pch.h"
#include"BlockManager.h"
#include"TankManager.h"
#include"WoodParticleManager.h"
#include"FireParticleManager.h"
#include"SceneManager.h"
#include"common.h"
#include "ParticleManager.h"

//�f�[�^�擾
ParticleManager::ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> fireParticle, vector<unique_ptr<DirectX::BasicEffect>>&& fireBasicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> fireInputLayout)
{
    m_woodParticleManager = new WoodParticleManager(move(woodModelHandle));
    m_fireParticleManager = new FireParticleManager(fireParticle, move(fireBasicEffect), fireInputLayout);
    Init();
}

//�f�[�^�j��
ParticleManager::~ParticleManager()
{
    delete(m_woodParticleManager);
    delete(m_fireParticleManager);
}

//������
void ParticleManager::Init()
{
    m_woodParticleManager->Init();
    m_fireParticleManager->Init();
}

//�p�[�e�B�N���̍X�V
void ParticleManager::Update(DirectX::SimpleMath::Matrix world, BlockManager* blockmanager, TankManager* tankManager, SceneManager* sceneManager)
{
    m_woodParticleManager->Update(world, blockmanager);
    if (sceneManager->GetNowSceneState() == SceneManager::SCENE::RESULT)m_fireParticleManager->Update(world, tankManager);
}

//�p�[�e�B�N���̕`��
void ParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, SceneManager* sceneManager)
{
    m_woodParticleManager->Draw(context, states, view, projection);
    if (sceneManager->GetNowSceneState() == SceneManager::SCENE::RESULT)
    {
        primitiveBatch->Begin();
        m_fireParticleManager->Draw(context, states, view, projection, primitiveBatch);
        primitiveBatch->End();
    }
}