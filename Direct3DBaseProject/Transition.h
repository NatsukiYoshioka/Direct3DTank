#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

class Transition
{
public:
    Transition(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> transitionTexture);
    ~Transition();

    void Update(bool isChangeScene);
    void Draw(DirectX::SpriteBatch* spritebatch, DirectX::CommonStates* states, ID3D11Device* deviceResources, ID3D11DeviceContext1* context, BasicEffect* basicEffect, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

    bool GetIsFinishFadeout() { return m_isFinishFadeout; }

    bool GetIsFinishFadein() { return m_isFinishFadein; }
private:
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_transitionTexture;
    static constexpr Vector2 m_pos = { 0.f,0.f };
    Vector2 m_origin;
    float m_alpha;

    unique_ptr<DirectX::BasicEffect> m_basicEffect;         //描画オプションの設定クラス
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

    bool m_isFinishFadeout;
    bool m_isFinishFadein;

    static constexpr float m_scale = 0.1f;
    static constexpr float m_layerDepth = 0.5f;

    static constexpr float m_alphaAdd = 0.01f;
};

