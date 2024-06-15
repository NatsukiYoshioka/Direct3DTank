#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class FireParticle;
class TankManager;

class FireParticleManager
{
public:
    FireParticleManager(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> fireParticle, vector<unique_ptr<DirectX::BasicEffect>>&& fireBasicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> fireInputLayout);
    ~FireParticleManager();

    void Init();
    void Update(DirectX::SimpleMath::Matrix world, TankManager* tankManager);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch);
private:
    vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_fireParticleHandle;
    vector<FireParticle*> m_fireParticles;

    vector<unique_ptr<DirectX::BasicEffect>> m_fireBasicEffect;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_fireInputLayout;

    vector<bool> m_isUseParticle;
};

