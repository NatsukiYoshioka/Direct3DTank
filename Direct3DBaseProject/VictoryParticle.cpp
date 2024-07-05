#include "pch.h"
#include<random>
#define _USE_MATH_DEFINES
#include<math.h>
#include"common.h"
#include "VictoryParticle.h"

VictoryParticle::VictoryParticle(ID3D11ShaderResourceView* victoryParticle):
    m_victoryParticle(victoryParticle),
    m_isFinish(false),
    m_rotation(float(initializeNum))
{
    std::random_device random;
    std::mt19937 generator(random());
    using dist_type = std::uniform_real_distribution<float>;
    dist_type distribution(m_minSponeWidth, m_maxSponeWidth);
    m_pos.x = distribution(generator);

    dist_type::param_type param(m_maxDistributionUpVectorY, m_minDistributionUpVectorY);
    distribution.param(param);
    m_maxUpVector = distribution(generator);

    param._Min = m_maxSponeHeight;
    param._Max = m_minSponeHeight;
    distribution.param(param);
    m_pos.y = distribution(generator);

    param._Min = m_minUpSpeed;
    param._Max = m_maxUpSpeed;
    distribution.param(param);
    m_upSpeed = distribution(generator);

    Microsoft::WRL::ComPtr<ID3D11Resource> resource;
    m_victoryParticle->GetResource(&resource);
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    DX::ThrowIfFailed(resource.As(&texture));
    CD3D11_TEXTURE2D_DESC textureDesc;
    texture->GetDesc(&textureDesc);
    m_origin.x = textureDesc.Width / 2;
    m_origin.y = textureDesc.Height / 2;
}

VictoryParticle::~VictoryParticle()
{

}

void VictoryParticle::Update()
{
    m_pos.y -= m_upSpeed;
    if (m_pos.y <= m_maxUpVector)
    {
        m_isFinish = true;
    }

    if (m_pos.x >= m_referenceWidth)
    {
        m_rotation -= m_rotationSpeed;
    }
    else
    {
        m_rotation += m_rotationSpeed;
    }
}

void VictoryParticle::Draw(DirectX::SpriteBatch* spritebatch)
{
    spritebatch->Draw(m_victoryParticle, m_pos, nullptr, Colors::White, m_rotation, m_origin, m_scale, SpriteEffects_None, m_depth);
}