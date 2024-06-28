#include "pch.h"
#include"BulletManager.h"
#include"Bullet.h"
#include"ReflectionParticle.h"
#include"common.h"
#include "ReflectionParticleManager.h"

//���˃p�[�e�B�N���̃}�l�[�W���[������
ReflectionParticleManager::ReflectionParticleManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> reflectionParticleHandle):
    m_reflectionParticleHandle(reflectionParticleHandle)
{
    Init();
}

//�f�[�^���
ReflectionParticleManager::~ReflectionParticleManager()
{
    m_reflectionParticleHandle.Reset();
}

//������
void ReflectionParticleManager::Init()
{
    m_reflectionParticles.clear();
}

//�}�l�[�W���[�X�V
void ReflectionParticleManager::Update(BulletManager* bulletManager)
{
    //�u���b�N�ɒe������������p�[�e�B�N������
    for (int i = initializeNum; i < bulletManager->GetBullets()->size(); i++)
    {
        if (bulletManager->GetBullets()->at(i)->GetIsHitBlock())
        {
            m_reflectionParticles.push_back(new ReflectionParticle(bulletManager->GetBullets()->at(i)->GetPos()));
        }
    }

    //�p�[�e�B�N���X�V
    for (int i = initializeNum; i < m_reflectionParticles.size(); i++)
    {
        m_reflectionParticles.at(i)->Update();
    }

    //�p�[�e�B�N���폜
    for (int i = initializeNum; i < m_reflectionParticles.size(); i++)
    {
        if (m_reflectionParticles.at(i)->GetIsFinish())
        {
            m_reflectionParticles.erase(m_reflectionParticles.begin() + i);
        }
    }
}

//�p�[�e�B�N���`��
void ReflectionParticleManager::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources)
{
    basicEffect->SetTexture(m_reflectionParticleHandle.Get());
    DX::ThrowIfFailed(CreateInputLayoutFromEffect<VertexPositionTexture>(deviceResources, basicEffect, inputLayout.ReleaseAndGetAddressOf()));
    for (int i = initializeNum; i < m_reflectionParticles.size(); i++)
    {
        m_reflectionParticles.at(i)->Draw(context, states, view, projection, basicEffect, inputLayout, primitiveBatch, deviceResources);
    }
}