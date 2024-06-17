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
    m_firstHeight(pos.y+m_sponeHeight),
    m_isFinish(false)
{
    m_pos.y = m_firstHeight;
    //炎が上がる最大Y軸量の設定
    std::random_device random;
    std::mt19937 generator(random());
    using dist_type = std::uniform_real_distribution<float>;
    dist_type distribution(m_minDistributionUpVectorY, m_maxDistributionUpVectorY);
    m_maxUpVectorY = m_pos.y + distribution(generator);

    //炎の上昇スピード設定
    dist_type::param_type param(m_minUpSpeed, m_maxUpSpeed);
    distribution.param(param);
    m_upSpeed = distribution(generator);

    //炎が上がる場所の設定
    param._Min = m_minDirection;
    param._Max = m_maxDirection;
    distribution.param(param);
    float degree = distribution(generator) * 180.f / M_PI;
    float cos, sin;
    cos = std::cos(degree);
    sin = std::sin(degree);
    m_direction.x = sin;
    m_direction.z = cos;

    param._Min = m_minWidth;
    param._Max = m_maxWidth;
    distribution.param(param);
    float widthX = distribution(generator);
    float widthZ = distribution(generator);
    m_direction.x *= widthX;
    m_direction.z *= widthZ;
}

FireParticle::~FireParticle()
{

}

void FireParticle::Update(DirectX::SimpleMath::Matrix world)
{
    m_pos += m_direction;
    m_pos.y += m_upSpeed;
    if (m_pos.y >= m_maxUpVectorY)
    {
        m_isFinish = true;
    }
    
    m_world = world;
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(m_world, m_local);
}

void FireParticle::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, ID3D11InputLayout* inputLayout)
{
    auto Context = context;
    Context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);
    Context->OMSetDepthStencilState(states->DepthRead(), initializeNum);
    Context->RSSetState(states->CullNone());

    auto a = 1.f - m_pos.y / (m_maxDistributionUpVectorY + m_firstHeight);
    basicEffect->SetDiffuseColor(Vector3(1.f - (m_pos.y - m_firstHeight) / (m_maxDistributionUpVectorY + m_firstHeight), 0.f, 0.f));
    basicEffect->SetAlpha(1.f - m_pos.y / (m_maxDistributionUpVectorY + m_firstHeight));
    basicEffect->Apply(Context);

    auto sampler = states->LinearClamp();
    Context->PSSetSamplers(0, 1, &sampler);

    Context->IASetInputLayout(inputLayout);

    basicEffect->SetView(view);
    basicEffect->SetProjection(projection);

    VertexPositionTexture v1(Vector3(m_pos.x, m_pos.y + m_textureWidth, m_pos.z - m_textureWidth), Vector2(0.f, 0.f));
    VertexPositionTexture v2(Vector3(m_pos.x, m_pos.y + m_textureWidth, m_pos.z + m_textureWidth), Vector2(1.f, 0.f));
    VertexPositionTexture v3(Vector3(m_pos.x, m_pos.y - m_textureWidth, m_pos.z + m_textureWidth), Vector2(1.f, 1.f));
    VertexPositionTexture v4(Vector3(m_pos.x, m_pos.y - m_textureWidth, m_pos.z - m_textureWidth), Vector2(0.f, 1.f));

    primitiveBatch->Begin();
    primitiveBatch->DrawQuad(v1, v2, v3, v4);
    primitiveBatch->End();
}