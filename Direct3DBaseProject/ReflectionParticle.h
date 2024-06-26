#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class ReflectionParticle
{
public:
    ReflectionParticle(Vector3 pos);
    ~ReflectionParticle();

    void Update();
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources);

    bool GetIsFinish()const { return m_isFinish; }
private:
    Vector3 m_pos;

    float m_textureWidth;

    static constexpr float m_textureWidthExpansionSpeed = 0.01f;
    static constexpr float m_maxTextureWidth = 0.6f;

    bool m_isFinish;
};

