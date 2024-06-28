#include "pch.h"
#include<random>
#define _USE_MATH_DEFINES
#include<math.h>
#include"AnimatedTexture.h"
#include"common.h"
#include "HitAroundFlameParticle.h"

HitAroundFlameParticle::HitAroundFlameParticle(AnimatedTexture* hitAroundFlameParticleHandle, Vector3 pos):
    m_hitAroundFlameParticleHandle(hitAroundFlameParticleHandle),
    m_pos(pos),
    m_nowMass(m_upPower),
    m_isFinish(false)
{
    m_pos.y += m_sponeHeight;

    std::random_device random;
    std::mt19937 generator(random());
    using dist_type = std::uniform_real_distribution<float>;
    dist_type distribution(m_minDirection, m_maxDirection);
    float degree = distribution(generator) * 180.f / M_PI;
    float cos, sin;
    cos = std::cos(degree);
    sin = std::sin(degree);
    m_direction.x = sin;
    m_direction.z = cos;

    dist_type::param_type param(m_minWidth, m_maxWidth);
    distribution.param(param);
    float widthX = distribution(generator);
    float widthZ = distribution(generator);
    m_direction.x *= widthX;
    m_direction.z *= widthZ;
}

HitAroundFlameParticle::~HitAroundFlameParticle()
{

}

void HitAroundFlameParticle::Update(float elapsedTime)
{
    m_pos += m_direction;
    m_pos.y += m_nowMass;
    m_nowMass -= m_gravity;
    if (m_pos.y <= float(initializeNum))
    {
        m_isFinish = true;
    }

    m_hitAroundFlameParticleHandle->Update(elapsedTime);
}

void HitAroundFlameParticle::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, ID3D11InputLayout* inputLayout)
{
    auto Context = context;
    //乗算なしの透過に設定
    Context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);
    Context->OMSetDepthStencilState(states->DepthRead(), initializeNum);
    Context->RSSetState(states->CullNone());

    //色、透過度の設定
    basicEffect->SetDiffuseColor(Vector3::One);
    basicEffect->SetAlpha(1.f);
    basicEffect->Apply(Context);

    auto sampler = states->LinearClamp();
    Context->PSSetSamplers(0, 1, &sampler);

    Context->IASetInputLayout(inputLayout);

    //カメラ位置、視野角の取得
    basicEffect->SetView(view);
    basicEffect->SetProjection(projection);

    m_hitAroundFlameParticleHandle->Draw(primitiveBatch, m_pos, m_textureWidth);
}