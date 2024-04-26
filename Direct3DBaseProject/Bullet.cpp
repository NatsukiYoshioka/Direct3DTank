#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(DirectX::Model* bulletModelHandle, DirectX::SimpleMath::Vector3 pos, float angle):
    m_bulletModelHandle(bulletModelHandle),
    m_pos(pos),
    m_local(),
    m_angle(angle),
    m_direction()
{
    
}

Bullet::~Bullet()
{
    
}

void Bullet::Update(DirectX::SimpleMath::Matrix world)
{
    float cos, sin;
    cos = std::cos(m_angle);
    sin = std::sin(m_angle);
    m_direction.x = sin;
    m_direction.z = cos;
    m_direction.Normalize();
    m_pos.x += m_direction.x * m_speed;
    m_pos.z += m_direction.z * m_speed;

    auto m_world = world;
    m_world = XMMatrixMultiply(world, Matrix::CreateScale(m_scale));
    m_world = XMMatrixMultiply(m_world, Matrix::CreateRotationX(XM_PIDIV2));
    m_world = XMMatrixMultiply(m_world, Matrix::CreateRotationY(m_angle));
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(m_world, m_local);
}

void Bullet::Draw(ID3D11DeviceContext1* deviceContext, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    m_bulletModelHandle->Draw(deviceContext, *states, m_local, view, projection);
}