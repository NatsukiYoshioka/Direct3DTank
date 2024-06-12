#include "pch.h"
#include"Game.h"
#include<random>
#define _USE_MATH_DEFINES
#include<math.h>
#include "WoodParticle.h"

//パーティクルのランダム設定
WoodParticle::WoodParticle(DirectX::Model* woodParticleModelHandle, Vector3 pos):
    m_woodParticleModelHandle(woodParticleModelHandle),
    m_pos(pos),
    m_direction(),
    m_world(),
    m_local()
{
    //向きのランダム設定
    std::random_device random;
    std::mt19937 generator(random());
    using dist_type = std::uniform_real_distribution<float>;
    dist_type distribution(m_minDirection, m_maxDirection);
    m_degree = distribution(generator) * 180.f / M_PI;
    float cos, sin;
    cos = std::cos(m_degree);
    sin = std::sin(m_degree);
    m_direction.x = sin;
    m_direction.z = cos;
    m_direction.Normalize();

    //上方向に入る力量のランダム設定
    dist_type::param_type param(m_minUpPower, m_maxUpPower);
    distribution.param(param);
    m_upPower = distribution(generator);
}

//デストラクタ
WoodParticle::~WoodParticle()
{

}

//パーティクル更新
void WoodParticle::Update(DirectX::SimpleMath::Matrix world)
{
    float woodRotation = Game::GetTime() * m_rotationSpeed;
    if (m_pos.y > m_minY)
    {
        m_pos.x += m_direction.x * m_speed;
        m_pos.y += m_upPower;
        m_pos.z += m_direction.z * m_speed;
    }
    if (m_pos.y < m_minY)
    {
        m_pos.y = m_minY;
    }

    m_world = world;
    m_world = XMMatrixMultiply(world, Matrix::CreateScale(m_scale));
    if (m_pos.y > m_minY)m_world = XMMatrixMultiply(m_world, XMMatrixRotationX(woodRotation));
    m_world = XMMatrixMultiply(m_world, Matrix::CreateRotationY(m_degree));
    if (m_pos.y > m_minY)m_world = XMMatrixMultiply(m_world, XMMatrixRotationZ(woodRotation));
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(m_world, m_local);

    m_upPower -= m_decreaseY;
}

//パーティクル描画
void WoodParticle::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    m_woodParticleModelHandle->Draw(context, *states, m_local, view, projection);
}