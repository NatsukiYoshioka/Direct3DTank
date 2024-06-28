#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class AnimatedTexture;
class HitExplosionManager;
class HitAroundEffectManager;

class HitEffectManager
{
public:
    HitEffectManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitFlameParticleHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitAroundFlameParticleHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitSmokeParticleHandle);
    ~HitEffectManager();

    void Init();
    void Update();
    void Draw();

private:
    HitExplosionManager* m_hitExplosionManager;
    HitAroundEffectManager* m_hitAroundEffectManager;

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hitFlameParticleHandle;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hitAroundFlameParticleHandle;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hitSmokeParticleHandle;

    unique_ptr<AnimatedTexture> m_hitFlameAnimatedParticleHandle;
    unique_ptr<AnimatedTexture> m_hitAroundFlameAnimatedParticleHandle;
    unique_ptr<AnimatedTexture> m_hitSmokeAnimatedParticleHandle;

    static constexpr int m_flameWarpCount = 5;
    static constexpr int m_flameSideCount = 10;

    static constexpr int m_aroundFlameWarpCount = 6;
    static constexpr int m_aroundFlameSideCount = 6;

    static constexpr int m_smokeWarpCount = 5;
    static constexpr int m_smokeSideCount = 5;

    static constexpr int m_framesPerSecond = 20;
};

