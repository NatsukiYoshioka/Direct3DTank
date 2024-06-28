#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class AnimatedTexture;
class HitAroundFlameParticle;
class TankManager;

class HitAroundEffectManager
{
public:
    HitAroundEffectManager(ID3D11ShaderResourceView* hitAroundFlameParticleHandle, int framesPerSecond);
    ~HitAroundEffectManager();

    void Init();
    void Update(float elapsedTime, TankManager* tankManager);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources);
private:
    vector<HitAroundFlameParticle*> m_hitAroundFlameParticles;
    unique_ptr<AnimatedTexture> m_hitAroundFlameAnimatedParticleHandle;

    ID3D11ShaderResourceView* m_hitAroundFlameParticleHandle;

    static constexpr int m_aroundFlameWarpCount = 6;
    static constexpr int m_aroundFlameSideCount = 6;

    static constexpr int m_particleNum = 5;
};

