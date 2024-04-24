#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(DirectX::Model* bulletModelHandle, DirectX::SimpleMath::Vector3 pos, float angle):
    m_bulletModelHandle(bulletModelHandle),
    m_pos(pos),
    m_local(),
    m_angle(angle)
{
    
}

Bullet::~Bullet()
{

}

void Bullet::Update(DirectX::SimpleMath::Matrix world)
{

}

void Bullet::Draw(ID3D11DeviceContext1* deviceContext, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    m_bulletModelHandle->Draw(deviceContext, *states, m_local, view, projection);
}