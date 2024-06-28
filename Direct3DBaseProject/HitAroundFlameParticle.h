#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class AnimatedTexture;

class HitAroundFlameParticle
{
public:
    HitAroundFlameParticle(AnimatedTexture* hitAroundFlameParticleHandle, Vector3 pos);
    ~HitAroundFlameParticle();

    void Update(float elapsedTime);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, ID3D11InputLayout* inputLayout);

    bool GetIsFinish() { return m_isFinish; }

private:
    AnimatedTexture* m_hitAroundFlameParticleHandle;

    Vector3 m_direction;
    Vector3 m_pos;

    float m_nowMass;

    static constexpr float m_upPower = 0.05f;
    static constexpr float m_gravity = 0.001f;

    static constexpr float m_minDirection = 0.f;                //Å¬Œü‚«(ƒ‰ƒWƒAƒ“)
    static constexpr float m_maxDirection = 0.2f;               //Å‘åŒü‚«

    static constexpr float m_minWidth = 0.005f;                //¶¬‚·‚éÅ¬…•½•
    static constexpr float m_maxWidth = 0.01f;                //¶¬‚·‚éÅ‘å…•½•

    static constexpr float m_sponeHeight = 0.3f;

    bool m_isFinish;

    static constexpr float m_textureWidth = 0.25f;
};

