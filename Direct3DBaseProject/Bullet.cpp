#include "pch.h"
#include"common.h"
#include "Bullet.h"

//’e‚Ì‰Šú‰»
Bullet::Bullet(DirectX::Model* bulletModelHandle, DirectX::SimpleMath::Vector3 pos, float angle):
    m_bulletModelHandle(bulletModelHandle),
    m_pos(pos),
    m_local(),
    m_world(),
    m_angle(angle),
    m_direction(),
    m_isHitBlock(false),
    m_isBreak(false),
    m_boundBlockCount(initializeNum)
{
    float cos, sin;
    cos = std::cos(m_angle);
    sin = std::sin(m_angle);
    m_direction.x = sin;
    m_direction.z = cos;
    m_pos.x += m_direction.x * m_fireFrontWidth;
    m_pos.z += m_direction.z * m_fireFrontWidth;

    m_bulletModelHandle->meshes.at(initializeNum)->boundingBox.Center.x = m_pos.x;
    m_bulletModelHandle->meshes.at(initializeNum)->boundingBox.Center.y = m_pos.y;
    m_bulletModelHandle->meshes.at(initializeNum)->boundingBox.Center.z = m_pos.z;

    m_bulletModelHandle->meshes.at(initializeNum)->boundingBox.Extents.x = m_boundingboxExtentsX;
    m_bulletModelHandle->meshes.at(initializeNum)->boundingBox.Extents.y = m_boundingboxExtentsY;
    m_bulletModelHandle->meshes.at(initializeNum)->boundingBox.Extents.z = m_boundingboxExtentsZ;
}

//ƒfƒXƒgƒ‰ƒNƒ^
Bullet::~Bullet()
{
    
}

//’e‚ÌXV
void Bullet::Update(DirectX::SimpleMath::Matrix world)
{
    //’e‚Ì‰Ÿ‚µo‚µˆ—
    float cos, sin;
    cos = std::cos(m_angle);
    sin = std::sin(m_angle);
    m_direction.x = sin;
    m_direction.z = cos;
    m_direction.Normalize();
    m_pos.x += m_direction.x * m_speed;
    m_pos.z += m_direction.z * m_speed;

    //’e‚Ìî•ñ‚ðs—ñ‚É•ÏŠ·
    m_world = world;
    m_world = XMMatrixMultiply(world, Matrix::CreateScale(m_scale));
    m_world = XMMatrixMultiply(m_world, Matrix::CreateRotationX(XM_PIDIV2));
    m_world = XMMatrixMultiply(m_world, Matrix::CreateRotationY(m_angle));
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(m_world, m_local);

    m_bulletModelHandle->meshes.at(initializeNum)->boundingBox.Center.x = m_pos.x;
    m_bulletModelHandle->meshes.at(initializeNum)->boundingBox.Center.y = m_pos.y;
    m_bulletModelHandle->meshes.at(initializeNum)->boundingBox.Center.z = m_pos.z;
}

//’e‚Ì•`‰æ
void Bullet::Draw(ID3D11DeviceContext1* deviceContext, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    m_bulletModelHandle->Draw(deviceContext, *states, m_local, view, projection);
}

//’e‚ÆƒXƒe[ƒW‚Æ‚Ì“–‚½‚è”»’è
bool Bullet::CheckHitBlock(BoundingBox blockBox, Vector3 blockPos)
{
    m_isHitBlock = m_bulletModelHandle->meshes.at(initializeNum)->boundingBox.Intersects(blockBox);
    if (m_isHitBlock)
    {
        m_boundBlockCount++;
        if (m_boundBlockCount > m_maxBoundCount)
        {
            m_isBreak = true;
        }

        Vector2 distance;
        distance.x = m_pos.x - blockPos.x;
        distance.y = m_pos.z - blockPos.z;
        if (distance.x < initializeNum)distance.x = -distance.x;
        if (distance.y < initializeNum)distance.y = -distance.y;

        if (distance.x > distance.y)
        {
            m_direction.x = -m_direction.x;
        }
        else if (distance.x < distance.y)
        {
            m_direction.z = -m_direction.z;
        }
        m_angle = atan2f(m_direction.x, m_direction.z);
        m_world = XMMatrixMultiply(m_world, Matrix::CreateRotationY(m_angle));
    }
    return m_isHitBlock;
}