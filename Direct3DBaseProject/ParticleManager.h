#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class WoodParticle;
class BlockManager;

class ParticleManager
{
public:
    ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle);
    ~ParticleManager();

    void Init();
    void Update(DirectX::SimpleMath::Matrix world, BlockManager* blockManager);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    vector<unique_ptr<DirectX::Model>> m_woodParticleModelHandle;
    vector<WoodParticle*> m_woodParticles;
    vector<bool> m_isUseWoodParticle;
    vector<bool> m_isSponeWoodParticle;
    int m_woodIndex;
};

