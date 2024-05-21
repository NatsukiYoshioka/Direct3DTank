#include "pch.h"
#include "BaseScene.h"
#include "ResultScene.h"

extern void ExitGame() noexcept;

//���U���g�V�[������
ResultScene::ResultScene():
    isFinish(false)
{

}

//���U���g�V�[���j��
ResultScene::~ResultScene()
{

}

//���U���g�V�[���X�V
void ResultScene::Update(DirectX::GamePad::State padState)
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

//���U���g�V�[���`��
void ResultScene::Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch)
{

}