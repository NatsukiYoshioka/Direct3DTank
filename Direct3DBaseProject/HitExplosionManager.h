#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class AnimatedTexture;

class HitExplosionManager
{
public:
    HitExplosionManager(ID3D11ShaderResourceView* hitFlameParticleHandle, ID3D11ShaderResourceView* hitSmokeParticleHandle, int framesPerSecond);
    ~HitExplosionManager();

    void Init();
    void Update();
    void Draw();

private:

    unique_ptr<AnimatedTexture> m_hitFlameAnimatedParticleHandle;
    unique_ptr<AnimatedTexture> m_hitSmokeAnimatedParticleHandle;

    static constexpr int m_flameWarpCount = 5;
    static constexpr int m_flameSideCount = 10;

    static constexpr int m_smokeWarpCount = 5;
    static constexpr int m_smokeSideCount = 5;
};

