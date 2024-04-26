#include "pch.h"
#include"common.h"
#include "Bullet.h"

const XMFLOAT3 Bullet::m_extents = XMFLOAT3(0.1f, 0.3f, 0.1f);

//�e�̏�����
Bullet::Bullet(DirectX::Model* bulletModelHandle, DirectX::SimpleMath::Vector3 pos, float angle):
    m_bulletModelHandle(bulletModelHandle),
    m_pos(pos),
    m_local(),
    m_angle(angle),
    m_direction(),
    m_shapeLocal()
{
    
}

//�f�X�g���N�^
Bullet::~Bullet()
{
    
}

//�e�̍X�V
void Bullet::Update(DirectX::SimpleMath::Matrix world)
{
    //�e�̉����o������
    float cos, sin;
    cos = std::cos(m_angle);
    sin = std::sin(m_angle);
    m_direction.x = sin;
    m_direction.z = cos;
    m_direction.Normalize();
    m_pos.x += m_direction.x * m_speed;
    m_pos.z += m_direction.z * m_speed;

    //�e�̏����s��ɕϊ�
    auto m_world = world;
    m_world = XMMatrixMultiply(world, Matrix::CreateScale(m_scale));
    m_world = XMMatrixMultiply(m_world, Matrix::CreateRotationX(XM_PIDIV2));
    m_world = XMMatrixMultiply(m_world, Matrix::CreateRotationY(m_angle));
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(m_world, m_local);

    //�����蔻��̍X�V
    m_shapeLocal = world;
    auto shapeWorld = world;
    shapeWorld = XMMatrixMultiply(world, Matrix::CreateRotationX(XM_PIDIV2));
    shapeWorld = XMMatrixMultiply(shapeWorld, Matrix::CreateRotationY(m_angle));
    m_shapeLocal = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_shapeLocal = XMMatrixMultiply(shapeWorld, m_shapeLocal);
}

//�e�̕`��
void Bullet::Draw(ID3D11DeviceContext1* deviceContext, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    m_bulletModelHandle->Draw(deviceContext, *states, m_local, view, projection);
}