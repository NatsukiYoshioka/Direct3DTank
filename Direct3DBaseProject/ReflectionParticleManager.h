#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class ReflectionParticle;
class BulletManager;

class ReflectionParticleManager
{
public:
    ReflectionParticleManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> reflectionParticleHandle);
    ~ReflectionParticleManager();

    void Init();
    void Update(BulletManager* bulletManager);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, ID3D11Device* deviceResources);
private:
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_reflectionParticleHandle;
    vector<ReflectionParticle*> m_reflectionParticles;
};

