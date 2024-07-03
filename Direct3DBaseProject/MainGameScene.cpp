#include "pch.h"
#include"TankManager.h"
#include"Tank.h"
#include"BaseScene.h"
#include "MainGameScene.h"

//メインシーン生成
MainGameScene::MainGameScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mainGameUI, vector<Vector2> mainGameUIPos, vector<float> mainGameUIScale):
    m_mainGameUI(mainGameUI),
    m_mainGameUIPos(mainGameUIPos),
    m_mainGameUIScale(mainGameUIScale),
    isFinish(false)
{
    for (int i = initializeNum; i < playerNum * maxHp; i++)
    {
        m_isEnableHeartUI[i] = true;
    }
}

//メインシーン破棄
MainGameScene::~MainGameScene()
{

}

//メインシーン更新
void MainGameScene::Update(DirectX::GamePad::State padState, TankManager* tankManager)
{
    for (int i = initializeNum; i < tankManager->GetTanks().size(); i++)
    {
        for (int j = initializeNum; j < maxHp - tankManager->GetTanks().at(i)->GetHP(); j++)
        {
            m_isEnableHeartUI[i * maxHp + j] = false;
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
        else if (i % int(hemipartition) == initializeNum)
        {
            spriteBatch->Draw(m_mainGameUI.at(i).Get(), m_mainGameUIPos.at(i), nullptr, Colors::White, static_cast<float>(initializeNum), Vector2::Zero, m_mainGameUIScale.at(i), SpriteEffects_None, m_UIDepth);
        }
        else 
        {
            if (m_isEnableHeartUI[heartIndex])
            {
                spriteBatch->Draw(m_mainGameUI.at(i).Get(), m_mainGameUIPos.at(i), nullptr, Colors::White, static_cast<float>(initializeNum), Vector2::Zero, m_mainGameUIScale.at(i), SpriteEffects_None, m_UIDepth);
            }
            heartIndex++;
        }
    }
}

void MainGameScene::DrawBackGround(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources)
{
    basicEffect->SetTexture(m_mainGameUI.at(m_backgroundIndex).Get());
    DX::ThrowIfFailed(CreateInputLayoutFromEffect<VertexPositionTexture>(deviceResources, basicEffect, inputLayout.ReleaseAndGetAddressOf()));
    Vector3 pos(m_mainGameUIPos.at(m_backgroundIndex).x, m_backgroundHeight, m_mainGameUIPos.at(m_backgroundIndex).y);

    auto Context = context;
    //乗算なしの透過に設定
    Context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);
    Context->OMSetDepthStencilState(states->DepthRead(), initializeNum);
    Context->RSSetState(states->CullNone());

    //色、透過度の設定
    basicEffect->SetDiffuseColor(Vector3::One);
    basicEffect->SetAlpha(1.f);
    basicEffect->Apply(Context);

    auto sampler = states->LinearClamp();
    Context->PSSetSamplers(0, 1, &sampler);

    Context->IASetInputLayout(inputLayout.Get());

    //カメラ位置、視野角の取得
    basicEffect->SetView(view);
    basicEffect->SetProjection(projection);

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