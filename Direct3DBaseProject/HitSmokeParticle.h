#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class AnimatedTexture;

class HitSmokeParticle
{
public:
    HitSmokeParticle(AnimatedTexture* hitFlameParticleHandle, Vector3 pos);
    ~HitSmokeParticle();

    void Update(float elapsedTime, Vector3 pos);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, ID3D11InputLayout* inputLayout);

    bool GetIsFinish() { return m_isFinish; }

private:
    AnimatedTexture* m_hitSmokeParticleHandle;

    float m_alpha;
    Vector3 m_pos;

    bool m_isFinish;

    static constexpr float m_textureWidth = 1.f;

    static constexpr float m_alphaDecreaseSpeed = 0.005f;
    static constexpr float m_sponeHeight = 0.75f;
};

