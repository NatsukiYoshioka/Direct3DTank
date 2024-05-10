#include "pch.h"
#include"Bullet.h"
#include"Tank.h"
#include"TankManager.h"
#include"BlockManager.h"
#include"common.h"
#include "BulletManager.h"

BulletManager::BulletManager(unique_ptr<DirectX::Model>&& bulletModelHandle):
    m_bullets()
{
    m_bulletModelHandle = bulletModelHandle.get();
}

BulletManager::~BulletManager()
{
    
}

void BulletManager::Update(DirectX::SimpleMath::Matrix world, TankManager* tankManager, BlockManager* blockManager)
{
    
    for (int i = initializeNum; i < tankManager->GetTanks().size(); i++)
    {
        if (tankManager->GetTanks().at(i)->GetIsFire() && tankManager->GetTanks().at(i)->GetFireRecast() == static_cast<float>(initializeNum))
        {
            m_bullets[i].push_back(new Bullet(m_bulletModelHandle, tankManager->GetTanks().at(i)->GetPos(), tankManager->GetTanks().at(i)->GetTurretAngle()));
        }
    }
}

void BulletManager::Draw(ID3D11DeviceContext1* context, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{

}