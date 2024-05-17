#include "pch.h"
#include"BaseScene.h"
#include "TitleScene.h"

extern void ExitGame() noexcept;

TitleScene::TitleScene():
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
    }
}

void TitleScene::Draw()
{

}