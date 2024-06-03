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
    Vector3 m_direction;

    static constexpr float m_scale = 0.1f;
};

