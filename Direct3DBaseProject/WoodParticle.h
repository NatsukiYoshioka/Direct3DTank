#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class WoodParticle
{
public:
    WoodParticle(DirectX::Model* woodParticleModelHandle, Vector3 pos);
    ~WoodParticle();

    void Update(DirectX::SimpleMath::Matrix world);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    DirectX::Model* m_woodParticleModelHandle;
    Vector3 m_pos;
    Matrix m_world;
    Matrix m_local;
    float m_degree;
    Vector3 m_direction;

    float m_upPower;

    static constexpr float m_scale = 0.075f;
    static constexpr float m_speed = 0.005f;

    static constexpr float m_minDirection = 0.f;
    static constexpr float m_maxDirection = 2.f;

    static constexpr float m_minUpPower = 0.01f;
    static constexpr float m_maxUpPower = 0.04f;
    static constexpr float m_decreaseY = 0.001f;
    static constexpr float m_minY = 0.5f;

    static constexpr float m_rotationSpeed = 10.f;
};

