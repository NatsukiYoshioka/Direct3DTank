#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class AnimatedTexture;

class HitAroundEffectManager
{
public:
    HitAroundEffectManager(ID3D11ShaderResourceView* hitAroundFlameParticleHandle, int framesPerSecond);
    ~HitAroundEffectManager();

    void Init();
    void Update();
    void Draw();
private:
    unique_ptr<AnimatedTexture> m_hitAroundFlameAnimatedParticleHandle;

    static constexpr int m_aroundFlameWarpCount = 6;
    static constexpr int m_aroundFlameSideCount = 6;
};

