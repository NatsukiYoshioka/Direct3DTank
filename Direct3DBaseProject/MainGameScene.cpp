#include "pch.h"
#include"TankManager.h"
#include"Tank.h"
#include"BaseScene.h"
#include"AnimatedTexture.h"
#include "MainGameScene.h"

//メインシーン生成
MainGameScene::MainGameScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mainGameUI, vector<Vector2> mainGameUIPos, vector<float> mainGameUIScale):
    m_mainGameUI(mainGameUI),
    m_mainGameUIPos(mainGameUIPos),
    m_mainGameUIScale(mainGameUIScale),
    isFinish(false)
{
    for (int i = initializeNum; i < 20; i++)
    {
        m_animatedTexture.push_back(make_unique<AnimatedTexture>(Vector2::Zero, float(initializeNum), m_mainGameUIScale.at(i), float(initializeNum)));
    }
    for (int i = initializeNum; i < m_animatedTexture.size(); i++)
    {
        m_animatedTexture.at(i)->Load(m_mainGameUI.at(i).Get(), 2, 4, m_framesPerSencond);
    }
    for (int i = initializeNum; i < playerNum * maxHp; i++)
    {
        m_isEnableHeartUI[i] = true;
    }
}

//メインシーン破棄
MainGameScene::~MainGameScene()
{
    m_animatedTexture.clear();
    if (m_basicEffect.get())
    {
        m_basicEffect.reset();
    }
}

//メインシーン更新
void MainGameScene::Update(DirectX::GamePad::State padState, TankManager* tankManager, float elapsedTime)
{
    for (int i = initializeNum; i < tankManager->GetTanks().size(); i++)
    {
        for (int j = initializeNum; j < maxHp - tankManager->GetTanks().at(i)->GetHP(); j++)
        {
            m_isEnableHeartUI[i * maxHp + j] = false;
        }
    }
    int heartIndex = initializeNum;
    for (int i = initializeNum; i < m_animatedTexture.size(); i++)
    {
        if (i % 2 == initializeNum && !m_isEnableHeartUI[heartIndex])
        {
            m_animatedTexture.at(i)->Update(elapsedTime);
        }
        else if(i % int(hemipartition) != initializeNum)
        {
            m_animatedTexture.at(i)->Update(elapsedTime);
            heartIndex++;
        }
    }
}

//メインシーン描画
void MainGameScene::Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spritebatch, ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources)
{
    auto spriteBatch = spritebatch;
    int heartIndex = initializeNum;
    for (int i = initializeNum; i < m_mainGameUI.size(); i++)
    {
        if (i == m_backgroundIndex)
        {
            DrawBackGround(context, states, view, projection, primitiveBatch, basicEffect, inputLayout, deviceResources);
        }
        else if (i % int(hemipartition) != initializeNum)
        {
            if (m_isEnableHeartUI[i / 2])
            {
                m_animatedTexture.at(i)->Draw(spriteBatch, m_mainGameUIPos.at(i));
            }
        }
        else 
        {
            if (!m_isEnableHeartUI[heartIndex])
            {
                if (m_animatedTexture.at(i)->GetFrame() == m_maxFrame)
                {
                    m_animatedTexture.at(i)->Paused();
                }
                m_animatedTexture.at(i)->Draw(spriteBatch, m_mainGameUIPos.at(i));
            }
            heartIndex++;
        }
    }
}

void MainGameScene::DrawBackGround(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources)
{
    if (!m_basicEffect.get())
    {
        m_basicEffect = make_unique<BasicEffect>(deviceResources);
        m_basicEffect->SetTextureEnabled(true);
    }
    //カメラ位置、視野角の取得
    m_basicEffect->SetView(view);
    m_basicEffect->SetProjection(projection);

    m_basicEffect->SetTexture(m_mainGameUI.at(m_backgroundIndex).Get());
    DX::ThrowIfFailed(CreateInputLayoutFromEffect<VertexPositionTexture>(deviceResources, m_basicEffect.get(), inputLayout.ReleaseAndGetAddressOf()));
    Vector3 pos(m_mainGameUIPos.at(m_backgroundIndex).x, m_backgroundHeight, m_mainGameUIPos.at(m_backgroundIndex).y);

    auto Context = context;
    //乗算なしの透過に設定
    Context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);
    Context->OMSetDepthStencilState(states->DepthRead(), initializeNum);
    Context->RSSetState(states->CullNone());

    //色、透過度の設定
    m_basicEffect->SetDiffuseColor(Vector3::One);
    m_basicEffect->SetAlpha(1.f);
    m_basicEffect->Apply(Context);

    auto sampler = states->LinearClamp();
    Context->PSSetSamplers(0, 1, &sampler);

    Context->IASetInputLayout(inputLayout.Get());

    //テクスチャ用のビルボード設定
    VertexPositionTexture v1(Vector3(pos.x + m_backgroundWidth, pos.y, pos.z - m_backgroundWidth), Vector2(0.f, 0.f));
    VertexPositionTexture v2(Vector3(pos.x + m_backgroundWidth, pos.y, pos.z + m_backgroundWidth), Vector2(1.f, 0.f));
    VertexPositionTexture v3(Vector3(pos.x - m_backgroundWidth, pos.y, pos.z + m_backgroundWidth), Vector2(1.f, 1.f));
    VertexPositionTexture v4(Vector3(pos.x - m_backgroundWidth, pos.y, pos.z - m_backgroundWidth), Vector2(0.f, 1.f));

    //描画
    primitiveBatch->Begin();
    primitiveBatch->DrawQuad(v1, v2, v3, v4);
    primitiveBatch->End();
}