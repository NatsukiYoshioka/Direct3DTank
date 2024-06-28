#include "pch.h"
#include"common.h"
#include "ReflectionParticle.h"

//�p�[�e�B�N������
ReflectionParticle::ReflectionParticle(Vector3 pos):
    m_pos(pos),
    m_textureWidth(m_textureWidthExpansionSpeed),
    m_isFinish(false)
{

}

//�f�[�^���
ReflectionParticle::~ReflectionParticle()
{

}

//�p�[�e�B�N���X�V
void ReflectionParticle::Update()
{
    m_textureWidth += m_textureWidthExpansionSpeed;
    //���̑傫���ɂȂ�����X�V�I��
    if (m_textureWidth >= m_maxTextureWidth)
    {
        m_isFinish = true;
    }
}

//�p�[�e�B�N���`��
void ReflectionParticle::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources)
{
    auto Context = context;
    Context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);
    Context->OMSetDepthStencilState(states->DepthRead(), initializeNum);
    Context->RSSetState(states->CullNone());

    basicEffect->SetDiffuseColor(Vector3::One);
    basicEffect->SetAlpha(1.f);
    basicEffect->Apply(Context);

    auto sampler = states->LinearClamp();
    Context->PSSetSamplers(0, 1, &sampler);

    Context->IASetInputLayout(inputLayout.Get());

    basicEffect->SetView(view);
    basicEffect->SetProjection(projection);

    VertexPositionTexture v1(Vector3(m_pos.x + m_textureWidth, m_pos.y, m_pos.z - m_textureWidth), Vector2(0.f, 0.f));
    VertexPositionTexture v2(Vector3(m_pos.x + m_textureWidth, m_pos.y, m_pos.z + m_textureWidth), Vector2(1.f, 0.f));
    VertexPositionTexture v3(Vector3(m_pos.x - m_textureWidth, m_pos.y, m_pos.z + m_textureWidth), Vector2(1.f, 1.f));
    VertexPositionTexture v4(Vector3(m_pos.x - m_textureWidth, m_pos.y, m_pos.z - m_textureWidth), Vector2(0.f, 1.f));

    primitiveBatch->Begin();
    primitiveBatch->DrawQuad(v1, v2, v3, v4);
    primitiveBatch->End();
}