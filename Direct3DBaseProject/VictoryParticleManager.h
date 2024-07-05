#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class VictoryParticle;

class VictoryParticleManager
{
public:
    VictoryParticleManager(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> victoryParticleHandle);
    ~VictoryParticleManager();

    void Init();
    void Update();
    void Draw(DirectX::SpriteBatch* spritebatch);

private:
    vector<VictoryParticle*> m_victoryParticles;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_victoryParticleHandle;

    static constexpr int m_particleNum = 10;
};

