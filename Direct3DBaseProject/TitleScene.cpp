#include "pch.h"
#include"common.h"
#include"TankManager.h"
#include"Tank.h"
#include"BaseScene.h"
#include"Game.h"
#include "TitleScene.h"

extern void ExitGame() noexcept;

const Vector2 TitleScene::m_titlePos = Vector2(940.f, 200.f);
const Vector2 TitleScene::m_titleScale = Vector2(1.f, 1.f);

const Vector2 TitleScene::m_confirmPos = Vector2(240.f, 50.f);

const Vector2 TitleScene::m_backPos = Vector2(190.f, 150.f);
const Vector2 TitleScene::m_selectPos = Vector2(220.f, 250.f);
const Vector2 TitleScene::m_playPos = Vector2(785.f, 830.f);
const Vector2 TitleScene::m_controlsPos = Vector2(1210.f, 830.f);
const Vector2 TitleScene::m_movePos = Vector2(950.f, 450.f);
const Vector2 TitleScene::m_anglePos = Vector2(950.f, 650.f);
const Vector2 TitleScene::m_shotPos = Vector2(950.f, 850.f);
const Vector2 TitleScene::m_descriptionStringScale= Vector2(0.35f, 0.35f);

//タイトルシーン初期化
TitleScene::TitleScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> titleUI, vector<Vector2> titleUIPos, vector<float> titleUIScale):
    m_titleUI(titleUI),
    m_titleUIPos(titleUIPos),
    m_titleUIScale(titleUIScale),
    m_nowSelect(m_leftIndex),
    m_choose(initializeNum),
    m_isFinish(false)
{
    
}

//タイトルシーン破棄
TitleScene::~TitleScene()
{

}

//タイトルシーン更新
void TitleScene::Update(DirectX::GamePad::State padState, TankManager* tankManager)
{
    if (padState.IsConnected())
    {
        if (padState.IsViewPressed())
        {
            ExitGame();
        }
        if (m_choose == initializeNum)
        {
            if (padState.IsLeftThumbStickRight())
            {
                m_nowSelect = m_rightIndex;
            }
            if (padState.IsLeftThumbStickLeft())
            {
                m_nowSelect = m_leftIndex;
            }
        }
        if (padState.IsAPressed() && m_choose == initializeNum)
        {
            m_choose = m_nowSelect;
        }
        if (padState.IsBPressed() && m_choose == m_rightIndex)
        {
            m_choose = initializeNum;
        }
    }
    if (m_choose == m_leftIndex)
    {
        m_isFinish = true;
    }
}

//タイトルシーン描画
void TitleScene::Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spritebatch, ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout, ID3D11Device* deviceResources)
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
            if (m_choose == m_rightIndex)
            {
                spriteBatch->Draw(m_titleUI.at(i).Get(), m_titleUIPos.at(i), nullptr, Colors::White, static_cast<float>(initializeNum), Vector2::Zero, m_titleUIScale.at(i), SpriteEffects_None, m_descriptionUIDepth);
            }
        }
        else if (i >= m_descriptionButtonUIIndex)
        {
            if (m_choose == m_rightIndex)
            {
                spriteBatch->Draw(m_titleUI.at(i).Get(), m_titleUIPos.at(i), nullptr, Colors::White, static_cast<float>(initializeNum), Vector2::Zero, m_titleUIScale.at(i), SpriteEffects_None, m_descriptionUIDepth);
            }
        }
        else
        {
            spriteBatch->Draw(m_titleUI.at(i).Get(), m_titleUIPos.at(i), nullptr, Colors::White, static_cast<float>(initializeNum), Vector2::Zero, m_titleUIScale.at(i), SpriteEffects_None, m_UIDepth);
        }
    }
    //タイトル名の描画
    origin = defaultFont->MeasureString(m_title) / hemipartition;
    defaultFont->DrawString(spriteBatch, m_title, m_titlePos, Colors::BurlyWood, static_cast<float>(initializeNum), origin, m_titleScale, SpriteEffects_None, m_stringDepth);

    //基本操作の文字描画
    origin = defaultFont->MeasureString(m_confirm) / hemipartition;
    defaultFont->DrawString(spriteBatch, m_confirm, m_confirmPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_stringDepth);

    origin = defaultFont->MeasureString(m_back) / hemipartition;
    defaultFont->DrawString(spriteBatch, m_back, m_backPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_stringDepth);

    origin = defaultFont->MeasureString(m_select) / hemipartition;
    defaultFont->DrawString(spriteBatch, m_select, m_selectPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_stringDepth);

    origin = defaultFont->MeasureString(m_play) / hemipartition;
    origin = defaultFont->MeasureString(m_controls) / hemipartition;
    Vector2 fixPos;

    //ゲーム選択ボタンの文字描画
    if (int(Game::GetTime() * m_timeSpeed) % int(hemipartition) == initializeNum)
    {
        defaultFont->DrawString(spriteBatch, m_play, m_playPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_stringDepth);
        defaultFont->DrawString(spriteBatch, m_controls, m_controlsPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_stringDepth);
    }
    else if (m_nowSelect == m_leftIndex)
    {
        fixPos.x = m_playPos.x;
        fixPos.y = m_playPos.y + m_fixButtonY;
        defaultFont->DrawString(spriteBatch, m_play, fixPos, Colors::DarkGray, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_stringDepth);
        defaultFont->DrawString(spriteBatch, m_controls, m_controlsPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_stringDepth);
    }
    else
    {
        fixPos.x = m_controlsPos.x;
        fixPos.y = m_controlsPos.y + m_fixButtonY;
        defaultFont->DrawString(spriteBatch, m_play, m_playPos, Colors::Beige, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_stringDepth);
        defaultFont->DrawString(spriteBatch, m_controls, fixPos, Colors::DarkGray, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_stringDepth);
    }
    
    //ゲーム操作説明文字の描画
    if (m_choose == m_rightIndex)
    {
        origin = defaultFont->MeasureString(m_move) / hemipartition;
        defaultFont->DrawString(spriteBatch, m_move, m_movePos, Colors::Black, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_descriptionStringDepth);

        origin = defaultFont->MeasureString(m_angle) / hemipartition;
        defaultFont->DrawString(spriteBatch, m_angle, m_anglePos, Colors::Black, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_descriptionStringDepth);

        origin = defaultFont->MeasureString(m_shot) / hemipartition;
        defaultFont->DrawString(spriteBatch, m_shot, m_shotPos, Colors::Black, static_cast<float>(initializeNum), origin, m_descriptionStringScale, SpriteEffects_None, m_descriptionStringDepth);
    }
}