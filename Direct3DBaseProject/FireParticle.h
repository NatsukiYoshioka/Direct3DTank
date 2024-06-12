#pragma once
class FireParticle
{
public:
    FireParticle(ID3D11ShaderResourceView* fireParticle);
    ~FireParticle();

    void Update(DirectX::SimpleMath::Matrix world);
    void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

private:
    ID3D11ShaderResourceView* m_fireParticle;
};

