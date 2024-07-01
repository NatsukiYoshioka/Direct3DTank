#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class AnimatedTexture;

class HitFlameParticle
{
public:
    HitFlameParticle(AnimatedTexture* hitFlameParticleHandle, Vector3 pos, int tankIndex);
    ~HitFlameParticle();

    void Update(float elapsedTime, Vector3 pos);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, ID3D11InputLayout* inputLayout);

    bool GetIsFinish() { return m_isFinish; }

    const int GetTankIndex() { return m_tankIndex; }

private:
    AnimatedTexture* m_hitFlameParticleHandle;

    Vector3 m_pos;

    float m_alpha;
    float m_textureWidth;

    bool m_isFinish;

    const int m_tankIndex;

    static constexpr float m_alphaDecreaseSpeed = 0.005f;
    static constexpr float m_initTextureWidth = 1.f;
    static constexpr float m_widthDecreaseSpeed = 0.001f;
    static constexpr float m_sponeHeight = 0.75f;
};

