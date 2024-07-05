#include "pch.h"
#include"TankManager.h"
#include"Tank.h"
#include "BaseScene.h"
#include "ResultScene.h"

extern void ExitGame() noexcept;

const Vector2 ResultScene::m_backPos = Vector2(325.f, 150.f);
const Vector2 ResultScene::m_descriptionStringScale = Vector2(0.35f, 0.35f);

//リザルトシーン生成
ResultScene::ResultScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resultUI, vector<Vector2> resultUIPos, vector<float> resultUIScale):
    m_resultUI(resultUI),
    m_resultUIPos(resultUIPos),
    m_resultUIScale(resultUIScale),
    isFinish(false)
{

}

//リザルトシーン破棄
ResultScene::~ResultScene()
{

}

//リザルトシーン更新
void ResultScene::Update(DirectX::GamePad::State padState, TankManager* tankManager)
{
    if (padState.IsConnected())
    {
        if (padState.IsViewPressed())
        {
            ExitGame();
        }
        if (padState.IsBPressed())
        {
            isFinish = true;
        }
    }
}

//リザルトシーン描画
void ResultScene::Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spritebatch, ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources)
{
    auto spriteBatch = spritebatch;
    for (int i = initializeNum; i < m_resultUI.size(); i++)
    {
        spriteBatch->Draw(m_resultUI.at(i).Get(), m_resultUIPos.at(i), nullptr, Colors::White, static_cast<float>(initializeNum), Vector2::Zero, m_resultUIScale.at(i), SpriteEffects_None, m_UIDepth);
    }
    auto origin = defaultfont->MeasureString(m_back) / hemipartition;
    defaultfont->DrawString(spriteBatch, m_back, m_backPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_stringDepth);
}