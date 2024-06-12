#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class FireParticle;

class FireParticleManager
{
public:
    FireParticleManager(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> fireParticle);
    ~FireParticleManager();

    void Init();
    void Update(DirectX::SimpleMath::Matrix world);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
private:
    vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_fireParticleHandle;
    vector<FireParticle*> m_fireParticles;
};

