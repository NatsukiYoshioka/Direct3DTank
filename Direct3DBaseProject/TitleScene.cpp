#include "pch.h"
#include"common.h"
#include"BaseScene.h"
#include"Game.h"
#include "TitleScene.h"

extern void ExitGame() noexcept;

const Vector2 TitleScene::m_titlePos = Vector2(960.f, 200.f);
const Vector2 TitleScene::m_titleScale = Vector2(1.f, 1.f);

const Vector2 TitleScene::m_playPos = Vector2(785.f, 830.f);
const Vector2 TitleScene::m_playScale = Vector2(0.35f, 0.35f);

const Vector2 TitleScene::m_controlsPos = Vector2(1210.f, 830.f);
const Vector2 TitleScene::m_controlsScale = Vector2(0.35f, 0.35f);


//タイトルシーン初期化
TitleScene::TitleScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale):
    m_titleUI(titleUI),
    m_titleUIPos(titleUIPos),
    m_titleUIScale(titleUIScale),
    m_nowSelect(m_leftIndex),
    isFinish(false)
{
    
}

//タイトルシーン破棄
TitleScene::~TitleScene()
{

}

//タイトルシーン更新
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
        if (padState.IsLeftThumbStickRight())
        {
            m_nowSelect = m_rightIndex;
        }
        if (padState.IsLeftThumbStickLeft())
        {
            m_nowSelect = m_leftIndex;
        }
    }
}

//タイトルシーン描画
void TitleScene::Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spritebatch)
{
    auto defaultFont = defaultfont;
    auto spriteBatch = spritebatch;

    Vector2 origin;
    
    //UIテクスチャの描画
    for (int i = initializeNum; i < m_titleUI.size(); i++)
    {
        if (i == m_nowSelect)
        {
            if (int(Game::GetTime() * m_timeSpeed) % int(hemipartition) == initializeNum)
            {
                spriteBatch->Draw(m_titleUI.at(i).Get(), m_titleUIPos.at(i), nullptr, Colors::White, static_cast<float>(initializeNum), Vector2::Zero, m_titleUIScale.at(i), SpriteEffects_None, m_UIDepth);
            }
        }
        else if (i == m_descriptionUIIndex)
        {
            spriteBatch->Draw(m_titleUI.at(i).Get(), m_titleUIPos.at(i), nullptr, Colors::White, static_cast<float>(initializeNum), Vector2::Zero, m_titleUIScale.at(i), SpriteEffects_None, m_descriptionUIDepth);
        }
        else
        {
            spriteBatch->Draw(m_titleUI.at(i).Get(), m_titleUIPos.at(i), nullptr, Colors::White, static_cast<float>(initializeNum), Vector2::Zero, m_titleUIScale.at(i), SpriteEffects_None, m_UIDepth);
        }
    }
    //タイトル名の描画
    origin = defaultFont->MeasureString(m_title) / hemipartition;
    defaultFont->DrawString(spriteBatch, m_title, m_titlePos, Colors::BurlyWood, static_cast<float>(initializeNum), origin, m_titleScale, SpriteEffects_None, m_stringDepth);

    origin = defaultFont->MeasureString(m_play) / hemipartition;
    origin = defaultFont->MeasureString(m_controls) / hemipartition;
    Vector2 fixPos;

    //ゲーム選択ボタンの文字描画
    if (int(Game::GetTime() * m_timeSpeed) % int(hemipartition) == initializeNum)
    {
        defaultFont->DrawString(spriteBatch, m_play, m_playPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_playScale, SpriteEffects_None, m_stringDepth);
        defaultFont->DrawString(spriteBatch, m_controls, m_controlsPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_controlsScale, SpriteEffects_None, m_stringDepth);
    }
    else if (m_nowSelect == m_leftIndex)
    {
        fixPos.x = m_playPos.x;
        fixPos.y = m_playPos.y + m_fixButtonY;
        defaultFont->DrawString(spriteBatch, m_play, fixPos, Colors::DarkGray, static_cast<float>(initializeNum), origin, m_playScale, SpriteEffects_None, m_stringDepth);
        defaultFont->DrawString(spriteBatch, m_controls, m_controlsPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_controlsScale, SpriteEffects_None, m_stringDepth);
    }
    else
    {
        fixPos.x = m_controlsPos.x;
        fixPos.y = m_controlsPos.y + m_fixButtonY;
        defaultFont->DrawString(spriteBatch, m_play, m_playPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_playScale, SpriteEffects_None, m_stringDepth);
        defaultFont->DrawString(spriteBatch, m_controls, fixPos, Colors::DarkGray, static_cast<float>(initializeNum), origin, m_controlsScale, SpriteEffects_None, m_stringDepth);
    }
    
}