#include "pch.h"
#include"common.h"
#include"BaseScene.h"
#include "TitleScene.h"

extern void ExitGame() noexcept;

const Vector2 TitleScene::m_titlePos = Vector2(960.f, 200.f);
const Vector2 TitleScene::m_titleScale = Vector2(1.f, 1.f);

TitleScene::TitleScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos):
    m_titleUI(titleUI),
    m_titleUIPos(titleUIPos),
    isFinish(false)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Update(DirectX::GamePad::State padState)
{
    if (padState.IsConnected())
    {
        if (padState.IsViewPressed())
        {
            ExitGame();
        }
        if (padState.IsAPressed())
        {
            isFinish = true;
        }
    }
}

void TitleScene::Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spritebatch)
{
    auto defaultFont = defaultfont;
    auto spriteBatch = spritebatch;
    spriteBatch->Begin();

    Vector2 origin = defaultFont->MeasureString(m_title) / hemipartition;
    

    defaultFont->DrawString(spriteBatch, m_title, m_titlePos, Colors::BurlyWood, static_cast<float>(initializeNum), origin, m_titleScale);
    spriteBatch->End();
}