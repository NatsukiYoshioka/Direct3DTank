#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class WoodParticle;

class ParticleManager
{
public:
    ParticleManager(vector<unique_ptr<DirectX::Model>>&& woodModelHandle);
    ~ParticleManager();

    void Update();
    void Draw();

private:
    vector<unique_ptr<DirectX::Model>> m_woodParticleModelHandle;
    vector<WoodParticle*> m_woodParticles;
};

