#include "pch.h"
#include "BaseScene.h"
#include "ResultScene.h"

extern void ExitGame() noexcept;

//リザルトシーン生成
ResultScene::ResultScene():
    isFinish(false)
{

}

//リザルトシーン破棄
ResultScene::~ResultScene()
{

}

//リザルトシーン更新
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

//リザルトシーン描画
void ResultScene::Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch)
{

}