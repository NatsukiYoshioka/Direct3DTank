#include "pch.h"
#include<random>
#define _USE_MATH_DEFINES
#include<math.h>
#include "WoodParticle.h"

WoodParticle::WoodParticle(DirectX::Model* woodParticleModelHandle, Vector3 pos):
    m_woodParticleModelHandle(woodParticleModelHandle),
    m_pos(pos),
    m_direction(),
    m_world(),
    m_local()
{
    //Œü‚«‚Ìƒ‰ƒ“ƒ_ƒ€İ’è
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_real_distribution<float> distribution(0.f, 2.f);
    float degree = distribution(generator) * 180.f / M_PI;
    float cos, sin;
    cos = std::cos(degree);
    sin = std::sin(degree);
    m_direction.x = sin;
    m_direction.z = cos;
    m_direction.Normalize();
}

WoodParticle::~WoodParticle()
{

}

void WoodParticle::Update(DirectX::SimpleMath::Matrix world)
{
    m_pos.x += m_direction.x * 0.04f;
    m_pos.z += m_direction.z * 0.04f;

    m_world = world;
    m_world = XMMatrixMultiply(world, Matrix::CreateScale(m_scale));
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(m_world, m_local);
}

void WoodParticle::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    m_woodParticleModelHandle->Draw(context, *states, m_local, view, projection);
}