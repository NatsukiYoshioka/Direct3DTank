#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class FireParticle
{
public:
    FireParticle(Vector3 pos);
    ~FireParticle();

    void Update();
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, ID3D11InputLayout* inputLayout);

    bool GetIsFinish()const { return m_isFinish; }

private:
    Vector3 m_direction;
    Vector3 m_pos;

    bool m_isFinish;

    float m_maxUpVectorY;
    const float m_firstHeight;
    static constexpr float m_minDistributionUpVectorY = 0.2f;
    static constexpr float m_maxDistributionUpVectorY = 0.6f;

    float m_upSpeed;
    static constexpr float m_minUpSpeed = 0.001f;
    static constexpr float m_maxUpSpeed = 0.004f;

    static constexpr float m_minDirection = 0.f;
    static constexpr float m_maxDirection = 0.2f;

    static constexpr float m_minWidth = 0.0005f;
    static constexpr float m_maxWidth = 0.0025f;

    static constexpr float m_scale = 0.1f;

    static constexpr float m_textureWidth = 0.3f;
    static constexpr float m_sponeHeight = 0.8f;
};

