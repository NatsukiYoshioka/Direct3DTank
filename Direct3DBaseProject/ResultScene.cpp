#include "pch.h"
#include "BaseScene.h"
#include "ResultScene.h"

extern void ExitGame() noexcept;

ResultScene::ResultScene():
    isFinish(false)
{

}

ResultScene::~ResultScene()
{

}

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

void ResultScene::Draw()
{

}