#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class HitFlameParticle;
class HitSmokeParticle;
class TankManager;
class AnimatedTexture;

class HitExplosionManager
{
public:
    HitExplosionManager(ID3D11ShaderResourceView* hitFlameParticleHandle, ID3D11ShaderResourceView* hitSmokeParticleHandle, int framesPerSecond);
    ~HitExplosionManager();

    void Init();
    void Update(float elapsedTime,TankManager* tankManager);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources);

private:
    vector<HitFlameParticle*> m_hitFlameParticles;
    vector<HitSmokeParticle*> m_hitSmokeParticles;

    unique_ptr<AnimatedTexture> m_hitFlameAnimatedParticleHandle;
    unique_ptr<AnimatedTexture> m_hitSmokeAnimatedParticleHandle;

    ID3D11ShaderResourceView* m_hitFlameParticleHandle;
    ID3D11ShaderResourceView* m_hitSmokeParticleHandle;

    static constexpr float m_resetTime = 0.5f;

    static constexpr int m_flameWarpCount = 5;
    static constexpr int m_flameSideCount = 10;

    static constexpr int m_smokeWarpCount = 5;
    static constexpr int m_smokeSideCount = 5;
};

