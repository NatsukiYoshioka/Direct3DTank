#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class FireParticle
{
public:
    FireParticle(ID3D11ShaderResourceView* fireParticle, int handleIndex, Vector3 pos);
    ~FireParticle();

    void Update(DirectX::SimpleMath::Matrix world);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch);

    bool GetIsFinish() { return m_isFinish; }

    const int GetHandleIndex() { return m_handleIndex; }
private:
    ID3D11ShaderResourceView* m_fireParticle;
    
    const int m_handleIndex;

    Vector3 m_pos;
    Matrix m_world;
    Matrix m_local;

    bool m_isFinish;

    float m_maxUpVectorY;
    static constexpr float m_minDistributionUpVectorY = 0.2f;
    static constexpr float m_maxDistributionUpVectorY = 0.8f;

    float m_upSpeed;
    static constexpr float m_minUpSpeed = 0.001f;
    static constexpr float m_maxUpSpeed = 0.004f;

    static constexpr float m_minDirection = 0.f;
    static constexpr float m_maxDirection = 0.2f;

    static constexpr float m_minWidth = 0.f;
    static constexpr float m_maxWidth = 0.7f;

    static constexpr float m_scale = 0.1f;
};

