#include "pch.h"
#include"common.h"
#include"BaseScene.h"
#include "MainGameScene.h"

//���C���V�[������
MainGameScene::MainGameScene(vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mainGameUI, vector<Vector2> mainGameUIPos, vector<float> mainGameUIScale):
    m_mainGameUI(mainGameUI),
    m_mainGameUIPos(mainGameUIPos),
    m_mainGameUIScale(mainGameUIScale),
    isFinish(false)
{

}

//���C���V�[���j��
MainGameScene::~MainGameScene()
{

}

//���C���V�[���X�V
void MainGameScene::Update(DirectX::GamePad::State padState)
{

}

//���C���V�[���`��
void MainGameScene::Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spritebatch)
{
    auto spriteBatch = spritebatch;
    for (int i = initializeNum; i < m_mainGameUI.size(); i++)
    {
        spriteBatch->Draw(m_mainGameUI.at(i).Get(), m_mainGameUIPos.at(i), nullptr, Colors::White, static_cast<float>(initializeNum), Vector2::Zero, m_mainGameUIScale.at(i), SpriteEffects_None, m_UIDepth);
    }
}