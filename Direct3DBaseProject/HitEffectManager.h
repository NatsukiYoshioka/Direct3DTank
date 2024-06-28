#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class AnimatedTexture;
class HitExplosionManager;
class HitAroundEffectManager;
class TankManager;

class HitEffectManager
{
public:
    HitEffectManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitFlameParticleHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitAroundFlameParticleHandle, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hitSmokeParticleHandle);
    ~HitEffectManager();

    void Init();
    void Update(float elapsedTime, TankManager* tankManager);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources);

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

    static constexpr int m_framesPerSecond = 30;
};

