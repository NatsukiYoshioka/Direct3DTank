#include "pch.h"
#include<random>
#define _USE_MATH_DEFINES
#include<math.h>
#include"common.h"
#include "FireParticle.h"

FireParticle::FireParticle(ID3D11ShaderResourceView* fireParticle, int handleIndex, Vector3 pos):
    m_fireParticle(fireParticle),
    m_handleIndex(handleIndex),
    m_pos(pos),
    m_world(),
    m_local(),
    m_isFinish(false)
{
    //炎が上がる最大Y軸量の設定
    std::random_device random;
    std::mt19937 generator(random());
    using dist_type = std::uniform_real_distribution<float>;
    dist_type distribution(m_minDistributionUpVectorY, m_maxDistributionUpVectorY);
    m_maxUpVectorY = distribution(generator);

    //炎の上昇スピード設定
    dist_type::param_type param(m_minUpSpeed, m_maxUpSpeed);
    distribution.param(param);
    m_upSpeed = distribution(generator);

    //炎が上がる場所の設定
    param._Min = m_minDirection;
    param._Max = m_maxDirection;
    distribution.param(param);
    Vector3 movePos = Vector3::Zero;
    float degree = distribution(generator) * 180.f / M_PI;
    float cos, sin;
    cos = std::cos(degree);
    sin = std::sin(degree);
    movePos.x = sin;
    movePos.z = cos;

    param._Min = m_minWidth;
    param._Max = m_maxWidth;
    distribution.param(param);
    float widthX = distribution(generator);
    float widthZ = distribution(generator);
    movePos.x *= widthX;
    movePos.z += widthZ;

    m_pos += movePos;
}

FireParticle::~FireParticle()
{

}

void FireParticle::Update(DirectX::SimpleMath::Matrix world)
{
    m_pos.y += m_upSpeed;
    if (m_pos.y >= m_maxUpVectorY)
    {
        m_isFinish = true;
    }

    m_world = world;
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(m_world, m_local);
}

void FireParticle::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch)
{
    
}