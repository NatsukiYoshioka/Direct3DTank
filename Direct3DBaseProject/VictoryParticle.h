#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class VictoryParticle
{
public:
    VictoryParticle(ID3D11ShaderResourceView* victoryParticle);
    ~VictoryParticle();

    void Update();
    void Draw(DirectX::SpriteBatch* spritebatch);

    bool GetIsFinish() { return m_isFinish; }

private:
    ID3D11ShaderResourceView* m_victoryParticle;
    Vector2 m_pos;
    float m_maxUpVector;
    float m_upSpeed;
    float m_rotation;
    Vector2 m_origin;

    bool m_isFinish;

    static constexpr float m_maxSponeWidth = 975.f;
    static constexpr float m_minSponeWidth = 675.f;

    static constexpr float m_maxSponeHeight = 300.f;
    static constexpr float m_minSponeHeight = 350.f;

    static constexpr float m_maxDistributionUpVectorY = 100.f;
    static constexpr float m_minDistributionUpVectorY = 125.f;

    static constexpr float m_maxUpSpeed = 2.f;
    static constexpr float m_minUpSpeed = 1.f;

    static constexpr float m_referenceWidth = 825.f;
    static constexpr float m_rotationSpeed = 0.2f;

    static constexpr float m_scale = 0.03f;
    static constexpr float m_depth = 0.f;
};

