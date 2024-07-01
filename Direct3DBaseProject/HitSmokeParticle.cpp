#include "pch.h"
#include"AnimatedTexture.h"
#include"common.h"
#include "HitSmokeParticle.h"

HitSmokeParticle::HitSmokeParticle(AnimatedTexture* hitFlameParticleHandle, Vector3 pos):
    m_hitSmokeParticleHandle(hitFlameParticleHandle),
    m_pos(pos),
    m_alpha(1.f),
    m_isFinish(false)
{
    m_pos.y += m_sponeHeight;
}

HitSmokeParticle::~HitSmokeParticle()
{

}

void HitSmokeParticle::Update(float elapsedTime, Vector3 pos)
{
    m_pos = pos;
    m_pos.y += m_sponeHeight;

    m_alpha -= m_alphaDecreaseSpeed;
    if (m_alpha <= float(initializeNum))
    {
        m_isFinish = true;
    }

    m_hitSmokeParticleHandle->Update(elapsedTime);
}

void HitSmokeParticle::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, ID3D11InputLayout* inputLayout)
{
    auto Context = context;
    //乗算なしの透過に設定
    Context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);
    Context->OMSetDepthStencilState(states->DepthRead(), initializeNum);
    Context->RSSetState(states->CullNone());

    //色、透過度の設定
    basicEffect->SetDiffuseColor(Vector3::One);
    basicEffect->SetAlpha(m_alpha);
    basicEffect->Apply(Context);

    auto sampler = states->LinearClamp();
    Context->PSSetSamplers(0, 1, &sampler);

    Context->IASetInputLayout(inputLayout);

    //カメラ位置、視野角の取得
    basicEffect->SetView(view);
    basicEffect->SetProjection(projection);

    m_hitSmokeParticleHandle->Draw(primitiveBatch, m_pos, m_textureWidth);
}