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
void MainGameScene::Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spritebatch)
{
    auto spriteBatch = spritebatch;
    int heartIndex = initializeNum;
    for (int i = initializeNum; i < m_mainGameUI.size(); i++)
    {
        if (i % int(hemipartition) == initializeNum)
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