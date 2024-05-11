#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class WoodParticle
{
public:
    WoodParticle(DirectX::Model* woodParticleModelHandle, Vector3 pos);
    ~WoodParticle();

    void Update();
    void Draw();

private:
    DirectX::Model* m_woodParticleModelHandle;
    Vector3 m_pos;
};

