#include "pch.h"
#include"common.h"
#include "Transition.h"

Transition::Transition(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> transitionTexture):
    m_transitionTexture(transitionTexture),
    m_alpha(float(initializeNum)),
    m_isFinishFadein(false),
    m_isFinishFadeout(false)
{
    Microsoft::WRL::ComPtr<ID3D11Resource> resource;
    m_transitionTexture->GetResource(&resource);
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    DX::ThrowIfFailed(resource.As(&texture));
    CD3D11_TEXTURE2D_DESC textureDesc;
    texture->GetDesc(&textureDesc);
    m_origin.x = textureDesc.Width / 2;
    m_origin.y = textureDesc.Height / 2;
}

Transition::~Transition()
{
    m_transitionTexture.Reset();
    if (m_basicEffect.get())
    {
        m_basicEffect.reset();
    }
}

void Transition::Update(bool isChangeScene)
{
    if (isChangeScene)
    {
        if (!m_isFinishFadeout)
        {
            m_alpha += m_alphaAdd * 2;
        }
        if (m_alpha >= 1.f)
        {
            m_isFinishFadeout = true;
        }
    }
    else
    {
        m_isFinishFadeout = false;
    }
    m_alpha -= m_alphaAdd;
    if (m_alpha <= float(initializeNum))
    {
        m_alpha = float(initializeNum);
        m_isFinishFadein = true;
    }
}

void Transition::Draw(DirectX::SpriteBatch* spritebatch, DirectX::CommonStates* states, ID3D11Device* deviceResources, ID3D11DeviceContext1* context, BasicEffect* basicEffect, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    if (!m_basicEffect.get())
    {
        m_basicEffect = make_unique<BasicEffect>(deviceResources);
        m_basicEffect->SetTextureEnabled(true);
        m_basicEffect->SetTexture(m_transitionTexture.Get());
    }

    void const* shaderByteCode;
    size_t byteCodeLength;
    
    m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
    deviceResources->CreateInputLayout(VertexPositionColorTexture::InputElements, VertexPositionColorTexture::InputElementCount, shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());

    spritebatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied(), nullptr, states->DepthRead(), states->CullNone(), [=]
        {
            m_basicEffect->SetAlpha(m_alpha);
            m_basicEffect->SetView(Matrix::Identity);
            m_basicEffect->Apply(context);
            context->IASetInputLayout(m_inputLayout.Get());
        });
    spritebatch->Draw(m_transitionTexture.Get(), m_pos, nullptr, Colors::White, float(initializeNum), m_origin, m_scale, SpriteEffects_None, m_layerDepth);
    spritebatch->End();
}