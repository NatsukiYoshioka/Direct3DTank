#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class FireParticle;
class TankManager;

class FireParticleManager
{
public:
    FireParticleManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> fireParticle);
    ~FireParticleManager();

    void Init();
    void Update(DirectX::SimpleMath::Matrix world, TankManager* tankManager);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources);
private:
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fireParticleHandle;
    vector<FireParticle*> m_fireParticles;

    vector<bool> m_isUseParticle;

    static constexpr int m_particleSize = 30;
};

