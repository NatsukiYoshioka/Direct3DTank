#include "pch.h"
#include"BlockManager.h"
#include"TankManager.h"
#include"WoodParticleManager.h"
#include"FireParticleManager.h"
#include"common.h"
#include "ParticleManager.h"

//�f�[�^�擾
ParticleManager::ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle, vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> fireParticle)
{
    m_woodParticleManager = new WoodParticleManager(move(woodModelHandle));
    m_fireParticleManager = new FireParticleManager(fireParticle);
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
void ParticleManager::Update(DirectX::SimpleMath::Matrix world, BlockManager* blockmanager, TankManager* tankManager)
{
    m_woodParticleManager->Update(world, blockmanager);
    m_fireParticleManager->Update(world, tankManager);
}

//�p�[�e�B�N���̕`��
void ParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch)
{
    m_woodParticleManager->Draw(context, states, view, projection);
    m_fireParticleManager->Draw(context, states, view, projection, primitiveBatch);
}